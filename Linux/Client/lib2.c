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
// DataBase Library, completed 68/68 functions now.
////////////////////////////////////////////////////////////
#ifdef L_DmArchiveRecord
Err DmArchiveRecord (DmOpenRef dbP, UInt16 index)
{
	Err (*DmArchiveRecordP) (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmArchiveRecordP, sizeof(void *), pDmArchiveRecord);
	return (*DmArchiveRecordP) ( dbP,  index);
}
#endif

#ifdef L_DmAttachRecord
Err DmAttachRecord (DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP)
{
	Err (*DmAttachRecordP) (DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP);

	GetParameter (&DmAttachRecordP, sizeof(void *), pDmAttachRecord);
	return (*DmAttachRecordP) ( dbP, atP,  newH, oldHP);
}
#endif

#ifdef L_DmAttachResource
Err DmAttachResource (DmOpenRef dbP, MemHandle newH, DmResType resType, DmResID resID)
{
	Err (*DmAttachResourceP) (DmOpenRef dbP, MemHandle newH, DmResType resType, DmResID resID);

	GetParameter (&DmAttachResourceP, sizeof(void *), pDmAttachResource);
	return (*DmAttachResourceP) ( dbP,  newH,  resType,  resID);
}
#endif

#ifdef L_DmCloseDatabase
Err DmCloseDatabase (DmOpenRef dbP)
{
	Err (*DmCloseDatabaseP) (DmOpenRef dbP);

	GetParameter (&DmCloseDatabaseP, sizeof(void *), pDmCloseDatabase);
	return (*DmCloseDatabaseP) ( dbP);
}
#endif

#ifdef L_DmCreateDatabase
Err DmCreateDatabase (UInt16 cardNo, const Char *nameP, UInt32 creator,
					  UInt32 type, Boolean resDB)
{
	Err (*DmCreateDatabaseP) (UInt16 cardNo, const Char *nameP, UInt32 creator,UInt32 type, Boolean resDB);

	GetParameter (&DmCreateDatabaseP, sizeof(void *), pDmCreateDatabase);
	return (*DmCreateDatabaseP) ( cardNo,  nameP,  creator, type,  resDB);
}
#endif

#ifdef L_DmCreateDatabaseFromImage
Err DmCreateDatabaseFromImage (MemPtr bufferP)
{
	Err (*DmCreateDatabaseFromImageP) (MemPtr bufferP);

	GetParameter (&DmCreateDatabaseFromImageP, sizeof(void *), pDmCreateDatabaseFromImage);
	return (*DmCreateDatabaseFromImageP) ( bufferP);
}
#endif

#ifdef L_DmDatabaseInfo
Err DmDatabaseInfo (UInt16 cardNo, LocalID dbID, Char *nameP, UInt16 *attributesP,
					UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP,
					UInt32 *typeP, UInt32 *creatorP)
{
	Err (*DmDatabaseInfoP) (UInt16 cardNo, LocalID dbID, Char *nameP, UInt16 *attributesP,
					UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP,
					UInt32 *typeP, UInt32 *creatorP);

	GetParameter (&DmDatabaseInfoP, sizeof(void *), pDmDatabaseInfo);
	return (*DmDatabaseInfoP) ( cardNo,  dbID, nameP, attributesP,
					versionP, crDateP, modDateP, bckUpDateP,
					modNumP, appInfoIDP, sortInfoIDP,
					typeP, creatorP);
}
#endif

#ifdef L_DmDatabaseProtect
Err DmDatabaseProtect (UInt16 cardNo, LocalID dbID, Boolean protect)
{
	Err (*DmDatabaseProtectP) (UInt16 cardNo, LocalID dbID, Boolean protect);
	
	GetParameter (&DmDatabaseProtectP, sizeof(void *), pDmDatabaseProtect);
	return (*DmDatabaseProtectP) ( cardNo,  dbID,  protect);
}
#endif

#ifdef L_DmDatabaseSize
Err DmDatabaseSize (UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP)
{
	Err (*DmDatabaseSizeP) (UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP);

	GetParameter (&DmDatabaseSizeP, sizeof(void *), pDmDatabaseSize);
	return (*DmDatabaseSizeP) ( cardNo,  dbID, numRecordsP,
					totalBytesP, dataBytesP);
}
#endif

#ifdef L_DmDeleteCategory
Err DmDeleteCategory (DmOpenRef dbp, UInt16 categoryNum)
{
	Err (*DmDeleteCategoryP) (DmOpenRef dbp, UInt16 categoryNum);

	GetParameter (&DmDeleteCategoryP, sizeof(void *), pDmDeleteCategory);
	return (*DmDeleteCategoryP) ( dbp,  categoryNum);
}
#endif

#ifdef L_DmDeleteDatabase
Err DmDeleteDatabase (UInt16 cardNo, LocalID dbID)
{
	Err (*DmDeleteDatabaseP) (UInt16 cardNo, LocalID dbID);
	
	GetParameter (&DmDeleteDatabaseP, sizeof(void *), pDmDeleteDatabase);
	return (*DmDeleteDatabaseP) ( cardNo,  dbID);
}
#endif

#ifdef L_DmDeleteRecord
Err DmDeleteRecord (DmOpenRef dbp, UInt16 index)
{
	Err (*DmDeleteRecordP) (DmOpenRef dbp, UInt16 index);

	GetParameter (&DmDeleteRecordP, sizeof(void *), pDmDeleteRecord);
	return (*DmDeleteRecordP) ( dbp,  index);
}
#endif

#ifdef L_DmDetachRecord
Err DmDetachRecord (DmOpenRef dbp, UInt16 index, MemHandle *oldHP)
{
	Err (*DmDetachRecordP) (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);

	GetParameter (&DmDetachRecordP, sizeof(void *), pDmDetachRecord);
	return (*DmDetachRecordP) ( dbp,  index, oldHP);
}
#endif

#ifdef L_DmDetachResource
Err DmDetachResource (DmOpenRef dbp, UInt16 index, MemHandle *oldHP)
{
	Err (*DmDetachResourceP) (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);

	GetParameter (&DmDetachResourceP, sizeof(void *), pDmDetachResource);
	return (*DmDetachResourceP) ( dbp,  index, oldHP);
}
#endif

#ifdef L_DmFindDatabase
Err DmFindDatabase (UInt16 cardNo, const Char *nameP)
{
	Err (*DmFindDatabaseP) (UInt16 cardNo, const Char *nameP);

	GetParameter (&DmFindDatabaseP, sizeof(void *), pDmFindDatabase);
	return (*DmFindDatabaseP) ( cardNo,  nameP);
}
#endif

#ifdef L_DmFindRecordByID
Err DmFindRecordByID (DmOpenRef dbp, UInt32 uniqueID, UInt16 *indexP)
{
	Err (*DmFindRecordByIDP) (DmOpenRef dbp, UInt32 uniqueID, UInt16 *indexP);

	GetParameter (&DmFindRecordByIDP, sizeof(void *), pDmFindRecordByID);
	return (*DmFindRecordByIDP) ( dbp,  uniqueID, indexP);
}
#endif

#ifdef L_DmFindResource
Err DmFindResource (DmOpenRef dbp, DmResType resType, DmResID resID, MemHandle resH)
{
	Err (*DmFindResourceP) (DmOpenRef dbp, DmResType resType, DmResID resID, MemHandle resH);

	GetParameter (&DmFindResourceP, sizeof(void *), pDmFindResource);
	return (*DmFindResourceP) ( dbp,  resType,  resID,  resH);
}
#endif

#ifdef L_DmFindResourceType
UInt16 DmFindResourceType (DmOpenRef dbp, DmResType resType, UInt16 typeIndex)
{
	UInt16 (*DmFindResourceTypeP) (DmOpenRef dbp, DmResType resType, UInt16 typeIndex);

	GetParameter (&DmFindResourceTypeP, sizeof(void *), pDmFindResourceType);
	return (*DmFindResourceTypeP) ( dbp,  resType,  typeIndex);
}
#endif

#ifdef L_DmFindSortPosition
UInt16 DmFindSortPosition (DmOpenRef dbP, void *newRecord, SortRecordInfoPtr newRecordInfo,
						   DmComparF *compar, Int16 other)
{
	UInt16 (*DmFindSortPositionP) (DmOpenRef dbP, void *newRecord, SortRecordInfoPtr newRecordInfo,
						   DmComparF *compar, Int16 other);

	GetParameter (&DmFindSortPositionP, sizeof(void *), pDmFindSortPosition);
	return (*DmFindSortPositionP) ( dbP, newRecord,  newRecordInfo,
						   compar,  other);
}
#endif

#ifdef L_DmFindSortPositionV10
UInt16		DmFindSortPositionV10(DmOpenRef dbP, void *newRecord,
					DmComparF *compar, Int16 other)
{
	UInt16 (*DmFindSortPositionP) (DmOpenRef dbP, void *newRecord, SortRecordInfoPtr newRecordInfo,
						   DmComparF *compar, Int16 other);

	GetParameter (&DmFindSortPositionV10P, sizeof(void *), pDmFindSortPositionV10);
	return (*DmFindSortPositionV10P) ( dbP, newRecord,  newRecordInfo,
						   compar,  other);
}
#endif


#ifdef L_DmGetAppInfoID
LocalID DmGetAppInfoID (DmOpenRef dbP)
{
	LocalID (*DmGetAppInfoIDP) (DmOpenRef dbP);

	GetParameter (&DmGetAppInfoIDP, sizeof(void *), pDmGetAppInfoID);
	return (*DmGetAppInfoIDP) ( dbP);
}
#endif

#ifdef L_DmGetDatabase
LocalID DmGetDatabase (UInt16 cardNo, UInt16 index)
{
	LocalID (*DmGetDatabaseP) (UInt16 cardNo, UInt16 index);

	GetParameter (&DmGetDatabaseP, sizeof(void *), pDmGetDatabase);
	return (*DmGetDatabaseP) ( cardNo,  index);
}
#endif

#ifdef L_DmGetDatabaseLocaState
void DmGetDatabaseLocaState (DmOpenRef dbR, UInt8 *highest, UInt32 *count, UInt32 *busy)
{
	void (*DmGetDatabaseLocaStateP) (DmOpenRef dbR, UInt8 *highest, UInt32 *count, UInt32 *busy);

	GetParameter (&DmGetDatabaseLocaStateP, sizeof(void *), pDmGetDatabaseLocaState);
	return (*DmGetDatabaseLocaStateP) ( dbR, highest, count, busy);
}
#endif

#ifdef L_DmGetLastErr
Err DmGetLastErr (void)
{
	Err (*DmGetLastErrP) (void);

	GetParameter (&DmGetLastErrP, sizeof(void *), pDmGetLastErr);
	return (*DmGetLastErrP) ();
}
#endif

#ifdef L_DmGetNextDatabaseByTypeCreator
Err DmGetNextDatabaseByTypeCreator (Boolean newSearch, DmSearchStatePtr stateInfoP, 
												UInt32 type, UInt32 creator, Boolean onlyLatesVers, 
												UInt16 *cardNoP, LocalID *dbIDP)
{
	Err (*DmGetNextDatabaseByTypeCreatorP) (Boolean newSearch, DmSearchStatePtr stateInfoP, 
												UInt32 type, UInt32 creator, Boolean onlyLatesVers, 
												UInt16 *cardNoP, LocalID *dbIDP);

	GetParameter (&DmGetNextDatabaseByTypeCreatorP, sizeof(void *), pDmGetNextDatabaseByTypeCreator);
	return (*DmGetNextDatabaseByTypeCreatorP) ( newSearch,  stateInfoP, type,  creator,  onlyLatesVers, 
												cardNoP, dbIDP);
}
#endif

#ifdef L_DmGetRecord
MemHandle DmGetRecord (DmOpenRef dbP, UInt16 index)
{
	MemHandle (*DmGetRecordP) (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmGetRecordP, sizeof(void *), pDmGetRecord);
	return (*DmGetRecordP) ( dbP,  index);
}
#endif

#ifdef L_DmGetResource
MemHandle DmGetResource (DmResType type, DmResID resID)
{
	MemHandle (*DmGetResourceP) (DmResType type, DmResID resID);

	GetParameter (&DmGetResourceP, sizeof(void *), pDmGetResource);
	return (*DmGetResourceP) ( type,  resID);
}
#endif

#ifdef L_DmGetResourceIndex
MemHandle DmGetResourceIndex (DmOpenRef dbP, UInt16 index)
{
	MemHandle(*DmGetResourceIndexP)  (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmGetResourceIndexP, sizeof(void *), pDmGetResourceIndex);
	return(*DmGetResourceIndexP)  ( dbP,  index);
}
#endif

#ifdef L_DmGet1Resource
MemHandle DmGet1Resource (DmResType type, DmResID resID)
{
	MemHandle (*DmGet1ResourceP) (DmResType type, DmResID resID);
	
	GetParameter (&DmGet1ResourceP, sizeof(void *), pDmGet1Resource);
	return (*DmGet1ResourceP) ( type,  resID);
}
#endif

#ifdef L_DmInsertionSort
Err DmInsertionSort (DmOpenRef dbR, DmComparF *compar, Int16 other)
{
	Err (*DmInsertionSortP) (DmOpenRef dbR, DmComparF *compar, Int16 other);

	GetParameter (&DmInsertionSortP, sizeof(void *), pDmInsertionSort);
	return (*DmInsertionSortP) ( dbR, compar,  other);
}
#endif

#ifdef L_DmMoveCategory
Err DmMoveCategory (DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty)
{
	Err (*DmMoveCategoryP) (DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty);

	GetParameter (&DmMoveCategoryP, sizeof(void *), pDmMoveCategory);
	return (*DmMoveCategoryP) ( dbP,  toCategory,  fromCategory,  dirty);
}
#endif

#ifdef L_DmMoveRecord
Err DmMoveRecord (DmOpenRef dbP, UInt16 from, UInt16 to)
{
	Err (*DmMoveRecordP) (DmOpenRef dbP, UInt16 from, UInt16 to);

	GetParameter (&DmMoveRecordP, sizeof(void *), pDmMoveRecord);
	return (*DmMoveRecordP) ( dbP,  from,  to);
}
#endif

#ifdef L_DmNewHandle
MemHandle DmNewHandle (DmOpenRef dbP, UInt32 size)
{
	MemHandle (*DmNewHandleP) (DmOpenRef dbP, UInt32 size);

	GetParameter (&DmNewHandleP, sizeof(void *), pDmNewHandle);
	return (*DmNewHandleP) ( dbP,  size);
}
#endif

#ifdef L_DmNewRecord
MemHandle DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size)
{
	MemHandle (*DmNewRecordP) (DmOpenRef dbP, UInt16 *atP, UInt32 size);

	GetParameter (&DmNewRecordP, sizeof(void *), pDmNewRecord);
	return	(*DmNewRecordP) ( dbP, atP,  size);
}
#endif

#ifdef L_DmNewReresource
MemHandle DmNewReresource (DmOpenRef dbP, DmResType resType, DmResID resID, UInt32 size)
{
	MemHandle (*DmNewReresourceP) (DmOpenRef dbP, DmResType resType, DmResID resID, UInt32 size);

	GetParameter (&DmNewReresourceP, sizeof(void *), pDmNewReresource);
	return (*DmNewReresourceP) ( dbP,  resType,  resID,  size);
}
#endif

#ifdef L_DmNextOpenDatabase
DmOpenRef DmNextOpenDatabase (DmOpenRef currentP)
{
	DmOpenRef (*DmNextOpenDatabaseP) (DmOpenRef currentP);

	GetParameter (&DmNextOpenDatabaseP, sizeof(void *), pDmNextOpenDatabase);
	return (*DmNextOpenDatabaseP) ( currentP);
}
#endif

#ifdef L_DmNumDatabases
UInt16 DmNumDatabases (UInt16 cardNo)
{
	UInt16 (*DmNumDatabasesP) (UInt16 cardNo);

	GetParameter (&DmNumDatabasesP, sizeof(void *), pDmNumDatabases);
	return (*DmNumDatabasesP) ( cardNo);
}
#endif

#ifdef L_DmNumRecords
UInt16 DmNumRecords (DmOpenRef dbP)
{
	UInt16 (*DmNumRecordsP) (DmOpenRef dbP);

	GetParameter (&DmNumRecordsP, sizeof(void *), pDmNumRecords);
	return (*DmNumRecordsP) (dbP);
}
#endif

#ifdef L_DmNumRecordsInCategory
UInt16 DmNumRecordsInCategory (DmOpenRef dbP, UInt16 category)
{
	UInt16 (*DmNumRecordsInCategoryP) (DmOpenRef dbP, UInt16 category);

	GetParameter (&DmNumRecordsInCategoryP, sizeof(void *), pDmNumRecordsInCategory);
	return (*DmNumRecordsInCategoryP) ( dbP,  category);
}
#endif

#ifdef L_DmNumResources
UInt16 DmNumResources (DmOpenRef dbP)
{
	UInt16 (*DmNumResourcesP) (DmOpenRef dbP);

	GetParameter (&DmNumResourcesP, sizeof(void *), pDmNumResources);
	return (*DmNumResourcesP) (dbP);
}
#endif

#ifdef L_DmOpenDatabase
DmOpenRef DmOpenDatabase (UInt32 cardNo, LocalID dbID, UInt16 mode)
{
	DmOpenRef (*DmOpenDatabaseP) (UInt32 cardNo, LocalID dbID, UInt16 mode);

	GetParameter (&DmOpenDatabaseP, sizeof(void *), pDmOpenDatabase);
	return (*DmOpenDatabaseP) ( cardNo,  dbID,  mode);
}
#endif

#ifdef L_DmOpenDatabaseByTypeCreator
DmOpenRef DmOpenDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode)
{
	DmOpenRef (*DmOpenDatabaseByTypeCreatorP) (UInt32 type, UInt32 creator, UInt16 mode);

	GetParameter (&DmOpenDatabaseByTypeCreatorP, sizeof(void *), pDmOpenDatabaseByTypeCreator);
	return (*DmOpenDatabaseByTypeCreatorP) ( type,  creator,  mode);
}
#endif

#ifdef L_DmOpenDatabaseInfo
Err DmOpenDatabaseInfo (DmOpenRef dbP, LocalID *dbIDP, UInt16 *openCountP, UInt16 *modeP,
						UInt16 *cardNoP, Boolean *resDBP)
{
	Err (*DmOpenDatabaseInfoP) (DmOpenRef dbP, LocalID *dbIDP, UInt16 *openCountP, UInt16 *modeP,
						UInt16 *cardNoP, Boolean *resDBP);

	GetParameter (&DmOpenDatabaseInfoP, sizeof(void *), pDmOpenDatabaseInfo);
	return (*DmOpenDatabaseInfoP) ( dbP, dbIDP, openCountP, modeP,
						cardNoP, resDBP);
}
#endif

#ifdef L_DmOpenDBNoOvelay
DmOpenRef DmOpenDBNoOvelay (UInt32 cardNo, LocalID dbID, UInt16 mode)
{
	DmOpenRef (*DmOpenDBNoOvelayP) (UInt32 cardNo, LocalID dbID, UInt16 mode);

	GetParameter (&DmOpenDBNoOvelayP, sizeof(void *), pDmOpenDBNoOvelay);
	return (*DmOpenDBNoOvelayP) ( cardNo,  dbID,  mode);
}
#endif

#ifdef L_DmPositionInCategory
UInt16 DmPositionInCategory (DmOpenRef dbP, UInt16 index, UInt16 category)
{
	UInt16 (*DmPositionInCategoryP) (DmOpenRef dbP, UInt16 index, UInt16 category);

	GetParameter (&DmPositionInCategoryP, sizeof(void *), pDmPositionInCategory);
	return (*DmPositionInCategoryP) ( dbP,  index,  category);
}
#endif

#ifdef L_DmQueryNextInCategory
MemHandle DmQueryNextInCategory (DmOpenRef dbP, UInt16 *indexP, UInt16 category)
{
	MemHandle (*DmQueryNextInCategoryP) (DmOpenRef dbP, UInt16 *indexP, UInt16 category);

	GetParameter (&DmQueryNextInCategoryP, sizeof(void *), pDmQueryNextInCategory);
	return (*DmQueryNextInCategoryP) ( dbP, indexP,  category);
}
#endif

#ifdef L_DmQueryRecord
MemHandle DmQueryRecord (DmOpenRef dbP, UInt16 index)
{
	MemHandle (*DmQueryRecordP) (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmQueryRecordP, sizeof(void *), pDmQueryRecord);
	return (*DmQueryRecordP) ( dbP,  index);
}
#endif

#ifdef L_DmQuickSort
Err DmQuickSort (DmOpenRef dbP, DmComparF *compar, Int16 other)
{
	Err (*DmQuickSortP) (DmOpenRef dbP, DmComparF *compar, Int16 other);

	GetParameter (&DmQuickSortP, sizeof(void *), pDmQuickSort);
	return (*DmQuickSortP) ( dbP, compar,  other);
}
#endif

#ifdef L_DmRecordInfo
Err DmRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, 
						UInt32 *uniqueIDP, LocalID *chunkIDP)
{
	Err (*DmRecordInfoP) (DmOpenRef dbP, UInt16 index, UInt16 *attrP, 
						UInt32 *uniqueIDP, LocalID *chunkIDP);

	GetParameter (&DmRecordInfoP, sizeof(void *), pDmRecordInfo);
	return (*DmRecordInfoP) ( dbP,  index, attrP, 
						uniqueIDP, chunkIDP);
}
#endif

#ifdef L_DmReleaseRecord
Err DmReleaseRecord (DmOpenRef dbP, UInt16 index, Boolean dirty)
{
	Err (*DmReleaseRecordP) (DmOpenRef dbP, UInt16 index, Boolean dirty);

	GetParameter (&DmReleaseRecordP, sizeof(void *), pDmReleaseRecord);
	return (*DmReleaseRecordP) ( dbP,  index,  dirty);
}
#endif

#ifdef L_DmReleaseResource
Err DmReleaseResource (MemHandle resourceH)
{
	Err (*DmReleaseResourceP) (MemHandle resourceH);

	GetParameter (&DmReleaseResourceP, sizeof(void *), pDmReleaseResource);
  	return (*DmReleaseResourceP) ( resourceH);
}
#endif

#ifdef L_DmRemoveRecord
Err DmRemoveRecord (DmOpenRef dbP, UInt16 index)
{
	Err (*DmRemoveRecordP) (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmRemoveRecordP, sizeof(void *), pDmRemoveRecord);
	return (*DmRemoveRecordP) ( dbP,  index);
}
#endif

#ifdef L_DmRemoveResource
Err DmRemoveResource (DmOpenRef dbP, UInt16 index)
{
	Err (*DmRemoveResourceP) (DmOpenRef dbP, UInt16 index);

	GetParameter (&DmRemoveResourceP, sizeof(void *), pDmRemoveResource);
	return (*DmRemoveResourceP) ( dbP,  index);
}
#endif

#ifdef L_DmRemoveSecretRecord
Err DmRemoveSecretRecord (DmOpenRef dbP)
{
	Err (*DmRemoveSecretRecordP) (DmOpenRef dbP);
	
	GetParameter (&DmRemoveSecretRecordP, sizeof(void *), pDmRemoveSecretRecord);
	return (*DmRemoveSecretRecordP) ( dbP);
}
#endif

#ifdef L_DmResizeRecord
MemHandle DmResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 newSize)
{
	MemHandle (*DmResizeRecordP) (DmOpenRef dbP, UInt16 index, UInt32 newSize);
	
	GetParameter (&DmResizeRecordP, sizeof(void *), pDmResizeRecord);
	return (*DmResizeRecordP) ( dbP,  index,  newSize);
}
#endif

#ifdef L_DmResizeResource
Err DmResizeResource (MemHandle resourceH, UInt32 newSize)
{
	Err (*DmResizeResourceP) (MemHandle resourceH, UInt32 newSize);

	GetParameter (&DmResizeResourceP, sizeof(void *), pDmResizeResource);
	return (*DmResizeResourceP) ( resourceH,  newSize);
}
#endif

#ifdef L_DmResourceInfo
Err DmResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, 
						  DmResID *resIDP, LocalID *chunkLocalIDP)
{
	Err (*DmResourceInfoP) (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, 
						  DmResID *resIDP, LocalID *chunkLocalIDP);
	
	GetParameter (&DmResourceInfoP, sizeof(void *), pDmResourceInfo);
	return (*DmResourceInfoP) ( dbP,  index, resTypeP, 
						  resIDP, chunkLocalIDP);
}
#endif

#ifdef L_DmResetRecordStates
Err DmResetRecordStates(DmOpenRef dbP)
{
	Err (*DmResetRecordStatesP)(DmOpenRef dbP);

	GetParameter (&DmResetRecordStatesP, sizeof(void *), pDmResetRecordStates);
	return (*DmResetRecordStatesP)( dbP);
}
#endif

#ifdef L_DmSearchRecord
UInt16 DmSearchRecord (MemHandle recH, DmOpenRef *dbPP)
{
	UInt16 (*DmSearchRecordP) (MemHandle recH, DmOpenRef *dbPP);

	GetParameter (&DmSearchRecordP, sizeof(void *), pDmSearchRecord);
	return (*DmSearchRecordP) ( recH, dbPP);
}
#endif

#ifdef L_DmSearchResource
UInt16 DmSearchResource (DmResType resType, DmResID resID, MemHandle resH, DmOpenRef *dbPP)
{
	UInt16 (*DmSearchResourceP) (DmResType resType, DmResID resID, MemHandle resH, DmOpenRef *dbPP);

	GetParameter (&DmSearchResourceP, sizeof(void *), pDmSearchResource);
	return (*DmSearchResourceP) ( resType,  resID,  resH, dbPP);
}
#endif

#ifdef L_DmSeekRecordInCategory
Err DmSeekRecordInCategory (DmOpenRef dbP, UInt16 *indexP, Int16 offset,
							Int16 direction, UInt16 category)
{
	Err (*DmSeekRecordInCategoryP) (DmOpenRef dbP, UInt16 *indexP, Int16 offset,
							Int16 direction, UInt16 category);

	GetParameter (&DmSeekRecordInCategoryP, sizeof(void *), pDmSeekRecordInCategory);
	return (*DmSeekRecordInCategoryP) ( dbP, indexP,  offset,
							 direction,  category);
}
#endif

#ifdef L_DmSet
Err DmSet (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value)
{
	Err (*DmSetP) (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value);

	GetParameter (&DmSetP, sizeof(void *), pDmSet);
	return (*DmSetP) (recordP,  offset,  bytes,  value);
}
#endif

#ifdef L_DmSetDatabaseInfo
Err DmSetDatabaseInfo (UInt16 cardNo, LocalID dbID, const Char *nameP, UInt16 *attributesP,
					   UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					   UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP, UInt32 *typeP,
					   UInt32 *creatorP)
{
	Err (*DmSetDatabaseInfoP) (UInt16 cardNo, LocalID dbID, const Char *nameP, UInt16 *attributesP,
					   UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					   UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP, UInt32 *typeP,
					   UInt32 *creatorP);

	GetParameter (&DmSetDatabaseInfoP, sizeof(void *), pDmSetDatabaseInfo);
	return (*DmSetDatabaseInfoP) ( cardNo,  dbID,  nameP, attributesP,
					   versionP, crDateP, modDateP, bckUpDateP,
					   modNumP, appInfoIDP, sortInfoIDP, typeP,
					   creatorP);
}
#endif

#ifdef L_DmSetRecordInfo
Err DmSetRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP)
{
	Err (*DmSetRecordInfoP) (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP);

	GetParameter (&DmSetRecordInfoP, sizeof(void *), pDmSetRecordInfo);
	return (*DmSetRecordInfoP) ( dbP,  index, attrP, uniqueIDP);
}
#endif

#ifdef L_DmSetResourceInfo
Err DmSetResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP)
{
	Err (*DmSetResourceInfoP) (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP);

	GetParameter (&DmSetResourceInfoP, sizeof(void *), pDmSetResourceInfo);
	return (*DmSetResourceInfoP) ( dbP,  index, resTypeP, resIDP);
}
#endif

#ifdef L_DmStrCopy
Err DmStrCopy (void *recordP, UInt32 offset, const Char *srcP)
{
	Err (*DmStrCopyP) (void *recordP, UInt32 offset, const Char *srcP);

	GetParameter (&DmStrCopyP, sizeof(void *), pDmStrCopy);
	return (*DmStrCopyP) (recordP,  offset, srcP);
}
#endif

#ifdef L_DmWrite
Err DmWrite (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes)
{
	Err (*DmWriteP) (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes);

	GetParameter (&DmWriteP, sizeof(void *), pDmWrite);
	return (*DmWriteP) (recordP,  offset,  srcP,  bytes);
}
#endif

#ifdef L_DmWriteCheck
Err DmWriteCheck (void *recordP, UInt32 offset, UInt32 bytes)
{
	Err (*DmWriteCheckP) (void *recordP, UInt32 offset, UInt32 bytes);

	GetParameter (&DmWriteCheckP, sizeof(void *), pDmWriteCheck);
	return (*DmWriteCheckP) (recordP,  offset,  bytes);
}
#endif



////////////////////////////////////////////////////////////
// Error Manager Library, completed 5/6 functions now.
////////////////////////////////////////////////////////////
#ifdef L_ErrFatalDisplayIf
void ErrFatalDisplayIf (Boolean condidtion, Char *msg)
{
	void (*ErrFatalDisplayIfP) (Boolean condidtion, Char *msg);

	GetParameter (&ErrFatalDisplayIfP, sizeof(void *), pErrFatalDisplayIf);
	(*ErrFatalDisplayIfP) (condidtion, msg);
}
#endif

#ifdef L_ErrFatalDisplay
void ErrFatalDisplay (Char *msg)
{
	void (*ErrFatalDisplayP) (Char *msg);

	GetParameter (&ErrFatalDisplayP, sizeof(void *), pErrFatalDisplay);
	(*ErrFatalDisplayP) (msg);
}
#endif

#ifdef L_ErrNonFatalDisplayIf
void ErrNonFatalDisplayIf (Boolean condidtion, Char *msg)
{
	void (*ErrNonFatalDisplayIfP) (Boolean condidtion, Char *msg);
	
	GetParameter (&ErrNonFatalDisplayIfP, sizeof(void *), pErrNonFatalDisplayIf);
	(*ErrNonFatalDisplayIfP) ( condidtion, msg);
}
#endif

#ifdef L_ErrThrow
void  ErrThrow(Int32 err) 
{
	void  (*ErrThrowP)(Int32 err) ;
	
	GetParameter (&ErrThrowP, sizeof(void *), pErrThrow);
	(*ErrThrowP) ( err);
}
#endif
	
							
#ifdef L_ErrDisplayFileLineMsg
void	ErrDisplayFileLineMsg(const Char * const filename, UInt16 lineNo, 
			const Char * const msg)
{
	void	(*ErrDisplayFileLineMsgP)(const Char * const filename, UInt16 lineNo, 
			const Char * const msg);
	
	GetParameter (&ErrDisplayFileLineMsgP, sizeof(void *), pErrDisplayFileLineMsg);
	(*ErrDisplayFileLineMsgP)( filename,  lineNo,    msg);	
}
#endif

//
#ifdef L_ErrAlert
Err	ErrAlert(Err err)
{
	Err	(*ErrAlertP)(Err err);
	
	GetParameter (&ErrAlertP, sizeof(void *), pErrAlert);
	(*ErrAlertP)(err);
}
#endif


////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_ExgConnect
Err ExgConnect(ExgSocketPtr socketP)

{
	Err (*ExgConnectP)(ExgSocketPtr socketP);

	GetParameter (&ExgConnectP, sizeof(void *), pExgConnect);
	return  (*ExgConnectP)(socketP);
}
#endif

#ifdef L_ExgPut
Err ExgPut(ExgSocketPtr socketP)
{
	Err (*ExgPutP)(ExgSocketPtr socketP);

	GetParameter (&ExgPutP, sizeof(void *), pExgPut);
	return  (*ExgPutP)(socketP);
}
#endif


#ifdef L_ExgAccept
Err ExgAccept(ExgSocketPtr socketP)
{
	Err (*ExgAcceptP)(ExgSocketPtr socketP);

	GetParameter (&ExgAcceptP, sizeof(void *), pExgAccept);
	return   (*ExgAcceptP)(socketP);
}
#endif


#ifdef L_ExgDisconnect
Err ExgDisconnect(ExgSocketPtr socketP,Err error)
{
	Err (*ExgDisconnectP)(ExgSocketPtr socketP,Err error);

	GetParameter (&ExgDisconnectP, sizeof(void *), pExgDisconnect);
	return		(*ExgDisconnectP)( socketP, error);
}
#endif

#ifdef L_ExgSend
UInt32 ExgSend(ExgSocketPtr socketP, const void * const bufP, const UInt32 bufLen, Err *err)
{
	UInt32 (*ExgSendP)(ExgSocketPtr socketP, const void * const bufP, const UInt32 bufLen, Err *err);

	GetParameter (&ExgSendP, sizeof(void *), pExgSend);
	return	(*ExgSendP)( socketP,   bufP,  bufLen, err);
}
#endif

#ifdef L_ExgReceive
UInt32 ExgReceive(ExgSocketPtr socketP, void *bufP, const UInt32 bufLen, Err *err)
{
	UInt32 (*ExgReceiveP)(ExgSocketPtr socketP, void *bufP, const UInt32 bufLen, Err *err);

	GetParameter (&ExgReceiveP, sizeof(void *), pExgReceive);
	return	(*ExgReceiveP)( socketP, bufP,  bufLen, err);
}
#endif

*/
#ifdef L_ExgRegisterData
Err ExgRegisterData(const UInt32 creatorID, const UInt16 id, const Char * const dataTypesP)
{
	Err (*ExgRegisterDataP)(const UInt32 creatorID, const UInt16 id, const Char * const dataTypesP);

	GetParameter (&ExgRegisterDataP, sizeof(void *), pExgRegisterData);
	return	(*ExgRegisterDataP)(  creatorID,   id, dataTypesP);
}
#endif
/*
#ifdef L_ExgDBRead
Err	ExgDBRead(
		ExgDBReadProcPtr		readProcP,
		ExgDBDeleteProcPtr		deleteProcP,
		void*					userDataP,
		LocalID*				dbIDP,
		UInt16					cardNo,
		Boolean*				needResetP,
		Boolean					keepDates)
{
	Err	(*ExgDBReadP)( ExgDBReadProcPtr	readProcP,
		ExgDBDeleteProcPtr		deleteProcP,
		void*					userDataP,
		LocalID*				dbIDP,
		UInt16					cardNo,
		Boolean*				needResetP,
		Boolean					keepDates);

	GetParameter (&ExgDBReadP, sizeof(void *), pExgDBRead);
	return	(*ExgDBReadP)( 	readProcP,	deleteProcP,userDataP,
			dbIDP,	cardNo,	needResetP,	keepDates);
}
#endif

#ifdef L_ExgDBWrite
Err	ExgDBWrite(
		ExgDBWriteProcPtr		writeProcP,
		void*					userDataP,
		const char*				nameP,
		LocalID					dbID,
		UInt16					cardNo)
{
	Err	(*ExgDBWriteP)(
		ExgDBWriteProcPtr		writeProcP,
		void*					userDataP,
		const char*				nameP,
		LocalID					dbID,
		UInt16					cardNo);
	
	GetParameter (&ExgDBWriteP, sizeof(void *), pExgDBWrite);
	return	(*ExgDBWriteP)(writeProcP,	userDataP,	nameP,
							dbID,	cardNo);
}
#endif
		

*/
 
////////////////////////////////////////////////////////////
// Feature Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////

#ifdef L_FtrGet
Err FtrGet (UInt32 creator, UInt16 featureNum, UInt32 *valueP)
{
	Err (*FtrGetP) (UInt32 creator, UInt16 featureNum, UInt32 *valueP);

	GetParameter (&FtrGetP, sizeof(void *), pFtrGet);
	return (*FtrGetP) ( creator,  featureNum, valueP);
}
#endif

#ifdef L_FtrSet
Err	FtrSet(UInt32 creator, UInt16 featureNum, UInt32 newValue)
{
	Err	(*FtrSetP)(UInt32 creator, UInt16 featureNum, UInt32 newValue);
	
	GetParameter (&FtrSetP, sizeof(void *), pFtrSet);
	return	(*FtrSetP)( creator,  featureNum,  newValue);
}
#endif
						
#ifdef L_FtrUnregister
Err	FtrUnregister(UInt32 creator, UInt16 featureNum)
{
	Err	(*FtrUnregisterP)(UInt32 creator, UInt16 featureNum);
	
	GetParameter (&FtrUnregisterP, sizeof(void *), pFtrUnregister);
	return	(*FtrUnregisterP)( creator,  featureNum);
}
#endif
						
#ifdef L_FtrGetByIndex
Err	FtrGetByIndex(UInt16 index, Boolean romTable, 
					UInt32 *creatorP, UInt16 *numP, UInt32 *valueP)
{
	Err	(*FtrGetByIndexP)(UInt16 index, Boolean romTable, 
					UInt32 *creatorP, UInt16 *numP, UInt32 *valueP);
	
	GetParameter (&FtrGetByIndexP, sizeof(void *), pFtrGetByIndex);
	return	(*FtrGetByIndexP)( index,  romTable, 
					creatorP, numP, valueP);
}
#endif
						
#ifdef L_FtrPtrNew
Err	FtrPtrNew(UInt32 creator, UInt16 featureNum, UInt32 size,
					void **newPtrP)
{
	Err	(*FtrPtrNewP)(UInt32 creator, UInt16 featureNum, UInt32 size,
					void **newPtrP);
	
	GetParameter (&FtrPtrNewP, sizeof(void *), pFtrPtrNew);
	return	(*FtrPtrNewP)( creator,  featureNum,  size,
					newPtrP);
}
#endif
						
#ifdef L_FtrPtrFree
Err	FtrPtrFree(UInt32 creator, UInt16 featureNum)
{
	Err	(*FtrPtrFreeP)(UInt32 creator, UInt16 featureNum);
	
	GetParameter (&FtrPtrFreeP, sizeof(void *), pFtrPtrFree);
	return 	(*FtrPtrFreeP)( creator,  featureNum);
}
#endif
					

#ifdef L_FtrPtrResize
Err	FtrPtrResize(UInt32 creator, UInt16 featureNum, UInt32 newSize,
					void **newPtrP)
{
	Err	(*FtrPtrResizeP)(UInt32 creator, UInt16 featureNum, UInt32 newSize,
					void **newPtrP);
	
	GetParameter (&FtrPtrResizeP, sizeof(void *), pFtrPtrResize);
	return	(*FtrPtrResizeP)( creator,  featureNum,  newSize,
					newPtrP);
}
				
#endif


