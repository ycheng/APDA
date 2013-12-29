
////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeAlmGetAlarm (void);
void PipeAlmGetProcAlarm (void);
void PipeAlmSetAlarm (void);
void PipeAlmSetProcAlarm (void);

////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipeBmpBitsSize (void);
void PipeBmpColortableSize (void);
void PipeBmpCompress (void);
void PipeBmpCreate (void);
void PipeBmpDelete (void);
void PipeBmpGetBits (void);
void PipeBmpGetColortable (void);
void PipeBmpSize (void);
void PipeColorTableEntries (void);

////////////////////////////////////////////////////////////
// Category Library, completed 16/16 functions now.
////////////////////////////////////////////////////////////
void PipeCategoryCreateList (void);
void PipeCategoryCreateListV10(void);
void PipeCategoryEdit (void);
void PipeCategoryEditV20 (void);
void PipeCategoryEditV10(void);
void PipeCategoryFind (void);
void PipeCategoryFreeList (void);
void PipeCategoryFreeListV10 (void);
void PipeCategoryGetName (void);
void PipeCategoryGetNext (void);
void PipeCategoryInitialize (void);
void PipeCategorySelect (void);
void PipeCategorySelectV10 (void);
void PipeCategorySetName (void);
void PipeCategorySetTriggerLabel (void);
void PipeCategoryTruncateName (void);

////////////////////////////////////////////////////////////
// Character Attributes Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeChrHorizEllipsis (void);
void PipeChrIsHardKey(void);
void PipeChrNumericSpace (void);
void PipeGetCharAttr (void);
void PipeGetCharCaselessValue (void);
void PipeGetCharSortValue (void);

////////////////////////////////////////////////////////////
// Clipboad functions, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeClipboardAddItem (void);
void PipeClipboardAppendItem (void);
void PipeClipboardGetItem (void);

////////////////////////////////////////////////////////////
// Connection Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeCncAddProfile(void);
void PipeCncDeleteProfile(void);
void PipeCncGetProfileInfo(void);
void PipeCncGetProfileList(void);

////////////////////////////////////////////////////////////
// Control Handle Library, completed 20/20 functions now.
////////////////////////////////////////////////////////////
void PipeCtlDrawControl (void);
void PipeCtlEnabled (void);
void PipeCtlEraseControl (void);
void PipeCtlGetLabel (void);
void PipeCtlGetSliderValues (void);
void PipeCtlGetValue (void);
void PipeCtlHandleEvent (void);
void PipeCtlHideControl (void);
void PipeCtlHitControl (void);
void PipeCtlNewControl (void);
void PipeCtlNewGraphicControl (void);
void PipeCtlNewSliderControl (void);
void PipeCtlSetEnabled (void);
void PipeCtlSetLabel (void);
void PipeCtlSetGraphics (void);
void PipeCtlSetSliderValue (void);
void PipeCtlSetUsable (void);
void PipeCtlSetValue (void);
void PipeCtlShowControl (void);
void PipeCtlValidatePointer (void);

///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 6/6 functions now.
///////////////////////////////////////////////////////////////

void PipeDayHandleEvent (void);
void PipeSelectDay (void);
void PipeSelectDayV10 (void);
void PipeSelectOneTime (void);
void PipeSelectTime (void);
void PipeSelectTimeV33 (void);

////////////////////////////////////////////////////////////
// DataBase Library, completed 68/68 functions now.
////////////////////////////////////////////////////////////
void PipeDmArchiveRecord (void);
void PipeDmAttachRecord (void);
void PipeDmAttachResource (void);
void PipeDmCloseDatabase (void);
void PipeDmCreateDatabase (void);
void PipeDmCreateDatabaseFromImage (void);
void PipeDmDatabaseInfo (void);
void PipeDmDatabaseProtect (void);
void PipeDmDatabaseSize (void);
void PipeDmDeleteCategory (void);
void PipeDmDeleteDatabase (void);
void PipeDmDeleteRecord (void);
void PipeDmDetachRecord (void);
void PipeDmDetachResource (void);
void PipeDmFindDatabase (void);
void PipeDmFindRecordByID(void);
void PipeDmFindResource (void);
void PipeDmFindResourceType (void);
void PipeDmFindSortPosition (void);
void PipeDmFindSortPositionV10(void);
void PipeDmGetAppInfoID (void);
void PipeDmGetDatabase (void);
void PipeDmGetDatabaseLocalState (void);
void PipeDmGetLastErr (void);
void PipeDmGetNextDatabaseByTypeCreator (void);
void PipeDmGetRecord (void);
void PipeDmGetResource(void);
void PipeDmGetResourceIndex(void);
void PipeDmGet1Resource (void);
void PipeDmInsertionSort (void);
void PipeDmMoveCategory (void);
void PipeDmMoveRecord (void);
void PipeDmNewHandle(void);
void PipeDmNewRecord (void);
void PipeDmNewResource (void);
void PipeDmNextOpenDatabase (void);
void PipeDmNumDatabases (void);
void PipeDmNumRecords (void);
void PipeDmNumRecordsInCategory (void);
void PipeDmNumResources (void);
void PipeDmOpenDatabase (void);
void PipeDmOpenDatabaseByTypeCreator(void);
void PipeDmOpenDatabaseInfo (void);
void PipeDmOpenDBNoOvelay(void);
void PipeDmPositionInCategory (void);
void PipeDmQueryNextInCategory (void);
void PipeDmQueryRecord (void);
void PipeDmQuickSort(void);
void PipeDmRecordInfo (void);
void PipeDmReleaseRecord (void);
void PipeDmReleaseResource (void);
void PipeDmRemoveRecord (void);
void PipeDmRemoveResource (void);
void PipeDmRemoveSecretRecord (void);
void PipeDmResizeRecord (void);
void PipeDmResizeResource (void);
void PipeDmResourceInfo (void);
void PipeDmResetRecordStates(void);
void PipeDmSearchRecord (void);
void PipeDmSearchResource (void);
void PipeDmSeekRecordInCategory (void);
void PipeDmSet (void);
void PipeDmSetDatabaseInfo (void);
void PipeDmSetRecordInfo (void);
void PipeDmSetResourceInfo (void);
void PipeDmStrCopy(void);
void PipeDmWrite (void);
void PipeDmWriteCheck (void);

////////////////////////////////////////////////////////////
// Error Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeErrAlert(void);
void PipeErrFatalDisplay (void);
void PipeErrDisplayFileLineMsg (void);
void PipeErrFatalDisplayIf (void);
void PipeErrNonFatalDisplayIf (void);
void PipeErrThrow (void);


////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipeExgAccept (void);
void PipeExgDBRead(void);
void PipeExgDBWrite (void);
void PipeExgDisconnect (void);
void PipeExgDoDialog (void);
void PipeExgPut (void);
void PipeExgReceive(void);
void PipeExgRegisterData(void);
void PipeExgSend (void);

////////////////////////////////////////////////////////////
// Feature Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////
void PipeFtrGet (void);
void PipeFtrGetByIndex(void);
void PipeFtrPtrFree(void);
void PipeFtrPtrNew (void);
void PipeFtrPtrResize (void);
void PipeFtrSet (void);
void PipeFtrUnregister (void);

////////////////////////////////////////////////////////////
// Field Processing Library, completed 52/52 functions now.
////////////////////////////////////////////////////////////
void PipeFldCalcFieldHeight (void);
void PipeFldCompactText (void);
void PipeFldCopy (void);
void PipeFldCut (void);
void PipeFldDelete(void);
void PipeFldDirty (void);
void PipeFldDrawField (void);
void PipeFldEraseField (void);
void PipeFldFreeMemory (void);
void PipeFldGetAttributes (void);
void PipeFldGetBounds (void);
void PipeFldGetFont (void);
void PipeFldGetInsPtPosition (void);
void PipeFldGetMaxChars (void);
void PipeFldGetNumberOfBlankLines (void);
void PipeFldGetScrollPosition (void);
void PipeFldGetScrollValues (void);
void PipeFldGetSelection (void);
void PipeFldGetTextAllocatedSize (void);
void PipeFldGetTextHandle (void);
void PipeFldGetTextHeight(void);
void PipeFldGetTextLength (void);
void PipeFldGetTextPtr (void);
void PipeFldGetVisibleLines (void);
void PipeFldGrabFocus (void);
void PipeFldHandleEvent (void);
void PipeFldInsert (void);
void PipeFldMakeFullyVisible (void);
void PipeFldNewField (void);
void PipeFldPaste(void);
void PipeFldRecalculateField (void);
void PipeFldReleaseFocus (void);
void PipeFldScrollable (void); 
void PipeFldScrollField(void);
void PipeFldSendChangeNotification (void);
void PipeFldSendHeightChangeNotification (void);
void PipeFldSetAttributes (void);
void PipeFldSetBounds (void);
void PipeFldSetDirty (void);
void PipeFldSetFont (void);
void PipeFldSetInsertionPoint (void);
void PipeFldSetInsPtPosition (void);
void PipeFldSetMaxChars (void);
void PipeFldSetScrollPosition (void);
void PipeFldSetSelection (void);
void PipeFldSetText  (void);
void PipeFldSetTextAllocatedSize  (void);
void PipeFldSetTextHandle  (void);
void PipeFldSetTextPtr  (void);
void PipeFldSetUsable  (void);
void PipeFldUndo  (void);
void PipeFldWordWrap  (void);

////////////////////////////////////////////////////////////
// File Streaming Library, completed 16/16 functions now.
////////////////////////////////////////////////////////////
void PipeFileClearerr  (void);
void PipeFileClose (void);
void PipeFileControl (void);
void PipeFileDelete  (void);
void PipeFileDmRead (void);
void PipeFileEOF  (void);
void PipeFileError (void);
void PipeFileFlush  (void);
void PipeFileGetLastError  (void);
void PipeFileOpen (void);
void PipeFileRead  (void);
void PipeFileRewind  (void);
void PipeFileSeek  (void);
void PipeFileTell (void);
void PipeFileTruncate (void);
void PipeFileWrite  (void);

////////////////////////////////////////////////////////////
// Find Processing Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeFindDrawHeader  (void);
void PipeFindGetLineBounds (void);
void PipeFindSaveMatch (void);
void PipeFindStrInStr  (void);

////////////////////////////////////////////////////////////
// Float Manager Library, completed 12/12 functions now.
////////////////////////////////////////////////////////////
void PipeFplAdd (void);
void PipeFplAToF  (void);
void PipeFplBase10Info  (void);
void PipeFplDiv (void);
void PipeFplFloatToLong  (void);
void PipeFplFloatToULong  (void);
void PipeFplFree  (void);
void PipeFplFToA(void);
void PipeFplInit (void);
void PipeFplLongToFloat  (void);
void PipeFplMul (void);
void PipeFplSub  (void);

////////////////////////////////////////////////////////////
// Font Processing Library, completed 18/18 functions now.
////////////////////////////////////////////////////////////
void PipeFntAverageCharWidth  (void);
void PipeFntBaseLine(void);
void PipeFntCharHeight  (void);
void PipeFntCharsInWidth  (void);
void PipeFntCharsWidth (void);
void PipeFntCharWidth  (void);
void PipeFntDefineFont(void);
void PipeFntGetFont  (void);
void PipeFntGetFontPtr(void);
void PipeFntGetScrollValues(void);
void PipeFntLineHeight  (void);
void PipeFntLineWidth  (void);
void PipeFntSetFont (void);
void PipeFntWidthToOffset(void);
void PipeFntWordWrap (void);
void PipeFntWordWrapReverseNLines(void);
void PipeFontSelect(void);
////////////////////////////////////////////////////////////
// Form Processing Library, completed 65/65 functions now.
////////////////////////////////////////////////////////////
void PipeFrmAlert  (void);
void PipeFrmCloseAllForms  (void);
void PipeFrmCopyLabel (void);
void PipeFrmCopyTitle  (void);
void PipeFrmCustomAlert  (void);
void PipeFrmCustomResponseAlert  (void);
void PipeFrmDeleteForm  (void);
void PipeFrmDispatchEvent (void);
void PipeFrmDoDialog  (void);
void PipeFrmDrawForm (void);
void PipeFrmEraseForm  (void);
void PipeFrmGetActiveForm  (void);
void PipeFrmGetActiveFormID (void);
void PipeFrmGetControlGroupSelection  (void);
void PipeFrmGetControlValue (void);
void PipeFrmGetFirstForm  (void);
void PipeFrmGetFocus (void);
void PipeFrmGetFormBounds  (void);
void PipeFrmGetFormId  (void);
void PipeFrmGetFormPtr (void);
void PipeFrmGetGadgetData  (void);
void PipeFrmGetLabel  (void);
void PipeFrmGetNumberOfObjects (void);
void PipeFrmGetObjectBounds  (void);
void PipeFrmGetObjectId  (void);
void PipeFrmGetObjectIndex (void);
void PipeFrmGetObjectPosition (void);
void PipeFrmGetObjectPtr  (void);
void PipeFrmGetObjectType  (void);
void PipeFrmGetTitle  (void);
void PipeFrmGetWindowHandle  (void);
void PipeFrmGotoForm  (void);
void PipeFrmHandleEvent (void);
void PipeFrmHelp  (void);
void PipeFrmHideObject (void);
void PipeFrmInitForm (void);
void PipeFrmNewBitmap  (void);
void PipeFrmNewForm  (void);
void PipeFrmNewGadget (void);
void PipeFrmNewGsi (void);
void PipeFrmNewLabel  (void);
void PipeFrmPointInTitle  (void);
void PipeFrmPopupForm  (void);
void PipeFrmRemoveObject  (void);
void PipeFrmRestoreActiveState  (void);
void PipeFrmReturnToForm  (void);
void PipeFrmSaveActiveState (void);
void PipeFrmSaveAllForms (void);
void PipeFrmSetActiveForm(void);
void PipeFrmSetCategoryLabel (void);
void PipeFrmSetControlGroupSelection (void);
void PipeFrmSetControlValue (void);
void PipeFrmSetEventHandler(void);
void PipeFrmSetFocus(void);
void PipeFrmSetGadgetData (void);
void PipeFrmSetGadgetHandler (void);
void PipeFrmSetMenu (void);
void PipeFrmSetObjectBounds (void);
void PipeFrmSetObjectPosition (void);
void PipeFrmSetTitle (void);
void PipeFrmShowObject (void);
void PipeFrmUpdateForm (void);
void PipeFrmUpdateScrollers (void);
void PipeFrmValidatePtr (void);
void PipeFrmVisible (void);

////////////////////////////////////////////////////////////
// Graffiti Manager Library, completed 19/19 functions now.
////////////////////////////////////////////////////////////
void PipeGrfAddMacro(void);
void PipeGrfAddPoint (void);
void PipeGrfCleanState (void);
void PipeGrfDeleteMacro(void);
void PipeGrfFilterPoints(void);
void PipeGrfFindBranch(void);
void PipeGrfFlushPoints (void);
void PipeGrfGetAndExpandMacro(void);
void PipeGrfGetGlyphMapping(void);
void PipeGrfGetMacro(void);
void PipeGrfGetMacroName(void);
void PipeGrfGetNumPoints (void);
void PipeGrfGetPoint (void);
void PipeGrfGetState (void);
void PipeGrfInitState (void);
void PipeGrfMatch(void);
void PipeGrfMatchGlyph(void);
void PipeGrfProcessStroke (void);
void PipeGrfSetState (void);

//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.
//////////////////////////////////////////////////////////////////
void PipeGsiEnable (void);
void PipeGsiEnabled (void);
void PipeGsiInitialize(void);
void PipeGsiSetLocation (void);
void PipeGsiSetShiftState (void);

////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeInsPtEnable (void);
void PipeInsPtEnabled (void);
void PipeInsPtGetHeight (void);
void PipeInsPtGetLocation (void);
void PipeInsPtSetHeight (void);
void PipeInsPtSetLocation (void);

////////////////////////////////////////////////////////////
// Key Manager Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeKeyCurrentState (void);
void PipeKeyRates (void);
void PipeKeySetMask (void);

////////////////////////////////////////////////////////////
// IR Library, completed 22/22 functions now.
////////////////////////////////////////////////////////////
void PipeIrAdvanceCredit(void);
void PipeIrBind (void);
void PipeIrClose (void);
void PipeIrConnectIrLap (void);
void PipeIrConnectReq (void);
void PipeIrConnectRsp (void);
void PipeIrDataReq (void);
void PipeIrDisconnectIrLap (void);
void PipeIrDiscoverReq (void);
void PipeIrIsIrLapConnected(void);
void PipeIrIsMediaBusy(void);
void PipeIrIsNoProgress (void);
void PipeIrIsRemoteBusy (void);
void PipeIrLocalBusy (void);
void PipeIrMaxRxSize (void);
void PipeIrMaxTxSize (void);
void PipeIrOpen (void);
void PipeIrSetConTypeLMP(void);
void PipeIrSetConTypeTTP(void);
void PipeIrSetDeviceInfo(void);
void PipeIrTestReq (void);
void PipeIrUnbind (void);

////////////////////////////////////////////////////////////
// IAS Library, completed 14/14 functions now.
////////////////////////////////////////////////////////////
void PipeIrIAS_Add(void);
void PipeIrIAS_GetInteger (void);
void PipeIrIAS_GetIntLsap (void);
void PipeIrIAS_GetObjectID(void);
void PipeIrIAS_GetOctetString(void);
void PipeIrIAS_GetOctetStringLen (void);
void PipeIrIAS_GetType(void);
void PipeIrIAS_GetUserString (void);
void PipeIrIAS_GetUserStringCharSet (void);
void PipeIrIAS_GetUserStringLen (void);
void PipeInsPtSetHeight (void);
void PipeIrIAS_Next (void);
void PipeIrIAS_Query(void);
void PipeIrIAS_SetDeviceName(void);
void PipeIrIAS_StartResult(void);

////////////////////////////////////////////////////////////
// List Handle Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
void PipeLstDrawList (void);
void PipeLstEraseList (void);
void PipeLstGetNumberOfItems (void);
void PipeLstGetSelection (void);
void PipeLstGetSelectionText (void);
void PipeLstGetVisibleItems (void);
void PipeLstHandleEvent (void);
void PipeLstMakeItemVisible (void);
void PipeLstNewList(void);
void PipeLstPopupList(void);
void PipeLstScrollList (void);
void PipeLstSetDrawFunction (void);
void PipeLstSetHeight (void);
void PipeLstSetListChoices (void);
void PipeLstSetPosition (void);
void PipeLstSetSelection (void);
void PipeLstSetTopItem (void);

////////////////////////////////////////////////////////////
// Memory Manager Library, completed 44/44 functions now.
////////////////////////////////////////////////////////////
void PipeMemCardInfo (void);
void PipeMemCmp(void);
void PipeMemDebugMode (void);
void PipeMemHandleCardNo (void);
void PipeMemHandleDataStorage (void);
void PipeMemHandleFree (void);
void PipeMemHandleHeapID (void);
void PipeMemHandleLock (void);
void PipeMemHandleNew (void);
void PipeMemHandleResize(void);
void PipeMemHandleSetOwner (void);
void PipeMemHandleSize(void);
void PipeMemHandleToLocalID (void);
void PipeMemHandleUnlock (void);
void PipeMemHeapCheck(void);
void PipeMemHeapCompact (void);
void PipeMemHeapDynamic (void);
void PipeMemHeapFlags (void);
void PipeMemHeapFreeBytes (void);
void PipeMemHeapID (void);
void PipeMemHeapScramble (void);
void PipeMemHeapSize (void);
void PipeMemLocalIDKind (void);
void PipeMemLocaIDToGlobal(void);
void PipeMemLocalIDToLockedPtr (void);
void PipeMemLocalIDToPtr (void);
void PipeMemMove (void);
void PipeMemNumCards (void);
void PipeMemNumHeaps (void);
void PipeMemNumRAMHeaps (void);
void PipeMemPtrCardNo (void);
void PipeMemPtrDataStorage (void);
void PipeMemPtrFree(void);
void PipeMemPtrHeapID (void);
void PipeMemPtrNew(void);
void PipeMemPtrRecoverHandle (void);
void PipeMemPtrResize (void);
void PipeMemPtrSetOwner (void);
void PipeMemPtrSize(void);
void PipeMemPtrToLocalID (void);
void PipeMemPtrUnlock (void);
void PipeMemSet(void);
void PipeMemSetDebugMode (void);
void PipeMemStoreInfo(void);

////////////////////////////////////////////////////////////
// Menu Processing Library, completed 14/14 functions now.
////////////////////////////////////////////////////////////
void PipeMenuAddItem (void);
void PipeMenuCmdBarAddButton (void);
void PipeMenuCmdBarDisplay (void);
void PipeMenuCmdBarGetButtonData (void);
void PipeMenuDispose (void);
void PipeMenuDrawMenu (void);
void PipeMenuEraseStatus (void);
void PipeMenuGetActiveMenu(void);
void PipeMenuHandleEvent(void);
void PipeMenuHideItem (void);
void PipeMenuInit (void);
void PipeMenuSetActiveMenu (void);
void PipeMenuSetActiveMenuRscID (void);
void PipeMenuShowItem(void);
   
////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeCrc16CalcBlock (void);
void PipeIntlGetRoutineAddress (void);
void PipeLocGetNumberSeparators(void);

////////////////////////////////////////////////////////////
// Modem Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
void PipeMdmDial(void);
void PipeMdmHangUp (void);

////////////////////////////////////////////////////////////
// Net Library, completed 44/44 functions now.
////////////////////////////////////////////////////////////
void PipeNetHToNL (void);
void PipeNetHToNS (void);
void PipeNetLibAddrAToIN(void);
void PipeNetLibAddrINToA (void);
void PipeNetLibClose(void);
void PipeNetLibConnectionRefresh(void);
void PipeNetLibDmReceive (void);
void PipeNetLibFinishCloseWait(void);
void PipeNetLibGetHostByAddr (void);
void PipeNetLibGetHostByName (void);
void PipeNetLibGetMailExchangeByName(void);
void PipeNetLibGetServByName (void);
void PipeNetLibIFAttach (void);
void PipeNetLibIFDetach (void);
void PipeNetLibIFDown (void);
void PipeNetLibIFGet (void);
void PipeNetLibIFSettingGet (void);
void PipeNetLibIFSettingSet (void);
void PipeNetLibIFUp (void);
void PipeNetLibMaster(void);
void PipeNetLibOpen (void);
void PipeNetLibOpenCount (void);
void PipeNetLibReceive (void);
void PipeNetLibReceivePB (void);
void PipeNetLibSelect (void);
void PipeNetLibSend (void);
void PipeNetLibSendPB (void);
void PipeNetLibSettingGet(void);
void PipeNetLibSettingSet (void);
void PipeNetLibSocketAccept (void);
void PipeNetLibSocketAddr(void);
void PipeNetLibSocketBind (void);
void PipeNetLibSocketClose(void);
void PipeNetLibSocketConnect (void);
void PipeNetLibSocketListen (void);
void PipeNetLibSocketOpen(void);
void PipeNetLibSocketOptionGet(void);
void PipeNetLibSocketOptionSet(void);
void PipeNetLibSocketShutdown(void);
void PipeNetLibTracePrintF(void);
void PipeNetLibTracePutS (void);
void PipeNetNToHL (void);
void PipeNetNToHS (void);

////////////////////////////////////////////////////////////
// Network Utilities Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeNetUReadN (void);
void PipeNetUTCPOpen (void);
void PipeNetUWriteN(void);

////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 21/21 functions now.
////////////////////////////////////////////////////////////
void PipeSrmClearErr (void);
void PipeSrmClose(void);
void PipeSrmControl(void);
void PipeSrmGetDeviceCount (void);
void PipeSrmGetDeviceInfo (void);
void PipeSrmGetStatus (void);
void PipeSrmOpen(void);
void PipeSrmOpenBackground (void);
void PipeSrmPrimeWakeupHandler (void);
void PipeSrmReceive(void);
void PipeSrmReceiveCheck(void);
void PipeSrmReceiveFlush(void);
void PipeSrmReceiveWait (void);
void PipeSrmReceiveWindowClose (void);
void PipeSrmReceiveWindowOpen (void);
void PipeSrmSend (void);
void PipeSrmSendCheck(void);
void PipeSrmSendFlush (void);
void PipeSrmSendWait(void);
void PipeSrmSetReceiveBuffer (void);
void PipeSrmSetWakeupHandler (void);

////////////////////////////////////////////////////////////
// Notification Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeSysNotifyBroadcast(void);
void PipeSysNotifyBroadcastDeferred (void);
void PipeSysNotifyRegister(void);
void PipeSysNotifyUnregister (void);

////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 7/7 functions now.
////////////////////////////////////////////////////////////
void PipeOmGetCurrentLocale (void);
void PipeOmGetIndexedLocale (void);
void PipeOmGetRoutineAddress (void);
void PipeOmGetSystemLocale (void);
void PipeOmLocaleToOverlayDBName (void);
void PipeOmOverlayDBNameToLocale(void);
void PipeOmSetSystemLocale (void);

////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipePwdExists (void);
void PipePwdRemove (void);
void PipePwdSet (void);
void PipePwdVerify (void);

////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.
////////////////////////////////////////////////////////////
void PipePenCalibrate (void);
void PipePenResetCalibrate (void);

////////////////////////////////////////////////////////////
// Preferences Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipePrefGetAppPreferences (void);
void PipePrefGetAppPreferencesV10 (void);
void PipePrefGetPreference (void);
void PipePrefGetPreferences (void);
void PipePrefOpenPreferenceDBV10 (void);
void PipePrefSetAppPreferences (void);
void PipePrefSetAppPreferencesV10 (void);
void PipePrefSetPreference (void);
void PipePrefSetPreferences (void);

///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 2/2 functions now.
///////////////////////////////////////////////////////////////////
void PipeSecSelectViewStatus(void);
void PipeSecVerifyPW(void);

////////////////////////////////////////////////////////////
// Progress Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipePrgHandleEvent (void);
void PipePrgStartDialog(void);
void PipePrgStartDialogV31 (void);
void PipePrgStopDialog (void);
void PipePrgUpdateDialog (void);
void PipePrgUserCancel (void);

////////////////////////////////////////////////////////////
// Rectangle Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeRctCopyRectangle (void);
void PipeRctGetIntersection(void);
void PipeRctInsetRectangle (void);
void PipeRctOffsetRectangle (void);
void PipeRctPtInRectangle (void);
void PipeRctSetRectangle(void);

////////////////////////////////////////////////////////////
// Script Plugin Library, completed 1/1 functions now.
////////////////////////////////////////////////////////////
void PipeScriptPluginSelectorProc(void);

////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeSclDrawScrollBar (void);
void PipeSclGetScrollBar (void);
void PipeSclHandleEvent (void);
void PipeSclSetScrollBar (void);

////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 8/8 functions now.
////////////////////////////////////////////////////////////
void PipeDrvEntryPoint (void);
void PipeSdrvClose (void);
void PipeSdrvControl(void);
void PipeSdrvISP (void);
void PipeSdrvOpen(void);
void PipeSdrvReadChar (void);
void PipeSdrvStatus(void);
void PipeSdrvWriteChar(void);

////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 10/10 functions now.
////////////////////////////////////////////////////////////
void PipeSlkClose (void);
void PipeSlkCloseSocket (void);
void PipeSlkFlushSocket(void);
void PipeSlkOpen(void);
void PipeSlkOpenSocket (void);
void PipeSlkReceivePacket(void);
void PipeSlkSendPacket(void);
void PipeSlkSetSocketListener(void);
void PipeSlkSocketPortID(void);
void PipeSlkSocketSetTimeout(void);

////////////////////////////////////////////////////////////
// Serial Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
void PipeSerClearErr (void);
void PipeSerClose(void);
void PipeSerControl(void);
void PipeSerGetSettings (void);
void PipeSerGetStatus(void);
void PipeSerOpen (void);
void PipeSerReceive(void);
void PipeSerReceive10(void);
void PipeSerReceiveCheck (void);
void PipeSerReceiveFlush (void);
void PipeSerReceiveWait(void);
void PipeSerSend (void);
void PipeSerSend10(void);
void PipeSerSendFlush(void);
void PipeSerSendWait(void);
void PipeSerSetReceiveBuffer(void);
void PipeSerSetSettings(void);

////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeGetSize(void);
void PipeGetSpace (void);
void PipeWriteBlock (void);
void PipeWriteByte(void);

////////////////////////////////////////////////////////////
// Sound Manager Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeSndCreateMidiList(void);
void PipeSndDoCmd(void);
void PipeSndGetDefaultVolume(void);
void PipeSndPlaySmf(void);
void PipeSndPlaySmfResource (void);
void PipeSndPlaySystemSound (void);

////////////////////////////////////////////////////////////
// Standard IO Library, completed 5/5 functions now.
////////////////////////////////////////////////////////////
void PipeSioClearScreen(void);
void PipeSioExecCommand(void);
void PipeSioFree(void);
void PipeSioHandleEvent(void);
void PipeSioInit (void);

////////////////////////////////////////////////////////////
// String Manager Library, completed 19/19 functions now.
////////////////////////////////////////////////////////////
void PipeStrAToI(void);
void PipeStrCaselessCompare (void);
void PipeStrCat (void);
void PipeStrChr(void);
void PipeStrCompare (void);
void PipeStrCopy (void);
void PipeStrDelocalizeNumber(void);
void PipeStrIToA(void);
void PipeStrIToH(void);
void PipeStrLen (void);
void PipeStrLocalizeNumber (void);
void PipeStrNCaselessCompare (void);
void PipeStrNCat (void);
void PipeStrNCompare (void);
void PipeStrNCopy (void);
void PipeStrPrintF (void);
void PipeStrStr (void);
void PipeStrToLower (void);
void PipeStrVPrintF(void);

////////////////////////////////////////////////////////////
// System Dialogs Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeSysAppLauncherDialog (void);
void PipeSysFatalAlert (void);
void PipeSysGraffitiReferenceDialogs(void);

//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 25/25 functions now.
//////////////////////////////////////////////////////////////
void PipeEvtAddEventToQueue (void);
void PipeEvtAddUniqueEventToQueue(void);
void PipeEvtCopyEvent(void);
void PipeEvtDequeuePenPoint (void);
void PipeEvtDequeuePenStrokeInfo (void);
void PipeEvtEnableGraffiti(void);
void PipeEvtEnqueueKey(void);
void PipeEvtEventAvail(void);
void PipeEvtFlushKeyQueue (void);
void PipeEvtFlushNextPenStroke(void);
void PipeEvtFlushPenQueue(void);
void PipeEvtGetEvent (void);
void PipeEvtGetPen(void);
void PipeEvtGetPenBtnList(void);
void PipeEvtGetSilkscreenAreaList(void);
void PipeEvtKeydownIsVirtual (void);
void PipeEvtKeyQueueEmpty (void);
void PipeEvtKeyQueueSize(void);
void PipeEvtPenQueueSize(void);
void PipeEvtProcessSoftKeyStroke(void);
void PipeEvtResetAutoOffTimer(void);
void PipeEvtSetAutoOffTimer(void);
void PipeEvtSetNullEventTick(void);
void PipeEvtSysEventAvail (void);
void PipeEvtWakeup(void);

////////////////////////////////////////////////////////////
// System Manager Library, completed 33/33 functions now.
////////////////////////////////////////////////////////////
void PipeSysAppLaunch (void);
void PipeSysBatteryInfo (void);
void PipeSysBatteryInfoV20 (void);
void PipeSysBinarySearch(void);
void PipeSysBroadcastActionCode(void);
void PipeSysCopyStringResource(void);
void PipeSysCreateDataBaseList (void);
void PipeSysCreatePanelList (void);
void PipeSysCurAppDatabase(void);
void PipeSysErrString (void);
void PipeSysFormPointerArrayToStrings (void);
void PipeSysGetOSVersionString (void);
void PipeSysGetROMToken(void);
void PipeSysGetStackInfo (void);
void PipeSysGetTrapAddress(void);
void PipeSysGraffitiReferenceDialog (void);
void PipeSysGremlins(void);
void PipeSysHandleEvent(void);
void PipeSysInsertionSort(void);
void PipeSysKeyboardDialog (void);
void PipeSysKeyboardDialogV10 (void);
void PipeSysLibFind (void);
void PipeSysLibLoad (void);
void PipeSysLibRemove (void);
void PipeSysQSort (void);
void PipeSysRandom (void);
void PipeSysReset (void);
void PipeSysSetAutoOffTime (void);
void PipeSysSetTrapAddress (void);
void PipeSysStringByIndex(void);
void PipeSysTaskDelay(void);
void PipeSysTicksPerSecond(void);
void PipeSysUIAppSwitch(void);

////////////////////////////////////////////////////////////
// Table Library, completed 57/57 functions now.
////////////////////////////////////////////////////////////
void PipeTblDrawTable (void);
void PipeTblEditing (void);
void PipeTblEraseTable (void);
void PipeTblFindRowData (void);
void PipeTblFindRowID (void);
void PipeTblGetBounds (void);
void PipeTblGetColumnSpacing (void);
void PipeTblGetColumnWidth (void);
void PipeTblGetCurrentField (void);
void PipeTblGetItemBounds (void);
void PipeTblGetItemFont (void);
void PipeTblGetItemInt (void);
void PipeTblGetItemPtr (void);
void PipeTblGetLastUsableRow (void);
void PipeTblGetNumberOfRows (void);
void PipeTblGetRowData (void);
void PipeTblGetRowHeight(void);
void PipeTblGetRowID (void);
void PipeTblGetSelection (void);
void PipeTblGrabFocus (void);
void PipeTblHandleEvent (void);
void PipeTblHasScrollBar (void);
void PipeTblInsertRow (void);
void PipeTblMarkRowInvalid (void);
void PipeTblMarkTableInvalid (void);
void PipeTblRedrawTable  (void);
void PipeTblReleaseFocus (void);
void PipeTblRemoveRow  (void);
void PipeTblReverseItem (void);
void PipeTblRowInvalid (void);
void PipeTblRowMasked (void);
void PipeTblRowSelectable (void);
void PipeTblRowUsable (void);
void PipeTblSelectItem  (void);
void PipeTblSetBounds (void);
void PipeTblSetColumnEditIndicator (void);
void PipeTblSetColumnMasked (void);
void PipeTblSetColumnSpacing  (void);
void PipeTblSetColumnUsable  (void);
void PipeTblSetColumnWidth  (void);
void PipeTblSetCustomDrawProcedure (void);
void PipeTblSetItemFont (void);
void PipeTblSetItemInt (void);
void PipeTblSetItemPtr (void);
void PipeTblSetItemStyle  (void);
void PipeTblSetLoadDataProcedure  (void);
void PipeTblSetRowData  (void);
void PipeTblSetRowHeight  (void);
void PipeTblSetRowID  (void);
void PipeTblSetRowMasked  (void);
void PipeTblSetRowSelectable  (void);
void PipeTblSetRowStaticHeight  (void);
void PipeTblSetRowUsable  (void);
void PipeTblSetSaveDataProcedure  (void);
void PipeTblUnhighlightSelection  (void);
void PipeTableDrawItemFuncType (void);
void PipeTableLoadDataFuncType(void);
void PipeTableSaveDataFuncType (void);

////////////////////////////////////////////////////////////
// Text Manager Library, completed 38/38 functions now.
////////////////////////////////////////////////////////////
void PipeTxtByteAttr(void);
void PipeTxtCaselessCompare (void);
void PipeTxtCharAttr (void);
void PipeTxtCharBounds(void);
void PipeTxtCharEncoding(void);
void PipeTxtCharIsAlNum (void);
void PipeTxtCharIsAlpha (void);
void PipeTxtCharIsCntrl (void);
void PipeTxtCharIsDelim (void);
void PipeTxtCharIsDigit (void);
void PipeTxtCharIsGraph (void);
void PipeTxtCharIsHardKey(void);
void PipeTxtCharIsHex (void);
void PipeTxtCharIsLower (void);
void PipeTxtCharIsPrint (void);
void PipeTxtCharIsPunct(void);
void PipeTxtCharIsSpace (void);
void PipeTxtCharIsUpper (void);
void PipeTxtCharIsValid(void);
void PipeTxtCharSize (void);

void PipeTxtCharWidth(void);
void PipeTxtCharXAttr (void);
void PipeTxtCompare (void);
void PipeTxtEncodingName (void);
void PipeTxtFindString(void);
void PipeTxtGetChar(void);
void PipeTxtGetNextChar(void);
void PipeTxtGetPreviousChar (void);
void PipeTxtGetTruncationOffset(void);
void PipeTxtMaxEncoding(void);
void PipeTxtNextCharSize(void);
void PipeTxtParamString(void);
void PipeTxtPreviousCharSize (void);
void PipeTxtReplaceStr(void);
void PipeTxtSetNextChar(void);
void PipeTxtStrEncoding(void);
void PipeTxtTransliterate (void);
void PipeTxtWordBounds (void);

////////////////////////////////////////////////////////////
// Time Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
void PipeDateAdjust(void);
void PipeDateDaysToDate (void);
void PipeDateSecondsToDate (void);
void PipeDateTemplateToAscii (void);
void PipeDateToAscii(void);
void PipeDateToDays (void);
void PipeDateToDOWDMFormat (void);
void PipeDayOfMonth (void);
void PipeDayOfWeek (void);
void PipeDaysInMonth(void);
void PipeTimeAdjust (void);
void PipeTimDateTimeToSeconds (void);
void PipeTimGetSeconds (void);
void PipeTimGetTicks (void);
void PipeTimSecondsToDateTime (void);
void PipeTimSetSeconds (void);
void PipeTimeToAscii (void);

////////////////////////////////////////////////////////////
// UI Color List Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeUIColorGetTableEntryIndex (void);
void PipeUIColorGetTableEntryRGB(void);
void PipeUIColorSetTableEntry(void);

////////////////////////////////////////////////////////////
// UI Controls Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeUIBrightnessAdjust (void);
void PipeUIContrastAdjust (void);
void PipeUIPickColor(void);

////////////////////////////////////////////////////////////
// User Interface Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipePhoneNumberLookup (void);
void PipeResLoadConstant (void);
void PipeResLoadForm (void);
void PipeResLoadMenu (void);

////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeDrvEntryPointV10 (void);
void PipeVdrvClose (void);
void PipeVdrvControl(void);
void PipeVdrvOpen (void);
void PipeVdrvStatus (void);
void PipeVdrvWrite(void);

////////////////////////////////////////////////////////////
// Window function, completed 80/80 functions now.
////////////////////////////////////////////////////////////
void PipeWinClipRectangle (void);
void PipeWinCopyRectangle (void);
void PipeWinCreateBitmapWindow(void);
void PipeWinCreateOffscreenWindow(void);
void PipeWinCreateWindow (void);
void PipeWinDeleteWindow(void);
void PipeWinDisplayToWindowPt(void);

void PipeWinDrawBitmap (void);
void PipeWinDrawChar (void);
void PipeWinDrawChars (void);
void PipeWinDrawGrayLine (void);
void PipeWinDrawGrayRectangleFrame (void);
void PipeWinDrawInvertedChars (void);
void PipeWinDrawLine (void);
void PipeWinDrawPixel (void);
void PipeWinDrawRectangle(void);
void PipeWinDrawRectangleFrame (void);
void PipeWinDrawTruncChars (void);
void PipeWinEraseChars (void);
void PipeWinEraseLine (void);
void PipeWinErasePixel (void);
void PipeWinEraseRectangle (void);
void PipeWinEraseRectangleFrame(void);
void PipeWinEraseWindow (void);
void PipeWinFillLine (void);
void PipeWinFillRectangle (void);
void PipeWinGetActiveWindow(void);
void PipeWinGetBitmap(void);
void PipeWinGetClip (void);
void PipeWinGetDisplayExtent (void);
void PipeWinGetDisplayWindow (void);
void PipeWinGetDrawWindow (void);
void PipeWinGetFirstWindow (void);
void PipeWinGetFramesRectangle (void);
void PipeWinGetPattern (void);
void PipeWinGetPatternType (void);

void PipeWinGetPixel (void);
void PipeWinGetWindowBounds(void);
void PipeWinGetWindowExtent(void);
void PipeWinGetWindowFrameRect(void);
void PipeWinIndexToRGB(void);
void PipeWinInvertChars(void);
void PipeWinInvertLine(void);
void PipeWinInvertPixel(void);
void PipeWinInvertRectangle(void);
void PipeWinInvertRectangleFrame(void);
void PipeWinModal(void);
void PipeWinPaintBitmap(void);
void PipeWinPaintChar(void);
void PipeWinPaintChars(void);
void PipeWinPaintLine(void);
void PipeWinPaintLines(void);
void PipeWinPaintPixel(void);
void PipeWinPaintPixels (void);
void PipeWinPaintRectangle (void);
void PipeWinPaintRectangleFrame(void);
void PipeWinPalette(void);
void PipeWinPopDrawState (void);
void PipeWinPushDrawState (void);
void PipeWinResetClip(void);
void PipeWinRestoreBits(void);
void PipeWinRGBToIndex(void);
void PipeWinSaveBits(void);
void PipeWinScreenLock(void);
void PipeWinScreenMode(void);
void PipeWinScreenUnlock(void);
void PipeWinScrollRectangle(void);
void PipeWinSetActiveWindow(void);
void PipeWinSetBackColor (void);
void PipeWinSetClip (void);
void PipeWinSetDrawMode (void);
void PipeWinSetDrawWindow (void);
void PipeWinSetForeColor (void);
void PipeWinSetPattern(void);
void PipeWinSetPatternType(void);
void PipeWinSetTextColor(void);
void PipeWinSetUnderlineMode(void);
void PipeWinSetWindowBounds(void);
void PipeWinValidateHandle(void);
void PipeWinWindowToDisplayPt(void);

void PipeVSetRCPFile (void);
