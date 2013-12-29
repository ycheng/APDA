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
// Sound Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////

#ifdef L_SndCreateMidiList
Boolean SndCreateMidiList (UInt32 creator,Boolean multipleDBs, UInt16* wCountP,MemHandle *entHP)
{
	Boolean (*SndCreateMidiListP) (UInt32 creator,Boolean multipleDBs, UInt16* wCountP,MemHandle *entHP);

	GetParameter (&SndCreateMidiListP , sizeof(void *), pSndCreateMidiList );
	return (*SndCreateMidiListP) ( creator, multipleDBs,  wCountP,entHP);
}
#endif
/*
#ifdef L_SndDoCmd
Err SndDoCmd (void* channelP, SndCommandPtr cmdP,Boolean noWait)
{
	Err (*SndDoCmdP) (void* channelP, SndCommandPtr cmdP,Boolean noWait);

	GetParameter (&SndDoCmdP , sizeof(void *), pSndDoCmd );
	return (*SndDoCmdP) ( channelP,  cmdP, noWait);
}
#endif
*/
#ifdef L_SndGetDefaultVolume
void SndGetDefaultVolume (UInt16* alarmAmpP,UInt16* sysAmpP, UInt16* masterAmpP)
{
	void (*SndGetDefaultVolumeP) (UInt16* alarmAmpP,UInt16* sysAmpP, UInt16* masterAmpP);

	GetParameter (&SndGetDefaultVolumeP , sizeof(void *), pSndGetDefaultVolume );
	return 	(*SndGetDefaultVolumeP) ( alarmAmpP, sysAmpP,  masterAmpP);
}
#endif
/*
#ifdef L_SndPlaySmf
Err SndPlaySmf (void* chanP, SndSmfCmdEnum cmd,UInt8* smfP, SndSmfOptionsType* selP,
			SndSmfChanRangeType* chanRangeP,SndSmfCallbacksType* callbacksP, Boolean bNoWait)
{
	Err (*SndPlaySmfP) (void* chanP, SndSmfCmdEnum cmd,UInt8* smfP, SndSmfOptionsType* selP,
			SndSmfChanRangeType* chanRangeP,SndSmfCallbacksType* callbacksP, Boolean bNoWait);

	GetParameter (&SndPlaySmfP , sizeof(void *), pSndPlaySmf );
	return (*SndPlaySmfP) ( chanP,  cmd, smfP,  selP,chanRangeP, callbacksP,  bNoWait);
}
#endif

#ifdef L_SndPlaySmfResource
Err SndPlaySmfResource (UInt32 resType,Int16 resID,SystemPreferencesChoice volumeSelector)
{
	Err (*SndPlaySmfResourceP) (UInt32 resType,Int16 resID,SystemPreferencesChoice volumeSelector);

	GetParameter (&SndPlaySmfResourceP , sizeof(void *), pSndPlaySmfResource );
	return (*SndPlaySmfResourceP) ( resType, resID, volumeSelector);
}
#endif

#ifdef L_SndPlaySystemSound
void SndPlaySystemSound (SndSysBeepType beepID)
{
	void (*SndPlaySystemSoundP) (SndSysBeepType beepID);

	GetParameter (&SndPlaySystemSoundP , sizeof(void *), pSndPlaySystemSound );
	(*SndPlaySystemSoundP) (beepID);
}
#endif
*/
////////////////////////////////////////////////////////////
// Standard IO Library, completed 5/5 functions now.
////////////////////////////////////////////////////////////
#ifdef L_SioClearScreen
void SioClearScreen(void)
{
	void (*SioClearScreenP)(void);

	GetParameter (&SioClearScreenP , sizeof(void *), pSioClearScreen );
	(*SioClearScreenP)(); 
}
#endif

#ifdef L_SioExecCommand
Int16 SioExecCommand (const Char* cmd)
{
	Int16 (*SioExecCommandP) (const Char* cmd);

	GetParameter (&SioExecCommandP , sizeof(void *), pSioExecCommand );
	return (*SioExecCommandP) (cmd);
}
#endif

#ifdef L_SioFree
Err SioFree(void)
{     
	Err (*SioFreeP)(void);

	GetParameter (&SioFreeP , sizeof(void *), pSioFree );
	return (*SioFreeP)();
}
#endif
/*
#ifdef L_SioHandleEvent
Boolean SioHandleEvent (SysEventType* event)
{
	Boolean (*SioHandleEventP) (SysEventType* event);

	GetParameter (&SioHandleEventP , sizeof(void *), pSioHandleEvent );
	return 	(*SioHandleEventP) ( event);
}
#endif
 */
#ifdef L_SioInit
Err SioInit (UInt16 formID, UInt16 fieldID,UInt16 scrollerID)
{     
	Err (*SioInitP) (UInt16 formID, UInt16 fieldID,UInt16 scrollerID);

	GetParameter (&SioInitP , sizeof(void *), pSioInit );
	return 	( formID,  fieldID, scrollerID);
}
#endif


////////////////////////////////////////////////////////////
// System Dialogs Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////

#ifdef L_SysAppLauncherDialog
void SysAppLauncherDialog()
{
	void (*SysAppLauncherDialogP)();

	GetParameter (&SysAppLauncherDialogP , sizeof(void *), pSysAppLauncherDialog );
	(*SysAppLauncherDialogP)();
}
#endif

#ifdef L_SysFatalAlert
UInt16 SysFatalAlert (const Char *msg)
{
	UInt16 (*SysFatalAlertP) (const Char *msg);

	GetParameter (&SysFatalAlertP , sizeof(void *), pSysFatalAlert );
	return 	(*SysFatalAlertP) (msg);
}
#endif
  /*
#ifdef L_SysGraffitiReferenceDialog
void SysGraffitiReferenceDialog(ReferenceType referenceType)
{
	void (*SysGraffitiReferenceDialogP)(ReferenceType referenceType);

	GetParameter (&SysGraffitiReferenceDialogP , sizeof(void *), pSysGraffitiReferenceDialog );
	(*SysGraffitiReferenceDialogP)(referenceType);
}
#endif

 */
//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 25/25 functions now.
//////////////////////////////////////////////////////////////
#ifdef L_EvtAddEventToQueue
void EvtAddEventToQueue (const EventType *event)
{
	void (*EvtAddEventToQueueP) (const EventType *event);

	GetParameter (&EvtAddEventToQueueP , sizeof(void *), pEvtAddEventToQueue );
	(*EvtAddEventToQueueP) (event);
}
#endif

#ifdef L_EvtAddUniqueEventToQueue
void EvtAddUniqueEventToQueue(const EventType *eventP, UInt32 id,Boolean inPlace)
{     
	void (*EvtAddUniqueEventToQueueP)(const EventType *eventP, UInt32 id,Boolean inPlace);

	GetParameter (&EvtAddUniqueEventToQueueP , sizeof(void *), pEvtAddUniqueEventToQueue );
	 (*EvtAddUniqueEventToQueueP)( eventP,  id, inPlace);
}
#endif

#ifdef L_EvtCopyEvent
void EvtCopyEvent (const EventType *source,EventType *dest)
{     
	void (*EvtCopyEventP) (const EventType *source,EventType *dest);

	GetParameter (&EvtCopyEventP , sizeof(void *), pEvtCopyEvent );
	(*EvtCopyEventP) (source,dest);
}
#endif

#ifdef L_EvtDequeuePenPoint
Err EvtDequeuePenPoint (PointType* retP)
{
	Err (*EvtDequeuePenPointP) (PointType* retP);

	GetParameter (&EvtDequeuePenPointP , sizeof(void *), pEvtDequeuePenPoint );
	return  (*EvtDequeuePenPointP) (retP);
}
#endif

#ifdef L_EvtDequeuePenStrokeInfo
Err EvtDequeuePenStrokeInfo (PointType* startPtP,PointType* endPtP)
{
	Err (*EvtDequeuePenStrokeInfoP) (PointType* startPtP,PointType* endPtP);

	GetParameter (&EvtDequeuePenStrokeInfoP , sizeof(void *), pEvtDequeuePenStrokeInfo );
	return	(*EvtDequeuePenStrokeInfoP) ( startPtP, endPtP);
}
#endif

#ifdef L_EvtEnableGraffiti
void EvtEnableGraffiti (Boolean enable)
{
	void (*EvtEnableGraffitiP) (Boolean enable);

	GetParameter (&EvtEnableGraffitiP , sizeof(void *), pEvtEnableGraffiti );
	(*EvtEnableGraffitiP) (enable);
}
#endif

#ifdef L_EvtEnqueueKey
Err EvtEnqueueKey (WChar ascii, UInt16 keycode,UInt16 modifiers)
{
	Err (*EvtEnqueueKeyP) (WChar ascii, UInt16 keycode,UInt16 modifiers);

	GetParameter (&EvtEnqueueKeyP , sizeof(void *), pEvtEnqueueKey );
	return	(*EvtEnqueueKeyP) ( ascii,  keycode, modifiers);
}
#endif

#ifdef L_EvtEventAvail
Boolean EvtEventAvail (void)
{
	Boolean (*EvtEventAvailP) (void);

	GetParameter (&EvtEventAvailP , sizeof(void *), pEvtEventAvail );
	return	(*EvtEventAvailP) ();
}
#endif

#ifdef L_EvtFlushKeyQueue
Err EvtFlushKeyQueue (void)
{
	Err (*EvtFlushKeyQueueP) (void);

	GetParameter (&EvtFlushKeyQueueP , sizeof(void *), pEvtFlushKeyQueue );
	return   (*EvtFlushKeyQueueP) ();
}
#endif

#ifdef L_EvtFlushNextPenStroke

Err EvtFlushNextPenStroke (void)
{
	Err (*EvtFlushNextPenStrokeP) (void);

	GetParameter (&EvtFlushNextPenStrokeP , sizeof(void *), pEvtFlushNextPenStroke );
	return	(*EvtFlushNextPenStrokeP) ();
}
#endif

#ifdef L_EvtFlushPenQueue
Err EvtFlushPenQueue (void)
{
	Err (*EvtFlushPenQueueP) (void);

	GetParameter (&EvtFlushPenQueueP , sizeof(void *), pEvtAddEventToQueue );
	return	(*EvtFlushPenQueueP) ();
}
#endif


#ifdef L_EvtGetEvent
void EvtGetEvent(EventType *event, Int32 timeout)
{     
	void (*EvtGetEventP)(EventType *event, Int32 timeout);

	GetParameter (&EvtGetEventP , sizeof(void *), pEvtGetEvent );
	(*EvtGetEventP)(event,  timeout);
}
#endif

#ifdef L_EvtGetPen
void EvtGetPen (Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown)
{     
	void (*EvtGetPenP) (Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown);

	GetParameter (&EvtGetPenP , sizeof(void *), pEvtGetPen );
	(*EvtGetPenP) (pScreenX, pScreenY, pPenDown);
}
#endif
/*
#ifdef L_EvtGetPenBtnList
 PenBtnInfoType* EvtGetPenBtnList(UInt16* numButtons)
{
	 PenBtnInfoType*   (*EvtGetPenBtnListP)(UInt16* numButtons);

	GetParameter (&EvtGetPenBtnListP , sizeof(void *), pEvtGetPenBtnList );
	return  (*EvtGetPenBtnListP)( numButtons);
}
#endif

#ifdef L_EvtGetSilkscreenAreaList
 SilkscreenAreaType* EvtGetSilkscreenAreaList(UInt16* numAreas)
{
	 SilkscreenAreaType* (*EvtGetSilkscreenAreaListP)(UInt16* numAreas);

	GetParameter (&EvtGetSilkscreenAreaListP , sizeof(void *), pEvtGetSilkscreenAreaList );
	return	(*EvtGetSilkscreenAreaListP)(numAreas);
}
#endif
*/
//#define EvtKeydownIsVirtual(eventP) (((eventP)->data.keyDown.modifiers &virtualKeyMask) != 0)
#ifdef L_EvtKeyQueueEmpty
Boolean EvtKeyQueueEmpty (void)
{
	Boolean (*EvtKeyQueueEmptyP) (void);

	GetParameter (&EvtKeyQueueEmptyP , sizeof(void *), pEvtKeyQueueEmpty );
	return	(*EvtKeyQueueEmptyP) ();
}
#endif

#ifdef L_EvtKeyQueueSize
UInt32 EvtKeyQueueSize (void)
{     
	UInt32 (*EvtKeyQueueSizeP) (void);

	GetParameter (&EvtKeyQueueSizeP , sizeof(void *), pEvtKeyQueueSize );
	return	(*EvtKeyQueueSizeP) ();
}
#endif

#ifdef L_EvtPenQueueSize
UInt32 EvtPenQueueSize (void)
{
	UInt32 (*EvtPenQueueSizeP) (void);

	GetParameter (&EvtPenQueueSizeP , sizeof(void *), pEvtPenQueueSize );
	return	(*EvtPenQueueSizeP) ();
}
#endif

#ifdef L_EvtProcessSoftKeyStroke
Err EvtProcessSoftKeyStroke(PointType* startPtP,PointType* endPtP)
{     
	Err (*EvtProcessSoftKeyStrokeP)(PointType* startPtP,PointType* endPtP);

	GetParameter (&EvtProcessSoftKeyStrokeP , sizeof(void *), pEvtProcessSoftKeyStroke );
	return	(*EvtProcessSoftKeyStrokeP)( startPtP, endPtP);
}
#endif

#ifdef L_EvtResetAutoOffTimer
Err EvtResetAutoOffTimer (void)
{     
	Err (*EvtResetAutoOffTimerP) (void);

	GetParameter (&EvtResetAutoOffTimerP , sizeof(void *), pEvtResetAutoOffTimer );
	return	(*EvtResetAutoOffTimerP) ();
}
#endif
/*
#ifdef L_EvtSetAutoOffTimer
Err EvtSetAutoOffTimer(EvtSetAutoOffCmd cmd,UInt16 timeoutSecs)
{
	Err (*EvtSetAutoOffTimerP)(EvtSetAutoOffCmd cmd,UInt16 timeoutSecs);

	GetParameter (&EvtSetAutoOffTimerP , sizeof(void *), pEvtSetAutoOffTimer );
	return	(*EvtSetAutoOffTimerP)( cmd, timeoutSecs);
}
#endif
 */
#ifdef L_EvtSetNullEventTick
Boolean EvtSetNullEventTick(UInt32 tick)
{
	Boolean (*EvtSetNullEventTickP)(UInt32 tick);

	GetParameter (&EvtSetNullEventTickP , sizeof(void *), pEvtSetNullEventTick );
	return	(*EvtSetNullEventTickP)(tick);
}
#endif

#ifdef L_EvtSysEventAvail
Boolean EvtSysEventAvail (Boolean ignorePenUps)
{
	Boolean (*EvtSysEventAvailP) (Boolean ignorePenUps);

	GetParameter (&EvtSysEventAvailP , sizeof(void *), pEvtSysEventAvail );
	return	(*EvtSysEventAvailP) (ignorePenUps);
}
#endif

#ifdef L_EvtWakeup
Err EvtWakeup (void)
{
	Err (*EvtWakeupP) (void);

	GetParameter (&EvtWakeupP , sizeof(void *), pEvtWakeup );
	return	(*EvtWakeupP) ();
}
#endif



////////////////////////////////////////////////////////////
// System Manager Library, completed 33/33 functions now.
////////////////////////////////////////////////////////////

#ifdef L_SysAppLaunch
Err SysAppLaunch (UInt16 cardNo, LocalID dbID, UInt16 launchFlags,
								  UInt16 cmd, MemPtr cmdPBP, UInt32 *resultP)
{
	Err (*SysAppLaunchP) (UInt16 cardNo, LocalID dbID, UInt16 launchFlags,
								  UInt16 cmd, MemPtr cmdPBP, UInt32 *resultP);

	GetParameter (&SysAppLaunchP, sizeof(void *), pSysAppLaunch );
	return (*SysAppLaunchP) ( cardNo,  dbID,  launchFlags, cmd,  cmdPBP, resultP);
}
#endif

#ifdef L_SysBatteryInfo
UInt16 SysBatteryInfo (Boolean set, UInt16 *warnThresholdP,
										 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
										 SysBatteryKind *kindP, Boolean *pluggedIn, 
										 UInt8 *percentP)
{     
	UInt16 (*SysBatteryInfoP) (Boolean set, UInt16 *warnThresholdP,
										 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
										 SysBatteryKind *kindP, Boolean *pluggedIn,
										 UInt8 *percentP);

	GetParameter (&SysBatteryInfoP , sizeof(void *), pSysBatteryInfo );
	return (*SysBatteryInfoP) ( set, warnThresholdP, criticalThresholdP, maxTicksP, kindP, pluggedIn,
										 percentP);
}				
#endif

#ifdef L_SysBatteryInfoV20
UInt16 SysBatteryInfoV20 (Boolean set, UInt16 *warnThresholdP,	 UInt16 *criticalThresholdP, UInt16 *maxTicksP,		 SysBatteryKind *kindP, Boolean *pluggedIn)
{
	UInt16 (*SysBatteryInfoV20P) (Boolean set, UInt16 *warnThresholdP,	 UInt16 *criticalThresholdP, UInt16 *maxTicksP,		 SysBatteryKind *kindP, Boolean *pluggedIn);

	GetParameter (&SysBatteryInfoV20P , sizeof(void *), pSysBatteryInfoV20 );
	return (*SysBatteryInfoV20P) ( set, warnThresholdP,criticalThresholdP, maxTicksP, kindP, pluggedIn);
}
#endif
/*
#ifdef L_SysBinarySearch
Boolean SysBinarySearch (void const *baseP,const UInt16 numOfElements, const Int16 width,
				  		SearchFuncPtr searchF, void const *searchData,const Int32 other, Int32* position,
						const Boolean findFirst)
{
	Boolean (*SysBinarySearchP) (void const *baseP,const UInt16 numOfElements, const Int16 width,
				  		SearchFuncPtr searchF, void const *searchData,const Int32 other, Int32* position,
						const Boolean findFirst);

	GetParameter (&SysBinarySearchP , sizeof(void *), pSysBinarySearch );
	return  (*SysBinarySearchP) ( baseP, numOfElements,  width, searchF,  searchData,  other,  position,
						 findFirst);
}
#endif
*/
#ifdef L_SysBroadcastActionCode
Err SysBroadcastActionCode (UInt16 cmd,MemPtr cmdPBP)
{
	Err (*SysBroadcastActionCodeP) (UInt16 cmd,MemPtr cmdPBP)  ;

	GetParameter (&SysBroadcastActionCodeP , sizeof(void *), pSysBroadcastActionCode );
	return (*SysBroadcastActionCodeP) (cmd,cmdPBP) ;
}
#endif

#ifdef L_SysCopyStringResource
void SysCopyStringResource (Char* string,Int16 theID)
{
	void (*SysCopyStringResourceP) (Char* string,Int16 theID);

	GetParameter (&SysCopyStringResourceP , sizeof(void *), pSysCopyStringResource );
	 (*SysCopyStringResourceP) ( string, theID);

}
#endif

#ifdef L_SysCreateDataBaseList
Boolean SysCreateDataBaseList (UInt32 type,UInt32 creator, UInt16* dbCount, MemHandle *dbIDs,Boolean lookupName)
{
	Boolean (*SysCreateDataBaseListP) (UInt32 type,UInt32 creator, UInt16* dbCount, MemHandle *dbIDs,Boolean lookupName);

	GetParameter (&SysCreateDataBaseListP , sizeof(void *), pSysCreateDataBaseList );
	return (*SysCreateDataBaseListP) (type, creator,  dbCount, dbIDs, lookupName);
}
#endif



#ifdef L_SysCreatePanelList
Boolean SysCreatePanelList (UInt16 *panelCount, MemHandle *panelIDs)
{
	Boolean (*SysCreatePanelListP) (UInt16 *panelCount, MemHandle *panelIDs);

	GetParameter (&SysCreatePanelListP , sizeof(void *), pSysCreatePanelList );
	return (*SysCreatePanelListP) (panelCount, panelIDs);
}
#endif

#ifdef L_SysCurAppDatabase
Err SysCurAppDatabase (UInt16 *cardNoP, LocalID *dbIDP)
{
	Err (*SysCurAppDatabaseP) (UInt16 *cardNoP, LocalID *dbIDP);

	GetParameter (&SysCurAppDatabaseP , sizeof(void *), pSysCurAppDatabase );
	return (*SysCurAppDatabaseP) (cardNoP, dbIDP);
}
#endif

#ifdef L_SysErrString
Char* SysErrString (Err err, Char* strP,UInt16 maxLen)
{
	Char* (*SysErrStringP) (Err err, Char* strP,UInt16 maxLen);

	GetParameter (&SysErrStringP , sizeof(void *), pSysErrString );
	return (*SysErrStringP) ( err, strP, maxLen);
}
#endif


#ifdef L_SysFormPointerArrayToStrings
MemHandle SysFormPointerArrayToStrings (Char* c,Int16 stringCount)
{     
	MemHandle (*SysFormPointerArrayToStringsP) (Char* c,Int16 stringCount);

	GetParameter (&SysFormPointerArrayToStringsP , sizeof(void *), pSysFormPointerArrayToStrings );
	return (*SysFormPointerArrayToStringsP) ( c, stringCount);
}
#endif




#ifdef L_SysGetOSVersionString
Char *SysGetOSVersionString ()
{     
	Char *(*SysGetOSVersionStringP) ();

	GetParameter (&SysGetOSVersionStringP , sizeof(void *), pSysGetOSVersionString );
	return(*SysGetOSVersionStringP) ();
}
#endif

#ifdef L_SysGetROMToken
Err SysGetROMToken (UInt16 cardNo, UInt32 token,UInt8 **dataP, UInt16 *sizeP)
{     
	Err (*SysGetROMTokenP) (UInt16 cardNo, UInt32 token,UInt8 **dataP, UInt16 *sizeP);

	GetParameter (&SysGetROMTokenP , sizeof(void *), pSysGetROMToken );
	return  (*SysGetROMTokenP) ( cardNo,  token,dataP, sizeP);
}
#endif

#ifdef L_SysGetStackInfo
Boolean SysGetStackInfo (MemPtr *startPP,MemPtr *endPP)
{     
	Boolean (*SysGetStackInfoP) (MemPtr *startPP,MemPtr *endPP);

	GetParameter (&SysGetStackInfoP , sizeof(void *), pSysGetStackInfo );
	return  (*SysGetStackInfoP) (startPP,endPP);
}
#endif

#ifdef L_SysGetTrapAddress
void* SysGetTrapAddress (UInt16 trapNum)
{     
	void* (*SysGetTrapAddressP) (UInt16 trapNum);

	GetParameter (&SysGetTrapAddressP , sizeof(void *), pSysGetTrapAddress );
	return (*SysGetTrapAddressP) (trapNum);
}
#endif
/*
#ifdef L_SysGraffitiReferenceDialog
void SysGraffitiReferenceDialog(ReferenceType referenceType)
{
	void (*SysGraffitiReferenceDialogP)(ReferenceType referenceType);

	GetParameter (&SysGraffitiReferenceDialogP , sizeof(void *), pSysGraffitiReferenceDialog );
	(*SysGraffitiReferenceDialogP)(referenceType);
}
#endif

#ifdef L_SysGremlins
UInt32 SysGremlins (GremlinFunctionType selector,GremlinParamsType *params)
{
	UInt32 (*SysGremlinsP) (GremlinFunctionType selector,GremlinParamsType *params);

	GetParameter (&SysGremlinsP , sizeof(void *), pSysGremlins );
	return (*SysGremlinsP) ( selector,params);
}
#endif
*/
#ifdef L_SysHandleEvent
Boolean SysHandleEvent (EventPtr eventP)
{
	Boolean (*SysHandleEventP) (EventPtr eventP);

	GetParameter (&SysHandleEventP , sizeof(void *), pSysHandleEvent );
	return (*SysHandleEventP) (eventP);
}
#endif
/*
#ifdef L_SysInsertionSort
void SysInsertionSort (void* baseP,Int16 numOfElements, Int16 width,const CmpFuncPtr comparF, const Int32 other)
{
	void (*SysInsertionSortP) (void* baseP,Int16 numOfElements, Int16 width,const CmpFuncPtr comparF, const Int32 other);

	GetParameter (&SysInsertionSortP , sizeof(void *), pSysInsertionSort );
	 (*SysInsertionSortP) (baseP, numOfElements,  width, comparF,  other);
}
#endif
*/



#ifdef L_SysKeyboardDialog
void SysKeyboardDialog (KeyboardType kbd)
{
	void (*SysKeyboardDialogP) (KeyboardType kbd);

	GetParameter (&SysKeyboardDialogP , sizeof(void *), pSysKeyboardDialog );
	(*SysKeyboardDialogP) ( kbd);

}
#endif

#ifdef L_SysKeyboardDialogV10
void SysKeyboardDialogV10 ()
{
	void (*SysKeyboardDialogV10P) ();

	GetParameter (&SysKeyboardDialogV10P , sizeof(void *), pSysKeyboardDialogV10 );
	(*SysKeyboardDialogV10P) ();
}
#endif

#ifdef L_SysLibFind
Err SysLibFind (const Char* nameP, UInt16 *refNumP)
{
	Err (*SysLibFindP) (const Char* nameP, UInt16 *refNumP);

	GetParameter (&SysLibFindP , sizeof(void *), pSysLibFind );
	return (*SysLibFindP) ( nameP, refNumP);
}
#endif

#ifdef L_SysLibLoad
Err SysLibLoad (UInt32 libType, UInt32 libCreator,UInt16* refNumP)
{     
	Err (*SysLibLoadP) (UInt32 libType, UInt32 libCreator,UInt16* refNumP);

	GetParameter (&SysLibLoadP , sizeof(void *), pSysLibLoad );
	return (*SysLibLoadP) ( libType,  libCreator, refNumP);
}
#endif

#ifdef L_SysLibRemove
Err SysLibRemove (UInt16 refNum)
{     
	Err (*SysLibRemoveP) (UInt16 refNum);

	GetParameter (&SysLibRemoveP , sizeof(void *), pSysLibRemove );
	return (*SysLibRemoveP) (refNum);
}
#endif

/*
#ifdef L_SysQSort
void SysQSort (void* baseP, Int16 numOfElements,Int16 width, const CmpFuncPtr comparF,const Int32 other)
{
	void (*SysQSortP) (void* baseP, Int16 numOfElements,Int16 width, const CmpFuncPtr comparF,const Int32 other);

	GetParameter (&SysQSortP , sizeof(void *), pSysQSort );
	 (*SysQSortP) ( baseP,  numOfElements, width,   comparF,  other);
}
#endif
*/


#ifdef L_SysRandom
Int16 SysRandom (UInt32 newSeed)
{     
	Int16 (*SysRandomP) (UInt32 newSeed);

	GetParameter (&SysRandomP , sizeof(void *), pSysRandom );
	return (*SysRandomP) ( newSeed);
}
#endif

#ifdef L_SysReset
void SysReset (void)
{     
	void (*SysResetP) (void);

	GetParameter (&SysResetP , sizeof(void *), pSysReset );
	 (*SysResetP) ();

}
#endif

#ifdef L_SysSetAutoOffTime
UInt16 SysSetAutoOffTime (UInt16 seconds)
{     
	UInt16 (*SysSetAutoOffTimeP) (UInt16 seconds);

	GetParameter (&SysSetAutoOffTimeP , sizeof(void *), pSysSetAutoOffTime );
	return (*SysSetAutoOffTimeP) (seconds);
}
#endif

#ifdef L_SysSetTrapAddressP
Err SysSetTrapAddress (UInt16 trapNum,void* procP)
{     
	Err (*SysSetTrapAddressP) (UInt16 trapNum,void* procP);

	GetParameter (&SysSetTrapAddressP , sizeof(void *), pSysSetTrapAddress );
	return (*SysSetTrapAddressP) ( trapNum, procP);
}
#endif

#ifdef L_SysStringByIndex
Char* SysStringByIndex (UInt16 resID,UInt16 index, Char* strP, UInt16 maxLen)
{     
	Char* (*SysStringByIndexP) (UInt16 resID,UInt16 index, Char* strP, UInt16 maxLen);

	GetParameter (&SysStringByIndexP , sizeof(void *), pSysStringByIndex );
	return (*SysStringByIndexP) ( resID, index,  strP,  maxLen);
}
#endif



#ifdef L_SysTaskDelay
Err SysTaskDelay (Int32 delay)
{     
	Err (*SysTaskDelayP) (Int32 delay);

	GetParameter (&SysTaskDelayP , sizeof(void *), pSysTaskDelay );
	return(*SysTaskDelayP) ( delay);
}
#endif

#ifdef L_SysTicksPerSecond
UInt16 SysTicksPerSecond (void)
{     
	UInt16 (*SysTicksPerSecondP) (void);

	GetParameter (&SysTicksPerSecondP , sizeof(void *), pSysTicksPerSecond );
	return (*SysTicksPerSecondP) ();
}
#endif

#ifdef L_SysUIAppSwitch
Err SysUIAppSwitch (UInt16 cardNo, LocalID dbID, UInt16 cmd, 
									 MemPtr cmdPBP)
{     
	Err (*SysUIAppSwitchP) (UInt16 cardNo, LocalID dbID, UInt16 cmd, 
									 MemPtr cmdPBP);

	GetParameter (&SysUIAppSwitchP , sizeof(void *), pSysUIAppSwitch );
	return (*SysUIAppSwitchP) ( cardNo,  dbID,  cmd,   cmdPBP);
}
#endif



////////////////////////////////////////////////////////////
// String Manager Library, completed 18/19 functions now.
////////////////////////////////////////////////////////////

#ifdef L_StrAToI
Int32 StrAToI(const Char *str)
{     
	Int32 (*StrAToIP)(const Char *str);

	GetParameter (&StrAToIP , sizeof(void *), pStrAToI );
	return (*StrAToIP)(str);
}
#endif

#ifdef L_StrCaselessCompare
Int16 StrCaselessCompare (const Char *s1, const Char *s2)
{
	Int16 (*StrCaselessCompareP) (const Char *s1, const Char *s2);

	GetParameter (&StrCaselessCompareP , sizeof(void *), pStrCaselessCompare );
	return (*StrCaselessCompareP) (s1,s2);
}
#endif

#ifdef L_StrCat
Char* StrCat (Char *dst, const Char* src)
{     
	Char* (*StrCatP) (Char *dst, const Char* src);
	
	GetParameter (&StrCatP , sizeof(void *), pStrCat );
	return (*StrCatP) (dst,   src);
}
#endif

#ifdef L_StrChr
Char* StrChr (const Char *str, WChar chr)
{     
	Char* (*StrChrP) (const Char *str, WChar chr);

	GetParameter (&StrChrP , sizeof(void *), pStrChr );
	return (*StrChrP) (str,  chr);

}
#endif

#ifdef L_StrCompare
Int16 StrCompare (const Char *dst, const Char* src)
{     
	Int16 (*StrCompareP) (const Char *dst, const Char* src);

	GetParameter (&StrCompareP , sizeof(void *), pStrCompare );
	return (*StrCompareP) (dst,  src);
}
#endif

#ifdef L_StrCopy
Char* StrCopy (Char *dst, const Char* src)
{     
	Char* (*StrCopyP) (Char *dst, const Char* src);

	GetParameter (&StrCopyP , sizeof(void *), pStrCopy );
	return (*StrCopyP) (dst, src);
}
#endif

#ifdef L_StrDelocalizeNumber
Char* StrDelocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator)
{     
	Char* (*StrDelocalizeNumberP) (Char *s, Char thousandSeparator, Char decimalSeparator);

	GetParameter (&StrDelocalizeNumberP , sizeof(void *), pStrDelocalizeNumber );
	return (*StrDelocalizeNumberP) (s,  thousandSeparator,  decimalSeparator);

}
#endif

#ifdef L_StrIToA
Char* StrIToA(Char *s, Int32 i)
{     
	Char* (*StrIToAP)(Char *s, Int32 i);

	GetParameter (&StrIToAP , sizeof(void *), pStrIToA );
	return (*StrIToAP)(s,  i);
}
#endif

#ifdef L_StrIToH
Char* StrIToH(Char *s, Int32 i)
{     
	Char* (*StrIToHP)(Char *s, Int32 i);

	GetParameter (&StrIToHP , sizeof(void *), pStrIToH );
	return (*StrIToHP)(s, i);
}
#endif

#ifdef L_StrLen
UInt16 StrLen (const Char* src)
{     
	UInt16 (*StrLenP) (const Char* src);

	GetParameter (&StrLenP , sizeof(void *), pStrLen );
	return (*StrLenP) ( src);
}
#endif

#ifdef L_StrLocalizeNumber
Char* StrLocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator)
{     
	Char* (*StrLocalizeNumberP) (Char *s, Char thousandSeparator, Char decimalSeparator);

	GetParameter (&StrLocalizeNumberP , sizeof(void *), pStrLocalizeNumber );
	return(*StrLocalizeNumberP) (s,  thousandSeparator,  decimalSeparator);
}
#endif

#ifdef L_StrNCaselessCompare
Int16 StrNCaselessCompare (const Char *s1, const Char *s2, Int32 n)
{     
	Int16 (*StrNCaselessCompareP) (const Char *s1, const Char *s2, Int32 n);

	GetParameter (&StrNCaselessCompareP , sizeof(void *), pStrNCaselessCompare );
	return (*StrNCaselessCompareP) (s1,  s2,  n);
}
#endif

#ifdef L_StrNCat
Char* StrNCat (Char *dst, const Char* src, Int16 n)
{     
	Char* (*StrNCatP) (Char *dst, const Char* src, Int16 n);

	GetParameter (&StrNCatP , sizeof(void *), pStrNCat );
	return (*StrNCatP) (dst,  src,  n);
}
#endif

#ifdef L_StrNCompare

Int16 StrNCompare (const Char *dst, const Char* src, UInt32 n)
{     
	Int16 (*StrNCompareP) (const Char *dst, const Char* src, UInt32 n);

	GetParameter (&StrNCompareP , sizeof(void *), pStrNCompare );
	return(*StrNCompareP) ( dst,  src,  n);
}
#endif

#ifdef L_StrNCopy
Char* StrNCopy (Char *dst, const Char* src, Int16 n)
{     
	Char* (*StrNCopyP) (Char *dst, const Char* src, Int16 n);

	GetParameter (&StrNCopyP , sizeof(void *), pStrNCopy );
	return(*StrNCopyP) (dst,   src,  n);
}
#endif

//Int16 StrPrintF (Char* s, const Char *formatStr, ...);

#ifdef L_StrStr
Char *StrStr (const Char *str, const Char *token)
{     
	Char *(*StrStrP) (const Char *str, const Char *token);

	GetParameter (&StrStrP , sizeof(void *), pStrStr );
	return(*StrStrP) (str, token);
}
#endif

#ifdef L_StrToLower
Char* StrToLower (Char *dst, const Char* src)
{     
	Char* (*StrToLowerP) (Char *dst, const Char* src);

	GetParameter (&StrToLowerP , sizeof(void *), pStrToLower );
	return (*StrToLowerP) (dst,  src);
}
#endif

#ifdef L_StrVPrintF
Int16 StrVPrintF (Char* s, const Char *formatStr, VoidPtr argParam)
{    
	Int16 (*StrVPrintFP) (Char* s, const Char *formatStr, VoidPtr argParam);

	GetParameter (&StrVPrintFP , sizeof(void *), pStrVPrintF );
	return (*StrVPrintFP) ( s, formatStr,  argParam);
}

#endif

////////////////////////////////////////////////////////////
// Text Manager Library, completed 12/38 functions now.
////////////////////////////////////////////////////////////
#ifdef L_TxtByteAttr
UInt8 TxtByteAttr (UInt8 inByte)
{     
	UInt8 (*TxtByteAttrP) (UInt8 inByte) ;

	GetParameter (&TxtByteAttrP , sizeof(void *), pTxtByteAttr );
	return (*TxtByteAttrP) (inByte)  ;
}
#endif

#ifdef L_TxtCaselessCompare
Int16 TxtCaselessCompare (const Char* s1,UInt16 s1Len, UInt16* s1MatchLen, const Char* s2,UInt16 s2Len, UInt16* s2MatchLen)
{
	Int16 (*TxtCaselessCompareP) (const Char* s1,UInt16 s1Len, UInt16* s1MatchLen, const Char* s2,UInt16 s2Len, UInt16* s2MatchLen);

	GetParameter (&TxtCaselessCompareP , sizeof(void *), pTxtCaselessCompare );
	return (*TxtCaselessCompareP) (  s1, s1Len,  s1MatchLen,   s2, s2Len,  s2MatchLen);
}
#endif

#ifdef L_TxtCharAttr
UInt16 TxtCharAttr (WChar inChar)
{     
	UInt16 (*TxtCharAttrP) (WChar inChar);
	
	GetParameter (&TxtCharAttrP , sizeof(void *), pTxtCharAttr );
	return (*TxtCharAttrP) (inChar);
}
#endif

#ifdef L_TxtCharBounds
WChar TxtCharBounds (const Char* inText,UInt32 inOffset, UInt32* outStart, UInt32* outEnd)
{     
	WChar (*TxtCharBoundsP) (const Char* inText,UInt32 inOffset, UInt32* outStart, UInt32* outEnd);
	
	GetParameter (&TxtCharBoundsP , sizeof(void *), pTxtCharBounds );
	return (*TxtCharBoundsP) (  inText, inOffset,  outStart,  outEnd);
}
#endif
/*
#ifdef L_TxtCharEncoding
CharEncodingType TxtCharEncoding (WChar inChar)
{
	CharEncodingType (*TxtCharEncodingP) (WChar inChar);

	GetParameter (&TxtCharEncodingP , sizeof(void *), pTxtCharEncoding );
	return (*TxtCharEncodingP) (inChar);
}
#endif
*/



#ifdef L_TxtCharIsAlNum
Boolean TxtCharIsAlNum (Char ch)
{     
	Boolean (*TxtCharIsAlNumP) (Char ch);

	GetParameter (&TxtCharIsAlNumP , sizeof(void *), pTxtCharIsAlNum );
	return (*TxtCharIsAlNumP) ( ch);
}
#endif

#ifdef L_TxtCharIsAlpha
Boolean TxtCharIsAlpha (Char ch)
{
	Boolean (*TxtCharIsAlphaP) (Char ch);

	GetParameter (&TxtCharIsAlphaP , sizeof(void *), pTxtCharIsAlpha );
	return (*TxtCharIsAlphaP) ( ch);
}
#endif

#ifdef L_TxtCharIsCntrl
Boolean TxtCharIsCntrl (Char ch)
{
	Boolean (*TxtCharIsCntrlP) (Char ch);

	GetParameter (&TxtCharIsCntrlP , sizeof(void *), pTxtCharIsCntrl );
	return (*TxtCharIsCntrlP) (ch);
}
#endif

#ifdef L_TxtCharIsDelim
Boolean TxtCharIsDelim (Char ch)
{     
	Boolean (*TxtCharIsDelimP) (Char ch);

	GetParameter (&TxtCharIsDelimP , sizeof(void *), pTxtCharIsDelim );
}
#endif

#ifdef L_TxtCharIsDigit
Boolean TxtCharIsDigit (Char ch)
{     
	Boolean (*TxtCharIsDigitP) (Char ch);

	GetParameter (&TxtCharIsDigitP , sizeof(void *), pTxtCharIsDigit );
	return (*TxtCharIsDigitP) ( ch);
}
#endif

#ifdef L_TxtCharIsGraph
Boolean TxtCharIsGraph (Char ch)
{
	Boolean (*TxtCharIsGraphP) (Char ch);

	GetParameter (&TxtCharIsGraphP , sizeof(void *), pTxtCharIsGraph );
	return (*TxtCharIsGraphP) (ch);
}
#endif

#ifdef L_TxtCharIsHardKey
Boolean  TxtCharIsHardKey (Char m,Char ch)
{
	Boolean (*TxtCharIsHardKeyP) (Char m,Char ch);

	GetParameter (&TxtCharIsHardKeyP , sizeof(void *), pTxtCharIsHardKey );
	return (*TxtCharIsHardKeyP) (m,ch);
}
#endif

#ifdef L_TxtCharIsHex
Boolean TxtCharIsHex   (Char ch)
{     
	Boolean (*TxtCharIsHexP)   (Char ch);

	GetParameter (&TxtCharIsHexP , sizeof(void *), pTxtCharIsHex );
	return (*TxtCharIsHexP) (ch);
}
#endif

#ifdef L_TxtCharIsLower
Boolean TxtCharIsLower (Char ch)
{     
	Boolean (*TxtCharIsLowerP) (Char ch);

	GetParameter (&TxtCharIsLowerP , sizeof(void *), pTxtCharIsLower );
	return (*TxtCharIsLowerP) (ch);
}
#endif

#ifdef L_TxtCharIsPrint
Boolean TxtCharIsPrint (Char ch)
{
	Boolean (*TxtCharIsPrintP) (Char ch);

	GetParameter (&TxtCharIsPrintP , sizeof(void *), pTxtCharIsPrint );
	return (*TxtCharIsPrintP) (ch);
}
#endif

#ifdef L_TxtCharIsSpace
Boolean TxtCharIsSpace (Char ch)
{     
	Boolean (*TxtCharIsSpaceP) (Char ch);

	GetParameter (&TxtCharIsSpaceP , sizeof(void *), pTxtCharIsSpace );
	return (*TxtCharIsSpaceP) ( ch);
}
#endif

#ifdef L_TxtCharIsUpper
Boolean TxtCharIsUpper (Char ch)
{     
	Boolean (*TxtCharIsUpperP) (Char ch);

	GetParameter (&TxtCharIsUpperP , sizeof(void *), pTxtCharIsUpper );
	return (*TxtCharIsUpperP) (ch);
}
#endif



#ifdef L_TxtCharSize
UInt16	TxtCharSize    (WChar inChar)
{    
	UInt16	(*TxtCharSizeP)    (WChar inChar);

	GetParameter (&TxtCharSizeP , sizeof(void *), pTxtCharSize );
	return(*TxtCharSizeP)  ( inChar);
}
#endif

#ifdef L_TxtCharWidth
Int16 TxtCharWidth (WChar inChar)
{    
	Int16 (*TxtCharWidthP) (WChar inChar);

	GetParameter (&TxtCharWidthP , sizeof(void *), pTxtCharWidth );
	return 	(*TxtCharWidthP) (inChar);
}
#endif

#ifdef L_TxtCharIsValid
Boolean TxtCharIsValid (WChar inChar)
{    
	Boolean (*TxtCharIsValidP) (WChar inChar);

	GetParameter (&TxtCharIsValidP , sizeof(void *), pTxtCharIsValid );
	return	(*TxtCharIsValidP) ( inChar);
}
#endif

#ifdef L_TxtCharXAttr
UInt16 TxtCharXAttr (WChar inChar)
{    
	UInt16 (*TxtCharXAttrP) (WChar inChar);

	GetParameter (&TxtCharXAttrP , sizeof(void *), pTxtCharXAttr );
	return	(*TxtCharXAttrP) (inChar);
}
#endif

#ifdef L_TxtCompare
Int16 TxtCompare (const Char* s1, UInt16 s1Len,UInt16* s1MatchLen, const Char* s2, UInt16 s2Len,UInt16* s2MatchLen)
{    
	Int16 (*TxtCompareP) (const Char* s1, UInt16 s1Len,UInt16* s1MatchLen, const Char* s2, UInt16 s2Len,UInt16* s2MatchLen);

	GetParameter (&TxtCompareP , sizeof(void *), pTxtCompare );
	return	(*TxtCompareP) (  s1,  s1Len, s1MatchLen,   s2,  s2Len, s2MatchLen);
}
#endif
 /*
#ifdef L_TxtEncodingName
const Char* TxtEncodingName(CharEncodingType inEncoding)
{
	Char* (*TxtEncodingNameP)(CharEncodingType inEncoding);

	GetParameter (&TxtEncodingNameP , sizeof(void *), pTxtEncodingName );
	return	(*TxtEncodingNameP)(inEncoding);
}
#endif
 */
#ifdef L_TxtFindString
Boolean TxtFindString (const Char* inSourceStr,const Char* inTargetStr, UInt32* outPos,UInt16* outLength)
{    
	Boolean (*TxtFindStringP) (const Char* inSourceStr,const Char* inTargetStr, UInt32* outPos,UInt16* outLength);

	GetParameter (&TxtFindStringP , sizeof(void *), pTxtFindString );
	return	(*TxtFindStringP) (  inSourceStr, inTargetStr, outPos, outLength);
}
#endif

#ifdef L_TxtGetChar
WChar TxtGetChar (const Char* inText,UInt32 inOffset)
{
	WChar (*TxtGetCharP) (const Char* inText,UInt32 inOffset);

	GetParameter (&TxtGetCharP , sizeof(void *), pTxtGetChar );
	return	(*TxtGetCharP) ( inText, inOffset);
}
#endif

#ifdef L_TxtGetNextChar
UInt16 TxtGetNextChar (const Char* inText,UInt32 inOffset, WChar* outChar)
{    
	UInt16 (*TxtGetNextCharP) (const Char* inText,UInt32 inOffset, WChar* outChar);

	GetParameter (&TxtGetNextCharP , sizeof(void *), pTxtGetNextChar );
	return	(*TxtGetNextCharP) ( inText, inOffset,  outChar);
}
#endif

#ifdef L_TxtGetPreviousChar
UInt16 TxtGetPreviousChar (const Char* inText,UInt32 inOffset, WChar* outChar)
{    
	UInt16 (*TxtGetPreviousCharP) (const Char* inText,UInt32 inOffset, WChar* outChar);

	GetParameter (&TxtGetPreviousCharP , sizeof(void *), pTxtGetPreviousChar );
	return	(*TxtGetPreviousCharP) (  inText, inOffset,  outChar);
}
#endif

#ifdef L_TxtGetTruncationOffset
UInt32 TxtGetTruncationOffset (const Char* inText,UInt32 inOffset)
{    
	UInt32 (*TxtGetTruncationOffsetP) (const Char* inText,UInt32 inOffset);

	GetParameter (&TxtGetTruncationOffsetP , sizeof(void *), pTxtGetTruncationOffset );
	return	(*TxtGetTruncationOffsetP) (  inText, inOffset);
}
#endif
/*
#ifdef L_TxtMaxEncoding
CharEncodingType TxtMaxEncoding(CharEncodingType a, CharEncodingType b)
{
	CharEncodingType (*TxtMaxEncodingP)(CharEncodingType a, CharEncodingType b);

	GetParameter (&TxtMaxEncodingP , sizeof(void *), pTxtMaxEncoding );
	return	(*TxtMaxEncodingP)(a,  b);

}
#endif
 */
#ifdef L_TxtNextCharSize
UInt16  TxtNextCharSize (char* inText,UInt32 inOffset)
{    
	UInt16  (*TxtNextCharSizeP) (char* inText,UInt32 inOffset);

	GetParameter (&TxtNextCharSizeP , sizeof(void *), pTxtNextCharSize );
	return	 (*TxtNextCharSizeP) (inText, inOffset);
}
#endif

#ifdef L_TxtParamString
Char* TxtParamString (const Char* inTemplate,const Char* param0, const Char* param1,const Char* param2, const Char* param3)
{    
	Char* (*TxtParamStringP) (const Char* inTemplate,const Char* param0, const Char* param1,const Char* param2, const Char* param3);

	GetParameter (&TxtParamStringP , sizeof(void *), pTxtParamString );
	return	(*TxtParamStringP) (  inTemplate,  param0,   param1,  param2,   param3);
}
#endif

#ifdef L_TxtPreviousCharSize
UInt16  TxtPreviousCharSize (char* inText,UInt32 inOffset)
{
	UInt16  (*TxtPreviousCharSizeP) (char* inText,UInt32 inOffset);

	GetParameter (&TxtPreviousCharSizeP , sizeof(void *), pTxtPreviousCharSize );
	return	(*TxtPreviousCharSizeP) ( inText, inOffset);
}
#endif

#ifdef L_TxtReplaceStr
UInt16 TxtReplaceStr (Char* ioStr,UInt16 inMaxLen, const Char* inParamStr,UInt16 inParamNum)
{    
	UInt16 (*TxtReplaceStrP) (Char* ioStr,UInt16 inMaxLen, const Char* inParamStr,UInt16 inParamNum);

	GetParameter (&TxtReplaceStrP , sizeof(void *), pTxtReplaceStr );
	return	 (*TxtReplaceStrP) ( ioStr, inMaxLen,  inParamStr, inParamNum);
}
#endif

#ifdef L_TxtSetNextChar
UInt16 TxtSetNextChar (Char* ioText,UInt32 inOffset, WChar inChar)
{
	UInt16 (*TxtSetNextCharP) (Char* ioText,UInt32 inOffset, WChar inChar);

	GetParameter (&TxtSetNextCharP , sizeof(void *), pTxtSetNextChar );
	return	(*TxtSetNextCharP) ( ioText, inOffset,  inChar);
}
#endif
 /*
#ifdef L_TxtStrEncoding
CharEncodingType TxtStrEncoding(const Char* inStr)
{
	CharEncodingType (*TxtStrEncodingP)(const Char* inStr);

	GetParameter (&TxtStrEncodingP , sizeof(void *), pTxtStrEncoding );
	return	(*TxtStrEncodingP)(inStr);
}
#endif

#ifdef L_TxtTransliterate
Err TxtTransliterate (const Char* inSrcText,UInt16 inSrcLength, Char* outDstText,UInt16* ioDstLength, TranslitOpType inOp)
{
	Err (*TxtTransliterateP) (const Char* inSrcText,UInt16 inSrcLength, Char* outDstText,UInt16* ioDstLength, TranslitOpType inOp);

	GetParameter (&TxtTransliterateP , sizeof(void *), pTxtTransliterate );
	return	(*TxtTransliterateP) (inSrcText, inSrcLength, outDstText,ioDstLength,  inOp);
}
#endif
*/
#ifdef L_TxtWordBounds
Boolean TxtWordBounds (const Char* inText,UInt32 inLength, UInt32 inOffset,UInt32* outStart, UInt32* outEnd)
{
	Boolean (*TxtWordBoundsP) (const Char* inText,UInt32 inLength, UInt32 inOffset,UInt32* outStart, UInt32* outEnd);

	GetParameter (&TxtWordBoundsP , sizeof(void *), pTxtWordBounds );
	return	(*TxtWordBoundsP) ( inText, inLength,  inOffset, outStart,  outEnd);
}
#endif










