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
// DataBase Library, completed 66/66 functions now.
////////////////////////////////////////////////////////////

void PipeDmArchiveRecord (void)
{
//	WriteParameter (DmArchiveRecord, sizeof(void*), pDmArchiveRecord);
}

void PipeDmAttachRecord (void)
{
//	WriteParameter (DmAttachRecord, sizeof(void*), pDmAttachRecord);
}

void PipeDmAttachResource (void)
{
//	WriteParameter (DmAttachResource, sizeof(void*), pDmAttachResource);
}

void PipeDmCloseDatabase (void)
{
	WriteParameter (DmCloseDatabase, sizeof(void*), pDmCloseDatabase);
}

void PipeDmCreateDatabase (void)
{
	WriteParameter (DmCreateDatabase, sizeof(void*), pDmCreateDatabase);
}

void PipeDmCreateDatabaseFromImage (void)
{
//	WriteParameter (DmCreateDatabaseFromImage , sizeof(void*), pDmCreateDatabaseFromImage);
}

void PipeDmDatabaseInfo (void)
{
	WriteParameter (DmDatabaseInfo, sizeof(void*), pDmDatabaseInfo);
}

void PipeDmDatabaseProtect (void)
{
//	WriteParameter (DmDatabaseProtect, sizeof(void*), pDmDatabaseProtect);
}

void PipeDmDatabaseSize (void)
{
	WriteParameter (DmDatabaseSize, sizeof(void*), pDmDatabaseSize);
}

void PipeDmDeleteCategory (void)
{
	WriteParameter (DmDeleteCategory, sizeof(void*), pDmDeleteCategory);
}

void PipeDmDeleteDatabase (void)
{
//	WriteParameter (DmDeleteDatabase, sizeof(void*), pDmDeleteDatabase);
}

void PipeDmDeleteRecord (void)
{
	WriteParameter (DmDeleteRecord, sizeof(void*), pDmDeleteRecord);
}

void PipeDmDetachRecord (void)
{
//	WriteParameter (DmDetachRecord, sizeof(void*), pDmDetachRecord);
}

void PipeDmDetachResource (void)
{
//	WriteParameter (DmDetachResource, sizeof(void*), pDmDetachResource);
}

void PipeDmFindDatabase (void)
{
//	WriteParameter (DmFindDatabase, sizeof(void*), pDmFindDatabase);
}

void PipeDmFindRecordByID(void)
{
//	WriteParameter (DmFindRecordByID, sizeof(void*), pDmFindRecordByID);
}

void PipeDmFindResource (void)
{
//	WriteParameter (DmFindResource, sizeof(void*), pDmFindResource);
}

void PipeDmFindResourceType (void)
{
//	WriteParameter (DmFindResourceType, sizeof(void*), pDmFindResourceType);
}

void PipeDmFindSortPosition (void)
{
//	WriteParameter (DmFindSortPosition, sizeof(void*), pDmFindSortPosition);
}
void PipeDmFindSortPositionV10 (void)
{
//	WriteParameter (DmFindSortPositionV10, sizeof(void*), pDmFindSortPositionV10);
}
void PipeDmGetAppInfoID (void)
{
//	WriteParameter (DmGetAppInfoID, sizeof(void*), pDmGetAppInfoID);
}

void PipeDmGetDatabase (void)
{
	WriteParameter (DmGetDatabase, sizeof(void*), pDmGetDatabase);
}

void PipeDmGetDatabaseLocalState (void)
{
//	WriteParameter (DmGetDatabaseLocalState, sizeof(void*), pDmGetDatabaseLocalState);
}

void PipeDmGetLastErr (void)
{
//	WriteParameter (DmGetLastErr, sizeof(void*), pDmGetLastErr);
}

void PipeDmGetNextDatabaseByTypeCreator (void)
{
	WriteParameter (DmGetNextDatabaseByTypeCreator, sizeof(void*), pDmGetNextDatabaseByTypeCreator);
}

void PipeDmGetRecord (void)
{
	WriteParameter (DmGetRecord, sizeof(void*), pDmGetRecord);
}

void PipeDmGetResource(void)
{
//	WriteParameter (DmGetResource, sizeof(void*), pDmGetResource);
}

void PipeDmGetResourceIndex(void)
{
//	WriteParameter (DmGetResourceIndex, sizeof(void*), pDmGetResourceIndex);
}

void PipeDmGet1Resource (void)
{
	WriteParameter (DmGet1Resource, sizeof(void*), pDmGet1Resource);
}

void PipeDmInsertionSort (void)
{
	WriteParameter (DmInsertionSort, sizeof(void*), pDmInsertionSort);
}

void PipeDmMoveCategory (void)
{
	WriteParameter (DmMoveCategory, sizeof(void*), pDmMoveCategory);
}

void PipeDmMoveRecord (void)
{
	WriteParameter (DmMoveRecord, sizeof(void*), pDmMoveRecord);
}

void PipeDmNewHandle(void)
{
	WriteParameter (DmNewHandle, sizeof(void*), pDmNewHandle);
}

void PipeDmNewRecord (void)
{
	WriteParameter (DmNewRecord, sizeof(void*), pDmNewRecord);
}

void PipeDmNewResource (void)
{
//	WriteParameter (DmNewResource, sizeof(void*), pDmNewResource);
}

void PipeDmNextOpenDatabase (void)
{
//	WriteParameter (DmNextOpenDatabase , sizeof(void*), pDmNextOpenDatabase);
}

void PipeDmNumDatabases (void)
{
	WriteParameter (DmNumDatabases, sizeof(void*), pDmNumDatabases);
}

void PipeDmNumRecords (void)
{
	WriteParameter (DmNumRecords, sizeof(void*), pDmNumRecords);
}

void PipeDmNumRecordsInCategory (void)
{
	WriteParameter (DmNumRecordsInCategory, sizeof(void*), pDmNumRecordsInCategory);
}

void PipeDmNumResources (void)
{
//	WriteParameter (DmNumResources, sizeof(void*), pDmNumResources);
}

void PipeDmOpenDatabase (void)
{
//	WriteParameter (DmOpenDatabase, sizeof(void*), pDmOpenDatabase);
}

void PipeDmOpenDatabaseByTypeCreator(void)
{
	WriteParameter (DmOpenDatabaseByTypeCreator, sizeof(void*), pDmOpenDatabaseByTypeCreator);
}

void PipeDmOpenDatabaseInfo (void)
{
	WriteParameter (DmOpenDatabaseInfo, sizeof(void*), pDmOpenDatabaseInfo);
}

void PipeDmOpenDBNoOvelay(void)
{
//	WriteParameter (DmOpenDBNoOvelay, sizeof(void*), pDmOpenDBNoOvelay);
}

void PipeDmPositionInCategory (void)
{
	WriteParameter (DmPositionInCategory, sizeof(void*), pDmPositionInCategory);
}

void PipeDmQueryNextInCategory (void)
{
//	WriteParameter (DmQueryNextInCategory, sizeof(void*), pDmQueryNextInCategory);
}

void PipeDmQueryRecord (void)
{
	WriteParameter (DmQueryRecord, sizeof(void*), pDmQueryRecord);
}

void PipeDmQuickSort(void)
{
//	WriteParameter (DmQuickSort, sizeof(void*), pDmQuickSort);
}

void PipeDmRecordInfo (void)
{
	WriteParameter (DmRecordInfo, sizeof(void*), pDmRecordInfo);
}

void PipeDmReleaseRecord (void)
{
	WriteParameter (DmReleaseRecord, sizeof(void*), pDmReleaseRecord);
}

void PipeDmReleaseResource (void)
{
	WriteParameter (DmReleaseResource, sizeof(void*), pDmReleaseResource);
}

void PipeDmRemoveRecord (void)
{
	WriteParameter (DmRemoveRecord, sizeof(void*), pDmRemoveRecord);
}

void PipeDmRemoveResource (void)
{
//	WriteParameter (DmRemoveResource, sizeof(void*), pDmRemoveResource);
}

void PipeDmRemoveSecretRecord (void)
{
//	WriteParameter (DmRemoveSecretRecord, sizeof(void*), pDmRemoveSecretRecord);
}

void PipeDmResizeRecord (void)
{
	WriteParameter (DmResizeRecord, sizeof(void*), pDmResizeRecord);
}

void PipeDmResizeResource (void)
{
//	WriteParameter (DmResizeResource, sizeof(void*), pDmResizeResource);
}

void PipeDmResourceInfo (void)
{
//	WriteParameter (DmResourceInfo, sizeof(void*), pDmResourceInfo);
}

void PipeDmResetRecordStates(void)
{
	WriteParameter (DmResetRecordStates, sizeof(void*), pDmResetRecordStates);
}

void PipeDmSearchRecord (void)
{
//	WriteParameter (DmSearchRecord, sizeof(void*), pDmSearchRecord);
}
void PipeDmSearchResource (void)
{
//	WriteParameter (DmSearchResource, sizeof(void*), pDmSearchResource);
}

void PipeDmSeekRecordInCategory (void)
{
	WriteParameter (DmSeekRecordInCategory, sizeof(void*), pDmSeekRecordInCategory);
}

void PipeDmSet (void)
{
	WriteParameter (DmSet, sizeof(void*), pDmSet);
}

void PipeDmSetDatabaseInfo (void)
{
	WriteParameter (DmSetDatabaseInfo, sizeof(void*), pDmSetDatabaseInfo);
}

void PipeDmSetRecordInfo (void)
{
	WriteParameter (DmSetRecordInfo, sizeof(void*), pDmSetRecordInfo);
}

void PipeDmSetResourceInfo (void)
{
//	WriteParameter (DmSetResourceInfo, sizeof(void*), pDmSetResourceInfo);
}

void PipeDmStrCopy(void)
{
	WriteParameter (DmStrCopy, sizeof(void*), pDmStrCopy);
}

void PipeDmWrite (void)
{
	WriteParameter (DmWrite, sizeof(void*), pDmWrite);
}

void PipeDmWriteCheck (void)
{
//	WriteParameter (DmWriteCheck, sizeof(void*), pDmWriteCheck);
}


////////////////////////////////////////////////////////////
// Error Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeErrFatalDisplayIf (void)
{
	WriteParameter (ErrFatalDisplayIf, sizeof(void*), pErrFatalDisplayIf);
}
void PipeErrFatalDisplay (void)
{
	WriteParameter (ErrFatalDisplay, sizeof(void*), pErrFatalDisplay);
}

void PipeErrNonFatalDisplayIf (void)
{
	WriteParameter (ErrNonFatalDisplayIf, sizeof(void*), pErrNonFatalDisplayIf);
}

void PipeErrAlert(void)
{
//	WriteParameter (ErrAlert, sizeof(void*), pErrAlert);
}
void PipeErrDisplayFileLineMsg (void)
{
//	WriteParameter (ErrDisplayFileLineMsg, sizeof(void*), pErrDisplayFileLineMsg);
}
void PipeErrThrow (void)
{
//	WriteParameter (ErrThrow, sizeof(void*), pErrThrow);
}



////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipeExgAccept (void)
{
//	WriteParameter (ExgAccept, sizeof(void*), pExgAccept);
}
void PipeExgDBRead(void)
{
//	WriteParameter (ExgDBRead, sizeof(void*), pExgDBRead);
}
void PipeExgDBWrite (void)
{
//	WriteParameter (ExgDBWrite, sizeof(void*), pExgDBWrite);
}
void PipeExgDisconnect (void)
{
//	WriteParameter (ExgDisconnect , sizeof(void*), pExgDisconnect );
}
void PipeExgDoDialog (void)
{
//	WriteParameter (ExgDoDialog, sizeof(void*), pExgDoDialog);
}
void PipeExgPut (void)
{
//	WriteParameter (ExgPut, sizeof(void*), pExgPut);
}
void PipeExgReceive(void)
{
//	WriteParameter (ExgReceive, sizeof(void*), pExgReceive);
}
void PipeExgRegisterData(void)
{
//	WriteParameter (ExgRegisterData, sizeof(void*), pExgRegisterData);
}
void PipeExgSend (void)
{
//	WriteParameter (ExgSend, sizeof(void*), pExgSend);
}



////////////////////////////////////////////////////////////
// Feature Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////
void PipeFtrGet (void)
{
	WriteParameter (FtrGet, sizeof(void*), pFtrGet);
}

void PipeFtrGetByIndex(void)
{
//	WriteParameter (FtrGetByIndex, sizeof(void*), pFtrGetByIndex);
}
void PipeFtrPtrFree(void)
{
//	WriteParameter (FtrPtrFree, sizeof(void*), pFtrPtrFree);
}
void PipeFtrPtrNew (void)
{
//	WriteParameter (FtrPtrNew, sizeof(void*), pFtrPtrNew);
}
void PipeFtrPtrResize (void)
{
//	WriteParameter (FtrPtrResize, sizeof(void*), pFtrPtrResize);
}
void PipeFtrSet (void)
{
//	WriteParameter (FtrSet , sizeof(void*), pFtrSet );
}
void PipeFtrUnregister (void)
{
//	WriteParameter (FtrUnregister, sizeof(void*), pFtrUnregister);
}

