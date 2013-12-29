/*========================================================
  File.c
  all routine is running with Platform non-related,
  simulated the File function in Palm OS.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0507, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#define fileOriginBeginning	0               /* seek to an absolute position */
#define fileOriginCurrent		1               /* seek relative to current position */
#define fileOriginEnd			2               /* seek relative to end of file */


////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileClose
//
// DESCRIPTION: This routine close the file stream and destory its handle.
//					 If the stream was opened with fileModeTemporary, it is 
//					 deleted upon closing
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//
// RETURNED:    Returns 0 if no error, or a fileErr.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FileClose (FileHand stream)
{
	return	Vfclose (stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileDelete
//
// DESCRIPTION: This routine deletes the specified file stream from the 
//					 specified card. Only a closed stream may be passed this
//					 function.
//
// PARAMETERS:  (UInt16) cardNo - Card on which the file stream to open
//									resides.
//					 (Char *) nameP - String that is the name of the stream
//									to delete.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FileDelete (UInt16 cardNo, Char *nameP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileEOF
//
// DESCRIPTION: This routine get end-of-file status.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//
// RETURNED:    Returns 0 if not end of file; non-zero if end of file.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FileEOF (FileHand stream)
{
	return	Vfeof (stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileFlush
//
// DESCRIPTION: This routine flush cached data to storage.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FileFlush (FileHand stream)
{
	return	Vfflush (stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileOpen
//
// DESCRIPTION: This routine open existing file stream or create an open
//					 file stream for I/O in the mode specified by the openMode
//					 parameter
//
// PARAMETERS:  (UInt16) cardNo - Card on which the file stream to open
//									resides.
//					 (Char *) nameP - Pointer to text string that is the name
//									of the file stream to open or create.
//					 (UInt32) type - File type of stream to open or create.
//					 (UInt32) creator - Creator of stream to open or create.
//					 (UInt32) openMode - Mode in which to open the file stream.
//					 (Err *) errP - Pointer to variable that is to hold the error
//									code returned by this function.
//
// RETURNED:    Returns a handle to an open file stream if successful,
//					 otherwise returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FileHand FileOpen (UInt16 cardNo, Char *nameP, UInt32 type,
								  UInt32 creator, UInt32 openMode, Err *errP)
{
	return VFileOpen ( nameP, type, creator, openMode );
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileRead
//
// DESCRIPTION: This routine reads data from a stream into a buffer. Do
//					 not use this function to read data into a chunk, record
//					 or resource residing in a datebase.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//					 (void *) bufP - Pointer to beginning of buffer into which
//										data is read.
//					 (Int32) objSize - Size of each stream object to read.
//					 (Int32) numObj - Number of stream objects to read.
//					 (Err *) errP - Pointer to variable that is to hold the
//										error code returned by this function. Pass
//										NULL to ignore.
//
// RETURNED:    Returns the number of while objects that were read - note
//					 that the number of objects actually read may be less than
//					 the number requested.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 FileRead (FileHand stream, void *bufP, Int32 objSize, Int32 numObj, Err *errP)
{
	return	Vfread (bufP, objSize, numObj, stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileRewind
//
// DESCRIPTION: This routine reset position marker to beginning of stream
//					 and clear all erorr codes.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FileRewind (FileHand stream)
{
	return	Vfseek (stream, 0, fileOriginBeginning);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileSeek
//
// DESCRIPTION: This routine set current position within a file stream,
//					 extending the stream as neccessary if it was opened with
//					 write access.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//					 (Int32) offset - Position to set, expressed as the number
//									of bytes from origin.
//					 (FileOriginEnum) origin - Describes the origin of the
//									position change. Possible values are:
//									fileOriginBeginning, fileOriginCurrent,
//									fileOriginEnd.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
//Err FileSeek (FileHand stream, Int32 offset, FileOriginEnum origin)
Err FileSeek (FileHand stream, Int32 offset, UInt16 origin)
{
	return	Vfseek (stream, offset, origin);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileTell
//
// DESCRIPTION: This routine get current position and, optionally, file size
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//					 (Int32 *) fileSizeP - Pointer to variable that holds value
//										describing size of stream in bytes when this
//										function returns. Pass NULL to ignore.
//					 (Err *) errP - Pointer to variable that is to hold the
//										error code returned by this function
//
// RETURNED:    Returns current position.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 FileTell (FileHand stream, Int32 *fileSizeP, Err *errP)
{
	Int32	offset;

	offset = (Int32) Vftell (stream);
	if ( fileSizeP ) {
		Vfseek (stream, 0, fileOriginEnd);
		*fileSizeP = (Int32) Vftell (stream);
		Vfseek (stream, offset, fileOriginBeginning);
	}

	return	offset;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FileWrite
//
// DESCRIPTION: This routine write data to a stream.
//
// PARAMETERS:  (FileHand) stream - Handle to open stream
//					 (void *) bufP - Pointer to beginning of buffer into which
//										data is write.
//					 (Int32) objSize - Size of each stream object to write.
//					 (Int32) numObj - Number of stream objects to write.
//					 (Err *) errP - Pointer to variable that is to hold the
//										error code returned by this function. Pass
//										NULL to ignore.
//
// RETURNED:    Returns the number of while objects that were written - note
//					 that the number of objects actually read may be less than
//					 the number requested.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 FileWrite (FileHand stream, void *bufP, Int32 objSize, Int32 numObj, Err *errP)
{
	return	Vfwrite (bufP, objSize, numObj, stream);
}
