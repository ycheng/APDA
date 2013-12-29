#include <stdio.h>

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#include <apidll.h>
#include <WisDll.h>

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#define	RecordCountOffset		0x4C
#define	DataBaseOffset			0x50
#define	RecordOffset			0x114
#define	CategoryOffset			0x52
#define	CARDNO					0x40


Boolean	vBeQuit=FALSE;

extern UInt16		menuCount;
char	*RCPFileName=NULL;
Char	*GlobalText=NULL;
extern SYSHandle	sysHandle;

UInt16 VGetRecordOffset (DmOpenRef dbP, UInt16 index, UInt16 totalRecords);
UInt16 VGetRecordSize (DmOpenRef dbP, UInt16 offset1, UInt16 totalRecords);
UInt16 VGetRecordIndexOffset (DmOpenRef dbP, UInt16 index, UInt16 totalRecords);
UInt16 VMoveToLastRecord (DmOpenRef dbP, UInt16 index, UInt16 offset1, UInt16 RecordSize, UInt16 totalRecords);
void VInsertData (DmOpenRef dbP, UInt16 offset, char *data, UInt16 size);
void VWriteNumRecords (DmOpenRef dbP, UInt numRecords);
void VGetRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset);
UInt16 VNumRecords (DmOpenRef dbP);
UInt16 VTransferUInt (UInt16 num);
UInt32 VTransferUInt32 (UInt32 num);
void VPDAToSysRect(RectangleType *dstRect, const RectangleType *srcRect);

extern void WDestroyForm();
extern void WDestroyMenu();

// Below APIs are category relative API, there are 3 functions now.
////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategorySetName
//
// DESCRIPTION: This routine set the category name and rename bits.
//				A NULL pointer removes the category name.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Index of category to set.
//				(const char *) name - A Category name (null-terminated) or 
//									NULL pointe to remove the category.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/03/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void VCategorySetName (DmOpenRef dbP, UInt16 index, const char *name)
{
	UInt16	numRecords;
	char	zero[16];

	Vmemset (zero, 0, 16);

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	Vfseek (dbP, CategoryOffset+numRecords*8+index*16, SEEK_SET);
	Vfwrite (name, 1, Vstrlen(name), dbP);
	Vfwrite (zero, 1, 16-Vstrlen(name), dbP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetCategory
//
// DESCRIPTION: This routine return the unique ID of the category .
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Which category to retrieve
//
// RETURNED:    return the category index.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VGetCategory (DmOpenRef dbP, UInt16 index)
{
	UInt16	numRecords;
	UInt16	offset;
	UInt16	category;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords )
		return	dmAllCategories;

	// Get Record Size
	offset = CategoryOffset+index*8;

	Vfseek (dbP, offset, SEEK_SET);
	Vfread (&category, sizeof(UInt16), 1, dbP);

	if ( category == 0x64 )
		return	0xff;
	else
		return	category-0x40;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VSetCategory
//
// DESCRIPTION: This routine set the specified record category .
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//					 (UInt16) index - Which category to retrieve
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err VSetCategory (DmOpenRef dbP, UInt16 index, UInt16 category)
{
	UInt16	numRecords;
	UInt16	offset;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords )
		return	dmAllCategories;

	// Get Record Size
	offset = VGetRecordIndexOffset (dbP, index, numRecords);

	Vfseek (dbP, offset, SEEK_SET);
	category += 0x40;
	Vfwrite (&category, sizeof(UInt16), 1, dbP);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetCategoryName
//
// DESCRIPTION: This routine get the specific string of categories
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Which category to retrieve
//				(void *) srcP - the pointer of string to put the Name of 
//								new category.
//
// RETURNED:    true if database containing category info, false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean VGetCategoryName (DmOpenRef dbP, UInt16 index, void *srcP)
{
	UInt16	numRecords;
	Char	*buffer;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	// Calculate Record Size
	Vfseek (dbP, CategoryOffset+numRecords*8+index*16, SEEK_SET);
	Vfread (srcP, 16, 1, dbP);

	buffer = (Char *)srcP;
	if (buffer[0])
		return	TRUE;
	else
		return	FALSE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VWriteCategory
//
// DESCRIPTION: This routine write the string to the index position of
//				categories
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Which category to retrieve
//				(void *) srcP - Name of new category, up to 16 ASCII 
//									bytes long, including the null terminator.
//				(UInt32) RecordSize - the size of name of category.
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/13/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void VWriteCategory (DmOpenRef dbP, UInt16 index, const void *srcP, UInt32 RecordSize)
{
	UInt16	numRecords;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	// Calculate Record Size
	Vfseek (dbP, CategoryOffset+numRecords*8+index*16, SEEK_SET);
	Vfwrite (srcP, 1, RecordSize, dbP);
}

// Below APIs are file relative API, there are 13 functions now.
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
		Vfseek (dbP, (DataBaseOffset+5+i*8), SEEK_SET);
		Vfread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF)-1;
		if ( RecordNo != index ) {
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfread (&offset2, 2, 1, dbP);
			offset2 = VTransferUInt (offset2);
			if ( offset2 > offset1 ) {
				return	FALSE;
			}
		}
	}

	return	TRUE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VCloseDatabaseFile
//
// DESCRIPTION: This routine close the opened database
//
// PARAMETERS:  (DmOpenRef) dbP - The handle of database.
//
// RETURNED:    Returns 0 if successfully closed, otherwise return 
//				error code.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int VCloseDatabaseFile (DmOpenRef dbP)
{
	if ( !Vfclose (dbP) ) {
		dbP = NULL;

		return	0;
	} else {
		return	-1;
	}
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

	if ( (dbP = Vfopen (filename, "r+b")) != NULL ) {
		return	dbP;
	}

	if ( CreateFlag ) {
		if ( (dbP = Vfopen (filename, "w+b")) != NULL ) {
			DatabaseHdrType	databaseHdr;
			char	appInfoBlock[0x114];

			Vmemset (appInfoBlock, 0, 0x114);
			Vmemset (&(databaseHdr.name), 0, 32);
			Vstrncpy (databaseHdr.name, filename, Vstrlen(filename)-4);
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

			Vfwrite (&databaseHdr, 1, sizeof (databaseHdr), dbP);	// write PDB header
			Vfwrite (appInfoBlock, 1, 0x114, dbP);	// write appInfo Block

			return	dbP;
		}
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VFileOpen
//
// DESCRIPTION: This routine open existing file stream or create an open
//					 file stream for I/O in the mode specified by the openMode
//					 parameter
//
// PARAMETERS:  (char *) filename - The file name of database.
//					 (UInt32) type - type of database.
//					 (UInt32) creator - Creator ID of database.
//					 (UInt32) mode - open mode of database.
//
// RETURNED:    Returns File Handle of file stream.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void *VFileOpen (char *filename, UInt32 type, UInt32 creator, UInt32 mode)
{
	DmOpenRef	fileP;

	if ( (fileP = Vfopen (filename, (Char *)mode)) != NULL ) {
		Vfwrite (&type, sizeof (UInt32), 1, fileP);	// write type
		Vfwrite (&creator, sizeof (UInt32), 1, fileP);	// write creator

		return	fileP;
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LoadRCP
//
// DESCRIPTION: This routine load the RCP file.
//
// PARAMETERS:  
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean LoadRCP ()
{
	DmOpenRef	dbP;
	char		*buffer;
	int		length;
	Boolean	rtn;

	if ( Vstrlen(RCPFileName) ) {
		if ( (dbP = Vfopen (RCPFileName, "rt")) != NULL ) {
			Vfseek (dbP, 0, SEEK_END);
			length = Vftell (dbP);
			buffer = (char *)Vmalloc ((length+1));

			Vfseek (dbP, 0, SEEK_SET);
			length = Vfread (buffer, 1, length, dbP);
			Vfclose (dbP);

			rtn = ParseRCP (buffer, length);
			Vfree (buffer);
			return	rtn;
		}
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VLoadResource
//
// DESCRIPTION: This routine get the list of name and id in resource file.
//
// PARAMETERS:  (char *) filename - resource file name.
//				(char **) sIDList - Pointer to ID string list.
//				(short *) iIDList - Pointer to ID integer list.
//
// RETURNED:    Returns the number of id in resource file.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
short VLoadResource (char *filename)
{
	DmOpenRef	dbP;
	char		*buffer;
	int		length, errno;

	if ( (dbP = Vfopen (filename, "rt")) != NULL ) {
		Vfseek (dbP, 0, SEEK_END);
		length = Vftell (dbP);
		buffer = Vmalloc ((length+1));
		Vfseek (dbP, 0, SEEK_SET);
		Vfread (buffer, 1, length, dbP);
		Vfclose (dbP);
		errno = ParseInclude (buffer, length);

		Vfree (buffer);
		buffer = NULL;
		return	errno;
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VAddRecord
//
// DESCRIPTION: This routine add application information into database.
//
// PARAMETERS:  (const Char *) szFileName - Pointer to application file 
//													name string.
//					 (const Char *) resourceFileName - Pointer to resource
//													file name string.
//
// RETURNED:    Returns true if install successful, false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/20/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 VAddRecord (DmOpenRef dbP, UInt16 index, const void *srcP, UInt32 RecordSize)
{
	UInt16	numRecords, i;
	UInt16	offset;
	char	buffer[8];

	// add record number by 1
	numRecords = VNumRecords (dbP);
	numRecords++;
	VWriteNumRecords (dbP, numRecords);

	// write record information
	for ( i = 0; i < (numRecords-1); i++ ) {
		Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
		Vfread (&offset, 2, 1, dbP);
		offset = VTransferUInt (offset)+8;
		offset = VTransferUInt (offset);
		Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
		Vfwrite (&offset, 2, 1, dbP);
	}

	Vfseek (dbP, 0, SEEK_END);
//	offset = (UInt16) (Vftell (dbP)-RecordOffset);
	offset = (UInt16) Vftell (dbP);
	buffer[0] = (char)((offset&0xff00)>>8);
	buffer[1] = (char)(offset&0x00ff)+8;
	buffer[2] = CARDNO;
	buffer[3] = 0x00;
	buffer[4] = 0;
	buffer[5] = (char)numRecords;
	buffer[6] = 0;
	buffer[7] = 0;
	VInsertData (dbP, (UInt16)(DataBaseOffset+(buffer[5]-1)*8), buffer, 8);
 
	// Calculate Record Size
	Vfseek (dbP, 0, SEEK_END);
	Vfwrite (srcP, 1, RecordSize, dbP);

	return	0;
}

void VCopyHeaderInfo (void *dstfp, void *rscfp)
{
	char	buffer[RecordOffset+10];
	int	numRecords;

	numRecords = VNumRecords (rscfp);

	Vfseek (rscfp, 0, SEEK_SET);
	Vfread (buffer, 1, DataBaseOffset, rscfp);
	Vfwrite (buffer, 1, DataBaseOffset, dstfp);

	Vfseek (rscfp, numRecords*8, SEEK_CUR);
	Vfread (buffer, 1, RecordOffset+10, rscfp);
	Vfwrite (buffer, 1, RecordOffset+10, dstfp);

	VWriteNumRecords (dstfp, 0);
	Vfflush (dstfp);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDeleteRecord
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
void VDeleteRecord (DmOpenRef dbP, UInt16 index)
{
	UInt16	numRecords;
	UInt16	RecordSize;
	UInt16	offset;
	UInt16	fileLength;
	UInt16	i, recordIndex;
	unsigned char	*buffer;

	// check the correct index
	numRecords = VNumRecords (dbP);
	if ( index >= numRecords )
		return;

	// Read all data into memory for processing conviniently
	Vfseek (dbP, 0, SEEK_END);
	fileLength = (UInt16) Vftell (dbP);
	Vfseek (dbP, 0, SEEK_SET);
	buffer = Vmalloc (fileLength);
	fread (buffer, 1, fileLength, dbP);

	// Remove the record from tempopary memory data
	offset = VGetRecordOffset (dbP, index, numRecords);
	RecordSize = VGetRecordSize (dbP, offset, numRecords);
	Vmemcpy (&(buffer[offset]), &(buffer[offset+RecordSize]), (fileLength-offset-RecordSize));
	fileLength -= RecordSize;

	// Remove record index from tempopary memory data
	offset = (DataBaseOffset+index*8);
	Vmemcpy (&(buffer[offset]), &(buffer[offset+8]), (fileLength-offset-8));
	fileLength -= 8;

	// Adjust record offset data
	numRecords--;
	for ( i = 0; i < numRecords; i++ ) {
		if ( i < index ) {
			// Get offset of record index data
			offset = (buffer[DataBaseOffset+i*8]<<8)+buffer[DataBaseOffset+i*8+1];
			offset -= 8;
			buffer[DataBaseOffset+i*8] = (unsigned char)((offset&0xff00)>>8);
			buffer[DataBaseOffset+i*8+1] = (unsigned char)(offset&0xff);
		} else {
			// Get offset of record index data
			offset = (buffer[DataBaseOffset+i*8]<<8)+buffer[DataBaseOffset+i*8+1];
			offset -= (8+RecordSize);
			buffer[DataBaseOffset+i*8] = (unsigned char)((offset&0xff00)>>8);
			buffer[DataBaseOffset+i*8+1] = (unsigned char)(offset&0xff);
			// record index - 1
			recordIndex = VTransferUInt ((UInt16)(i+1));
			buffer[DataBaseOffset+i*8+5] = (unsigned char)((recordIndex&0xff00)>>8);
			buffer[DataBaseOffset+i*8+6] = (unsigned char)(recordIndex&0xff);
		}
	}

	// write back the memory data into the database
	if ( (dbP = Vfopen (PDBFilename, "wb+")) == NULL ) {
		Vfree (buffer);
		Vfclose (dbP);
		return;
	}
	fwrite (buffer, 1, fileLength, dbP);
	VCloseDatabaseFile (dbP);
	Vfree (buffer);

	// reopen database in user opend mode
	if ( (dbP = Vfopen (PDBFilename, "rb+")) == NULL ) {
		Vfclose (dbP);
		return;
	}

	// Adjust the numRecords
	VWriteNumRecords (dbP, numRecords);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetRecord
//
// DESCRIPTION: This routine return the record data of the specified record.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//					 (UInt16) index - the record index to get.
//					 (UInt16) recOffset - the offset of the specified record.
//					 (char *) buffer - Point to buffer to store the data
//
// RETURNED:    Returns the record data of the specified record.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/02/01	Initial Revision
//			Jerry	8/24/01	Add NULL terminator to read data
////////////////////////////////////////////////////////////////////////
void VGetRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset)
{
	UInt16	numRecords;
	UInt16	RecordSize;
	UInt16	offset;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords ) {
		if ( sysHandle.handle[NUMSYSHANDLE-1] ) {
			Vfree (sysHandle.handle[NUMSYSHANDLE-1]);
			sysHandle.handle[NUMSYSHANDLE-1] = NULL;
			sysHandle.size[NUMSYSHANDLE-1] = 0;
			sysHandle.locked[NUMSYSHANDLE-1] = false;
		}
		return;
	}

	// Get Record Size
	offset = VGetRecordOffset (dbP, index, numRecords);
	RecordSize = VGetRecordSize (dbP, offset, numRecords);

	//	move to data record
	Vfseek (dbP, offset+recOffset, SEEK_SET);

	if ( RecordSize == 0 ) {
		if ( sysHandle.handle[NUMSYSHANDLE-1] ) {
			Vfree (sysHandle.handle[NUMSYSHANDLE-1]);
			sysHandle.handle[NUMSYSHANDLE-1] = NULL;
		}
	} else {
		sysHandle.handle[NUMSYSHANDLE-1] = 
				Vrealloc (sysHandle.handle[NUMSYSHANDLE-1], RecordSize);
		Vmemset (sysHandle.handle[NUMSYSHANDLE-1], 0, RecordSize);
		Vfread (sysHandle.handle[NUMSYSHANDLE-1], 1, RecordSize, dbP);
	}
	sysHandle.size[NUMSYSHANDLE-1] = RecordSize;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetRecordIndexOffset
//
// DESCRIPTION: This routine return the offset of the specified record
//					 index.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//				(UInt16) index - the index of record to get.
//				(UInt16) totalRecords - total records in databsae.
//
// RETURNED:    Returns the offset of the specified record index.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/02/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 VGetRecordIndexOffset (DmOpenRef dbP, UInt16 index, UInt16 totalRecords)
{
	UInt16	i;
	UInt32	RecordNo;

	for ( i = 0; i < totalRecords; i++ ) {
		Vfseek (dbP, (DataBaseOffset+i*8+5), SEEK_SET);
		Vfread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF) -1;
		return CategoryOffset+i*8;
	}

	Vfseek ( dbP, 0, SEEK_END );

	return	(UInt16) Vftell(dbP);
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
		Vfseek (dbP, (DataBaseOffset+i*8+5), SEEK_SET);
		Vfread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF) -1;
		if ( RecordNo == index ) {
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfread (&offset, 2, 1, dbP);
			return VTransferUInt (offset);
		}
	}

	Vfseek ( dbP, 0, SEEK_END );

	return	(UInt16) Vftell(dbP);
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

	Vfseek ( dbP, 0, SEEK_END );
	minOffset = (UInt16) Vftell(dbP);
	for ( i = 0; i < totalRecords; i++ ) {
		Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
		Vfread (&offset2, 2, 1, dbP);
		offset2 = VTransferUInt (offset2);
		if ( (offset2 > offset1) && (offset2 < minOffset) ) {
			minOffset = offset2;
		}
	}

	return	minOffset-offset1;
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


	Vfseek (dbP, 0, SEEK_END);
	filelength = Vftell (dbP);

	readlength = filelength-offset;
	buffer = Vmalloc (readlength);

	Vfseek (dbP, offset, SEEK_SET);
	Vfread (buffer, 1, readlength, dbP);

	Vfseek (dbP, offset, SEEK_SET);
	Vfwrite (data, 1, size, dbP);
	Vfwrite (buffer, 1, readlength, dbP);

	Vfflush (dbP);
	Vfree (buffer);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetRecordNo
//
// DESCRIPTION: This routine returns the record index number.
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//					 (UInt16) index - record index to search
//
// RETURNED:   Returns the record index number.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 VGetRecordNo (DmOpenRef dbP, UInt16 index)
{
	UInt32	RecordNo;

	// Recalculate the new offset of each record
	Vfseek (dbP, (DataBaseOffset+5+index*8), SEEK_SET);
	Vfread (&RecordNo, 3, 1, dbP);
	RecordNo = (RecordNo&0x00FFFFFF)-1;

	return	RecordNo;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VSetRecordNo
//
// DESCRIPTION: This routine set the record index number.
//
// PARAMETERS:  (DmOpenRef) dbP - pointer to the Memo database file
//					 (UInt16) index - record index to search
//					 (UInt32) RecordNo - record number of specified record.
//
// RETURNED:   Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err VSetRecordNo (DmOpenRef dbP, UInt16 index, UInt32 RecordNo)
{
	UInt32	data;

	// Recalculate the new offset of each record
	Vfseek (dbP, (DataBaseOffset+4+index*8), SEEK_SET);
	Vfread (&data, 4, 1, dbP);

	data = (data&0xFF000000) | ((RecordNo+1) & 0x00FFFFFF);

	Vfseek (dbP, (DataBaseOffset+4+index*8), SEEK_SET);
	Vfwrite (&data, 4, 1, dbP);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDatabaseSize
//
// DESCRIPTION: This routine return total number of bytes used by the
//					 database.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//
// RETURNED:    Returns total number of bytes used by the database.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 VDatabaseSize (DmOpenRef dbP)
{
	Vfseek (dbP, 0, SEEK_END);

	return (UInt32) Vftell (dbP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDataSize
//
// DESCRIPTION: This routine return total number of bytes used to store
//					 data records.
//
// PARAMETERS:  (DmOpenRef) dbP - Pointer to database file.
//
// RETURNED:    Returns total number of bytes used to store data records.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/09/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 VDataSize (DmOpenRef dbP)
{
	UInt16	offset, numRecords, index, minOffset = 0xffff;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	for ( index = 0; index < numRecords; index++ ) {
		Vfseek (dbP, (DataBaseOffset+index*8), SEEK_SET);
		Vfread (&offset, 2, 1, dbP);
		offset = VTransferUInt (offset);
		if ( offset < minOffset )
			minOffset = offset;
	}

	Vfseek (dbP, 0, SEEK_END);

	return (UInt32) (Vftell (dbP)-minOffset);
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

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	if ( fread (&numRecords, 2, 1, (FILE *)dbP) ) {
		return	VTransferUInt (numRecords);
	} else {
		return	0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VWriteNumRecords
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
void VWriteNumRecords (DmOpenRef dbP, UInt numRecords)
{
	numRecords = VTransferUInt (numRecords);
	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfwrite (&numRecords, 2, 1, dbP);
	Vfflush (dbP);
}

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
//			Jerry	2/27/01	Initial Revision
//			Jerry	12/06/01	Append record if new an existing record
////////////////////////////////////////////////////////////////////////
void *VNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size)
{
	UInt16	numRecords, i;
	UInt16	offset;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);
	numRecords++;
	numRecords = VTransferUInt (numRecords);
	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfwrite (&numRecords, 2, 1, dbP);
	Vfflush (dbP);

	if ( *atP == dmMaxRecordIndex ) {	// add record in the tail of file
		char	buffer[8];

		numRecords = VTransferUInt (numRecords);
		for ( i = 0; i < (numRecords-1); i++ ) {
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfread (&offset, 2, 1, dbP);
			offset = VTransferUInt (offset)+8;
			offset = VTransferUInt (offset);
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfwrite (&offset, 2, 1, dbP);
		}

		Vfseek (dbP, 0, SEEK_END);
//		offset = (UInt16) (Vftell (dbP)-RecordOffset);
		offset = (UInt16) (Vftell (dbP)+8);
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
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfread (&offset, 2, 1, dbP);
			offset = VTransferUInt (offset)+8;
			offset = VTransferUInt (offset);
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfwrite (&offset, 2, 1, dbP);
		}

		Vfseek (dbP, 0, SEEK_END);
//		offset = (UInt16) (Vftell (dbP)-RecordOffset+8);
		offset = (UInt16) (Vftell (dbP)+8);
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

	if ( sysHandle.handle[NUMSYSHANDLE-1] ) {
		sysHandle.handle[NUMSYSHANDLE-1] = 
					Vrealloc (sysHandle.handle[NUMSYSHANDLE-1], size);
		sysHandle.size[NUMSYSHANDLE-1] = size;
	} else {
		sysHandle.handle[NUMSYSHANDLE-1] = Vmalloc (size);
		Vmemset (sysHandle.handle[NUMSYSHANDLE-1], 0, size);
		sysHandle.size[NUMSYSHANDLE-1] = size;
	}

//	VWriteRecord (dbP, *atP, 0, sysHandle.handle, size);

	return	&(sysHandle.handle[NUMSYSHANDLE-1]);
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
		Vfseek (dbP, (DataBaseOffset+5+i*8), SEEK_SET);
		Vfread (&RecordNo, 3, 1, dbP);
		RecordNo = (RecordNo&0x00FFFFFF)-1;
		if ( RecordNo != index ) {
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfread (&offset2, 2, 1, dbP);
			offset2 = VTransferUInt (offset2);
			if ( offset2 > offset1 ) {
				offset2 -= RecordSize;
				offset2 = VTransferUInt (offset2);
				Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
				Vfwrite (&offset2, 2, 1, dbP);
			}
		} else {
			Vfseek (dbP, 0, SEEK_END);
//			newOffset = (UInt16) (Vftell (dbP)-RecordSize-RecordOffset);
			newOffset = (UInt16) (Vftell (dbP)-RecordSize);
			newOffset = VTransferUInt (newOffset);
			Vfseek (dbP, (DataBaseOffset+i*8), SEEK_SET);
			Vfwrite (&newOffset, 2, 1, dbP);
		}
	}

	// Move the data to the tail of database file
	buffer1 = Vmalloc (RecordSize);
	newOffset = VTransferUInt (newOffset);
	buffer2 = Vmalloc ((newOffset-offset1));
//	Vfseek (dbP, offset1+RecordOffset, SEEK_SET);
	Vfseek (dbP, offset1, SEEK_SET);
	Vfread (buffer1, 1, RecordSize, dbP);
	Vfread (buffer2, 1, newOffset-offset1, dbP);
//	Vfseek (dbP, offset1+RecordOffset, SEEK_SET);
	Vfseek (dbP, offset1, SEEK_SET);
	Vfwrite (buffer2, 1, newOffset-offset1, dbP);
	Vfwrite (buffer1, 1, RecordSize, dbP);
	Vfree (buffer2);
	Vfree (buffer1);

	return	newOffset;
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
		Vfree (sysHandle.handle[NUMSYSHANDLE-1]);
		sysHandle.handle[NUMSYSHANDLE-1] = NULL;
		sysHandle.size[NUMSYSHANDLE-1] = 0;
	}

	return	0;
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

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
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

	sysHandle.handle[NUMSYSHANDLE-1] = 
				Vrealloc (sysHandle.handle[NUMSYSHANDLE-1], size);
	sysHandle.size[NUMSYSHANDLE-1] = size;

	return	sysHandle.handle[NUMSYSHANDLE-1];
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

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
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

//	Vfseek (dbP, offset+RecordOffset+recOffset, SEEK_SET);
	Vfseek (dbP, offset+recOffset, SEEK_SET);
	Vfwrite (srcP, 1, RecordSize, dbP);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VWriteRecordInfo
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
Int16 VWriteRecordInfo (DmOpenRef dbP, UInt16 index, char *srcP)
{
	UInt16	numRecords;

	Vfseek (dbP, RecordCountOffset, SEEK_SET);
	Vfread (&numRecords, 2, 1, dbP);
	numRecords = VTransferUInt (numRecords);

	if ( index >= numRecords ) {
		return	0;
	}

	srcP[0] |= 0x40;
	Vfseek (dbP, DataBaseOffset+index*8+2, SEEK_SET);
	Vfwrite (srcP, sizeof(UInt16), 1, dbP);

	return	0;
}


UInt16 VTransferUInt (UInt16 num)
{
	return	((num>>8)&0x00FF) | ((num<<8)&0xFF00);
}

UInt32 VTransferUInt32 (UInt32 num)
{
	return	((num>>24)&0x000000FF) | ((num>>8)&0x0000FF00) | 
		((num<<8)&0x00FF0000) | ((num<<24)&0xFF000000);
}

void VAppendStr (Char *str, WChar wchar)
{
	UInt16	size=(UInt16) Vstrlen(str);

	if ( (wchar & 0xFF00) ) {	// it's a two bytes code
		str[size] = (char)(((wchar&0xFF00)>>8)&0x00FF);
		str[size+1] = (char)(wchar&0x00FF);
		str[size+2] = 0;
	} else {					// it's a one byte code
		if ( wchar == 0x08 ) {	// input backspace, erase character
			if ( ((UChar)str[size-2] > 0x80) && ((UChar)str[size-2] <= 0xB8) ) {	// earse two bytes charater
				if ( (size-2) <= 0 ) {
					str[0] = 0;
				} else {
					str[size-2] = 0;
				}
			} else {
				if ( (size-1) <= 0 ) {
					str[0] = 0;
				} else {
					str[size-1] = 0;
				}
			}

		} else {				// add input character to string
			str[size] = (char)(wchar&0x00FF);
			str[size+1] = 0;

		}
	}
}

Boolean VSetRCPFile (Char *filename)
{
	int	size = Vstrlen (filename);

	if ( RCPFileName ) {
		Vfree (RCPFileName);
		RCPFileName = NULL;
	}
	RCPFileName = Vmalloc ((size+1));
	Vstrcpy (RCPFileName, filename);
	RCPFileName[size] = 0;
	return	LoadRCP ();
}


