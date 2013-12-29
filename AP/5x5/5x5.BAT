pilrc  5x5.rcp
m68k-palmos-coff-gcc -O1 -c  5x5.c -o 5x5.o
m68k-palmos-coff-gcc -O1     5x5.o -o 5x5
m68k-palmos-coff-obj-res  5x5
build-prc  5x5.prc "5x5" CATS *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del 5x5.o
@del *.bak
@del 5x5
 