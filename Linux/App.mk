ifeq ($(BLD_ROOT),)

BLD_ROOT	=	../../../
endif
#APP_BASE	=	$(BLD_ROOT)Apps/
LIBC_BASE	=	$(BLD_ROOT)uClibc/

CROSS_COMPILE	=	arm-elf-
CC		=	$(CROSS_COMPILE)gcc
C++		=	$(CROSS_COMPILE)g++
AS		=	$(CROSS_COMPILE)as
LD		=	$(CROSS_COMPILE)ld
OBJCOPY 	=	$(CROSS_COMPILE)objcopy
OBJDUMP		=	$(CROSS_COMPILE)objdump
DEL		=	/bin/rm -f

STARTS		=	$(LIBC_BASE)lib/crt0.o
ifeq ($(ARCH_CFLAGS),)
ARCH_CFLAGS	=
endif
ifeq ($(CPU_CFLAGS),)
CPU_CFLAGS	=	-msoft-float -mcpu=arm7tdmi -fomit-frame-pointer
endif
DFLAGS		=	-D_uclinux_ -DEMBED
CFLAGS		=	-I$(LIBC_BASE)include $(ARCH_CFLAGS) $(CPU_CFLAGS) $(DFLAGS)
ASFLAGS 	=
LDFLAGS 	=	-elf2flt -L$(LIBC_BASE)lib
lFLAGS		=	-lc -lgcc -lc
OPTIMIZATION	=	-O1
ifndef OPTIMIZATION
OPTIMIZATION = ${shell if $(CC) -Os -S -o /dev/null -xc /dev/null >/dev/null 2>&1; \
    then echo "-Os"; else echo "-O2" ; fi}
endif

ifeq ($(__USE_OLD_UCLIBC__),yes)
LIBC_BASE	=	$(BLD_ROOT)uClibc/
STARTS		=	$(LIBC_BASE)sysdeps/arm/crt0.o
LDFLAGS 	=	-L$(LIBC_BASE)
endif

LIBGCCPATH	=	${shell $(CC) $(CFLAGS) -print-libgcc-file-name | sed -ne "s/\.*\/libgcc.a//p"}
LDFLAGS		+=	-L$(LIBGCCPATH)
ifneq ($(filter arm-elf-,$(CROSS_COMPILE)),)
CRTBEGIN	=	$(LIBGCCPATH)/crtbegin.o
CRTEND		=	$(LIBGCCPATH)/crtend.o
endif

.c.o:
	$(CC) $(CFLAGS) $(OPTIMIZATION) -o $@ -c $<

.S.o:
	$(AS) $(ASFLAGS) -o $@ $<

.PHONY: all clean

all:: $(TARGET)
	rm $(OUTDIR)$(TARGET).gdb

$(TARGET): $(OBJECTS)
	FLTFLAGS=-z $(LD) $(LDFLAGS) -o $(OUTDIR)$@ $(STARTS) $(CRTBEGIN) $^ $(CRTEND) $(lFLAGS)

clean::
	@$(DEL) $(OUTDIR)$(TARGET) $(OUTDIR)$(TARGET).elf $(OUTDIR)$(TARGET).gdb $(OBJECTS)
