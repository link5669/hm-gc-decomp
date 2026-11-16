#!/usr/bin/env python3
"""Haunted Mansion online co-op relay (Python 3.7+, no dependencies).

Hosts register a room, guests join it by code, the relay pipes bytes both ways.
Preamble (one text line each way, then raw bytes):
  host  -> "HMRELAY HOST [CODE]\n"   relay -> "OK CODE\n", later "WAIT\n" keepalives, then "PAIRED\n"
  guest -> "HMRELAY JOIN CODE\n"     relay -> "OK\n" (paired) or "ERR reason\n"
Usage: python3 hm_relay.py [--port 7778] [--idle 120] [--wait 3600]
"""
import argparse
import asyncio
import logging
import random
import string

ALPHABET = "ABCDEFGHJKLMNPQRSTUVWXYZ23456789"
log = logging.getLogger("hm_relay")


class Room:
    def __init__(self, code, reader, writer):
        self.code, self.reader, self.writer = code, reader, writer
        self.paired = asyncio.get_running_loop().create_future()


rooms = {}


def peer(w):
    p = w.get_extra_info("peername")
    return "%s:%s" % (p[0], p[1]) if p else "?"


async def pipe(reader, writer, idle, stats, key):
    try:
        while True:
            data = await asyncio.wait_for(reader.read(65536), timeout=idle)
            if not data:
                break
            stats[key] += len(data)
            writer.write(data)
            await writer.drain()  # back-pressure: never buffer more than the slow side accepts
    except (asyncio.TimeoutError, ConnectionError, OSError):
        pass
    finally:
        try:
            writer.close()
        except Exception:
            pass


async def handle(reader, writer, args):
    who = peer(writer)
    try:
        line = (await asyncio.wait_for(reader.readline(), timeout=15)).decode("ascii", "replace").strip()
    except (asyncio.TimeoutError, ConnectionError, OSError):
        writer.close()
        return
    parts = line.split()
    if len(parts) < 2 or parts[0] != "HMRELAY" or parts[1] not in ("HOST", "JOIN"):
        log.info("%s: bad preamble %r", who, line[:60])
        writer.close()
        return
    code = parts[2].upper()[:15] if len(parts) > 2 else ""
    if parts[1] == "HOST":
        if not code:
            code = "".join(random.SystemRandom().choice(ALPHABET) for _ in range(6))
        old = rooms.get(code)
        if old and not old.paired.done():
            old.paired.cancel()  # the same host reconnecting: replace the stale registration
            old.writer.close()
        room = Room(code, reader, writer)
        rooms[code] = room
        writer.write(("OK %s\n" % code).encode())
        await writer.drain()
        log.info("room %s: host %s waiting", code, who)
        waited = 0
        try:
            while True:  # keepalive while waiting; detects hosts that went away
                try:
                    await asyncio.wait_for(asyncio.shield(room.paired), timeout=20)
                    break
                except asyncio.TimeoutError:
                    if room.paired.done():
                        break
                    waited += 20
                    if waited >= args.wait:
                        raise ConnectionError("wait timeout")
                    writer.write(b"WAIT\n")
                    await writer.drain()
        except (asyncio.CancelledError, ConnectionError, OSError) as e:
            log.info("room %s: host %s gone (%s)", code, who, e.__class__.__name__)
            if rooms.get(code) is room:
                del rooms[code]
            writer.close()
            return
        return  # the guest's handler runs the pipes
    # JOIN
    room = rooms.get(code)
    if not room or room.paired.done():
        log.info("%s: join %s refused (%s)", who, code, "busy" if room else "no such room")
        writer.write(b"ERR " + (b"room busy" if room else b"no such room") + b"\n")
        await writer.drain()
        writer.close()
        return
    del rooms[code]
    room.paired.set_result(True)
    room.writer.write(b"PAIRED\n")
    writer.write(b"OK\n")
    log.info("room %s: guest %s paired with host %s", code, who, peer(room.writer))
    stats = {"up": 0, "down": 0}
    loop = asyncio.get_running_loop()
    t0 = loop.time()
    await asyncio.gather(pipe(reader, room.writer, args.idle, stats, "up"),
                         pipe(room.reader, writer, args.idle, stats, "down"))
    dt = max(loop.time() - t0, 1e-3)
    log.info("room %s: session ended after %.0f s (host->guest %.1f MB, %.2f Mbit/s; guest->host %.2f MB)",
             code, dt, stats["down"] / 1e6, stats["down"] * 8 / 1e6 / dt, stats["up"] / 1e6)


def main():
    ap = argparse.ArgumentParser(description="Haunted Mansion online co-op relay")
    ap.add_argument("--port", type=int, default=7778)
    ap.add_argument("--bind", default="0.0.0.0")
    ap.add_argument("--idle", type=float, default=120, help="close a session after this many seconds without data")
    ap.add_argument("--wait", type=float, default=3600, help="drop a waiting host after this many seconds")
    args = ap.parse_args()
    logging.basicConfig(level=logging.INFO, format="%(asctime)s %(message)s")
    async def serve():
        server = await asyncio.start_server(lambda r, w: handle(r, w, args), args.bind, args.port)
        log.info("hm_relay listening on %s:%d", args.bind, args.port)
        async with server:
            await server.serve_forever()
    try:
        asyncio.run(serve())
    except KeyboardInterrupt:
        pass

if __name__ == "__main__":
    main()
