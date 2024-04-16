obj = main.obj hello.obj
bin = hello.exe

CC = wcc386
CFLAGS = -zq
LD = wlink

$(bin): $(obj)
	$(LD) name $@ file { $(obj) }

.c.obj:
	$(CC) -fo=$@ $(CFLAGS) $<

clean: .symbolic
	del *.obj
	del $(bin) 