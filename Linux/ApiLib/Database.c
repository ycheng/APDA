#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#define	SEEK_SET    0
#define	SEEK_END    2
#define	DBFILE	"APM_Database.pdb"

char			PDBFilename[32];
UInt16		currentRecord=0xFFFF;
UInt8			dmMode=dmModeReadOnly;
DmOpenRef	currentDBP=NULL;
Boolean		CreateDB = FALSE;

// Global variable to record the current opend database
UInt16	curCardNo;
Boolean	curResDB;
LocalID	curDBID=0;
LocalID	curAppInfoID=0;
UInt32	curCreator;
UInt32	curType;

extern SYSHandle	sysHandle;

MemHandle DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
Boolean WSearchDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode, char *filename);
extern UInt16 VTransferUInt (UInt16 num);
extern Int16 VWriteRecordInfo (DmOpenRef dbP, UInt16 index, char *srcP);



////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmAttachRecord
//
// DESCRIPTION: This routine attach an existing chunk ID handle to
//				a database as a record
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16 *) atP - Pointer to the index where the new record
//								should be placed.
//				(MemHandle) newH - Handle of the new record.
//				(MemHandle *) oldHP - If non-NULL upon entry, indicates 
//								that the record at *atP should be replaced.
//								Upon return, contains the handle to the 
//								replaced record
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/7/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmAttachRecord (DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmCloseDatabase
//
// DESCRIPTION: This routine close a database
//
// PARAMETERS:  (DmOpenRef) dbP - Database access pointer
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmCloseDatabase (DmOpenRef dbp)
{
	CreateDB = FALSE;
	Vmemset (PDBFilename, 0, 32);

	if (!VCloseDatabaseFile (dbp)) {
		dbp = NULL;
		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmCreateDatabase
//
// DESCRIPTION: This routine create a new database on the specified card
//				with the given name, creator, and type.
//
// PARAMETERS:  (UInt16) cardNo - The card number to create the database on.
//				(const Char *) nameP - Name of new database, up to 32 ASCII 
//									bytes long, including the null terminator.
//				(UInt32) creator - Creator of the database
//				(UInt32) type - Type of the database.
//				(Boolean) resDB - If true, create a resource database
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01	Initial Revision
//			Jerry 5/15/01	Added return dmErrAlreadyExists option
////////////////////////////////////////////////////////////////////////
Err DmCreateDatabase (UInt16 cardNo, const Char *nameP, UInt32 creator, UInt32 type, Boolean resDB)
{
	DmOpenRef	dbP;

	curCardNo = cardNo;
	curResDB = resDB;
	curCreator = creator;
	curType = type;

	Vstrcpy (PDBFilename, nameP);
	Vstrcat (PDBFilename, ".PDB");
	CreateDB = TRUE;

	if ( (dbP = Vfopen (PDBFilename, "rb")) != NULL ) {
		Vfclose (dbP);

		return	dmErrAlreadyExists;
	} else {
		UInt32		length = Vstrlen(nameP)+16;

		if ( (dbP = Vfopen (DBFILE, "ab+")) != NULL ) {
			Vfseek (dbP, 0, SEEK_END);
			Vfwrite (&length, sizeof(UInt32), 1, dbP);
			Vfwrite (&cardNo, sizeof(UInt16), 1, dbP);
			Vfwrite (&resDB, sizeof(Boolean), 1, dbP);
			Vfwrite (&creator, sizeof(UInt32), 1, dbP);
			Vfwrite (&type, sizeof(UInt32), 1, dbP);
			// hardcore, 16 is creator database header length
			Vfwrite (nameP, length-16, 1, dbP);
			Vfclose (dbP);
		}
		return	0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmDatabaseInfo
//
// DESCRIPTION: This routine retrieve information about a database.
//
// PARAMETERS:  (UInt16) cardNo - Number of the card the database resides
//										on.
//					 (LocalID) dbID - Database ID of the database
//					 (Char *) nameP - The database's name. Pass a pointer to 
//									32-byte character array for this parameter,
//									or NULL if you don't care about the name.
//					 (UInt16 *) attributesP - The database's attribute flags.
//					 (UInt16 *) versionP - The application-specific version number.
//					 (UInt32 *) crDateP - The date the database was created.
//					 (UInt32 *) modDateP - The date the database was last modified.
//					 (UInt32 *) bckUpDateP - The date the database was backed up.
//					 (UInt32 *) modNumP - The modification number, which is incremented
//										every time a record in the database is added, modified,
//										or deleted.
//					 (LocalID *) appInfoIDP - The local ID of the application info block.
//					 (LocalID *) sortInfoIDP - The local ID of the database's sort table.
//					 (UInt32 *) typeP - The database's type.
//					 (UInt32 *) creatorP - The database's creator.
//
// RETURNED:    Returns a handle to record data.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01		Initial Revision
////////////////////////////////////////////////////////////////////////
extern Err DmDatabaseInfo (UInt16 cardNo, LocalID dbID, Char *nameP, UInt16 *attributesP,
					UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP,
					UInt32 *typeP, UInt32 *creatorP)
{
	if ( (cardNo == curCardNo) && (dbID == curDBID) ) {
		if ( appInfoIDP ) 
			*appInfoIDP = curAppInfoID;
		if ( typeP )
			*typeP = curType;
		if ( creatorP ) 
			*creatorP = curCreator;

		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmDatabaseSize
//
// DESCRIPTION: This routine retrieve size information on a database.
//
// PARAMETERS:  (UInt16) cardNo - Number of the card the database resides
//										on.
//					 (LocalID) dbID - Database ID of the database
//					 (UInt32 *) numRecordsP - The total number of records
//										in the database.
//					 (UInt32 *) totalBytesP - The total number of bytes
//										used by the database.
//					 (UInt32 *) dataBytesP - The total number of bytes
//										used to store just each record's data.
//
// RETURNED:    Returns errNone if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmDatabaseSize (UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP)
{
	if ( curDBID == dbID ) {
		*numRecordsP = VNumRecords (currentDBP);
		*totalBytesP = VDatabaseSize (currentDBP);
		*dataBytesP = VDataSize (currentDBP);

		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmDeleteCategory
//
// DESCRIPTION: This routine delete all records in a category. The 
//					 category name is not changed.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) categoryNum - Category of records to delete.
//									Category masks such as dmAllCategories are
//									invalid.
//
// RETURNED:    Returns errNone if no error, or error code if error 
//					 occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmDeleteCategory (DmOpenRef dbp, UInt16 categoryNum)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmDeleteRecord
//
// DESCRIPTION: This routine delete record's chunk from a database but
//					 leave the record entry in the header and set the delete
//					 bit for the next sync.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) index - Which record to delete.
//
// RETURNED:    Returns errNone if no error, or error code if error 
//					 occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmDeleteRecord (DmOpenRef dbp, UInt16 index)
{
	VDeleteRecord (dbp, index);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmGetDatabase
//
// DESCRIPTION: This routine return the database header ID of a database
//					 by index and card number.
//
// PARAMETERS:  (UInt16) cardNo - Card number of database
//					 (UInt16) index - Index of database
//
// RETURNED:    Returns the database ID, or 0 if an invalid parameter is
//					 passed.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
LocalID DmGetDatabase (UInt16 cardNo, UInt16 index)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmGetNextDatabaseByTypeCreator
//
// DESCRIPTION: This routine return a database header ID and card number
//					 given the type and/or creator. This routine searches all
//					 memory cards for a match.
//
// PARAMETERS:  (Boolean) newSearch - true if starting a new search.
//					 (DmSearchStatePtr) stateInfoP - If newSearch is false,
//										this must point to the same data used for
//										the previous invocation.
//					 (UInt32) type - Type of database to search for, pass 0
//										as a wildcard.
//					 (UInt32) creator - Creator of database to search for,
//										pass 0 as a wildcard.
//					 (Boolean) onlyLatesVers - If true, only the lasted 
//										version of database with a given type and 
//										creator is returned.
//					 (UInt16 *) cardNoP - On exit, the card number of the 
//										found database.
//					 (LocalID *) dbIDP - Database local ID of the found
//										database.
//
// RETURNED:    Returns errNone if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmGetNextDatabaseByTypeCreator (Boolean newSearch, DmSearchStatePtr stateInfoP, 
												UInt32 type, UInt32 creator, Boolean onlyLatesVers, 
												UInt16 *cardNoP, LocalID *dbIDP)
{
	return	errNone;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmGetRecord
//
// DESCRIPTION: This routine return a handle to a record by index and
//					 mark the record busy.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) index - Which record to retrieve
//
// RETURNED:    Returns a handle to record data.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01	Initial Revision
////////////////////////////////////////////////////////////////////////
MemHandle DmGetRecord (DmOpenRef dbP, UInt16 index)
{
	dmMode = dmModeReadWrite;
	currentRecord = index;
	currentDBP = dbP;

	VGetRecord (dbP, index, 0);
	
	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		return	&(sysHandle.handle[NUMSYSHANDLE-1]);
	else
		return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmGet1Resource
//
// DESCRIPTION: This routine search the most recently opened resource 
//					 database and return a handle to a resource given the
//					 resource type and ID.
//
// PARAMETERS:  (DmResType) type - The resource type
//					 (DmResID) resID - The resource ID.
//
// RETURNED:    Returns handle to resource data. If unsuccessful, this
//					 function returns NULL.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
MemHandle DmGet1Resource (DmResType type, DmResID resID)
{

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmInsertionSort
//
// DESCRIPTION: This routine sort records in a database
//
// PARAMETERS:  (DmOpenRef) dbR - Database access pointer
//					 (DmComparF *) compar - Compaison function.
//					 (UInt16) other - Any Value the application wants to pass
//								to the comparison function
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/26/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmInsertionSort (DmOpenRef dbR, DmComparF *compar, Int16 other)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmMoveCategory
//
// DESCRIPTION: This routine move all records in a category to another
//					 category.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) toCategory - Category to which the records
//										should be added.
//					 (UInt16) fromCategory - Category from which to remove
//										records..
//					 (Boolean) dirty - If true, set the dirty bit.
//
// RETURNED:    Returns 0 if successful.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmMoveCategory (DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty)
{
	UInt16	index;
	UInt16	numRecords = VNumRecords (dbP);

	for ( index = 0; index < numRecords; index++ ) {
		if ( toCategory == VGetCategory (dbP, index) )
			VSetCategory (dbP, index, fromCategory);
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmMoveRecord
//
// DESCRIPTION: This routine move a record from one index to another
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database.
//					 (UInt16) from - Index of record to move.
//					 (UInt16) to - Where to move the record.
//
// RETURNED:    Returns 0 if successful.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmMoveRecord (DmOpenRef dbP, UInt16 from, UInt16 to)
{
	UInt16	index;
	UInt16	numRecords = VNumRecords (dbP);

	for ( index = 0; index < numRecords; index++ ) {
		if ( from == VGetRecordNo (dbP, index) ) {
			VSetRecordNo (dbP, index, (UInt32)to);

			return	0;
		}
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNewHandle
//
// DESCRIPTION: This routine Attempt to allocate a new chuck in the same
//				data heap or card as the database header of the passed 
//				database access pointer. If there is not enough space
//				in th data hap, try other heaps.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt32) size - Size of new handle
//
// RETURNED:    Returns the chuckID of new chuck. If an error occurs, 
//				returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/6/01	Initial Revision
//			Jerry 5/08/01	Modify DmNewRecord to Vmalloc
////////////////////////////////////////////////////////////////////////
MemHandle DmNewHandle (DmOpenRef dbP, UInt32 size)
{
	sysHandle.handle[NUMSYSHANDLE-1] = Vmalloc (size);
	sysHandle.size[NUMSYSHANDLE-1] = size;

	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		return	&(sysHandle.handle[NUMSYSHANDLE-1]);
	else
		return	NULL;
//	return	DmNewRecord (dbP, &at, size);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNewRecord
//
// DESCRIPTION: This routine return a handle to a new record in the 
//				database and mark the record busy.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16 *) atP - Pointer to index where new record should
//								be placed.
//				(UInt32) size - Size of new record.
//
// RETURNED:    Handle to record data.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01	Initial Revision
//			Jerry	9/20/01	Modified to return MemHandle
////////////////////////////////////////////////////////////////////////
MemHandle DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size)
{
	MemHandle	handle;

	dmMode=dmModeReadWrite;
	currentDBP = dbP;
	if ( *atP == dmMaxRecordIndex ) {	// add record in the tail of file
		currentRecord = VNumRecords (dbP);
	} else {
		currentRecord = *atP;
	}

	if ( (handle = VNewRecord ( dbP, atP, size )) == NULL )
		return	NULL;

	return	(&(sysHandle.handle[NUMSYSHANDLE-1]));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNumDatabases
//
// DESCRIPTION: This routine determine how many databases reside on a
//					 memory card.
//
// PARAMETERS:  (UInt16) cardNo - DmOpenRef to open database
//
// RETURNED:    Returns the number of database found.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 DmNumDatabases (UInt16 cardNo)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNumRecords
//
// DESCRIPTION: This routine return the number of records in a database.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//
// RETURNED:    Returns the number of records in a database.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 DmNumRecords (DmOpenRef dbP)
{
	return	VNumRecords (dbP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNumRecordsInCategory
//
// DESCRIPTION: This routine return the number of records of a specified
//					 category in a database.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) category - Category index.
//
// RETURNED:    Returns the number of records in the category.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 DmNumRecordsInCategory (DmOpenRef dbP, UInt16 category)
{
	UInt16	count=0, index;
	UInt16	numRecords = VNumRecords (dbP);

	for ( index = 0; index < numRecords; index++ ) {
		if ( (category==dmAllCategories) || (category == VGetCategory (dbP, index)) )
			count++;
	}

	return	count;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmOpenDatabaseByTypeCreator
//
// DESCRIPTION: This routine clear the busy bit for the given record 
//					 and the dirty bit if dirty is true
//
// PARAMETERS:  (UInt32) type - Type of the database
//					 (UInt32) creator - Creator of the database
//					 (UInt16) mode - Type of the database.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01	Initial Revision
//			Jerry	9/19/01	Completed search database by type and creator
////////////////////////////////////////////////////////////////////////
DmOpenRef DmOpenDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode)
{
	if ( Vstrlen (PDBFilename) ) {
		currentDBP = VLoadDatabaseFile (PDBFilename, type, creator, CreateDB);
		return	currentDBP;
	} else if ( WSearchDatabaseByTypeCreator (type, creator, mode, PDBFilename) ) {
		currentDBP = VLoadDatabaseFile (PDBFilename, type, creator, CreateDB);
		return	currentDBP;
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmOpenDatabaseInfo
//
// DESCRIPTION: This routine retrieve information about an open database
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (LocalID *) dbIDP - The ID of database. Pass NULL for
//										this parameter if you don't want to retrieve
//										this information.
//					 (UInt16 *) openCountP - The number of applications that 
//										have this database open. Pass NULL for
//										this parameter if you don't want to retrieve
//										this information.
//					 (UInt16 *) modeP - The mode used to open the database.Pass 
//										NULL for	this parameter if you don't want to 
//										retrieve	this information.
//					 (UInt16 *) cardNoP - The number of the card on which this 
//										database resides. Pass NULL for this parameter 
//										if you don't want to retrieve	this information.
//					 (Boolean *) resDBP - If true upon return, the database is a 
//										resource database, false otherwise. Pass NULL for
//										this parameter if you don't want to retrieve
//										this information
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmOpenDatabaseInfo (DmOpenRef dbP, LocalID *dbIDP, UInt16 *openCountP, UInt16 *modeP,
						UInt16 *cardNoP, Boolean *resDBP)
{
	if ( dbP ) {
		*dbIDP = curDBID;
		*cardNoP = curCardNo;

		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmPositionInCategory
//
// DESCRIPTION: This routine return a position of a record within the 
//					 specified category.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) index - Index of the record.
//					 (UInt16) category - Index of category to search.
//
// RETURNED:    Returns the position.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 DmPositionInCategory (DmOpenRef dbP, UInt16 index, UInt16 category)
{
	UInt16	count=0, i;
	UInt16	numRecords = VNumRecords (dbP);

	if ( index >= numRecords ) {
		return	0;
	}

	for ( i = 0; i <= index; i++ ) {
		if ( category == VGetCategory (dbP, index) )
			count++;
	}

	return	count;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmRecordInfo
//
// DESCRIPTION: This routine clear the busy bit for the given record 
//				and the dirty bit if dirty is true
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16) index - Index of the record
//				(UInt16 *) attrP - The record's attributes.
//				(UInt32 *) uniqueIDP - The record's unique ID. Pass
//							NULL fo this parater if you don't want
//							to retrieve this value.
//				(LocalID *) chunkIDP - The record's local ID. Pass
//							NULL fo this parater if you don't want
//							to retrieve this value.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/7/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP, LocalID *chunkIDP)
{
	*attrP =	VGetCategory (dbP, index);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmResizeRecord
//
// DESCRIPTION: This routine resize a record by index.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database.
//					 (UInt16) index - The record to unlock.
//					 (UInt32) newSize - new size of record.
//
// RETURNED:    Returns handle to resized record.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
//			Jerry 5/08/01	Corrected to return MemHandle
////////////////////////////////////////////////////////////////////////
MemHandle DmResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 newSize)
{
	dmMode=dmModeReadWrite;
	currentDBP = dbP;
	currentRecord = index;

	sysHandle.handle[NUMSYSHANDLE-1] = VResizeRecord ( dbP, index, newSize );
	sysHandle.size[NUMSYSHANDLE-1] = newSize;

	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		return	&(sysHandle.handle[NUMSYSHANDLE-1]);
	else
		return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmReleaseRecord
//
// DESCRIPTION: This routine clear the busy bit for the given record 
//					 and the dirty bit if dirty is true
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//					 (UInt16) index - The record to unlock
//					 (Boolean) dirty - If true, set the dirty bit
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmReleaseRecord (DmOpenRef dbP, UInt16 index, Boolean dirty)
{
	if ( index == currentRecord ) {
		currentDBP = NULL;
		dmMode = dmModeReadOnly;
		currentRecord = 0xFFFF;
		Vfflush (dbP);

		return	VReleaseRecord () ;
	} else {
		return	-1;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmReleaseResource
//
// DESCRIPTION: This routine release a resource acquired with 
//					 DmGetResource.
//
// PARAMETERS:  (MemHandle) resourceH - Handle to resource.
//
// RETURNED:    Returns errNone if no error.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmReleaseResource (MemHandle resourceH)
{
	Vfree (*resourceH);
	Vfree (resourceH);
	resourceH = NULL;

	return	errNone;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmRemoveRecord
//
// DESCRIPTION: This routine remove a record from a database and dispose
//				of its data chunk
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16) index - The record to remove
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmRemoveRecord (DmOpenRef dbP, UInt16 index)
{
	VDeleteRecord (dbP, index);
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmResetRecordStates
//
// DESCRIPTION: This routine remove a record from a database and dispose
//				of its data chunk
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmResetRecordStates(DmOpenRef dbP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmQueryRecord
//
// DESCRIPTION: This routine return a handle to a record for reading 
//				only (does not set the busy bit).
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16) index - Which record to retrieve
//
// RETURNED:    Returns a handle to the given record. Use this routine
//				only when viewing the record. This routine successfully 
//				returns a handle to the record even if te record is busy.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01	Initial Revision
//			Jerry	11/24/01	Modify to use sysHandle to get record
////////////////////////////////////////////////////////////////////////
MemHandle DmQueryRecord (DmOpenRef dbP, UInt16 index)
{
	dmMode = dmModeReadOnly;
	currentRecord = index;

	VGetRecord (dbP, currentRecord, 0);

	return	&(sysHandle.handle[NUMSYSHANDLE-1]);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmSeekRecordInCategory
//
// DESCRIPTION: This routine return the index of the record nearest the
//					 offset from the passed record index whose category matches
//					 the passed category.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				 	 (UInt16) index - Which record to retrieve
//					 (UInt16) offset - Offset of the passed record index.
//					 (Int16) direction - Must be either dmSeekForward or
//										dmSeekBackward.
//					 (UInt16) category - Category index.
//
// RETURNED:    Returns a handle to the given record. Use this routine
//				only when viewing the record. This routine successfully 
//				returns a handle to the record even if te record is busy.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmSeekRecordInCategory (DmOpenRef dbP, UInt16 *indexP, Int16 offset,
							Int16 direction, UInt16 category)
{
	UInt16	recCategory;
	UInt16	numRecords = VNumRecords (dbP);

	if ( (numRecords == 0) || (*indexP >= numRecords) ) {
		return	-1;
	} else if ( category == dmAllCategories ) {
		return	0;
	}

	do {
		recCategory = VGetCategory (dbP, *indexP);

		if ( recCategory == category )
			break;

		if (++(*indexP) >= numRecords)
			return	-1;
	} while (TRUE);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmSet
//
// DESCRIPTION: This routine write a specified value into a section of
//					 a record. This function also checks the validity of the
//					 record and makes sure the writing of the record 
//					 information doesn't exceed the bounds of the record.
//
// PARAMETERS:  (void *) recordP - Pointer to locked data record
//					 (UInt32) offset - Offset within record to start writing.
//					 (UInt32) bytes - Number of bytes to write
//					 (UInt8) value - Byte value to write.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmSet (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value)
{
	return	MemSet (((Char *)recordP+offset), bytes, value);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmSetDatabaseInfo
//
// DESCRIPTION: This routine set information about a database.
//
// PARAMETERS:  (UInt16) cardNo - Card number the database resides on.
//					 (LocalID) dbID - Database ID of the database.
//					 (const Char *) nameP - Pointer to 32-byte character array
//											for new name, or NULL.
//					 (UInt16 *) attributesP - Pointer to new attribute variable.
//					 (UInt16 *) versionP - Pointer to new version.
//					 (UInt32 *) crDateP - Pointer to new creation date variable.
//					 (UInt32 *) modDateP - Pointer to new modification date 
//											variable.
//					 (UInt32 *) bckUpDateP - Pointer to new backup date variable.
//					 (UInt32 *) modNumP - Pointer to new modification number 
//											variable.
//					 (LocalID *) appInfoIDP - Pointer to new appInfoID variable.
//					 (LocalID *) sortInfoIDP - Pointer to new sortInfoID variable.
//					 (UInt32 *) typeP - Pointer to new type variable.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmSetDatabaseInfo (UInt16 cardNo, LocalID dbID, const Char *nameP, UInt16 *attributesP,
					   UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					   UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP, UInt32 *typeP,
					   UInt32 *creatorP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmSetRecordInfo
//
// DESCRIPTION: This routine set record information stored in the 
//				database header.
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16) index - Index of the record
//				(UInt16 *) attrP - Pointer to new attribute variable.
//				(UInt32 *) uniqueIDP - Pointer to new unique ID variable,
//								or NULL.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/7/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmSetRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP)
{
//	if ( dmMode == dmModeReadOnly ) {
//		return	-1;
//	} else {
		VWriteRecordInfo (dbP, index, attrP);
//	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmStrCopy
//
// DESCRIPTION: This routine check the validity of the chunk pointer
//					 for the record and make sure that writing the record
//					 will not exceed the chunk bounds.
//
// PARAMETERS:  (void *) recordP - Pointer to data record(chunk pointer).
//					 (UInt32) offset - Offset within record to start writing.
//					 (const void *) srcP - Pointer to null-terminated string.
//
// RETURNED:    Returns errNone if no error.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmStrCopy (void *recordP, UInt32 offset, const Char *srcP)
{
	if ( dmMode == dmModeReadOnly ) {
		return	-1;
	} else {
		VWriteRecord (currentDBP, currentRecord, offset, srcP, (Vstrlen (srcP)+1));
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmWrite
//
// DESCRIPTION: This routine must be used to wite to data manager records
//				because the data storage area is write protected. This 
//				routine checks the validity of the chunk pointer for 
//				the record and makes sure that the write will not exceed
//				the chunk bounds.
//
// PARAMETERS:  (void *) recordP - Pointer to locked data record(chunk pointer).
//				(UInt32) offset - Offset within record to start writing.
//				(const void *) srcP - Pointer to data to copy into record
//				(UInt32) bytes - Number of bytes to write
//
// RETURNED:    Returns a handle to the given record. Use this routine
//				only when viewing the record. This routine successfully 
//				returns a handle to the record even if te record is busy.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err DmWrite (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes)
{
	if ( dmMode == dmModeReadOnly ) {
		return	-1;
	} else {
		VWriteRecord (currentDBP, currentRecord, offset, srcP, bytes);
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WSearchDatabaseByTypeCreator
//
// DESCRIPTION: This routine search the type creator database find the
//					 database file name created by specified type creator.
//
// PARAMETERS:  (UInt32) type - Type of the database
//					 (UInt32) creator - Creator of the database
//					 (UInt16) mode - Type of the database.
//					 (char *) filename - Pointer to the string to storage
//										found file name.
//
// RETURNED:    Returns TRUE if find specified filename.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean WSearchDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode, char *filename)
{
	DmOpenRef	dbP;
	UInt32		length, count = 0, fileLength;
	UInt32		fType, fCreator;
	UInt16		fCardNo;
	Boolean		fResDB;
	Boolean		fileFound=FALSE;

	if ( (dbP = Vfopen (DBFILE, "rb")) != NULL ) {
		Vfseek (dbP, 0, SEEK_END);
		fileLength = Vftell (dbP);

		do {
			Vfseek (dbP, count, SEEK_SET);
			Vfread (&length, sizeof(UInt32), 1, dbP);
			Vfread (&fCardNo, sizeof(UInt16), 1, dbP);
			Vfread (&fResDB, sizeof(Boolean), 1, dbP);
			Vfread (&fCreator, sizeof(UInt32), 1, dbP);
			Vfread (&fType, sizeof(UInt32), 1, dbP);

			// find the right database file
			if ( (creator==fCreator) && (fType==type) ) {
				// hardcore, 16 is creator database header length
				Vfread (filename, 1, (length-16), dbP);
				curCardNo = fCardNo;
				curResDB = fResDB;
				curCreator = fCreator;
				curType = fType;

				fileFound = TRUE;
				break;
			}

			count += length;

			// search to the end of file, break;
			if ( count >= fileLength )
				break;
		} while (TRUE);

		Vfclose (dbP);
	} 
	
	// type creator database file not exist, return false
	return	fileFound;
}
