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
// Memory Manager Library, completed 44/44 functions now.
////////////////////////////////////////////////////////////
#ifdef L_MemCardInfo
Err MemCardInfo (UInt16 cardNo, Char *cardNameP, Char *manufNameP,
                                          UInt16 *versionP, UInt32 *crDateP, UInt32 *romSizeP,
                                          UInt32 *ramSizeP, UInt32 *freeBytesP)
{     
	Err (*MemCardInfoP) (UInt16 cardNo, Char *cardNameP, Char *manufNameP,
                                          UInt16 *versionP, UInt32 *crDateP, UInt32 *romSizeP,
                                          UInt32 *ramSizeP, UInt32 *freeBytesP);

	GetParameter (&MemCardInfoP , sizeof(void *), pMemCardInfo );
	return(*MemCardInfoP) ( cardNo, cardNameP, manufNameP,
                                          versionP, crDateP, romSizeP,
                                          ramSizeP, freeBytesP);
}                          
#endif

#ifdef L_MemCmp              
Int16 MemCmp(const void *str1, const void *str2, Int32 numBytes)
{     
	Int16(*MemCmpP) (const void *str1, const void *str2, Int32 numBytes);

	GetParameter (&MemCmpP , sizeof(void *), pMemCmp );
	return(*MemCmpP) (str1,  str2,  numBytes);
}       
#endif

#ifdef L_MemDebugMode
UInt16 MemDebugMode (void)
{     
	UInt16 (*MemDebugModeP) (void);

	GetParameter (&MemDebugModeP , sizeof(void *), pMemDebugMode );
	return(*MemDebugModeP) ();
}
#endif

#ifdef L_MemHandleCardNo
UInt16 MemHandleCardNo (MemHandle h)
{     
	UInt16 (*MemHandleCardNoP) (MemHandle h);

	GetParameter (&MemHandleCardNoP , sizeof(void *), pMemHandleCardNo );
	return(*MemHandleCardNoP) (h);
}
#endif

#ifdef L_MemHandleDataStorage
Boolean MemHandleDataStorage (MemHandle h)
{     
	Boolean (*MemHandleDataStorageP) (MemHandle h);

	GetParameter (&MemHandleDataStorageP , sizeof(void *), pMemHandleDataStorage );
	return(*MemHandleDataStorageP) (h);
}
#endif

#ifdef L_MemHandleFree
Err MemHandleFree (MemHandle h)
{     
	Err (*MemHandleFreeP) (MemHandle h);

	GetParameter (&MemHandleFreeP , sizeof(void *), pMemHandleFree );
	return(*MemHandleFreeP) (h);
}
#endif

#ifdef L_MemHandleHeapID
UInt16 MemHandleHeapID (MemHandle h)
{     
	UInt16 (*MemHandleHeapIDP) (MemHandle h);

	GetParameter (&MemHandleHeapIDP , sizeof(void *), pMemHandleHeapID );
	return(*MemHandleHeapIDP) (h);
}
#endif

#ifdef L_MemHandleLock
MemPtr MemHandleLock (MemHandle h)
{     
	MemPtr(*MemHandleLockP)  (MemHandle h);

	GetParameter (&MemHandleLockP , sizeof(void *), pMemHandleLock );
	return(*MemHandleLockP)  (h);
}
#endif

#ifdef L_MemHandleNew
MemHandle MemHandleNew (UInt32 size)
{     
	MemHandle (*MemHandleNewP) (UInt32 size);

	GetParameter (&MemHandleNewP , sizeof(void *), pMemHandleNew );
	return(*MemHandleNewP) (size);
}       
#endif

#ifdef L_MemHandleResize
Err MemHandleResize (MemHandle h, UInt32 newSize)
{     
	Err (*MemHandleResizeP) (MemHandle h, UInt32 newSize);

	GetParameter (&MemHandleResizeP , sizeof(void *), pMemHandleResize );
	return(*MemHandleResizeP) ( h,  newSize);
}       
#endif

#ifdef L_MemHandleSetOwner
Err MemHandleSetOwner (MemHandle h, UInt16 owner)
{     
	Err (*MemHandleSetOwnerP) (MemHandle h, UInt16 owner);

	GetParameter (&MemHandleSetOwnerP , sizeof(void *), pMemHandleSetOwner );
	return(*MemHandleSetOwnerP) (h,  owner);
}     
#endif

#ifdef L_MemHandleSize
UInt32 MemHandleSize (MemHandle h)
{     
	UInt32 (*MemHandleSizeP) (MemHandle h);

	GetParameter (&MemHandleSizeP , sizeof(void *), pMemHandleSize );
	return(*MemHandleSizeP) (h);
}
#endif

#ifdef L_MemHandleToLocalID
LocalID MemHandleToLocalID (MemHandle h)
{     
	LocalID (*MemHandleToLocalIDP) (MemHandle h);

	GetParameter (&MemHandleToLocalIDP , sizeof(void *), pMemHandleToLocalID );
	return(*MemHandleToLocalIDP) (h);
}
#endif

#ifdef L_MemHandleUnlock
Err MemHandleUnlock (MemHandle h)
{     
	Err (*MemHandleUnlockP) (MemHandle h);

	GetParameter (&MemHandleUnlockP , sizeof(void *), pMemHandleUnlock );
	return(*MemHandleUnlockP) (h);
}
#endif

#ifdef L_MemHeapCheck
Err MemHeapCheck (UInt16 heapID)
{     
	Err (*MemHeapCheckP) (UInt16 heapID);

	GetParameter (&MemHeapCheckP , sizeof(void *), pMemHeapCheck );
	return(*MemHeapCheckP) (heapID);
}       
#endif

#ifdef L_MemHeapCompact
Err MemHeapCompact (UInt16 heapID)
{     
	Err (*MemHeapCompactP) (UInt16 heapID);

	GetParameter (&MemHeapCompactP , sizeof(void *), pMemHeapCompact );
	return (*MemHeapCompactP) (heapID);
}
#endif

#ifdef L_MemHeapDynamic
Boolean MemHeapDynamic (UInt16 heapID)
{     
	Boolean (*MemHeapDynamicP) (UInt16 heapID);

	GetParameter (&MemHeapDynamicP , sizeof(void *), pMemHeapDynamic );
	return(*MemHeapDynamicP) (heapID);
}
#endif

#ifdef L_MemHeapFlags
UInt16 MemHeapFlags (UInt16 heapID)
{     
	UInt16 (*MemHeapFlagsP) (UInt16 heapID);

	GetParameter (&MemHeapFlagsP , sizeof(void *), pMemHeapFlags );
	return(*MemHeapFlagsP) (heapID);
}
#endif

#ifdef L_MemHeapFreeBytes
Err MemHeapFreeBytes (UInt16 heapID, UInt32 *freeP, UInt32 maxP)
{     
	Err (*MemHeapFreeBytesP) (UInt16 heapID, UInt32 *freeP, UInt32 maxP);

	GetParameter (&MemHeapFreeBytesP , sizeof(void *), pMemHeapFreeBytes );
	return(*MemHeapFreeBytesP) (heapID, freeP, maxP);
}       
#endif

#ifdef L_MemHeapID
UInt16 MemHeapID (UInt16 cardNo, UInt16 heapIndex)
{
	UInt16 (*MemHeapIDP) (UInt16 cardNo, UInt16 heapIndex);

	GetParameter (&MemHeapIDP , sizeof(void *), pMemHeapID );
	return(*MemHeapIDP) (cardNo, heapIndex);
}
#endif

#ifdef L_MemHeapScramble
Err MemHeapScramble (UInt16 heapID)
{     
	Err (*MemHeapScrambleP) (UInt16 heapID);

	GetParameter (&MemHeapScrambleP , sizeof(void *), pMemHeapScramble );
	return(*MemHeapScrambleP) (heapID);
}
#endif

#ifdef L_MemHeapSize
UInt32 MemHeapSize (UInt16 heapID)
{     
	UInt32 (*MemHeapSizeP) (UInt16 heapID);

	GetParameter (&MemHeapSizeP , sizeof(void *), pMemHeapSize );
	return(*MemHeapSizeP) (heapID);
}
#endif
/*
#ifdef L_MemLocalIDKind
LocalIDKind MemLocalIDKind (LocalID local)
{     
	LocalIDKind (*MemLocalIDKindP) (LocalID local);

	GetParameter (&MemLocalIDKindP , sizeof(void *), pMemLocalIDKind );
	return (*MemLocalIDKindP) (local);
}
#endif
*/
#ifdef L_MemLocaIDToGlobal
MemPtr MemLocaIDToGlobal (LocalID local, UInt16 cardNo)
{     
	MemPtr (*MemLocaIDToGlobalP) (LocalID local, UInt16 cardNo);

	GetParameter (&MemLocaIDToGlobalP , sizeof(void *), pMemLocaIDToGlobal );
	return(*MemLocaIDToGlobalP) (local, cardNo);
}
#endif

#ifdef L_MemLocalIDToLockedPtr
MemPtr MemLocalIDToLockedPtr (LocalID local, UInt16 cardNo)
{     
	MemPtr (*MemLocalIDToLockedPtrP) (LocalID local, UInt16 cardNo);

	GetParameter (&MemLocalIDToLockedPtrP , sizeof(void *), pMemLocalIDToLockedPtr );
	return(*MemLocalIDToLockedPtrP) (local,  cardNo);
}
#endif

#ifdef L_MemLocalIDToPtr
MemPtr MemLocalIDToPtr (LocalID local, UInt16 cardNo)
{     
	MemPtr (*MemLocalIDToPtrP) (LocalID local, UInt16 cardNo);

	GetParameter (&MemLocalIDToPtrP , sizeof(void *), pMemLocalIDToPtr );
	return(*MemLocalIDToPtrP) ( local,  cardNo);
}
#endif

#ifdef L_MemMove
Err MemMove (VoidPtr dstP, VoidPtr srcP, Int32 numBytes)
{     
	Err (*MemMoveP) (VoidPtr dstP, VoidPtr srcP, Int32 numBytes);

	GetParameter (&MemMoveP , sizeof(void *), pMemMove );
	return (*MemMoveP) ( dstP,  srcP,  numBytes);
}
#endif

#ifdef L_MemNumCards
UInt16 MemNumCards (void)
{     
	UInt16 (*MemNumCardsP) (void);
	
	GetParameter (&MemNumCardsP , sizeof(void *), pMemNumCards );
	return(*MemNumCardsP) ();
}
#endif

#ifdef L_MemNumHeaps
UInt16 MemNumHeaps (UInt16 cardNo)
{     
	UInt16 (*MemNumHeapsP) (UInt16 cardNo);

	GetParameter (&MemNumHeapsP , sizeof(void *), pMemNumHeaps );
	return (*MemNumHeapsP) (cardNo);
}
#endif

#ifdef L_MemNumRAMHeaps
UInt16 MemNumRAMHeaps (UInt16 cardNo)
{      
	UInt16 (*MemNumRAMHeapsP) (UInt16 cardNo);

	GetParameter (&MemNumRAMHeapsP , sizeof(void *), pMemNumRAMHeaps );
	return (*MemNumRAMHeapsP) (cardNo);
}
#endif

#ifdef L_MemPtrCardNo
UInt16 MemPtrCardNo (MemPtr p)
{     
	UInt16 (*MemPtrCardNoP) (MemPtr p);

	GetParameter (&MemPtrCardNoP , sizeof(void *), pMemPtrCardNo );
	return (*MemPtrCardNoP) ( p);
}
#endif

#ifdef L_MemPtrDataStorage
Boolean MemPtrDataStorage (MemPtr p)
{     
	Boolean (*MemPtrDataStorageP) (MemPtr p);

	GetParameter (&MemPtrDataStorageP , sizeof(void *), pMemPtrDataStorage );
	return (*MemPtrDataStorageP) (p);
}
#endif

#ifdef L_MemPtrFree
Err MemPtrFree(MemPtr p)
{     
	Err (*MemPtrFreeP)(MemPtr p);

	GetParameter (&MemPtrFreeP , sizeof(void *), pMemPtrFree );
	return(*MemPtrFreeP)(p);
}
#endif

#ifdef L_MemPtrHeapID
UInt16 MemPtrHeapID (MemPtr p)
{     
	UInt16 (*MemPtrHeapIDP) (MemPtr p);

	GetParameter (&MemPtrHeapIDP , sizeof(void *), pMemPtrHeapID );
	return(*MemPtrHeapIDP) (p);
}
#endif

#ifdef L_MemPtrNew
MemPtr MemPtrNew(UInt32 size)
{     
	MemPtr (*MemPtrNewP)(UInt32 size);

	GetParameter (&MemPtrNewP , sizeof(void *), pMemPtrNew );
	return(*MemPtrNewP)(size);
}
#endif

#ifdef L_MemPtrRecoverHandle
MemHandle MemPtrRecoverHandle (MemPtr p)
{     
	MemHandle (*MemPtrRecoverHandleP) (MemPtr p);

	GetParameter (&MemPtrRecoverHandleP , sizeof(void *), pMemPtrRecoverHandle );
	return(*MemPtrRecoverHandleP) (p);
}
#endif

#ifdef L_MemPtrResize
Err MemPtrResize (MemPtr p, UInt32 newSize)
{   
	Err (*MemPtrResizeP) (MemPtr p, UInt32 newSize);

	GetParameter (&MemPtrResizeP , sizeof(void *), pMemPtrResize );
	return(*MemPtrResizeP) ( p,  newSize);
}
#endif

#ifdef L_MemPtrSetOwner
Err MemPtrSetOwner (MemPtr p, UInt16 owner)
{     
	Err (*MemPtrSetOwnerP) (MemPtr p, UInt16 owner);

	GetParameter (&MemPtrSetOwnerP , sizeof(void *), pMemPtrSetOwner );
	return (*MemPtrSetOwnerP) ( p,  owner);
}
#endif

#ifdef L_MemPtrSize
UInt32 MemPtrSize (MemPtr p)
{     
	UInt32 (*MemPtrSizeP) (MemPtr p);

	GetParameter (&MemPtrSizeP , sizeof(void *), pMemPtrSize );
	return(*MemPtrSizeP) (p);
}
#endif

#ifdef L_MemPtrToLocalID
LocalID MemPtrToLocalID (MemPtr p)
{     
	LocalID (*MemPtrToLocalIDP) (MemPtr p);

	GetParameter (&MemPtrToLocalIDP , sizeof(void *), pMemPtrToLocalID );
	return(*MemPtrToLocalIDP) (p);
}
#endif

#ifdef L_MemPtrUnlock
Err MemPtrUnlock (MemPtr p)
{  
	Err (*MemPtrUnlockP) (MemPtr p);

	GetParameter (&MemPtrUnlockP , sizeof(void *), pMemPtrUnlock );
	return (*MemPtrUnlockP) (p);
}
#endif

#ifdef L_MemSet
Err MemSet(void *dstP, UInt32 numBytes, UInt8 value)
{   
	Err (*MemSetP)(void *dstP, UInt32 numBytes, UInt8 value);

	GetParameter (&MemSetP , sizeof(void *), pMemSet );
	return (*MemSetP)(dstP,  numBytes, value);
}
#endif

#ifdef L_MemSetDebugMode
Err MemSetDebugMode (UInt16 flags)
{     
	Err (*MemSetDebugModeP) (UInt16 flags);

	GetParameter (&MemSetDebugModeP , sizeof(void *), pMemSetDebugMode );
	return (*MemSetDebugModeP) (flags);
}
#endif

// Err MemStoreInfo (UInt16 cardNo, UInt16 storeNumber, UInt16 *versionP,
//                                              UInt16 *flagsP, Char *nameP, UInt32 *crDateP,
//                                              UInt32 *bckUpDateP, UInt32 *heapListOffsetP,
//                                              UInt32 *initCodeOffset1P, UInt32 *initCodeOffset2P,
//                                              LocalID *databaseDirIDP);



////////////////////////////////////////////////////////////
// Menu Processing Library, completed 10/14 functions now.
////////////////////////////////////////////////////////////
#ifdef L_MenuAddItem
Err MenuAddItem (UInt16 positionID, UInt16 id, Char cmd, const Char *textP)
{  
	Err (*MenuAddItemP) (UInt16 positionID, UInt16 id, Char cmd, const Char *textP);

	GetParameter (&MenuAddItemP , sizeof(void *), pMenuAddItem );
	return (*MenuAddItemP) ( positionID,  id,  cmd,  textP);
}
#endif

//Err MenuCmdBarAddButton (UInt8 where, UInt16 bitmapID, MenuCmdBarResultType resultType, 
//                                               UInt32 result, Char *nameP);
//void MenuCmdBarDisplay (void);
//Boolean MenuCmdBarGetButtonData (Int16 buttonIndex, UInt16 *bitmapIdP, 
//                                                               MenuCmdBarResultType *resultTypeP,
//                                                               UInt32 *resultP, Char *nameP);
#ifdef L_MenuDispose
void MenuDispose (MenuBarType *menuP)
{     
	void (*MenuDisposeP) (MenuBarType *menuP);

	GetParameter (&MenuDisposeP , sizeof(void *), pMenuDispose );
	(*MenuDisposeP) (menuP);
}
#endif

#ifdef L_MenuDrawMenu
void MenuDrawMenu (MenuBarType *menuP)
{     
	void (*MenuDrawMenuP) (MenuBarType *menuP);
 
	GetParameter (&MenuDrawMenuP , sizeof(void *), pMenuDrawMenu );
	(*MenuDrawMenuP) (menuP);
}
#endif

#ifdef L_MenuEraseStatus
void MenuEraseStatus (MenuBarType *menuP)
{     
	void (*MenuEraseStatusP) (MenuBarType *menuP);

	GetParameter (&MenuEraseStatusP , sizeof(void *), pMenuEraseStatus );
	(*MenuEraseStatusP) (menuP);
}
#endif

#ifdef L_MenuGetActiveMenu
MenuBarType *MenuGetActiveMenu (void)
{     
	MenuBarType *(*MenuGetActiveMenuP) (void);

	GetParameter (&MenuGetActiveMenuP , sizeof(void *), pMenuGetActiveMenu );
	return(*MenuGetActiveMenuP) ();
}
#endif

#ifdef L_MenuHandleEvent
Boolean MenuHandleEvent(MenuBarType *menuP, EventType *event, UInt16 *error) 
{     
	Boolean (*MenuHandleEventP)(MenuBarType *menuP, EventType *event, UInt16 *error) ;

	GetParameter (&MenuHandleEventP , sizeof(void *), pMenuHandleEvent );
	return(*MenuHandleEventP)(menuP, event, error) ;
}
#endif

#ifdef L_MenuHideItem
Boolean MenuHideItem (UInt16 id)
{     
	Boolean (*MenuHideItemP) (UInt16 id);

	GetParameter (&MenuHideItemP , sizeof(void *), pMenuHideItem );
	return (*MenuHideItemP) (id);
}
#endif

#ifdef L_MenuInit
MenuBarType *MenuInit (UInt16 resourceID)
{    
	MenuBarType *(*MenuInitP) (UInt16 resourceID);

	GetParameter (&MenuInitP , sizeof(void *), pMenuInit );
	return(*MenuInitP) (resourceID);
}
#endif

#ifdef L_MenuSetActiveMenu
MenuBarType *MenuSetActiveMenu (MenuBarType *menuP)
{     
	MenuBarType *(*MenuSetActiveMenuP) (MenuBarType *menuP);

	GetParameter (&MenuSetActiveMenuP , sizeof(void *), pMenuSetActiveMenu );
	return(*MenuSetActiveMenuP) (menuP);
}
#endif

#ifdef L_MenuSetActiveMenuRscID
void MenuSetActiveMenuRscID (UInt16 resourceID)
{     
	void (*MenuSetActiveMenuRscIDP) (UInt16 resourceID);

	GetParameter (&MenuSetActiveMenuRscIDP , sizeof(void *), pMenuSetActiveMenuRscID );
	(*MenuSetActiveMenuRscIDP) (resourceID);
}
#endif

#ifdef L_MenuShowItem
Boolean MenuShowItem (UInt16 id)
{     
	Boolean (*MenuShowItemP) (UInt16 id);

	GetParameter (&MenuShowItemP , sizeof(void *), pMenuShowItem );
	return(*MenuShowItemP) (id);
}
#endif


////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
#ifdef L_Crc16CalcBlock
UInt16	Crc16CalcBlock(const void *bufP, UInt16 count, UInt16 crc)
{

	UInt16	(*Crc16CalcBlockP)(const void *bufP, UInt16 count, UInt16 crc);

	GetParameter (&Crc16CalcBlockP , sizeof(void *), pCrc16CalcBlock );
	return  (*Crc16CalcBlockP)(bufP,  count,  crc);
}
#endif
/*
#ifdef L_IntlGetRoutineAddress
void *IntlGetRoutineAddress(IntlSelector inSelector)
{
	void *(*IntlGetRoutineAddressP)(IntlSelector inSelector);

	GetParameter (&IntlGetRoutineAddressP , sizeof(void *), pIntlGetRoutineAddress );
	return	(*IntlGetRoutineAddressP)(inSelector);
}
#endif
*/
#ifdef L_LocGetNumberSeparators
void LocGetNumberSeparators(NumberFormatType numberFormat,Char *thousandSeparator, Char *decimalSeparator)
{

	void (*LocGetNumberSeparatorsP)(NumberFormatType numberFormat,Char *thousandSeparator, Char *decimalSeparator);

	GetParameter (&LocGetNumberSeparatorsP , sizeof(void *), pLocGetNumberSeparators );
	return	(*LocGetNumberSeparatorsP)( numberFormat,thousandSeparator, decimalSeparator);
}
#endif

////////////////////////////////////////////////////////////
// Modem Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_MdmDial
Err MdmDial (MdmInfoPtr modemP, Char *okDialP,Char *userInitP, Char *phoneNumP)
{

	Err (*MdmDialP) (MdmInfoPtr modemP, Char *okDialP,Char *userInitP, Char *phoneNumP);

	GetParameter (&MdmDialP , sizeof(void *), pMdmDial );
	return	 (*MdmDialP) (modemP, okDialP,userInitP, phoneNumP);
}
#endif
*/
/*
#ifdef L_MdmHangUp
Err MdmHangUp (MdmInfoPtr modemP)
{

	Err (*MdmHangUpP) (MdmInfoPtr modemP);

	GetParameter (&MdmHangUpP , sizeof(void *), pMdmHangUp );
	return (*MdmHangUpP) (modemP);
}
#endif
*/
////////////////////////////////////////////////////////////
// Net Library, completed 43/43 functions now.
////////////////////////////////////////////////////////////

#ifdef L_NetLibAddrAToIN
NetIPAddr NetLibAddrAToIN (UInt16 libRefNum, Char *a)
{     
	NetIPAddr (*NetLibAddrAToINP) (UInt16 libRefNum, Char *a);

	GetParameter (&NetLibAddrAToINP , sizeof(void *), pNetLibAddrAToIN );
	return (*NetLibAddrAToINP) ( libRefNum, a);
}
#endif

#ifdef L_NetLibAddrINToA
Char *NetLibAddrINToA (UInt16 libRefNum, NetIPAddr inet, Char *spaceP)
{     
	Char *(*NetLibAddrINToAP) (UInt16 libRefNum, NetIPAddr inet, Char *spaceP);

	GetParameter (&NetLibAddrINToAP , sizeof(void *), pNetLibAddrINToA );
	return(*NetLibAddrINToAP) ( libRefNum,  inet, spaceP);
}
#endif

#ifdef L_NetLibClose
Err NetLibClose (UInt16 libRefNum, UInt16 immediate)
{   
	Err (*NetLibCloseP) (UInt16 libRefNum, UInt16 immediate);

	GetParameter (&NetLibCloseP , sizeof(void *), pNetLibClose );
	return(*NetLibCloseP) ( libRefNum,  immediate);
}
#endif

#ifdef L_NetLibGetHostByName
NetHostInfoPtr NetLibGetHostByName (UInt16 libRefNum, Char *nameP,
                                                                  NetHostInfoBufPtr bufP, Int32 timeout, Err *errP)
{     
	NetHostInfoPtr (*NetLibGetHostByNameP) (UInt16 libRefNum, Char *nameP,
                                                                  NetHostInfoBufPtr bufP, Int32 timeout, Err *errP);

	GetParameter (&NetLibGetHostByNameP , sizeof(void *), pNetLibGetHostByName );
	return(*NetLibGetHostByNameP) ( libRefNum, nameP,   bufP,  timeout, errP);
}         
#endif

#ifdef L_NetLibOpen                                                                           
Err NetLibOpen (UInt16 libRefNum, UInt16 *netIFErrP)
{     
	Err (*NetLibOpenP) (UInt16 libRefNum, UInt16 *netIFErrP);

	GetParameter (&NetLibOpenP , sizeof(void *), pNetLibOpen );
	return (*NetLibOpenP) ( libRefNum, netIFErrP);
}
#endif

#ifdef L_NetLibSocketClose
Int16 NetLibSocketClose (UInt16 libRefNum, NetSocketRef socket,
                                                                                        Int32 timeout, Err* errP)
{       
	Int16 (*NetLibSocketCloseP) (UInt16 libRefNum, NetSocketRef socket,
                                                                                        Int32 timeout, Err* errP);

	GetParameter (&NetLibSocketCloseP , sizeof(void *), pNetLibSocketClose );
	return (*NetLibSocketCloseP) ( libRefNum,  socket,     timeout,  errP);
}
#endif

#ifdef L_NetLibSocketConnect
Int16 NetLibSocketConnect (UInt16 libRefNum, NetSocketRef socket,
                                                                                          NetSocketAddrType *sockAddrP, Int16 addrLen,
                                                                                          Int32 timeout, Err *errP)
{     
	Int16 (*NetLibSocketConnectP) (UInt16 libRefNum, NetSocketRef socket,
                                                                                          NetSocketAddrType *sockAddrP, Int16 addrLen,
                                                                                          Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketConnectP , sizeof(void *), pNetLibSocketConnect );
	return (*NetLibSocketConnectP) ( libRefNum,  socket,   sockAddrP,  addrLen,
                                                                                     timeout, errP);
}
#endif

#ifdef L_NetLibSocketOpen
NetSocketRef NetLibSocketOpen (UInt16 libRefNum, NetSocketAddrEnum domain,
                                                                                        NetSocketTypeEnum type, Int16 protocol, 
                                                                                        Int32 timeout, Err *errP)
{     
	NetSocketRef (*NetLibSocketOpenP) (UInt16 libRefNum, NetSocketAddrEnum domain,
                                                                                        NetSocketTypeEnum type, Int16 protocol, Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketOpenP , sizeof(void *), pNetLibSocketOpen );
	return (*NetLibSocketOpenP) ( libRefNum,  domain,      type,  protocol, timeout, errP) ;
}

#endif


#ifdef L_NetLibSleep
Err	NetLibSleep (UInt16 libRefnum)
{
	Err	(*NetLibSleepP) (UInt16 libRefnum);

	GetParameter (&NetLibSleepP , sizeof(void *), pNetLibSleep );
	return 	(*NetLibSleepP) (libRefnum);
}

#endif

#ifdef L_NetLibWake
Err	NetLibWake (UInt16 libRefnum)
{
	Err	(*NetLibWakeP) (UInt16 libRefnum);

	GetParameter (&NetLibWakeP , sizeof(void *), pNetLibWake );
	return 	(*NetLibWakeP) (libRefnum);
}
#endif


#ifdef L_NetLibFinishCloseWait
Err	NetLibFinishCloseWait(UInt16 libRefnum)
{
	Err	(*NetLibFinishCloseWaitP)(UInt16 libRefnum);

	GetParameter (&NetLibFinishCloseWaitP , sizeof(void *), pNetLibFinishCloseWait );
	return   (*NetLibFinishCloseWaitP)(libRefnum);
}
#endif

#ifdef L_NetLibOpenIfCloseWait
Err	NetLibOpenIfCloseWait(UInt16 libRefnum)
{
	Err	(*NetLibOpenIfCloseWaitP)(UInt16 libRefnum);

	GetParameter (&NetLibOpenIfCloseWaitP , sizeof(void *), pNetLibOpenIfCloseWait );
	return  (*NetLibOpenIfCloseWaitP)(libRefnum);
}
#endif

#ifdef L_NetLibOpenCount
Err	NetLibOpenCount (UInt16 refNum, UInt16 *countP)
{
	Err	(*NetLibOpenCountP) (UInt16 refNum, UInt16 *countP);

	GetParameter (&NetLibOpenCountP , sizeof(void *), pNetLibOpenCount );
	return  (*NetLibOpenCountP) (refNum, countP);
}
#endif

#ifdef L_NetLibHandlePowerOff
Err	NetLibHandlePowerOff (UInt16 refNum, SysEventType *eventP)
{
	Err	(*NetLibHandlePowerOffP) (UInt16 refNum, SysEventType *eventP);

	GetParameter (&NetLibHandlePowerOffP , sizeof(void *), pNetLibHandlePowerOff );
	return  (*NetLibHandlePowerOffP) (refNum, eventP);
}
#endif


#ifdef L_NetLibConnectionRefresh
Err	NetLibConnectionRefresh(UInt16 refNum, Boolean refresh,
							UInt8 *allInterfacesUpP, UInt16 *netIFErrP)
{
	Err	(*NetLibConnectionRefreshP)(UInt16 refNum, Boolean refresh,
							UInt8 *allInterfacesUpP, UInt16 *netIFErrP);

	GetParameter (&NetLibConnectionRefreshP , sizeof(void *), pNetLibConnectionRefresh );
	return (*NetLibConnectionRefreshP)( refNum,  refresh, allInterfacesUpP, netIFErrP);
}
#endif


/*
#ifdef L_NetLibSocketOptionSet
Int16	NetLibSocketOptionSet(UInt16 libRefnum, NetSocketRef socket,
							UInt16  level, UInt16  option,
							void *optValueP, UInt16 optValueLen,
							Int32 timeout, Err *errP)
{
	Int16	(*NetLibSocketOptionSetP)(UInt16 libRefnum, NetSocketRef socket,
							UInt16  level, UInt16  option,
							void *optValueP, UInt16 optValueLen,
							Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketOptionSetP , sizeof(void *), pNetLibSocketOptionSet );
	return (*NetLibSocketOptionSetP)(libRefnum, socket, level,   option,
							optValueP,  optValueLen, timeout, errP);
}
#endif

#ifdef L_NetLibSocketOptionGet
Int16	NetLibSocketOptionGet(UInt16 libRefnum, NetSocketRef socket,
							UInt16 level, UInt16 option,
							void *optValueP, UInt16 *optValueLenP,
							Int32 timeout, Err *errP)
{
	Int16	(*NetLibSocketOptionGetP)(UInt16 libRefnum, NetSocketRef socket,
							UInt16  level, UInt16  option,
							void *optValueP, UInt16 *optValueLenP,
							Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketOptionGetP , sizeof(void *), pNetLibSocketOptionGet );
	return  (*NetLibSocketOptionGetP)(libRefnum,  socket, level,   option,
							optValueP, optValueLenP,
							 timeout, errP);
}
#endif

#ifdef L_NetLibSocketBind
Int16	NetLibSocketBind(UInt16 libRefnum, NetSocketRef socket,
							NetSocketAddrType *sockAddrP, Int16 addrLen, Int32 timeout,
							Err *errP)
{
	Int16	(*NetLibSocketBindP)(UInt16 libRefnum, NetSocketRef socket,
							NetSocketAddrType *sockAddrP, Int16 addrLen, Int32 timeout,
							Err *errP);

	GetParameter (&NetLibSocketBindP , sizeof(void *), pNetLibSocketBind );
	return (*NetLibSocketBindP)(libRefnum,  socket,sockAddrP,  addrLen,  timeout, errP);
}
#endif




#ifdef L_NetLibSocketListen
Int16	NetLibSocketListen(UInt16 libRefnum, NetSocketRef socket,
							UInt16	queueLen, Int32 timeout, Err *errP)
{
	Int16	(*NetLibSocketListenP)(UInt16 libRefnum, NetSocketRef socket,
							UInt16	queueLen, Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketListenP , sizeof(void *), pNetLibSocketListen );
	return (*NetLibSocketListenP)(libRefnum,  socket,queueLen,  timeout, errP);
}
#endif


#ifdef L_NetLibSocketAccept
Int16	NetLibSocketAccept(UInt16 libRefnum, NetSocketRef socket,
							NetSocketAddrType *sockAddrP, Int16 *addrLenP, Int32 timeout,
							Err *errP)
{
	Int16	(*NetLibSocketAcceptP)(UInt16 libRefnum, NetSocketRef socket,
							NetSocketAddrType *sockAddrP, Int16 *addrLenP, Int32 timeout,
							Err *errP);

	GetParameter (&NetLibSocketAcceptP , sizeof(void *), pNetLibSocketAccept );
	return  (*NetLibSocketAcceptP)(libRefnum,  socket,sockAddrP, addrLenP,  timeout,errP);
}
#endif


#ifdef L_NetLibSocketShutdown
Int16	NetLibSocketShutdown(UInt16 libRefnum, NetSocketRef socket,
							Int16  direction, Int32 timeout, Err *errP)
{
	Int16	(*NetLibSocketShutdownP)(UInt16 libRefnum, NetSocketRef socket,
							Int16  direction, Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketShutdownP , sizeof(void *), pNetLibSocketShutdown );
	return (*NetLibSocketShutdownP)( libRefnum,  socket,  direction,  timeout, errP);
}
#endif



#ifdef L_NetLibSocketAddr
Int16	NetLibSocketAddr(UInt16 libRefnum, NetSocketRef socketRef,
							NetSocketAddrType *locAddrP, Int16 *locAddrLenP,
							NetSocketAddrType *remAddrP, Int16 *remAddrLenP,
							Int32 timeout, Err *errP)
{
	Int16	(*NetLibSocketAddrP)(UInt16 libRefnum, NetSocketRef socketRef,
							NetSocketAddrType *locAddrP, Int16 *locAddrLenP,
							NetSocketAddrType *remAddrP, Int16 *remAddrLenP,
							Int32 timeout, Err *errP);

	GetParameter (&NetLibSocketAddrP , sizeof(void *), pNetLibSocketAddr );
	return  (*NetLibSocketAddrP)(libRefnum,  socketRef,locAddrP, locAddrLenP,
							remAddrP, remAddrLenP,
							 timeout, errP);
}
#endif




#ifdef L_NetLibSendPB
Int16	NetLibSendPB(UInt16 libRefNum, NetSocketRef socket,
							NetIOParamType *pbP, UInt16 flags, Int32 timeout, Err *errP)
{
	Int16	(*NetLibSendPBP)(UInt16 libRefNum, NetSocketRef socket,
							NetIOParamType *pbP, UInt16 flags, Int32 timeout, Err *errP);

	GetParameter (&NetLibSendPBP , sizeof(void *), NetLibSendPBP );
	return (*NetLibSendPBP)( libRefNum,  socket,pbP,  flags,  timeout, errP);
}
#endif

#ifdef L_NetLibSend
Int16	NetLibSend(UInt16 libRefNum, NetSocketRef socket,
							void *bufP, UInt16 bufLen, UInt16 flags,
							void *toAddrP, UInt16 toLen, Int32 timeout, Err *errP)
{
	Int16	(*NetLibSendP)(UInt16 libRefNum, NetSocketRef socket,
							void *bufP, UInt16 bufLen, UInt16 flags,
							void *toAddrP, UInt16 toLen, Int32 timeout, Err *errP);

	GetParameter (&NetLibSendP , sizeof(void *), pNetLibSend );
	return  (*NetLibSendP)( libRefNum,  socket,bufP,  bufLen,  flags,
							toAddrP,  toLen,  timeout, errP);
}
#endif

#ifdef L_NetLibReceivePB
Int16	NetLibReceivePB(UInt16 libRefNum, NetSocketRef socket,
							NetIOParamType *pbP, UInt16 flags, Int32 timeout, Err *errP)
{
	Int16	(*NetLibReceivePBP)(UInt16 libRefNum, NetSocketRef socket,
							NetIOParamType *pbP, UInt16 flags, Int32 timeout, Err *errP);

	GetParameter (&NetLibReceivePBP , sizeof(void *), pNetLibReceivePB );
	return (*NetLibReceivePBP)(libRefNum, socket,pbP,  flags,  timeout, errP);
}
#endif

#ifdef L_NetLibReceive
Int16	NetLibReceive(UInt16 libRefNum, NetSocketRef socket,
							void *bufP, UInt16 bufLen, UInt16 flags,
							void *fromAddrP, UInt16 *fromLenP, Int32 timeout, Err *errP)
{
	nt16	(*NetLibReceiveP)(UInt16 libRefNum, NetSocketRef socket,
							void *bufP, UInt16 bufLen, UInt16 flags,
							void *fromAddrP, UInt16 *fromLenP, Int32 timeout, Err *errP);

	GetParameter (&NetLibReceiveP , sizeof(void *), pNetLibReceive );
	return (*NetLibReceiveP)( libRefNum,  socket,bufP,  bufLen,  flags,
							fromAddrP, fromLenP,  timeout, errP);
}

#endif
*/
#ifdef L_NetLibDmReceive
Int16	NetLibDmReceive(UInt16 libRefNum, NetSocketRef socket,
							void *recordP, UInt32 recordOffset, UInt16 rcvLen, UInt16 flags, 
							void *fromAddrP, UInt16 *fromLenP, Int32 timeout, Err *errP)
{     
	Int16	(*NetLibDmReceiveP)(UInt16 libRefNum, NetSocketRef socket,
							void *recordP, UInt32 recordOffset, UInt16 rcvLen, UInt16 flags, 
							void *fromAddrP, UInt16 *fromLenP, Int32 timeout, Err *errP);

	GetParameter (&NetLibDmReceiveP , sizeof(void *), pNetLibDmReceive );
	return (*NetLibDmReceiveP)(libRefNum,  socket,recordP,  recordOffset,  rcvLen,  flags, 
							fromAddrP, fromLenP,  timeout, errP);
}
						
#endif


/*
#ifdef L_NetLibGetHostByAddr
NetHostInfoPtr	NetLibGetHostByAddr(UInt16 libRefNum, UInt8 *addrP, UInt16 len, UInt16 type,
							NetHostInfoBufPtr bufP, Int32	timeout, Err *errP)
{     
	NetHostInfoPtr	(*NetLibGetHostByAddrp)(UInt16 libRefNum, UInt8 *addrP, UInt16 len, UInt16 type,
							NetHostInfoBufPtr bufP, Int32	timeout, Err *errP);
	
	GetParameter (&NetLibGetHostByAddrP , sizeof(void *), pNetLibGetHostByAddr );
	return (*NetLibGetHostByAddrp)( libRefNum, addrP,  len,  type,
							 bufP, 	timeout, errP);
}
#endif
*/
#ifdef L_NetLibGetServByName
NetServInfoPtr	NetLibGetServByName(UInt16 libRefNum, const Char *servNameP, 
							const Char *protoNameP,  NetServInfoBufPtr bufP, 
							Int32	timeout, Err *errP)
{     
	NetServInfoPtr	(*NetLibGetServByNameP)(UInt16 libRefNum, const Char *servNameP,
							const Char *protoNameP,  NetServInfoBufPtr bufP, 
							Int32	timeout, Err *errP);
	
	GetParameter (&NetLibGetServByNameP , sizeof(void *), pNetLibGetServByName );
	return (*NetLibGetServByNameP)(libRefNum, servNameP, protoNameP,   bufP, 
								timeout, errP);
}
#endif
/*
#ifdef L_NetLibGetMailExchangeByName
Int16	NetLibGetMailExchangeByName(UInt16 libRefNum, Char *mailNameP,
							UInt16 maxEntries,
							Char hostNames[][netDNSMaxDomainName+1], UInt16 priorities[],
							Int32	timeout, Err *errP)
{
	Int16	(*NetLibGetMailExchangeByNameP)(UInt16 libRefNum, Char *mailNameP,
							UInt16 maxEntries,
							Char hostNames[][netDNSMaxDomainName+1], UInt16 priorities[],
							Int32	timeout, Err *errP);

	GetParameter (&NetLibGetMailExchangeByNameP , sizeof(void *), pNetLibGetMailExchangeByName );
	return (*NetLibGetMailExchangeByNameP)(libRefNum, mailNameP,
							 maxEntries,
							 hostNames[][netDNSMaxDomainName+1],  priorities[],
								timeout, errP);
}
#endif
*/
#ifdef L_NetLibIFGet
Err	NetLibIFGet(UInt16 libRefNum, UInt16 index, UInt32 *ifCreatorP,
								UInt16 *ifInstanceP)
{
	Err	(*NetLibIFGetP)(UInt16 libRefNum, UInt16 index, UInt32 *ifCreatorP,
								UInt16 *ifInstanceP);
									
	GetParameter (&NetLibIFGetP , sizeof(void *), pNetLibIFGet );
	return (*NetLibIFGetP)( libRefNum,  index, ifCreatorP, ifInstanceP);
}
#endif
						
#ifdef L_NetLibIFAttach
Err	NetLibIFAttach(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,
							Int32 timeout)
{     
	Err	(*NetLibIFAttachp)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,Int32 timeout);
	
	GetParameter (&NetLibIFAttachp , sizeof(void *), pNetLibIFAttach );
	return (*NetLibIFAttachp)(libRefNum,  ifCreator,  ifInstance, timeout);
}
#endif
						
#ifdef L_NetLibIFDetach
Err	NetLibIFDetach(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,Int32 timeout)
{     
	Err	(*NetLibIFDetachP)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,Int32 timeout);
	
	GetParameter (&NetLibIFDetachP , sizeof(void *), pNetLibIFDetach );
	return (*NetLibIFDetachP)( libRefNum,  ifCreator,  ifInstance, timeout);
}
#endif
						
#ifdef L_NetLibIFUp
Err	NetLibIFUp(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance)
{     
	Err	(*NetLibIFUpP)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance);
	
	GetParameter (&NetLibIFUpP , sizeof(void *), pNetLibIFUp );
	return (*NetLibIFUpP)( libRefNum,  ifCreator,  ifInstance);
}
#endif

#ifdef L_NetLibIFDown
Err	NetLibIFDown(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,Int32 timeout)
{     
	Err	(*NetLibIFDownP)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,Int32 timeout);
	
	GetParameter (&NetLibIFDownP , sizeof(void *), pNetLibIFDown );
	return (*NetLibIFDownP)( libRefNum,  ifCreator,  ifInstance, timeout);
}
#endif
						



#ifdef L_NetLibSettingGet
Err	NetLibSettingGet(UInt16 libRefNum,UInt16  setting, void *valueP, UInt16 *valueLenP)
{     
	Err	(*NetLibSettingGetP)(UInt16 libRefNum,UInt16  setting, void *valueP, UInt16 *valueLenP);
	
	GetParameter (&NetLibSettingGetP , sizeof(void *), pNetLibSettingGet );
	return  (*NetLibSettingGetP)(libRefNum,  setting, valueP, valueLenP);
}
#endif
						
#ifdef L_NetLibSettingSet
Err	NetLibSettingSet(UInt16 libRefNum,UInt16 setting, void *valueP, UInt16 valueLen)
{     
	Err	(*NetLibSettingSetP)(UInt16 libRefNum,UInt16 setting, void *valueP, UInt16 valueLen);
	
	GetParameter (&NetLibSettingSetP , sizeof(void *), pNetLibSettingSet );
	return (*NetLibSettingSetP)(libRefNum, setting, valueP,  valueLen);
}
#endif
/*
#ifdef L_NetLibIFSettingGet
Err	NetLibIFSettingGet(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,
							UInt16  setting, void *valueP, UInt16 *valueLenP)
{
	Err	(*NetLibIFSettingGetP)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,
							UInt16 setting, void *valueP, UInt16 *valueLenP);

	GetParameter (&NetLibIFSettingGetP , sizeof(void *), pNetLibIFSettingGet );
	return (*NetLibIFSettingGetP)( libRefNum,  ifCreator,  ifInstance, setting, valueP, valueLenP);
}
#endif
*/
#ifdef L_NetLibIFSettingSet						
Err	NetLibIFSettingSet(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,
							UInt16  setting, void *valueP, UInt16 valueLen)
{
	Err	(*NetLibIFSettingSetP)(UInt16 libRefNum, UInt32 ifCreator, UInt16 ifInstance,
							UInt16  setting, void *valueP, UInt16 valueLen);

	GetParameter (&NetLibIFSettingSetP , sizeof(void *), pNetLibIFSettingSet );
	return (*NetLibIFSettingSetP)( libRefNum,  ifCreator,  ifInstance, setting, valueP,  valueLen);
}
#endif
						
/*
#ifdef L_NetLibSelect
Int16	NetLibSelect(UInt16 libRefNum, UInt16 width, NetFDSetType *readFDs,
							NetFDSetType *writeFDs, NetFDSetType *exceptFDs,
							Int32	timeout, Err *errP)
{     
	Int16	(*NetLibSelectP)(UInt16 libRefNum, UInt16 width, NetFDSetType *readFDs, 
							NetFDSetType *writeFDs, NetFDSetType *exceptFDs,
							Int32	timeout, Err *errP);
	
	GetParameter (&NetLibSelectP , sizeof(void *), pNetLibSelect );
	return (*NetLibSelectP)(libRefNum, width, readFDs, writeFDs, exceptFDs,
								timeout, errP);
}
					
#endif


#ifdef L_NetLibMaster
Err	NetLibMaster(UInt16 libRefNum, UInt16 cmd, NetMasterPBPtr pbP,Int32 timeout)

{
	Err	(*NetLibMasterP)(UInt16 libRefNum, UInt16 cmd, NetMasterPBPtr pbP,Int32 timeout);

	GetParameter (&NetLibMasterP , sizeof(void *), pNetLibMaster );
	return (*NetLibMasterP)(libRefNum, cmd, pbP, timeout);
}
#endif
*/    /*
#ifdef L_NetLibTracePrintF
Err	NetLibTracePrintF(UInt16 libRefNum, char *formatStr, ...)
{
	Err	(*NetLibTracePrintFP)(UInt16 libRefNum, char *formatStr, ...);

	GetParameter (&NetLibTracePrintFP , sizeof(void *), pNetLibTracePrintF );
	return  (*NetLibTracePrintFP)(libRefNum, formatStr, ...);
}

#endif
 */
#ifdef L_NetLibTracePutS
Err	NetLibTracePutS(UInt16 libRefNum, Char *strP)
{
	Err	(*NetLibTracePutSP)(UInt16 libRefNum, Char *strP);
	
	GetParameter (&NetLibTracePutSP , sizeof(void *), pNetLibTracePutS );
	return (*NetLibTracePutSP)(libRefNum, strP);
}
					
#endif
						




////////////////////////////////////////////////////////////
// Network Utilities Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
#ifdef L_NetUReadN
Int32 NetUReadN (NetSocketRef fd, UInt8* bufP,UInt32 numBytes)
{     
	Int32 (*NetUReadNP) (NetSocketRef fd, UInt8* bufP,UInt32 numBytes);
	
	GetParameter (&NetUReadNP , sizeof(void *), pNetUReadN );
	return (*NetUReadNP) (fd,  bufP, numBytes);
}
					
#endif

#ifdef L_NetUTCPOpen
NetSocketRef NetUTCPOpen (Char* hostName,Char* serviceName, Int16 port)
{     
	NetSocketRef (*NetUTCPOpenP) (Char* hostName,Char* serviceName, Int16 port);
	
	GetParameter (&NetUTCPOpenP , sizeof(void *), pNetUTCPOpen );
	return (*NetUTCPOpenP) ( hostName, serviceName,  port);
}
					
#endif

#ifdef L_NetUWriteN
Int32 NetUWriteN (NetSocketRef fd, UInt8* bufP,UInt32 numBytes)
{     
	Int32 (*NetUWriteNP) (NetSocketRef fd, UInt8* bufP,UInt32 numBytes);
	
	GetParameter (&NetUWriteNP , sizeof(void *), pNetUWriteN );
	return (*NetUWriteNP) (fd,  bufP, numBytes);
}

#endif







