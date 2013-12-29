# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/

LIBC= $(CLIENTLIBDIR)libclient1.a

include ./make.rules


LIB1SRC=lib1.c
LIB1OBJ=AlmGetAlarm.o      \
AlmGetProcAlarm.o      \
AlmSetAlarm.o      \
AlmSetProcAlarm.o      \
BmpBitsSize.o		\
BmpColortableSize.o	\
BmpCompress.o		\
BmpCreate.o		\
BmpDelete.o		\
BmpGetBits.o		\
BmpGetColortable.o	\
BmpSize.o		\
ColorTableEntries.o	\
CategoryCreateList.o		\
CategoryCreateListV10.o		\
CategoryEdit.o			\
CategoryEditV20.o		\
CategoryEditV10.o		\
CategoryFind.o			\
CategoryFreeList.o		\
CategoryFreeListV10.o	\
CategoryGetName.o	\
CategoryGetNext.o	\
CategoryInitialize.o	\
CategorySelect.o	\
CategorySelectV10.o	\
CategorySetName.o	\
CategorySetTriggerLabel.o	\
CategoryTruncateName.o		\
ChrHorizEllipsis.o 		\
ChrIsHardKey.o			\
ChrNumericSpace.o 		\
GetCharAttr.o			\
GetCharCaselessValue.o 		\
GetCharSortValue.o 		\
ClipboardAddItem.o      \
ClipboardAppendItem.o      \
ClipboardGetItem.o      \
CncAddProfile.o		\
CncDeleteProfile.o	\
CncGetProfileInfo.o	\
CncGetProfileList.o	\
CtlDrawControl.o      \
CtlEnabled.o      \
CtlEraseControl.o      \
CtlGetLabel.o      \
CtlGetSliderValues.o      \
CtlGetValue.o      \
CtlHandleEvent.o      \
CtlHideControl.o      \
CtlHitControl.o      \
CtlNewControl.o      \
CtlNewGraphicControl.o      \
CtlNewSliderControl.o      \
CtlSetEnabled.o      \
CtlSetLabel.o      \
CtlSetGraphics.o      \
CtlSetSliderValue.o      \
CtlSetUsable.o      \
CtlSetValue.o      \
CtlShowControl.o      \
CtlValidatePointer.o      \
DayHandleEvent.o		\
SelectDay.o		\
SelectDayV10.o		\
SelectOneTime.o		\
SelectTime.o		\
SelectTimeV33.o




OBJ= $(LIB1OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: $(LIBC)
	@$(RM) $(OBJ)


$(LIBC): $(LIBC)($(OBJ))

$(LIBC)($(LIB1OBJ)): $(LIB1SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o



transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient1.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

