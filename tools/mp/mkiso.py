import struct,sys,os
"""mkiso.py EXTRACTED_DIR OUT.iso : build a GameCube disc image from an extracted disc (sys/ + files/),
 placing every file at its original FST offset (the FST moves to the end if main.dol grew)."""
E=sys.argv[1]; out=sys.argv[2]
S=lambda n:open(f"{E}/sys/{n}","rb").read()
boot,bi2,app,fst,dol=S("boot.bin"),S("bi2.bin"),S("apploader.img"),S("fst.bin"),S("main.dol")
dolo,fsto,fsts=struct.unpack(">III",boot[0x420:0x42c])
assert fsts==len(fst), (fsts,len(fst))
n0=struct.unpack(">I",fst[8:12])[0]
first_file=min(struct.unpack(">I",fst[i*12+4:i*12+8])[0] for i in range(1,n0) if fst[i*12]==0)
assert dolo+len(dol)<=first_file, "DOL overlaps file data"
if dolo+len(dol)>fsto:
    # DOL grew over the FST: move the FST to the end of the image and patch boot.bin
    end=max(struct.unpack(">I",fst[i*12+4:i*12+8])[0]+struct.unpack(">I",fst[i*12+8:i*12+12])[0] for i in range(1,n0) if fst[i*12]==0)
    fsto=(end+0x7FFF)&~0x7FFF
    boot=boot[:0x424]+struct.pack(">I",fsto)+boot[0x428:]
    print("FST moved to",hex(fsto))
f=open(out,"wb"); f.truncate(max(1459978240,fsto+len(fst)))
def w(o,d): f.seek(o); f.write(d)
w(0,boot); w(0x440,bi2); w(0x2440,app); w(dolo,dol); w(fsto,fst)
n=struct.unpack(">I",fst[8:12])[0]; st=n*12
def name(i):
    o=struct.unpack(">I",fst[i*12:i*12+4])[0]&0xffffff; e=fst.index(b"\0",st+o); return fst[st+o:e].decode("shift_jis")
def walk(i,end,path):
    while i<end:
        t=fst[i*12]; a,b=struct.unpack(">II",fst[i*12+4:i*12+12])
        if t: walk(i+1,b,path+[name(i)]); i=b
        else:
            p=os.path.join(E,"files",*path,name(i)); d=open(p,"rb").read(); assert len(d)==b,p; w(a,d); i+=1
walk(1,n,[]); f.close(); print("ok",n,"entries")
