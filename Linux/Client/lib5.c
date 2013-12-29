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
// Graffiti Manager Library, completed 19/19 functions now.
////////////////////////////////////////////////////////////
#ifdef L_GrfAddPoint
Err GrfAddPoint (PointType *pt)
{
	Err (*GrfAddPointP) (PointType *pt);

	GetParameter (&GrfAddPointP , sizeof(void *), pGrfAddPoint );
	return (*GrfAddPointP) (pt);
}
#endif

#ifdef L_GrfCleanState
Err GrfCleanState (void)
{
	Err (*GrfCleanStateP) (void);

	GetParameter (&GrfCleanStateP , sizeof(void *), pGrfCleanState );
	return(*GrfCleanStateP) ();
}
#endif

#ifdef L_GrfFlushPoints
Err GrfFlushPoints (void)
{
	Err (*GrfFlushPointsP) (void);

	GetParameter (&GrfFlushPointsP , sizeof(void *), pGrfFlushPoints );
	return(*GrfFlushPointsP) ();
}
#endif

#ifdef L_GrfGetNumPoints
Err GrfGetNumPoints (UInt16 *numPtsP)
{
	Err (*GrfGetNumPointsP) (UInt16 *numPtsP);

	GetParameter (&GrfGetNumPointsP , sizeof(void *), pGrfGetNumPoints );
	return(*GrfGetNumPointsP) (numPtsP);
}
#endif

#ifdef L_GrfGetPoint
Err GrfGetPoint (UInt16 index, PointType *pointP)
{
	Err (*GrfGetPointP) (UInt16 index, PointType *pointP);

	GetParameter (&GrfGetPointP , sizeof(void *), pGrfGetPoint );
	return(*GrfGetPointP) ( index, pointP);
}
#endif

#ifdef L_GrfGetState
Err GrfGetState (Boolean *capsLockP, Boolean *numLockP, 
                                                                UInt16 *tempShiftP, Boolean *autoShiftedP)
{
	Err (*GrfGetStateP) (Boolean *capsLockP, Boolean *numLockP, 
                                                                UInt16 *tempShiftP, Boolean *autoShiftedP);

	GetParameter (&GrfGetStateP , sizeof(void *), pGrfGetState );
	return(*GrfGetStateP) (capsLockP, numLockP, tempShiftP, autoShiftedP);
}
#endif

#ifdef L_GrfInitState
Err GrfInitState (void)
{
	Err (*GrfInitStateP) (void);

	GetParameter (&GrfInitStateP , sizeof(void *), pGrfInitState );
	return(*GrfInitStateP) ();
}
#endif

#ifdef L_GrfProcessStroke
Err GrfProcessStroke (PointType *startPtP, PointType *endPtP, Boolean upShift)
{
	Err (*GrfProcessStrokeP) (PointType *startPtP, PointType *endPtP, Boolean upShift);

	GetParameter (&GrfProcessStrokeP , sizeof(void *), pGrfProcessStroke );
	return(*GrfProcessStrokeP) (startPtP, endPtP,  upShift);
}
#endif

#ifdef L_GrfSetState
Err GrfSetState (Boolean capsLock, Boolean numLock, Boolean upperShift)
{
	Err (*GrfSetStateP) (Boolean capsLock, Boolean numLock, Boolean upperShift);

	GetParameter (&GrfSetStateP , sizeof(void *), pGrfSetState );
	return (*GrfSetStateP) ( capsLock,  numLock,  upperShift);
}
#endif
/*
#ifdef L_GrfMatch
Err 	GrfMatch (UInt16 *flagsP, void *dataPtrP, UInt16 *dataLenP,	UInt16 *uncertainLenP, GrfMatchInfoPtr matchInfoP)
{
	Err 	(*GrfMatchP)(UInt16 *flagsP, void *dataPtrP, UInt16 *dataLenP,	UInt16 *uncertainLenP, GrfMatchInfoPtr matchInfoP);

	GetParameter (&GrfMatchP , sizeof(void *), pGrfMatch );
	return (*GrfMatchP)(flagsP, dataPtrP, dataLenP,	uncertainLenP,  matchInfoP);
}
#endif
*/
#ifdef L_GrfGetMacro
Err 	GrfGetMacro(Char *nameP, UInt8 *macroDataP,UInt16 *dataLenP)
{
	Err 	(*GrfGetMacroP)(Char *nameP, UInt8 *macroDataP,UInt16 *dataLenP);

	GetParameter (&GrfGetMacroP , sizeof(void *), pGrfGetMacro );
	return 	(*GrfGetMacroP)(nameP, macroDataP,dataLenP);
}
#endif
				
#ifdef L_GrfGetAndExpandMacro
Err 	GrfGetAndExpandMacro(Char *nameP, UInt8 *macroDataP,	UInt16 *dataLenP)
{
	Err 	(*GrfGetAndExpandMacroP)(Char *nameP, UInt8 *macroDataP,	UInt16 *dataLenP);

	GetParameter (&GrfGetAndExpandMacroP , sizeof(void *), pGrfGetAndExpandMacro );
	return (*GrfGetAndExpandMacroP)(nameP, macroDataP,dataLenP);
}
#endif
				

#ifdef L_GrfFilterPoints
Err 	GrfFilterPoints (void)
{
	Err 	(*GrfFilterPointsP) (void);

	GetParameter (&GrfFilterPointsP , sizeof(void *), pGrfFilterPoints );
	return  (*GrfFilterPointsP) ();
}
#endif
				


#ifdef L_GrfFindBranch
Err 	GrfFindBranch(UInt16 flags)
{
	Err 	(*GrfFindBranchP)(UInt16 flags);

	GetParameter (&GrfFindBranchP , sizeof(void *), pGrfFindBranch );
	return (*GrfFindBranchP)(flags);
}
#endif
/*
#ifdef L_GrfMatchGlyph
Err 	GrfMatchGlyph (GrfMatchInfoPtr matchInfoP,Int16 maxUnCertainty, UInt16 maxMatches)
{
	Err 	(*GrfMatchGlyphP) (GrfMatchInfoPtr matchInfoP,Int16 maxUnCertainty, UInt16 maxMatches);

	GetParameter (&GrfMatchGlyphP , sizeof(void *), pGrfMatchGlyph );
	return (*GrfMatchGlyphP) ( matchInfoP, maxUnCertainty,  maxMatches);
}
#endif
*/
#ifdef L_GrfGetGlyphMapping
Err 	GrfGetGlyphMapping (UInt16 glyphID, UInt16 *flagsP,void *dataPtrP, UInt16 *dataLenP, UInt16 *uncertainLenP)
{
	Err 	(*GrfGetGlyphMappingP) (UInt16 glyphID, UInt16 *flagsP,void *dataPtrP, UInt16 *dataLenP, UInt16 *uncertainLenP);

	GetParameter (&GrfGetGlyphMappingP , sizeof(void *), pGrfGetGlyphMapping );
	return (*GrfGetGlyphMappingP) ( glyphID, flagsP,dataPtrP, dataLenP, uncertainLenP);
}
#endif
				
#ifdef L_GrfGetMacroName				
Err 	GrfGetMacroName(UInt16 index, Char *nameP)
{
	Err 	(*GrfGetMacroNameP)(UInt16 index, Char *nameP);

	GetParameter (&GrfGetMacroNameP , sizeof(void *), pGrfGetMacroName );
	return (*GrfGetMacroNameP)( index, nameP);
}
#endif
			
#ifdef L_GrfDeleteMacro
Err 	GrfDeleteMacro(UInt16 index)
{
	Err 	(*GrfDeleteMacroP)(UInt16 index);

	GetParameter (&GrfDeleteMacroP , sizeof(void *), pGrfDeleteMacro );
	return  (*GrfDeleteMacroP)(index);
}
#endif
				
#ifdef L_GrfAddMacro
Err 	GrfAddMacro(Char *nameP, UInt8 *macroDataP,UInt16 dataLen)
{
	Err 	(*GrfAddMacroP)(Char *nameP, UInt8 *macroDataP,UInt16 dataLen);

	GetParameter (&GrfAddMacroP , sizeof(void *), pGrfAddMacro );
	return (*GrfAddMacroP)(nameP, macroDataP, dataLen);
}
#endif
				


//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.
//////////////////////////////////////////////////////////////////
#ifdef L_GsiEnable
void GsiEnable (const Boolean enableIt)
{
	void (*GsiEnableP) (const Boolean enableIt);

	GetParameter (&GsiEnableP , sizeof(void *), pGsiEnable );
	(*GsiEnableP) ( enableIt);
}
#endif

#ifdef L_GsiEnabled
Boolean GsiEnabled (void)
{
	Boolean (*GsiEnabledP) (void);

	GetParameter (&GsiEnabledP , sizeof(void *), pGsiEnabled );
	return (*GsiEnabledP) ();
}
#endif

#ifdef L_GsiInitialize
void GsiInitialize (void)
{
	void (*GsiInitializeP) (void);

	GetParameter (&GsiInitializeP , sizeof(void *), pGsiInitialize );
	(*GsiInitializeP) ();
}
#endif

#ifdef L_GsiSetLocation
void GsiSetLocation (const Int16 x, const Int16 y)
{
	void (*GsiSetLocationP) (const Int16 x, const Int16 y);

	GetParameter (&GsiSetLocationP , sizeof(void *), pGsiSetLocation);
	(*GsiSetLocationP) ( x, y);
}
#endif

#ifdef L_GsiSetShiftState
void GsiSetShiftState (const UInt16 lockFlags, const UInt16 tempShift)
{
	void (*GsiSetShiftStateP) (const UInt16 lockFlags, const UInt16 tempShift);

	GetParameter (&GsiSetShiftStateP , sizeof(void *), pGsiSetShiftState );
	(*GsiSetShiftStateP) ( lockFlags,  tempShift);
}
#endif




////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
#ifdef L_InsPtEnable
void InsPtEnable (Boolean enableIt)
{
	void (*InsPtEnableP) (Boolean enableIt);

	GetParameter (&InsPtEnableP , sizeof(void *), pInsPtEnable );
	(*InsPtEnableP) (enableIt);
}
        
#endif

#ifdef L_InsPtEnabled     
Boolean InsPtEnabled (void)
{
	Boolean (*InsPtEnabledP) (void);

	GetParameter (&InsPtEnabledP , sizeof(void *), pInsPtEnabled );
	return(*InsPtEnabledP) ();
}
#endif

#ifdef L_InsPtGetHeight
Int16 InsPtGetHeight (void)
{
	Int16 (*InsPtGetHeightP) (void);

	GetParameter (&InsPtGetHeightP , sizeof(void *), pInsPtGetHeight );
	return(*InsPtGetHeightP) ();
}
#endif

#ifdef L_InsPtGetLocation
void InsPtGetLocation (Int16 *x, Int16 *y)
{
	void (*InsPtGetLocationP) (Int16 *x, Int16 *y);

	GetParameter (&InsPtGetLocationP , sizeof(void *), pInsPtGetLocation );
	(*InsPtGetLocationP) (x, y);
}
#endif

#ifdef L_InsPtSetHeight      
void InsPtSetHeight (const Int16 height)
{
	void (*InsPtSetHeightP) (const Int16 height);

	GetParameter (&InsPtSetHeightP , sizeof(void *), pInsPtSetHeight );
	(*InsPtSetHeightP) (height);
}
#endif

#ifdef L_InsPtSetLocation
void InsPtSetLocation (const Int16 x, const Int16 y)
{
	void (*InsPtSetLocationP) (const Int16 x, const Int16 y);

	GetParameter (&InsPtSetLocationP , sizeof(void *), pInsPtSetLocation );
	(*InsPtSetLocationP) ( x, y);
}
#endif

////////////////////////////////////////////////////////////
// Key Manager Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
#ifdef L_KeyRates
Err 	KeyRates(Boolean set, UInt16 *initDelayP, UInt16 *periodP, 
						UInt16 *doubleTapDelayP, Boolean *queueAheadP)
{
	Err 	(*KeyRatesP)(Boolean set, UInt16 *initDelayP, UInt16 *periodP, 
						UInt16 *doubleTapDelayP, Boolean *queueAheadP);

	GetParameter (&KeyRatesP , sizeof(void *), pKeyRates );
	return  (*KeyRatesP)( set, initDelayP, periodP, doubleTapDelayP, queueAheadP);
}
#endif

#ifdef L_KeyCurrentState							
UInt32	KeyCurrentState(void)
{
	
	UInt32	(*KeyCurrentStateP)(void);

	GetParameter (&KeyCurrentStateP , sizeof(void *), pKeyCurrentState );
	return   (*KeyCurrentStateP)();
}
#endif
							
#ifdef L_KeySetMask							
UInt32	KeySetMask(UInt32 keyMask)
{
	
	UInt32	(*KeySetMaskP)(UInt32 keyMask);

	GetParameter (&KeySetMaskP , sizeof(void *), pKeySetMask );
	return  (*KeySetMaskP)(keyMask);
}
#endif


////////////////////////////////////////////////////////////
// IR Library, completed 22/22 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_IrAdvanceCredit
void IrAdvanceCredit (IrConnect* con,UInt8 credit)
{
	void (*IrAdvanceCreditP) (IrConnect* con,UInt8 credit);

	GetParameter (&IrAdvanceCreditP , sizeof(void *), pIrAdvanceCredit );
	 (*IrAdvanceCreditP) ( con, credit);
}
#endif

#ifdef L_IrBind
IrStatus IrBind (UInt16 refNum, IrConnect* con,IrCallBack callBack)
{
	IrStatus (*IrBindP) (UInt16 refNum, IrConnect* con,IrCallBack callBack);

	GetParameter (&IrBindP , sizeof(void *), pIrBind );
	return	(*IrBindP) ( refNum, con, callBack);

}
#endif
*/
#ifdef L_IrClose
Err IrClose (UInt16 refnum)
{
	Err (*IrCloseP) (UInt16 refnum);

	GetParameter (&IrCloseP , sizeof(void *), pIrClose );
	return  (*IrCloseP) (refnum);
}
#endif
/*
#ifdef L_IrConnectIrLap
IrStatus IrConnectIrLap (UInt16 refNum,IrDeviceAddr deviceAddr)
{
	IrStatus (*IrConnectIrLapP) (UInt16 refNum,IrDeviceAddr deviceAddr);

	GetParameter (&IrConnectIrLapP , sizeof(void *), pIrConnectIrLap );
	return  (*IrConnectIrLapP) (refNum,deviceAddr);
}
#endif

#ifdef L_IrConnectReq
IrStatus IrConnectReq (UInt16 refNum,IrConnect* con, IrPacket* packet, UInt8 credit)
{
	IrStatus (*IrConnectReqP) (UInt16 refNum,IrConnect* con, IrPacket* packet, UInt8 credit);

	GetParameter (&IrConnectReqP , sizeof(void *), pIrConnectReq );
	return  (*IrConnectReqP) ( refNum, con,  packet,  credit);
}
#endif

#ifdef L_IrConnectRsp
IrStatus IrConnectRsp (UInt16 refNum,IrConnect* con, IrPacket* packet, UInt8 credit)
{
	IrStatus (*IrConnectRspP) (UInt16 refNum,IrConnect* con, IrPacket* packet, UInt8 credit);

	GetParameter (&IrConnectRspP , sizeof(void *), pIrConnectRsp );
	return  (*IrConnectRspP) ( refNum, con,  packet,  credit);
}
#endif

#ifdef L_IrDataReq
IrStatus IrDataReq (UInt16 refNum, IrConnect* con,IrPacket* packet)
{
	IrStatus (*IrDataReqP) (UInt16 refNum, IrConnect* con,IrPacket* packet);

	GetParameter (&IrDataReqP , sizeof(void *), pIrDataReq );
	return  (*IrDataReqP) ( refNum,  con, packet);
}
#endif

#ifdef L_IrDisconnectIrLap
IrStatus IrDisconnectIrLap (UInt16 refNum)
{
	IrStatus (*IrDisconnectIrLapP) (UInt16 refNum);

	GetParameter (&IrDisconnectIrLapP , sizeof(void *), pIrDisconnectIrLap );
	return  (*IrDisconnectIrLapP) (refNum);
}
#endif

#ifdef L_IrDiscoverReq
IrStatus IrDiscoverReq (UInt16 refNum,IrConnect* con)
{
	IrStatus (*IrDiscoverReqP) (UInt16 refNum,IrConnect* con);

	GetParameter (&IrDiscoverReqP , sizeof(void *), pIrDiscoverReq );
	return  (*IrDiscoverReqP) ( refNum,con);
}
#endif
*/
/*
#ifdef L_IrIsIrLapConnected
BOOL IrIsIrLapConnected (UInt16 refNum)
{
	BOOL (*IrIsIrLapConnectedP) (UInt16 refNum);

	GetParameter (&IrIsIrLapConnectedP , sizeof(void *), pIrIsIrLapConnected );
	return  (*IrIsIrLapConnectedP) (refNum);
}
#endif

#ifdef L_IrIsMediaBusy
BOOL IrIsMediaBusy (UInt16 refNum)
{
	BOOL (*IrIsMediaBusyP) (UInt16 refNum);

	GetParameter (&IrIsMediaBusyP , sizeof(void *), pIrIsMediaBusy );
	return  (*IrIsMediaBusyP) (refNum);
}
#endif

#ifdef L_IrIsNoProgress
BOOL IrIsNoProgress (UInt16 refNum)
{
	BOOL (*IrIsNoProgressP) (UInt16 refNum);

	GetParameter (&IrIsNoProgressP , sizeof(void *), pIrIsNoProgress );
	return  (*IrIsNoProgressP) (refNum);
}
#endif

#ifdef L_IrIsRemoteBusy
BOOL IrIsRemoteBusy (UInt16 refNum)
{
	BOOL (*IrIsRemoteBusyP) (UInt16 refNum);

	GetParameter (&IrIsRemoteBusyP , sizeof(void *), pIrIsRemoteBusy );
	return  (*IrIsRemoteBusyP) (refNum);
}
#endif

#ifdef L_IrLocalBusy
void IrLocalBusy (UInt16 refNum, BOOL flag)
{
	void (*IrLocalBusyP) (UInt16 refNum, BOOL flag);

	GetParameter (&IrLocalBusyP , sizeof(void *), pIrLocalBusy );
	(*IrLocalBusyP) ( refNum,  flag);
}
#endif
*/
/*
#ifdef L_IrMaxRxSize
UInt16 IrMaxRxSize (UInt16 refNum, IrConnect* con)
{
	UInt16 (*IrMaxRxSizeP) (UInt16 refNum, IrConnect* con);

	GetParameter (&IrMaxRxSizeP , sizeof(void *), pIrMaxRxSize );
	return  (*IrMaxRxSizeP) ( refNum,  con);
}
#endif

#ifdef L_IrMaxTxSize
UInt16 IrMaxTxSize (UInt16 refNum, IrConnect* con)
{
	UInt16 (*IrMaxTxSizeP) (UInt16 refNum, IrConnect* con);

	GetParameter (&IrMaxTxSizeP , sizeof(void *), pIrMaxTxSize );
	return  (*IrMaxTxSizeP) ( refNum,  con);

}
#endif
*/
#ifdef L_IrOpen
Err IrOpen (UInt16 refnum, UInt32 options)
{
	Err (*IrOpenP) (UInt16 refnum, UInt32 options);

	GetParameter (&IrOpenP , sizeof(void *), pIrOpen );
	return  (*IrOpenP) ( refnum,  options);
}
#endif
/*
#ifdef L_IrSetConTypeLMP
void IrSetConTypeLMP (IrConnect* con)
{
	void (*IrSetConTypeLMPP) (IrConnect* con);

	GetParameter (&IrSetConTypeLMPP , sizeof(void *), pIrSetConTypeLMP );
	  (*IrSetConTypeLMPP) ( con);
}
#endif

#ifdef L_IrSetConTypeTTP
void IrSetConTypeTTP (IrConnect* con)
{
	void (*IrSetConTypeTTPP) (IrConnect* con);

	GetParameter (&IrSetConTypeTTPP , sizeof(void *), pIrSetConTypeTTP );
	(*IrSetConTypeTTPP) ( con);
}
#endif
*/
/*
#ifdef L_IrSetDeviceInfo
IrStatus IrSetDeviceInfo (UInt16 refNum,UInt8 *info, UInt8 len)
{
	IrStatus (*IrSetDeviceInfoP) (UInt16 refNum,UInt8 *info, UInt8 len);

	GetParameter (&IrSetDeviceInfoP , sizeof(void *), pIrSetDeviceInfo );
	return  (*IrSetDeviceInfoP) ( refNum,info,  len);
}
#endif
*/
/*
#ifdef L_IrTestReq
IrStatus IrTestReq (UInt16 refNum,IrDeviceAddr devAddr, IrConnect* con,IrPacket* packet)
{
	IrStatus (*IrTestReqP) (UInt16 refNum,IrDeviceAddr devAddr, IrConnect* con,IrPacket* packet);

	GetParameter (&IrTestReqP , sizeof(void *), pIrTestReq );
	return   (*IrTestReqP) ( refNum, devAddr,  con, packet);
}
#endif

#ifdef L_IrUnbind
IrStatus IrUnbind (UInt16 refNum, IrConnect* con)
{
	IrStatus (*IrUnbindP) (UInt16 refNum, IrConnect* con);

	GetParameter (&IrUnbindP , sizeof(void *), pIrUnbind );
	return  (*IrUnbindP) ( refNum,  con);
}
#endif

*/
////////////////////////////////////////////////////////////
// IAS Library, completed 14/14 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_IrIAS_Add
IrStatus IrIAS_Add (UInt16 refNum,IrIasObject* obj)
{
	IrStatus  (*IrIAS_AddP) (UInt16 refNum,IrIasObject* obj);

	GetParameter (&IrIAS_AddP , sizeof(void *), pIrIAS_Add );
	return  (*IrIAS_AddP) ( refNum, obj);
}
#endif

#ifdef L_IrIAS_GetInteger
UInt32  IrIAS_GetInteger (IrIasQuery* t)
{
	UInt32  (*IrIAS_GetIntegerP) (IrIasQuery* t);

	GetParameter (&IrIAS_GetIntegerP , sizeof(void *), pIrIAS_GetInteger );
	return   (*IrIAS_GetIntegerP) (t);
}
#endif

#ifdef L_IrIAS_GetIntLsap
UInt8   IrIAS_GetIntLsap (IrIasQuery* t)
{
	UInt8   (*IrIAS_GetIntLsapP) (IrIasQuery* t);

	GetParameter (&IrIAS_GetIntLsapP , sizeof(void *), pIrIAS_GetIntLsap );
	return  (*IrIAS_GetIntLsapP) ( t);
}
#endif

#ifdef L_IrIAS_GetObjectID
UInt16  IrIAS_GetObjectID (IrIasQuery* t)
{
	UInt16  (*IrIAS_GetObjectIDP) (IrIasQuery* t);

	GetParameter (&IrIAS_GetObjectIDP , sizeof(void *), pIrIAS_GetObjectID );
	return   (*IrIAS_GetObjectIDP) (t);
}
#endif

#ifdef L_IrIAS_GetOctetString
UInt8*   IrIAS_GetOctetString (IrIasQuery* t)
{
	UInt8*   (*IrIAS_GetOctetStringP) (IrIasQuery* t);

	GetParameter (&IrIAS_GetOctetStringP , sizeof(void *), pIrIAS_GetOctetString );
	return  (*IrIAS_GetOctetStringP) (t);
}
#endif

#ifdef L_GetOctetStringLen
UInt16   GetOctetStringLen (IrIasQuery* t)
{
	UInt16   (*GetOctetStringLenP) (IrIasQuery* t);

	GetParameter (&GetOctetStringLenP , sizeof(void *), pGetOctetStringLen );
	return  (*GetOctetStringLenP) ( t);
}
#endif

#ifdef L_IrIAS_GetType
UInt8     IrIAS_GetType (IrIasQuery*  t)
{
	UInt8    (*IrIAS_GetTypeP)  (IrIasQuery*  t);

	GetParameter (&IrIAS_GetTypeP , sizeof(void *), pIrIAS_GetType );
	return  (*IrIAS_GetTypeP)  (  t);
}
#endif

#ifdef L_IrIAS_GetUserString
UInt8*     IrIAS_GetUserString(IrIasQuery* t)
{
	UInt8*     (*IrIAS_GetUserStringP)(IrIasQuery* t);

	GetParameter (&IrIAS_GetUserStringP , sizeof(void *), pIrIAS_GetUserString );
	return   (*IrIAS_GetUserStringP)( t);
}
#endif

#ifdef L_IrIAS_GetUserStringCharSet
IrCharSet  IrIAS_GetUserStringCharSet(IrIasQuery* t)
{
	IrCharSet  (*IrIAS_GetUserStringCharSetP)(IrIasQuery* t);

	GetParameter (&IrIAS_GetUserStringCharSetP , sizeof(void *), pIrIAS_GetUserStringCharSet );
	return  (*IrIAS_GetUserStringCharSetP)(t);
}
#endif

#ifdef L_IrIAS_GetUserStringLen
UInt8     IrIAS_GetUserStringLen (IrIasQuery* t)
{
	UInt8     (*IrIAS_GetUserStringLenP) (IrIasQuery* t);

	GetParameter (&IrIAS_GetUserStringLenP , sizeof(void *), pIrIAS_GetUserStringLen );
	return  (*IrIAS_GetUserStringLenP) (t);

}
#endif



#ifdef L_IrIAS_Next
UInt8* IrIAS_Next (UInt16 refNum,IrIasQuery* token)
{
	UInt8* (*IrIAS_NextP) (UInt16 refNum,IrIasQuery* token);

	GetParameter (&IrIAS_NextP , sizeof(void *), pIrIAS_Next );
	return (*IrIAS_NextP) ( refNum,token);

}
#endif

#ifdef L_IrIAS_Query
IrStatus IrIAS_Query (UInt16 refNum,IrIasQuery* token)
{
	IrStatus (*IrIAS_QueryP) (UInt16 refNum,IrIasQuery* token);

	GetParameter (&KeySetMaskP , sizeof(void *), pKeySetMask );
	return  (*IrIAS_QueryP) ( refNum, token);
}
#endif

#ifdef L_IrIAS_SetDeviceName
IrStatus IrIAS_SetDeviceName (UInt16 refNum,UInt8 *name, UInt8 len)
{
	IrStatus (*IrIAS_SetDeviceNameP) (UInt16 refNum,UInt8 *name, UInt8 len);

	GetParameter (&IrIAS_SetDeviceNameP , sizeof(void *), pIrIAS_SetDeviceName );
	return  (*IrIAS_SetDeviceNameP) ( refNum,name,  len);
}
#endif

#ifdef L_
void  IrIAS_StartResult(IrIasQuery* t)
{
	void  (*IrIAS_StartResultP)(IrIasQuery* t);

	GetParameter (&IrIAS_StartResultP , sizeof(void *), pIrIAS_StartResult );
	return  (*IrIAS_StartResultP)(t);
}
#endif
*/

////////////////////////////////////////////////////////////
// List Handle Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
#ifdef L_LstDrawList
void LstDrawList (ListType *listP)
{
	void (*LstDrawListP) (ListType *listP);

	GetParameter (&LstDrawListP , sizeof(void *), pLstDrawList );
	(*LstDrawListP) (listP);
}
#endif

#ifdef L_LstEraseList
void LstEraseList (ListType *listP)
{
	void (*LstEraseListP) (ListType *listP);

	GetParameter (&LstEraseListP , sizeof(void *), pLstEraseList );
	(*LstEraseListP) (listP);
}
#endif

#ifdef L_LstGetNumberOfItems
Int16 LstGetNumberOfItems (const ListType *listP)
{
	Int16 (*LstGetNumberOfItemsP) (const ListType *listP);

	GetParameter (&LstGetNumberOfItemsP , sizeof(void *), pLstGetNumberOfItems );
	return(*LstGetNumberOfItemsP) (listP);
}
#endif

#ifdef L_LstGetSelection
Int16 LstGetSelection (ListType *listP)
{
	Int16 (*LstGetSelectionP) (ListType *listP);

	GetParameter (&LstGetSelectionP , sizeof(void *), pLstGetSelection );
	return(*LstGetSelectionP) (listP);
}
#endif

#ifdef L_LstGetSelectionText
Char *LstGetSelectionText (const ListType *listP, Int16 itemNum)
{ 
	Char *(*LstGetSelectionTextP) (const ListType *listP, Int16 itemNum);

	GetParameter (&LstGetSelectionTextP , sizeof(void *), pLstGetSelectionText );
	return(*LstGetSelectionTextP) (listP,  itemNum);
}
#endif

#ifdef L_LstGetVisibleItems
Int16 LstGetVisibleItems (const ListType *listP)
{
	Int16 (*LstGetVisibleItemsP) (const ListType *listP);

	GetParameter (&LstGetVisibleItemsP , sizeof(void *), pLstGetVisibleItems );
	return(*LstGetVisibleItemsP) (listP);
}
#endif

#ifdef L_LstHandleEvent
Boolean LstHandleEvent (ListType *listP, const EventType *eventP)
{
	Boolean (*LstHandleEventP) (ListType *listP, const EventType *eventP);

	GetParameter (&LstHandleEventP , sizeof(void *), pLstHandleEvent );
	return(*LstHandleEventP) (listP, eventP);
}
#endif

#ifdef L_LstMakeItemVisible
void LstMakeItemVisible (ListType *listP, Int16 itemNum)
{
	void (*LstMakeItemVisibleP) (ListType *listP, Int16 itemNum);

	GetParameter (&LstMakeItemVisibleP , sizeof(void *), pLstMakeItemVisible );
	(*LstMakeItemVisibleP) (listP,  itemNum);
}
#endif

#ifdef L_LstNewList
Err LstNewList (void **formPP, UInt16 id, Coord x, Coord y,
					Coord width, Coord height, FontID font,
					Int16 visibleItems, Int16 triggerID)
{
	Err (*LstNewListP) (void **formPP, UInt16 id, Coord x, Coord y,
					Coord width, Coord height, FontID font,
					Int16 visibleItems, Int16 triggerID);

	GetParameter (&LstNewListP , sizeof(void *), pLstNewList );
	return (*LstNewListP) (formPP,  id,  x,  y,
					 width,  height,  font,
					 visibleItems,  triggerID);
}
#endif

#ifdef L_LstPopupList                                               
Int16 LstPopupList (ListType *listP)
{
	Int16 (*LstPopupListP) (ListType *listP);
 
	GetParameter (&LstPopupListP , sizeof(void *), pLstPopupList );
	return(*LstPopupListP) (listP);
}
#endif

#ifdef L_LstScrollList
Boolean LstScrollList (ListType *listp, WinDrectionType direction,
                                                                Int16 itemCount)
{
	Boolean (*LstScrollListP) (ListType *listp, WinDrectionType direction,
                                                                Int16 itemCount);

	GetParameter (&LstScrollListP , sizeof(void *), pLstScrollList );
	return(*LstScrollListP) (listp,  direction,    itemCount);
}      
#endif

#ifdef L_LstSetDrawFunction                                                         
void LstSetDrawFunction (ListType *listP, ListDrawDataFuncPtr func)
{
	void (*LstSetDrawFunctionP) (ListType *listP, ListDrawDataFuncPtr func);

	GetParameter (&LstSetDrawFunctionP , sizeof(void *), pLstSetDrawFunction );
	(*LstSetDrawFunctionP) (listP,  func);
}          
#endif

#ifdef L_LstSetHeight            
void LstSetHeight (ListType *listP, Int16 visibleItems)
{
	void (*LstSetHeightP) (ListType *listP, Int16 visibleItems);

	GetParameter (&LstSetHeightP , sizeof(void *), pLstSetHeight );
	(*LstSetHeightP) (listP,  visibleItems);
}                    
#endif

#ifdef L_LstSetListChoices  
void LstSetListChoices (ListType *listP, Char **itemsText, UInt16 numItems)
{
	void (*LstSetListChoicesP) (ListType *listP, Char **itemsText, UInt16 numItems);

	GetParameter (&LstSetListChoicesP , sizeof(void *), pLstSetListChoices );
	(*LstSetListChoicesP) (listP, itemsText,  numItems);
}               
#endif

#ifdef L_LstSetPosition       
void LstSetPosition (ListType *listP, Coord x, Coord y)
{
	void (*LstSetPositionP) (ListType *listP, Coord x, Coord y);

	GetParameter (&LstSetPositionP , sizeof(void *), pLstSetPosition );
	(*LstSetPositionP) (listP,  x,  y);
}                     
#endif

#ifdef L_LstSetSelection  
void LstSetSelection (ListType *listP, Int16 itemNum)
{
	void (*LstSetSelectionP) (ListType *listP, Int16 itemNum);

	GetParameter (&LstSetSelectionP , sizeof(void *), pLstSetSelection );
	(*LstSetSelectionP) (listP, itemNum);
}              
#endif

#ifdef L_LstSetTopItem        
void LstSetTopItem (ListType *listP, Int16 itemNum)
{
	void (*LstSetTopItemP) (ListType *listP, Int16 itemNum);

	GetParameter (&LstSetTopItemP , sizeof(void *), pLstSetTopItem );
	(*LstSetTopItemP) (listP,  itemNum);
}
#endif



