#include <VCommon.h>
#include <VParser.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#include "wisapi.h"


////////////////////////////////////////////////////////////
// Field Processing Library, completed 52/52 functions now.
////////////////////////////////////////////////////////////
void PipeFldCalcFieldHeight (void)
{
	WriteParameter (FldCalcFieldHeight, sizeof(void*), pFldCalcFieldHeight);
}

void PipeFldCompactText (void)
{
//	WriteParameter (FldCompactText, sizeof(void*), pFldCompactText);
}

void PipeFldCopy (void)
{
	WriteParameter (FldCopy, sizeof(void*), pFldCopy);
}

void PipeFldCut (void)
{
	WriteParameter (FldCut, sizeof(void*), pFldCut);
}

void PipeFldDelete(void)
{
	WriteParameter (FldDelete, sizeof(void*), pFldDelete);
}

void PipeFldDirty (void)
{
	WriteParameter (FldDirty, sizeof(void*), pFldDirty);
}

void PipeFldDrawField (void)
{
	WriteParameter (FldDrawField, sizeof(void*), pFldDrawField);
}

void PipeFldEraseField (void)
{
	WriteParameter (FldEraseField, sizeof(void*), pFldEraseField);
}

void PipeFldFreeMemory (void)
{
	WriteParameter (FldFreeMemory, sizeof(void*), pFldFreeMemory);
}

void PipeFldGetAttributes (void)
{
	WriteParameter (FldGetAttributes, sizeof(void*), pFldGetAttributes);
}

void PipeFldGetBounds (void)
{
	WriteParameter (FldGetBounds, sizeof(void*), pFldGetBounds);
}

void PipeFldGetFont (void)
{
	WriteParameter (FldGetFont, sizeof(void*), pFldGetFont);
}

void PipeFldGetInsPtPosition (void)
{
	WriteParameter (FldGetInsPtPosition, sizeof(void*), pFldGetInsPtPosition);
}

void PipeFldGetMaxChars (void)
{
	WriteParameter (FldGetMaxChars, sizeof(void*), pFldGetMaxChars);
}

void PipeFldGetNumberOfBlankLines (void)
{
	WriteParameter (FldGetNumberOfBlankLines, sizeof(void*), pFldGetNumberOfBlankLines);
}

void PipeFldGetScrollPosition (void)
{
//	WriteParameter (FldGetScrollPosition, sizeof(void*), pFldGetScrollPosition);
}

void PipeFldGetScrollValues (void)
{
	WriteParameter (FldGetScrollValues, sizeof(void*), pFldGetScrollValues);
}

void PipeFldGetSelection (void)
{
	WriteParameter (FldGetSelection, sizeof(void*), pFldGetSelection);
}

void PipeFldGetTextAllocatedSize (void)
{
	WriteParameter (FldGetTextAllocatedSize, sizeof(void*), pFldGetTextAllocatedSize);
}

void PipeFldGetTextHandle (void)
{
	WriteParameter (FldGetTextHandle, sizeof(void*), pFldGetTextHandle);
}

void PipeFldGetTextHeight(void)
{
//	WriteParameter (FldGetTextHeight, sizeof(void*), pFldGetTextHeight);
}

void PipeFldGetTextLength (void)
{
	WriteParameter (FldGetTextLength, sizeof(void*), pFldGetTextLength);
}

void PipeFldGetTextPtr (void)
{
	WriteParameter (FldGetTextPtr, sizeof(void*), pFldGetTextPtr);
}

void PipeFldGetVisibleLines (void)
{
	WriteParameter (FldGetVisibleLines, sizeof(void*), pFldGetVisibleLines);
}

void PipeFldGrabFocus (void)
{
	WriteParameter (FldGrabFocus, sizeof(void*), pFldGrabFocus);
}

void PipeFldHandleEvent (void)
{
//	WriteParameter (FldHandleEvent, sizeof(void*), pFldHandleEvent);
}

void PipeFldInsert (void)
{
	WriteParameter (FldInsert, sizeof(void*), pFldInsert);
}

void PipeFldMakeFullyVisible (void)
{
	WriteParameter (FldMakeFullyVisible, sizeof(void*), pFldMakeFullyVisible);
}

void PipeFldNewField (void)
{
	WriteParameter (FldNewField, sizeof(void*), pFldNewField);
}

void PipeFldPaste(void)
{
	WriteParameter (FldPaste, sizeof(void*), pFldPaste);
}

void PipeFldRecalculateField (void)
{
	WriteParameter (FldRecalculateField, sizeof(void*), pFldRecalculateField);
}

void PipeFldReleaseFocus (void)
{
	WriteParameter (FldReleaseFocus, sizeof(void*), pFldReleaseFocus);
}

void PipeFldScrollable (void) 
{
//	WriteParameter (FldScrollable, sizeof(void*), pFldScrollable);
}

void PipeFldScrollField(void)
{
	WriteParameter (FldScrollField, sizeof(void*), pFldScrollField);
}

void PipeFldSendChangeNotification (void)
{
//	WriteParameter (FldSendChangeNotification, sizeof(void*), pFldSendChangeNotification);
}

void PipeFldSendHeightChangeNotification (void)
{
//	WriteParameter (FldSendHeightChangeNotification, sizeof(void*), pFldSendHeightChangeNotification);
}

void PipeFldSetAttributes (void)
{
	WriteParameter (FldSetAttributes, sizeof(void*), pFldSetAttributes);
}

void PipeFldSetBounds (void)
{
	WriteParameter (FldSetBounds, sizeof(void*), pFldSetBounds);
}

void PipeFldSetDirty (void)
{
	WriteParameter (FldSetDirty, sizeof(void*), pFldSetDirty);
}

void PipeFldSetFont (void)
{
	WriteParameter (FldSetFont , sizeof(void*), pFldSetFont);
}

void PipeFldSetInsertionPoint (void)
{
	WriteParameter (FldSetInsertionPoint, sizeof(void*), pFldSetInsertionPoint);
}

void PipeFldSetInsPtPosition (void)
{
	WriteParameter (FldSetInsPtPosition, sizeof(void*), pFldSetInsPtPosition);
}

void PipeFldSetMaxChars (void)
{
	WriteParameter (FldSetMaxChars, sizeof(void*), pFldSetMaxChars);
}

void PipeFldSetScrollPosition (void)
{
	WriteParameter (FldSetScrollPosition, sizeof(void*), pFldSetScrollPosition);
}

void PipeFldSetSelection (void)
{
	WriteParameter (FldSetSelection, sizeof(void*), pFldSetSelection);
}

void PipeFldSetText  (void)
{
	WriteParameter (FldSetText, sizeof(void*), pFldSetText);
}

void PipeFldSetTextAllocatedSize  (void)
{
	WriteParameter (FldSetTextAllocatedSize, sizeof(void*), pFldSetTextAllocatedSize);
}

void PipeFldSetTextHandle  (void)
{
	WriteParameter (FldSetTextHandle, sizeof(void*), pFldSetTextHandle);
}

void PipeFldSetTextPtr  (void)
{
	WriteParameter (FldSetTextPtr, sizeof(void*), pFldSetTextPtr);
}

void PipeFldSetUsable  (void)
{
	WriteParameter (FldSetUsable, sizeof(void*), pFldSetUsable);
}

void PipeFldUndo  (void)
{
	WriteParameter (FldUndo, sizeof(void*), pFldUndo);
}

void PipeFldWordWrap  (void)
{
//	WriteParameter (FldWordWrap, sizeof(void*), pFldWordWrap);
}




////////////////////////////////////////////////////////////
// File Streaming Library, completed 16/16 functions now.
////////////////////////////////////////////////////////////

void PipeFileClearerr  (void)
{
//	WriteParameter (FileClearerr, sizeof(void*), pFileClearerr);
}

void PipeFileClose (void)
{
	WriteParameter (FileClose, sizeof(void*), pFileClose);
}

void PipeFileControl (void)
{
//	WriteParameter (FileControl, sizeof(void*), pFileControl);
}

void PipeFileDelete  (void)
{
	WriteParameter (FileDelete, sizeof(void*), pFileDelete);
}

void PipeFileDmRead (void)
{
//	WriteParameter (FileDmRead, sizeof(void*), pFileDmRead);
}

void PipeFileEOF  (void)
{
	WriteParameter (FileEOF, sizeof(void*), pFileEOF);
}

void PipeFileError (void)
{
//	WriteParameter (FileError, sizeof(void*), pFileError);
}

void PipeFileFlush  (void)
{
	WriteParameter (FileFlush, sizeof(void*), pFileFlush);
}

void PipeFileGetLastError  (void)
{
//	WriteParameter (FileGetLastError, sizeof(void*), pFileGetLastError);
}

void PipeFileOpen (void)
{
	WriteParameter (FileOpen, sizeof(void*), pFileOpen);
}

void PipeFileRead  (void)
{
	WriteParameter (FileRead, sizeof(void*), pFileRead);
}

void PipeFileRewind  (void)
{
	WriteParameter (FileRewind, sizeof(void*), pFileRewind);
}

void PipeFileSeek  (void)
{
	WriteParameter (FileSeek, sizeof(void*), pFileSeek);
}

void PipeFileTell (void)
{
	WriteParameter (FileTell, sizeof(void*), pFileTell);
}

void PipeFileTruncate (void)
{
//	WriteParameter (FileTruncate, sizeof(void*), pFileTruncate);
}

void PipeFileWrite  (void)
{
	WriteParameter (FileWrite, sizeof(void*), pFileWrite);
}




////////////////////////////////////////////////////////////
// Find Processing Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeFindDrawHeader  (void)
{
//	WriteParameter (FindDrawHeader, sizeof(void*), pFindDrawHeader);
}
void PipeFindGetLineBounds (void)
{
//	WriteParameter (FindGetLineBounds, sizeof(void*), pFindGetLineBounds);
}
void PipeFindSaveMatch (void)
{
//	WriteParameter (FindSaveMatch, sizeof(void*), pFindSaveMatch);
}
void PipeFindStrInStr  (void)
{
//	WriteParameter (FindStrInStr, sizeof(void*), pFindStrInStr);
}


////////////////////////////////////////////////////////////
// Float Manager Library, completed 12/12 functions now.
////////////////////////////////////////////////////////////
void PipeFplAdd (void)
{
//	WriteParameter (FplAdd, sizeof(void*), pFplAdd);
}
void PipeFplAToF  (void)
{
//	WriteParameter (FplAToF, sizeof(void*), pFplAToF);
}
void PipeFplBase10Info  (void)
{
//	WriteParameter (FplBase10Info, sizeof(void*), pFplBase10Info);
}
void PipeFplDiv (void)
{
//	WriteParameter (FplDiv , sizeof(void*), pFplDiv );
}
void PipeFplFloatToLong  (void)
{
//	WriteParameter (FplFloatToLong, sizeof(void*), pFplFloatToLong);
}
void PipeFplFloatToULong  (void)
{
//	WriteParameter (FplFloatToULong, sizeof(void*), pFplFloatToULong);
}
void PipeFplFree  (void)
{
//	WriteParameter (FplFree, sizeof(void*), pFplFree);
}
void PipeFplFToA(void)
{
//	WriteParameter (FplFToA, sizeof(void*), pFplFToA);
}
void PipeFplInit (void)
{
//	WriteParameter (FplInit, sizeof(void*), pFplInit);
}
void PipeFplLongToFloat  (void)
{
//	WriteParameter (FplLongToFloat, sizeof(void*), pFplLongToFloat);
}
void PipeFplMul (void)
{
//	WriteParameter (FplMul, sizeof(void*), pFplMul);
}
void PipeFplSub  (void)
{
//	WriteParameter (FplSub, sizeof(void*), pFplSub);
}



