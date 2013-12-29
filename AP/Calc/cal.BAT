pilrc  calculator.rcp
m68k-palmos-coff-gcc -O1 -c  calculator.c -o calculator.o
m68k-palmos-coff-gcc -O1     calculator.o -o calculator
m68k-palmos-coff-obj-res  calculator
build-prc  calculator.prc "CalDemo" CATS *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del calculator.o
@del *.bak
@del calculator
 