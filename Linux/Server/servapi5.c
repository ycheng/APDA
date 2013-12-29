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
// Graffiti Manager Library, completed 19/19 functions now.
////////////////////////////////////////////////////////////
void PipeGrfAddMacro(void)
{
//	WriteParameter (GrfAddMacro, sizeof(void*), pGrfAddMacro);
}
void PipeGrfAddPoint (void)
{
        WriteParameter (GrfAddPoint, sizeof(void*), pGrfAddPoint);
}
void PipeGrfCleanState (void)
{
	WriteParameter (GrfCleanState, sizeof(void*), pGrfCleanState);
}
void PipeGrfFlushPoints (void)
{
	WriteParameter (GrfFlushPoints, sizeof(void*), pGrfFlushPoints);
}	
void PipeGrfGetNumPoints (void)
{
	WriteParameter (GrfGetNumPoints, sizeof(void*), pGrfGetNumPoints);
}	
void PipeGrfGetPoint (void)
{
	WriteParameter (GrfGetPoint, sizeof(void*), pGrfGetPoint);
}	
void PipeGrfGetState (void)
{
	WriteParameter (GrfGetState, sizeof(void*), pGrfGetState);
}									
void PipeGrfInitState (void)
{
	WriteParameter (GrfInitState, sizeof(void*), pGrfInitState);
}	
void PipeGrfProcessStroke (void)
{
	WriteParameter (GrfProcessStroke, sizeof(void*), pGrfProcessStroke);
}	
void PipeGrfSetState (void)
{
	WriteParameter (GrfSetState, sizeof(void*), pGrfSetState);
}        


void PipeGrfDeleteMacro(void)
{
//	WriteParameter (GrfDeleteMacro, sizeof(void*), pGrfDeleteMacro);
}
void PipeGrfFilterPoints(void)
{
//	WriteParameter (GrfFilterPoints, sizeof(void*), pGrfFilterPoints);
}
void PipeGrfFindBranch(void)
{
//	WriteParameter (GrfFindBranch, sizeof(void*), pGrfFindBranch);
}
void PipeGrfGetAndExpandMacro(void)
{
//	WriteParameter (GrfGetAndExpandMacro, sizeof(void*), pGrfGetAndExpandMacro);
}
void PipeGrfGetGlyphMapping(void)
{
//	WriteParameter (GrfGetGlyphMapping, sizeof(void*), pGrfGetGlyphMapping);
}
void PipeGrfGetMacro(void)
{
//	WriteParameter (GrfGetMacro, sizeof(void*), pGrfGetMacro);
}
void PipeGrfGetMacroName(void)
{
//	WriteParameter (GrfGetMacroName, sizeof(void*), pGrfGetMacroName);
}
void PipeGrfMatch(void)
{
//	WriteParameter (GrfMatch, sizeof(void*), pGrfMatch);
}
void PipeGrfMatchGlyph(void)
{
//	WriteParameter (GrfMatchGlyph, sizeof(void*), pGrfMatchGlyph);
}

//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.
//////////////////////////////////////////////////////////////////
void PipeGsiEnable (void)
{
	WriteParameter (GsiEnable, sizeof(void*), pGsiEnable);

}
void PipeGsiEnabled (void)
{
	WriteParameter (GsiEnabled, sizeof(void*), pGsiEnabled);
}
void PipeGsiInitialize(void)
{
	WriteParameter (GsiInitialize, sizeof(void*), pGsiInitialize);
}
void PipeGsiSetLocation (void)
{
	WriteParameter (GsiSetLocation, sizeof(void*), pGsiSetLocation);
}
void PipeGsiSetShiftState (void)
{
	WriteParameter (GsiSetShiftState, sizeof(void*), pGsiSetShiftState);
}


////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeInsPtEnable (void)
{
	WriteParameter (InsPtEnable, sizeof(void*), pInsPtEnable);

}
void PipeInsPtEnabled (void)
{
	WriteParameter (InsPtEnabled, sizeof(void*), pInsPtEnabled);
}
void PipeInsPtGetHeight (void)
{
	WriteParameter (InsPtGetHeight, sizeof(void*), pInsPtGetHeight);
}
void PipeInsPtGetLocation (void)
{
	WriteParameter (InsPtGetLocation, sizeof(void*), pInsPtGetLocation);
}
void PipeInsPtSetHeight (void)
{
	WriteParameter (InsPtSetHeight, sizeof(void*), pInsPtSetHeight);
}	
void PipeInsPtSetLocation (void)
{
	WriteParameter (InsPtSetLocation, sizeof(void*), pInsPtSetLocation);
}	

////////////////////////////////////////////////////////////
// Key Manager Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeKeyCurrentState (void)
{
//	WriteParameter (KeyCurrentState, sizeof(void*), pKeyCurrentState);
}
void PipeKeyRates (void)
{
//	WriteParameter (KeyRates, sizeof(void*), pKeyRates);
}
void PipeKeySetMask (void)
{
//	WriteParameter (KeySetMask, sizeof(void*), pKeySetMask);
}



////////////////////////////////////////////////////////////
// IR Library, completed 22/22 functions now.
////////////////////////////////////////////////////////////
void PipeIrAdvanceCredit(void)
{
//	WriteParameter (IrAdvanceCredit, sizeof(void*), pIrAdvanceCredit);
}
void PipeIrBind (void)
{
//	WriteParameter (IrBind, sizeof(void*), pIrBind);
}
void PipeIrClose (void)
{
//	WriteParameter (IrClose , sizeof(void*), pIrClose );
}
void PipeIrConnectIrLap (void)
{
//	WriteParameter (IrConnectIrLap , sizeof(void*), pIrConnectIrLap );
}
void PipeIrConnectReq (void)
{
//	WriteParameter (IrConnectReq , sizeof(void*), pIrConnectReq );
}
void PipeIrConnectRsp (void)
{
//	WriteParameter (IrConnectRsp, sizeof(void*), pIrConnectRsp);
}
void PipeIrDataReq (void)
{
//	WriteParameter (IrDataReq, sizeof(void*), pIrDataReq);
}
void PipeIrDisconnectIrLap (void)
{
//	WriteParameter (IrDisconnectIrLap, sizeof(void*), pIrDisconnectIrLap);
}
void PipeIrDiscoverReq (void)
{
//	WriteParameter (IrDiscoverReq , sizeof(void*), pIrDiscoverReq );
}
void PipeIrIsIrLapConnected(void)
{
//	WriteParameter (IrIsIrLapConnected, sizeof(void*), pIrIsIrLapConnected);
}
void PipeIrIsMediaBusy(void)
{
//	WriteParameter (IrIsMediaBusy, sizeof(void*), pIrIsMediaBusy);
}
void PipeIrIsNoProgress (void)
{
//	WriteParameter (IrIsNoProgress, sizeof(void*), pIrIsNoProgress);
}
void PipeIrIsRemoteBusy (void)
{
//	WriteParameter (IrIsRemoteBusy, sizeof(void*), pIrIsRemoteBusy);
}
void PipeIrLocalBusy (void)
{
//	WriteParameter (IrLocalBusy, sizeof(void*), pIrLocalBusy);
}
void PipeIrMaxRxSize (void)
{
//	WriteParameter (IrMaxRxSize, sizeof(void*), pIrMaxRxSize);
}
void PipeIrMaxTxSize (void)
{
//	WriteParameter (IrMaxTxSize, sizeof(void*), pIrMaxTxSize);
}
void PipeIrOpen (void)
{
//	WriteParameter (IrOpen, sizeof(void*), pIrOpen);
}
void PipeIrSetConTypeTTP(void)
{
//	WriteParameter (IrSetConTypeTTP, sizeof(void*), pIrSetConTypeTTP);
}
void PipeIrSetConTypeLMP(void)
{
//	WriteParameter (IrSetConTypeLMP, sizeof(void*), pIrSetConTypeLMP);
}
void PipeIrSetDeviceInfo(void)
{
//	WriteParameter (IrSetDeviceInfo, sizeof(void*), pIrSetDeviceInfo);
}
void PipeIrTestReq (void)
{
//	WriteParameter (IrTestReq , sizeof(void*), pIrTestReq );
}
void PipeIrUnbind (void)
{
//	WriteParameter (IrUnbind, sizeof(void*), pIrUnbind);
}



////////////////////////////////////////////////////////////
// IAS Library, completed 14/14 functions now.
////////////////////////////////////////////////////////////
void PipeIrIAS_Add(void)
{
//	WriteParameter (IrIAS_Add, sizeof(void*), pIrIAS_Add);
}
void PipeIrIAS_GetInteger (void)
{
//	WriteParameter (IrIAS_GetInteger, sizeof(void*), pIrIAS_GetInteger);
}
void PipeIrIAS_GetIntLsap (void)
{
//	WriteParameter (IrIAS_GetIntLsap, sizeof(void*), pIrIAS_GetIntLsap);
}
void PipeIrIAS_GetObjectID(void)
{
//	WriteParameter (IrIAS_GetObjectID, sizeof(void*), pIrIAS_GetObjectID);
}
void PipeIrIAS_GetOctetString(void)
{
//	WriteParameter (IrIAS_GetOctetString, sizeof(void*), pIrIAS_GetOctetString);
}
void PipeIrIAS_GetOctetStringLen (void)
{
//	WriteParameter (IrIAS_GetOctetStringLen, sizeof(void*), pIrIAS_GetOctetStringLen);
}
void PipeIrIAS_GetType(void)
{
//	WriteParameter (IrIAS_GetType, sizeof(void*), pIrIAS_GetType);
}
void PipeIrIAS_GetUserString (void)
{
//	WriteParameter (IrIAS_GetUserString , sizeof(void*), pIrIAS_GetUserString );
}
void PipeIrIAS_GetUserStringCharSet (void)
{
//	WriteParameter (IrIAS_GetUserStringCharSet, sizeof(void*), pIrIAS_GetUserStringCharSet);
}
void PipeIrIAS_GetUserStringLen (void)
{
//	WriteParameter (IrIAS_GetUserStringLen, sizeof(void*), pIrIAS_GetUserStringLen);
}
void PipeIrIAS_Next (void)
{
//	WriteParameter (IrIAS_Next, sizeof(void*), pIrIAS_Next);
}
void PipeIrIAS_Query(void)
{
//	WriteParameter (IrIAS_Query, sizeof(void*), pIrIAS_Query);
}
void PipeIrIAS_SetDeviceName(void)
{
//	WriteParameter (IrIAS_SetDeviceName, sizeof(void*), pIrIAS_SetDeviceName);
}
void PipeIrIAS_StartResult(void)
{
//	WriteParameter (IrIAS_StartResult, sizeof(void*), pIrIAS_StartResult);
}



////////////////////////////////////////////////////////////
// List Handle Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
void PipeLstDrawList (void)
{
	WriteParameter (LstDrawList, sizeof(void*), pLstDrawList);
}
void PipeLstEraseList (void)
{
	WriteParameter (LstEraseList, sizeof(void*), pLstEraseList);

}
void PipeLstGetNumberOfItems (void)
{
	WriteParameter (LstGetNumberOfItems, sizeof(void*), pLstGetNumberOfItems);
}	
void PipeLstGetSelection (void)
{
	WriteParameter (LstGetSelection, sizeof(void*), pLstGetSelection);
}	
void PipeLstGetSelectionText (void)
{
	WriteParameter (LstGetSelectionText, sizeof(void*), pLstGetSelectionText);
}	
void PipeLstGetVisibleItems (void)
{
	WriteParameter (LstGetVisibleItems, sizeof(void*), pLstGetVisibleItems);
}	

void PipeLstHandleEvent (void)
{
//	WriteParameter (LstHandleEvent, sizeof(void*), pLstHandleEvent);
}
	
void PipeLstMakeItemVisible (void)
{
	WriteParameter (LstMakeItemVisible, sizeof(void*), pLstMakeItemVisible);
}	
void PipeLstNewList(void)
{
	WriteParameter (LstNewList, sizeof(void*), pLstNewList);
}							
void PipeLstPopupList(void)
{
	WriteParameter (LstPopupList, sizeof(void*), pLstPopupList);
}	
void PipeLstScrollList (void)
{
	WriteParameter (LstScrollList, sizeof(void*), pLstScrollList);
}									
void PipeLstSetDrawFunction (void)
{
	WriteParameter (LstSetDrawFunction, sizeof(void*), pLstSetDrawFunction);
}	
void PipeLstSetHeight (void)
{
	WriteParameter (LstSetHeight, sizeof(void*), pLstSetHeight);
}	
void PipeLstSetListChoices (void)
{
	WriteParameter (LstSetListChoices, sizeof(void*), pLstSetListChoices);
}	
void PipeLstSetPosition (void)
{
	WriteParameter (LstSetPosition, sizeof(void*), pLstSetPosition);
}	
void PipeLstSetSelection (void)
{
	WriteParameter (LstSetSelection, sizeof(void*), pLstSetSelection);
}	
void PipeLstSetTopItem (void)
{
	WriteParameter (LstSetTopItem, sizeof(void*), pLstSetTopItem);
	
}


