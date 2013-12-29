pilrc  memo.rcp
m68k-palmos-coff-gcc -O1 -c  memo.c -o memo.o
m68k-palmos-coff-gcc -O1  memo.o -o memo
m68k-palmos-coff-obj-res  memo
build-prc  memo.prc "MemoDemo" CATS *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del memo.o
@del *.bak
@del memo
 
