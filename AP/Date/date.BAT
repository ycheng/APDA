pilrc  date.rcp
m68k-palmos-coff-gcc -O1 -c  date.c -o date.o
m68k-palmos-coff-gcc -O1     date.o -o date
m68k-palmos-coff-obj-res  date
build-prc  date.prc "DateDemo" CATS *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del date.o
@del *.bak
@del date
 