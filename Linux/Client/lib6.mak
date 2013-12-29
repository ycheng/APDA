# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/
LIBC=$(CLIENTLIBDIR)libclient6.a

include ./make.rules

LIB6SRC=lib6.c
LIB6OBJ=MemCardInfo.o      \
MemCmp.o      \
MemDebugMode.o      \
MemHandleCardNo.o      \
MemHandleDataStorage.o      \
MemHandleFree.o      \
MemHandleHeapID.o      \
MemHandleLock.o      \
MemHandleNew.o      \
MemHandleResize.o      \
MemHandleSetOwner.o      \
MemHandleSize.o      \
MemHandleToLocalID.o      \
MemHandleUnlock.o      \
MemHeapCheck.o      \
MemHeapCompact.o      \
MemHeapDynamic.o      \
MemHeapFlags.o      \
MemHeapFreeBytes.o      \
MemHeapID.o      \
MemHeapScramble.o      \
MemHeapSize.o      \
MemLocalIDKind.o      \
MemLocaIDToGlobal.o      \
MemLocalIDToLockedPtr.o      \
MemLocalIDToPtr.o      \
MemMove.o      \
MemNumCards.o      \
MemNumHeaps.o      \
MemNumRAMHeaps.o      \
MemPtrCardNo.o      \
MemPtrDataStorage.o      \
MemPtrFree.o      \
MemPtrHeapID.o      \
MemPtrNew.o      \
MemPtrRecoverHandle.o      \
MemPtrResize.o      \
MemPtrSetOwner.o      \
MemPtrSize.o      \
MemPtrToLocalID.o      \
MemPtrUnlock.o      \
MemSet.o      \
MemSetDebugMode.o      \
MemStoreInfo.o      \
MenuAddItem.o      \
MenuCmdBarAddButton.o      \
MenuCmdBarDisplay.o      \
MenuCmdBarGetButtonData.o      \
MenuDispose.o      \
MenuDrawMenu.o      \
MenuEraseStatus.o      \
MenuGetActiveMenu.o      \
MenuHandleEvent.o      \
MenuHideItem.o      \
MenuInit.o      \
MenuSetActiveMenu.o      \
MenuSetActiveMenuRscID.o      \
MenuShowItem.o      \
Crc16CalcBlock.o		\
IntlGetRoutineAddress.o		\
LocGetNumberSeparators.o	\
MdmDial.o			\
MdmHangUp.o			\
NetHToNL.o			\
NetHToNS.o			\
NetLibAddrAToIN.o		\
NetLibAddrINToA.o		\
NetLibClose.o			\
NetLibConnectionRefresh.o	\
NetLibDmReceive.o		\
NetLibFinishCloseWait.o		\
NetLibGetHostByAddr.o		\
NetLibGetHostByName.o		\
NetLibGetMailExchangeByName.o	\
NetLibGetServByName.o		\
NetLibIFAttach.o		\
NetLibIFDetach.o		\
NetLibIFDown.o			\
NetLibIFGet.o			\
NetLibIFSettingGet.o		\
NetLibIFSettingSet.o		\
NetLibIFUp.o			\
NetLibMaster.o			\
NetLibOpen.o			\
NetLibOpenCount.o		\
NetLibReceive.o			\
NetLibReceivePB.o		\
NetLibSelect.o			\
NetLibSend.o			\
NetLibSendPB.o			\
NetLibSettingGet.o		\
NetLibSettingSet.o		\
NetLibSocketAddr.o		\
NetLibSocketBind.o		\
NetLibSocketClose.o		\
NetLibSocketConnect.o		\
NetLibSocketListen.o		\
NetLibSocketOpen.o		\
NetLibSocketOptionGet.o		\
NetLibSocketOptionSet.o		\
NetLibSocketShutdown.o		\
NetLibTracePrintF.o		\
NetNToHL.o			\
NetNToHS.o			\
NetUReadN.o			\
NetUTCPOpen.o			\
NetUWriteN.o







OBJ=  $(LIB6OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: 	$(LIBC)
	@$(RM) $(OBJ)

$(LIBC): $(LIBC)($(OBJ))


$(LIBC)($(LIB6OBJ)): $(LIB6SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o


transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)/libclient6.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

