#include <VCommon.h>
#include <VParser.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#include "wisapi.h"


////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 21/21 functions now.
////////////////////////////////////////////////////////////
void PipeSrmClearErr (void)
{
//	WriteParameter (SrmClearErr, sizeof(void*), pSrmClearErr);
}
void PipeSrmClose(void)
{
//	WriteParameter (SrmClose, sizeof(void*), pSrmClose);
}
void PipeSrmControl(void)
{
//	WriteParameter (SrmControl, sizeof(void*), pSrmControl);
}
void PipeSrmGetDeviceCount (void)
{
//	WriteParameter (SrmGetDeviceCount, sizeof(void*), pSrmGetDeviceCount);
}
void PipeSrmGetDeviceInfo (void)
{
//	WriteParameter (SrmGetDeviceInfo, sizeof(void*), pSrmGetDeviceInfo);
}
void PipeSrmGetStatus (void)
{
//	WriteParameter (SrmGetStatus, sizeof(void*), pSrmGetStatus);
}
void PipeSrmOpen(void)
{
//	WriteParameter (SrmOpen, sizeof(void*), pSrmOpen);
}
void PipeSrmOpenBackground (void)
{
//	WriteParameter (SrmOpenBackground, sizeof(void*), pSrmOpenBackground);
}
void PipeSrmPrimeWakeupHandler (void)
{
//	WriteParameter (SrmPrimeWakeupHandler sizeof(void*), pSrmPrimeWakeupHandler);
}
void PipeSrmReceive(void)
{
//	WriteParameter (SrmReceive, sizeof(void*), pSrmReceive);
}
void PipeSrmReceiveCheck(void)
{
//	WriteParameter (SrmReceiveCheck, sizeof(void*), pSrmReceiveCheck);
}
void PipeSrmReceiveFlush(void)
{
//	WriteParameter (SrmReceiveFlushvoid, sizeof(void*), pSrmReceiveFlushvoid);
}
void PipeSrmReceiveWait (void)
{
//	WriteParameter (SrmReceiveWait , sizeof(void*), pSrmReceiveWait );
}
void PipeSrmReceiveWindowClose (void)
{
//	WriteParameter (SrmReceiveWindowClose, sizeof(void*), pSrmReceiveWindowClose);
}
void PipeSrmReceiveWindowOpen (void)
{
//	WriteParameter (SrmReceiveWindowOpen , sizeof(void*), pSrmReceiveWindowOpen );
}
void PipeSrmSend (void)
{
//	WriteParameter (SrmSend, sizeof(void*), pSrmSend);
}
void PipeSrmSendCheck(void)
{
//	WriteParameter (SrmSendCheck, sizeof(void*), pSrmSendCheck);
}
void PipeSrmSendFlush (void)
{
//	WriteParameter (SrmSendFlush , sizeof(void*), pSrmSendFlush );
}
void PipeSrmSendWait(void)
{
//	WriteParameter (SrmSendWait, sizeof(void*), pSrmSendWait);
}
void PipeSrmSetReceiveBuffer (void)
{
//	WriteParameter (SrmSetReceiveBuffer, sizeof(void*), pSrmSetReceiveBuffer);
}
void PipeSrmSetWakeupHandler (void)
{
//	WriteParameter (SrmSetWakeupHandler, sizeof(void*), pSrmSetWakeupHandler);
}

////////////////////////////////////////////////////////////
// Notification Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeSysNotifyBroadcast(void)
{
//	WriteParameter (SysNotifyBroadcast, sizeof(void*), pSysNotifyBroadcast);
}
void PipeSysNotifyBroadcastDeferred (void)
{
//	WriteParameter (SysNotifyBroadcastDeferred, sizeof(void*), pSysNotifyBroadcastDeferred);
}
void PipeSysNotifyRegister(void)
{
//	WriteParameter (SysNotifyRegister, sizeof(void*), pSysNotifyRegister);
}
void PipeSysNotifyUnregister (void)
{
//	WriteParameter (SysNotifyUnregister, sizeof(void*), pSysNotifyUnregister);
}




////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////
void PipeOmGetCurrentLocale (void)
{
//	WriteParameter (OmGetCurrentLocale, sizeof(void*), pOmGetCurrentLocale);
}
void PipeOmGetIndexedLocale (void)
{
//	WriteParameter (OmGetIndexedLocale, sizeof(void*), pOmGetIndexedLocale);
}
void PipeOmGetRoutineAddress (void)
{
//	WriteParameter (OmGetRoutineAddress, sizeof(void*), pOmGetRoutineAddress);
}
void PipeOmGetSystemLocale (void)
{
//	WriteParameter (OmGetSystemLocale , sizeof(void*), pOmGetSystemLocale );
}
void PipeOmLocaleToOverlayDBName (void)
{
//	WriteParameter (OmLocaleToOverlayDBName , sizeof(void*), pOmLocaleToOverlayDBName );
}
void PipeOmOverlayDBNameToLocale(void)
{
//	WriteParameter (OmOverlayDBNameToLocale, sizeof(void*), pOmOverlayDBNameToLocale);
}
void PipeOmSetSystemLocale (void)
{
//	WriteParameter (OmSetSystemLocale, sizeof(void*), pOmSetSystemLocale);
}


////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipePwdExists (void)
{
	WriteParameter (PwdExists, sizeof(void*), pPwdExists);
}

void PipePwdRemove (void)
{
	WriteParameter (PwdRemove, sizeof(void*), pPwdRemove);
}

void PipePwdSet (void)
{
	WriteParameter (PwdSet, sizeof(void*), pPwdSet);
}
void PipePwdVerify (void)
{
	WriteParameter (PwdVerify, sizeof(void*), pPwdVerify);
}


////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
void PipePenCalibrate (void)
{
	WriteParameter (PenCalibrate, sizeof(void*), pPenCalibrate);
}
void PipePenResetCalibrate (void)
{
	WriteParameter (PenResetCalibrate, sizeof(void*), pPenResetCalibrate);
}


////////////////////////////////////////////////////////////
// Preferences Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipePrefGetAppPreferences (void)
{
	WriteParameter (PrefGetAppPreferences, sizeof(void*), pPrefGetAppPreferences);
}
void PipePrefGetAppPreferencesV10 (void)
{
	WriteParameter (PrefGetAppPreferencesV10, sizeof(void*), pPrefGetAppPreferencesV10);
}
void PipePrefGetPreference (void)
{
	WriteParameter (PrefGetPreference, sizeof(void*), pPrefGetPreference);
}
void PipePrefGetPreferences (void)
{
	WriteParameter (PrefGetPreferences, sizeof(void*), pPrefGetPreferences);
}
void PipePrefOpenPreferenceDBV10 (void)
{
//	WriteParameter (PrefOpenPreferenceDBV10, sizeof(void*), pPrefOpenPreferenceDBV10);
}

void PipePrefSetAppPreferences (void)
{
	WriteParameter (PrefSetAppPreferences, sizeof(void*), pPrefSetAppPreferences);
}
void PipePrefSetAppPreferencesV10 (void)
{
	WriteParameter (PrefSetAppPreferencesV10, sizeof(void*), pPrefSetAppPreferencesV10);
}

void PipePrefSetPreference (void)
{
//	WriteParameter (PrefSetPreference, sizeof(void*), pPrefSetPreference);
}

void PipePrefSetPreferences (void)
{
	WriteParameter (PrefSetPreferences, sizeof(void*), pPrefSetPreferences);

}
///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 2/2 functions now.
///////////////////////////////////////////////////////////////////
void PipeSecSelectViewStatus(void)
{
//	WriteParameter (SecSelectViewStatus, sizeof(void*), pSecSelectViewStatus);

}
void PipeSecVerifyPW(void)
{
//	WriteParameter (SecVerifyPW, sizeof(void*), pSecVerifyPW);

}



////////////////////////////////////////////////////////////
// Progress Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipePrgHandleEvent (void)
{
//	WriteParameter (PrgHandleEvent, sizeof(void*), pPrgHandleEvent);

}
void PipePrgStartDialog(void)
{
//	WriteParameter (PrgStartDialog, sizeof(void*), pPrgStartDialog);

}
void PipePrgStartDialogV31 (void)
{
//	WriteParameter (PrgStartDialogV31, sizeof(void*), pPrgStartDialogV31);

}
void PipePrgStopDialog (void)
{
//	WriteParameter (PrgStopDialog, sizeof(void*), pPrgStopDialog);

}
void PipePrgUpdateDialog (void)
{
//	WriteParameter (PrgUpdateDialog, sizeof(void*), pPrgUpdateDialog);

}
void PipePrgUserCancel (void)
{
//	WriteParameter (PrgUserCancel, sizeof(void*), pPrgUserCancel);

}



////////////////////////////////////////////////////////////
// Rectangle Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeRctPtInRectangle (void)
{
	WriteParameter (RctPtInRectangle, sizeof(void*), pRctPtInRectangle);
}
void PipeRctSetRectangle (void)
{
	WriteParameter (RctSetRectangle, sizeof(void*), pRctSetRectangle);
}


#define     PenGetPoint(a,b,c)    EvtGetPen(a,b,c)

void PipeRctCopyRectangle (void)
{
//	WriteParameter (RctRctCopyRectangle, sizeof(void*), pRctCopyRectangle);
}
void PipeRctGetIntersection(void)
{
//	WriteParameter (RctGetIntersection, sizeof(void*), pRctGetIntersection);
}
void PipeRctInsetRectangle (void)
{
//	WriteParameter (RctInsetRectangle , sizeof(void*), pRctInsetRectangle );
}
void PipeRctOffsetRectangle (void)
{
//	WriteParameter (RctOffsetRectangle, sizeof(void*), pRctOffsetRectangle);
}


////////////////////////////////////////////////////////////
// Script Plugin Library, completed 1/1 functions now.
////////////////////////////////////////////////////////////
void PipeScriptPluginSelectorProc(void)
{
//	WriteParameter (ScriptPluginSelectorProc, sizeof(void*), pScriptPluginSelectorProc);
}



////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeSclDrawScrollBar (void)
{
	WriteParameter (SclDrawScrollBar, sizeof(void*), pSclDrawScrollBar);
}

void PipeSclGetScrollBar (void)
{
	WriteParameter (SclGetScrollBar, sizeof(void*), pSclGetScrollBar);
}
void PipeSclHandleEvent (void)
{
//	WriteParameter (SclHandleEvent, sizeof(void*), pSclHandleEvent);
}

void PipeSclSetScrollBar (void)
{
	WriteParameter (SclSetScrollBar, sizeof(void*), pSclSetScrollBar);
}
////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 8/8 functions now.
////////////////////////////////////////////////////////////
void PipeDrvEntryPoint (void)
{
//	WriteParameter (DrvEntryPoint, sizeof(void*), pDrvEntryPoint);
}
void PipeSdrvClose (void)
{
//	WriteParameter (SdrvClose , sizeof(void*), pSdrvClose );
}
void PipeSdrvControl(void)
{
//	WriteParameter (SdrvControl, sizeof(void*), pSdrvControl);
}
void PipeSdrvISP (void)
{
//	WriteParameter (SdrvISP, sizeof(void*), pSdrvISP);
}
void PipeSdrvOpen(void)
{
//	WriteParameter (SdrvOpen, sizeof(void*), pSdrvOpen);
}
void PipeSdrvReadChar (void)
{
//	WriteParameter (SdrvReadChar, sizeof(void*), pSdrvReadChar);
}
void PipeSdrvStatus(void)
{
//	WriteParameter (SdrvStatus, sizeof(void*), pSdrvStatus);
}
void PipeSdrvWriteChar(void)
{
//	WriteParameter (SdrvWriteChar, sizeof(void*), pSdrvWriteChar);
}



////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 10/10 functions now.
////////////////////////////////////////////////////////////

void PipeSlkClose (void)
{
//	WriteParameter (SlkClose, sizeof(void*), pSlkClose);
}
void PipeSlkCloseSocket (void)
{
//	WriteParameter (SlkCloseSocket, sizeof(void*), pSlkCloseSocket);
}
void PipeSlkFlushSocket(void)
{
//	WriteParameter (SlkFlushSocket, sizeof(void*), pSlkFlushSocket);
}
void PipeSlkOpen(void)
{
//	WriteParameter (SlkOpen, sizeof(void*), pSlkOpen);
}
void PipeSlkOpenSocket (void)
{
//	WriteParameter (SlkOpenSocket, sizeof(void*), pSlkOpenSocket);
}
void PipeSlkReceivePacket(void)
{
//	WriteParameter (SlkReceivePacket, sizeof(void*), pSlkReceivePacket);
}
void PipeSlkSendPacket(void)
{
//	WriteParameter (SlkSendPacket, sizeof(void*), pSlkSendPacket);
}
void PipeSlkSetSocketListener(void)
{
//	WriteParameter (SlkSetSocketListener, sizeof(void*), pSlkSetSocketListener);
}
void PipeSlkSocketPortID(void)
{
//	WriteParameter (SlkSocketPortID, sizeof(void*), pSlkSocketPortID);
}
void PipeSlkSocketSetTimeout(void)
{
//	WriteParameter (SlkSocketSetTimeout, sizeof(void*), pSlkSocketSetTimeout);
}



////////////////////////////////////////////////////////////
// Serial Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////

void PipeSerClose (void)
{
//	WriteParameter (SerClose, sizeof(void*), pSerClose);

}
void PipeSerGetStatus (void)
{
//	WriteParameter (SerGetStatus, sizeof(void*), pSerGetStatus);
}
void PipeSerOpen(void)
{
//	WriteParameter (SerOpen, sizeof(void*), pSerOpen);
}
void PipeSerReceive (void)
{
//	WriteParameter (SerReceive, sizeof(void*), pSerReceive);
}
void PipeSerReceiveCheck(void)
{
//	WriteParameter (SerReceiveCheck, sizeof(void*), pSerReceiveCheck);
}

void PipeSerReceiveFlush (void)
{
//	WriteParameter (SerReceiveFlush, sizeof(void*), pSerReceiveFlush);

}
void PipeSerSend(void)
{
//	WriteParameter (SerSend, sizeof(void*), pSerSend);
}
void PipeSerSendFlush(void)

{
//	WriteParameter (SerSendFlush, sizeof(void*), pSerSendFlush);
}


void PipeSerClearErr (void)
{
//	WriteParameter (SerClearErr, sizeof(void*), pSerClearErr);
}
void PipeSerControl(void)
{
//	WriteParameter (SerControl, sizeof(void*), pSerControl);
}
void PipeSerGetSettings (void)
{
//	WriteParameter (SerGetSettings , sizeof(void*), pSerGetSettings );
}
void PipeSerReceive10(void)
{
//	WriteParameter (SerReceive10, sizeof(void*), pSerReceive10);
}
void PipeSerReceiveWait(void)
{
//	WriteParameter (SerReceiveWait, sizeof(void*), pSerReceiveWait);
}
void PipeSerSend10(void)
{
//	WriteParameter (SerSend10, sizeof(void*), pSerSend10);
}
void PipeSerSendWait(void)
{
//	WriteParameter (SerSendWait, sizeof(void*), pSerSendWait);
}
void PipeSerSetReceiveBuffer(void)
{
//	WriteParameter (SerSetReceiveBuffer, sizeof(void*), pSerSetReceiveBuffer);
}
void PipeSerSetSettings(void)
{
//	WriteParameter (SerSetSettings, sizeof(void*), pSerSetSettings);
}

////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeGetSize(void)
{
//	WriteParameter (GetSize, sizeof(void*), pGetSize);
}
void PipeGetSpace (void)
{
//	WriteParameter (GetSpace, sizeof(void*), pGetSpace);
}
void PipeWriteBlock (void)
{
//	WriteParameter (WriteBlock, sizeof(void*), pWriteBlock);
}
void PipeWriteByte(void)
{
//	WriteParameter (WriteByte, sizeof(void*), pWriteByte);
}
