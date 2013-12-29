# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/

LIBC= $(CLIENTLIBDIR)libclient3.a

include ./make.rules


LIB3SRC=lib3.c
LIB3OBJ=FldCalcFieldHeight.o      \
FldCompactText.o      \
FldCopy.o      \
FldCut.o	\
FldDelete.o      \
FldDirty.o      \
FldDrawField.o      \
FldEraseField.o      \
FldFreeMemory.o      \
FldGetAttributes.o      \
FldGetBounds.o      \
FldGetFont.o      \
FldGetInsPtPosition.o      \
FldGetMaxChars.o      \
FldGetNumberOfBlankLines.o      \
FldGetScrollPosition.o      \
FldGetScrollValues.o      \
FldGetSelection.o      \
FldGetTextAllocatedSize.o      \
FldGetTextHandle.o      \
FldGetTextHeight.o      \
FldGetTextLength.o      \
FldGetTextPtr.o      \
FldGetVisibleLines.o      \
FldGrabFocus.o      \
FldHandleEvent.o      \
FldInsert.o      \
FldMakeFullyVisible.o      \
FldNewField.o      \
FldPaste.o      \
FldRecalculateField.o      \
FldReleaseFocus.o      \
FldScrollable.o      \
FldScrollField.o      \
FldSendChangeNotification.o      \
FldSendHeightChangeNotification.o      \
FldSetAttributes.o      \
FldSetBounds.o      \
FldSetDirty.o      \
FldSetFont.o      \
FldSetInsertionPoint.o      \
FldSetInsPtPosition.o      \
FldSetMaxChars.o      \
FldSetScrollPosition.o      \
FldSetSelection.o      \
FldSetText.o      \
FldSetTextAllocatedSize.o      \
FldSetTextHandle.o      \
FldSetTextPtr.o      \
FldSetUsable.o      \
FldUndo.o      \
FldWordWrap.o      \
FileClearerr.o      \
FileClose.o      \
FileControl.o      \
FileDelete.o      \
FileDmRead.o      \
FileEOF.o      \
FileError.o      \
FileFlush.o      \
FileGetLastError.o      \
FileOpen.o      \
FileRead.o      \
FileRewind.o      \
FileSeek.o      \
FileTell.o      \
FileTruncate.o      \
FileWrite.o      \
FindDrawHeader.o	\
FindGetLineBounds.o	\
FindSaveMatch.o		\
FindStrInStr.o		\
FplAdd.o			\
FplAToF.o			\
FplBase10Info.o		\
FplDiv.o			\
FplFloatToLong.o		\
FplFloatToULong.o		\
FplFree.o			\
FplFToA.o			\
FplInit.o			\
FplLongToFloat.o		\
FplMul.o			\
FplSub.o





OBJ= $(LIB3OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: $(LIBC)
	@$(RM) $(OBJ)
	

$(LIBC): $(LIBC)($(OBJ))

$(LIBC)($(LIB3OBJ)): $(LIB3SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o



transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient3.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

