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
// Memory Manager Library, completed 24/44 functions now.
////////////////////////////////////////////////////////////
void PipeMemCardInfo (void)
{
	WriteParameter (MemCardInfo, sizeof(void*), pMemCardInfo);
}						  
void PipeMemCmp(void)
{
	WriteParameter (MemCmp, sizeof(void*), pMemCmp);
}	
void PipeMemDebugMode (void)
{
	WriteParameter (MemDebugMode, sizeof(void*), pMemDebugMode);
}	
void PipeMemHandleCardNo (void)
{
	WriteParameter (MemHandleCardNo, sizeof(void*), pMemHandleCardNo);
}	

void PipeMemHandleDataStorage (void)
{
//	WriteParameter (MemHandleDataStorage, sizeof(void*), pMemHandleDataStorage);
}
	
void PipeMemHandleFree (void)
{
	WriteParameter (MemHandleFree, sizeof(void*), pMemHandleFree);
}	

void PipeMemHandleHeapID (void)
{
//	WriteParameter (MemHandleHeapID, sizeof(void*), pMemHandleHeapID);
}
	
void PipeMemHandleLock (void)
{
	WriteParameter (MemHandleLock, sizeof(void*), pMemHandleLock);
}	
void PipeMemHandleNew (void)
{
	WriteParameter (MemHandleNew, sizeof(void*), pMemHandleNew);
}	
void PipeMemHandleResize(void)
{
	WriteParameter (MemHandleResize, sizeof(void*), pMemHandleResize);
}	
void PipeMemHandleSetOwner (void)
{
	WriteParameter (MemHandleSetOwner, sizeof(void*), pMemHandleSetOwner);
}	
void PipeMemHandleSize(void)
{
	WriteParameter (MemHandleSize, sizeof(void*), pMemHandleSize);
}	
void PipeMemHandleToLocalID (void)
{
	WriteParameter (MemHandleToLocalID, sizeof(void*), pMemHandleToLocalID);
}	
void PipeMemHandleUnlock (void)
{
	WriteParameter (MemHandleUnlock, sizeof(void*), pMemHandleUnlock);
}	

void PipeMemHeapCheck(void)
{
//	WriteParameter (MemHeapCheck, sizeof(void*), pMemHeapCheck);
}	

void PipeMemHeapCompact (void)
{
//	WriteParameter (MemHeapCompact, sizeof(void*), pMemHeapCompact);
}	

void PipeMemHeapDynamic (void)
{
//	WriteParameter (MemHeapDynamic, sizeof(void*), pMemHeapDynamic);
}	

void PipeMemHeapFlags (void)
{
//	WriteParameter (MemHeapFlags, sizeof(void*), pMemHeapFlags);
}	

void PipeMemHeapFreeBytes (void)
{
//	WriteParameter (MemHeapFreeBytes, sizeof(void*), pMemHeapFreeBytes);
}

void PipeMemHeapID (void)
{
//	WriteParameter (MemHeapID, sizeof(void*), pMemHeapID);
}	

void PipeMemHeapScramble (void)
{
//	WriteParameter (MemHeapScramble, sizeof(void*), pMemHeapScramble);
}	

void PipeMemHeapSize (void)
{
//	WriteParameter (MemHeapSize, sizeof(void*), pMemHeapSize);
}	

void PipeMemLocalIDKind (void)
{
//	WriteParameter (MemLocalIDKind, sizeof(void*), pMemLocalIDKind);
}

void PipeMemLocaIDToGlobal(void)
{
//	WriteParameter (MemLocaIDToGlobal, sizeof(void*), pMemLocaIDToGlobal);
}	

void PipeMemLocalIDToLockedPtr (void)
{
	WriteParameter (MemLocalIDToLockedPtr, sizeof(void*), pMemLocalIDToLockedPtr);
}
	
void PipeMemLocalIDToPtr (void)
{
//	WriteParameter (MemLocalIDToPtr, sizeof(void*), pMemLocalIDToPtr);
}
	
void PipeMemMove (void)
{
	WriteParameter (MemMove, sizeof(void*), pMemMove);
}	
void PipeMemNumCards (void)
{
	WriteParameter (MemNumCards, sizeof(void*), pMemNumCards);
}	
void PipeMemNumHeaps (void)
{
	WriteParameter (MemNumHeaps, sizeof(void*), pMemNumHeaps);
}	
void PipeMemNumRAMHeaps (void)
{
	WriteParameter (MemNumRAMHeaps, sizeof(void*), pMemNumRAMHeaps);
}	

void PipeMemPtrCardNo (void)
{
//	WriteParameter (MemPtrCardNo, sizeof(void*), pMemPtrCardNo);
}	

void PipeMemPtrDataStorage (void)
{
//	WriteParameter (MemPtrDataStorage, sizeof(void*), pMemPtrDataStorage);
}
	
void PipeMemPtrFree(void)
{
	WriteParameter (MemPtrFree, sizeof(void*), pMemPtrFree);
}	

void PipeMemPtrHeapID (void)
{
//	WriteParameter (MemPtrHeapID, sizeof(void*), pMemPtrHeapID);
}
	
void PipeMemPtrNew(void)
{
	WriteParameter (MemPtrNew, sizeof(void*), pMemPtrNew);
}	

void PipeMemPtrRecoverHandle (void)
{
//	WriteParameter (MemPtrRecoverHandle, sizeof(void*), pMemPtrRecoverHandle);
}
	
void PipeMemPtrResize (void)
{
	WriteParameter (MemPtrResize, sizeof(void*), pMemPtrResize);
}	

void PipeMemPtrSetOwner (void)
{
//	WriteParameter (MemPtrSetOwner, sizeof(void*), pMemPtrSetOwner);
}
	
void PipeMemPtrSize(void)
{
	WriteParameter (MemPtrSize, sizeof(void*), pMemPtrSize);
}	

void PipeMemPtrToLocalID (void)
{
//	WriteParameter (MemPtrToLocalID, sizeof(void*), pMemPtrToLocalID);
}
	
void PipeMemPtrUnlock (void)
{
	WriteParameter (MemPtrUnlock, sizeof(void*), pMemPtrUnlock);
}	
void PipeMemSet(void)
{
	WriteParameter (MemSet, sizeof(void*), pMemSet);
}	
void PipeMemSetDebugMode (void)
{
	WriteParameter (MemSetDebugMode, sizeof(void*), pMemSetDebugMode);
}	

void PipeMemStoreInfo(void)
{
//	WriteParameter (MemStoreInfo, sizeof(void*), pMemStoreInfo);
}

////////////////////////////////////////////////////////////
// Menu Processing Library, completed 14/14 functions now.
////////////////////////////////////////////////////////////
void PipeMenuAddItem (void)
{
	WriteParameter (MenuAddItem, sizeof(void*), pMenuAddItem);
}	

void PipeMenuCmdBarAddButton (void)
{
//	WriteParameter (MenuCmdBarAddButton, sizeof(void*), pMenuCmdBarAddButton);
}
		 
void PipeMenuCmdBarDisplay (void)
{
//	WriteParameter (MenuCmdBarDisplay, sizeof(void*), pMenuCmdBarDisplay);
}
	
void PipeMenuCmdBarGetButtonData (void)
{
//	WriteParameter (MenuCmdBarGetButtonData, sizeof(void*), pMenuCmdBarGetButtonData);
}									 

void PipeMenuDispose (void)
{
	WriteParameter (MenuDispose, sizeof(void*), pMenuDispose);
}	
void PipeMenuDrawMenu (void)
{
	WriteParameter (MenuDrawMenu, sizeof(void*), pMenuDrawMenu);
}	
void PipeMenuEraseStatus (void)
{
	WriteParameter (MenuEraseStatus, sizeof(void*), pMenuEraseStatus);
}	
void PipeMenuGetActiveMenu(void)
{
	WriteParameter (MenuGetActiveMenu, sizeof(void*), pMenuGetActiveMenu);
}	
void PipeMenuHandleEvent(void)
{
	WriteParameter (MenuHandleEvent, sizeof(void*), pMenuHandleEvent);
}	
void PipeMenuHideItem (void)
{
	WriteParameter (MenuHideItem, sizeof(void*), pMenuHideItem);
}	
void PipeMenuInit (void)
{
	WriteParameter (MenuInit, sizeof(void*), pMenuInit);
}
void PipeMenuSetActiveMenu (void)
{
	WriteParameter (MenuSetActiveMenu, sizeof(void*), pMenuSetActiveMenu);
}	

void PipeMenuSetActiveMenuRscID (void)
{
//	WriteParameter (MenuSetActiveMenuRscID, sizeof(void*), pMenuSetActiveMenuRscID);
}
	
void PipeMenuShowItem(void)
{
	WriteParameter (MenuShowItem, sizeof(void*), pMenuShowItem);
}   
   
////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////

void PipeCrc16CalcBlock (void)
{
//	WriteParameter (Crc16CalcBlock, sizeof(void*), pCrc16CalcBlock);
}
void PipeIntlGetRoutineAddress (void)
{
//	WriteParameter (IntlGetRoutineAddress, sizeof(void*), pIntlGetRoutineAddress);
}
void PipeLocGetNumberSeparators(void)
{
//	WriteParameter (LocGetNumberSeparators, sizeof(void*), pLocGetNumberSeparators);
}


////////////////////////////////////////////////////////////
// Modem Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
void PipeMdmDial(void)
{
//	WriteParameter (MdmDial, sizeof(void*), pMdmDial);
}
void PipeMdmHangUp (void)
{
//	WriteParameter (MdmHangUp , sizeof(void*), pMdmHangUp );
}



////////////////////////////////////////////////////////////
// Net Library, completed 43/43 functions now.
////////////////////////////////////////////////////////////

void PipeNetLibAddrAToIN (void)
{
//	WriteParameter (NetLibAddrAToIN, sizeof(void*), pNetLibAddrAToIN);
}
void PipeNetLibAddrINToA (void)
{
//	WriteParameter (NetLibAddrINToA, sizeof(void*), pNetLibAddrINToA);
}
void PipeNetLibClose (void)
{
//	WriteParameter (NetLibClose, sizeof(void*), pNetLibClose);
}
void PipeNetLibGetHostByName (void)
{
//	WriteParameter (NetLibGetHostByName, sizeof(void*), pNetLibGetHostByName);
}
void PipeNetLibOpen (void)
{
//	WriteParameter (NetLibOpen, sizeof(void*), pNetLibOpen);
}
void PipeNetLibSocketClose (void)
{
//	WriteParameter (NetLibSocketClose, sizeof(void*), pNetLibSocketClose);
}
void PipeNetLibSocketConnect (void)
{
//	WriteParameter (NetLibSocketConnect, sizeof(void*), pNetLibSocketConnect);
}

void PipeNetLibSocketOpen(void)
{
//	WriteParameter (NetLibSocketOpen, sizeof(void*), pNetLibSocketOpen);
}


void PipeNetHToNL (void)
{
//	WriteParameter (NetHToNL , sizeof(void*), pNetHToNL );
}
void PipeNetHToNS (void)
{
//	WriteParameter (NetHToNS, sizeof(void*), pNetHToNS);
}
void PipeNetLibConnectionRefresh(void)
{
//	WriteParameter (NetLibConnectionRefresh, sizeof(void*), pNetLibConnectionRefresh);
}
void PipeNetLibDmReceive (void)
{
//	WriteParameter (NetLibDmReceive, sizeof(void*), pNetLibDmReceive);
}
void PipeNetLibFinishCloseWait(void)
{
//	WriteParameter (NetLibFinishCloseWait, sizeof(void*), pNetLibFinishCloseWait);
}
void PipeNetLibGetHostByAddr (void)
{
//	WriteParameter (NetLibGetHostByAddr, sizeof(void*), pNetLibGetHostByAddr);
}
void PipeNetLibGetMailExchangeByName(void)
{
//	WriteParameter (NetLibGetMailExchangeByName, sizeof(void*), pNetLibGetMailExchangeByName);
}
void PipeNetLibGetServByName (void)
{
//	WriteParameter (NetLibGetServByName, sizeof(void*), pNetLibGetServByName);
}
void PipeNetLibIFAttach (void)
{
//	WriteParameter (NetLibIFAttach, sizeof(void*), pNetLibIFAttach);
}
void PipeNetLibIFDetach (void)
{
//	WriteParameter (NetLibIFDetach, sizeof(void*), pNetLibIFDetach);
}
void PipeNetLibIFDown (void)
{
//	WriteParameter (NetLibIFDown , sizeof(void*), pNetLibIFDown );
}
void PipeNetLibIFGet (void)
{
//	WriteParameter (NetLibIFGet, sizeof(void*), pNetLibIFGet);
}
void PipeNetLibIFSettingGet (void)
{
//	WriteParameter (NetLibIFSettingGet, sizeof(void*), pNetLibIFSettingGet);
}
void PipeNetLibIFSettingSet (void)
{
//	WriteParameter (NetLibIFSettingSet, sizeof(void*), pNetLibIFSettingSet);
}
void PipeNetLibIFUp (void)
{
//	WriteParameter (NetLibIFUp, sizeof(void*), pNetLibIFUp);
}
void PipeNetLibMaster(void)
{
//	WriteParameter (NetLibMaster, sizeof(void*), pNetLibMaster);
}
void PipeNetLibOpenCount (void)
{
//	WriteParameter (NetLibOpenCount, sizeof(void*), pNetLibOpenCount);
}
void PipeNetLibReceive (void)
{
//	WriteParameter (NetLibReceive , sizeof(void*), pNetLibReceive );
}
void PipeNetLibReceivePB (void)
{
//	WriteParameter (NetLibReceivePB, sizeof(void*), pNetLibReceivePB);
}
void PipeNetLibSelect (void)
{
//	WriteParameter (NetLibSelect , sizeof(void*), pNetLibSelect );
}
void PipeNetLibSend (void)
{
//	WriteParameter (NetLibSend, sizeof(void*), pNetLibSend);
}
void PipeNetLibSendPB (void)
{
//	WriteParameter (NetLibSendPB, sizeof(void*), pNetLibSendPB);
}
void PipeNetLibSettingGet(void)
{
//	WriteParameter (NetLibSettingGet, sizeof(void*), pNetLibSettingGet);
}
void PipeNetLibSettingSet (void)
{
//	WriteParameter (NetLibSettingSet, sizeof(void*), pNetLibSettingSet);
}
void PipeNetLibSocketAccept (void)
{
//	WriteParameter (NetLibSocketAccept, sizeof(void*), pNetLibSocketAccept);
}
void PipeNetLibSocketAddr(void)
{
//	WriteParameter (NetLibSocketAddr, sizeof(void*), pNetLibSocketAddr);
}
void PipeNetLibSocketBind (void)
{
//	WriteParameter (NetLibSocketBind, sizeof(void*), pNetLibSocketBind);
}
void PipeNetLibSocketListen (void)
{
//	WriteParameter (NetLibSocketListen , sizeof(void*), pNetLibSocketListen );
}
void PipeNetLibSocketOptionGet(void)
{
//	WriteParameter (NetLibSocketOptionGet, sizeof(void*), pNetLibSocketOptionGet);
}
void PipeNetLibSocketOptionSet(void)
{
//	WriteParameter (NetLibSocketOptionSet, sizeof(void*), pNetLibSocketOptionSet);
}
void PipeNetLibSocketShutdown(void)
{
//	WriteParameter (NetLibSocketShutdown, sizeof(void*), pNetLibSocketShutdown);
}
void PipeNetLibTracePrintF(void)
{
//	WriteParameter (NetLibTracePrintF, sizeof(void*), pNetLibTracePrintF);
}
void PipeNetLibTracePutS (void)
{
//	WriteParameter (NetLibTracePutS , sizeof(void*), pNetLibTracePutS );
}
void PipeNetNToHL (void)
{
//	WriteParameter (NetNToHL, sizeof(void*), pNetNToHL);
}
void PipeNetNToHS (void)
{
//	WriteParameter (NetNToHS, sizeof(void*), pNetNToHS);
}

////////////////////////////////////////////////////////////
// Network Utilities Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeNetUReadN (void)
{
//	WriteParameter (NetUReadN , sizeof(void*), pNetUReadN  );
}
void PipeNetUTCPOpen (void)
{
//	WriteParameter (NetUTCPOpen, sizeof(void*), pNetUTCPOpen);
}
void PipeNetUWriteN(void)
{
//	WriteParameter (NetUWriteN, sizeof(void*), pNetUWriteN);
}



