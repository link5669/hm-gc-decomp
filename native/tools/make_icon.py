#!/usr/bin/env python3
"""Draw a simple 256x256 ghost icon (no game assets)."""
import sys
from PIL import Image, ImageDraw
im = Image.new('RGBA', (256, 256), (0, 0, 0, 0))
d = ImageDraw.Draw(im)
d.rounded_rectangle((8, 8, 248, 248), 48, fill=(34, 20, 58, 255))
d.ellipse((68, 40, 188, 160), fill=(225, 235, 255, 255))
d.rectangle((68, 100, 188, 200), fill=(225, 235, 255, 255))
for i in range(4):
    x = 68 + i * 30
    d.polygon([(x, 200), (x + 15, 222), (x + 30, 200)], fill=(225, 235, 255, 255))
d.ellipse((96, 84, 118, 112), fill=(34, 20, 58, 255)); d.ellipse((138, 84, 160, 112), fill=(34, 20, 58, 255))
d.ellipse((116, 128, 140, 156), fill=(34, 20, 58, 255))
im.save(sys.argv[1])
