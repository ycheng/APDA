
#include "stdafx.h"
#include "database.h"


#define		NUMSYSHANDLE		256
#define	DBFILE	"APM_Database.pdb"

SYSHandle	sysHandle;
char			PDBFilename[256];
UInt16		currentRecord=0xFFFF;
UInt8			dmMode=dmModeReadOnly;
DmOpenRef	currentDBP=NULL;
Boolean		CreateDB = FALSE;
UInt16	curCardNo;
Boolean	curResDB;
LocalID	curDBID=0;
LocalID	curAppInfoID=0;
UInt32	curCreator;
UInt32	curType;
extern char		directory[256];

UInt16 VGetRecordSize (DmOpenRef dbP, UInt16 offset1, UInt16 totalRecords);
UInt16 VMoveToLastRecord (DmOpenRef dbP, UInt16 index, UInt16 offset1, UInt16 RecordSize, UInt16 totalRecords);


UInt16 VTransferUInt (UInt16 num)
{
	return	((num>>8)&0x00FF) | ((num<<8)&0xFF00);
}

UInt32 VTransferUInt32 (UInt32 num)
{
	return	((num>>24)&0x000000FF) | ((num>>8)&0x0000FF00) | 
		((num<<8)&0x00FF0000) | ((num<<24)&0xFF000000);
}
////////////////////////////////////////////////////////////////////////
// FUNCTION:    VNumRecords
//
// DESCRIPTION: This routine return total record number in database.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//
// RETURNED:    Returns total record number in database.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VNumRecords (DmOpenRef dbP)
{
	UInt16	numRecords;

	fseek (dbP, RecordCountOffset, SEEK_SET);
	if ( fread (&numRecords, 2, 1, (FILE *)dbP) ) {
		return	VTransferUInt (numRecords);
	} else {
		return	0;
	}
}

// Below APIs are file relative API, there are 13 functions now.
////////////////////////////////////////////////////////////////////////
// FUNCTION:    VNewRecord
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
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void *VNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size)
{
	UInt16	numRecords, i;
	UInt16	offset;

	fseek (dbP, RecordCountOffset, SEEK_SET);
	fread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);
	numRecords++;
	numRecords = VTransferUInt (numRecords);
	fseek (dbP, RecordCountOffset, SEEK_SET);
	fwrite (&numRecords, 2, 1, dbP);
	fflush (dbP);

	if ( *atP == dmMaxRecordIndex ) {	// add record in the tail of file
		char	buffer[8];

		numRecords = VTransferUInt (numRecords);
		for ( i = 0; i < (numRecords-1); i++ ) {
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fread (&offset, 2, 1, dbP);
			offset = VTransferUInt (offset)+8;
			offset = VTransferUInt (offset);
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fwrite (&offset, 2, 1, dbP);
		}

		fseek (dbP, 0, SEEK_END);
		offset = (UInt16) (ftell (dbP))+8;
		buffer[0] = (char)((offset&0xff00)>>8);
		buffer[1] = (char)(offset&0x00ff);
		buffer[2] = CARDNO;
		buffer[3] = 0x00;
		buffer[4] = 0;
		buffer[5] = (char)numRecords;
		buffer[6] = 0;
		buffer[7] = 0;
		VInsertData (dbP, (UInt16)(DataBaseOffset+(buffer[5]-1)*8), buffer, 8);
	} else {							// add record in the head of file
		char	buffer[8];

		numRecords = VTransferUInt (numRecords);
		for ( i = 0; i < (numRecords-1); i++ ) {
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fread (&offset, 2, 1, dbP);
			offset = VTransferUInt (offset)+8;
			offset = VTransferUInt (offset);
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fwrite (&offset, 2, 1, dbP);
		}

		fseek (dbP, 0, SEEK_END);
		offset = (UInt16) (ftell (dbP))+8;
		buffer[0] = (char)((offset&0xff00)>>8);
		buffer[1] = (char)(offset&0x00ff);
		buffer[2] = CARDNO;
		buffer[3] = 0x00;
		buffer[4] = 0;
		buffer[5] = (char)numRecords;
		buffer[6] = 0;
		buffer[7] = 0;
		VInsertData (dbP, (UInt16)(DataBaseOffset+(buffer[5]-1)*8), buffer, 8);
	}

	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		sysHandle.handle[NUMSYSHANDLE-1] = realloc (sysHandle.handle[NUMSYSHANDLE-1], size);
	else
		sysHandle.handle[NUMSYSHANDLE-1] = malloc (size);

	return	&(sysHandle.handle[NUMSYSHANDLE-1]);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VInsertData
//
// DESCRIPTION: This routine insert data to the specified offset
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//					 (UInt16) offset - the data offset of current record
//					 (char *) data - Pointer to the data to insert.
//					 (UInt16) size - size of data.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/12/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void VInsertData (DmOpenRef dbP, UInt16 offset, char *data, UInt16 size)
{
	char		*buffer;
	UInt32	readlength, filelength;


	fseek (dbP, 0, SEEK_END);
	filelength = ftell (dbP);

	readlength = filelength-offset;
	buffer = (char *)malloc (readlength);

	fseek (dbP, offset, SEEK_SET);
	fread (buffer, 1, readlength, dbP);

	fseek (dbP, offset, SEEK_SET);
	fwrite (data, 1, size, dbP);
	fwrite (buffer, 1, readlength, dbP);

	fflush (dbP);
	free (buffer);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VbeLastRecord
//
// DESCRIPTION: This routine judge that is the record of index been the
//				last record(offset) of database file
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//				(UInt16) index - record index to search
//				(UInt16) offset - record data offset of database file
//				(UInt16) totalRecords - total record in database file
//
// RETURNED:    Returns FALSE if not the last record, TRUE if the last
//				record.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/12/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean VbeLastRecord (DmOpenRef dbP, UInt16 index, UInt16 offset1, UInt16 totalRecords)
{
	UInt16	RecordNo, i, offset2;

	for ( i = 0; i < totalRecords; i++ ) {
		fseek (dbP, (DataBaseOffset+5+i*8), SEEK_SET);
		fread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF)-1;
		if ( RecordNo != index ) {
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fread (&offset2, 2, 1, dbP);
			offset2 = VTransferUInt (offset2);
			if ( offset2 > offset1 ) {
				return	FALSE;
			}
		}
	}

	return	TRUE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetRecordOffset
//
// DESCRIPTION: This routine return the offset of the specified record.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//				(UInt16) index - the index of record to get.
//				(UInt16) totalRecords - total records in databsae.
//
// RETURNED:    Returns the offset of the specified record.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VGetRecordOffset (DmOpenRef dbP, UInt16 index, UInt16 totalRecords)
{
	UInt16	i, offset;
	UInt32	RecordNo;

	for ( i = 0; i < totalRecords; i++ ) {
		fseek (dbP, (DataBaseOffset+i*8+5), SEEK_SET);
		fread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF) -1;
		if ( RecordNo == index ) {
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fread (&offset, 2, 1, dbP);
			return VTransferUInt (offset);
		}
	}

	fseek ( dbP, 0, SEEK_END );

	return	(UInt16) ftell(dbP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VWriteRecord
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
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 VWriteRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset, const void *srcP, UInt32 RecordSize)
{
	UInt16	numRecords;
	UInt16	offset, oldSize;

	fseek (dbP, RecordCountOffset, SEEK_SET);
	fread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords ) {
		return	0;
	}

	// Calculate Record Size
	offset = VGetRecordOffset (dbP, index, numRecords);

	if ( !VbeLastRecord (dbP, index, offset, numRecords) ) {
		oldSize = VGetRecordSize (dbP, offset, numRecords);

		offset = VMoveToLastRecord (dbP, index, offset, oldSize, numRecords);
	}

	fseek (dbP, offset+recOffset, SEEK_SET);
	fwrite (srcP, 1, RecordSize, dbP);

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

	if ( (dbP = fopen (DBFILE, "rb")) != NULL ) {
		fseek (dbP, 0, SEEK_END);
		fileLength = ftell (dbP);

		do {
			fseek (dbP, count, SEEK_SET);
			fread (&length, sizeof(UInt32), 1, dbP);
			fread (&fCardNo, sizeof(UInt16), 1, dbP);
			fread (&fResDB, sizeof(Boolean), 1, dbP);
			fread (&fCreator, sizeof(UInt32), 1, dbP);
			fread (&fType, sizeof(UInt32), 1, dbP);

			// find the right database file
			if ( (creator==fCreator) && (fType==type) ) {
				// hardcore, 16 is creator database header length
				fread (filename, (length-16), 1, dbP);
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

		fclose (dbP);
	} 
	
	// type creator database file not exist, return false
	return	fileFound;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VMoveToLastRecord
//
// DESCRIPTION: This routine move the index record data to the tail
//				of database file
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//				(UInt16) index - record index to search
//				(UInt16) offset - record data offset of database file
//				(UInt16) RecordSize - record size of record
//				(UInt16) totalRecords - total record in database file
//
// RETURNED:   Return the new offset of record
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/12/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VMoveToLastRecord (DmOpenRef dbP, UInt16 index, UInt16 offset1, UInt16 RecordSize, UInt16 totalRecords)
{
	UInt16	RecordNo, i, offset2, newOffset;
	char	*buffer1, *buffer2;

	// Recalculate the new offset of each record
	for ( i = 0; i < totalRecords; i++ ) {
		fseek (dbP, (DataBaseOffset+5+i*8), SEEK_SET);
		fread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF)-1;
		if ( RecordNo != index ) {
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fread (&offset2, 2, 1, dbP);
			offset2 = VTransferUInt (offset2);
			if ( offset2 > offset1 ) {
				offset2 -= RecordSize;
				offset2 = VTransferUInt (offset2);
				fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
				fwrite (&offset2, 2, 1, dbP);
			}
		} else {
			fseek (dbP, 0, SEEK_END);
			newOffset = (UInt16) (ftell (dbP)-RecordSize);
			newOffset = VTransferUInt (newOffset);
			fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			fwrite (&newOffset, 2, 1, dbP);
		}
	}

	// Move the data to the tail of database file
	buffer1 = (char *)malloc (RecordSize);
	newOffset = VTransferUInt (newOffset);
	buffer2 = (char *)malloc ((newOffset-offset1));
	fseek (dbP, offset1, SEEK_SET);
	fread (buffer1, 1, RecordSize, dbP);
	fread (buffer2, 1, newOffset-offset1, dbP);
	fseek (dbP, offset1, SEEK_SET);
	fwrite (buffer2, 1, newOffset-offset1, dbP);
	fwrite (buffer1, 1, RecordSize, dbP);

	return	newOffset;
}



////////////////////////////////////////////////////////////////////////
// FUNCTION:    VResizeRecord
//
// DESCRIPTION: This routine return a handle to the resized record. 
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database.
//					 (UInt16) index - the index of record.
//					 (UInt32) size - Size of new record.
//
// RETURNED:    Handle to the new size record data.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void *VResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 size)
{
	UInt16	numRecords;
	UInt16	offset, oldSize;

	fseek (dbP, RecordCountOffset, SEEK_SET);
	fread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords ) {
		return	0;
	}

	// Calculate Record Size
	offset = (unsigned int)VGetRecordOffset (dbP, index, numRecords);

	if ( !VbeLastRecord (dbP, index, offset, numRecords) ) {
		oldSize = VGetRecordSize (dbP, offset, numRecords);

		offset = VMoveToLastRecord (dbP, index, offset, oldSize, numRecords);
	}

	sysHandle.handle[NUMSYSHANDLE-1] = (void *)realloc (sysHandle.handle[NUMSYSHANDLE-1], size);

	return	sysHandle.handle[NUMSYSHANDLE-1];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VLoadDatabaseFile
//
// DESCRIPTION: This routine write the string to the index position of
//				categories
//
// PARAMETERS:  (char *) filename - The file name of database.
//				(UInt32) type - type of database.
//				(UInt32) creator - Creator ID of database.
//				(Boolean) CreateFlag - flag for create database.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void *VLoadDatabaseFile (char *filename, UInt32 type, UInt32 creator, Boolean CreateFlag)
{
	DmOpenRef dbP;

	if ( CreateFlag ) {
		if ( (dbP = fopen (filename, "wb")) != NULL ) {
			DatabaseHdrType	databaseHdr;
			char	appInfoBlock[0x114];

			memset (appInfoBlock, 0, 0x114);
			memset (&(databaseHdr.name), 0, 32);
			strcpy ((char *)databaseHdr.name, "PMail");
			databaseHdr.appInfoID = 0;
			databaseHdr.attributes = 0x0800;
			databaseHdr.creationDate = 0;		// change to exact date later
			databaseHdr.lastBackupDate = 0;		// change to exact date later
			databaseHdr.modificationDate = 0;	// change to exact date later
			databaseHdr.creator = VTransferUInt32(creator);
			databaseHdr.modificationNumber = 0;
			databaseHdr.recordList.firstEntry = 0;
			databaseHdr.recordList.nextRecordListID = 0;
			databaseHdr.recordList.numRecords = 0;
			databaseHdr.sortInfoID = 0;
			databaseHdr.type = VTransferUInt32(type);
			databaseHdr.uniqueIDSeed = 0;
			databaseHdr.version = 0;

			fwrite (&databaseHdr, 1, sizeof (databaseHdr), dbP);	// write PDB header
			fwrite (appInfoBlock, 1, 0x114, dbP);	// write appInfo Block

			return	dbP;
		}
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VReleaseRecord
//
// DESCRIPTION: This routine clear the busy bit for the given record 
//				and the dirty bit if dirty is true
//
// PARAMETERS:  (DmOpenRef) dbP - DmOpenRef to open database
//				(UInt16) index - The record to unlock
//				(Boolean) dirty - If true, set the dirty bit
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 VReleaseRecord ()
{
	if ( sysHandle.handle[NUMSYSHANDLE-1] ) {
		free (sysHandle.handle[NUMSYSHANDLE-1]);
		sysHandle.handle[NUMSYSHANDLE-1] = NULL;
	}

	return	0;
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
	if ( strlen (PDBFilename) ) {
		currentDBP =(struct _iobuf *) VLoadDatabaseFile (PDBFilename, type, creator, CreateDB);
		return	currentDBP;
	} else if ( WSearchDatabaseByTypeCreator (type, creator, mode, PDBFilename) ) {
		currentDBP =(struct _iobuf *) VLoadDatabaseFile (PDBFilename, type, creator, CreateDB);
		return	currentDBP;
	}

	return	NULL;
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
	curCardNo = cardNo;
	curResDB = resDB;
	curCreator = creator;
	curType = type;

	strcpy (PDBFilename, directory);
	strcat (PDBFilename, "\\");
	strcat (PDBFilename, nameP);
	strcat (PDBFilename, ".PDB");
	CreateDB = TRUE;

	return	dmErrAlreadyExists;
}

Boolean WNewHandle ()
{
	if ( sysHandle.count < NUMSYSHANDLE-1 ) {
		sysHandle.locked[sysHandle.count] = 0;

		return	TRUE;
	}

	return	FALSE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DmNewHandle
//
// DESCRIPTION: This routine Attempt to allocate a new chuck in the same
//				data heap or card as the database header of the passed 
//				database access pointer. If there is not enough space
//				in the data hap, try other heaps.
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
	sysHandle.handle[NUMSYSHANDLE-1] = (void *)malloc (size);

	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		return	&(sysHandle.handle[NUMSYSHANDLE-1]);
	else
		return	NULL;
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
	dmMode=dmModeReadWrite;
	currentDBP = dbP;
	if ( *atP == dmMaxRecordIndex ) {	// add record in the tail of file
		currentRecord = VNumRecords (dbP);
	} else {
		currentRecord = *atP;
	}

	if ( !VNewRecord ( dbP, atP, size ) )
		return	NULL;

	return	&(sysHandle.handle[NUMSYSHANDLE-1]);
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

	if ( sysHandle.handle[NUMSYSHANDLE-1] )
		return	&(sysHandle.handle[NUMSYSHANDLE-1]);
	else
		return	NULL;
}


////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleLock
//
// DESCRIPTION: This routine lock a chunk and obtain a pointer to the
//				chuck's data
//
// PARAMETERS:  (MemHandle) h - Chunk handle.
//
// RETURNED:    Returns a pointer to the chunk
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01		Initial Revision
//			Jerry	10/09/01	Modify to use sysHandle structure
////////////////////////////////////////////////////////////////////////
MemPtr MemHandleLock (MemHandle h)
{
	if ( (h >= sysHandle.handle) && (h <= (sysHandle.handle+NUMSYSHANDLE)) )
		return	sysHandle.handle[(h-sysHandle.handle)];

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleUnlock
//
// DESCRIPTION: This routine unlock a chunk given a chunk handle
//
// PARAMETERS:  (MemHandle) h - Chunk handle.
//
// RETURNED:    Returns 0 if no error or error code if error occurs
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01	Initial Revision
//			Jerry	10/09/01	Modify to use sysHandle structure
////////////////////////////////////////////////////////////////////////
Err MemHandleUnlock (MemHandle h)
{
	int	index;

	if ( (h >= sysHandle.handle) && (h <= (sysHandle.handle+NUMSYSHANDLE)) ) {
		index = h-sysHandle.handle;
		if ( sysHandle.locked[index] ) {
			sysHandle.locked[index] = FALSE;

			return	0;
		}
	}

	return	-1;
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
	return	(int)memset (((Char *)recordP+offset), bytes, value);
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
		fflush (dbP);

		return	VReleaseRecord () ;
	} else {
		return	-1;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetRecordSize
//
// DESCRIPTION: This routine get the record size of current record
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//				(UInt16) offset1 - the data offset of current record
//				(UInt16) totalRecords - total record in database file
//
// RETURNED:    Returns the record size of current record
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/12/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VGetRecordSize (DmOpenRef dbP, UInt16 offset1, UInt16 totalRecords)
{
	UInt16	i, offset2, minOffset;

	fseek ( dbP, 0, SEEK_END );
	minOffset = (UInt16) (ftell(dbP));
	for ( i = 0; i < totalRecords; i++ ) {
		fseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
		fread (&offset2, 2, 1, dbP);
		offset2 = VTransferUInt (offset2);
		if ( (offset2 > offset1) && (offset2 < minOffset) ) {
			minOffset = offset2;
		}
	}

	return	minOffset-offset1;
}

