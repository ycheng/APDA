//
// Handler functions, ordered by reqType
//
struct GrFunction {
	void		(*func)(void);
//	GR_FUNC_NAME 	name;
} GrFunctions[] = {

////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.                  0
////////////////////////////////////////////////////////////
	PipeAlmGetAlarm,				//	0
	PipeAlmGetProcAlarm,			//		1
	PipeAlmSetAlarm,				//	2
	PipeAlmSetProcAlarm,			//		3

////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 9/9 functions now.              4
////////////////////////////////////////////////////////////
 	PipeBmpBitsSize ,				//	4
 	PipeBmpColortableSize ,				//	5
 	PipeBmpCompress ,				//	6
 	PipeBmpCreate ,					//	7
 	PipeBmpDelete ,					//	8
 	PipeBmpGetBits,					//	9
 	PipeBmpGetColortable ,				//	10
 	PipeBmpSize ,					//	11
 	PipeColorTableEntries ,				//	12

////////////////////////////////////////////////////////////
// Category Library, completed 16/16 functions now.                    13
////////////////////////////////////////////////////////////
	PipeCategoryCreateList,		//		        13
	PipeCategoryCreateListV10,		//              14
	PipeCategoryEdit,				//	15
	PipeCategoryEditV20,				//	16
	PipeCategoryEditV10,				//      17
	PipeCategoryFind,				//	18
	PipeCategoryFreeList,		//		        19
	PipeCategoryFreeListV10,		//	        20
	PipeCategoryGetName,			//	        21
	PipeCategoryGetNext,			//		22
	PipeCategoryInitialize,		//		        23
	PipeCategorySelect,			//		24
	PipeCategorySelectV10,			//	        25
	PipeCategorySetName,			//		26
	PipeCategorySetTriggerLabel,	//		        27
	PipeCategoryTruncateName,	//		        28

////////////////////////////////////////////////////////////
// Character Attributes Library, completed 6/6 functions now.           29
////////////////////////////////////////////////////////////
	 PipeChrHorizEllipsis ,				//	29
	 PipeChrIsHardKey,				//	30
	 PipeChrNumericSpace ,		        	//	31
	 PipeGetCharAttr ,				//	32
	 PipeGetCharCaselessValue ,			//	33
	 PipeGetCharSortValue ,				//	34

////////////////////////////////////////////////////////////
// Clipboad functions, completed 3/3 functions now.                     35
////////////////////////////////////////////////////////////
	PipeClipboardAddItem,		        //		35
	PipeClipboardAppendItem,	        //		36
	PipeClipboardGetItem,		        //		37

////////////////////////////////////////////////////////////
// Connection Manager Library, completed 4/4 functions now.             38
////////////////////////////////////////////////////////////
	PipeCncAddProfile,				//	38
	PipeCncDeleteProfile,				//	39
	PipeCncGetProfileInfo,				//	40
	PipeCncGetProfileList,				//	41

////////////////////////////////////////////////////////////
// Control Handle Library, completed 20/20 functions now.               42
////////////////////////////////////////////////////////////
	PipeCtlDrawControl,			//		42
	PipeCtlEnabled,				//		43
	PipeCtlEraseControl,			//		44
	PipeCtlGetLabel,			//		45
	PipeCtlGetSliderValues,		        //		46
	PipeCtlGetValue,			//		47
	PipeCtlHandleEvent,			//		48
	PipeCtlHideControl,			//		49
	PipeCtlHitControl,			//		50
	PipeCtlNewControl,			//		51
	PipeCtlNewGraphicControl,	        //		52
	PipeCtlNewSliderControl,	        //		53
	PipeCtlSetEnabled,			//		54
	PipeCtlSetLabel,			//		55
	PipeCtlSetGraphics,			//		56
	PipeCtlSetSliderValue,		        //		57
	PipeCtlSetUsable,			//		58
	PipeCtlSetValue,			//		59
	PipeCtlShowControl,			//		60
	PipeCtlValidatePointer,		        //		61

///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 6/6 functions now.          62
///////////////////////////////////////////////////////////////
	PipeDayHandleEvent,				//	62
	PipeSelectDay,				        //	63
	PipeSelectDayV10,				//	64
	PipeSelectOneTime,			        //	65
	PipeSelectTime,				        //	66
	PipeSelectTimeV33,				//	67
////////////////////////////////////////////////////////////
// DataBase Library, completed 68/68 functions now.                      68
////////////////////////////////////////////////////////////
	PipeDmArchiveRecord,			//		68
	PipeDmAttachRecord,			//		69
	PipeDmAttachResource,		//		        70
	PipeDmCloseDatabase,			//		71
	PipeDmCreateDatabase,		//		        72
	PipeDmCreateDatabaseFromImage,	//		        73
	PipeDmDatabaseInfo,			//		74
	PipeDmDatabaseProtect,		//		        75
	PipeDmDatabaseSize,			//		76
	PipeDmDeleteCategory,		//		        77
	PipeDmDeleteDatabase,		//		        78
	PipeDmDeleteRecord,			//		79
	PipeDmDetachRecord,			//		80
	PipeDmDetachResource,		//		        81
	PipeDmFindDatabase,			//		82
	PipeDmFindRecordByID,		//		        83
	PipeDmFindResource,			//		84
	PipeDmFindResourceType,		//		        85
	PipeDmFindSortPosition,		//		        86
	PipeDmFindSortPositionV10,		//	        87
	PipeDmGetAppInfoID,			//		88
	PipeDmGetDatabase,			//		89
	PipeDmGetDatabaseLocalState,	//		        90
	PipeDmGetLastErr,				//	91
	PipeDmGetNextDatabaseByTypeCreator,	//		92
	PipeDmGetRecord,				//	93
	PipeDmGetResource,			//		94
	PipeDmGetResourceIndex,		//		        95
	PipeDmGet1Resource,			//		96
	PipeDmInsertionSort,			//		97
	PipeDmMoveCategory,			//		98
	PipeDmMoveRecord,				//	99
	PipeDmNewHandle,				//	100
	PipeDmNewRecord,				//	101
	PipeDmNewResource,			//		102
	PipeDmNextOpenDatabase,		//		        103
	PipeDmNumDatabases,			//		104
	PipeDmNumRecords,				//	105
	PipeDmNumRecordsInCategory,	//		        106
	PipeDmNumResources,			//		107
	PipeDmOpenDatabase,			//		108
	PipeDmOpenDatabaseByTypeCreator,	//		109
	PipeDmOpenDatabaseInfo,		//		        110
	PipeDmOpenDBNoOvelay,		//		        111
	PipeDmPositionInCategory,	//		        112
	PipeDmQueryNextInCategory,	//		        113
	PipeDmQueryRecord,			//		114
	PipeDmQuickSort,				//	115
	PipeDmRecordInfo,				//	116
	PipeDmReleaseRecord,			//		117
	PipeDmReleaseResource,		//		        118
	PipeDmRemoveRecord,			//		119
	PipeDmRemoveResource,		//		        120
	PipeDmRemoveSecretRecord,	//		        121
	PipeDmResizeRecord,			//		122
	PipeDmResizeResource,		//		        123
	PipeDmResourceInfo,			//		124
	PipeDmResetRecordStates,	//		        125
	PipeDmSearchRecord,			//		126
	PipeDmSearchResource,		//		        127
	PipeDmSeekRecordInCategory,//		                128
	PipeDmSet,					//      129
	PipeDmSetDatabaseInfo,		//		        130
	PipeDmSetRecordInfo,			//		131
	PipeDmSetResourceInfo,		//		        132
	PipeDmStrCopy,					//	133
	PipeDmWrite,					//	134
	PipeDmWriteCheck,				//	135

////////////////////////////////////////////////////////////
// Error Manager Library, completed 6/6 functions now.                           136
////////////////////////////////////////////////////////////
	PipeErrAlert,                    //                     136
	PipeErrFatalDisplayIf,		//		        137
	PipeErrDisplayFileLineMsg,			//	138
	PipeErrFatalDisplay,			//		139
	PipeErrNonFatalDisplayIf,	//		        140
	PipeErrThrow,				//              141
////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 9/9 functions now.                       142
////////////////////////////////////////////////////////////
	PipeExgAccept,				//	        142
	PipeExgDBRead,				//	        143
	PipeExgDBWrite,				//	        144
	PipeExgDisconnect,			//	        145
	PipeExgDoDialog,			//	        146
	PipeExgPut,				//		147
	PipeExgReceive,					//	148
	PipeExgRegisterData,			//	        149
	PipeExgSend,					//	150
////////////////////////////////////////////////////////////
// Feature Manager Library, completed 7/7 functions now.                    151
////////////////////////////////////////////////////////////
	PipeFtrGet,					//	151
	PipeFtrGetByIndex,			//		152
	PipeFtrPtrFree,					//	153
	PipeFtrPtrNew,					//	154
	PipeFtrPtrResize,				//	155
	PipeFtrSet,					//	156
	PipeFtrUnregister,				//	157
////////////////////////////////////////////////////////////
// Field Processing Library, completed 52/52 functions now.                 158
////////////////////////////////////////////////////////////
	PipeFldCalcFieldHeight,		//		        158
	PipeFldCompactText,			//		159
	PipeFldCopy,					//	160
	PipeFldCut,				//		161
	PipeFldDelete,					//	162
	PipeFldDirty,					//	163
	PipeFldDrawField,				//	164
	PipeFldEraseField,			//		165
	PipeFldFreeMemory,			//		166
	PipeFldGetAttributes,		//		        167
	PipeFldGetBounds,				//	168
	PipeFldGetFont,				//		169
	PipeFldGetInsPtPosition,	//		        170
	PipeFldGetMaxChars,			//		171
	PipeFldGetNumberOfBlankLines,	//		        172
	PipeFldGetScrollPosition,	//		        173
	PipeFldGetScrollValues,		//		        174
	PipeFldGetSelection,			//		175
	PipeFldGetTextAllocatedSize,	//		        176
	PipeFldGetTextHandle,		//		        177
	PipeFldGetTextHeight,		//		        178
	PipeFldGetTextLength,		//		        179
	PipeFldGetTextPtr,			       //	180
	PipeFldGetVisibleLines,		//		        181
	PipeFldGrabFocus,				//	182
	PipeFldHandleEvent,			//		183
	PipeFldInsert,					//	184
	PipeFldMakeFullyVisible,	//		        185
	PipeFldNewField,				//	186
	PipeFldPaste,					//	187
	PipeFldRecalculateField,	//		        188
	PipeFldReleaseFocus,			//		189
	PipeFldScrollable,			//		190
	PipeFldScrollField,			//		191
	PipeFldSendChangeNotification,	//		        192
	PipeFldSendHeightChangeNotification,	//		193
	PipeFldSetAttributes,		//	        	194
	PipeFldSetBounds,				//	195
	PipeFldSetDirty,				//	196
	PipeFldSetFont,				//		197
	PipeFldSetInsertionPoint,	//		        198
	PipeFldSetInsPtPosition,	//		        199
	PipeFldSetMaxChars,			//		200
	PipeFldSetScrollPosition,	//		        201
	PipeFldSetSelection,			//		202
	PipeFldSetText,				//		203
	PipeFldSetTextAllocatedSize,	//		        204
	PipeFldSetTextHandle,		//		        205
	PipeFldSetTextPtr,			//		206
	PipeFldSetUsable,				//	207
	PipeFldUndo,					//	208
	PipeFldWordWrap,				//	209

////////////////////////////////////////////////////////////
// File Streaming Library, completed 16/16 functions now.               210
////////////////////////////////////////////////////////////
	PipeFileClearerr,				//	210
	PipeFileClose,					//	211
	PipeFileControl,				//	212
	PipeFileDelete,				//		213
	PipeFileDmRead,				//		214
	PipeFileEOF,					//	215
	PipeFileError,					//	216
	PipeFileFlush,					//	217
	PipeFileGetLastError,		//		        218
	PipeFileOpen,					//	219
	PipeFileRead,					//	220
	PipeFileRewind,				//		221
	PipeFileSeek,					//	222
	PipeFileTell,					//	223
	PipeFileTruncate,				//	224
	PipeFileWrite,					//	225

////////////////////////////////////////////////////////////
// Find Processing Library, completed 4/4 functions now.                     226
////////////////////////////////////////////////////////////
	PipeFindDrawHeader,				//	226
	PipeFindGetLineBounds,				//	227
	PipeFindSaveMatch,				//	228
	PipeFindStrInStr,				//	229
////////////////////////////////////////////////////////////
// Float Manager Library, completed 12/12 functions now.                     230
////////////////////////////////////////////////////////////
	PipeFplAdd,					//	230
	PipeFplAToF,					//	231
	PipeFplBase10Info,				//	232
	PipeFplDiv,					//	233
	PipeFplFloatToLong,				//	234
	PipeFplFloatToULong,				//	235
	PipeFplFree,					//	236
	PipeFplFToA,					//	237
	PipeFplInit,					//	238
	PipeFplLongToFloat	,			//	239
	PipeFplMul	,				//	240
	PipeFplSub,					//	241
////////////////////////////////////////////////////////////
// Font Processing Library, completed 18/18 functions now.                   242
////////////////////////////////////////////////////////////
	PipeFntAverageCharWidth,	//		        242
	PipeFntBaseLine,			//		243
	PipeFntCharHeight,			//		244
	PipeFntCharsInWidth,			//		245
	PipeFntCharsWidth,			//		246
	PipeFntCharWidth,				//	247
	PipeFntDefineFont,			//		248
	PipeFntGetFont,				//		249
	PipeFntGetFontPtr,				//	250
	PipeFntGetScrollValues,				//	251
	PipeFntLineHeight,			//		252
	PipeFntLineWidth,				//	253
	PipeFntSetFont,				//		254
	PipeFntWidthToOffset,				//	255
	PipeFntWordWrap,				//	256
	PipeFntWordWrapReverseNLines,			//	257
	PipeFontSelect,					//	258
	// below index must +1


////////////////////////////////////////////////////////////
// Form Processing Library, completed 65/65 functions now.              259
////////////////////////////////////////////////////////////
	PipeFrmAlert,					//	259
	PipeFrmCloseAllForms,		//		        260
	PipeFrmCopyLabel,				//	261
	PipeFrmCopyTitle,				//	262
	PipeFrmCustomAlert,			//		263
	PipeFrmCustomResponseAlert,	//		        264
	PipeFrmDeleteForm,			//		265
	PipeFrmDispatchEvent,		//		        266
	PipeFrmDoDialog,				//	267
	PipeFrmDrawForm,				//	268
	PipeFrmEraseForm,				//	269
	PipeFrmGetActiveForm,		//		        270
	PipeFrmGetActiveFormID,		//		        271
	PipeFrmGetControlGroupSelection,	//		272
	PipeFrmGetControlValue,		//		        273
	PipeFrmGetFirstForm,			//		274
	PipeFrmGetFocus,				//	275
	PipeFrmGetFormBounds,		//		        276
	PipeFrmGetFormId,				//	277
	PipeFrmGetFormPtr,			//		278
	PipeFrmGetGadgetData,		//		        279
	PipeFrmGetLabel,				//	280
	PipeFrmGetNumberOfObjects,	//		        281
	PipeFrmGetObjectBounds,		//		        282
	PipeFrmGetObjectId,			//		283
	PipeFrmGetObjectIndex,		//		        284
	PipeFrmGetObjectPosition,	//		        285
	PipeFrmGetObjectPtr,			//		286
	PipeFrmGetObjectType,		//		        287
	PipeFrmGetTitle,				//	288
	PipeFrmGetWindowHandle,		//		        289
	PipeFrmGotoForm,				//	290
	PipeFrmHandleEvent,			//		291
	PipeFrmHelp,					//	292
	PipeFrmHideObject,			//		293
	PipeFrmInitForm,				//	294
	PipeFrmNewBitmap,				//	295
	PipeFrmNewForm,				//		296
	PipeFrmNewGadget,				//	297
	PipeFrmNewGsi,					//	298
	PipeFrmNewLabel,				//	299
	PipeFrmPointInTitle,			//		300
	PipeFrmPopupForm,				//	301
	PipeFrmRemoveObject,			//		302
	PipeFrmRestoreActiveState,	//		        303
	PipeFrmReturnToForm,			//		304
	PipeFrmSaveActiveState,		//		        305
	PipeFrmSaveAllForms,			//		306
	PipeFrmSetActiveForm,		//		        307
	PipeFrmSetCategoryLabel,	//		        308
	PipeFrmSetControlGroupSelection,	//		309
	PipeFrmSetControlValue,		//		        310
	PipeFrmSetEventHandler,		//		        311
	PipeFrmSetFocus,				//	312
	PipeFrmSetGadgetData,		//		        313
	PipeFrmSetGadgetHandler,	//		        314
	PipeFrmSetMenu,				//		315
	PipeFrmSetObjectBounds,		//		        316
	PipeFrmSetObjectPosition,	//		        317
	PipeFrmSetTitle,				//	318
	PipeFrmShowObject,			//		319
	PipeFrmUpdateForm,			//		320
	PipeFrmUpdateScrollers,		//		        321
	PipeFrmValidatePtr,			//		322
	PipeFrmVisible,				//		323

////////////////////////////////////////////////////////////
// Graffiti Manager Library, completed 19/19 functions now.             324
////////////////////////////////////////////////////////////
	PipeGrfAddMacro,
	PipeGrfAddPoint,				//	324
	PipeGrfCleanState,			//		325
	PipeGrfDeleteMacro,			//	        326
	PipeGrfFilterPoints,			//	        327
	PipeGrfFindBranch,			//	        328
	PipeGrfFlushPoints,			//		329
	PipeGrfGetAndExpandMacro,		//	        330
	PipeGrfGetGlyphMapping,			//	        331
	PipeGrfGetMacro,			//	        332
	PipeGrfGetMacroName,			//	        333
	PipeGrfGetNumPoints,			//		334
	PipeGrfGetPoint,				//	335
	PipeGrfGetState,				//	336
	PipeGrfInitState,				//	337
	PipeGrfMatch,				//	        338
	PipeGrfMatchGlyph,			//	        339
	PipeGrfProcessStroke,		//		        340
	PipeGrfSetState,				//	341

//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.      342
//////////////////////////////////////////////////////////////////
	PipeGsiEnable,					//	342
	PipeGsiEnabled,				//		343
	PipeGsiInitialize,			//		344
	PipeGsiSetLocation,			//		345
	PipeGsiSetShiftState,		//		        346

////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.                347
////////////////////////////////////////////////////////////
	PipeInsPtEnable,				//	347
	PipeInsPtEnabled,				//	348
	PipeInsPtGetHeight,			//		349
	PipeInsPtGetLocation,		//		        350
	PipeInsPtSetHeight,			//		351
	PipeInsPtSetLocation,		//		        352

////////////////////////////////////////////////////////////
// Key Manager Library, completed 3/3 functions now.                    353
////////////////////////////////////////////////////////////
	PipeKeyCurrentState,			//		353
	PipeKeyRates,				//		354
	PipeKeySetMask,				//		355
////////////////////////////////////////////////////////////
// IR Library, completed 22/22 functions now.                           356
////////////////////////////////////////////////////////////
	PipeIrAdvanceCredit,			//		356
	PipeIrBind,				//		357
	PipeIrClose,				//		358
	PipeIrConnectIrLap,			//		359
	PipeIrConnectReq,			//		360
	PipeIrConnectRsp,			//		361
	PipeIrDataReq,				//		362
	PipeIrDisconnectIrLap	,		//		363
	PipeIrDiscoverReq,			//		364
	PipeIrIsIrLapConnected	,		//		365
	PipeIrIsMediaBusy	,		//		366
	PipeIrIsNoProgress,			//		367
	PipeIrIsRemoteBusy,			//		368
	PipeIrLocalBusy,			//		369
	PipeIrMaxRxSize,			//		370
	PipeIrMaxTxSize,			//		371
	PipeIrOpen	,			//		372
	PipeIrSetConTypeLMP,			//		373
	PipeIrSetConTypeTTP	,		//		374
	PipeIrSetDeviceInfo,			//		375
	PipeIrTestReq	,			//		376
	PipeIrUnbind	,			//		377
////////////////////////////////////////////////////////////
// IAS Library, completed 14/14 functions now.                          378
////////////////////////////////////////////////////////////
	PipeIrIAS_Add,				//		378
	PipeIrIAS_GetInteger,			//		379
	PipeIrIAS_GetIntLsap,			//		380
	PipeIrIAS_GetObjectID,			//		381
	PipeIrIAS_GetOctetString,		//		382
	PipeIrIAS_GetOctetStringLen,		//		383
	PipeIrIAS_GetType	,		//		384
	PipeIrIAS_GetUserString	,		//		385
	PipeIrIAS_GetUserStringCharSet,		//		386
	PipeIrIAS_GetUserStringLen,		//		387
	PipeIrIAS_Next,				//		388
	PipeIrIAS_Query,			//		389
	PipeIrIAS_SetDeviceName	,		//		390
	PipeIrIAS_StartResult	,		//		391
////////////////////////////////////////////////////////////
// List Handle Library, completed 17/17 functions now.                  392
////////////////////////////////////////////////////////////
	PipeLstDrawList,				//	393
	PipeLstEraseList,				//	394
	PipeLstGetNumberOfItems,	//		        395
	PipeLstGetSelection,			//		396
	PipeLstGetSelectionText,	//		        397
	PipeLstGetVisibleItems,		//		        398
	PipeLstHandleEvent,			//		399
	PipeLstMakeItemVisible,		//		        400
	PipeLstNewList,				//		410
	PipeLstPopupList,				//	411
	PipeLstScrollList,			//		412
	PipeLstSetDrawFunction,		//		        413
	PipeLstSetHeight,				//	414
	PipeLstSetListChoices,		//		        415
	PipeLstSetPosition,			//		416
	PipeLstSetSelection,			//		417
	PipeLstSetTopItem,			//		418

////////////////////////////////////////////////////////////
// Memory Manager Library, completed 44/44 functions now.               419
////////////////////////////////////////////////////////////
	PipeMemCardInfo,				//	419
	PipeMemCmp,					//	420
	PipeMemDebugMode,				//	421
	PipeMemHandleCardNo,			//		422
	PipeMemHandleDataStorage,	//		        423
	PipeMemHandleFree,			//		424
	PipeMemHandleHeapID,			//		425
	PipeMemHandleLock,			//		426
	PipeMemHandleNew,				//	427
	PipeMemHandleResize,			//		428
	PipeMemHandleSetOwner,		//		        429
	PipeMemHandleSize,			//		430
	PipeMemHandleToLocalID,		//		        431
	PipeMemHandleUnlock,			//		432
	PipeMemHeapCheck,				//	433
	PipeMemHeapCompact,			//		434
	PipeMemHeapDynamic,			//		435
	PipeMemHeapFlags,				//	436
	PipeMemHeapFreeBytes,		//		        437
	PipeMemHeapID,					//	438
	PipeMemHeapScramble,			//		439
	PipeMemHeapSize,				//	440
	PipeMemLocalIDKind,			//		441
	PipeMemLocaIDToGlobal,		//		        442
	PipeMemLocalIDToLockedPtr,	//		        443
	PipeMemLocalIDToPtr,			//		444
	PipeMemMove,					//	445
	PipeMemNumCards,				//	446
	PipeMemNumHeaps,				//	447
	PipeMemNumRAMHeaps,			//		448
	PipeMemPtrCardNo,				//	449
	PipeMemPtrDataStorage,		//		        450
	PipeMemPtrFree,				//		451
	PipeMemPtrHeapID,				//	452
	PipeMemPtrNew,					//	453
	PipeMemPtrRecoverHandle,	//		        454
	PipeMemPtrResize,				//	455
	PipeMemPtrSetOwner,			//		456
	PipeMemPtrSize,				//		457
	PipeMemPtrToLocalID,			//		458
	PipeMemPtrUnlock,				//	459
	PipeMemSet,				//		460
	PipeMemSetDebugMode,			//		461
	PipeMemStoreInfo,			//		462

////////////////////////////////////////////////////////////
// Menu Processing Library, completed 14/14 functions now               463
////////////////////////////////////////////////////////////
	PipeMenuAddItem,				//	463
	PipeMenuCmdBarAddButton,	//		        464
	PipeMenuCmdBarDisplay,		//		        465
	PipeMenuCmdBarGetButtonData,	//		        466
	PipeMenuDispose,				//	467
	PipeMenuDrawMenu,				//	468
	PipeMenuEraseStatus,			//		469
	PipeMenuGetActiveMenu,		//		        470
	PipeMenuHandleEvent,			//		471
	PipeMenuHideItem,				//	472
	PipeMenuInit,					//	473
	PipeMenuSetActiveMenu,		//		        474
	PipeMenuSetActiveMenuRscID,	//		        475
	PipeMenuShowItem,				//	476

////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 3/3 functions now.           477
////////////////////////////////////////////////////////////
	PipeCrc16CalcBlock,				//	477
	PipeIntlGetRoutineAddress,			//	478
	PipeLocGetNumberSeparators,			//	479
////////////////////////////////////////////////////////////
// Modem Manager Library, completed 2/2 functions now.                  480
////////////////////////////////////////////////////////////
	PipeMdmDial,					//	480
	PipeMdmHangUp,					//	481
////////////////////////////////////////////////////////////
// Net Library, completed 44/44 functions now.                          482
////////////////////////////////////////////////////////////
	PipeNetHToNL,				//	482
	PipeNetHToNS,					//	483
	PipeNetLibAddrAToIN,				//	484
	PipeNetLibAddrINToA,				//	485
	PipeNetLibClose,				//	486
	PipeNetLibConnectionRefresh,			//	487
	PipeNetLibDmReceive,				//	488
	PipeNetLibFinishCloseWait,			//	489
	PipeNetLibGetHostByAddr,			//	490
	PipeNetLibGetHostByName,			//	491
	PipeNetLibGetMailExchangeByName,		//	492
	PipeNetLibGetServByName,			//	493
	PipeNetLibIFAttach,				//	494
	PipeNetLibIFDetach,				//	495
	PipeNetLibIFDown,				//	496
	PipeNetLibIFGet,				//	497
	PipeNetLibIFSettingGet,				//	498
	PipeNetLibIFSettingSet,				//	499
	PipeNetLibIFUp,					//	500
	PipeNetLibMaster,				//	501
	PipeNetLibOpen,					//	502
	PipeNetLibOpenCount,				//	503
	PipeNetLibReceive,				//	504
	PipeNetLibReceivePB,				//	505
	PipeNetLibSelect,				//	506
	PipeNetLibSend,					//	507
	PipeNetLibSendPB,				//	508
	PipeNetLibSettingGet,				//	509
	PipeNetLibSettingSet,				//	510
	PipeNetLibSocketAddr,				//	511
	PipeNetLibSocketBind,				//	512
	PipeNetLibSocketClose,				//	513
	PipeNetLibSocketConnect,				//	514
	PipeNetLibSocketListen,				//	515
	PipeNetLibSocketOpen,				//	516
	PipeNetLibSocketOptionGet,			//	517
	PipeNetLibSocketOptionSet,			//	518
	PipeNetLibSocketShutdown,			//	519
	PipeNetLibTracePrintF,				//	520
	PipeNetNToHL,					//	521
	PipeNetNToHS,					//	522

////////////////////////////////////////////////////////////
// Network Utilities Library, completed 3/3 functions now.              523
////////////////////////////////////////////////////////////
	PipeNetUReadN,					//	523
	PipeNetUTCPOpen,				//	524
	PipeNetUWriteN,					//	525
////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 21/21 functions now.           526
////////////////////////////////////////////////////////////
	PipeSrmClearErr,				//	526
	PipeSrmClose,					//	527
	PipeSrmControl,					//	528
	PipeSrmGetDeviceCount,				//	529
	PipeSrmGetDeviceInfo,				//	530
	PipeSrmGetStatus,				//	531
	PipeSrmOpen,					//	532
	PipeSrmOpenBackground,				//	533
	PipeSrmPrimeWakeupHandler,			//	534
	PipeSrmReceive,					//	535
	PipeSrmReceiveCheck,				//	536
	PipeSrmReceiveFlush,				//	537
	PipeSrmReceiveWait,				//	538
	PipeSrmReceiveWindowClose,			//	539
	PipeSrmReceiveWindowOpen,			//	540
	PipeSrmSend,					//	541
	PipeSrmSendCheck ,				//	542
	PipeSrmSendFlush,				//	543
	PipeSrmSendWait,				//	544
	PipeSrmSetReceiveBuffer,			//	545
	PipeSrmSetWakeupHandler,			//	546


////////////////////////////////////////////////////////////
// Notification Manager Library, completed 4/4 functions now.          547
////////////////////////////////////////////////////////////
	PipeSysNotifyBroadcast,				//	547
	PipeSysNotifyBroadcastDeferred,			//	548
	PipeSysNotifyRegister,				//	549
	PipeSysNotifyUnregister,			//	550

////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 7/7 functions now.               551
////////////////////////////////////////////////////////////
	PipeOmGetCurrentLocale,				//	551
	PipeOmGetIndexedLocale,				//	552
	PipeOmGetRoutineAddress,			//	553
	PipeOmGetSystemLocale,				//	554
	PipeOmLocaleToOverlayDBName,			//	555
	PipeOmOverlayDBNameToLocale,			//	556
	PipeOmSetSystemLocale,				//	557


////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.                      558
////////////////////////////////////////////////////////////
	PipePwdExists,					//	558
	PipePwdRemove,					//	559
	PipePwdSet,					//	560
	PipePwdVerify,				//		561

////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.                   562
////////////////////////////////////////////////////////////
	PipePenCalibrate,				//	562
	PipePenResetCalibrate,		//		        563

////////////////////////////////////////////////////////////
// Preferences Library, completed 9/9 functions now.                    564
////////////////////////////////////////////////////////////
	PipePrefGetAppPreferences,	//		        564
	PipePrefGetAppPreferencesV10,	//		        565
	PipePrefGetPreference,		//		        566
	PipePrefGetPreferences,		//		        567
	PipePrefOpenPreferenceDBV10,			//	568
	PipePrefSetAppPreferences,	//		        569
	PipePrefSetAppPreferencesV10,	//		        570
	PipePrefSetPreference,		//		        571
	PipePrefSetPreferences,		//		        572

///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 2/2 functions now.     573
///////////////////////////////////////////////////////////////////
	PipeSecSelectViewStatus,		//		573
	PipeSecVerifyPW,			//		574

////////////////////////////////////////////////////////////
// Progress Manager Library, completed 6/6 functions now.               575
////////////////////////////////////////////////////////////
	PipePrgHandleEvent,			//		575
	PipePrgStartDialog,			//		576
	PipePrgStartDialogV31,			//		577
	PipePrgStopDialog,			//		578
	PipePrgUpdateDialog,			//		579
	PipePrgUserCancel,			//		580

////////////////////////////////////////////////////////////
// Rectangle Library, completed 6/6 functions now.                      581
////////////////////////////////////////////////////////////
	PipeRctCopyRectangle,		//		        581
	PipeRctGetIntersection,			//		582
	PipeRctInsetRectangle,		//		        583
	PipeRctOffsetRectangle,			//		584
	PipeRctPtInRectangle,		//		        585
	PipeRctSetRectangle,			//		586

////////////////////////////////////////////////////////////
// Script Plugin Library, completed 1/1 functions now.                  587
////////////////////////////////////////////////////////////
	PipeScriptPluginSelectorProc,			//	587

////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 4/4 functions now.                     588
////////////////////////////////////////////////////////////
	PipeSclDrawScrollBar,		//		        588
	PipeSclGetScrollBar,			//		589
	PipeSclHandleEvent,			//		590
	PipeSclSetScrollBar,			//		591

////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 8/8 functions now.          592
////////////////////////////////////////////////////////////
	PipeDrvEntryPoint,			//		592
	PipeSdrvClose,				//		593
	PipeSdrvControl,			//		594
	PipeSdrvISP,				//		595
	PipeSdrvOpen,			//	        	596
	PipeSdrvReadChar,			//		597
	PipeSdrvStatus,				//		598
	PipeSdrvWriteChar,			//		599

////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 10/10 functions now.          600
////////////////////////////////////////////////////////////
	PipeSlkClose,					//	600
	PipeSlkCloseSocket,				//	601
	PipeSlkFlushSocket,				//	602
	PipeSerOpen,					//	603
	PipeSlkOpenSocket,				//	604
	PipeSlkReceivePacket,			//		605
	PipeSlkSendPacket,			//		606
	PipeSlkSetSocketListener,			//	607
	PipeSerSendFlush,				//	608
	PipeSlkSocketSetTimeout,		//		609

////////////////////////////////////////////////////////////
// Serial Manager Library, completed 17/17 functions now.               610
////////////////////////////////////////////////////////////
	PipeSerClearErr,				//	610
	PipeSerClose,				//		611
	PipeSerControl,					//	612
	PipeSerGetSettings,				//	613
	PipeSerGetStatus,			//		614
	PipeSerOpen,			//		        615
	PipeSerReceive,					//	616
	PipeSerReceive10,				//	617
	PipeSerReceiveCheck,			//		618
	PipeSerReceiveFlush,				//	619
	PipeSerReceiveWait,		        //		620
	PipeSerSend,				//		621
	PipeSerSend10,			//		622
	PipeSerSendFlush,			//		623
	PipeSerSendWait,			//		624
	PipeSerSetReceiveBuffer,		//		625
	PipeSerSetSettings,	        	//		626

////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 4/4 functions now.           627
////////////////////////////////////////////////////////////
	PipeGetSize,			//		        627
	PipeGetSpace,					//	628
	PipeWriteBlock,				//		629
	PipeWriteByte,				//		630

////////////////////////////////////////////////////////////
// Sound Manager Library, completed 6/6 functions now.                  631
////////////////////////////////////////////////////////////
	PipeSndCreateMidiList,			//		631
	PipeSndDoCmd,					//	632
	PipeSndGetDefaultVolume,		//		633
	PipeSndPlaySmf,				//		634
	PipeSndPlaySmfResource,			//		635
	PipeSndPlaySystemSound,			//		636

////////////////////////////////////////////////////////////
// Standard IO Library, completed 5/5 functions now.                    637
////////////////////////////////////////////////////////////
	PipeSioClearScreen,			//		637
	PipeSioExecCommand,			//		638
	PipeSioFree,				//		639
	PipeSioHandleEvent,			//		640
	PipeSioInit,				//		641

////////////////////////////////////////////////////////////
// String Manager Library, completed 19/19 functions now.               642
////////////////////////////////////////////////////////////
	PipeStrAToI,					//	642
	PipeStrCaselessCompare,		//		        643
	PipeStrCat,				//		644
	PipeStrChr,				//		645
	PipeStrCompare,				//		646
	PipeStrCopy,				//		647
	PipeStrDelocalizeNumber,	//		        648
	PipeStrIToA,				//		649
	PipeStrIToH,				//		650
	PipeStrLen,				//		651
	PipeStrLocalizeNumber,		//	                652
	PipeStrNCaselessCompare,	//		        653
	PipeStrNCat,				//		654
	PipeStrNCompare,			//		655
	PipeStrNCopy,					//	656
	PipeStrPrintF,					//	657
	PipeStrStr,				//		658
	PipeStrToLower,				//		659
	PipeStrVPrintF,				//		660

////////////////////////////////////////////////////////////
// System Dialogs Library, completed 3/3 functions now.                 661
////////////////////////////////////////////////////////////
	PipeSysAppLauncherDialog,		//		661
	PipeSysFatalAlert,				//	662
	PipeSysGraffitiReferenceDialog,		//		663

//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 25/25 functions now.         664
//////////////////////////////////////////////////////////////
	PipeEvtAddEventToQueue,		//		        664
	PipeEvtAddUniqueEventToQueue,		//		665
	PipeEvtCopyEvent,			//		666
	PipeEvtDequeuePenPoint,			//		667
	PipeEvtDequeuePenStrokeInfo,		//		668
	PipeEvtEnableGraffiti,				//	669
	PipeEvtEnqueueKey,			//		670
	PipeEvtEventAvail,			//		671
	PipeEvtFlushKeyQueue,		//		        672
	PipeEvtFlushNextPenStroke,		//		673
	PipeEvtFlushPenQueue,			//		674
	PipeEvtGetEvent,			//		675
	PipeEvtGetPen,		//		                676
	PipeEvtGetPenBtnList,				//	677
	PipeEvtGetSilkscreenAreaList,			//	678
	PipeEvtKeydownIsVirtual,		//		679
	PipeEvtKeyQueueEmpty,		//		        680
	PipeEvtKeyQueueSize,				//	681
	PipeEvtPenQueueSize,			//		682
	PipeEvtProcessSoftKeyStroke,		//		683
	PipeEvtResetAutoOffTimer,		//		684
	PipeEvtSetAutoOffTimer,			//		685
	PipeEvtSetNullEventTick,		//		686
	PipeEvtSysEventAvail,			//		687
	PipeEvtWakeup,			        //		688

////////////////////////////////////////////////////////////
// System Manager Library, completed 33/33 functions now.               689
////////////////////////////////////////////////////////////
	PipeSysAppLaunch,				//      689
	PipeSysBatteryInfo,			//		690
	PipeSysBatteryInfoV20,		//		        691
	PipeSysBinarySearch,		//		        692
	PipeSysBroadcastActionCode,		//		693
	PipeSysCopyStringResource,	//		        694
	PipeSysCreateDataBaseList,		//		695
	PipeSysCreatePanelList,	//		                696
	PipeSysCurAppDatabase,				//	697
	PipeSysErrString,			//		698
	PipeSysFormPointerArrayToStrings,		//	699
	PipeSysGetOSVersionString,		//		700
	PipeSysGetROMToken,			//		701
	PipeSysGetStackInfo,				//	702
	PipeSysGetTrapAddress,			//		703
	PipeSysGraffitiReferenceDialog,		//		704
	PipeSysGremlins,		//		        705
	PipeSysHandleEvent,		//		        706
	PipeSysInsertionSort,	//		                707
	PipeSysKeyboardDialog,		//		        708
	PipeSysKeyboardDialogV10,	//		        709
	PipeSysLibFind,				//		710
	PipeSysLibLoad,					//	711
	PipeSysLibRemove,				//	712
	PipeSysQSort,		//		                713
	PipeSysRandom,				//		714
	PipeSysReset,			//		        715
	PipeSysSetAutoOffTime,		//		        716
	PipeSysSetTrapAddress,		//		        717
	PipeSysStringByIndex,		//		        718
	PipeSysTaskDelay,		//		        719
	PipeSysTicksPerSecond,		//		        720
	PipeSysUIAppSwitch,		//		        721

////////////////////////////////////////////////////////////
// Table Library, completed 57/57 functions now.                        722
////////////////////////////////////////////////////////////
	PipeTblDrawTable,				//	722
	PipeTblEditing,				//		723
	PipeTblEraseTable,			//		724
	PipeTblFindRowData,			//		725
	PipeTblFindRowID,				//	726
	PipeTblGetBounds,				//	727
	PipeTblGetColumnSpacing,	//		        728
	PipeTblGetColumnWidth,		//		        729
	PipeTblGetCurrentField,		//		        730
	PipeTblGetItemBounds,		//		        731
	PipeTblGetItemFont,			//		732
	PipeTblGetItemInt,			//		733
	PipeTblGetItemPtr,			//		734
	PipeTblGetLastUsableRow,	//		        735
	PipeTblGetNumberOfRows,		//		        736
	PipeTblGetRowData,			//		737
	PipeTblGetRowHeight,			//		738
	PipeTblGetRowID,				//	739
	PipeTblGetSelection,			//		740
	PipeTblGrabFocus,				//	741
	PipeTblHandleEvent,			//		742
	PipeTblHasScrollBar,			//		743
	PipeTblInsertRow,				//	744
	PipeTblMarkRowInvalid,		//		        745
	PipeTblMarkTableInvalid,	//		        746
	PipeTblRedrawTable,			//		747
	PipeTblReleaseFocus,			//		748
	PipeTblRemoveRow,				//	749
	PipeTblReverseItem,			//		750
	PipeTblRowInvalid,			//		751
	PipeTblRowMasked,				//	752
	PipeTblRowSelectable,		//		        753
	PipeTblRowUsable,				//	754
	PipeTblSelectItem,			//		755
	PipeTblSetBounds,				//	756
	PipeTblSetColumnEditIndicator,	//		        757
	PipeTblSetColumnMasked,		//		        758
	PipeTblSetColumnSpacing,	//		        759
	PipeTblSetColumnUsable,		//		        760
	PipeTblSetColumnWidth,		//		        761
	PipeTblSetCustomDrawProcedure,	//		        762
	PipeTblSetItemFont,			//		763
	PipeTblSetItemInt,			//		764
	PipeTblSetItemPtr,			//		765
	PipeTblSetItemStyle,			//		766
	PipeTblSetLoadDataProcedure,	//		        767
	PipeTblSetRowData,			//		768
	PipeTblSetRowHeight,			//		769
	PipeTblSetRowID,				//	770
	PipeTblSetRowMasked,			//		771
	PipeTblSetRowSelectable,	//		        772
	PipeTblSetRowStaticHeight,	//		        773
	PipeTblSetRowUsable,			//		774
	PipeTblSetSaveDataProcedure,	//		        775
	PipeTblUnhighlightSelection,			//	776
	PipeTableDrawItemFuncType,	//		        777
	PipeTableLoadDataFuncType,	//		        778
	PipeTableSaveDataFuncType,	//		        779

////////////////////////////////////////////////////////////
// Text Manager Library, completed 38/38 functions now.                 780
////////////////////////////////////////////////////////////
	PipeTxtByteAttr,				//	780
	PipeTxtCaselessCompare,			//		781
	PipeTxtCharAttr,		//		        782
	PipeTxtCharBounds,	//		                783
	PipeTxtCharEncoding,				//	784
	PipeTxtCharIsAlNum,			//		785
	PipeTxtCharIsAlpha,			//		786
	PipeTxtCharIsCntrl,			//		787
	PipeTxtCharIsDelim,			//		788
	PipeTxtCharIsDigit,			//		789
	PipeTxtCharIsGraph,			//		790
	PipeTxtCharIsHardKey,				//	791
	PipeTxtCharIsHex,				//	792
	PipeTxtCharIsLower,			//		793
	PipeTxtCharIsPrint,			//		794
	PipeTxtCharIsPunct,				//	795
	PipeTxtCharIsSpace,			//		796
	PipeTxtCharIsUpper,			//		797
	PipeTxtCharIsValid,				//	798
	PipeTxtCharSize,				//	799

	PipeTxtCharWidth,				//	800
	PipeTxtCharXAttr,			//		801
	PipeTxtCompare,		//		                802
	PipeTxtEncodingName,	//		                803
	PipeTxtFindString,				//	804
	PipeTxtGetChar,				//		805
	PipeTxtGetNextChar,		//		        806
	PipeTxtGetPreviousChar,				//	807
	PipeTxtGetTruncationOffset,		//		808
	PipeTxtMaxEncoding,			//		809
	PipeTxtNextCharSize,			//		810
	PipeTxtParamString,		//	        	811
	PipeTxtPreviousCharSize,	//		        812
	PipeTxtReplaceStr,				//	813
	PipeTxtSetNextChar,				//	814
	PipeTxtStrEncoding,		//		        815
	PipeTxtTransliterate,				//	816
	PipeTxtWordBounds,			//		817

////////////////////////////////////////////////////////////
// Time Manager Library, completed 17/17 functions now.                 818
////////////////////////////////////////////////////////////
	PipeDateAdjust,				//		818
	PipeDateDaysToDate,			//		819
	PipeDateSecondsToDate,		//		        820
	PipeDateTemplateToAscii,	//		        821
	PipeDateToAscii,				//	822
	PipeDateToDays,				//		823
	PipeDateToDOWDMFormat,		//		        824
	PipeDayOfMonth,				//		825
	PipeDayOfWeek,					//      826
	PipeDaysInMonth,				//	827
	PipeTimeAdjust,				//		828
	PipeTimDateTimeToSeconds,	//		        829
	PipeTimGetSeconds,			//		830
	PipeTimGetTicks,				//	831
	PipeTimSecondsToDateTime,	//		        832
	PipeTimSetSeconds,			//		833
	PipeTimeToAscii,				//	834

////////////////////////////////////////////////////////////
// UI Color List Library, completed 3/3 functions now.                  835
////////////////////////////////////////////////////////////
	PipeUIColorGetTableEntryIndex,			//      835
	PipeUIColorGetTableEntryRGB,		//		836
	PipeUIColorSetTableEntry,		//		837

////////////////////////////////////////////////////////////
// UI Controls Library, completed 3/3 functions now.                    838
////////////////////////////////////////////////////////////
	PipeUIBrightnessAdjust,			//		838
	PipeUIContrastAdjust,				//	839
	PipeUIPickColor,				//	840

////////////////////////////////////////////////////////////
// User Interface Library, completed 4/4 functions now.                 841
////////////////////////////////////////////////////////////
	PipePhoneNumberLookup,			//		841
	PipeResLoadConstant,				//	842
	PipeResLoadForm,				//	843
	PipeResLoadMenu,			//		844

////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 6/6 functions now.         845
////////////////////////////////////////////////////////////
	PipeDrvEntryPointV10,			//		845
	PipeVdrvClose,				//		846
	PipeVdrvControl,				//	847
	PipeVdrvOpen,			//		        848
	PipeVdrvStatus,				//		849
	PipeVdrvWrite,				//		850

////////////////////////////////////////////////////////////
// Window function, completed 80/80 functions now.                      851
////////////////////////////////////////////////////////////
	PipeWinClipRectangle,			//		851
	PipeWinCopyRectangle,				//	852
	PipeWinCreateBitmapWindow,		//		853
	PipeWinCreateOffscreenWindow,			//      854
	PipeWinCreateWindow,				//      855
	PipeWinDeleteWindow,				//	856
	PipeWinDisplayToWindowPt,		//		857
	PipeWinDrawBitmap,			//              858
	PipeWinDrawChar,				//	859
	PipeWinDrawChars,				//	860
	PipeWinDrawGrayLine,			//		861
	PipeWinDrawGrayRectangleFrame,	//		        862
	PipeWinDrawInvertedChars,	//		        863
	PipeWinDrawLine,				//	864
	PipeWinDrawPixel,				//	865
	PipeWinDrawRectangle,		//		        866
	PipeWinDrawRectangleFrame,	//		        867
	PipeWinDrawTruncChars,		//		        868
	PipeWinEraseChars,			//		869
	PipeWinEraseLine,				//	870
	PipeWinErasePixel,			//		871
	PipeWinEraseRectangle,		//		        872
	PipeWinEraseRectangleFrame,		//	        873
	PipeWinEraseWindow,			//		874
	PipeWinFillLine,				//	875
	PipeWinFillRectangle,		//		        876
	PipeWinGetActiveWindow,				//  	877
	PipeWinGetBitmap,				//	878
	PipeWinGetClip,				//		879
	PipeWinGetDisplayExtent,			//	880
	PipeWinGetDisplayWindow,			//	881
	PipeWinGetDrawWindow,				//	882
	PipeWinGetFirstWindow,				//	883
	PipeWinGetFramesRectangle,			//	884
	PipeWinGetPattern,				//	885
	PipeWinGetPatternType,				//	886
	PipeWinGetWindowBounds,				//	887
	PipeWinGetWindowExtent,				//	888
	PipeWinGetWindowFrameRect,			//	889
	PipeWinIndexToRGB,				//	890
	PipeWinInvertChars,				//	891
	PipeWinInvertLine,				//	892
	PipeWinGetPixel,				//	893
	PipeWinInvertPixel,			//		894
	PipeWinInvertRectangle,		//		        895
	PipeWinInvertRectangleFrame,			//	896
	PipeWinModal,					//	897
	PipeWinPaintBitmap,				//	898
	PipeWinPaintChar,				//	899
	PipeWinPaintChars,				//	900
	PipeWinPaintLine,				//	901
	PipeWinPaintLines,				//	902
	PipeWinPaintPixel,			//		903
	PipeWinPaintPixels,			//		904
	PipeWinPaintRectangle,		//		        905
	PipeWinPaintRectangleFrame,			//	906
	PipeWinPalette	,				//	907
	PipeWinPopDrawState,			//		908
	PipeWinPushDrawState,		//		        909
	PipeWinResetClip,				//	910
	PipeWinRestoreBits,				//	911
	PipeWinRGBToIndex,				//	912
	PipeWinSaveBits,				//	913
	PipeWinScreenLock,				//	914
	PipeWinScreenMode,				//	915
	PipeWinScreenUnlock,				//	916
	PipeWinScrollRectangle,				//	917
	PipeWinSetActiveWindow,				//	918
	PipeWinSetBackColor,			       //	919
	PipeWinSetClip,				//		920
	PipeWinSetDrawMode,				//	921
	PipeWinSetDrawWindow,				//	922
	PipeWinSetForeColor,			//		923
	PipeWinSetPattern,				//	924
	PipeWinSetPatternType,				//	925
	PipeWinSetTextColor,				//	926
	PipeWinSetUnderlineMode,			//	927
	PipeWinSetWindowBounds,				//	928
	PipeWinValidateHandle,				//	929
	PipeWinWindowToDisplayPt,			//	930

	PipeVSetRCPFile			//		931
};

