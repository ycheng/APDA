ifndef __MEMOTYPES_H__
#define __MEMOTYPES_H__

#define LocalizedAppInfoStr	1000

// MemoDBRecord.
//
// All strings are null terminated and appear within the record.
//
typedef struct {
	ULong	ID;
	UInt	length;
	char	*text;
} MemoDBRecord;

typedef MemoDBRecord			MemoDBRecordType;
typedef MemoDBRecord*		MemoDBRecordPtr;

// ToDoItemType
//
// This is the format of a to do record used by the application.  All 
// pointers are either NULL or point to data within the PackedDB record.
// All strings are null character terminated.
//
typedef struct {
	DateType 			dueDate;
	Byte 				priority;		// high bit is complete flag
	Byte				reserved;
	Char *				description;
	Char *				note;
} ToDoItemType;

typedef ToDoItemType * ToDoItemPtr;

#endif	// __MEMOTYPES_H__
