#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


/************************************************************
 * Memory Manager Debug settings for the MemSetDebugMode function
 *************************************************************/
#define		memDebugModeCheckOnChange			0x0001
#define		memDebugModeCheckOnAll				0x0002
#define		memDebugModeScrambleOnChange		0x0004
#define		memDebugModeScrambleOnAll			0x0008
#define		memDebugModeFillFree					0x0010
#define		memDebugModeAllHeaps					0x0020
#define		memDebugModeRecordMinDynHeapFree	0x0040

#define		SYSNumCards			1

#define		CARDNAMESIZE		32
#define		MANUNAMESIZE		32


UInt16	debugMode = memDebugModeCheckOnChange;
UInt16	curOwner=0;
UInt16	SysNumHeaps[SYSNumCards];
UInt16	SysNumRAMHeaps[SYSNumCards];
extern	UInt16	curCardNo;
Char		curCardName[CARDNAMESIZE];
Char		curManuName[MANUNAMESIZE];

typedef struct {
	UInt32 romSize;
	UInt32 ramSize;
	UInt32 usedRomSize;
	UInt32 usedRamSize;
} SysMemory;

SysMemory	sysMemory;

SYSHandle	sysHandle;

Boolean WNewHandle ();

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemCardInfo
//
// DESCRIPTION: This routine return information about a memory card.
//
// PARAMETERS:  (UIn16) cardNo - Card number.
//					 (Char *) cardNameP - Pointer to character array
//											(32 bytes), or 0.
//					 (Char *) manufNameP - Pointer to character array
//											(32 bytes), or 0.
//					 (UInt16 *) versionP - Pointer to version variable, or 0
//					 (UInt32 *) crDateP - Pointer to creation date variable,
//											or 0.
//					 (UInt32) romSizeP - Pointer to ROM size variable, or 0
//					 (UInt32) ramSizeP - Pointer to RAM size variable, or 0
//					 (UInt32) freeBytesP - Pointer to free byte-count variable,
//											or 0.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemCardInfo (UInt16 cardNo, Char *cardNameP, Char *manufNameP,
					  UInt16 *versionP, UInt32 *crDateP, UInt32 *romSizeP,
					  UInt32 *ramSizeP, UInt32 *freeBytesP)
{
	cardNo = curCardNo;
	Vmemcpy ( cardNameP, curCardName, CARDNAMESIZE );
	Vmemcpy ( manufNameP, curManuName, MANUNAMESIZE );
	*romSizeP = sysMemory.romSize;
	*ramSizeP = sysMemory.ramSize;
	*freeBytesP = (sysMemory.ramSize+sysMemory.romSize) -
				(sysMemory.usedRamSize+sysMemory.usedRomSize);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemCmp
//
// DESCRIPTION: This routine compare two blocks of memory
//
// PARAMETERS:  (const void *) s1, s2 - Pointers to block of memory
//					 (Int32) numBytes - Number of bytes to compare
//
// RETURNED:    Zero if they match, non-zeo if not:
//					 + if s1 > s2
//					 - if s1 < s2
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 MemCmp(const void *str1, const void *str2, Int32 numBytes)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemDebugMode
//
// DESCRIPTION: This routine return the current debugging mode of the
//					 memory manager.
//
// PARAMETERS:  
//
// RETURNED:    Returns debug flags.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 MemDebugMode (void)
{
	return	debugMode;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleCardNo
//
// DESCRIPTION: This routine return the card number a chunk resides on
//
// PARAMETERS:  (MemHandle) h - Chunk handle.
//
// RETURNED:    Returns the card number.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description0 
//			----	----		-----------
//			Jerry	5/06/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 MemHandleCardNo (MemHandle h)
{
	return	curCardNo;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleFree
//
// DESCRIPTION: This routine dispose of a movable chunk
//
// PARAMETERS:  (MemHandle) h - Chunk handle.
//
// RETURNED:    Returns 0 if no error, or error code if and error occurs
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/7/01	Initial Revision
//			Jerry	10/09/01	Modify to use sysHandle structure
////////////////////////////////////////////////////////////////////////
Err MemHandleFree (MemHandle h)
{
	if ( *h ) 
		Vfree (*h);

	return	0;
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
	if ( h && (h >= sysHandle.handle) && (h < (sysHandle.handle+NUMSYSHANDLE)) )
		if ( !sysHandle.locked[(h-sysHandle.handle)] ) {
			sysHandle.locked[(h-sysHandle.handle)] = true;

			if ( sysHandle.size[(h-sysHandle.handle)] )
				return	sysHandle.handle[(h-sysHandle.handle)];
			else
				return	NULL;
		}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleNew
//
// DESCRIPTION: This routine allocate a new movable chunk in the 
//				dynamic heap and return a handle to it.
//
// PARAMETERS:  (UInt32) size - The desired size of the chunk
//
// RETURNED:    Return pointer to the new chunk, or 0 if unsuccessful
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
//			Jerry	9/19/01	Modify return void * to void **
//			Jerry	10/09/01	Modify to use sysHandle structure
////////////////////////////////////////////////////////////////////////
MemHandle MemHandleNew(UInt32 size)
{
	if ( WNewHandle () ) {
		sysHandle.size[sysHandle.count] = size;
		sysHandle.handle[sysHandle.count] = Vmalloc (size);
		sysHandle.count++;

		return	&(sysHandle.handle[sysHandle.count-1]);
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleResize
//
// DESCRIPTION: This routine resize a chunk
//
// PARAMETERS:  (MemHandle) h - Chunk Handle.
//					 (UInt32) newSize - The new desired size.
//
// RETURNED:    Returns 0 if no error, otherwise returns error code
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemHandleResize (MemHandle h, UInt32 newSize)
{
	if ( (h >= sysHandle.handle) && (h < (sysHandle.handle+NUMSYSHANDLE)) ) {
		sysHandle.handle[(h-sysHandle.handle)] = 
					Vrealloc (sysHandle.handle[(h-sysHandle.handle)], newSize);

		sysHandle.size[(h-sysHandle.handle)] = newSize;
		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleSetOwner
//
// DESCRIPTION: This routine set the owner ID of a chunk
//
// PARAMETERS:  (MemHandle) h - Chunk Handle.
//					 (UInt16) owner - New owner ID of the chunk. specify 0
//									to set the owner to the operating system.
//
// RETURNED:    Returns 0 if no error, or memErrInvalidParam if an
//					 error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemHandleSetOwner (MemHandle h, UInt16 owner)
{
	curOwner = owner;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleSize
//
// DESCRIPTION: This routine return the requested size of a chunk
//
// PARAMETERS:  (MemHandle) h - Chunk Handle.
//
// RETURNED:    Returns the requested size of a chunk
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 MemHandleSize (MemHandle h)
{
	if ( (h >= sysHandle.handle) && (h < (sysHandle.handle+NUMSYSHANDLE)) ) {
		return	sysHandle.size[(h-sysHandle.handle)];
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemHandleToLocalID
//
// DESCRIPTION: This routine convert a handle into a local chunk ID
//					 which is card relative.
//
// PARAMETERS:  (MemHandle) h - Chunk handle.
//
// RETURNED:    Returns local ID, or NULL if unsuccessful.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
LocalID MemHandleToLocalID (MemHandle h)
{
	if ( (h >= sysHandle.handle) && (h < (sysHandle.handle+NUMSYSHANDLE)) )
		return	(h-sysHandle.handle);

	return	0;
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

	if ( (h >= sysHandle.handle) && (h < (sysHandle.handle+NUMSYSHANDLE)) ) {
		index = h-sysHandle.handle;
		if ( sysHandle.locked[index] ) {
			sysHandle.locked[index] = FALSE;

			return	0;
		}
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemLocalIDToLockedPtr
//
// DESCRIPTION: This routine return a pointer to a chunk given its local
//					 ID and card number. 
//
// PARAMETERS:  (localID) local - Local chunk ID.
//					 (UInt16) cardNo - Card number.
//
// RETURNED:    Returns pointer to chunk, or 0 if an error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
MemPtr MemLocalIDToLockedPtr (LocalID local, UInt16 cardNo)
{
	if ( !sysHandle.locked[local] ) {
		sysHandle.locked[local] = true;

		return	sysHandle.handle[local];
	} else {
		return	NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemMove
//
// DESCRIPTION: This routine move a range of memory to another range in
//					 the dynamic heap.
//
// PARAMETERS:  (void *) dstP - Pointer to the destination.
//					 (void *) srcP - Pointer to source.
//					 (Int32) numBytes - Number of bytes to move.
//
// RETURNED:    Always returns 0
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemMove (VoidPtr dstP, VoidPtr srcP, Int32 numBytes)
{
	if ( srcP && dstP )
		Vmemmove (dstP, srcP, numBytes);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemNumCards
//
// DESCRIPTION: This routine return the number of memory card slots in
//					 the system.
//
// PARAMETERS:  None.
//
// RETURNED:    Return number of slots in the system
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 MemNumCards (void)
{
	return	SYSNumCards;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemNumHeaps
//
// DESCRIPTION: This routine the number of heaps available on a 
//					 particular card.
//
// PARAMETERS:  (UInt16) cardNo - The card number; either 0 or 1.
//
// RETURNED:    Return number of heaps available, including ROM- and 
//					 RAM-based heaps.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 MemNumHeaps (UInt16 cardNo)
{
	return	SysNumHeaps[cardNo]+SysNumRAMHeaps[cardNo];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemNumRAMHeaps
//
// DESCRIPTION: This routine return the number of RAM heaps in the given
//					 card.
//
// PARAMETERS:  (UInt16) cardNo - The card number; either 0 or 1.
//
// RETURNED:    Return number of heaps available, including ROM- and 
//					 RAM-based heaps.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 MemNumRAMHeaps (UInt16 cardNo)
{
	return	SysNumRAMHeaps[cardNo];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemPtrFree
//
// DESCRIPTION: This routine macro to dispose a chunk
//
// PARAMETERS:  (MemPtr) p - Pointer to a chunk
//
// RETURNED:    Return 0 if no error or error code if error occurs
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/9/01	Initial Revision
//			Jerry	11/16/01	Modify to free sysHandle and reorginize sysHandle
////////////////////////////////////////////////////////////////////////
Err MemPtrFree(MemPtr p)
{
	int	i;

	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( (sysHandle.handle[i]) && (p == sysHandle.handle[i]) ) {
			if ( !sysHandle.locked[i] ) {
				Vfree(sysHandle.handle[i]);

				if ( i < (sysHandle.count-1) ) {
					sysHandle.handle[i] = sysHandle.handle[sysHandle.count-1];
					sysHandle.locked[i] = sysHandle.locked[sysHandle.count-1];
					sysHandle.size[i] = sysHandle.size[sysHandle.count-1];
					i = sysHandle.count-1;
				}

				sysHandle.handle[i] = NULL;
				sysHandle.locked[i] = FALSE;
				sysHandle.size[i] = 0;
				sysHandle.count--;

				return	0;
			}
		}
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemPtrNew
//
// DESCRIPTION: This routine allocate a new nonmovable chunk in the 
//				dynamic heap.
//
// PARAMETERS:  (Int32) size - The desired size of the chunk
//
// RETURNED:    Return pointer to the new chunk, or 0 if unsuccessful
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/9/01		Initial Revision
////////////////////////////////////////////////////////////////////////
MemPtr MemPtrNew(UInt32 size)
{
	if ( WNewHandle () ) {
		sysHandle.size[sysHandle.count] = size;
		sysHandle.handle[sysHandle.count] = Vmalloc (size);
		sysHandle.count++;

		return	(MemPtr)(sysHandle.handle[sysHandle.count-1]);
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemPtrResize
//
// DESCRIPTION: This routine resize a chunk
//
// PARAMETERS:  (MemPtr) p - Pointer to  the Chunk.
//					 (UInt32) newSize - The new desired size.
//
// RETURNED:    Returns 0 if no error, otherwise returns error code
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemPtrResize (MemPtr p, UInt32 newSize)
{
	int	i;

	if ( (sysHandle.handle[NUMSYSHANDLE-1]) && (p == sysHandle.handle[NUMSYSHANDLE-1]) ) {
		sysHandle.handle[NUMSYSHANDLE-1] = 
					Vrealloc (sysHandle.handle[NUMSYSHANDLE-1], newSize);

		sysHandle.size[NUMSYSHANDLE-1] = newSize;

		return	0;
	}

	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( (sysHandle.handle[i]) && (p == sysHandle.handle[i]) ) {
			sysHandle.handle[i] = 
						Vrealloc (sysHandle.handle[i], newSize);
			sysHandle.size[i] = newSize;

			return	0;
		}
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemPtrSize
//
// DESCRIPTION: This routine return the size of a chunk
//
// PARAMETERS:  (MemPtr) p - Pointer to the chunk.
//
// RETURNED:    Returns the requested size of a chunk
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 MemPtrSize (MemPtr p)
{
	int	i;

	if ( (sysHandle.handle[NUMSYSHANDLE-1]) && (p == sysHandle.handle[NUMSYSHANDLE-1]) )
		return	sysHandle.size[NUMSYSHANDLE-1];

	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( (sysHandle.handle[i]) && (p == sysHandle.handle[i]) ) {
			return	sysHandle.size[i];
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemPtrUnlock
//
// DESCRIPTION: This routine unlock a chunk, given a pointer to the 
//					 chunk
//
// PARAMETERS:  (MemPtr) p - Pointer to the chunk.
//
// RETURNED:    Returns 0 if no error, or memErrInvalidParam if an
//					 error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemPtrUnlock (MemPtr p)
{
	int	i;

	if ( (sysHandle.handle[NUMSYSHANDLE-1]) && (p == sysHandle.handle[NUMSYSHANDLE-1]) ) {
		sysHandle.locked[NUMSYSHANDLE-1] = false;
		return	0;
	}

	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( (sysHandle.handle[i]) && (p == sysHandle.handle[i]) ) {
			sysHandle.locked[i] = false;

			return	0;
		}
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemSet
//
// DESCRIPTION: This routine set a memory range in a dynamic heap to 
//				a specific value
//
// PARAMETERS:  (void *) dstP - Pointer to the destination.
//				(Int32) numBytes - Number of bytes to set
//				(UInt8) value - Value to set
//
// RETURNED:    Always returns 0
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemSet(void *dstP, UInt32 numBytes, UInt8 value)
{
	Vmemset(dstP, value, numBytes);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MemSetDebugMode
//
// DESCRIPTION: This routine set the debugging mode of the memory
//					 manager.
//
// PARAMETERS:  (UInt16) flags - Debug flags.
//
// RETURNED:    Returns 0 if no error, or -1 if and error occurs.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err MemSetDebugMode (UInt16 flags)
{
#define		memDebugModeCheckOnChange			0x0001
#define		memDebugModeCheckOnAll				0x0002
#define		memDebugModeScrambleOnChange		0x0004
#define		memDebugModeScrambleOnAll			0x0008
#define		memDebugModeFillFree					0x0010
#define		memDebugModeAllHeaps					0x0020
#define		memDebugModeRecordMinDynHeapFree	0x0040
	if ( (flags == memDebugModeCheckOnChange) ||
			(flags == memDebugModeCheckOnAll) ||
			(flags == memDebugModeScrambleOnChange) ||
			(flags == memDebugModeScrambleOnAll) ||
			(flags == memDebugModeFillFree) ||
			(flags == memDebugModeAllHeaps) ||
			(flags == memDebugModeRecordMinDynHeapFree) ) {
		debugMode = flags;

		return	0;
	} 

	return	-1;
}

Boolean WNewHandle ()
{
	if ( sysHandle.count < NUMSYSHANDLE-1 ) {
		sysHandle.locked[sysHandle.count] = 0;

		return	TRUE;
	}

	return	FALSE;
}
