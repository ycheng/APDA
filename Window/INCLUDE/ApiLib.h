/*========================================================
  Apilib.h
  This file list all current supported function 
  compitable with Palm OS.

  Current status completed 352 functions.
  Total List 381 functions.
  508 funtions not list below.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0507, 2001 by Jerry Chu
 =========================================================*/
#ifndef __APILIB_H__
#define __APILIB_H__



////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
extern UInt32 AlmGetAlarm (UInt16 cardNo, LocalID dbID, UInt32 *refP);
extern UInt32 AlmGetProcAlarm (AlmAlarmProcPtr procP, UInt32 refP);
extern Err AlmSetAlarm (UInt16 cardNo, LocalID dbID, UInt32 ref,
								UInt32 alarmSeconds, Boolean quiet);
extern Err AlmSetProcAlarm (AlmAlarmProcPtr proc, UInt32 ref, UInt32 alarmSeconds);


////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 0/9 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Category Library, completed 10/11 functions now.
////////////////////////////////////////////////////////////
extern void CategoryCreateList (DmOpenRef db, ListType *listP, UInt16 currentCategory,
						 Boolean showAll, Boolean showUneditables, 
						 UInt8 numUneditableCategories,
						 UInt32 editingStrID, Boolean resizeList);
//extern CategoryEdit (DmOpenRef db, UInt16 *categoryP, UInt32 titleStrID,
//					 UInt16 numUneditableCategories);
extern UInt16 CategoryFind (DmOpenRef db, char *name);
extern void CategoryFreeList (DmOpenRef db, const ListType *listP, 
							  Boolean showAll, UInt32 editingStrID);
extern void CategoryGetName (DmOpenRef db, UInt16 index, char *name);
extern UInt16 CategoryGetNext (DmOpenRef db, UInt16 index);
extern void CategoryInitialize (AppInfoPtr appInfoP, UInt16 localizedAppInfoStrID);
extern Boolean CategorySelect (DmOpenRef db, const FormType *frm, UInt16 ctlID,
					 UInt16 lstID, Boolean title, UInt16 *categoryP,
					 char *categoryName, UInt8 numUneditableCategories,
					 UInt32 editingStrID);
extern void CategorySetName (DmOpenRef db, UInt16 index, const char *name);
extern void CategorySetTriggerLabel (ControlType *ctl, Char *name);
extern void CategoryTruncateName (Char *name, UInt16 maxWidth);



////////////////////////////////////////////////////////////
// Character Attributes Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Clipboad functions, completed 0/3 functions now.
////////////////////////////////////////////////////////////
//extern void ClipboardAddItem (const ClipboardFormatType format, const void *ptr, UInt16 length);
//extern Err ClipboardAppendItem (const ClipboardFormatType format, const void *ptr, UInt16 length);
//extern MemHandle ClipboardGetItem (const ClipboardFormatType format, UInt16 *length);


////////////////////////////////////////////////////////////
// Connection Manager Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Control Handle Library, completed 18/19 functions now.
////////////////////////////////////////////////////////////
extern void CtlDrawControl (ControlType *controlP);
extern Boolean CtlEnabled (const ControlType *controlP);
extern void CtlEraseControl (ControlType *controlP);
extern const Char *CtlGetLabel (const ControlType *controlP);
extern void CtlGetSliderValues (const ControlType *ctlP, UInt16 *minValueP,
								  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP);
extern Int16 CtlGetValue (const ControlType *controlP);
//extern Boolean CtlHandleEvent (ControlType *controlP, EventType pEvent);
extern void CtlHideControl (ControlType *controlP);
extern void CtlHitControl (const ControlType *controlP);
extern ControlType *CtlNewControl (void **formPP, UInt16 ID, ControlStyleType style,
								   const Char *textP, Coord x, Coord y, Coord width,
								   Coord height, FontID font, UInt8 group, 
								   Boolean leftAnchor);
extern GraphicControlType *CtlNewGraphicControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID bitmapID, 
								   DmResID selectedBitmapID, Coord x, Coord y, 
								   Coord width, Coord height, UInt8 group, 
								   Boolean leftAnchor);
extern SliderControlType *CtlNewSliderControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID thumbID, 
								   DmResID backgroundID, Coord x, Coord y, 
								   Coord width, Coord height, UInt16 minValue,
								   UInt16 maxValue, UInt16 pageSize, UInt16 value);
extern void CtlSetEnabled (ControlType *controlP, Boolean enable);
extern void CtlSetLabel (ControlType *controlP, const Char *newLabel);
extern void CtlSetGraphics (ControlType *controlP, DmResID newBitmapID,
							  DmResID newSelectedBitmapID);
extern void *CtlSetSliderValue (ControlType *ctlP, const UInt16 *minValueP,
								  const UInt16 *maxValueP, const UInt16 *pageSizeP, 
								  const UInt16 *valueP);
extern void CtlSetUsable (ControlType *controlP, Boolean usable);
extern void CtlSetValue (ControlType *controlP, Int16 newValue);
extern Boolean CtlValidatePointer (const ControlType *controlP);



///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 0/6 functions now.
///////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// DataBase Library, completed 27/66 functions now.
////////////////////////////////////////////////////////////
//extern Err DmArchiveRecord (DmOpenRef dbP, UInt16 index);
extern Err			DmAttachRecord (DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP);
//extern Err			DmAttachResource (DmOpenRef dbP, MemHandle newH, DmResType resType, DmResID resID);
extern Err			DmCloseDatabase (DmOpenRef dbp);
extern Err			DmCreateDatabase (UInt16 cardNo, const Char *nameP, UInt32 creator,
					  UInt32 type, Boolean resDB);
//extern Err DmCreateDatabaseFromImage (MemPtr bufferP);
extern Err DmDatabaseInfo (UInt16 cardNo, LocalID dbID, Char *nameP, UInt16 *attributesP,
					UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP,
					UInt32 *typeP, UInt32 *creatorP);
//extern Err DmDatabaseProtect (UInt16 cardNo, LocalID dbID, Boolean protect);
extern Err DmDatabaseSize (UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP);
extern Err DmDeleteCategory (DmOpenRef dbp, UInt16 categoryNum);
//extern Err DmDeleteDatabase (UInt16 cardNo, LocalID dbID);
extern Err DmDeleteRecord (DmOpenRef dbp, UInt16 index);
//extern Err DmDetachRecord (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);
//extern Err DmDetachResource (DmOpenRef dbp, UInt16 index, MemHandle *oldHP);
//extern Err DmFindDatabase (UInt16 cardNo, const Char *nameP);
//extern Err DmFindRecordByID (DmOpenRef dbp, UInt32 uniqueID, UInt16 *indexP);
//extern Err DmFindResource (DmOpenRef dbp, DmResType resType, DmResID resID, memHandle resH);
//extern UInt16 DmFindResourceType (DmOpenRef dbp, DmResType resType, UInt16 typeIndex);
//extern UInt16 DmFindSortPosition (DmOpenRef dbp, void *newRecord, SortRecordInfoPtr newRecordInfo,
//						   DmComparF *compar, Int16 other);
//extern LocalID DmGetAppInfoID (DmOpenRef dbP);
//extern LocalID DmGetDatabase (UInt16 cardNo, UInt16 index);
//extern void DmGetDatabaseLocaState (DmOpenRef dbR, UInt8 *highest, UInt32 *count, UInt32 *busy);
//extern Err DmGetLastErr (void);
//extern Err DmGetNextDatabaseByTypeCreator (Boolan newSearch, DmSearchStatePtr stateInfoP, UInt32 type,
//									UInt32 creator, Boolean onlyLatesVers, UInt16 *cardNoP, LocalID *dbIDP);
extern MemHandle	DmGetRecord (DmOpenRef dbP, UInt16 index);
//extern MemHandle	DmGetResource (DmResType type, DmResID resID);
//extern MemHandle	DmGetResourceIndex (DmOpenRef dbP, UInt16 index);
//extern MemHandle	DmGet1Resource (DmResType type, DmResID resID);
extern Err			DmInsertionSort (DmOpenRef dbR, DmComparF *compar, Int16 other);
extern Err DmMoveCategory (DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty);
extern Err DmMoveRecord (DmOpenRef dbP, UInt16 from, UInt16 to);
extern MemHandle	DmNewHandle (DmOpenRef dbP, UInt32 size);
extern MemHandle	DmNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
//extern MemHandle DmNewReresource (DmOpenRef dbP, DmResType resType, DmResID resID, UInt32 size);
//extern DmOpenRef DmNextOpenDatabase (DmOpenRef currentP);
//extern UInt16 DmNumDatabases (UInt16 cardNo);
extern UInt16		DmNumRecords (DmOpenRef dbP);
extern UInt16 DmNumRecordsInCategory (DmOpenRef dbP, UInt16 category);
//extern UInt16 DmNumResources (DmOpenRef dbP);
//extern DmOpenRef DmOpenDatabase (UInt32 cardNo, LocalID dbID, UInt16 mode);
extern DmOpenRef DmOpenDatabaseByTypeCreator (UInt32 type, UInt32 creator, UInt16 mode);
extern Err DmOpenDatabaseInfo (DmOpenRef dbP, LocalID *dbIDP, UInt16 *openCountP, UInt16 *modeP,
						UInt16 *cardNoP, Boolean *resDBP);
//extern DmOpenRef DmOpenDBNoOvelay (UInt32 cardNo, LocalID dbID, UInt16 mode);
extern UInt16 DmPositionInCategory (DmOpenRef dbP, UInt16 index, UInt16 category);
//extern MemHandle DmQueryNextInCategory (DmOpenRef dbP, UInt16 *indexP, UInt16 category);
extern MemHandle DmQueryRecord (DmOpenRef dbP, UInt16 index);
//extern Err DmQuickSort (DmOpenRef dbP, DmComparF *compar, Int16 other);
extern Err DmRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP, LocalID *chunkIDP);
extern Err DmReleaseRecord (DmOpenRef dbP, UInt16 index, Boolean dirty);
//extern Err DmReleaseResource (MemHandle resourceH);
extern Err DmRemoveRecord (DmOpenRef dbP, UInt16 index);
//extern Err DmRemoveResource (DmOpenRef dbP, UInt16 index);
//extern Err DmRemoveSecretRecord (DmOpenRef dbP);
extern MemHandle DmResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 newSize);
//extern Err DmResizeResource (MemHandle resourceH, UInt32 newSize);
//Err DmResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP,
//					LocalID *chunkLocalIDP);
extern Err			DmResetRecordStates(DmOpenRef dbP);
//extern UInt16 DmSearchRecord (MemHandle recH, DmOpenRef *dbPP);
//extern UInt16 DmSearchResource (DmResType resType, DmResID resID, MemHandle resH, DmOpenRef *dbPP);
extern Err DmSeekRecordInCategory (DmOpenRef dbP, UInt16 *indexP, Int16 offset,
							Int16 direction, UInt16 category);
extern Err DmSet (void *recordP, UInt32 offset, UInt32 bytes, UInt8 value);
extern Err DmSetDatabaseInfo (UInt16 cardNo, LocalID dbID, const Char *nameP, UInt16 *attributesP,
					   UInt16 *versionP, UInt32 *crDateP, UInt32 *modDateP, UInt32 *bckUpDateP,
					   UInt32 *modNumP, LocalID *appInfoIDP, LocalID *sortInfoIDP, UInt32 *typeP,
					   UInt32 *creatorP);
extern Err DmSetRecordInfo (DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP);
//extern Err DmSetResourceInfo (DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP);
//extern Err DmStrCopy (void *recordP, UInt32 offset, const Char *srcP);
extern Err			DmWrite (void *recordP, UInt32 offset, const void *srcP, UInt32 bytes);
//extern Err DmWriteCheck (void *recordP, UInt32 offset, UInt32 bytes);



////////////////////////////////////////////////////////////
// Error Manager Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 0/9 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Feature Manager Library, completed 0/7 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Field Processing Library, completed 32/52 functions now.
////////////////////////////////////////////////////////////
extern UInt16 FldCalcFieldHeight (const Char* chars, UInt16 maxWidth);
//extern void FldCompactText (FieldType *fldP);
extern void FldCopy (const FieldType *fldP);
extern void FldCut (FieldType *fldP);
extern void FldDelete (FieldType *fldP, UInt16 start, UInt16 end);
extern Boolean FldDirty (FieldType *fldP);
extern void FldDrawField (FieldType *fldP);
extern void FldEraseField (FieldType *fldP);
extern void FldFreeMemory (FieldType *fldP);
extern void FldGetAttributes (const FieldType *fldP, FieldAttrPtr attrP);
extern void FldGetBounds (const FieldType *fldP, RectangleType *rect);
extern FontID FldGetFont (const FieldType *fldP);
//extern UInt16 FldGetInsPtPosition (const FieldType *fldP);
extern UInt16 FldGetMaxChars (const FieldType *fldP);
extern UInt16 FldGetNumberOfBlankLines (const FieldType *fldP);
//extern UInt16 FldGetScrollPosition (const FieldType *fldP);
//extern void FldGetScrollValues (const FieldType *fldP, UInt16 *scrollPosP,
//								UInt16 *textHeightP, UInt16 *fieldHeghtP);
extern void FldGetSelection (const FieldType *fldP, UInt16 *startPosition,
								UInt16 *endPosition);
extern UInt16 FldGetTextAllocatedSize (const FieldType *fldP);
extern MemHandle FldGetTextHandle (const FieldType *fldP);
//extern UInt16 FldGetTextHeight (const FieldType *fldP);
extern UInt16 FldGetTextLength (const FieldType *fldP);
extern Char *FldGetTextPtr (FieldType *fldP);
//extern UInt16 FldGetVisibleLines (const FieldType *fldP);
extern void FldGrabFocus (FieldType *fldP);
//extern Boolean FldHandleEvent (const FieldType *fldP, EventType *eventP);
extern void FldInsert (FieldType *fldP, const Char* insertChars, UInt16 insertLen);
//extern Boolean FldMakeFullyVisible (FieldType *fldP);
extern FieldType *fldNewField (void **formPP, UInt16 id, Coord x, Coord y, Coord width,
						Coord heght, FontID font, UInt32 maxChars, Boolean editable,
						Boolean underlined, Boolean singleLine, Boolean dynamicSize,
						JustificationType justification, Boolean autoShift,
						Boolean hasScrollBar, Boolean numeric);
extern void FldPaste (FieldType *fldP);
//extern void FldRecalculateField (FieldType *fldP, Boolean redraw);
//extern void FldReleaseFocus (FieldType *fldP);
//extern Boolean FldScrollable (const FieldType *fldP, WinDirectionType direction); 
//extern void FldScrollField (FieldType *fldP, UInt16 linesToScroll, WinDirectionType direction); 
//extern void FldSendChangeNotification (const FieldType *fldP);
//extern void FldSendHeightChangeNotification (const FieldType *fldP, UInt16 pos, Int16 numLines);
extern void FldSetAttributes (FieldType *fldP, const FieldAttrType *attrP);
extern void FldSetBounds (FieldType *fldP, const RectangleType *rP);
extern void FldSetDirty (FieldType *fldP, Boolean dirty);
extern void FldSetFont (FieldType *fldP, FontID fontID);
//extern void FldSetInsertionPoint (FieldType *fldP, UInt16 pos);
//extern void FldSetInsPtPosition (FieldType *fldP, UInt16 pos);
extern void FldSetMaxChars (FieldType *fldP, UInt16 maxChars);
//extern void FldsetScrollPosition (FieldType *fldP);
extern void FldSetSelection (FieldType *fldP, UInt16 startPosition,
								UInt16 endPosition);
extern void FldSetText (FieldType *fldP, MemHandle textHandle, UInt16 offset,
						  UInt16 size);
extern void FldSetTextAllocatedSize (FieldType *fldP, UInt16 allocatedSize);
extern void FldSetTextHandle (FieldType *fldP, MemHandle textHandle);
extern void FldSetTextPtr (FieldType *fldP, Char *textP);
extern void FldSetUsable (FieldType *fldP, Boolean usable);
//extern void FldUndo (FieldType *fldP);
//extern UInt16 FldWordWrap (const Char *chars, Int16 maxWidth);



////////////////////////////////////////////////////////////
// File Streaming Library, completed 10/16 functions now.
////////////////////////////////////////////////////////////
//extern Err FileClearerr (FileHand stream);
extern Err FileClose (FileHand stream);
//extern Err FileControl (FileOpEnum op, FileHand stream, 
//					  void *valueP, Int32 valueLenP);
extern Err FileDelete (UInt16 cardNo, Char *nameP);
//extern Int32 FileDmRead (FileHand stream, void *startofDmChunkP,
//						Int32 deskOffset, Int32 objSize, Int32 numObj,
//						Err *errP);
extern Err FileEOF (FileHand stream);
//extern Err FileError (FileHand stream);
extern Err FileFlush (FileHand stream);
//extern Err FileGetLastError (FileHand stream);
extern FileHand FileOpen (UInt16 cardNo, Char *nameP, UInt32 type,
								  UInt32 creator, UInt32 openMode, Err *errP);
extern Int32 FileRead (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);
extern Err FileRewind (FileHand stream);
//extern Err FileSeek (FileHand stream, Int32 offset, FileOriginEnum origin);
extern Err FileSeek (FileHand stream, Int32 offset, UInt16 origin);
extern Int32 FileTell (FileHand stream, Int32 *fileSizeP, Err *errP);
//extern Err FileTruncate (FileHand stream, Int32 newSize);
extern Int32 FileWrite (FileHand stream, void *bufP, Int32 objSize,
					  Int32 numObj, Err *errP);



////////////////////////////////////////////////////////////
// Find Processing Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Float Manager Library, completed 0/12 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Font Processing Library, completed 5/18 functions now.
////////////////////////////////////////////////////////////
extern Int16 FntAverageCharWidth (void);
extern Int16 FntCharsWidth (const Char *chars, Int16 len);
extern Int16 FntCharWidth (Char ch);
extern FontID FntGetFont (void);
extern FontID FntSetFont (FontID font);



////////////////////////////////////////////////////////////
// Form Processing Library, completed 51/66 functions now.
////////////////////////////////////////////////////////////
//extern UInt16 FrmAlert (UInt16 alertID);
extern void FrmCloseAllForms (void);
extern void FrmCopyLabel(FormType *formp, UInt16 labelID, char *newLabel);
extern void FrmCopyTitle (FormType *formP, const Char *newTitle);
//extern UInt16 FrmCustomAlert (UInt16 alertID, const Char *s1, const Char *s2, const Char *s3);
//extern UInt16 FrmCustomResponseAlert (UInt16 alertID, const Char *s1, const Char *s2,
//							   const Char *s3, Char *entryStringBuf,
//							   UInt16 entryStringBufLength, FormCheckResponseFuncPtr callback);
extern void FrmDeleteForm (FormType *formP);
extern Boolean FrmDispatchEvent(EventType *eventP);
//extern UInt16 FrmDoDialog (FormType *formP);
extern void FrmDrawForm(FormType *form);
extern void FrmEraseForm (FormType *form);
extern FormType *FrmGetActiveForm ();
extern UInt16 FrmGetActiveFormID (void);
//extern UInt16 FrmGetControlGroupSelection (FormType *formp, UInt8 groupNum);
extern Int16 FrmGetControlValue (const FormType *formP, UInt16 controlID);
extern FormType *FrmGetFirstForm (void);
extern UInt16 FrmGetFocus (const FormType *formp);
extern void FrmGetFormBounds (const FormType *formP, RectangleType *rP);
extern UInt16 FrmGetFormId (FormType *formP);
extern FormType *FrmGetFormPtr (UInt16 formId);
extern void *FrmGetGadgetData (const FormType *formP, UInt16 objIndex);
extern const Char *FrmGetLabel (FormType *formP, UInt16 labelID);
extern UInt16 FrmGetNumberOfObjects (const FormType *formP);
extern void FrmGetObjectBounds (const FormType *formP, UInt16 ObjIndex, RectangleType *rP);
extern UInt16 FrmGetObjectId (const FormType *formP, UInt16 objIndex);
extern UInt16 FrmGetObjectIndex(const FormType *formp, UInt16 id);
extern void FrmGetObjectPosition (const FormType *formP, UInt16 objIndex, Coord *x, Coord *y);
extern void *FrmGetObjectPtr (const FormType *formP, UInt16 objIndex);
extern FormObjectKind FrmGetObjectType (const FormType *formP, UInt16 objIndex);
extern const Char *FrmGetTitle (const FormType *formP);
extern WinHandle FrmGetWindowHandle (const FormType *formP);
extern void FrmGotoForm (UInt16 fIndex);
//extern Boolean FrmHandleEvent (FormType *formP, EventType *eventP);
//extern void FrmHelp (UInt16 helpMsgId);
extern void FrmHideObject(FormType *formp, UInt16 objIndex);
extern FormType *FrmInitForm(UInt16 formID);
//extern FormBitmapType *FrmNewBitmap (FormType **formPP, UInt16 ID, UItn16 rscID, Coord x, Coord y);
extern FormType *FrmNewForm (UInt16 formID, const Char *titleStrP, Coord x, Coord y,
							 Coord width, Coord height, Boolean modal, UInt16 defaultButton,
							 UInt16 helpRscID, UInt16 menuRscID);
//extern FromGadgetType *FrmNewGadget (FormType **formPP, UInt16 id, Coord x, Coord y,
//										Coord width, Coord height);
//extern FrmGraffitiStateType *FrmNewGsi (FromType **formPP, Coord x, Coord y);
extern FormLabelType *FrmNewLabel (FormType **formPP, UInt16 ID, const Char *textP, Coord x, Coord y, FontID font);
extern Boolean FrmPointInTitle (const FormType *formP, Coord x, Coord y);
extern void FrmPopupForm (UInt16 fIndex);
extern Err FrmRemoveObject (FormType **formPP, UInt16 objIndex);
extern FrmRestoreActiveState (FormActiveStateType stateP);
extern void FrmReturnToForm (UInt16 fIndex);
extern FrmSaveActiveState (FormActiveStateType stateP);
//extern void FrmSaveAllForms (void);
extern void FrmSetActiveForm(FormType *formP);
extern void FrmSetCategoryLabel (FormType *formP, UInt16 objIndex, Char *newLabel);
//extern void FrmSetControlGroupSelection (const FormType *formP, UInt8 groupNum, UInt16 controlID);
extern void FrmSetControlValue (FormType *formP, UInt16 objIndex, Int16 newValue);
extern void FrmSetEventHandler(FormType *form, FormEventHandlerType *handler);
extern void FrmSetFocus(FormType *form, UInt16 fieldIndex);
extern void FrmShowObject(FormType *formp, UInt16 objIndex);
//extern void FrmSetGadgetData (FormType *formP, UInt16 objIndex, const void *data);
//extern void FrmSetGadgetHandler (FormType *formP, UInt16 objIndex, FormGadgetHandlerType *attrP);
extern void FrmSetMenu (FormType *formP, UInt16 menuRscID);
extern void FrmSetObjectBounds (FormType *formP, UInt16 objIndex, const RectangleType *bounds);
extern void FrmSetObjectPosition (FormType *formP, UInt16 objIndex, Coord x, Coord y);
extern void FrmSetTitle (FormType *formP, Char *newTitle);
extern void FrmShowObject (FormType *formP, UInt16 objIndex);
//extern void FrmUpdateForm (UInt16 formId, UInt16 updateCode);
//extern void FrmUpdateScrollers (FormType *formP, UInt16 upIndex, UInt16 downIndex,
//								 Boolean scrollableUp, Boolean scrollableDown);
extern Boolean FrmValidatePtr (const FormType *formP);
extern Boolean FrmVisible (const FormType *formP);



////////////////////////////////////////////////////////////
// Graffiti Manager Library, completed 9/19 functions now.
////////////////////////////////////////////////////////////
extern Err GrfAddPoint (PointType *pt);
extern Err GrfCleanState (void);
extern Err GrfFlushPoints (void);
extern Err GrfGetNumPoints (UInt16 *numPtsP);
extern Err GrfGetPoint (UInt16 index, PointType *pointP);
extern Err GrfGetState (Boolean *capsLockP, Boolean *numLockP, 
								UInt16 *tempShiftP, Boolean *autoShiftedP);
extern Err GrfInitState (void);
extern Err GrfProcessStroke (PointType *startPtP, PointType *endPtP, Boolean upShift);
extern Err GrfSetState (Boolean capsLock, Boolean numLock, Boolean upperShift);


//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.
//////////////////////////////////////////////////////////////////
extern void GsiEnable (const Boolean enableIt);
extern Boolean GsiEnabled (void);
extern void GsiInitialize (void);
extern void GsiSetLocation (const Int16 x, const Int16 y);
extern void GsiSetShiftState (const UInt16 lockFlags, const UInt16 tempShift);



////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
extern void InsPtEnable (Boolean enableIt);
extern Boolean InsPtEnabled (void);
extern Int16 InsPtGetHeight (void);
extern void InsPtGetLocation (Int16 *x, Int16 *y);
extern void InsPtSetHeight (const Int16 height);
extern void InsPtSetLocation (const Int16 x, const Int16 y);


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
extern void LstDrawList (ListType *listP);
extern void LstEraseList (ListType *listP);
extern Int16 LstGetNumberOfItems (const ListType *listP);
extern Int16 LstGetSelection (const ListType *listP);
extern Char *LstGetSelectionText (const ListType *listP, Int16 itemNum);
extern Int16 LstGetVisibleItems (const ListType *listP);
//extern Boolean LstHandleEvent (ListType *listP, const EventType *eventP);
extern Int16 LstMakeItemVisible (ListType *listP, Int16 itemNum);
extern Err LstNewList (void *formPP, UInt16 id, Coord x, Coord y,
						 Coord width, Coord height, FontID font,
						 Int16 visibleItems, Int16 triggerID);
extern Int16 LstPopupList (ListType *listP);
extern Boolean LstScrollList (ListType *listp, WinDrectionType direction,
								Int16 itemCount);
extern void LstSetDrawFunction (ListType *listP, ListDrawDataFuncPtr func);
extern void LstSetHeight (ListType *listP, Int16 visibleItems);
extern void LstSetListChoices (ListType *listP, Char **itemsText, UInt16 numItems);
extern void LstSetPosition (ListType *listP, Coord x, Coord y);
extern void LstSetSelection (ListType *listP, Int16 itemNum);
extern void LstSetTopItem (ListType *listP, Int16 itemNum);



////////////////////////////////////////////////////////////
// Memory Processing Library, completed 23/44 functions now.
////////////////////////////////////////////////////////////
//extern Err MemCardInfo (UInt16 cardNo, Char *cardNameP, Char *manufNameP,
//					  UInt16 *versionP, UInt32 crDateP, UInt32 *romSizeP,
//					  UInt32 *ramSizeP, UInt32 *freeBytesP);
extern Int16 MemCmp(const void *str1, const void *str2, Int32 numBytes);
extern UInt16 MemDebugMode (void);
extern UInt16 MemHandleCardNo (MemHandle h);
//extern Boolean MemHandleDataStorage (MemHandle h);
extern Err MemHandleFree (MemHandle h);
//extern UInt16 MemHandleHeapID (MemHandle h);
extern MemPtr MemHandleLock (MemHandle h);
extern MemHandle MemHandleNew (UInt32 size);
extern Err MemHandleResize (MemHandle h, UInt32 newSize);
extern Err MemHandleSetOwner (MemHandle h, UInt16 owner);
extern UInt32 MemHandleSize (MemHandle h);
extern LocalID MemHandleToLocalID (MemHandle h);
extern Err MemHandleUnlock (MemHandle h);
//extern Err MemHeapCheck (UInt16 heapID);
//extern Err MemHeapCompact (UInt16 heapID);
//extern Boolean MemHeapDynamic (UInt16 heapID);
//extern UInt16 MemHeapFlags (UInt16 heapID);
//extern Err MemHeapFreeBytes (UInt16 heapID, UInt32 *freeP, UInt32 maxP);
//extern UInt16 MemHeapID (UInt16 cardNo, UInt16 heapIndex);
//extern Err MemHeapScramble (UInt16 heapID);
//extern UInt32 MemHeapSize (UInt16 heapID);
//extern LocalIDKind MemLocalIDKind (LocalID local);
//extern MemPtr MemLocaIDToGlobal (LocalID local, UInt16 cardNo);
extern MemPtr MemLocalIDToLockedPtr (LocalID local, UInt16 cardNo);
//extern MemPtr MemLocalIDToPtr (LovalID local, UInt16 cardNo);
extern Err MemMove (VoidPtr dstP, VoidPtr srcP, Int32 numBytes);
extern UInt16 MemNumCards (void);
extern UInt16 MemNumHeaps (UInt16 cardNo);
extern UInt16 MemNumRAMHeaps (UInt16 cardNo);
//extern UInt16 MemPtrCardNo (MemPtr p);
//extern Boolean MemPtrDataStorage (MemPtr p);
extern Err MemPtrFree(MemPtr p);
//extern UInt16 MemPtrHeapID (MemPtr p);
extern MemPtr MemPtrNew(UInt32 size);
//extern MemHandle MemPtrRecoverHandle (MemPtr p);
extern Err MemPtrResize (MemPtr p, UInt32 newSize);
//extern Err MemPtrSetOwner (MemPtr p, UInt16 owner);
extern UInt32 MemPtrSize (MemPtr p);
//extern LocalID MemPtrToLocalID (MemPtr p);
extern Err MemPtrUnlock (MemPtr p);
extern Err MemSet(void *dstP, UInt32 numBytes, UInt8 value);
extern Err MemSetDebugMode (UInt16 flags);
// extern Err MemStoreInfo (UInt16 cardNo, UInt16 storeNumber, UInt16 *versionP,
//						UInt16 *flagsP, Char *nameP, UInt32 *crDateP,
//						UInt32 *bckUpDateP, UInt32 *heapListOffsetP,
//						UInt32 *initCodeOffset1P, UInt32 *initCodeOffset2P,
//						LocalID *databaseDirIDP);



////////////////////////////////////////////////////////////
// Menu Processing Library, completed 9/14 functions now.
////////////////////////////////////////////////////////////
extern Err MenuAddItem (UInt16 positionID, UInt16 id, Char cmd, const Char *textP);
//Err MenuCmdBarAddButton (UInt8 where, UInt16 bitmapID, MenuCmdBarResultType resultType, 
//						 UInt32 result, Char *nameP);
//void MenuCmdBarDisplay (void);
//Boolean MenuCmdBarGetButtonData (Int16 buttonIndex, UInt16 *bitmapIdP, 
//								 MenuCmdBarResultType *resultTypeP,
//								 UInt32 *resultP, Char *nameP);
extern void MenuDispose (MenuBarType *menuP);
extern void MenuDrawMenu (MenuBarType *menuP);
extern void MenuEraseStatus (MenuBarType *menuP);
extern MenuBarType *MenuGetActiveMenu (void);
extern Boolean MenuHandleEvent(MenuBarType *menuP, EventType *event, UInt16 *error) ;
extern Boolean MenuHideItem (UInt16 id);
extern MenuBarType *MenuInit (UInt16 resourceID);
extern MenuBarType *MenuSetActiveMenu (MenuBarType *menuP);
//extern void MenuSetActiveMenuRscID (UInt16 resouceID);
extern Boolean MenuShowItem (UInt16 id);



////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Modem Manager Library, completed 0/2 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Net Library, completed 0/43 functions now.
////////////////////////////////////////////////////////////



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
extern Boolean PwdExists ();
extern void PwdRemove (void);
extern void PwdSet (Char *oldPassword, Char *newPassword);
extern Boolean PwdVerify (Char *string);


////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
extern Err PenCalibrate (PointType *digTopLeftP, PointType *digBotRightP,
						PointType *scrTopLeftP, PointType *scrBotRightP);
extern Err PenResetCalibrate (void);



////////////////////////////////////////////////////////////
// Preferences Library, completed 6/7 functions now.
////////////////////////////////////////////////////////////
extern Int16 PrefGetAppPreferences (UInt32 creator, UInt16 id, void *prefs,
									  UInt16 *prefsSize, Boolean saved);
extern UInt32 PrefGetPreference (SystemPreferencesChoice choice);
extern void PrefGetPreferences (SystemPreferencesPtr p);
extern void PrefSetAppPreferences (UInt32 creator, UInt16 id, UInt16 version,
											  void *prefs, UInt16 prefsSize, Boolean saved);
extern void PrefSetPreference (SystemPreferencesChoice choice, UInt32 value);
extern void PrefSetPreferences (SystemPreferencesPtr p);



///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 0/2 functions now.
///////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Progress Manager Library, completed 0/6 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Rectangle Library, completed 2/6 functions now.
////////////////////////////////////////////////////////////
extern Boolean RctPtInRectangle (Coord x, Coord y, const RectangleType *rP);
extern void RctSetRectangle (RectangleType *P, Coord left, Coord top, Coord width, Coord height);


#define     PenGetPoint(a,b,c)    EvtGetPen(a,b,c)



////////////////////////////////////////////////////////////
// Script Plugin Library, completed 0/1 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 0/4 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 0/8 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 0/10 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// Serial Manager Library, completed 0/17 functions now.
////////////////////////////////////////////////////////////



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
// String Manager Library, completed 12/19 functions now.
////////////////////////////////////////////////////////////
extern Int32 StrAToI(const Char *str);
//extern Int16 StrCaselessCompare (const Char *s1, const Char *s2);
extern Char* StrCat (Char *dst, const Char* src);
extern Char* StrChr (const Char *str, WChar chr);
extern Int16 StrCompare (const Char *dst, const Char* src);
extern Char* StrCopy (Char *dst, const Char* src);
//extern Char* StrDelocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator);
extern Char* StrIToA(Char *s, Int32 i);
extern Char* StrIToH(Char *s, Int32 i);
extern UInt16 StrLen (const Char* src);
//extern Char* StrLocalizeNumber (Char *s, Char thousandSeparator, Char decimalSeparator);
//extern Int16 StrNCaselessCompare (const Char *s1, const Char *s2, Int32 n);
extern Char* StrNCat (Char *dst, const Char* src, Int16 n);
extern Int16 StrNCompare (const Char *dst, const Char* src, UInt32 n);
extern Char* StrNCopy (Char *dst, const Char* src, Int16 n);
//extern Int16 StrPrintF (Char* s, const Char *formatStr, ...);
//extern Char *StrStr (const Char *str, const Char *token);
extern Char* StrToLower (Char *dst, const Char* src);
//extern Int16 StrVPrintF (Char* s, const Char *formatStr, _Palm_va_list argParam);



////////////////////////////////////////////////////////////
// System Dialogs Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
// System Event Manager Library, completed 3/25 functions now.
////////////////////////////////////////////////////////////
extern void EvtGetEvent(EventType *event, Int32 timeout);
extern Boolean SysHandleEvent(EventType *event);
extern void EvtGetPen (Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown);



////////////////////////////////////////////////////////////
// System Manager Library, completed 2/33 functions now.
////////////////////////////////////////////////////////////
extern Char *SysGetOSVersionString ();
extern Int16 SysRandom (UInt32 newSeed);



////////////////////////////////////////////////////////////
// Table Library, completed 47/58 functions now.
////////////////////////////////////////////////////////////
extern void TblDrawTable (TableType *tableP);
extern Boolean TblEditing (const TableType *tableP);
extern void TblEraseTable (TableType *tableP);
//extern Boolean TblFindRowData (const TableType *tableP, UInt32 data, Int16 *rowP);
extern Int16 TblFindRowID (const TableType *tableP, UInt16 id, Int16 *rowP);
extern void TblGetBounds (const TableType *tableP, RectangleType *r);
extern Int16 TblGetColumnSpacing (const TableType *tableP, Int16 column);
extern Int16 TblGetColumnWidth (const TableType *tableP, Int16 column);
extern FieldPtr TblGetCurrentField (const TableType *tableP);
//extern void TblGetItemBounds (const TableType *tableP, Int16 row, Int16 column, RectangleType *r);
extern FontID TblGetItemFont (const TableType *tableP, Int16 row, Int16 column);
extern Int16 TblGetItemInt (const TableType *tableP, Int16 row, Int16 column);
extern void *TblGetItemPtr (const TableType *tableP, Int16 row, Int16 column);
extern Int16 TblGetLastUsableRow (const TableType *tableP);
extern Int16 TblGetNumberOfRows (const TableType *tableP);
extern UInt32 TblGetRowData (const TableType *tableP, Int16 row);
extern Coord TblGetRowHeight (const TableType *tableP, Int16 row);
extern UInt16 TblGetRowID (const TableType *tableP, Int16 row);
extern Boolean TblGetSelection (const TableType *tableP, Int16 *rowP, Int16 *columnP);
extern void TblGrabFocus (TableType *tableP, Int16 row, Int16 column);
//extern Boolean TblHandleEvent (TableType *tableP, EventType *event);
extern void TblHasScrollBar (TableType *tableP, Boolean hasScrollBar);
//extern void TblInsertRow (TableType *tableP, Int16 row);
extern void TblMarkRowInvalid (const TableType *tableP, Int16 row);
extern void TblMarkTableInvalid (const TableType *tableP);
//extern void TblRedrawTable (TableType *tableP);
//extern void TblReleaseFocus (TableType *tableP);
//extern void TblRemoveRow (const TableType *tableP, Int16 row);
extern void tblReverseItem (TableType *tableP, Int16 row, Int16 column);
extern Boolean TblRowInvalid (const TableType *tableP, Int16 row);
extern Boolean TblRowMasked (const TableType *tableP, Int16 row);
extern Boolean TblRowSelectable (const TableType *tableP, Int16 row);
extern Boolean TblRowUsable (TableType *tableP, Int16 row);
extern void TblSelectItem (TableType *tableP, Int16 row, Int16 column);
extern void TblSetBounds (TableType *tableP, const RectangleType *rP);
extern void TblSetColumnEditIndicator (TableType *tableP, Int16 column, Boolean editIndicator);
extern void TblSetColumnMasked (TableType *tableP, Int16 column, Boolean masked);
extern void TblSetColumnSpacing (TableType *tableP, Int16 column, Coord spacing);
extern void TblSetColumnUsable (TableType *tableP, Int16 column, Boolean usable);
extern void TblSetColumnWidth (TableType *tableP, Int16 column, Coord width);
extern void TblSetCostomDrawProcedure (TableType *tableP, Int16 column, TableDrawItemFuncPtr drawCallback);
extern void TblSetItemFont (const TableType *tableP, Int16 row, Int16 column, FontID fontID);
extern void TblSetItemInt (TableType *tableP, Int16 row, Int16 column, Int16 value);
extern void TblSetItemPtr (TableType *tableP, Int16 row, Int16 column, void *value);
extern void TblSetItemStyle (TableType *tableP, Int16 row, Int16 column, TableItemStyleType type);
extern void TblSetLoadDataProcedure (TableType *tableP, Int16 column, TableLoadDataFuncPtr loadDataCallback);
extern void TblSetRowData (TableType *tableP, Int16 row, UInt32 data);
extern void TblSetRowHeight (TableType *tableP, Int16 row, Coord height);
extern void TblSetRowID (TableType *tableP, Int16 row, UInt16 id);
extern void TblSetRowMasked (TableType *tableP, Int16 row, Boolean masked);
extern void TblSetRowSelectable (TableType *tableP, Int16 row, Boolean selectable);
extern void TblSetRowStaticHeight (TableType *tableP, Int16 row, Boolean staticHeight);
extern void TblSetRowUsable (TableType *tableP, Int16 row, Boolean usable);
extern void TblSetSaveDataProcedure (TableType *tableP, Int16 column, TableSaveDataFuncPtr saveDataCallback);
//extern void TblUnhighlightSelection (TableType *tableP);
//extern void TableDrawItemFuncType (void *tableP, Int16 row, Int16 column, RectangleType *bounds);
//extern Err TableLoadDataFuncType (void *tableP, Int16 row, Int16 column, Boolan editable,
//								  MemHandle *dataH, Int16 *dataOffset, Int16 *dataSize, 
//								  FieldPtr fld);
//extern Boolean TableSaveDataFuncType (void *tableP, Int16 row, Int16 column);



////////////////////////////////////////////////////////////
// Text Manager Library, completed 12/38 functions now.
////////////////////////////////////////////////////////////
extern Boolean TxtCharIsAlNum (Char ch);
extern Boolean TxtCharIsAlpha (Char ch);
extern Boolean TxtCharIsCntrl (Char ch);
extern Boolean TxtCharIsDelim (Char ch);
extern Boolean TxtCharIsDigit (Char ch);
extern Boolean TxtCharIsGraph (Char ch);
extern Boolean TxtCharIsHex (Char ch);
extern Boolean TxtCharIsLower (Char ch);
extern Boolean TxtCharIsPrint (Char ch);
extern Boolean TxtCharIsSpace (Char ch);
extern Boolean TxtCharIsUpper (Char ch);
extern UInt16	TxtCharSize (WChar inChar);


////////////////////////////////////////////////////////////
// Time Manager Library, completed 15/17 functions now.
////////////////////////////////////////////////////////////
extern void DateAdjust (DatePtr dateP, Int32 adjustment);
extern void DateDaysToDate (UInt32 days, DatePtr Date);
extern void DateSecondsToDate (UInt32 seconds, DatePtr date);
//extern void DateTemplateToAscii (const Char *templateP, UInt8 months,
//											UInt8 days, UInt16 years, Char *stringP,
//											Int16 stringLen);
extern void DateToAscii (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString);
extern UInt32 DateToDays (DateType date);
extern void DateToDOWDMFormat (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString);
extern Int16 DayOfMonth (Int16 month, Int16 day, Int16 year);
//extern Int16 DayOfWeek (Int16 month, Int16 day, Int16 year);
extern Int16 DaysInMonth (Int16 month, Int16 year);
extern void TimeAdjust (DateTimePtr datetimeP, Int32 adjustment);
extern UInt32 TimDateTimeToSeconds (DateTimePtr dateTimeP);
extern UInt32 TimGetSeconds (void);
extern UInt32 TimGetTicks (void);
extern void TimSecondsToDateTime (UInt32 seconds, DateTimePtr dateTimeP);
extern void TimSetSeconds (UInt32 seconds);
extern void TimeToAscii (UInt8 hours, UInt8 minutes, 
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
// Window function, completed 21/80 functions now.
////////////////////////////////////////////////////////////
extern void WinDrawChar (WChar theChar, Coord x, Coord y);
extern void WinDrawChars (const Char *chars, Int16 len, Coord x, Coord y);
extern void WinDrawGrayLine (Coord x1, Coord y1, Coord x2, Coord y2);
extern void WinDrawGrayRectangle (FrameType frame, RectangleType *rP);
extern void WinDrawInvertedChars (const Char *chars, Int16 len, Coord x, Coord y);
extern void WinDrawLine (Coord x1, Coord y1, Coord x2, Coord y2);
extern void WinDrawPixel (Coord x, Coord y);
extern void WinDrawRectangle (RectangleType *rP, UInt16 cornerDiam);
extern void WinDrawRectangleFrame (FrameType frame, RectangleType *rP);
extern void WinDrawTruncChars (const Char *chars, Int16 len, Coord x, Coord y, Coord maxWidth);
extern void WinEraseChars (const Char *chars, Int16 len, Coord x, Coord y);
extern void WinEraseLine (Coord x1, Coord y1, Coord x2, Coord y2);
extern void WinErasePixel (Coord x, Coord y);
extern void WinEraseRectangle (RectangleType *rP, UInt16 corneDiam);
extern void WinEraseWindow (void);
extern void WinFillLine (Coord x1, Coord y1, Coord x2, Coord y2);
extern void WinFillRectangle (RectangleType *rP, UInt16 cornerDiam);
extern IndexedColorType WinGetPixel (Coord x, Coord y);
extern void WinInvertPixel (Coord x, Coord y);
extern void WinPaintPixel (Coord x, Coord y);
extern void WinPaintPixels (UInt16 numPoints, PointType pts[]);
extern void WinResetClip(void);

#endif // __APILIB_H__
