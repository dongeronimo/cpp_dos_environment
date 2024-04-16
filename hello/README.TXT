How to build

Assuming OpenWatcom installed you can build using command line 
or the makefile

command line:
c:\hello> wcc386 main.c
c:\hello> wcc386 hello.c
c:\hello> wlink name hello.exe file { main.obj hello.obj }

Or using the makefile
c:\hello> wmake
