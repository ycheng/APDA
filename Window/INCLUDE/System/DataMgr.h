#ifndef __DATABASE_H__
#define __DATABASE_H__


typedef UInt32	DmResType;

/************************************************************
 * Database Header equates
 *************************************************************/
#define	dmDBNameLength				32			// 31 chars + 1 null terminator


// Record Attributes 
#define	dmRecAttrDelete			0x80	// delete this record next sync
#define	dmRecAttrDirty				0x40	// archive this record next sync
#define	dmRecAttrBusy				0x20	// record currently in use
#define	dmRecAttrSecret			0x10	// "secret" record - password protected


// Attributes of a Database
#define	dmHdrAttrResDB					0x0001	// Resource database
#define 	dmHdrAttrReadOnly				0x0002	// Read Only database
#define	dmHdrAttrAppInfoDirty		0x0004	// Set if Application Info block is dirty
															// Optionally supported by an App's conduit
#define	dmHdrAttrBackup				0x0008	//	Set if database should be backed up to PC if
															//	no app-specific synchronization conduit has
															//	been supplied.
#define	dmHdrAttrOpen					0x8000	// Database not closed properly

															
/************************************************************
 * Category equates
 *************************************************************/
#define	dmRecAttrCategoryMask	0x0F	// mask for category #
#define	dmRecNumCategories		16		// number of categories
#define	dmCategoryLength			16		// 15 chars + 1 null terminator

#define  dmAllCategories			0xff
#define  dmUnfiledCategory  		0

#define	dmMaxRecordIndex			0xffff


/************************************************************
 * Structure passed to DmGetNextDatabaseByTypeCreator and used
 *  to cache search information between multiple searches.
 *************************************************************/
typedef struct {
	DWord		info[8];
	} DmSearchStateType;
typedef DmSearchStateType*	DmSearchStatePtr;	


/************************************************************
 * Structure of a record list extension. This is used if all
 *  the database record/resource entries of a database can't fit into
 *  the database header.
 *************************************************************/
typedef struct {
	LocalID				nextRecordListID;			// local chunkID of next list
	Word					numRecords;					// number of records in this list
	Word					firstEntry;					// array of Record/Rsrc entries 
															// starts here
	} RecordListType;
typedef RecordListType*	RecordListPtr;

/************************************************************
 * Structure of a Database Header
 *************************************************************/
typedef struct {
	Byte			name[dmDBNameLength];	// name of database
	Word			attributes;					// database attributes
	Word			version;						// version of database

	DWord			creationDate;				// creation date of database
	DWord			modificationDate;			// latest modification date
	DWord			lastBackupDate;			// latest backup date
	DWord			modificationNumber;		// modification number of database

	LocalID		appInfoID;					// application specific info
	LocalID		sortInfoID;					// app specific sorting info

	DWord			type;							// database type
	DWord			creator;						// database creator 
	
	DWord			uniqueIDSeed;				// used to generate unique IDs.
													//	Note that only the low order
													//	3 bytes of this is used (in
													//	RecordEntryType.uniqueID).
													//	We are keeping 4 bytes for 
													//	alignment purposes.

	RecordListType	recordList;				// first record list
} DatabaseHdrType;		

typedef DatabaseHdrType*	DatabaseHdrPtr;
typedef DatabaseHdrPtr*		DatabaseHdrHand;

#endif // __DATABASE_H__
