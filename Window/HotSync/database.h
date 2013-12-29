
// data type redefine
typedef  char                 Char;
typedef  unsigned char        Byte;
typedef  Byte                 UInt8;
typedef  unsigned int         UInt16;
typedef  unsigned int         Word;
typedef  int                  Int16;
typedef  int                  Err; 
typedef  BOOL                 Boolean;
typedef  unsigned long        DWord;
typedef  unsigned long        UInt32;
typedef  unsigned long        LocalID;
 
typedef  FILE*						DmOpenRef;
typedef  void*                MemPtr;
//
#define	RecordCountOffset		0x4C
#define	DataBaseOffset			0x50
#define	RecordOffset			0x114
#define	CategoryOffset			0x52
#define	CARDNO					0x40

/************************************************************
 * Database Header equates
 *************************************************************/
#define	dmDBNameLength				32			// 31 chars + 1 null terminator

/************************************************************
 * Mode flags passed to DmOpenDatabase
 *************************************************************/
#define	dmModeReadOnly				0x0001		// read  access
#define	dmModeWrite					0x0002		// write access
#define	dmModeReadWrite				0x0003		// read & write access
#define	dmModeLeaveOpen				0x0004		// leave open when app quits
#define	dmModeExclusive				0x0008		// don't let anyone else open it
#define	dmModeShowSecret			0x0010		// force show of secret records


#define	dmMaxRecordIndex			0xffff

#define	dmErrorClass				0x0200	// Data Manager
#define dmErrAlreadyExists			(dmErrorClass | 25)

typedef void*		VoidPtr;
typedef VoidPtr*	MemHandle;	// global handle

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

// system handle structure
typedef struct SYSHandle {
	void		*handle[256];
	UInt16	count;
	Boolean	locked[256];
} SYSHandle;



//  Pdb constant definition

#define  dBName        "PMail"           
#define  creatorID     'CATS'           /* Define the information of the database */
#define  dBType        'DATA'
#define  nullChr			0x00  
#define  crChr				0x0D
#define  linefeedChr		0x0A
#define  nullChrSize       1 
#define  DatabaseBound  (UInt32)(60*1024)
     
DmOpenRef OpenPdb() ;
void  SaveMailToDb(DmOpenRef  dbP,CString  fromP,CString  subjP,CString  bodyP,Word  index);
void  ReplaceCrChrToLfChr(CString  *SrcP);
UInt16  DataBaseSize(DmOpenRef  dbP,CString fromP,CString subjP, CString bodyP);


						//  function  prototype  declaration
Err DmCreateDatabase (UInt16 cardNo, const Char *nameP, UInt32 creator, UInt32 type, Boolean resDB);
DmOpenRef DmOpenDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode);
Int16 VReleaseRecord ();
UInt16 VGetRecordOffset (DmOpenRef dbP, UInt16 index, UInt16 totalRecords);
Int16 VWriteRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset, const void *srcP, UInt32 RecordSize);
UInt16 VMoveToLastRecord (DmOpenRef dbP, UInt16 index, UInt16 offset1, UInt16 RecordSize, UInt16 totalRecords);
void *VResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 size);
void *VLoadDatabaseFile (char *filename, UInt32 type, UInt32 creator, Boolean CreateFlag);
Int16 VReleaseRecord ();
Boolean WNewHandle ();
MemPtr MemHandleLock (MemHandle h);
Err MemHandleUnlock (MemHandle h);
Err DmSet (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value);
Err DmWrite (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes);
Err DmReleaseRecord (DmOpenRef dbP, UInt16 index, Boolean dirty);
UInt16 VGetRecordSize (DmOpenRef dbP, UInt16 offset1, UInt16 totalRecords);
void *VLoadDatabaseFile (char *filename, UInt32 type, UInt32 creator, Boolean CreateFlag);
MemHandle DmResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 newSize);
MemHandle DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
void *VNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
void VInsertData (DmOpenRef dbP, UInt16 offset, char *data, UInt16 size);







