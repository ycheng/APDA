# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/

LIBC=$(CLIENTLIBDIR)libclient8.a

include ./make.rules


LIB8SRC=lib8.c
LIB8OBJ=SndCreateMidiList.o		\
SndDoCmd.o				\
SndGetDefaultVolume.o			\
SndPlaySmf.o				\
SndPlaySmfResource.o			\
SndPlaySystemSound.o			\
SioClearScreen.o			\
SioExecCommand.o			\
SioFree.o				\
SioHandleEvent.o			\
SioInit.o				\
StrAToI.o				\
StrCaselessCompare.o		\
StrCat.o			\
StrChr.o			\
StrCompare.o			\
StrCopy.o			\
StrDelocalizeNumber.o	\
StrIToA.o		\
StrIToH.o		\
StrLen.o		\
StrLocalizeNumber.o	\
StrNCaselessCompare.o	\
StrNCat.o		\
StrNCompare.o		\
StrNCopy.o		\
StrPrintF.o		\
StrStr.o		\
StrToLower.o		\
StrVPrintF.o		\
SysAppLauncherDialog.o	\
SysFatalAlert.o                 \
SysGraffitiReferenceDialog.o	\
EvtAddEventToQueue.o		\
EvtAddUniqueEventToQueue.o	\
EvtCopyEvent.o			\
EvtDequeuePenPoint.o		\
EvtDequeuePenStrokeInfo.o	\
EvtEnableGraffiti.o		\
EvtEnqueueKey.o			\
EvtEventAvail.o			\
EvtFlushKeyQueue.o		\
EvtFlushNextPenStroke.o		\
EvtFlushPenQueue.o		\
EvtGetEvent.o			\
EvtGetPen.o		\
EvtGetPenBtnList.o	\
EvtGetSilkscreenAreaList.o	\
EvtKeydownIsVirtual.o		\
EvtKeyQueueEmpty.o		\
EvtKeyQueueSize.o		\
EvtPenQueueSize.o		\
EvtProcessSoftKeyStroke.o	\
EvtResetAutoOffTimer.o		\
EvtSetAutoOffTimer.o		\
EvtSetNullEventTick.o		\
EvtSysEventAvail.o		\
EvtWakeup.o			\
SysAppLaunch.o			\
SysBatteryInfo.o		\
SysBatteryInfoV20.o		\
SysBinarySearch.o		\
SysBroadcastActionCode.o	\
SysCopyStringResource.o		\
SysCreateDataBaseList.o		\
SysCreatePanelList.o		\
SysCurAppDatabase.o		\
SysErrString.o			\
SysFormPointerArrayToStrings.o	\
SysGetOSVersionString.o		\
SysGetROMToken.o		\
SysGetStackInfo.o		\
SysGetTrapAddress.o		\
SysGraffitiReferenceDialogs.o	\
SysGremlins.o		\
SysHandleEvent.o	\
SysInsertionSort.o	\
SysKeyboardDialog.o	\
SysKeyboardDialogV10.o	\
SysLibFind.o		\
SysLibLoad.o		\
SysLibRemove.o		\
SysQSort.o		\
SysRandom.o		\
SysReset.o		\
SysSetAutoOffTime.o	\
SysSetTrapAddress.o	\
SysStringByIndex.o	\
SysTaskDelay.o		\
SysTicksPerSecond.o	\
SysUIAppSwitch.o	\
TxtByteAttr.o		\
TxtCaselessCompare.o	\
TxtCharAttr.o		\
TxtCharBounds.o		\
TxtCharEncoding.o	\
TxtCharIsAlNum.o	\
TxtCharIsAlphal.o	\
TxtCharIsCntrl.o	\
TxtCharIsDelim.o	\
TxtCharIsDigit.o	\
TxtCharIsGraph.o	\
TxtCharIsHardKey.o	\
TxtCharIsHex.o		\
TxtCharIsLower.o	\
TxtCharIsPrint.o	\
TxtCharIsPunct.o	\
TxtCharIsSpace.o	\
TxtCharIsUpper.o	\
TxtCharIsValid.o	\
TxtCharSize.o		\
TxtCharWidth.o		\
TxtCharXAttr.o		\
TxtCompare.o		\
TxtEncodingName.o	\
TxtFindString.o		\
TxtGetChar.o		\
TxtGetNextChar.o	\
TxtGetPreviousChar.o	\
TxtGetTruncationOffset.o	\
TxtMaxEncoding.o		\
TxtNextCharSize.o		\
TxtParamString.o		\
TxtPreviousCharSize.o	\
TxtReplaceStr.o		\
TxtSetNextChar.o	\
TxtStrEncoding.o	\
TxtTransliterate.o	\
TxtWordBounds.o





OBJ=  $(LIB8OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: 	$(LIBC)
	@$(RM) $(OBJ)

$(LIBC): $(LIBC)($(OBJ))


$(LIBC)($(LIB8OBJ)): $(LIB8SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o


transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient8.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

