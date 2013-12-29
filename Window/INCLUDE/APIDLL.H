/*========================================================
  Apilib.h
  This file list all current supported function 
  compitable with Palm OS.

  Current status completed 432 functions.
  Total List 539 functions.
  350 funtions not list below.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0814, 2001 by Jerry Chu
 =========================================================*/
#ifndef __APIDLL_H__
#define __APIDLL_H__

#include <System/NetMgr.h>

#define  _APM_SIMULATOR
#define	_WISEXPORTDLL

#ifndef	LINUX
#ifndef _WISIMP

#if defined(_WISEXPORTDLL)
#define _WISIMP __declspec(dllexport)
#elif defined(_WISIMPORTDLL)
#define _WISIMP __declspec(dllimport)
#endif

#endif
#else
#define	_WISIMP	extern
#endif

_WISIMP Boolean VSetRCPFile (Char *filename);



////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
_WISIMP UInt32 AlmGetAlarm (UInt16 cardNo, LocalID dbID, UInt32 *refP);
_WISIMP UInt32 AlmGetProcAlarm (AlmAlarmProcPtr procP, UInt32 refP);
_WISIMP Err AlmSetAlarm (UInt16 cardNo, LocalID dbID, UInt32 ref,
								UInt32 alarmSeconds, Boolean quiet);
_WISIMP Err AlmSetProcAlarm (AlmAlarmProcPtr proc, UInt32 ref, UInt32 alarmSeconds);


////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 0/9 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Category Library, completed 9/11 functions now.
////////////////////////////////////////////////////////////
_WISIMP void CategoryCreateList (DmOpenRef db, ListType *listP, UInt16 currentCategory,
						 Boolean showAll, Boolean showUneditables, 
						 UInt8 numUneditableCategories,
						 UInt32 editingStrID, Boolean resizeList);
//_WISIMP CategoryEdit (DmOpenRef db, UInt16 *categoryP, UInt32 titleStrID,
//					 UInt16 numUneditableCategories);
_WISIMP UInt16 CategoryFind (DmOpenRef db, char *name);
_WISIMP void CategoryFreeList (DmOpenRef db, const ListType *listP, 
							  Boolean showAll, UInt32 editingStrID);
_WISIMP void CategoryGetName (DmOpenRef db, UInt16 index, char *name);
_WISIMP UInt16 CategoryGetNext (DmOpenRef db, UInt16 index);
_WISIMP void CategoryInitialize (AppInfoPtr appInfoP, UInt16 localizedAppInfoStrID);
_WISIMP Boolean CategorySelect (DmOpenRef db, const FormType *frm, UInt16 ctlID,
					 UInt16 lstID, Boolean title, UInt16 *categoryP,
					 char *categoryName, UInt8 numUneditableCategories,
					 UInt32 editingStrID);
_WISIMP void CategorySetName (DmOpenRef db, UInt16 index, const char *name);
_WISIMP void CategorySetTriggerLabel (ControlType *ctl, Char *name);
_WISIMP void CategoryTruncateName (Char *name, UInt16 maxWidth);



////////////////////////////////////////////////////////////
// Character Attributes Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Clipboad functions, completed 1/3 functions now.
////////////////////////////////////////////////////////////
_WISIMP void ClipboardAddItem (const ClipboardFormatType format, const void *ptr, UInt16 length);
//_WISIMP Err ClipboardAppendItem (const ClipboardFormatType format, const void *ptr, UInt16 length);
//_WISIMP MemHandle ClipboardGetItem (const ClipboardFormatType format, UInt16 *length);


////////////////////////////////////////////////////////////
// Connection Manager Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Control Handle Library, completed 19/20 functions now.
////////////////////////////////////////////////////////////
_WISIMP void CtlDrawControl (ControlType *controlP);
_WISIMP Boolean CtlEnabled (const ControlType *controlP);
_WISIMP void CtlEraseControl (ControlType *controlP);
_WISIMP const Char *CtlGetLabel (const ControlType *controlP);
_WISIMP void CtlGetSliderValues (const ControlType *ctlP, UInt16 *minValueP,
								  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP);
_WISIMP Int16 CtlGetValue (const ControlType *controlP);
//_WISIMP Boolean CtlHandleEvent (ControlType *controlP, EventType pEvent);
_WISIMP void CtlHideControl (ControlType *controlP);
_WISIMP void CtlHitControl (const ControlType *controlP);
_WISIMP ControlType *CtlNewControl (void **formPP, UInt16 ID, ControlStyleType style,
								   const Char *textP, Coord x, Coord y, Coord width,
								   Coord height, FontID font, UInt8 group, 
								   Boolean leftAnchor);
_WISIMP GraphicControlType *CtlNewGraphicControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID bitmapID, 
								   DmResID selectedBitmapID, Coord x, Coord y, 
								   Coord width, Coord height, UInt8 group, 
								   Boolean leftAnchor);
_WISIMP SliderControlType *CtlNewSliderControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID thumbID, 
								   DmResID backgroundID, Coord x, Coord y, 
								   Coord width, Coord height, UInt16 minValue,
								   UInt16 maxValue, UInt16 pageSize, UInt16 value);
_WISIMP void CtlSetEnabled (ControlType *controlP, Boolean enable);
_WISIMP void CtlSetLabel (ControlType *controlP, const Char *newLabel);
_WISIMP void CtlSetGraphics (ControlType *controlP, DmResID newBitmapID,
							  DmResID newSelectedBitmapID);
_WISIMP void CtlSetSliderValue (ControlType *ctlP, const UInt16 *minValueP,
								  const UInt16 *maxValueP, const UInt16 *pageSizeP, 
								  const UInt16 *valueP);
_WISIMP void CtlSetUsable (ControlType *controlP, Boolean usable);
_WISIMP void CtlSetValue (ControlType *controlP, Int16 newValue);
_WISIMP void CtlShowControl (ControlType *controlP);
_WISIMP Boolean CtlValidatePointer (const ControlType *controlP);



///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 0/6 functions now.
///////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// DataBase Library, completed 35/66 functions now.
////////////////////////////////////////////////////////////
//_WISIMP Err DmArchiveRecord (DmOpenRef dbP, UInt16 index);
_WISIMP Err	DmAttachRecord (DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP);
//_WISIMP Err		DmAttachResource (DmOpenRef dbP, MemHandle newH, DmResType resType, DmResID resID);
_WISIMP Err	DmCloseDatabase (DmOpenRef dbp);
_WISIMP Err	DmCreateDatabase (UInt16 cardNo, const Char *nameP, UInt32 creator,
					  UInt32 type, Boolean resDB);
//_WISIMP Err DmCreateDatabaseFromImage (MemPtr bufferP);
_WISIMP Err DmDatabaseInfo (UInt16 cardNo, LocalID dbID, Char *nameP, UInt16 *attributesP,
					UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP,
					UInt32 *typeP, UInt32 *creatorP);
//_WISIMP Err DmDatabaseProtect (UInt16 cardNo, LocalID dbID, Boolean protect);
_WISIMP Err DmDatabaseSize (UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP);
_WISIMP Err DmDeleteCategory (DmOpenRef dbp, UInt16 categoryNum);
//_WISIMP Err DmDeleteDatabase (UInt16 cardNo, LocalID dbID);
_WISIMP Err DmDeleteRecord (DmOpenRef dbp, UInt16 index);
//_WISIMP Err DmDetachRecord (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);
//_WISIMP Err DmDetachResource (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);
//_WISIMP Err DmFindDatabase (UInt16 cardNo, const Char *nameP);
//_WISIMP Err DmFindRecordByID (DmOpenRef dbp, UInt32 uniqueID, UInt16 *indexP);
//_WISIMP Err DmFindResource (DmOpenRef dbp, DmResType resType, DmResID resID, memHandle resH);
//_WISIMP UInt16 DmFindResourceType (DmOpenRef dbp, DmResType resType, UInt16 typeIndex);
//_WISIMP UInt16 DmFindSortPosition (DmOpenRef dbp, void *newRecord, SortRecordInfoPtr newRecordInfo,
//						   DmComparF *compar, Int16 other);
//_WISIMP LocalID DmGetAppInfoID (DmOpenRef dbP);
_WISIMP LocalID DmGetDatabase (UInt16 cardNo, UInt16 index);
//_WISIMP void DmGetDatabaseLocaState (DmOpenRef dbR, UInt8 *highest, UInt32 *count, UInt32 *busy);
//_WISIMP Err DmGetLastErr (void);
_WISIMP Err DmGetNextDatabaseByTypeCreator (Boolean newSearch, DmSearchStatePtr stateInfoP, UInt32 type,
									UInt32 creator, Boolean onlyLatesVers, UInt16 *cardNoP, LocalID *dbIDP);
_WISIMP MemHandle	DmGetRecord (DmOpenRef dbP, UInt16 index);
//_WISIMP MemHandle	DmGetResource (DmResType type, DmResID resID);
//_WISIMP MemHandle	DmGetResourceIndex (DmOpenRef dbP, UInt16 index);
_WISIMP MemHandle	DmGet1Resource (DmResType type, DmResID resID);
_WISIMP Err	DmInsertionSort (DmOpenRef dbR, DmComparF *compar, Int16 other);
_WISIMP Err DmMoveCategory (DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty);
_WISIMP Err DmMoveRecord (DmOpenRef dbP, UInt16 from, UInt16 to);
_WISIMP MemHandle	DmNewHandle (DmOpenRef dbP, UInt32 size);
_WISIMP MemHandle	DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
//_WISIMP MemHandle DmNewReresource (DmOpenRef dbP, DmResType resType, DmResID resID, UInt32 size);
//_WISIMP DmOpenRef DmNextOpenDatabase (DmOpenRef currentP);
_WISIMP UInt16 DmNumDatabases (UInt16 cardNo);
_WISIMP UInt16	DmNumRecords (DmOpenRef dbP);
_WISIMP UInt16 DmNumRecordsInCategory (DmOpenRef dbP, UInt16 category);
//_WISIMP UInt16 DmNumResources (DmOpenRef dbP);
//_WISIMP DmOpenRef DmOpenDatabase (UInt32 cardNo, LocalID dbID, UInt16 mode);
_WISIMP DmOpenRef DmOpenDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode);
_WISIMP Err DmOpenDatabaseInfo (DmOpenRef dbP, LocalID *dbIDP, UInt16 *openCountP, UInt16 *modeP,
						UInt16 *cardNoP, Boolean *resDBP);
//_WISIMP DmOpenRef DmOpenDBNoOvelay (UInt32 cardNo, LocalID dbID, UInt16 mode);
_WISIMP UInt16 DmPositionInCategory (DmOpenRef dbP, UInt16 index, UInt16 category);
//_WISIMP MemHandle DmQueryNextInCategory (DmOpenRef dbP, UInt16 *indexP, UInt16 category);
_WISIMP MemHandle DmQueryRecord (DmOpenRef dbP, UInt16 index);
//_WISIMP Err DmQuickSort (DmOpenRef dbP, DmComparF *compar, Int16 other);
_WISIMP Err DmRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP, LocalID *chunkIDP);
_WISIMP Err DmReleaseRecord (DmOpenRef dbP, UInt16 index, Boolean dirty);
_WISIMP Err DmReleaseResource (MemHandle resourceH);
_WISIMP Err DmRemoveRecord (DmOpenRef dbP, UInt16 index);
//_WISIMP Err DmRemoveResource (DmOpenRef dbP, UInt16 index);
//_WISIMP Err DmRemoveSecretRecord (DmOpenRef dbP);
_WISIMP MemHandle DmResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 newSize);
//_WISIMP Err DmResizeResource (MemHandle resourceH, UInt32 newSize);
//Err DmResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP,
//					LocalID *chunkLocalIDP);
_WISIMP Err	DmResetRecordStates(DmOpenRef dbP);
//_WISIMP UInt16 DmSearchRecord (MemHandle recH, DmOpenRef *dbPP);
//_WISIMP UInt16 DmSearchResource (DmResType resType, DmResID resID, MemHandle resH, DmOpenRef *dbPP);
_WISIMP Err DmSeekRecordInCategory (DmOpenRef dbP, UInt16 *indexP, Int16 offset,
							Int16 direction, UInt16 category);
_WISIMP Err DmSet (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value);
_WISIMP Err DmSetDatabaseInfo (UInt16 cardNo, LocalID dbID, const Char *nameP, UInt16 *attributesP,
					   UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					   UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP, UInt32 *typeP,
					   UInt32 *creatorP);
_WISIMP Err DmSetRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP);
//_WISIMP Err DmSetResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP);
_WISIMP Err DmStrCopy (void *recordP, UInt32 offset, const Char *srcP);
_WISIMP Err	DmWrite (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes);
//_WISIMP Err DmWriteCheck (void *recordP, UInt32 offset, UInt32 bytes);



////////////////////////////////////////////////////////////
// Error Manager Library, completed 3/6 functions now.
////////////////////////////////////////////////////////////
_WISIMP void ErrFatalDisplayIf (Boolean condidtion, Char *msg);
_WISIMP void ErrFatalDisplay (Char *msg);
_WISIMP void ErrNonFatalDisplayIf (Boolean condidtion, Char *msg);



////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 0/9 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Feature Manager Library, completed 1/7 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err FtrGet (UInt32 creator, UInt16 featureNum, UInt32 *valueP);



////////////////////////////////////////////////////////////
// Field Processing Library, completed 42/52 functions now.
////////////////////////////////////////////////////////////
_WISIMP UInt16 FldCalcFieldHeight (const Char* chars, UInt16 maxWidth);
//_WISIMP void FldCompactText (FieldType *fldP);
_WISIMP void FldCopy (const FieldType *fldP);
_WISIMP void FldCut (FieldType *fldP);
_WISIMP void FldDelete (FieldType *fldP, UInt16 start, UInt16 end);
_WISIMP Boolean FldDirty (FieldType *fldP);
_WISIMP void FldDrawField (FieldType *fldP);
_WISIMP void FldEraseField (FieldType *fldP);
_WISIMP void FldFreeMemory (FieldType *fldP);
_WISIMP void FldGetAttributes (const FieldType *fldP, FieldAttrPtr attrP);
_WISIMP void FldGetBounds (const FieldType *fldP, RectangleType *rect);
_WISIMP FontID FldGetFont (const FieldType *fldP);
_WISIMP UInt16 FldGetInsPtPosition (const FieldType *fldP);
_WISIMP UInt16 FldGetMaxChars (const FieldType *fldP);
_WISIMP UInt16 FldGetNumberOfBlankLines (const FieldType *fldP);
//_WISIMP UInt16 FldGetScrollPosition (const FieldType *fldP);
_WISIMP void FldGetScrollValues (const FieldType *fldP, UInt16 *scrollPosP,
								UInt16 *textHeightP, UInt16 *fieldHeightP);
_WISIMP void FldGetSelection (const FieldType *fldP, UInt16 *startPosition,
								UInt16 *endPosition);
_WISIMP UInt16 FldGetTextAllocatedSize (const FieldType *fldP);
_WISIMP MemHandle FldGetTextHandle (const FieldType *fldP);
//_WISIMP UInt16 FldGetTextHeight (const FieldType *fldP);
_WISIMP UInt16 FldGetTextLength (const FieldType *fldP);
_WISIMP Char *FldGetTextPtr (FieldType *fldP);
_WISIMP UInt16 FldGetVisibleLines (const FieldType *fldP);
_WISIMP void FldGrabFocus (FieldType *fldP);
//_WISIMP Boolean FldHandleEvent (const FieldType *fldP, EventType *eventP);
_WISIMP Boolean FldInsert (FieldType *fldP, const Char* insertChars, UInt16 insertLen);
_WISIMP Boolean FldMakeFullyVisible (FieldType *fldP);
_WISIMP FieldType *FldNewField (void **formPP, UInt16 id, Coord x, Coord y, Coord width,
						Coord heght, FontID font, UInt32 maxChars, Boolean editable,
						Boolean underlined, Boolean singleLine, Boolean dynamicSize,
						JustificationType justification, Boolean autoShift,
						Boolean hasScrollBar, Boolean numeric);
_WISIMP void FldPaste (FieldType *fldP);
_WISIMP void FldRecalculateField (FieldType *fldP, Boolean redraw);
_WISIMP void FldReleaseFocus (FieldType *fldP);
//_WISIMP Boolean FldScrollable (const FieldType *fldP, WinDirectionType direction); 
_WISIMP void FldScrollField (FieldType *fldP, UInt16 linesToScroll, WinDirectionType direction); 
//_WISIMP void FldSendChangeNotification (const FieldType *fldP);
//_WISIMP void FldSendHeightChangeNotification (const FieldType *fldP, UInt16 pos, Int16 numLines);
_WISIMP void FldSetAttributes (FieldType *fldP, const FieldAttrType *attrP);
_WISIMP void FldSetBounds (FieldType *fldP, const RectangleType *rP);
_WISIMP void FldSetDirty (FieldType *fldP, Boolean dirty);
_WISIMP void FldSetFont (FieldType *fldP, FontID fontID);
_WISIMP void FldSetInsertionPoint (FieldType *fldP, UInt16 pos);
_WISIMP void FldSetInsPtPosition (FieldType *fldP, UInt16 pos);
_WISIMP void FldSetMaxChars (FieldType *fldP, UInt16 maxChars);
_WISIMP void FldSetScrollPosition (FieldType *fldP, UInt16 pos);
_WISIMP void FldSetSelection (FieldType *fldP, UInt16 startPosition,
								UInt16 endPosition);
_WISIMP void FldSetText (FieldType *fldP, MemHandle textHandle, UInt16 offset,
						  UInt16 size);
_WISIMP void FldSetTextAllocatedSize (FieldType *fldP, UInt16 allocatedSize);
_WISIMP void FldSetTextHandle (FieldType *fldP, MemHandle textHandle);
_WISIMP void FldSetTextPtr (FieldType *fldP, Char *textP);
_WISIMP void FldSetUsable (FieldType *fldP, Boolean usable);
_WISIMP void FldUndo (FieldType *fldP);
//_WISIMP UInt16 FldWordWrap (const Char *chars, Int16 maxWidth);



////////////////////////////////////////////////////////////
// File Streaming Library, completed 10/16 functions now.
////////////////////////////////////////////////////////////
//_WISIMP Err FileClearerr (FileHand stream);
_WISIMP Err FileClose (FileHand stream);
//_WISIMP Err FileControl (FileOpEnum op, FileHand stream, 
//					  void *valueP, Int32 valueLenP);
_WISIMP Err FileDelete (UInt16 cardNo, Char *nameP);
//_WISIMP Int32 FileDmRead (FileHand stream, void *startofDmChunkP,
//						Int32 deskOffset, Int32 objSize, Int32 numObj,
//						Err *errP);
_WISIMP Err FileEOF (FileHand stream);
//_WISIMP Err FileError (FileHand stream);
_WISIMP Err FileFlush (FileHand stream);
//_WISIMP Err FileGetLastError (FileHand stream);
_WISIMP FileHand FileOpen (UInt16 cardNo, Char *nameP, UInt32 type,
								  UInt32 creator, UInt32 openMode, Err *errP);
_WISIMP Int32 FileRead (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);
_WISIMP Err FileRewind (FileHand stream);
//_WISIMP Err FileSeek (FileHand stream, Int32 offset, FileOriginEnum origin);
_WISIMP Err FileSeek (FileHand stream, Int32 offset, UInt16 origin);
_WISIMP Int32 FileTell (FileHand stream, Int32 *fileSizeP, Err *errP);
//_WISIMP Err FileTruncate (FileHand stream, Int32 newSize);
_WISIMP Int32 FileWrite (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);



////////////////////////////////////////////////////////////
// Find Processing Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Float Manager Library, completed 0/12 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Font Processing Library, completed 10/18 functions now.
////////////////////////////////////////////////////////////
_WISIMP Int16 FntAverageCharWidth (void);
_WISIMP Int16 FntCharHeight (void);
_WISIMP void FntCharsInWidth (Char const *string, Int16 *stringWidthP,
										Int16 *stringLengthP, Boolean *fitWithinWidth);
_WISIMP Int16 FntCharsWidth (const Char *chars, Int16 len);
_WISIMP Int16 FntCharWidth (Char ch);
_WISIMP FontID FntGetFont (void);
_WISIMP Int16 FntLineHeight (void);
_WISIMP Int16 FntLineWidth (Char const *pChar, UInt16 length);
_WISIMP FontID FntSetFont (FontID font);
_WISIMP UInt16 FntWordWrap (const Char *chars, UInt16 maxWidth);



////////////////////////////////////////////////////////////
// Form Processing Library, completed 57/66 functions now.
////////////////////////////////////////////////////////////
_WISIMP UInt16 FrmAlert (UInt16 alertID);
_WISIMP void FrmCloseAllForms (void);
_WISIMP void FrmCopyLabel(FormType *formp, UInt16 labelID, char *newLabel);
_WISIMP void FrmCopyTitle (FormType *formP, const Char *newTitle);
_WISIMP UInt16 FrmCustomAlert (UInt16 alertID, const Char *s1, const Char *s2, const Char *s3);
//_WISIMP UInt16 FrmCustomResponseAlert (UInt16 alertID, const Char *s1, const Char *s2,
//							   const Char *s3, Char *entryStringBuf,
//							   UInt16 entryStringBufLength, FormCheckResponseFuncPtr callback);
_WISIMP void FrmDeleteForm (FormType *formP);
_WISIMP Boolean FrmDispatchEvent(EventType *eventP);
_WISIMP UInt16 FrmDoDialog (FormType *formP);
_WISIMP void FrmDrawForm(FormType *form);
_WISIMP void FrmEraseForm (FormType *form);
_WISIMP FormType *FrmGetActiveForm ();
_WISIMP UInt16 FrmGetActiveFormID (void);
//_WISIMP UInt16 FrmGetControlGroupSelection (FormType *formp, UInt8 groupNum);
_WISIMP Int16 FrmGetControlValue (const FormType *formP, UInt16 controlID);
_WISIMP FormType *FrmGetFirstForm (void);
_WISIMP UInt16 FrmGetFocus (const FormType *formp);
_WISIMP void FrmGetFormBounds (const FormType *formP, RectangleType *rP);
_WISIMP UInt16 FrmGetFormId (FormType *formP);
_WISIMP FormType *FrmGetFormPtr (UInt16 formId);
_WISIMP void *FrmGetGadgetData (const FormType *formP, UInt16 objIndex);
_WISIMP const Char *FrmGetLabel (FormType *formP, UInt16 labelID);
_WISIMP UInt16 FrmGetNumberOfObjects (const FormType *formP);
_WISIMP void FrmGetObjectBounds (const FormType *formP, UInt16 ObjIndex, RectangleType *rP);
_WISIMP UInt16 FrmGetObjectId (const FormType *formP, UInt16 objIndex);
_WISIMP UInt16 FrmGetObjectIndex(const FormType *formp, UInt16 id);
_WISIMP void FrmGetObjectPosition (const FormType *formP, UInt16 objIndex, Coord *x, Coord *y);
_WISIMP void *FrmGetObjectPtr (const FormType *formP, UInt16 objIndex);
_WISIMP FormObjectKind FrmGetObjectType (const FormType *formP, UInt16 objIndex);
_WISIMP const Char *FrmGetTitle (const FormType *formP);
_WISIMP WinHandle FrmGetWindowHandle (const FormType *formP);
_WISIMP void FrmGotoForm (UInt16 fIndex);
_WISIMP Boolean FrmHandleEvent (FormType *formP, EventType *eventP);
_WISIMP void FrmHelp (UInt16 helpMsgId);
_WISIMP void FrmHideObject(FormType *formp, UInt16 objIndex);
_WISIMP FormType *FrmInitForm(UInt16 formID);
//_WISIMP FormBitmapType *FrmNewBitmap (FormType **formPP, UInt16 ID, UItn16 rscID, Coord x, Coord y);
_WISIMP FormType *FrmNewForm (UInt16 formID, const Char *titleStrP, Coord x, Coord y,
							 Coord width, Coord height, Boolean modal, UInt16 defaultButton,
							 UInt16 helpRscID, UInt16 menuRscID);
//_WISIMP FromGadgetType *FrmNewGadget (FormType **formPP, UInt16 id, Coord x, Coord y,
//										Coord width, Coord height);
//_WISIMP FrmGraffitiStateType *FrmNewGsi (FromType **formPP, Coord x, Coord y);
_WISIMP FormLabelType *FrmNewLabel (FormType **formPP, UInt16 ID, const Char *textP, Coord x, Coord y, FontID font);
_WISIMP Boolean FrmPointInTitle (const FormType *formP, Coord x, Coord y);
_WISIMP void FrmPopupForm (UInt16 fIndex);
_WISIMP Err FrmRemoveObject (FormType **formPP, UInt16 objIndex);
_WISIMP Boolean FrmRestoreActiveState (FormActiveStateType stateP);
_WISIMP void FrmReturnToForm (UInt16 fIndex);
_WISIMP Boolean FrmSaveActiveState (FormActiveStateType stateP);
_WISIMP void FrmSaveAllForms (void);
_WISIMP void FrmSetActiveForm(FormType *formP);
_WISIMP void FrmSetCategoryLabel (FormType *formP, UInt16 objIndex, Char *newLabel);
_WISIMP void FrmSetControlGroupSelection (const FormType *formP, UInt8 groupNum, UInt16 controlID);
_WISIMP void FrmSetControlValue (FormType *formP, UInt16 objIndex, Int16 newValue);
_WISIMP void FrmSetEventHandler(FormType *form, FormEventHandlerType *handler);
_WISIMP void FrmSetFocus(FormType *form, UInt16 fieldIndex);
//_WISIMP void FrmSetGadgetData (FormType *formP, UInt16 objIndex, const void *data);
//_WISIMP void FrmSetGadgetHandler (FormType *formP, UInt16 objIndex, FormGadgetHandlerType *attrP);
_WISIMP void FrmSetMenu (FormType *formP, UInt16 menuRscID);
_WISIMP void FrmSetObjectBounds (FormType *formP, UInt16 objIndex, const RectangleType *bounds);
_WISIMP void FrmSetObjectPosition (FormType *formP, UInt16 objIndex, Coord x, Coord y);
_WISIMP void FrmSetTitle (FormType *formP, Char *newTitle);
_WISIMP void FrmShowObject (FormType *formP, UInt16 objIndex);
//_WISIMP void FrmUpdateForm (UInt16 formId, UInt16 updateCode);
//_WISIMP void FrmUpdateScrollers (FormType *formP, UInt16 upIndex, UInt16 downIndex,
//								 Boolean scrollableUp, Boolean scrollableDown);
_WISIMP Boolean FrmValidatePtr (const FormType *formP);
_WISIMP Boolean FrmVisible (const FormType *formP);



////////////////////////////////////////////////////////////
// Graffiti Manager Library, completed 9/19 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err GrfAddPoint (PointType *pt);
_WISIMP Err GrfCleanState (void);
_WISIMP Err GrfFlushPoints (void);
_WISIMP Err GrfGetNumPoints (UInt16 *numPtsP);
_WISIMP Err GrfGetPoint (UInt16 index, PointType *pointP);
_WISIMP Err GrfGetState (Boolean *capsLockP, Boolean *numLockP, 
								UInt16 *tempShiftP, Boolean *autoShiftedP);
_WISIMP Err GrfInitState (void);
_WISIMP Err GrfProcessStroke (PointType *startPtP, PointType *endPtP, Boolean upShift);
_WISIMP Err GrfSetState (Boolean capsLock, Boolean numLock, Boolean upperShift);


//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.
//////////////////////////////////////////////////////////////////
_WISIMP void GsiEnable (const Boolean enableIt);
_WISIMP Boolean GsiEnabled (void);
_WISIMP void GsiInitialize (void);
_WISIMP void GsiSetLocation (const Int16 x, const Int16 y);
_WISIMP void GsiSetShiftState (const UInt16 lockFlags, const UInt16 tempShift);



////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
_WISIMP void InsPtEnable (Boolean enableIt);
_WISIMP Boolean InsPtEnabled (void);
_WISIMP Int16 InsPtGetHeight (void);
_WISIMP void InsPtGetLocation (Int16 *x, Int16 *y);
_WISIMP void InsPtSetHeight (const Int16 height);
_WISIMP void InsPtSetLocation (const Int16 x, const Int16 y);


////////////////////////////////////////////////////////////
// Key Manager Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// IR Library, completed 0/22 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// IAS Library, completed 0/14 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// List Handle Library, completed 16/17 functions now.
////////////////////////////////////////////////////////////
_WISIMP void LstDrawList (ListType *listP);
_WISIMP void LstEraseList (ListType *listP);
_WISIMP Int16 LstGetNumberOfItems (const ListType *listP);
_WISIMP Int16 LstGetSelection (ListType *listP);
_WISIMP Char *LstGetSelectionText (const ListType *listP, Int16 itemNum);
_WISIMP Int16 LstGetVisibleItems (const ListType *listP);
//_WISIMP Boolean LstHandleEvent (ListType *listP, const EventType *eventP);
_WISIMP void LstMakeItemVisible (ListType *listP, Int16 itemNum);
_WISIMP Err LstNewList (void **formPP, UInt16 id, Coord x, Coord y,
						 Coord width, Coord height, FontID font,
						 Int16 visibleItems, Int16 triggerID);
_WISIMP Int16 LstPopupList (ListType *listP);
_WISIMP Boolean LstScrollList (ListType *listp, WinDrectionType direction,
								Int16 itemCount);
_WISIMP void LstSetDrawFunction (ListType *listP, ListDrawDataFuncPtr func);
_WISIMP void LstSetHeight (ListType *listP, Int16 visibleItems);
_WISIMP void LstSetListChoices (ListType *listP, Char **itemsText, UInt16 numItems);
_WISIMP void LstSetPosition (ListType *listP, Coord x, Coord y);
_WISIMP void LstSetSelection (ListType *listP, Int16 itemNum);
_WISIMP void LstSetTopItem (ListType *listP, Int16 itemNum);



////////////////////////////////////////////////////////////
// Memory Manager Library, completed 24/44 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err MemCardInfo (UInt16 cardNo, Char *cardNameP, Char *manufNameP,
					  UInt16 *versionP, UInt32 *crDateP, UInt32 *romSizeP,
					  UInt32 *ramSizeP, UInt32 *freeBytesP);
_WISIMP Int16 MemCmp(const void *str1, const void *str2, Int32 numBytes);
_WISIMP UInt16 MemDebugMode (void);
_WISIMP UInt16 MemHandleCardNo (MemHandle h);
//_WISIMP Boolean MemHandleDataStorage (MemHandle h);
_WISIMP Err MemHandleFree (MemHandle h);
//_WISIMP UInt16 MemHandleHeapID (MemHandle h);
_WISIMP MemPtr MemHandleLock (MemHandle h);
_WISIMP MemHandle MemHandleNew (UInt32 size);
_WISIMP Err MemHandleResize (MemHandle h, UInt32 newSize);
_WISIMP Err MemHandleSetOwner (MemHandle h, UInt16 owner);
_WISIMP UInt32 MemHandleSize (MemHandle h);
_WISIMP LocalID MemHandleToLocalID (MemHandle h);
_WISIMP Err MemHandleUnlock (MemHandle h);
//_WISIMP Err MemHeapCheck (UInt16 heapID);
//_WISIMP Err MemHeapCompact (UInt16 heapID);
//_WISIMP Boolean MemHeapDynamic (UInt16 heapID);
//_WISIMP UInt16 MemHeapFlags (UInt16 heapID);
//_WISIMP Err MemHeapFreeBytes (UInt16 heapID, UInt32 *freeP, UInt32 maxP);
//_WISIMP UInt16 MemHeapID (UInt16 cardNo, UInt16 heapIndex);
//_WISIMP Err MemHeapScramble (UInt16 heapID);
//_WISIMP UInt32 MemHeapSize (UInt16 heapID);
//_WISIMP LocalIDKind MemLocalIDKind (LocalID local);
//_WISIMP MemPtr MemLocaIDToGlobal (LocalID local, UInt16 cardNo);
_WISIMP MemPtr MemLocalIDToLockedPtr (LocalID local, UInt16 cardNo);
//_WISIMP MemPtr MemLocalIDToPtr (LovalID local, UInt16 cardNo);
_WISIMP Err MemMove (VoidPtr dstP, VoidPtr srcP, Int32 numBytes);
_WISIMP UInt16 MemNumCards (void);
_WISIMP UInt16 MemNumHeaps (UInt16 cardNo);
_WISIMP UInt16 MemNumRAMHeaps (UInt16 cardNo);
//_WISIMP UInt16 MemPtrCardNo (MemPtr p);
//_WISIMP Boolean MemPtrDataStorage (MemPtr p);
_WISIMP Err MemPtrFree(MemPtr p);
//_WISIMP UInt16 MemPtrHeapID (MemPtr p);
_WISIMP MemPtr MemPtrNew(UInt32 size);
//_WISIMP MemHandle MemPtrRecoverHandle (MemPtr p);
_WISIMP Err MemPtrResize (MemPtr p, UInt32 newSize);
//_WISIMP Err MemPtrSetOwner (MemPtr p, UInt16 owner);
_WISIMP UInt32 MemPtrSize (MemPtr p);
//_WISIMP LocalID MemPtrToLocalID (MemPtr p);
_WISIMP Err MemPtrUnlock (MemPtr p);
_WISIMP Err MemSet(void *dstP, UInt32 numBytes, UInt8 value);
_WISIMP Err MemSetDebugMode (UInt16 flags);
// _WISIMP Err MemStoreInfo (UInt16 cardNo, UInt16 storeNumber, UInt16 *versionP,
//						UInt16 *flagsP, Char *nameP, UInt32 *crDateP,
//						UInt32 *bckUpDateP, UInt32 *heapListOffsetP,
//						UInt32 *initCodeOffset1P, UInt32 *initCodeOffset2P,
//						LocalID *databaseDirIDP);



////////////////////////////////////////////////////////////
// Menu Processing Library, completed 10/14 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err MenuAddItem (UInt16 positionID, UInt16 id, Char cmd, const Char *textP);
//Err MenuCmdBarAddButton (UInt8 where, UInt16 bitmapID, MenuCmdBarResultType resultType, 
//						 UInt32 result, Char *nameP);
//void MenuCmdBarDisplay (void);
//Boolean MenuCmdBarGetButtonData (Int16 buttonIndex, UInt16 *bitmapIdP, 
//								 MenuCmdBarResultType *resultTypeP,
//								 UInt32 *resultP, Char *nameP);
_WISIMP void MenuDispose (MenuBarType *menuP);
_WISIMP void MenuDrawMenu (MenuBarType *menuP);
_WISIMP void MenuEraseStatus (MenuBarType *menuP);
_WISIMP MenuBarType *MenuGetActiveMenu (void);
_WISIMP Boolean MenuHandleEvent(MenuBarType *menuP, EventType *event, UInt16 *error) ;
_WISIMP Boolean MenuHideItem (UInt16 id);
_WISIMP MenuBarType *MenuInit (UInt16 resourceID);
_WISIMP MenuBarType *MenuSetActiveMenu (MenuBarType *menuP);
//_WISIMP void MenuSetActiveMenuRscID (UInt16 resouceID);
_WISIMP Boolean MenuShowItem (UInt16 id);



////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Modem Manager Library, completed 0/2 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Net Library, completed 8/43 functions now.
////////////////////////////////////////////////////////////
_WISIMP NetIPAddr NetLibAddrAToIN (UInt16 libRefNum, Char *a);
_WISIMP Char *NetLibAddrINToA (UInt16 libRefNum, NetIPAddr inet, Char *spaceP);
_WISIMP Err NetLibClose (UInt16 libRefnum, UInt16 immediate);
_WISIMP NetHostInfoPtr NetLibGetHostByName (UInt16 libRefNum, Char *nameP,
											NetHostInfoBufPtr bufP, Int32 timeout, Err *errP);
_WISIMP Err NetLibOpen (UInt16 libRefnum, UInt16 *netIFErrP);
_WISIMP Int16 NetLibSocketClose (UInt16 libRefNum, NetSocketRef socket,
											Int32 timeout, Err* errP);
_WISIMP Int16 NetLibSocketConnect (UInt16 libRefNum, NetSocketRef socket,
											  NetSocketAddrType *sockAddrP, Int16 addrLen,
											  Int32 timeout, Err *errP);
_WISIMP NetSocketRef NetLibSocketOpen (UInt16 libREfNum, NetSocketAddrEnum domain,
											NetSocketTypeEnum type, Int16 protocol, 
											Int32 timeout, Err *errP);



////////////////////////////////////////////////////////////
// Network Utilities Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 0/21 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Notification Manager Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 0/7 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
_WISIMP Boolean PwdExists ();
_WISIMP void PwdRemove (void);
_WISIMP void PwdSet (Char *oldPassword, Char *newPassword);
_WISIMP Boolean PwdVerify (Char *string);


////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err PenCalibrate (PointType *digTopLeftP, PointType *digBotRightP,
						PointType *scrTopLeftP, PointType *scrBotRightP);
_WISIMP Err PenResetCalibrate (void);



////////////////////////////////////////////////////////////
// Preferences Library, completed 8/9 functions now.
////////////////////////////////////////////////////////////
_WISIMP Int16 PrefGetAppPreferences (UInt32 creator, UInt16 id, void *prefs,
									  UInt16 *prefsSize, Boolean saved);
_WISIMP Boolean PrefGetAppPreferencesV10 (UInt32 type, Int16 version, 
														void *prefs, UInt16 prefsSize);
_WISIMP UInt32 PrefGetPreference (SystemPreferencesChoice choice);
_WISIMP void PrefGetPreferences (SystemPreferencesPtr p);
_WISIMP void PrefSetAppPreferences (UInt32 creator, UInt16 id, UInt16 version,
											  void *prefs, UInt16 prefsSize, Boolean saved);
_WISIMP void PrefSetAppPreferencesV10 (UInt32 creator, Int16 version, 
											void *prefs, UInt16 prefsSize);
_WISIMP void PrefSetPreference (SystemPreferencesChoice choice, UInt32 value);
_WISIMP void PrefSetPreferences (SystemPreferencesPtr p);



///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 0/2 functions now.
///////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Progress Manager Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Rectangle Library, completed 2/6 functions now.
////////////////////////////////////////////////////////////
_WISIMP Boolean RctPtInRectangle (Coord x, Coord y, const RectangleType *rP);
_WISIMP void RctSetRectangle (RectangleType *P, Coord left, Coord top, Coord width, Coord height);


#define     PenGetPoint(a,b,c)    EvtGetPen(a,b,c)



////////////////////////////////////////////////////////////
// Script Plugin Library, completed 0/1 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 3/4 functions now.
////////////////////////////////////////////////////////////
_WISIMP void SclDrawScrollBar (const ScrollBarPtr bar);
_WISIMP void SclGetScrollBar (const ScrollBarPtr bar, Int16 *valueP,
										Int16 *minP, Int16 *maxP, Int16 *pageSizeP);
_WISIMP void SclSetScrollBar (const ScrollBarPtr bar, Int16 value,
										const Int16 minP, const Int16 maxP, 
										const Int16 pageSizeP);



////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 0/8 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 0/10 functions now.
////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////
// Serial Manager Library, completed 8/15 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err SerClose (UInt16 refNum);
_WISIMP UInt16 SerGetStatus (UInt16 refNum, Boolean *ctsOnP, Boolean *dsrOnP);
_WISIMP Err SerOpen (UInt16 refNum, UInt16 port, UInt32 baud);
_WISIMP UInt32 SerReceive (UInt16 refNum, void *bufP, UInt32 count,
								  Int32 timeout, Err *errP);
_WISIMP Err SerReceiveCheck (UInt16 refNum, UInt32 *numBytesP);
_WISIMP void SerReceiveFlush (UInt16 refNum, Int32 timeout);
_WISIMP UInt32 SerSend (UInt16 refNum, void *bufP, UInt32 count, Err *errP);
_WISIMP Err SerSendFlush (UInt16 refNum);



////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Sound Manager Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Standard IO Library, completed 0/5 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// String Manager Library, completed 13/19 functions now.
////////////////////////////////////////////////////////////
_WISIMP Int32 StrAToI(const Char *str);
//_WISIMP Int16 StrCaselessCompare (const Char *s1, const Char *s2);
_WISIMP Char* StrCat (Char *dst, const Char* src);
_WISIMP Char* StrChr (const Char *str, WChar chr);
_WISIMP Int16 StrCompare (const Char *dst, const Char* src);
_WISIMP Char* StrCopy (Char *dst, const Char* src);
//_WISIMP Char* StrDelocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator);
_WISIMP Char* StrIToA(Char *s, Int32 i);
_WISIMP Char* StrIToH(Char *s, Int32 i);
_WISIMP UInt16 StrLen (const Char* src);
//_WISIMP Char* StrLocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator);
//_WISIMP Int16 StrNCaselessCompare (const Char *s1, const Char *s2, Int32 n);
_WISIMP Char* StrNCat (Char *dst, const Char* src, Int16 n);
_WISIMP Int16 StrNCompare (const Char *dst, const Char* src, UInt32 n);
_WISIMP Char* StrNCopy (Char *dst, const Char* src, Int16 n);
//_WISIMP Int16 StrPrintF (Char* s, const Char *formatStr, ...);
_WISIMP Char *StrStr (const Char *str, const Char *token);
_WISIMP Char* StrToLower (Char *dst, const Char* src);
_WISIMP Int16 StrVPrintF (Char* s, const Char *formatStr, VoidPtr argParam);



////////////////////////////////////////////////////////////
// System Dialogs Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 4/25 functions now.
//////////////////////////////////////////////////////////////
_WISIMP void EvtAddEventToQueue (const EventType *event);
_WISIMP void EvtGetEvent(EventType *event, Int32 timeout);
_WISIMP Boolean SysHandleEvent(EventType *event);
_WISIMP void EvtGetPen (Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown);



////////////////////////////////////////////////////////////
// System Manager Library, completed 13/33 functions now.
////////////////////////////////////////////////////////////
_WISIMP Err SysAppLaunch (UInt16 cardNo, LocalID dbID, UInt16 launchFlags,
								  UInt16 cmd, MemPtr cmdPBP, UInt32 *resultP);
_WISIMP UInt16 SysBatteryInfo (Boolean set, UInt16 *warnThresholdP,
										 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
										 SysBatteryKind *kindP, Boolean *pluggedIn, 
										 UInt8 *percentP);
_WISIMP UInt16 SysBatteryInfoV20 (Boolean set, UInt16 *warnThresholdP,
										 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
										 SysBatteryKind *kindP, Boolean *pluggedIn);
_WISIMP Boolean SysCreatePanelList (UInt16 *panelCount, MemHandle *panelIDs);
_WISIMP Err SysCurAppDatabase (UInt16 *cardNoP, LocalID *dbIDP);
_WISIMP Char *SysGetOSVersionString ();
_WISIMP void SysKeyboardDialog (KeyboardType kbd);
_WISIMP void SysKeyboardDialogV10 ();
_WISIMP Err SysLibFind (const Char* nameP, UInt16 *refNumP);
_WISIMP Int16 SysRandom (UInt32 newSeed);
_WISIMP Err SysTaskDelay (Int32 delay);
_WISIMP UInt16 SysTicksPerSecond (void);
_WISIMP Err SysUIAppSwitch (UInt16 cardNo, LocalID dbID, UInt16 cmd, 
									 MemPtr cmdPBP);



////////////////////////////////////////////////////////////
// Table Library, completed 47/58 functions now.
////////////////////////////////////////////////////////////
_WISIMP void TblDrawTable (TableType *tableP);
_WISIMP Boolean TblEditing (const TableType *tableP);
_WISIMP void TblEraseTable (TableType *tableP);
//_WISIMP Boolean TblFindRowData (const TableType *tableP, UInt32 data, Int16 *rowP);
_WISIMP Int16 TblFindRowID (const TableType *tableP, UInt16 id, Int16 *rowP);
_WISIMP void TblGetBounds (const TableType *tableP, RectangleType *r);
_WISIMP Int16 TblGetColumnSpacing (const TableType *tableP, Int16 column);
_WISIMP Int16 TblGetColumnWidth (const TableType *tableP, Int16 column);
_WISIMP FieldPtr TblGetCurrentField (const TableType *tableP);
//_WISIMP void TblGetItemBounds (const TableType *tableP, Int16 row, Int16 column, RectangleType *r);
_WISIMP FontID TblGetItemFont (const TableType *tableP, Int16 row, Int16 column);
_WISIMP Int16 TblGetItemInt (const TableType *tableP, Int16 row, Int16 column);
_WISIMP void *TblGetItemPtr (const TableType *tableP, Int16 row, Int16 column);
_WISIMP Int16 TblGetLastUsableRow (const TableType *tableP);
_WISIMP Int16 TblGetNumberOfRows (const TableType *tableP);
_WISIMP UInt32 TblGetRowData (const TableType *tableP, Int16 row);
_WISIMP Coord TblGetRowHeight (const TableType *tableP, Int16 row);
_WISIMP UInt16 TblGetRowID (const TableType *tableP, Int16 row);
_WISIMP Boolean TblGetSelection (const TableType *tableP, Int16 *rowP, Int16 *columnP);
_WISIMP void TblGrabFocus (TableType *tableP, Int16 row, Int16 column);
//_WISIMP Boolean TblHandleEvent (TableType *tableP, EventType *event);
_WISIMP void TblHasScrollBar (TableType *tableP, Boolean hasScrollBar);
//_WISIMP void TblInsertRow (TableType *tableP, Int16 row);
_WISIMP void TblMarkRowInvalid (const TableType *tableP, Int16 row);
_WISIMP void TblMarkTableInvalid (const TableType *tableP);
//_WISIMP void TblRedrawTable (TableType *tableP);
//_WISIMP void TblReleaseFocus (TableType *tableP);
//_WISIMP void TblRemoveRow (const TableType *tableP, Int16 row);
_WISIMP void TblReverseItem (TableType *tableP, Int16 row, Int16 column);
_WISIMP Boolean TblRowInvalid (const TableType *tableP, Int16 row);
_WISIMP Boolean TblRowMasked (const TableType *tableP, Int16 row);
_WISIMP Boolean TblRowSelectable (const TableType *tableP, Int16 row);
_WISIMP Boolean TblRowUsable (TableType *tableP, Int16 row);
_WISIMP void TblSelectItem (TableType *tableP, Int16 row, Int16 column);
_WISIMP void TblSetBounds (TableType *tableP, const RectangleType *rP);
_WISIMP void TblSetColumnEditIndicator (TableType *tableP, Int16 column, Boolean editIndicator);
_WISIMP void TblSetColumnMasked (TableType *tableP, Int16 column, Boolean masked);
_WISIMP void TblSetColumnSpacing (TableType *tableP, Int16 column, Coord spacing);
_WISIMP void TblSetColumnUsable (TableType *tableP, Int16 column, Boolean usable);
_WISIMP void TblSetColumnWidth (TableType *tableP, Int16 column, Coord width);
_WISIMP void TblSetCustomDrawProcedure (TableType *tableP, Int16 column, TableDrawItemFuncPtr drawCallback);
_WISIMP void TblSetItemFont (const TableType *tableP, Int16 row, Int16 column, FontID fontID);
_WISIMP void TblSetItemInt (TableType *tableP, Int16 row, Int16 column, Int16 value);
_WISIMP void TblSetItemPtr (TableType *tableP, Int16 row, Int16 column, void *value);
_WISIMP void TblSetItemStyle (TableType *tableP, Int16 row, Int16 column, TableItemStyleType type);
_WISIMP void TblSetLoadDataProcedure (TableType *tableP, Int16 column, TableLoadDataFuncPtr loadDataCallback);
_WISIMP void TblSetRowData (TableType *tableP, Int16 row, UInt32 data);
_WISIMP void TblSetRowHeight (TableType *tableP, Int16 row, Coord height);
_WISIMP void TblSetRowID (TableType *tableP, Int16 row, UInt16 id);
_WISIMP void TblSetRowMasked (TableType *tableP, Int16 row, Boolean masked);
_WISIMP void TblSetRowSelectable (TableType *tableP, Int16 row, Boolean selectable);
_WISIMP void TblSetRowStaticHeight (TableType *tableP, Int16 row, Boolean staticHeight);
_WISIMP void TblSetRowUsable (TableType *tableP, Int16 row, Boolean usable);
_WISIMP void TblSetSaveDataProcedure (TableType *tableP, Int16 column, TableSaveDataFuncPtr saveDataCallback);
//_WISIMP void TblUnhighlightSelection (TableType *tableP);
//_WISIMP void TableDrawItemFuncType (void *tableP, Int16 row, Int16 column, RectangleType *bounds);
//_WISIMP Err TableLoadDataFuncType (void *tableP, Int16 row, Int16 column, Boolan editable,
//								  MemHandle *dataH, Int16 *dataOffset, Int16 *dataSize, 
//								  FieldPtr fld);
//_WISIMP Boolean TableSaveDataFuncType (void *tableP, Int16 row, Int16 column);



////////////////////////////////////////////////////////////
// Text Manager Library, completed 12/38 functions now.
////////////////////////////////////////////////////////////
_WISIMP Boolean TxtCharIsAlNum (Char ch);
_WISIMP Boolean TxtCharIsAlpha (Char ch);
_WISIMP Boolean TxtCharIsCntrl (Char ch);
_WISIMP Boolean TxtCharIsDelim (Char ch);
_WISIMP Boolean TxtCharIsDigit (Char ch);
_WISIMP Boolean TxtCharIsGraph (Char ch);
_WISIMP Boolean TxtCharIsHex (Char ch);
_WISIMP Boolean TxtCharIsLower (Char ch);
_WISIMP Boolean TxtCharIsPrint (Char ch);
_WISIMP Boolean TxtCharIsSpace (Char ch);
_WISIMP Boolean TxtCharIsUpper (Char ch);
_WISIMP UInt16	TxtCharSize (WChar inChar);


////////////////////////////////////////////////////////////
// Time Manager Library, completed 16/17 functions now.
////////////////////////////////////////////////////////////
_WISIMP void DateAdjust (DatePtr dateP, Int32 adjustment);
_WISIMP void DateDaysToDate (UInt32 days, DatePtr Date);
_WISIMP void DateSecondsToDate (UInt32 seconds, DatePtr date);
//_WISIMP void DateTemplateToAscii (const Char *templateP, UInt8 months,
//											UInt8 days, UInt16 years, Char *stringP,
//											Int16 stringLen);
_WISIMP void DateToAscii (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString);
_WISIMP UInt32 DateToDays (DateType date);
_WISIMP void DateToDOWDMFormat (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString);
_WISIMP Int16 DayOfMonth (Int16 month, Int16 day, Int16 year);
_WISIMP Int16 DayOfWeek (Int16 month, Int16 day, Int16 year);
_WISIMP Int16 DaysInMonth (Int16 month, Int16 year);
_WISIMP void TimeAdjust (DateTimePtr datetimeP, Int32 adjustment);
_WISIMP UInt32 TimDateTimeToSeconds (DateTimePtr dateTimeP);
_WISIMP UInt32 TimGetSeconds (void);
_WISIMP UInt32 TimGetTicks (void);
_WISIMP void TimSecondsToDateTime (UInt32 seconds, DateTimePtr dateTimeP);
_WISIMP void TimSetSeconds (UInt32 seconds);
_WISIMP void TimeToAscii (UInt8 hours, UInt8 minutes, 
								 TimeFormatType timeFomrat, Char *pString);



////////////////////////////////////////////////////////////
// UI Color List Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// UI Controls Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// User Interface Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Window function, completed 31/80 functions now.
////////////////////////////////////////////////////////////
_WISIMP void WinDrawBitmap (BitmapPtr bitmapP, Coord x, Coord y);
_WISIMP void WinDrawChar (WChar theChar, Coord x, Coord y);
_WISIMP void WinDrawChars (const Char *chars, Int16 len, Coord x, Coord y);
_WISIMP void WinDrawGrayLine (Coord x1, Coord y1, Coord x2, Coord y2);
_WISIMP void WinDrawGrayRectangleFrame (FrameType frame, RectangleType *rP);
_WISIMP void WinDrawInvertedChars (const Char *chars, Int16 len, Coord x, Coord y);
_WISIMP void WinDrawLine (Coord x1, Coord y1, Coord x2, Coord y2);
_WISIMP void WinDrawPixel (Coord x, Coord y);
_WISIMP void WinDrawRectangle (RectangleType *rP, UInt16 cornerDiam);
_WISIMP void WinDrawRectangleFrame (FrameType frame, RectangleType *rP);
_WISIMP void WinDrawTruncChars (const Char *chars, Int16 len, Coord x, Coord y, Coord maxWidth);
_WISIMP void WinEraseChars (const Char *chars, Int16 len, Coord x, Coord y);
_WISIMP void WinEraseLine (Coord x1, Coord y1, Coord x2, Coord y2);
_WISIMP void WinErasePixel (Coord x, Coord y);
_WISIMP void WinEraseRectangle (RectangleType *rP, UInt16 corneDiam);
_WISIMP void WinEraseWindow (void);
_WISIMP void WinFillLine (Coord x1, Coord y1, Coord x2, Coord y2);
_WISIMP void WinFillRectangle (RectangleType *rP, UInt16 cornerDiam);
_WISIMP void WinGetClip (RectangleType *rP);
_WISIMP IndexedColorType WinGetPixel (Coord x, Coord y);
_WISIMP void WinInvertPixel (Coord x, Coord y);
_WISIMP void WinInvertRectangle (RectangleType *rP, UInt16 cornerDim);
_WISIMP void WinPaintPixel (Coord x, Coord y);
_WISIMP void WinPaintPixels (UInt16 numPoints, PointType pts[]);
_WISIMP void WinPaintRectangle (RectangleType *rP, UInt16 cornerDiam);
_WISIMP void WinPopDrawState ();
_WISIMP void WinPushDrawState ();
_WISIMP void WinResetClip(void);
_WISIMP IndexedColorType WinSetBackColor (IndexedColorType backColor);
_WISIMP void WinSetClip (RectangleType *rP);
_WISIMP IndexedColorType WinSetForeColor (IndexedColorType foreColor);

#endif // __APIDLL_H__
