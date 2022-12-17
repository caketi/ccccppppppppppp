
def Myreadlines(f, newline):
    buf = ""
    while True:
        while newline in buf:
            pos = buf.index(newline)
            yield buf[:pos]
            buf = buf[pos+len(newline):]
        chunk = f.read(4096)
        if not chunk:
            yield buf
            break
        buf += chunk
with open('sort.txt') as f:
    for line in Myreadlines(f, "-"):
        print(line)