pilrc  mail.rcp
m68k-palmos-coff-gcc -O1 -c  mail.c -o mail.o
m68k-palmos-coff-gcc -O1  mail.o -o mail
m68k-palmos-coff-obj-res  mail
build-prc  mail.prc "Mail" CATS *.grc *.bin
dir  *.prc
@del *.grc
@del *.bin
@del mail.o
@del *.bak
@del mail
 
