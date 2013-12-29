#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <linux/mman.h>
#include <linux/fb.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//#include <unistd.h>

#include <Common.h>
#include "wisapi.h"

#define	false		FALSE
#define	true		TRUE

extern struct FuncCount funcCount[];



////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 21/21 functions now.
////////////////////////////////////////////////////////////
#ifdef L_SrmClearErr
Err SrmClearErr(UInt16 portId)
{     
	Err  (*SrmClearErrP)(UInt16 portId);
	
	GetParameter (&SrmClearErrP , sizeof(void *), pSrmClearErr );
	return (*SrmClearErrP)(portId);
}
					
#endif

#ifdef L_SrmClose
Err SrmClose(UInt16 portID)
{     
	Err (*SrmCloseP)(UInt16 portID);
	
	GetParameter (&SrmCloseP , sizeof(void *), pSrmClose );
	return (*SrmCloseP)(portID);
}
					
#endif

#ifdef L_SrmControl
Err SrmControl(UInt16 portId, UInt16 op,void *valueP, UInt16 *valueLenP)
{     
	Err (*SrmControlP)(UInt16 portId, UInt16 op,void *valueP, UInt16 *valueLenP);
	
	GetParameter (&SrmControlP , sizeof(void *), pSrmControl );
	return (*SrmControlP)(portId,  op,valueP, valueLenP);
}
					
#endif

#ifdef L_SrmGetDeviceCount
Err SrmGetDeviceCount(UInt16* numOfDevicesP)
{
	Err (*SrmGetDeviceCountP)(UInt16* numOfDevicesP);
	
	GetParameter (&SrmGetDeviceCountP , sizeof(void *), pSrmGetDeviceCount );
	return (*SrmGetDeviceCountP)(numOfDevicesP);
}
					
#endif
/*
#ifdef L_SrmGetDeviceInfo
Err SrmGetDeviceInfo(UInt32 deviceID,DeviceInfoType* deviceInfoP)
{
	Err (*SrmGetDeviceInfoP)(UInt32 deviceID,DeviceInfoType* deviceInfoP);

	GetParameter (&SrmGetDeviceInfoP , sizeof(void *), pSrmGetDeviceInfo );
	return (*SrmGetDeviceInfoP)(deviceID, deviceInfoP);
}

#endif
*/
#ifdef L_SrmGetStatus
Err SrmGetStatus(UInt16 portId,UInt32* statusFieldP, UInt16* lineErrsP)
{
	Err (*SrmGetStatusP)(UInt16 portId,UInt32* statusFieldP, UInt16* lineErrsP);

	GetParameter (&SrmGetStatusP , sizeof(void *), pSrmGetStatus );
	return (*SrmGetStatusP)(portId, statusFieldP,  lineErrsP);
}
					
#endif

#ifdef L_SrmOpen
Err SrmOpen(UInt32 port, UInt32 baud,UInt16* newPortIdP)
{     
	Err (*SrmOpenP)(UInt32 port, UInt32 baud,UInt16* newPortIdP);
	
	GetParameter (&SrmOpenP , sizeof(void *), pSrmOpen );
	return (*SrmOpenP)( port,  baud, newPortIdP);
}
					
#endif

#ifdef L_SrmOpenBackground
Err SrmOpenBackground(UInt32 port, UInt32 baud,UInt16* newPortIdP)
{     
	Err (*SrmOpenBackgroundP)(UInt32 port, UInt32 baud,UInt16* newPortIdP);
	
	GetParameter (&SrmOpenBackgroundP , sizeof(void *), pSrmOpenBackground );
	return (*SrmOpenBackgroundP)(port,  baud, newPortIdP);
}
					
#endif

#ifdef L_SrmPrimeWakeupHandler
Err SrmPrimeWakeupHandler(UInt16 portId,UInt16 minBytes)
{     
	Err (*SrmPrimeWakeupHandlerP)(UInt16 portId,UInt16 minBytes);
	
	GetParameter (&SrmPrimeWakeupHandlerP , sizeof(void *), pSrmPrimeWakeupHandler );
	return (*SrmPrimeWakeupHandlerP)(portId, minBytes);
}
					
#endif

#ifdef L_SrmReceive
UInt32 SrmReceive(UInt16 portId, void *rcvBufP,UInt32 count, Int32 timeout, Err* errP)
{     
	UInt32 (*SrmReceiveP)(UInt16 portId, void *rcvBufP,UInt32 count, Int32 timeout, Err* errP);
	
	GetParameter (&SrmReceiveP , sizeof(void *), pSrmReceive );
	return (*SrmReceiveP)(portId, rcvBufP, count,  timeout,  errP);
}
					
#endif

#ifdef L_SrmReceiveCheck
Err SrmReceiveCheck(UInt16 portId,UInt32* numBytesP)
{     
	Err (*SrmReceiveCheckP)(UInt16 portId,UInt32* numBytesP);
	
	GetParameter (&SrmReceiveCheckP , sizeof(void *), pSrmReceiveCheck );
	return (*SrmReceiveCheckP)(portId, numBytesP);
}
					
#endif

#ifdef L_SrmReceiveFlush
Err SrmReceiveFlush(UInt16 portId, Int32 timeout)
{     
	Err (*SrmReceiveFlushP)(UInt16 portId, Int32 timeout);
	
	GetParameter (&SrmReceiveFlushP , sizeof(void *), pSrmReceiveFlush );
	return (*SrmReceiveFlushP)(portId, timeout);
}
					
#endif

#ifdef L_SrmReceiveWait
Err SrmReceiveWait(UInt16 portId, UInt32 bytes,Int32 timeout)
{     
	Err (*SrmReceiveWaitP)(UInt16 portId, UInt32 bytes,Int32 timeout);
	
	GetParameter (&SrmReceiveWaitP , sizeof(void *), pSrmReceiveWait );
	return (*SrmReceiveWaitP)(portId,  bytes, timeout);
}
					
#endif

#ifdef L_SrmReceiveWindowClose
Err SrmReceiveWindowClose(UInt16 portId,UInt32 bytesPulled)
{     
	Err (*SrmReceiveWindowCloseP)(UInt16 portId,UInt32 bytesPulled);
	
	GetParameter (&SrmReceiveWindowCloseP , sizeof(void *), pSrmReceiveWindowClose );
	return (*SrmReceiveWindowCloseP)( portId, bytesPulled);
}
					
#endif

#ifdef L_SrmReceiveWindowOpen
Err SrmReceiveWindowOpen(UInt16 portId,UInt8 **bufPP, UInt32* sizeP)
{     
	Err (*SrmReceiveWindowOpenP)(UInt16 portId,UInt8 **bufPP, UInt32* sizeP);
	
	GetParameter (&SrmReceiveWindowOpenP , sizeof(void *), pSrmReceiveWindowOpen );
	return (*SrmReceiveWindowOpenP)(portId,bufPP, sizeP);
}
					
#endif

#ifdef L_SrmSend
UInt32 SrmSend(UInt16 portId, void *bufP,UInt32 count, Err* errP)
{     
	UInt32 (*SrmSendP)(UInt16 portId, void *bufP,UInt32 count, Err* errP);
	
	GetParameter (&SrmSendP , sizeof(void *), pSrmSend );
	return (*SrmSendP)(portId, bufP, count,  errP);
}
					
#endif

#ifdef L_SrmSendCheck
Err SrmSendCheck(UInt16 portId, UInt32* numBytesP)
{     
	Err (*SrmSendCheckP)(UInt16 portId, UInt32* numBytesP);
	
	GetParameter (&SrmSendCheckP , sizeof(void *), pSrmSendCheck );
	return (*SrmSendCheckP)( portId, numBytesP);
}
					
#endif

#ifdef L_SrmSendFlush
Err SrmSendFlush(UInt16 portId)
{     
	Err (*SrmSendFlushP)(UInt16 portId);
	
	GetParameter (&SrmSendFlushP , sizeof(void *), pSrmSendFlush );
	return (*SrmSendFlushP)(portId);
}
					
#endif

#ifdef L_SrmSendWait
Err SrmSendWait(UInt16 portId)
{     
	Err (*SrmSendWaitP)(UInt16 portId);
	
	GetParameter (&SrmSendWaitP , sizeof(void *), pSrmSendWait );
	return (*SrmSendWaitP)(portId);
}
					
#endif

#ifdef L_SrmSetReceiveBufferP
Err SrmSetReceiveBuffer(UInt16 portId, void *bufP,UInt16 bufSize)
{     
	Err (*SrmSetReceiveBufferP)(UInt16 portId, void *bufP,UInt16 bufSize);
	
	GetParameter (&SrmSetReceiveBufferP , sizeof(void *), pSrmSetReceiveBuffer );
	return (*SrmSetReceiveBufferP)(portId, bufP, bufSize);
}
					
#endif
/*
#ifdef L_SrmSetWakeupHandler
Err SrmSetWakeupHandler(UInt16 portId,WakeupHandlerProcPtr procP, UInt32 refCon)
{
	Err (*SrmSetWakeupHandlerP)(UInt16 portId,WakeupHandlerProcPtr procP, UInt32 refCon);

	GetParameter (&SrmSetWakeupHandlerP , sizeof(void *), pSrmSetWakeupHandler );
	return (*SrmSetWakeupHandlerP)(portId,procP,  refCon);
}

#endif
*/




////////////////////////////////////////////////////////////
// Notification Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_SysNotifyBroadcast
Err SysNotifyBroadcast(SysNotifyParamType *notify)
{
	Err (*SysNotifyBroadcastP)(SysNotifyParamType *notify);

	GetParameter (&SysNotifyBroadcastP , sizeof(void *), pSysNotifyBroadcast );
	return (*SysNotifyBroadcastP)(notify);
}

#endif

#ifdef L_SysNotifyBroadcastDeferred
Err SysNotifyBroadcastDeferred(SysNotifyParamType *notify, Int16 paramSize)
{
	Err (*SysNotifyBroadcastDeferredP)(SysNotifyParamType *notify, Int16 paramSize);

	GetParameter (&SysNotifyBroadcastDeferredP , sizeof(void *), pSysNotifyBroadcastDeferred );
	return (*SysNotifyBroadcastDeferredP)(notify, paramSize);
}

#endif
*
#ifdef L_SysNotifyRegister
Err SysNotifyRegister (UInt16 cardNo,LocalID dbID, UInt32 notifyType,SysNotifyProcPtr callbackP, Int8 priority,
					void *userDataP)
{
	Err (*SysNotifyRegisterP) (UInt16 cardNo,LocalID dbID, UInt32 notifyType,SysNotifyProcPtr callbackP, Int8 priority,
						void *userDataP);

	GetParameter (&SysNotifyRegisterP , sizeof(void *), pSysNotifyRegister );
	return (*SysNotifyRegisterP) (cardNo, dbID,  notifyType, callbackP,  priority,
						userDataP);
}

#endif
*/
#ifdef L_SysNotifyUnregister
Err SysNotifyUnregister(UInt16 cardNo,LocalID dbID, UInt32 notifyType, Int8 priority)
{
	Err (*SysNotifyUnregisterP)(UInt16 cardNo,LocalID dbID, UInt32 notifyType, Int8 priority);

	GetParameter (&SysNotifyUnregisterP , sizeof(void *), pSysNotifyUnregister );
	return (*SysNotifyUnregisterP)(cardNo, dbID,  notifyType,  priority);
}

#endif


////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_OmGetCurrentLocale
void OmGetCurrentLocale(OmLocaleType *currentLocale)
{
	void (*OmGetCurrentLocaleP)(OmLocaleType *currentLocale);

	GetParameter (&OmGetCurrentLocaleP , sizeof(void *), pOmGetCurrentLocale );
	(*OmGetCurrentLocaleP)(currentLocale);
}

#endif

#ifdef L_OmGetIndexedLocale
Err OmGetIndexedLocale (UInt16 localeIndex,OmLocaleType *theLocale)
{     
	Err (*OmGetIndexedLocaleP) (UInt16 localeIndex,OmLocaleType *theLocale);
	
	GetParameter (&OmGetIndexedLocaleP , sizeof(void *), pOmGetIndexedLocale );
	return (*OmGetIndexedLocaleP) (localeIndex,theLocale);
}
					
#endif

#ifdef L_OmGetRoutineAddress
void *OmGetRoutineAddress (OmSelector inSelector)
{     
	void *(*OmGetRoutineAddressP) (OmSelector inSelector);
	
	GetParameter (&OmGetRoutineAddressP , sizeof(void *), pOmGetRoutineAddress );
	return (*OmGetRoutineAddressP) (inSelector);
}
					
#endif

#ifdef L_OmGetSystemLocale
void OmGetSystemLocale(OmLocaleType *systemLocale)
{     
	void (*OmGetSystemLocaleP)(OmLocaleType *systemLocale);
	
	GetParameter (&OmGetSystemLocaleP , sizeof(void *), pOmGetSystemLocale );
	(*OmGetSystemLocaleP)(systemLocale); 
}
					
#endif

#ifdef L_OmLocaleToOverlayDBName
Err OmLocaleToOverlayDBName(const Char *baseDBName,const OmLocaleType *targetLocale,Char *overlayDBName)
{     
	Err (*OmLocaleToOverlayDBNameP)(const Char *baseDBName,const OmLocaleType *targetLocale,Char *overlayDBName);
	
	GetParameter (&OmLocaleToOverlayDBNameP , sizeof(void *), pOmLocaleToOverlayDBName );
	return (*OmLocaleToOverlayDBNameP)( baseDBName, targetLocale,overlayDBName);
}
					
#endif

#ifdef L_OmOverlayDBNameToLocale
Err OmOverlayDBNameToLocale(const Char *overlayDBName,OmLocaleType *overlayLocale)
{     
	Err (*OmOverlayDBNameToLocaleP)(const Char *overlayDBName,OmLocaleType *overlayLocale);
	
	GetParameter (&OmOverlayDBNameToLocaleP , sizeof(void *), pOmOverlayDBNameToLocale );
	return (*OmOverlayDBNameToLocaleP)( overlayDBName,overlayLocale);
}
					
#endif

#ifdef L_OmSetSystemLocale
Err OmSetSystemLocale(const OmLocaleType *systemLocale)
{     
	Err (*OmSetSystemLocaleP)(const OmLocaleType *systemLocale);
	
	GetParameter (&OmSetSystemLocaleP , sizeof(void *), pOmSetSystemLocale );
	return (*OmSetSystemLocaleP)( systemLocale);
}
					
#endif
*/
////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////

#ifdef L_PwdExists
Boolean PwdExists ()
{     
	Boolean (*PwdExistsP) ();

	GetParameter (&PwdExistsP , sizeof(void *), pPwdExists );
	return (*PwdExistsP) ();
}
#endif

#ifdef L_PwdRemove
void PwdRemove (void)
{     
	void (*PwdRemoveP) (void);

	GetParameter (&PwdRemoveP , sizeof(void *), pPwdRemove );
	(*PwdRemoveP) ();
}
#endif

#ifdef L_PwdSet
void PwdSet (Char *oldPassword, Char *newPassword)
{     
	void (*PwdSetP) (Char *oldPassword, Char *newPassword);

	GetParameter (&PwdSetP , sizeof(void *), pPwdSet );
	(*PwdSetP) (oldPassword, newPassword);
}
#endif

#ifdef L_PwdVerify
Boolean PwdVerify (Char *string)

{     
	Boolean (*PwdVerifyP) (Char *string);

	GetParameter (&PwdVerifyP , sizeof(void *), pPwdVerify );
	return(*PwdVerifyP) (string);
}
#endif
////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////

#ifdef L_PenCalibrate
Err PenCalibrate (PointType *digTopLeftP, PointType *digBotRightP,
                                                PointType *scrTopLeftP, PointType *scrBotRightP)
{     
	Err (*PenCalibrateP) (PointType *digTopLeftP, PointType *digBotRightP,
	                                                PointType *scrTopLeftP, PointType *scrBotRightP);
	
	GetParameter (&PenCalibrateP , sizeof(void *), pPenCalibrate );
	return (*PenCalibrateP) (digTopLeftP, digBotRightP,
	                                                scrTopLeftP, scrBotRightP);
}
#endif

#ifdef L_PenResetCalibrate
Err PenResetCalibrate (void)

{     
	Err (*PenResetCalibrateP) (void);

	GetParameter (&PenResetCalibrateP , sizeof(void *), pPenResetCalibrate );
	return (*PenResetCalibrateP) ();
}
#endif

////////////////////////////////////////////////////////////
// Preferences Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
#ifdef L_PrefGetAppPreferences
Int16 PrefGetAppPreferences (UInt32 creator, UInt16 id, void *prefs,
                                                                          UInt16 *prefsSize, Boolean saved)
{     
	Int16 (*PrefGetAppPreferencesP) (UInt32 creator, UInt16 id, void *prefs,
                                                                          UInt16 *prefsSize, Boolean saved);

	GetParameter (&PrefGetAppPreferencesP , sizeof(void *), pPrefGetAppPreferences );
	return (*PrefGetAppPreferencesP) ( creator,  id, prefs,
                                                                          prefsSize,  saved);
}
#endif

#ifdef L_PrefGetAppPreferencesV10
Boolean PrefGetAppPreferencesV10 (UInt32 type, Int16 version, 
                                                        void *prefs, UInt16 prefsSize)
{     
	Boolean (*PrefGetAppPreferencesV10P) (UInt32 type, Int16 version, 
                                                        void *prefs, UInt16 prefsSize);

	GetParameter (&PrefGetAppPreferencesV10P , sizeof(void *), pPrefGetAppPreferencesV10 );
	return(*PrefGetAppPreferencesV10P) ( type,  version, 
                                                        prefs,  prefsSize);
}                                          
#endif

#ifdef L_PrefGetPreference            
UInt32 PrefGetPreference (SystemPreferencesChoice choice)
{     
	UInt32 (*PrefGetPreferenceP) (SystemPreferencesChoice choice);

	GetParameter (&PrefGetPreferenceP , sizeof(void *), pPrefGetPreference );
	return(*PrefGetPreferenceP) (choice);
}
#endif

#ifdef L_PrefGetPreferences
void PrefGetPreferences (SystemPreferencesPtr p)
{     
	void (*PrefGetPreferencesP) (SystemPreferencesPtr p);

	GetParameter (&PrefGetPreferencesP , sizeof(void *), pPrefGetPreferences );
	(*PrefGetPreferencesP) (p);
}
#endif

#ifdef L_PrefSetAppPreferences
void PrefSetAppPreferences (UInt32 creator, UInt16 id, UInt16 version,
                                                                         void *prefs, UInt16 prefsSize, Boolean saved)
{     
	void (*PrefSetAppPreferencesP) (UInt32 creator, UInt16 id, UInt16 version,
                                                                         void *prefs, UInt16 prefsSize, Boolean saved);

	GetParameter (&PrefSetAppPreferencesP , sizeof(void *), pPrefSetAppPreferences );
	(*PrefSetAppPreferencesP) ( creator,  id,  version,prefs,  prefsSize,  saved);
}       
#endif

#ifdef L_PrefSetAppPreferencesV10
void PrefSetAppPreferencesV10 (UInt32 creator, Int16 version,  void *prefs, UInt16 prefsSize)

{     
	void (*PrefSetAppPreferencesV10P) (UInt32 creator, Int16 version,  void *prefs, UInt16 prefsSize);

	GetParameter (&PrefSetAppPreferencesV10P , sizeof(void *), pPrefSetAppPreferencesV10 );
	(*PrefSetAppPreferencesV10P) ( creator,  version,  prefs,  prefsSize);
}       
#endif

#ifdef L_PrefSetPreference
void PrefSetPreference (SystemPreferencesChoice choice, UInt32 value)
{     
	void (*PrefSetPreferenceP) (SystemPreferencesChoice choice, UInt32 value);

	GetParameter (&PrefSetPreferenceP , sizeof(void *), pPrefSetPreference );
	(*PrefSetPreferenceP) (choice,  value);
}
#endif

#ifdef L_PrefSetPreferences
void PrefSetPreferences (SystemPreferencesPtr p)
{     
	void (*PrefSetPreferencesP) (SystemPreferencesPtr p);

	GetParameter (&PrefSetPreferencesP , sizeof(void *), pPrefSetPreferences );
	(*PrefSetPreferencesP) (p);
}
#endif

#ifdef L_PrefOpenPreferenceDBV10
DmOpenRef PrefOpenPreferenceDBV10 (void)
{     
	DmOpenRef (*PrefOpenPreferenceDBV10P) (void);

	GetParameter (&PrefOpenPreferenceDBV10P , sizeof(void *), pPrefOpenPreferenceDBV10 );
	return (*PrefOpenPreferenceDBV10P) ();
}
#endif


///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 2/2 functions now.
///////////////////////////////////////////////////////////////////
/*
#ifdef L_SecSelectViewStatus
privateRecordViewEnum SecSelectViewStatus (void)
{
	privateRecordViewEnum (*SecSelectViewStatusP) (void);

	GetParameter (&SecSelectViewStatusP , sizeof(void *), pSecSelectViewStatus );
	return (*SecSelectViewStatusP) ();
}
#endif

#ifdef L_SecVerifyPW
Boolean SecVerifyPW(privateRecordViewEnum newSecLevel)
{
	Boolean (*SecVerifyPWP)(privateRecordViewEnum newSecLevel);

	GetParameter (&SecVerifyPWP , sizeof(void *), pSecVerifyPW );
	return  (*SecVerifyPWP)(newSecLevel);
}
#endif

*/
////////////////////////////////////////////////////////////
// Progress Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_PrgHandleEvent
Boolean PrgHandleEvent (ProgressPtr prgP,EventType *eventP)
{
	Boolean (*PrgHandleEventP) (ProgressPtr prgP,EventType *eventP);

	GetParameter (&PrgHandleEventP , sizeof(void *), pPrgHandleEvent );
	return  (*PrgHandleEventP) (prgP,eventP);
}
#endif

#ifdef L_PrgStartDialog
ProgressPtr PrgStartDialog (Char *title,PrgCallbackFunc textCallback, void *userDataP)
{
	ProgressPtr (*PrgStartDialogP) (Char *title,PrgCallbackFunc textCallback, void *userDataP);

	GetParameter (&PrgStartDialogP , sizeof(void *), pPrgStartDialog );
	return  (*PrgStartDialogP) (title, textCallback, userDataP);
}
#endif

#ifdef L_PrgStartDialogV31
ProgressPtr PrgStartDialogV31 (Char *title,PrgCallbackFunc textCallback)
{
	ProgressPtr (*PrgStartDialogV31P) (Char *title,PrgCallbackFunc textCallback);

	GetParameter (&PrgStartDialogV31P , sizeof(void *), pPrgStartDialogV31 );
	return  (*PrgStartDialogV31P) (title, textCallback);
}
#endif

#ifdef L_PrgStopDialog
void PrgStopDialog (ProgressPtr prgP,Boolean force)
{
	void (*PrgStopDialogP) (ProgressPtr prgP,Boolean force);

	GetParameter (&PrgStopDialogP , sizeof(void *), pPrgStopDialog );
	(*PrgStopDialogP) ( prgP, force);
}
#endif

#ifdef L_PrgUpdateDialog
void PrgUpdateDialog (ProgressPtr prgP,UInt16 err, UInt16 stage, Char *messageP,Boolean updateNow)
{
	void (*PrgUpdateDialogP) (ProgressPtr prgP,UInt16 err, UInt16 stage, Char *messageP,Boolean updateNow);

	GetParameter (&PrgUpdateDialogP , sizeof(void *), pPrgUpdateDialog );
	(*PrgUpdateDialogP)( prgP, err,  stage, messageP, updateNow);
}
#endif



#ifdef L_PrgUserCancel
Boolean  PrgUserCancel (ProgressPtr prgP)
{
	Boolean  (*PrgUserCancelP) (ProgressPtr prgP);

	GetParameter (&PrgUserCancelP , sizeof(void *), pPrgUserCancel );
	return	(*PrgUserCancelP) (prgP);
}
#endif

*/
////////////////////////////////////////////////////////////
// Rectangle Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
#ifdef L_RctCopyRectangle
void RctCopyRectangle(const RectangleType* srcRectP,RectangleType* dstRectP)
{     
	void (*RctCopyRectangleP)(const RectangleType* srcRectP,RectangleType* dstRectP);

	GetParameter (&RctCopyRectangleP , sizeof(void *), pRctCopyRectangle );
	(*RctCopyRectangleP)(  srcRectP, dstRectP);
}
#endif

#ifdef L_RctGetIntersection
void RctGetIntersection (const RectangleType* r1P,const RectangleType* r2P, RectangleType* r3P)
{     
	void (*RctGetIntersectionP) (const RectangleType* r1P,const RectangleType* r2P, RectangleType* r3P);
	
	GetParameter (&RctGetIntersectionP , sizeof(void *), pRctGetIntersection );
	(*RctGetIntersectionP) (  r1P, r2P, r3P);
}
#endif

#ifdef L_RctInsetRectangle
void RctInsetRectangle (RectangleType* rP,Coord insetAmt)
{     
	void (*RctInsetRectangleP) (RectangleType* rP,Coord insetAmt);

	GetParameter (&RctInsetRectangleP , sizeof(void *), pRctInsetRectangle );
	(*RctInsetRectangleP) ( rP, insetAmt);
}
#endif

#ifdef L_RctOffsetRectangle
void RctOffsetRectangle (RectangleType* rP,Coord deltaX, Coord deltaY)
{     
	void (*RctOffsetRectangleP) (RectangleType* rP,Coord deltaX, Coord deltaY);
	
	GetParameter (&RctOffsetRectangleP , sizeof(void *), pRctOffsetRectangle );
	 (*RctOffsetRectangleP) ( rP, deltaX,  deltaY);
}
#endif


#ifdef L_RctPtInRectangle
Boolean RctPtInRectangle (Coord x, Coord y, const RectangleType *rP)
{     
	Boolean (*RctPtInRectangleP) (Coord x, Coord y, const RectangleType *rP);

	GetParameter (&RctPtInRectangleP , sizeof(void *), pRctPtInRectangle );
	return (*RctPtInRectangleP) ( x,  y,  rP);
}
#endif

#ifdef L_RctSetRectangle
void RctSetRectangle (RectangleType *rP, Coord left, Coord top, Coord width, Coord height)
{     
	void (*RctSetRectangleP) (RectangleType *rP, Coord left, Coord top, Coord width, Coord height);

	GetParameter (&RctSetRectangleP , sizeof(void *), pRctSetRectangle );
	(*RctSetRectangleP) (rP,  left,  top,  width,  height);
}

#endif

////////////////////////////////////////////////////////////
// Script Plugin Library, completed 1/1 functions now.
////////////////////////////////////////////////////////////
#ifdef L_ScriptPluginSelectorProcPtr
Err (*ScriptPluginSelectorProcPtr) (void *handle,UInt16 command, void *dataBufferP, UInt16 *sizeP,UInt16 *dataTimeoutP, void *procAddrP);
{     
	Err (*ScriptPluginSelectorProcPtrP) (void *handle,UInt16 command, void *dataBufferP, UInt16 *sizeP,UInt16 *dataTimeoutP, void *procAddrP);

	GetParameter (&ScriptPluginSelectorProcPtrP , sizeof(void *), pScriptPluginSelectorProcPtr );
	return (*ScriptPluginSelectorProcPtrP) (handle, command, dataBufferP, sizeP,dataTimeoutP, procAddrP);
}
#endif


////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
#ifdef L_SclDrawScrollBar
void SclDrawScrollBar (const ScrollBarPtr bar)
{     
	void (*SclDrawScrollBarP) (const ScrollBarPtr bar);

	GetParameter (&SclDrawScrollBarP , sizeof(void *), pSclDrawScrollBar );
	(*SclDrawScrollBarP) (bar);
}
#endif

#ifdef L_SclGetScrollBar
void SclGetScrollBar (const ScrollBarPtr bar, Int16 *valueP,
							   Int16 *minP, Int16 *maxP, Int16 *pageSizeP)
{     
	void (*SclGetScrollBarP) (const ScrollBarPtr bar, Int16 *valueP,
								   Int16 *minP, Int16 *maxP, Int16 *pageSizeP);

	GetParameter (&SclGetScrollBarP , sizeof(void *), pSclGetScrollBar );
	(*SclGetScrollBarP) (  bar, valueP,   minP, maxP, pageSizeP);
}
#endif

#ifdef L_SclSetScrollBar
void SclSetScrollBar (const ScrollBarPtr bar, Int16 value,
		const Int16 minP, const Int16 maxP,
		const Int16 pageSizeP)
{
	void (*SclSetScrollBarP) (const ScrollBarPtr bar, Int16 value,
                        const Int16 minP, const Int16 maxP,
                        const Int16 pageSizeP);

	GetParameter (&SclSetScrollBarP , sizeof(void *), pSclSetScrollBar );
	(*SclSetScrollBarP) ( bar,  value,  minP,   maxP,pageSizeP);
}
#endif

#ifdef L_SclHandleEvent
Boolean SclHandleEvent (const ScrollBarPtr bar,const EventType *event)
{     
	Boolean (*SclHandleEventP) (const ScrollBarPtr bar,const EventType *event);

	GetParameter (&SclHandleEventP , sizeof(void *), pSclHandleEvent );
	return	(*SclHandleEventP) ( bar, event);
}
#endif


////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 8/8 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_DrvEntryPoint
Err DrvEntryPoint(DrvrEntryOpCodeEnum opCode,void * uartData)
{
	Err (*DrvEntryPointP)(DrvrEntryOpCodeEnum opCode,void * uartData);

	GetParameter (&DrvEntryPointP , sizeof(void *), pDrvEntryPoint );
	return	(*DrvEntryPointP)(opCode, uartData);
}
#endif

#ifdef L_SdrvClose
Err SdrvClose(SdrvDataPtr drvrDataP)
{
	Err (*SdrvCloseP)(SdrvDataPtr drvrDataP);

	GetParameter (&SdrvCloseP , sizeof(void *), pSdrvClose );
	return	(*SdrvCloseP)(drvrDataP);
}
#endif

#ifdef L_SdrvControl
Err *SdrvControl(SdrvDataPtr drvrDataP,SdrvCtlOpCodeEnum controlCode,void * controlDataP, UInt16 * controlDataLenP)
{
	Err *(*SdrvControlP)(SdrvDataPtr drvrDataP,SdrvCtlOpCodeEnum controlCode,void * controlDataP, UInt16 * controlDataLenP);

	GetParameter (&SdrvControlP , sizeof(void *), pSdrvControl );
	return	*(*SdrvControlP)(SdrvDataPtr drvrDataP,SdrvCtlOpCodeEnum controlCode,void * controlDataP, UInt16 * controlDataLenP);
}
#endif


//asm Boolean SdrvISP(UInt32 param: __A0):__D0
#ifdef L_SdrvOpen
Err SdrvOpen(SdrvDataPtr* drvrDataP,UInt32 baudRate, void * portP,SerialMgrISPProcPtr saveDataProc)
{
	Err (*SdrvOpenP)(SdrvDataPtr* drvrDataP,UInt32 baudRate, void * portP,SerialMgrISPProcPtr saveDataProc);

	GetParameter (&SdrvOpenP , sizeof(void *), pSdrvOpen );
	return (*SdrvOpenP)( drvrDataP, baudRate,  portP, saveDataProc);
}
#endif

//asm UInt16 SdrvReadChar(SdrvDataPtrdrvrDataP:__A0):__D0

#ifdef L_SdrvStatus
UInt16 SdrvStatus(SdrvDataPtr drvrDataP)
{
	UInt16 (*SdrvStatusP)(SdrvDataPtr drvrDataP);

	GetParameter (&SdrvStatusP , sizeof(void *), pSdrvStatus );
	return	(*SdrvStatusP)(drvrDataP);
}
#endif

#ifdef L_SdrvWriteChar
Err SdrvWriteChar(SdrvDataPtr drvrDataP,UInt8 aChar)
{
	Err (*SdrvWriteCharP)(SdrvDataPtr drvrDataP,UInt8 aChar);

	GetParameter (&SdrvWriteCharP , sizeof(void *), pSdrvWriteChar );
	return	(*SdrvWriteCharP)( drvrDataP, aChar);
}
#endif
*/
////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 10/10 functions now.
////////////////////////////////////////////////////////////
#ifdef L_SlkClose
Err SlkClose (void)
{
	Err (*SlkCloseP) (void);

	GetParameter (&SlkCloseP , sizeof(void *), pSlkClose );
	return	(*SlkCloseP) ();
}
#endif

#ifdef L_SlkCloseSocket
Err SlkCloseSocket (UInt16 socket)
{     
	Err (*SlkCloseSocketP) (UInt16 socket);

	GetParameter (&SlkCloseSocketP , sizeof(void *), pSlkCloseSocket );
	return	(*SlkCloseSocketP) (socket);
}
#endif

#ifdef L_SlkFlushSocket
Err SlkFlushSocket (UInt16 socket, Int32 timeout)
{     	
	Err (*SlkFlushSocketP) (UInt16 socket, Int32 timeout);

	GetParameter (&SlkFlushSocketP , sizeof(void *), pSlkFlushSocket );
	return	(*SlkFlushSocketP) (socket, timeout);
}
#endif

#ifdef L_SlkOpen
Err SlkOpen (void)
{     
	Err (*SlkOpenP) (void);

	GetParameter (&SlkOpenP , sizeof(void *), pSlkOpen );
	return	(*SlkOpenP) ();
}
#endif

#ifdef L_SlkOpenSocket
Err SlkOpenSocket (UInt16 portID, UInt16 *socketP,Boolean staticSocket)
{
	Err (*SlkOpenSocketP) (UInt16 portID, UInt16 *socketP,Boolean staticSocket);

	GetParameter (&SlkOpenSocketP , sizeof(void *), pSlkOpenSocket );
	return	(*SlkOpenSocketP) (portID, socketP, staticSocket);
}
#endif
/*
#ifdef L_SlkReceivePacket
Err SlkReceivePacket (UInt16 socket,Boolean andOtherSockets, SlkPktHeaderPtr headerP,void* bodyP, UInt16 bodySize, Int32 timeout)
{
	Err (*SlkReceivePacketP) (UInt16 socket,Boolean andOtherSockets, SlkPktHeaderPtr headerP,void* bodyP, UInt16 bodySize, Int32 timeout);

	GetParameter (&SlkReceivePacketP , sizeof(void *), pSlkReceivePacket );
	return	(*SlkReceivePacketP) ( socket, andOtherSockets,  headerP, bodyP,  bodySize,  timeout);
}
#endif

#ifdef L_SlkSendPacket
Err SlkSendPacket (SlkPktHeaderPtr headerP,SlkWriteDataPtr writeList)
{
	Err (*SlkSendPacketP) (SlkPktHeaderPtr headerP,SlkWriteDataPtr writeList);

	GetParameter (&SlkSendPacketP , sizeof(void *), pSlkSendPacket );
	return	(*SlkSendPacketP) ( headerP, writeList);
}
#endif

#ifdef L_SlkSetSocketListener
Err SlkSetSocketListener (UInt16 socket,SlkSocketListenPtr socketP)
{
	Err (*SlkSetSocketListenerP) (UInt16 socket,SlkSocketListenPtr socketP);

	GetParameter (&SlkSetSocketListenerP , sizeof(void *), pSlkSetSocketListener );
	return	(*SlkSetSocketListenerP) ( socket, socketP);
}
#endif
*/
#ifdef L_SlkSocketPortID
Err  SlkSocketPortID (UInt16 socket,UInt16 * portIDP)
{
	Err  (*SlkSocketPortIDP) (UInt16 socket,UInt16 * portIDP);

	GetParameter (&SlkSocketPortIDP , sizeof(void *), pSlkSocketPortID );
	return	(*SlkSocketPortIDP) (socket,portIDP);
}
#endif

#ifdef L_SlkSocketSetTimeout
Err SlkSocketSetTimeout (UInt16 socket,Int32 timeout)
{
	Err (*SlkSocketSetTimeoutP) (UInt16 socket,Int32 timeout);

	GetParameter (&SlkSocketSetTimeoutP , sizeof(void *), pSlkSocketSetTimeout );
	return	(*SlkSocketSetTimeoutP) ( socket,timeout);
}
#endif


////////////////////////////////////////////////////////////
// Serial Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
#ifdef L_SerClose
Err SerClose (UInt16 refNum)
{
	Err (*SerCloseP) (UInt16 refNum);

	GetParameter (&SerCloseP , sizeof(void *), pSerClose );
	return (*SerCloseP) ( refNum);
}
#endif

#ifdef L_SerGetStatus
UInt16 SerGetStatus (UInt16 refNum, Boolean *ctsOnP, Boolean *dsrOnP)
{     
	UInt16 (*SerGetStatusP) (UInt16 refNum, Boolean *ctsOnP, Boolean *dsrOnP);

	GetParameter (&SerGetStatusP , sizeof(void *), pSerGetStatus );
	return (*SerGetStatusP) ( refNum, ctsOnP, dsrOnP);
}
#endif

#ifdef L_SerOpen
Err SerOpen (UInt16 refNum, UInt16 port, UInt32 baud)
{     
	Err (*SerOpenP) (UInt16 refNum, UInt16 port, UInt32 baud);

	GetParameter (&SerOpenP , sizeof(void *), pSerOpen );
	return (*SerOpenP) ( refNum,  port,  baud);
}
#endif

#ifdef L_SerReceive
UInt32 SerReceive (UInt16 refNum, void *bufP, UInt32 count,
								  Int32 timeout, Err *errP)
{    
	UInt32 (*SerReceiveP) (UInt16 refNum, void *bufP, UInt32 count,
								  Int32 timeout, Err *errP);

	GetParameter (&SerReceiveP , sizeof(void *), pSerReceive );
	return (*SerReceiveP) ( refNum, bufP,  count,   timeout, errP);
}	
#endif

#ifdef L_SerReceiveCheck							  
Err SerReceiveCheck (UInt16 refNum, UInt32 *numBytesP)
{     
	Err (*SerReceiveCheckP) (UInt16 refNum, UInt32 *numBytesP);

	GetParameter (&SerReceiveCheckP , sizeof(void *), pSerReceiveCheck );
	return (*SerReceiveCheckP) ( refNum, numBytesP);
}
#endif

#ifdef L_SerReceiveFlush
void SerReceiveFlush (UInt16 refNum, Int32 timeout)
{     
	void (*SerReceiveFlushP) (UInt16 refNum, Int32 timeout);

	GetParameter (&SerReceiveFlushP , sizeof(void *), pSerReceiveFlush );
	(*SerReceiveFlushP) ( refNum,  timeout);
}
#endif

#ifdef L_SerSend
UInt32 SerSend (UInt16 refNum, void *bufP, UInt32 count, Err *errP)
{    
	UInt32 (*SerSendP) (UInt16 refNum, void *bufP, UInt32 count, Err *errP);

	GetParameter (&SerSendP , sizeof(void *), pSerSend );
	return (*SerSendP) ( refNum, bufP,  count, errP);
}
#endif

#ifdef L_SerSendFlush
Err SerSendFlush (UInt16 refNum)
{     
	Err (*SerSendFlushP) (UInt16 refNum);

	GetParameter (&SerSendFlushP , sizeof(void *), pSerSendFlush );
	return (*SerSendFlushP) (refNum);
}
#endif

#ifdef L_SerClearErr
Err SerClearErr (UInt16 refNum)
{
	Err (*SerClearErrP) (UInt16 refNum);

	GetParameter (&SerClearErrP , sizeof(void *), pSerClearErr );
	return (*SerClearErrP) (refNum);
}
#endif

#ifdef L_SerControl
Err SerControl (UInt16 refNum, UInt16 op,void *valueP, UInt16 *valueLenP)
{
	Err (*SerControlP) (UInt16 refNum, UInt16 op,void *valueP, UInt16 *valueLenP);

	GetParameter (&SerControlP , sizeof(void *), pSerControl );
	return   (*SerControlP) (refNum, op,valueP, valueLenP);
}
#endif
/*
#ifdef L_SerGetSettings
Err SerGetSettings (UInt16 refNum,SerSettingsPtr settingsP)
{
	Err (*SerGetSettingsP) (UInt16 refNum,SerSettingsPtr settingsP);

	GetParameter (&SerGetSettingsP , sizeof(void *), pSerGetSettings );
	return (*SerGetSettingsP) ( refNum, settingsP);
}
#endif
*/
#ifdef L_SerReceive10
Err SerReceive10 (UInt16 refNum, void *bufP,UInt32 bytes, Int32 timeout)
{
	Err (*SerReceive10P) (UInt16 refNum, void *bufP,UInt32 bytes, Int32 timeout);

	GetParameter (&SerReceive10P , sizeof(void *), pSerReceive10 );
	return (*SerReceive10P) ( refNum, bufP, bytes,  timeout);
}
#endif

#ifdef L_SerReceiveWait
Err SerReceiveWait (UInt16 refNum, UInt32 bytes,Int32 timeout)
{     
	Err (*SerReceiveWaitP) (UInt16 refNum, UInt32 bytes,Int32 timeout);

	GetParameter (&SerReceiveWaitP , sizeof(void *), pSerReceiveWait );
	return (*SerReceiveWaitP) ( refNum,  bytes, timeout);
}
#endif

#ifdef L_SerSend10
Err SerSend10 (UInt16 refNum, void *bufP,UInt32 size)
{
	Err (*SerSend10P) (UInt16 refNum, void *bufP,UInt32 size);

	GetParameter (&SerSend10P , sizeof(void *), pSerSend10 );
	return (*SerSend10P) ( refNum, bufP, size);
}
#endif

#ifdef L_SerSendWait
Err SerSendWait (UInt16 refNum, Int32 timeout)
{     
	Err (*SerSendWaitP) (UInt16 refNum, Int32 timeout);

	GetParameter (&SerSendWaitP , sizeof(void *), pSerSendWait );
	return (*SerSendWaitP) (refNum, timeout);
}
#endif

#ifdef L_SerSetReceiveBuffer
Err SerSetReceiveBuffer (UInt16 refNum,void *bufP, UInt16 bufSize)
{     
	Err (*SerSetReceiveBufferP) (UInt16 refNum,void *bufP, UInt16 bufSize);

	GetParameter (&SerSetReceiveBufferP , sizeof(void *), pSerSetReceiveBuffer );
	return (*SerSetReceiveBufferP) (refNum,bufP,  bufSize);
}
#endif
/*
#ifdef L_SerSetSettings
Err SerSetSettings (UInt16 refNum,SerSettingsPtr settingsP)
{
	Err (*SerSetSettingsP) (UInt16 refNum,SerSettingsPtr settingsP);

	GetParameter (&SerSetSettingsP , sizeof(void *), pSerSetSettings );
	return
}
#endif
*/

////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 4/4 functions now.
///////////////////#ifdef L_(*GetSizeProcPtr)
/////////////////////////////////////////
#ifdef L_GetSizeProcPtr
UInt32 *GetSizeProcPtr(void * theQ)
{
	UInt32 *(*GetSizeProcPtrP)(void * theQ);

	GetParameter (&GetSizeProcPtrP , sizeof(void *), pGetSizeProcPtr );
	return (*GetSizeProcPtrP)(theQ);
}
#endif

#ifdef L_GetSpaceProcPtr
UInt32 *GetSpaceProcPtr(void * theQ)
{
	UInt32 *(*GetSpaceProcPtrP)(void * theQ);

	GetParameter (&GetSpaceProcPtrP , sizeof(void *), pGetSpaceProcPtr );
	return (*GetSpaceProcPtrP)(theQ);
}
#endif

#ifdef L_WriteBlockProcPtr
Err *WriteBlockProcPtr(void * theQ,UInt8 * bufP, UInt16 size, UInt16 lineErrs)
{
	Err *(*WriteBlockProcPtrP)(void * theQ,UInt8 * bufP, UInt16 size, UInt16 lineErrs);

	GetParameter (&WriteBlockProcPtrP , sizeof(void *), pWriteBlockProcPtr );
	return (*WriteBlockProcPtrP)( theQ, bufP,  size,  lineErrs);
}
#endif

#ifdef L_WriteByteProcPtr
Err (*WriteByteProcPtr)(void * theQ,UInt8 theByte, UInt16 lineErrs)
{
	Err *(*WriteByteProcPtr)(void * theQ,UInt8 theByte, UInt16 lineErrs);

	GetParameter (&WriteByteProcPtrP , sizeof(void *), pWriteByteProcPtr );
	return  (*WriteByteProcPtr)( theQ, theByte,  lineErrs);
}
#endif
