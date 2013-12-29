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
// Sound Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////

void PipeSndCreateMidiList(void)
{
//	WriteParameter (SndCreateMidiList, sizeof(void*), pSndCreateMidiList);
}
void PipeSndDoCmd(void)
{
//	WriteParameter (SndDoCmd, sizeof(void*), pSndDoCmd);
}
void PipeSndGetDefaultVolume(void)
{
//	WriteParameter (SndGetDefaultVolume, sizeof(void*), pSndGetDefaultVolume);
}
void PipeSndPlaySmf(void)
{
//	WriteParameter (SndPlaySmf, sizeof(void*), pSndPlaySmf);
}
void PipeSndPlaySmfResource (void)
{
//	WriteParameter (SndPlaySmfResource, sizeof(void*), pSndPlaySmfResource);
}
void PipeSndPlaySystemSound (void)
{
//	WriteParameter (SndPlaySystemSound, sizeof(void*), pSndPlaySystemSound);
}


////////////////////////////////////////////////////////////
// Standard IO Library, completed 5/5 functions now.
////////////////////////////////////////////////////////////

void PipeSioClearScreen(void)
{
//	WriteParameter (SioClearScreen, sizeof(void*), pSioClearScreen);
}
void PipeSioExecCommand(void)
{
//	WriteParameter (SioExecCommand, sizeof(void*), pSioExecCommand);
}
void PipeSioFree(void)
{
//	WriteParameter (SioFree, sizeof(void*), pSioFree);
}
void PipeSioHandleEvent(void)
{
//	WriteParameter (SioHandleEvent, sizeof(void*), pSioHandleEvent);
}
void PipeSioInit (void)
{
//	WriteParameter (SioInit , sizeof(void*), pSioInit );
}


////////////////////////////////////////////////////////////
// String Manager Library, completed 19/19 functions now.
////////////////////////////////////////////////////////////
void PipeStrAToI(void)
{
	WriteParameter (StrAToI, sizeof(void*), pStrAToI);
}

void PipeStrCaselessCompare (void)
{
//	WriteParameter (StrCaselessCompare, sizeof(void*), pStrCaselessCompare);
}

void PipeStrCat (void)
{
	WriteParameter (StrCat, sizeof(void*), pStrCat);
}
void PipeStrChr(void)
{
	WriteParameter (StrChr, sizeof(void*), pStrChr);
}
void PipeStrCompare (void)
{
	WriteParameter (StrCompare, sizeof(void*), pStrCompare);
}
void PipeStrCopy (void)
{
	WriteParameter (StrCopy, sizeof(void*), pStrCopy);
}

void PipeStrDelocalizeNumber(void)
{
//	WriteParameter (StrDelocalizeNumber, sizeof(void*), pStrDelocalizeNumber);
}

void PipeStrIToA(void)
{

	WriteParameter (StrIToA, sizeof(void*), pStrIToA);
}
void PipeStrIToH(void)
{
	WriteParameter (StrIToH, sizeof(void*), pStrIToH);
}
void PipeStrLen (void)
{
	WriteParameter (StrLen, sizeof(void*), pStrLen);
}

void PipeStrLocalizeNumber (void)
{
//	WriteParameter (StrLocalizeNumber, sizeof(void*), pStrLocalizeNumber);
}

void PipeStrNCaselessCompare (void)
{
//	WriteParameter (StrNCaselessCompare, sizeof(void*), pStrNCaselessCompare);
}

void PipeStrNCat (void)
{
	WriteParameter (StrNCat, sizeof(void*), pStrNCat);
}

void PipeStrNCompare (void)
{
	WriteParameter (StrNCompare, sizeof(void*), pStrNCompare);
}

void PipeStrNCopy (void)
{
	WriteParameter (StrNCopy, sizeof(void*), pStrNCopy);
}

//Int16 StrPrintF (Char* s, const Char *formatStr, ...);
void PipeStrPrintF (void)
{
//	WriteParameter (StrPrintF, sizeof(void*), pStrPrintF);
}

void PipeStrStr (void)
{
	WriteParameter (StrStr, sizeof(void*), pStrStr);
}

void PipeStrToLower (void)
{
	WriteParameter (StrToLower, sizeof(void*), pStrToLower);
}

void PipeStrVPrintF(void)
{

	WriteParameter (StrVPrintF, sizeof(void*), pStrVPrintF);
}


////////////////////////////////////////////////////////////
// System Dialogs Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeSysAppLauncherDialog (void)
{
//	WriteParameter (SysAppLauncherDialog, sizeof(void*), pSysAppLauncherDialog);
}
void PipeSysFatalAlert (void)
{
//	WriteParameter (SysFatalAlert, sizeof(void*), pSysFatalAlert);
}
void PipeSysGraffitiReferenceDialogs(void)
{
//	WriteParameter (SysGraffitiReferenceDialogs, sizeof(void*), pSysGraffitiReferenceDialogs);
}



//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 25/25 functions now.
//////////////////////////////////////////////////////////////
void PipeEvtAddEventToQueue (void)
{
	WriteParameter (EvtAddEventToQueue, sizeof(void*), pEvtAddEventToQueue);
}

void PipeEvtGetEvent(void)
{
	WriteParameter (EvtGetEvent, sizeof(void*), pEvtGetEvent);
}

void PipeSysHandleEvent(void)
{
	WriteParameter (SysHandleEvent, sizeof(void*), pSysHandleEvent);
}

void PipeEvtGetPen (void)
{
	WriteParameter (EvtGetPen, sizeof(void*), pEvtGetPen);
}

void PipeEvtAddUniqueEventToQueue(void)
{
//	WriteParameter (EvtAddUniqueEventToQueue, sizeof(void*), pEvtAddUniqueEventToQueue);
}
void PipeEvtCopyEvent(void)
{
//	WriteParameter (EvtCopyEvent, sizeof(void*), pEvtCopyEvent);
}
void PipeEvtDequeuePenPoint (void)
{
//	WriteParameter (EvtDequeuePenPoint, sizeof(void*), pEvtDequeuePenPoint);
}
void PipeEvtDequeuePenStrokeInfo (void)
{
//	WriteParameter (EvtDequeuePenStrokeInfo , sizeof(void*), pEvtDequeuePenStrokeInfo );
}
void PipeEvtEnableGraffiti(void)
{
//	WriteParameter (EvtEnableGraffiti, sizeof(void*), pEvtEnableGraffiti);
}
void PipeEvtEnqueueKey(void)
{
//	WriteParameter (EvtEnqueueKey, sizeof(void*), pEvtEnqueueKey);
}
void PipeEvtEventAvail(void)
{
//	WriteParameter (EvtEventAvail, sizeof(void*), pEvtEventAvail);
}
void PipeEvtFlushKeyQueue (void)
{
//	WriteParameter (EvtFlushKeyQueue, sizeof(void*), pEvtFlushKeyQueue);
}
void PipeEvtFlushNextPenStroke(void)
{
//	WriteParameter (EvtFlushNextPenStroke, sizeof(void*), pEvtFlushNextPenStroke);
}
void PipeEvtFlushPenQueue(void)
{
//	WriteParameter (EvtFlushPenQueue, sizeof(void*), pEvtFlushPenQueue);
}
void PipeEvtGetPenBtnList(void)
{
//	WriteParameter (EvtGetPenBtnList, sizeof(void*), pEvtGetPenBtnList);
}
void PipeEvtGetSilkscreenAreaList(void)
{
//	WriteParameter (EvtGetSilkscreenAreaList, sizeof(void*), pEvtGetSilkscreenAreaList);
}
void PipeEvtKeydownIsVirtual (void)
{
//	WriteParameter (EvtKeydownIsVirtual, sizeof(void*), pEvtKeydownIsVirtual);
}
void PipeEvtKeyQueueEmpty (void)
{
//	WriteParameter (EvtKeyQueueEmpty, sizeof(void*), pEvtKeyQueueEmpty);
}
void PipeEvtKeyQueueSize(void)
{
//	WriteParameter (EvtKeyQueueSize, sizeof(void*), pEvtKeyQueueSize);
}
void PipeEvtPenQueueSize(void)
{
//	WriteParameter (EvtPenQueueSize, sizeof(void*), pEvtPenQueueSize);
}
void PipeEvtProcessSoftKeyStroke(void)
{
//	WriteParameter (EvtProcessSoftKeyStroke, sizeof(void*), pEvtProcessSoftKeyStroke);
}
void PipeEvtResetAutoOffTimer(void)
{
//	WriteParameter (EvtResetAutoOffTimer, sizeof(void*), pEvtResetAutoOffTimer);
}
void PipeEvtSetAutoOffTimer(void)
{
//	WriteParameter (EvtSetAutoOffTimer, sizeof(void*), pEvtSetAutoOffTimer);
}
void PipeEvtSetNullEventTick(void)
{
//	WriteParameter (EvtSetNullEventTick, sizeof(void*), pEvtSetNullEventTick);
}
void PipeEvtSysEventAvail (void)
{
//	WriteParameter (EvtSysEventAvail, sizeof(void*), pEvtSysEventAvail);
}
void PipeEvtWakeup(void)
{
//	WriteParameter (EvtWakeup, sizeof(void*), pEvtWakeup);
}

////////////////////////////////////////////////////////////
// System Manager Library, completed 33/33 functions now.
////////////////////////////////////////////////////////////
void PipeSysAppLaunch (void)
{
	WriteParameter (SysAppLaunch, sizeof(void*), pSysAppLaunch);
}
void PipeSysBatteryInfo (void)
{
	WriteParameter (SysBatteryInfo, sizeof(void*), pSysBatteryInfo);
}
void PipeSysBatteryInfoV20 (void)
{
	WriteParameter (SysBatteryInfoV20, sizeof(void*), pSysBatteryInfoV20);
 }
void PipeSysCreatePanelList(void)
{
	WriteParameter (SysCreatePanelList, sizeof(void*), pSysCreatePanelList);
}
void PipeSysCurAppDatabase(void)
{
	WriteParameter (SysCurAppDatabase, sizeof(void*), pSysCurAppDatabase);
}
void PipeSysGetOSVersionString(void)
{
	WriteParameter (SysGetOSVersionString, sizeof(void*), pSysGetOSVersionString);
}
void PipeSysKeyboardDialog (void)
{
	WriteParameter (SysKeyboardDialog, sizeof(void*), pSysKeyboardDialog);
}
void PipeSysKeyboardDialogV10 (void)
{
	WriteParameter (SysKeyboardDialogV10, sizeof(void*), pSysKeyboardDialogV10);
}
void PipeSysLibFind (void)
{
	WriteParameter (SysLibFind, sizeof(void*), pSysLibFind);
}
void PipeSysRandom (void)
{
	WriteParameter (SysRandom, sizeof(void*), pSysRandom);
}
void PipeSysTaskDelay (void)
{
	WriteParameter (SysTaskDelay, sizeof(void*), pSysTaskDelay);
}
void PipeSysTicksPerSecond (void)
{
	WriteParameter (SysTicksPerSecond, sizeof(void*), pSysTicksPerSecond);
}
void PipeSysUIAppSwitch (void)

{
	WriteParameter (SysUIAppSwitch, sizeof(void*), pSysUIAppSwitch);
}



void PipeSysBinarySearch(void)
{
//	WriteParameter (SysBinarySearch, sizeof(void*), pSysBinarySearch);
}
void PipeSysBroadcastActionCode(void)
{
//	WriteParameter (SysBroadcastActionCode, sizeof(void*), pSysBroadcastActionCode);
}
void PipeSysCopyStringResource(void)
{
//	WriteParameter (SysCopyStringResource, sizeof(void*), pSysCopyStringResource);
}
void PipeSysCreateDataBaseList (void)
{
//	WriteParameter (SysCreateDataBaseList, sizeof(void*), pSysCreateDataBaseList);
}
void PipeSysErrString (void)
{
//	WriteParameter (SysErrString , sizeof(void*), pSysErrString );
}
void PipeSysFormPointerArrayToStrings (void)
{
//	WriteParameter (SysFormPointerArrayToStrings, sizeof(void*), pSysFormPointerArrayToStrings);
}
void PipeSysGetROMToken(void)
{
//	WriteParameter (SysGetROMToken, sizeof(void*), pSysGetROMToken);
}
void PipeSysGetStackInfo (void)
{
//	WriteParameter (SysGetStackInfo, sizeof(void*), pSysGetStackInfo);
}
void PipeSysGetTrapAddress(void)
{
//	WriteParameter (SysGetTrapAddress, sizeof(void*), pSysGetTrapAddress);
}
void PipeSysGraffitiReferenceDialog (void)
{
//	WriteParameter (SysGraffitiReferenceDialog, sizeof(void*), pSysGraffitiReferenceDialog);
}
void PipeSysGremlins(void)
{
//	WriteParameter (SysGremlins, sizeof(void*), pSysGremlins);
}
void PipeSysInsertionSort(void)
{
//	WriteParameter (SysInsertionSort, sizeof(void*), pSysInsertionSort);
}
void PipeSysLibLoad (void)
{
//	WriteParameter (SysLibLoad, sizeof(void*), pSysLibLoad);
}
void PipeSysLibRemove (void)
{
//	WriteParameter (SysLibRemove , sizeof(void*), pSysLibRemove );
}
void PipeSysQSort (void)
{
//	WriteParameter (SysLibRemove , sizeof(void*), pSysLibRemove );
}
void PipeSysReset (void)
{
//	WriteParameter (SysReset, sizeof(void*), pSysReset);
}
void PipeSysSetAutoOffTime (void)
{
//	WriteParameter (SysSetAutoOffTime , sizeof(void*), pSysSetAutoOffTime );
}
void PipeSysSetTrapAddress (void)
{
//	WriteParameter (SysSetTrapAddress, sizeof(void*), pSysSetTrapAddress);
}
void PipeSysStringByIndex(void)
{
//	WriteParameter (SysStringByIndex, sizeof(void*), pSysStringByIndex);
}


////////////////////////////////////////////////////////////
// Text Manager Library, completed 38/38 functions now.
////////////////////////////////////////////////////////////
void PipeTxtCharIsAlNum (void)
{
	WriteParameter (TxtCharIsAlNum, sizeof(void*), pTxtCharIsAlNum);
}

void PipeTxtCharIsAlpha (void)
{
	WriteParameter (TxtCharIsAlpha, sizeof(void*), pTxtCharIsAlpha);
}

void PipeTxtCharIsCntrl (void)
{
	WriteParameter (TxtCharIsCntrl, sizeof(void*), pTxtCharIsCntrl);
}

void PipeTxtCharIsDelim (void)
{
	WriteParameter (TxtCharIsDelim, sizeof(void*), pTxtCharIsDelim);
}

void PipeTxtCharIsDigit (void)
{
	WriteParameter (TxtCharIsDigit, sizeof(void*), pTxtCharIsDigit);
}

void PipeTxtCharIsGraph (void)
{
	WriteParameter (TxtCharIsGraph, sizeof(void*), pTxtCharIsGraph);
}

void PipeTxtCharIsHex (void)
{
	WriteParameter (TxtCharIsHex, sizeof(void*), pTxtCharIsHex);
}

void PipeTxtCharIsLower (void)
{
	WriteParameter (TxtCharIsLower, sizeof(void*), pTxtCharIsLower);
}

void PipeTxtCharIsPrint (void)
{
	WriteParameter (TxtCharIsPrint, sizeof(void*), pTxtCharIsPrint);
}

void PipeTxtCharIsSpace (void)
{
	WriteParameter (TxtCharIsSpace, sizeof(void*), pTxtCharIsSpace);
}

void PipeTxtCharIsUpper (void)
{
	WriteParameter (TxtCharIsUpper, sizeof(void*), pTxtCharIsUpper);
}

void PipeTxtCharSize (void)
{
	WriteParameter (TxtCharSize, sizeof(void*), pTxtCharSize);
}



void PipeTxtByteAttr(void)
{
//	WriteParameter (TxtByteAttr, sizeof(void*), pTxtByteAttr);
}
void PipeTxtCaselessCompare (void)
{
//	WriteParameter (TxtCaselessCompare, sizeof(void*), pTxtCaselessCompare);
}
void PipeTxtCharAttr (void)
{
//	WriteParameter (TxtCharAttr , sizeof(void*), pTxtCharAttr );
}
void PipeTxtCharBounds(void)
{
//	WriteParameter (TxtCharBounds, sizeof(void*), pTxtCharBounds);
}
void PipeTxtCharEncoding(void)
{
//	WriteParameter (TxtCharEncoding, sizeof(void*), pTxtCharEncoding);
}
void PipeTxtCharIsHardKey(void)
{
//	WriteParameter (TxtCharIsHardKey, sizeof(void*), pTxtCharIsHardKey);
}
void PipeTxtCharIsPunct(void)
{
//	WriteParameter (TxtCharIsPunct, sizeof(void*), pTxtCharIsPunct);
}
void PipeTxtCharIsValid(void)
{
//	WriteParameter (TxtCharIsValid, sizeof(void*), pTxtCharIsValid);
}

void PipeTxtCharWidth(void)
{
//	WriteParameter (TxtCharWidth, sizeof(void*), pTxtCharWidth);
}
void PipeTxtCharXAttr (void)
{
//	WriteParameter (TxtCharXAttr , sizeof(void*), pTxtCharXAttr );
}
void PipeTxtCompare (void)
{
//	WriteParameter (TxtCompare, sizeof(void*), pTxtCompare);
}
void PipeTxtEncodingName (void)
{
//	WriteParameter (TxtEncodingName, sizeof(void*), pTxtEncodingName);
}
void PipeTxtFindString(void)
{
//	WriteParameter (TxtFindString, sizeof(void*), pTxtFindString);
}
void PipeTxtGetChar(void)
{
//	WriteParameter (TxtGetChar, sizeof(void*), pTxtGetChar);
}
void PipeTxtGetNextChar(void)
{
//	WriteParameter (TxtGetNextChar, sizeof(void*), pTxtGetNextChar);
}
void PipeTxtGetPreviousChar (void)
{
//	WriteParameter (TxtGetPreviousChar, sizeof(void*), pTxtGetPreviousChar);
}
void PipeTxtGetTruncationOffset(void)
{
//	WriteParameter (TxtGetTruncationOffset, sizeof(void*), pTxtGetTruncationOffset);
}
void PipeTxtMaxEncoding(void)
{
//	WriteParameter (TxtMaxEncoding sizeof(void*), pTxtMaxEncoding);
}
void PipeTxtNextCharSize(void)
{
//	WriteParameter (TxtNextCharSize, sizeof(void*), pTxtNextCharSize);
}
void PipeTxtParamString(void)
{
//	WriteParameter (TxtParamString, sizeof(void*), pTxtParamString);
}
void PipeTxtPreviousCharSize (void)
{
//	WriteParameter (TxtPreviousCharSize, sizeof(void*), pTxtPreviousCharSize);
}
void PipeTxtReplaceStr(void)
{
//	WriteParameter (TxtReplaceStr, sizeof(void*), pTxtReplaceStr);
}
void PipeTxtSetNextChar(void)
{
//	WriteParameter (TxtSetNextChar, sizeof(void*), pTxtSetNextChar);
}
void PipeTxtStrEncoding(void)
{
//	WriteParameter (TxtStrEncoding, sizeof(void*), pTxtStrEncoding);
}
void PipeTxtTransliterate (void)
{
//	WriteParameter (TxtTransliterate, sizeof(void*), pTxtTransliterate);
}
void PipeTxtWordBounds (void)
{
//	WriteParameter (TxtWordBounds, sizeof(void*), pTxtWordBounds);
}

