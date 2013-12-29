pilrc  address.rcp
m68k-palmos-coff-gcc -O1 -c  address.c -o address.o
m68k-palmos-coff-gcc -O1  address.o -o address
m68k-palmos-coff-obj-res  address
build-prc  address.prc "AdrsTest" CHEN  *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del address.o
@del *.bak
@del address