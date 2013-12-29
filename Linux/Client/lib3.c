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
// Field Processing Library, completed 52/52 functions now.
////////////////////////////////////////////////////////////
#ifdef L_FldCalcFieldHeight
UInt16 FldCalcFieldHeight (const Char* chars, UInt16 maxWidth)
{
	UInt16 (*FldCalcFieldHeightP) (const Char* chars, UInt16 maxWidth);
	
	GetParameter (&FldCalcFieldHeightP, sizeof(void *), pFldCalcFieldHeight);
	return (*FldCalcFieldHeightP) ( chars,  maxWidth);
}
#endif

#ifdef L_FldCompactText
void FldCompactText (FieldType *fldP)
{
	void (*FldCompactTextP) (FieldType *fldP);
	
	GetParameter (&FldCompactTextP, sizeof(void *), pFldCompactText);
	(*FldCompactTextP) (fldP);
}
#endif

#ifdef L_FldCopy
void FldCopy (const FieldType *fldP)
{
	void (*FldCopyP) (const FieldType *fldP);
	
	GetParameter (&FldCopyP, sizeof(void *), pFldCopy);
	(*FldCopyP) (fldP);
}
#endif

#ifdef L_FldCut
void FldCut (FieldType *fldP)
{
	void (*FldCutP) (FieldType *fldP);
	
	GetParameter (&FldCutP, sizeof(void *), pFldCut);
	(*FldCutP) (fldP);
}
#endif

#ifdef L_FldDelete
void FldDelete (FieldType *fldP, UInt16 start, UInt16 end)
{
	void (*FldDeleteP) (FieldType *fldP, UInt16 start, UInt16 end);

	GetParameter (&FldDeleteP, sizeof(void *), pFldDelete);
	(*FldDeleteP) (fldP,  start,  end);
}
#endif

#ifdef L_FldDirty
Boolean FldDirty (FieldType *fldP)
{
	Boolean (*FldDirtyP) (FieldType *fldP);

	GetParameter (&FldDirtyP, sizeof(void *), pFldDirty);
	return (*FldDirtyP) (fldP);
}
#endif

#ifdef L_FldDrawField
void FldDrawField (FieldType *fldP)
{
	void (*FldDrawFieldP) (FieldType *fldP);

	GetParameter (&FldDrawFieldP, sizeof(void *), pFldDrawField);
	(*FldDrawFieldP) (fldP);
}
#endif

#ifdef L_FldEraseField
void FldEraseField (FieldType *fldP)
{
	void (*FldEraseFieldP) (FieldType *fldP);

	GetParameter (&FldEraseFieldP, sizeof(void *), pFldEraseField);
	(*FldEraseFieldP) (fldP);
}
#endif

#ifdef L_FldFreeMemory
void FldFreeMemory (FieldType *fldP)
{
	void (*FldFreeMemoryP) (FieldType *fldP);

	GetParameter (&FldFreeMemoryP, sizeof(void *), pFldFreeMemory);
	(*FldFreeMemoryP) (fldP);
}
#endif

#ifdef L_FldGetAttributes
void FldGetAttributes (const FieldType *fldP, FieldAttrPtr attrP)
{
	void (*FldGetAttributesP) (const FieldType *fldP, FieldAttrPtr attrP);

	GetParameter (&FldGetAttributesP, sizeof(void *), pFldGetAttributes);
   (*FldGetAttributesP) (fldP,  attrP);
}
#endif

#ifdef L_FldGetBounds
void FldGetBounds (const FieldType *fldP, RectangleType *rect)
{
	void (*FldGetBoundsP) (const FieldType *fldP, RectangleType *rect);

	GetParameter (&FldGetBoundsP, sizeof(void *), pFldGetBounds);
	(*FldGetBoundsP) (fldP, rect);
}
#endif

#ifdef L_FldGetFont
FontID FldGetFont (const FieldType *fldP)
{
	FontID (*FldGetFontP) (const FieldType *fldP);

	GetParameter (&FldGetFontP, sizeof(void *), pFldGetFont);
	return (*FldGetFontP) (fldP);
}
#endif

#ifdef L_FldGetInsPtPosition
UInt16 FldGetInsPtPosition (const FieldType *fldP)
{
	UInt16 (*FldGetInsPtPositionP) (const FieldType *fldP);

	GetParameter (&FldGetInsPtPositionP, sizeof(void *), pFldGetInsPtPosition);
	return (*FldGetInsPtPositionP) (fldP);
}
#endif

#ifdef L_FldGetMaxChars
UInt16 FldGetMaxChars (const FieldType *fldP)
{
	UInt16 (*FldGetMaxCharsP) (const FieldType *fldP);

	GetParameter (&FldGetMaxCharsP, sizeof(void *), pFldGetMaxChars);
	return (*FldGetMaxCharsP) (fldP);
}
#endif

#ifdef L_FldGetNumberOfBlankLines
UInt16 FldGetNumberOfBlankLines (const FieldType *fldP)
{
	UInt16 (*FldGetNumberOfBlankLinesP) (const FieldType *fldP);

	GetParameter (&FldGetNumberOfBlankLinesP, sizeof(void *), pFldGetNumberOfBlankLines);
	return (*FldGetNumberOfBlankLinesP) (fldP);
}
#endif

#ifdef L_FldGetScrollPosition
UInt16 FldGetScrollPosition (const FieldType *fldP)
{
	UInt16 (*FldGetScrollPositionP) (const FieldType *fldP);

	GetParameter (&FldGetScrollPositionP, sizeof(void *), pFldGetScrollPosition);
	return (*FldGetScrollPositionP) (fldP);
}
#endif

#ifdef L_FldGetScrollValues
void FldGetScrollValues (const FieldType *fldP, UInt16 *scrollPosP,
								UInt16 *textHeightP, UInt16 *fieldHeghtP)
{
	void (*FldGetScrollValuesP) (const FieldType *fldP, UInt16 *scrollPosP,
								UInt16 *textHeightP, UInt16 *fieldHeghtP);

	GetParameter (&FldGetScrollValuesP, sizeof(void *), pFldGetScrollValues);
        (*FldGetScrollValuesP) (fldP, scrollPosP,textHeightP, fieldHeghtP);
}
#endif

#ifdef L_FldGetSelection
void FldGetSelection (const FieldType *fldP, UInt16 *startPosition,
								UInt16 *endPosition)
{
	void (*FldGetSelectionP) (const FieldType *fldP, UInt16 *startPosition,UInt16 *endPosition);

	GetParameter (&FldGetSelectionP, sizeof(void *), pFldGetSelection);
	(*FldGetSelectionP) ( fldP, startPosition,endPosition);
}
#endif

#ifdef L_FldGetTextAllocatedSize
UInt16 FldGetTextAllocatedSize (const FieldType *fldP)
{
	UInt16 (*FldGetTextAllocatedSizeP) (const FieldType *fldP);

	GetParameter (&FldGetTextAllocatedSizeP, sizeof(void *), pFldGetTextAllocatedSize);
	return (*FldGetTextAllocatedSizeP) ( fldP);
}
#endif

#ifdef L_FldGetTextHandle
MemHandle FldGetTextHandle (const FieldType *fldP)
{
	MemHandle(*FldGetTextHandleP)  (const FieldType *fldP);

	GetParameter (&FldGetTextHandleP, sizeof(void *), pFldGetTextHandle);
	return(*FldGetTextHandleP)  (fldP);
}
#endif

#ifdef L_FldGetTextHeight
UInt16 FldGetTextHeight (const FieldType *fldP)
{
	UInt16(*FldGetTextHeightP)  (const FieldType *fldP);

	GetParameter (&FldGetTextHeightP, sizeof(void *), pFldGetTextHeight);
	return(*FldGetTextHeightP)  (fldP);
}
#endif

#ifdef L_FldGetTextLength
UInt16 FldGetTextLength (const FieldType *fldP)
{
	UInt16 (*FldGetTextLengthP) (const FieldType *fldP);

	GetParameter (&FldGetTextLengthP, sizeof(void *), pFldGetTextLength);
	return (*FldGetTextLengthP) (fldP);
}
#endif

#ifdef L_FldGetTextPtr
Char *FldGetTextPtr (FieldType *fldP)
{
	Char *(*FldGetTextPtrP) (FieldType *fldP);

	GetParameter (&FldGetTextPtrP, sizeof(void *), pFldGetTextPtr);
	return(*FldGetTextPtrP) (fldP);
}
#endif

#ifdef L_FldGetVisibleLines
UInt16 FldGetVisibleLines (const FieldType *fldP)
{
	UInt16 (*FldGetVisibleLinesP) (const FieldType *fldP);

	GetParameter (&FldGetVisibleLinesP, sizeof(void *), pFldGetVisibleLines);
	return (*FldGetVisibleLinesP) (fldP);
}
#endif

#ifdef L_FldGrabFocus
void FldGrabFocus (FieldType *fldP)
{
	void (*FldGrabFocusP) (FieldType *fldP);

	GetParameter (&FldGrabFocusP, sizeof(void *), pFldGrabFocus);
	(*FldGrabFocusP) (fldP);
}
#endif

#ifdef L_FldHandleEvent
Boolean FldHandleEvent (const FieldType *fldP, EventType *eventP)
{
	Boolean (*FldHandleEventP) (const FieldType *fldP, EventType *eventP);

	GetParameter (&FldHandleEventP, sizeof(void *), pFldHandleEvent);
	return (*FldHandleEventP) (fldP, eventP);
}
#endif

#ifdef L_FldInsert
Boolean FldInsert (FieldType *fldP, const Char* insertChars, UInt16 insertLen)
{
	Boolean (*FldInsertP) (FieldType *fldP, const Char* insertChars, UInt16 insertLen);

	GetParameter (&FldInsertP, sizeof(void *), pFldInsert);
	return (*FldInsertP) (fldP,  insertChars,  insertLen);
}
#endif

#ifdef L_FldMakeFullyVisible
Boolean FldMakeFullyVisible (FieldType *fldP)
{
	Boolean(*FldMakeFullyVisibleP)  (FieldType *fldP);

	GetParameter (&FldMakeFullyVisibleP, sizeof(void *), pFldMakeFullyVisible);
	return(*FldMakeFullyVisibleP)  (fldP);
}
#endif

#ifdef L_fldNewField
FieldType *fldNewField (void **formPP, UInt16 id, Coord x, Coord y, Coord width,
						Coord heght, FontID font, UInt32 maxChars, Boolean editable,
						Boolean underlined, Boolean singleLine, Boolean dynamicSize,
						JustificationType justification, Boolean autoShift,
						Boolean hasScrollBar, Boolean numeric)
{
FieldType *(*fldNewFieldP) (void **formPP, UInt16 id, Coord x, Coord y, Coord width,
						Coord heght, FontID font, UInt32 maxChars, Boolean editable,
						Boolean underlined, Boolean singleLine, Boolean dynamicSize,
						JustificationType justification, Boolean autoShift,
						Boolean hasScrollBar, Boolean numeric);

	GetParameter (&fldNewFieldP, sizeof(void *), pfldNewField);
        return (*fldNewFieldP) (formPP,  id,  x,  y,  width,
						 heght,  font,  maxChars,  editable,
						 underlined,  singleLine,  dynamicSize,
						 justification,  autoShift,
						 hasScrollBar,  numeric);
}
#endif

#ifdef L_FldPaste
void FldPaste (FieldType *fldP)
{
	void (*FldPasteP) (FieldType *fldP);

	GetParameter (&FldPasteP, sizeof(void *), pFldPaste);
	(*FldPasteP) (fldP);
}
#endif

#ifdef L_FldRecalculateField
void FldRecalculateField (FieldType *fldP, Boolean redraw)
{
	void (*FldRecalculateFieldP) (FieldType *fldP, Boolean redraw);

	GetParameter (&FldRecalculateFieldP, sizeof(void *), pFldRecalculateField);
	(*FldRecalculateFieldP) (fldP,  redraw);
}
#endif

#ifdef L_FldReleaseFocus
void FldReleaseFocus (FieldType *fldP)
{
	void (*FldReleaseFocusP) (FieldType *fldP);

	GetParameter (&FldReleaseFocusP, sizeof(void *), pFldReleaseFocus);
	(*FldReleaseFocusP) (fldP);
}
#endif

#ifdef L_FldScrollable
Boolean FldScrollable (const FieldType *fldP, WinDirectionType direction) 
{
	Boolean (*FldScrollableP) (const FieldType *fldP, WinDirectionType direction) ;

	GetParameter (&FldScrollableP, sizeof(void *), pFldScrollable);
	return (*FldScrollableP) (fldP,  direction) ;
}
#endif

#ifdef L_FldScrollField
void FldScrollField (FieldType *fldP, UInt16 linesToScroll, WinDirectionType direction)
{
	void (*FldScrollFieldP) (FieldType *fldP, UInt16 linesToScroll, WinDirectionType direction);

	GetParameter (&FldScrollFieldP, sizeof(void *), pFldScrollField);
	(*FldScrollFieldP) (fldP,  linesToScroll,  direction);
}
#endif

#ifdef L_FldSendChangeNotification
void FldSendChangeNotification (const FieldType *fldP)
{
	void (*FldSendChangeNotificationP) (const FieldType *fldP);

	GetParameter (&FldSendChangeNotificationP, sizeof(void *), pFldSendChangeNotification);
	(*FldSendChangeNotificationP) (fldP);
}
#endif

#ifdef L_FldSendHeightChangeNotification
void FldSendHeightChangeNotification (const FieldType *fldP, UInt16 pos, Int16 numLines)
{
	void (*FldSendHeightChangeNotificationP) (const FieldType *fldP, UInt16 pos, Int16 numLines);

	GetParameter (&FldSendHeightChangeNotificationP, sizeof(void *), pFldSendHeightChangeNotification);
	(*FldSendHeightChangeNotificationP) (fldP,  pos,  numLines);
}
#endif

#ifdef L_FldSetAttributes
void FldSetAttributes (FieldType *fldP, const FieldAttrType *attrP)
{
	void (*FldSetAttributesP) (FieldType *fldP, const FieldAttrType *attrP);

	GetParameter (&FldSetAttributesP, sizeof(void *), pFldSetAttributes);
	(*FldSetAttributesP) (fldP, attrP);
}
#endif

#ifdef L_FldSetBounds
void FldSetBounds (FieldType *fldP, const RectangleType *rP)
{
	void(*FldSetBoundsP)  (FieldType *fldP, const RectangleType *rP);

	GetParameter (&FldSetBoundsP, sizeof(void *), pFldSetBounds);
	(*FldSetBoundsP)  ( fldP,  rP);
}
#endif

#ifdef L_FldSetDirty
void FldSetDirty (FieldType *fldP, Boolean dirty)
{
	void (*FldSetDirtyP) (FieldType *fldP, Boolean dirty);

	GetParameter (&FldSetDirtyP, sizeof(void *), pFldSetDirty);
	(*FldSetDirtyP) (fldP,  dirty);
}
#endif

#ifdef L_FldSetFont
void FldSetFont (FieldType *fldP, FontID fontID)
{
	void (*FldSetFontP) (FieldType *fldP, FontID fontID);

	GetParameter (&FldSetFontP, sizeof(void *), pFldSetFont);
	(*FldSetFontP) (fldP,  fontID);
}
#endif

#ifdef L_FldSetInsertionPoint
void FldSetInsertionPoint (FieldType *fldP, UInt16 pos)
{
	void(*FldSetInsertionPointP)  (FieldType *fldP, UInt16 pos);

	GetParameter (&FldSetInsertionPointP, sizeof(void *), pFldSetInsertionPoint);
	(*FldSetInsertionPointP)  (fldP,  pos);
}
#endif

#ifdef L_FldSetInsPtPosition
void FldSetInsPtPosition (FieldType *fldP, UInt16 pos)
{
	void(*FldSetInsPtPositionP)  (FieldType *fldP, UInt16 pos);

	GetParameter (&FldSetInsPtPositionP, sizeof(void *), pFldSetInsPtPosition);
	(*FldSetInsPtPositionP)  (fldP,  pos);
}
#endif

#ifdef L_FldSetMaxChars
void FldSetMaxChars (FieldType *fldP, UInt16 maxChars)
{
	void (*FldSetMaxCharsP) (FieldType *fldP, UInt16 maxChars);

	GetParameter (&FldSetMaxCharsP, sizeof(void *), pFldSetMaxChars);
	(*FldSetMaxCharsP) (fldP,  maxChars);
}
#endif

#ifdef L_FldSetScrollPosition
void FldSetScrollPosition (FieldType *fldP, UInt16 pos)
{
	void (*FldSetScrollPositionP) (FieldType *fldP, UInt16 pos);

	GetParameter (&FldSetScrollPositionP, sizeof(void *), pFldSetScrollPosition);
	(*FldSetScrollPositionP) (fldP,  pos);
}
#endif

#ifdef L_FldSetSelection
void FldSetSelection (FieldType *fldP, UInt16 startPosition,
								UInt16 endPosition)
{
	void (*FldSetSelectionP) (FieldType *fldP, UInt16 startPosition,
								UInt16 endPosition);

	GetParameter (&FldSetSelectionP, sizeof(void *), pFldSetSelection);
	(*FldSetSelectionP) (fldP,  startPosition, endPosition);
}
#endif

#ifdef L_FldSetText
void FldSetText (FieldType *fldP, MemHandle textHandle, UInt16 offset,  UInt16 size)
{
	void (*FldSetTextP) (FieldType *fldP, MemHandle textHandle, UInt16 offset,  UInt16 size);

	GetParameter (&FldSetTextP, sizeof(void *), pFldSetText);
	(*FldSetTextP) (fldP, textHandle,  offset,   size);
}
#endif

#ifdef L_FldSetTextAllocatedSize
void FldSetTextAllocatedSize (FieldType *fldP, UInt16 allocatedSize)
{
	void (*FldSetTextAllocatedSizeP) (FieldType *fldP, UInt16 allocatedSize);

	GetParameter (&FldSetTextAllocatedSizeP, sizeof(void *), pFldSetTextAllocatedSize);
	(*FldSetTextAllocatedSizeP) (fldP, allocatedSize);
}
#endif

#ifdef L_FldSetTextHandle
void FldSetTextHandle (FieldType *fldP, MemHandle textHandle)
{
	void(*FldSetTextHandleP)  (FieldType *fldP, MemHandle textHandle);

	GetParameter (&FldSetTextHandleP, sizeof(void *), pFldSetTextHandle);
	(*FldSetTextHandleP)  (fldP,  textHandle);
}
#endif

#ifdef L_FldSetTextPtr
void FldSetTextPtr (FieldType *fldP, Char *textP)
{
	void (*FldSetTextPtrP) (FieldType *fldP, Char *textP);

	GetParameter (&FldSetTextPtrP, sizeof(void *), pFldSetTextPtr);
	(*FldSetTextPtrP) (fldP, textP);
}
#endif

#ifdef L_FldSetUsable
void FldSetUsable (FieldType *fldP, Boolean usable)
{
	void (*FldSetUsableP) (FieldType *fldP, Boolean usable);

	GetParameter (&FldSetUsableP, sizeof(void *), pFldSetUsable);
	(*FldSetUsableP) (fldP,  usable);
}
#endif

#ifdef L_FldUndo
void FldUndo (FieldType *fldP)
{
	void (*FldUndoP) (FieldType *fldP);
	GetParameter (&FldUndoP, sizeof(void *), pFldUndo);
	(*FldUndoP) (fldP);
}
#endif

#ifdef L_FldWordWrap
UInt16 FldWordWrap (const Char *chars, Int16 maxWidth)
{
	UInt16 (*FldWordWrapP) (const Char *chars, Int16 maxWidth);

	GetParameter (&FldWordWrapP, sizeof(void *), pFldWordWrap);
	return (*FldWordWrapP) (chars,  maxWidth);
}
#endif




////////////////////////////////////////////////////////////
// File Streaming Library, completed 16/16 functions now.
////////////////////////////////////////////////////////////
#ifdef L_FileClearerr
Err FileClearerr (FileHand stream)
{
	Err (*FileClearerrP) (FileHand stream);

	GetParameter (&FileClearerrP, sizeof(void *), pFileClearerr);
	return (*FileClearerrP) ( stream);
}
#endif

#ifdef L_FileClose
Err FileClose (FileHand stream)
{
	Err (*FileCloseP) (FileHand stream);

	GetParameter (&FileCloseP, sizeof(void *), pFileClose);
	return (*FileCloseP) (stream);
}
#endif

/*
Err FileControl (FileOpEnum op, FileHand stream,   void *valueP, Int32 valueLenP)
{
	Err (*FileControlP) (FileOpEnum op, FileHand stream,   void *valueP, Int32 valueLenP);

	GetParameter (&FileControlP, sizeof(void *), pFileControl);
	return (*FileControlP) ( op,  stream,   valueP,  valueLenP);
}
*/
#ifdef L_FileDelete
Err FileDelete (UInt16 cardNo, Char *nameP)
{
	Err (*FileDeleteP) (UInt16 cardNo, Char *nameP);

	GetParameter (&FileDeleteP, sizeof(void *), pFileDelete);
	return (*FileDeleteP) ( cardNo, nameP);
}
#endif

#ifdef L_FileDmRead
Int32 FileDmRead (FileHand stream, void *startofDmChunkP,
						Int32 deskOffset, Int32 objSize, Int32 numObj,
						Err *errP)
{
	Int32 (*FileDmReadP) (FileHand stream, void *startofDmChunkP,
						Int32 deskOffset, Int32 objSize, Int32 numObj,
						Err *errP);

	GetParameter (&FileDmReadP, sizeof(void *), pFileDmRead);
	return (*FileDmReadP) ( stream, startofDmChunkP, deskOffset,  objSize,  numObj,
						errP);
}
#endif

#ifdef L_FileEOF
Err FileEOF (FileHand stream)
{
	Err (*FileEOFP) (FileHand stream);

	GetParameter (&FileEOFP, sizeof(void *), pFileEOF);
	return (*FileEOFP) (stream);
}
#endif

#ifdef L_FileError
Err FileError (FileHand stream)
{
	Err (*FileErrorP) (FileHand stream);

	GetParameter (&FileErrorP, sizeof(void *), pFileError);
	return (*FileErrorP) (stream);
}
#endif

#ifdef L_FileFlush
Err FileFlush (FileHand stream)
{
	Err (*FileFlushP) (FileHand stream);

	GetParameter (&FileFlushP, sizeof(void *), pFileFlush);
	return (*FileFlushP) ( stream);
}
#endif

#ifdef L_FileGetLastError
Err FileGetLastError (FileHand stream)
{
	Err (*FileGetLastErrorP) (FileHand stream);

	GetParameter (&FileGetLastErrorP, sizeof(void *), pFileGetLastError);
	return (*FileGetLastErrorP) ( stream);
}
#endif

#ifdef L_FileOpen
FileHand FileOpen (UInt16 cardNo, Char *nameP, UInt32 type,
								  UInt32 creator, UInt32 openMode, Err *errP)
{
	FileHand (*FileOpenP) (UInt16 cardNo, Char *nameP, UInt32 type,
								  UInt32 creator, UInt32 openMode, Err *errP);

	GetParameter (&FileOpenP, sizeof(void *), pFileOpen);
	return (*FileOpenP) ( cardNo, nameP,  type,   creator,  openMode, errP);
}
#endif

#ifdef L_FileRead
Int32 FileRead (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP)
{
	Int32 (*FileReadP) (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);

	GetParameter (&FileReadP, sizeof(void *), pFileRead);
	return (*FileReadP) ( stream, bufP,  objSize,
					   numObj, errP);
}
#endif

#ifdef L_FileRewind
Err FileRewind (FileHand stream)
{
	Err (*FileRewindP) (FileHand stream);

	GetParameter (&FileRewindP, sizeof(void *), pFileRewind);
	return (*FileRewindP) (stream);
}
#endif

#ifdef L_FileSeek
Err FileSeek (FileHand stream, Int32 offset, UInt16 origin)
{
	Err (*FileSeekP) (FileHand stream, Int32 offset, UInt16 origin);

	GetParameter (&FileSeekP, sizeof(void *), pFileSeek);
	return (*FileSeekP) ( stream,  offset,  origin);
}
#endif

#ifdef L_FileTell
Int32 FileTell (FileHand stream, Int32 *fileSizeP, Err *errP)
{
	Int32 (*FileTellP) (FileHand stream, Int32 *fileSizeP, Err *errP);

	GetParameter (&FileTellP, sizeof(void *), pFileTell);
	return (*FileTellP) ( stream, fileSizeP, errP);
}
#endif

#ifdef L_FileTruncate
Err FileTruncate (FileHand stream, Int32 newSize)
{
	Err (*FileTruncateP) (FileHand stream, Int32 newSize);

	GetParameter (&FileTruncateP, sizeof(void *), pFileTruncate);
	return (*FileTruncateP) ( stream,  newSize);
}
#endif

#ifdef L_FileWrite
Int32 FileWrite (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP)
{
	Int32 (*FileWriteP) (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);

	GetParameter (&FileWriteP, sizeof(void *), pFileWrite);
	return (*FileWriteP) ( stream, bufP,  objSize, numObj, errP);
}
#endif




////////////////////////////////////////////////////////////
// Find Processing Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
#ifdef L_FindStrInStr
Boolean FindStrInStr (Char const *strToSearch, Char const *strToFind,
	UInt16 *posP)
{
	Boolean (*FindStrInStrP) (Char const *strToSearch, Char const *strToFind, 
	UInt16 *posP);

	GetParameter (&FindStrInStrP, sizeof(void *), pFindStrInStr);
	return (*FindStrInStrP) (strToSearch, strToFind, posP);
}
#endif
/*
#ifdef L_FindSaveMatch
Boolean FindSaveMatch (FindParamsPtr findParams, UInt16 recordNum, 
	UInt16 pos, UInt16 fieldNum, UInt32 appCustom, UInt16 cardNo, LocalID dbID)
{
	Boolean (*FindSaveMatchP) (FindParamsPtr findParams, UInt16 recordNum, 
	UInt16 pos, UInt16 fieldNum, UInt32 appCustom, UInt16 cardNo, LocalID dbID);

	GetParameter (&FindSaveMatchP, sizeof(void *), pFindSaveMatch);
	return  (*FindSaveMatchP) ( findParams,  recordNum,  pos,  fieldNum,  appCustom,  cardNo,  dbID);

}
#endif

#ifdef L_FindGetLineBounds
void FindGetLineBounds (const FindParamsType *findParams, RectanglePtr r)
{
	void (*FindGetLineBoundsP) (const FindParamsType *findParams, RectanglePtr r);

	GetParameter (&FindGetLineBoundsP, sizeof(void *), pFindGetLineBounds);
	 (*FindGetLineBoundsP) (findParams,  r);
}
#endif

#ifdef L_FindDrawHeader
Boolean FindDrawHeader (FindParamsPtr findParams, Char const *title)
{
	Boolean (*FindDrawHeaderP) (FindParamsPtr findParams, Char const *title);

	GetParameter (&FindDrawHeaderP, sizeof(void *), pFindDrawHeader);
	return  (*FindDrawHeaderP) ( findParams, title);
}
#endif

*/


////////////////////////////////////////////////////////////
// Float Manager Library, completed 12/12 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_FplAdd
FloatType FplAdd (FloatType a, FloatType b)
{
	FloatType (*FplAddP) (FloatType a, FloatType b);

	GetParameter (&FplAddP, sizeof(void *), pFplAdd);
	return (*FplAddP) ( a,  b);
}
#endif

#ifdef L_ FplAToF
FloatType FplAToF (char* s)
{
	FloatType (*FplAToFP) (char* s);

	GetParameter (&FplAToFP, sizeof(void *), pFplAToF);
	return (*FplAToFP) (s);
}
#endif

#ifdef L_FplBase10Info
Err FplBase10Info (FloatType a, ULong* mantissaP,Int* exponentP, Int* signP) 
{
	Err (*FplBase10InfoP) (FloatType a, ULong* mantissaP,Int* exponentP, Int* signP) ;

	GetParameter (&FplBase10InfoP, sizeof(void *), pFplBase10Info);
	return (*FplBase10InfoP) ( a,  mantissaP, exponentP,  signP) ;
}
#endif

#ifdef L_FplDiv
FloatType FplDiv (FloatType dividend,FloatType divisor)
{
	FloatType (*FplDivP) (FloatType dividend,FloatType divisor);

	GetParameter (&FplDivP, sizeof(void *), pFplDiv);
	return (*FplDivP) ( dividend, divisor);
}
#endif

#ifdef L_FplFloatToLong
Long FplFloatToLong (FloatType f)
{
	Long (*FplFloatToLongP) (FloatType f);

	GetParameter (&FplFloatToLongP, sizeof(void *), pFplFloatToLong);
	return 
}
#endif

#ifdef L_FplFloatToULong
ULong FplFloatToULong (FloatType f)
{
	ULong (*FplFloatToULongP) (FloatType f);

	GetParameter (&FplFloatToULongP, sizeof(void *), pFplFloatToULong);
	return (*FplFloatToULongP) (f);
}
#endif

#ifdef L_FplFree
void FplFree()
{
	void (*FplFreeP)();

	GetParameter (&FplFreeP, sizeof(void *), pFplFree);
	(*FplFreeP)(); 
}
#endif

#ifdef L_FplFToA
Err FplFToA (FloatType a, char* s)
{
	Err (*FplFToAP) (FloatType a, char* s);

	GetParameter (&FplFToAP, sizeof(void *), pFplFToA);
	return (*FplFToAP) (a,s);
}
#endif
*/
#ifdef L_FplInit
Err FplInit()
{
	Err (*FplInitP)();

	GetParameter (&FplInitP, sizeof(void *), pFplInit);
	return (*FplInitP)();
}
#endif
/*
#ifdef L_FplLongToFloat
FloatType FplLongToFloat (Long x)
{
	FloatType (*FplLongToFloatP) (Long x);

	GetParameter (&FplLongToFloatP, sizeof(void *), pFplLongToFloat);
	return (*FplLongToFloatP) (x);
}
#endif

#ifdef L_FplMul
FloatType FplMul (FloatType a, FloatType b)
{
	FloatType (*FplMulP) (FloatType a, FloatType b);

	GetParameter (&FplMulP, sizeof(void *), pFplMul);
	return  (*FplMulP) (a, b);
}
#endif

#ifdef L_FplSub
FloatType FplSub (FloatType a, FloatType b)
{
	FloatType (*FplSubP) (FloatType a, FloatType b);

	GetParameter (&FplSubP, sizeof(void *), pFplSub);
	return (*FplSubP) ( a,  b);
}
#endif


*/










