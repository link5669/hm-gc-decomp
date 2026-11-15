# .gxcap: GPU test captures

The runtime writes these when started with `HM_GXCAP=<file> HM_GXCAP_FRAME=<n>`. They record frames n..n+k.
All integers are little-endian. File = "GXCAP001" then records `{u32 tag; u32 len; u8 payload[len]}`:

- `'RAMS'` (0x534D4152): full 24 MiB guest RAM snapshot. Always the first record.
- `'MEMW'`: `u32 phys_addr` then `len-4` bytes. Guest RAM changed at this point in the stream (4 KiB pages
  that the CPU dirtied since the previous FIFO record). Apply it before the following FIFO bytes.
- `'FIFO'`: GP command-stream bytes, to pass to gpu_fifo_write in order.
- `'FRME'`: a frame boundary marker (the CPU reached VI retrace). Payload u32 frame number.

A player (gpu/tools/gxplay) replays the records: RAMS into a 24 MiB buffer, MEMW memcpy, FIFO to gpu_fifo_write.
At each gpu_cb_xfb_copy it saves a PNG of the presented image.
