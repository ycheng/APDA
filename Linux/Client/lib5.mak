# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/

LIBC=$(CLIENTLIBDIR)libclient5.a

include ./make.rules

LIB5SRC=lib5.c
LIB5OBJ=LIB5OBJ=GrfAdDmacro.o		\
GrfAddPoint.o				\
GrfCleanState.o			\
GrfDeleteMacro.o		\
GrfFilterPoints.o		\
GrfFindBranch.o			\
GrfFlushPoints.o		\
GrfGetAndExpanDmacro.o		\
GrfGetGlyphMapping.o		\
GrfGetMacro.o			\
GrfGetMacroName.o		\
GrfGetNumPoints.o		\
GrfGetPoint.o			\
GrfGetState.o			\
GrfInitState.o			\
GrfMatch.o			\
GrfMatchGlyph.o			\
GrfProcessStroke.o		\
GrfSetState.o			\
GsiEnable.o      \
GsiEnabled.o      \
GsiInitialize.o      \
GsiSetLocation.o      \
GsiSetShiftState.o      \
InsPtEnable.o      \
InsPtEnabled.o      \
InsPtGetHeight.o      \
InsPtGetLocation.o      \
InsPtSetHeight.o      \
InsPtSetLocation.o      \
KeyCurrentState.o		\
KeyRates.o			\
KeySetMask.o			\
IrAdvanceCredit.o		\
IrBind.o			\
IrClose.o			\
IrConnectIrLap.o		\
IrConnectReq.o			\
IrConnectRsp.o			\
IrDataReq.o			\
IrDisconnectIrLap.o		\
IrDiscoverReq.o			\
IrIsIrLapConnected.o		\
IrIsMediaBusy.o			\
IrIsNoProgress.o		\
IrIsRemoteBusy.o		\
IrLocalBusy.o			\
IrMaxRxSize.o			\
IrMaxTxSize.o			\
IrOpen.o			\
IrSetConTypeLMP.o		\
IrSetConTypeTTP.o		\
IrSetDeviceInfo.o		\
IrTestReq.o			\
IrUnbind.o			\
IrIAS_Add.o			\
IrIAS_GetInteger.o		\
IrIAS_GetIntLsap.o		\
IrIAS_GetObjectID.o		\
IrIAS_GetOctetString.o		\
IrIAS_GetOctetStringLen.o	\
IrIAS_GetType.o			\
IrIAS_GetUserString.o		\
IrIAS_GetUserStringCharSet.o	\
rIAS_GetUserStringLen.o		\
IrIAS_Next.o			\
IrIAS_Query.o			\
IrIAS_SetDeviceName.o		\
IrIAS_StartResult.o		\
LstDrawList.o      \
LstEraseList.o      \
LstGetNumberOfItems.o      \
LstGetSelection.o      \
LstGetSelectionText.o      \
LstGetVisibleItems.o      \
LstHandleEvent.o      \
LstMakeItemVisible.o      \
LstNewList.o      \
LstPopupList.o      \
LstScrollList.o      \
LstSetDrawFunction.o      \
LstSetHeight.o      \
LstSetListChoices.o      \
LstSetPosition.o      \
LstSetSelection.o      \
LstSetTopItem.o



OBJ=  $(LIB5OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: 	$(LIBC)
	@$(RM) $(OBJ)

$(LIBC): $(LIBC)($(OBJ))


$(LIBC)($(LIB5OBJ)): $(LIB5SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o


transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient5.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

