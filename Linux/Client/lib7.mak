# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/
LIBC=$(CLIENTLIBDIR)libclient7.a

include ./make.rules

LIB7SRC=lib7.c
LIB7OBJ=SrmClearErr.o		\
SrmClose.o			\
SrmControl.o			\
SrmGetDeviceCount.o		\
SrmGetDeviceInfo.o		\
SrmGetStatus.o			\
SrmOpen.o			\
SrmOpenBackground.o		\
SrmPrimeWakeupHandler.o		\
SrmReceive.o			\
SrmReceiveCheck.o		\
SrmReceiveFlush.o		\
SrmReceiveWait.o		\
SrmReceiveWindowClose.o		\
SrmReceiveWindowOpen.o		\
SrmSend.o			\
SrmSend10.o			\
SrmSendFlush.o			\
SrmSendWait.o			\
SrmSetReceiveBuffer.o		\
SrmSetWakeupHandler.o		\
SysNotifyBroadcast.o		\
SysNotifyBroadcastDeferred.o	\
SysNotifyRegister.o		\
SysNotifyUnregister.o		\
OmGetCurrentLocale.o		\
OmGetIndexedLocale.o		\
OmGetRoutineAddress.o		\
OmGetSystemLocale.o		\
OmLocaleToOverlayDBName.o	\
OmOverlayDBNameToLocale.o	\
OmSetSystemLocale.o		\
PwdExists.o			\
PwdRemove.o			\
PwdSet.o			\
PwdVerify.o			\
PenCalibrate.o			\
PenResetCalibrate.o		\
PrefGetAppPreferences.o		\
PrefGetAppPreferencesV10.o	\
PrefGetPreference.o		\
PrefGetPreferences.o		\
PrefOpenPreferenceDBV10.o	\
PrefSetAppPreferences.o		\
PrefSetAppPreferencesV10.o	\
PrefSetPreference.o		\
PrefSetPreferences.o		\
SecSelectViewStatus.o		\
SecVerifyPW.o			\
PrgHandleEvent.o		\
PrgStartDialog.o		\
PrgStartDialogV31.o		\
PrgStopDialog.o			\
PrgUpdateDialog.o		\
PrgUserCancel.o			\
RctCopyRectangle.o		\
RctGetIntersection.o		\
RctInsetRectangle.o		\
RctOffsetRectangle.o		\
RctPtInRectangle.o		\
RctSetRectangle.o		\
ScriptPluginSelectorProc.o	\
SclDrawScrollBar.o		\
SclGetScrollBar.o		\
SclHandleEvent.o		\
SclSetScrollBar.o		\
DrvEntryPoint.o			\
SdrvClose.o			\
SdrvControl.o			\
SdrvISP.o			\
SdrvOpen.o			\
SdrvReadChar.o			\
SdrvStatus.o			\
SdrvWriteChar.o			\
SlkClose.o			\
SlkCloseSocket.o		\
SlkFlushSocket.o		\
SlkOpen.o			\
SlkOpenSocket.o			\
SlkReceivePacket.o		\
SlkSendPacket.o			\
SlkSetSocketListener.o		\
SlkSendFlush.o			\
SlkSocketSetTimeout.o		\
SerClearErr.o			\
SerClose.o			\
SerControl.o			\
SerGetSettings.o		\
SerGetStatus.o			\
SerOpen.o		\
SerReceive.o		\
SerReceive10.o		\
SerReceiveCheck.o	\
SerReceiveFlush.o	\
SerReceiveWait.o	\
SerSend.o		\
SerSendCheck.o		\
SerSendFlush.o		\
SerSendWait.o		\
SerSetReceiveBuffer.o	\
SerSetSettings.o	\
GetSize.o		\
GetSpace.o		\
WriteBlock.o		\
WriteByte.o





OBJ=  $(LIB7OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: 	$(LIBC)
	@$(RM) $(OBJ)

$(LIBC): $(LIBC)($(OBJ))


$(LIBC)($(LIB7OBJ)): $(LIB7SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o


transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient7.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

