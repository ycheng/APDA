#ifndef __APPLICATION_MANAGET_H__
#define __APPLICATION_MANAGET_H__


#define	errNone						0x0000	// No error


#define	sem_callkey			0x3576
#define	sem_returnkey		0x3567

//	Pipe offset define
#define	APICALLOFFSET		0
#define	APITYPEOFFSET		1
#define	APIADDRESSOFFSET	100

#define	ADDSIZE				sizeof(void *)


//	API function number define
////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.	(100)     0
////////////////////////////////////////////////////////////
#define pAlmGetAlarm 									10000
#define pAlmGetProcAlarm 								10001
#define pAlmSetAlarm 									10002
#define pAlmSetProcAlarm 								10003

////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 9/9 functions now.(101)   4
////////////////////////////////////////////////////////////
#define pBmpBitsSize 									10100
#define pBmpColortableSize 								10101
#define pBmpCompress 									10102
#define pBmpCreate 									10103
#define pBmpDelete 									10104
#define pBmpGetBits									10105
#define pBmpGetColortable								10106
#define pBmpSize 									10107
#define pColorTableEntries 								10108

////////////////////////////////////////////////////////////
// Category Library, completed 16/16 functions now.	(102)      13
////////////////////////////////////////////////////////////
#define pCategoryCreateList 							10200
#define pCategoryCreateListV10 							10201
#define pCategoryEdit 									10202
#define pCategoryEditV20 							10203
#define pCategoryEditV10							10204
#define pCategoryFind 									10205
#define pCategoryFreeList 								10206
#define pCategoryFreeListV10 							10207
#define pCategoryGetName 								10208
#define pCategoryGetNext 								10209
#define pCategoryInitialize 							10210
#define pCategorySelect 								10211
#define pCategorySelectV10 							10212
#define pCategorySetName 								10213
#define pCategorySetTriggerLabel 					10214
#define pCategoryTruncateName 						10215

////////////////////////////////////////////////////////////
// Character Attributes Library, completed 6/6 functions now.(103)    29
////////////////////////////////////////////////////////////
#define pChrHorizEllipsis 							10300
#define pChrIsHardKey 								10301
#define pChrNumericSpace 							10302
#define pGetCharAttr 								10303
#define pGetCharCaselessValue 							10304
#define pGetCharSortValue 							10305

////////////////////////////////////////////////////////////
// Clipboad functions, completed 3/3 functions now.		(104)  35
////////////////////////////////////////////////////////////
#define pClipboardAddItem 								10400
#define pClipboardAppendItem 							10401
#define pClipboardGetItem 								10402

////////////////////////////////////////////////////////////
// Connection Manager Library, completed 4/4 functions now.(105)        38
////////////////////////////////////////////////////////////
#define pCncAddProfile									10500
#define pCncDeleteProfile									10501
#define pCncGetProfileInfo								10502
#define pCncGetProfileList								10503
////////////////////////////////////////////////////////////
// Control Handle Library, completed 20/20 functions now.	(106)   42
////////////////////////////////////////////////////////////
#define pCtlDrawControl 								10600
#define pCtlEnabled 										10601
#define pCtlEraseControl 								10602
#define pCtlGetLabel 									10603
#define pCtlGetSliderValues 							10604
#define pCtlGetValue 									10605
#define pCtlHandleEvent 								10606
#define pCtlHideControl 								10607
#define pCtlHitControl 									10608
#define pCtlNewControl 									10609
#define pCtlNewGraphicControl 						10610
#define pCtlNewSliderControl 							10611
#define pCtlSetEnabled 									10612
#define pCtlSetLabel 									10613
#define pCtlSetGraphics 								10614
#define pCtlSetSliderValue 							10615
#define pCtlSetUsable 									10616
#define pCtlSetValue 									10617
#define pCtlShowControl 								10618
#define pCtlValidatePointer 							10619

///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 6/6 functions now.(107)      62
///////////////////////////////////////////////////////////////
#define pDayHandleEvent								10700
#define pSelectDay								10701
#define pSelectDayV10							10702
#define pSelectOneTime							10703
#define pSelectTime								10704
#define pSelectTimeV33								10705
////////////////////////////////////////////////////////////
// DataBase Library, completed 68/68 functions now.		(108)      68
////////////////////////////////////////////////////////////
#define pDmArchiveRecord 								10800
#define pDmAttachRecord 								10801
#define pDmAttachResource 								10802
#define pDmCloseDatabase 								10803
#define pDmCreateDatabase 								10804
#define pDmCreateDatabaseFromImage 					10805
#define pDmDatabaseInfo 								10806
#define pDmDatabaseProtect 							10807
#define pDmDatabaseSize 								10808
#define pDmDeleteCategory 								10809
#define pDmDeleteDatabase 								10810
#define pDmDeleteRecord 								10811
#define pDmDetachRecord 								10812
#define pDmDetachResource 								10813
#define pDmFindDatabase 								10814
#define pDmFindRecordByID								10815
#define pDmFindResource 								10816
#define pDmFindResourceType 							10817
#define pDmFindSortPosition 							10818
#define pDmFindSortPositionV10								10819
#define pDmGetAppInfoID 								10820
#define pDmGetDatabase 									10821
#define pDmGetDatabaseLocaState 						10822
#define pDmGetLastErr 									10823
#define pDmGetNextDatabaseByTypeCreator 			10824
#define pDmGetRecord 									10825
#define pDmGetResource									10826
#define pDmGetResourceIndex							10827
#define pDmGet1Resource 								10828
#define pDmInsertionSort 								10829
#define pDmMoveCategory 								10830
#define pDmMoveRecord 									10831
#define pDmNewHandle										10832
#define pDmNewRecord 									10833
#define pDmNewReresource 								10834
#define pDmNextOpenDatabase 							10835
#define pDmNumDatabases 								10836
#define pDmNumRecords 									10837
#define pDmNumRecordsInCategory 						10838
#define pDmNumResources 								10839
#define pDmOpenDatabase 								10840
#define pDmOpenDatabaseByTypeCreator				10841
#define pDmOpenDatabaseInfo 							10842
#define pDmOpenDBNoOvelay								10843
#define pDmPositionInCategory 						10844
#define pDmQueryNextInCategory 						10845
#define pDmQueryRecord 									10846
#define pDmQuickSort										10847
#define pDmRecordInfo 									10848
#define pDmReleaseRecord 								10849
#define pDmReleaseResource 							10850
#define pDmRemoveRecord 								10851
#define pDmRemoveResource 								10852
#define pDmRemoveSecretRecord 						10853
#define pDmResizeRecord 								10854
#define pDmResizeResource 								10855
#define pDmResourceInfo 								10856
#define pDmResetRecordStates							10857
#define pDmSearchRecord 								10858
#define pDmSearchResource 								10859
#define pDmSeekRecordInCategory 						10860
#define pDmSet 											10861
#define pDmSetDatabaseInfo 							10862
#define pDmSetRecordInfo 								10863
#define pDmSetResourceInfo 							10864
#define pDmStrCopy										10865
#define pDmWrite 											10866
#define pDmWriteCheck 									10867

////////////////////////////////////////////////////////////
// Error Manager Library, completed 6/6 functions now.	(109)           136
////////////////////////////////////////////////////////////
#define pErrAlert								10900
#define pErrFatalDisplayIf 							10901
#define pErrDisplayFileLineMsg								10902
#define pErrFatalDisplay 								10903
#define pErrNonFatalDisplayIf 						10904
#define pErrThrow							10905
////////////////////////////////////////////////////////////
// Exchange Manager Library, completed 9/9 functions now.(110)           142
////////////////////////////////////////////////////////////
#define pExgAccept								11000
#define pExgDBRead								11001
#define pExgDBWrite 								11002
#define pExgDisconnect 									11003
#define pExgDoDialog							11004
#define pExgPut 								11005
#define pExgReceive 								11006
#define pExgRegisterData								11007
#define pExgSend 										11008

////////////////////////////////////////////////////////////
// Feature Manager Library, completed 7/7 functions now.(111)            151
////////////////////////////////////////////////////////////
#define pFtrGet 						11100
#define pFtrGetByIndex							11101
#define pFtrPtrFree						11102
#define pFtrPtrNew 							11103
#define pFtrPtrResize								11104
#define pFtrSet									11105
#define pFtrUnregister									11106

////////////////////////////////////////////////////////////
// Field Processing Library, completed 52/52 functions now.(112)         158
////////////////////////////////////////////////////////////
#define pFldCalcFieldHeight 							11200
#define pFldCompactText 								11201
#define pFldCopy											11202
#define pFldCut 											11203
#define pFldDelete										11204
#define pFldDirty 										11205
#define pFldDrawField 									11206
#define pFldEraseField 									11207
#define pFldFreeMemory 									11208
#define pFldGetAttributes 								11209
#define pFldGetBounds 									11210
#define pFldGetFont 										11211
#define pFldGetInsPtPosition 							11212
#define pFldGetMaxChars 								11213
#define pFldGetNumberOfBlankLines 					11214
#define pFldGetScrollPosition 						11215
#define pFldGetScrollValues 							11216
#define pFldGetSelection 								11217
#define pFldGetTextAllocatedSize 					11218
#define pFldGetTextHandle 								11219
#define pFldGetTextHeight								11220
#define pFldGetTextLength 								11221
#define pFldGetTextPtr 									11222
#define pFldGetVisibleLines 							11223
#define pFldGrabFocus 									11224
#define pFldHandleEvent 								11225
#define pFldInsert 										11226
#define pFldMakeFullyVisible 							11227
#define pFldNewField 									11228
#define pFldPaste											11229
#define pFldRecalculateField 							11230
#define pFldReleaseFocus 								11231
#define pFldScrollable 									11232
#define pFldScrollField									11233
#define pFldSendChangeNotification 					11234
#define pFldSendHeightChangeNotification 			11235
#define pFldSetAttributes 								11236
#define pFldSetBounds 									11237
#define pFldSetDirty 									11238
#define pFldSetFont 										11239
#define pFldSetInsertionPoint 						11240
#define pFldSetInsPtPosition 							11241
#define pFldSetMaxChars 								11242
#define pFldSetScrollPosition 						11243
#define pFldSetSelection 								11244
#define pFldSetText  									11245
#define pFldSetTextAllocatedSize  					11246
#define pFldSetTextHandle  							11247
#define pFldSetTextPtr  								11248
#define pFldSetUsable  									11249
#define pFldUndo  										11250
#define pFldWordWrap  									11251

////////////////////////////////////////////////////////////
// File Streaming Library, completed 16/16 functions now.(113)            210
////////////////////////////////////////////////////////////
#define pFileClearerr  									11300
#define pFileClose 										11301
#define pFileControl 									11302
#define pFileDelete  									11303
#define pFileDmRead 										11304
#define pFileEOF  										11305
#define pFileError 										11306
#define pFileFlush  										11307
#define pFileGetLastError  							11308	
#define pFileOpen 										11309
#define pFileRead  										11310
#define pFileRewind  									11311
#define pFileSeek  										11312
#define pFileTell 										11313
#define pFileTruncate 									11314
#define pFileWrite  										11315

////////////////////////////////////////////////////////////
// Find Processing Library, completed 4/4 functions now.(114)           226
////////////////////////////////////////////////////////////
#define pFindDrawHeader  								11400
#define pFindGetLineBounds 								11401
#define pFindSaveMatch 									11402
#define pFindStrInStr  										11403

////////////////////////////////////////////////////////////
// Float Manager Library, completed 12/12 functions now.	(115)   230
////////////////////////////////////////////////////////////
#define pFplAdd  									11500
#define pFplAToF										11501
#define pFplBase10Info 									11502
#define pFplDiv  										11503
#define pFplFloatToLong  										11504
#define pFplFloatToULong 										11505
#define pFplFree 									11506
#define pFplFToA  										11507
#define pFplInit 										11508
#define pFplLongToFloat										11509
#define pFplMul  										11510
#define pFplSub										11511

////////////////////////////////////////////////////////////
// Font Processing Library, completed 18/18 functions now.(116)         242
////////////////////////////////////////////////////////////
#define pFntAverageCharWidth  						11600
#define pFntBaseLine										11601	
#define pFntCharHeight  								11602
#define pFntCharsInWidth  								11603
#define pFntCharsWidth 									11604
#define pFntCharWidth  									11605
#define pFntDefineFont											11606
#define pFntGetFont  									11607
#define pFntGetFontPtr									11608
#define pFntGetScrollValues									11609
#define pFntLineHeight  								11610
#define pFntLineWidth  									11611
#define pFntSetFont 										11612
#define pFntWidthToOffset								11613
#define pFntWordWrap										11614
#define pFntWordWrapReverseNLines							11615
#define pFontSelect										11616
////////////////////////////////////////////////////////////
// Form Processing Library, completed 65/65 functions now.(117)          260
////////////////////////////////////////////////////////////
#define pFrmAlert  										11700
#define pFrmCloseAllForms  							11701	
#define pFrmCopyLabel 									11702
#define pFrmCopyTitle  									11703
#define pFrmCustomAlert  								11704
#define pFrmCustomResponseAlert  					11705			
#define pFrmDeleteForm  								11706
#define pFrmDispatchEvent 								11707
#define pFrmDoDialog  									11708
#define pFrmDrawForm 									11709
#define pFrmEraseForm  									11710
#define pFrmGetActiveForm  							11711	
#define pFrmGetActiveFormID 							11712
#define pFrmGetControlGroupSelection  				11713				
#define pFrmGetControlValue 							11714	
#define pFrmGetFirstForm  								11715
#define pFrmGetFocus 									11716
#define pFrmGetFormBounds  							11717	
#define pFrmGetFormId  									11718
#define pFrmGetFormPtr 									11719
#define pFrmGetGadgetData  							11720
#define pFrmGetLabel  									11721
#define pFrmGetNumberOfObjects 						11722		
#define pFrmGetObjectBounds  							11723	
#define pFrmGetObjectId  								11724
#define pFrmGetObjectIndex 							11725	
#define pFrmGetObjectPosition 						11726		
#define pFrmGetObjectPtr  								11727
#define pFrmGetObjectType  							11728	
#define pFrmGetTitle  									11729
#define pFrmGetWindowHandle  							11730	
#define pFrmGotoForm  									11731
#define pFrmHandleEvent 								11732
#define pFrmHelp  										11733
#define pFrmHideObject 									11734
#define pFrmInitForm 									11735
#define pFrmNewBitmap  									11736
#define pFrmNewForm  									11737
#define pFrmNewGadget 									11738
#define pFrmNewGsi 										11739
#define pFrmNewLabel  									11740
#define pFrmPointInTitle  								11741
#define pFrmPopupForm  									11742
#define pFrmRemoveObject  								11743
#define pFrmRestoreActiveState  						11744		
#define pFrmReturnToForm  								11745
#define pFrmSaveActiveState 							11746	
#define pFrmSaveAllForms 								11747
#define pFrmSetActiveForm								11748
#define pFrmSetCategoryLabel 							11749	
#define pFrmSetControlGroupSelection 				11750
#define pFrmSetControlValue 							11751	
#define pFrmSetEventHandler							11752	
#define pFrmSetFocus										11753
#define pFrmSetGadgetData 								11754
#define pFrmSetGadgetHandler 							11755	
#define pFrmSetMenu 										11756
#define pFrmSetObjectBounds 							11757	
#define pFrmSetObjectPosition 						11758		
#define pFrmSetTitle 									11759
#define pFrmShowObject 									11760
#define pFrmUpdateForm 									11761
#define pFrmUpdateScrollers 							11762	
#define pFrmValidatePtr 								11763
#define pFrmVisible 										11764

////////////////////////////////////////////////////////////
// Graffiti Manager Library, completed 19/19 functions now.(118)           325
////////////////////////////////////////////////////////////
#define pGrfAddMacro										11800
#define pGrfAddPoint 									11801
#define pGrfCleanState 									11802
#define pGrfDeleteMacro										11803
#define pGrfFilterPoints								11804
#define pGrfFindBranch										11805
#define pGrfFlushPoints 								11806
#define pGrfGetAndExpandMacro									11807
#define pGrfGetGlyphMapping									11808
#define pGrfGetMacro									11809
#define pGrfGetMacroName								11810
#define pGrfGetNumPoints 								11811			
#define pGrfGetPoint 									11812
#define pGrfGetState 									11813
#define pGrfInitState 									11814
#define pGrfMatch										11815
#define pGrfMatchGlyph									11816
#define pGrfProcessStroke 								11817			
#define pGrfSetState 									11818

//////////////////////////////////////////////////////////////////
// Graffiti Shift Processing Library, completed 5/5 functions now.(119)      344
//////////////////////////////////////////////////////////////////
#define pGsiEnable 										11900
#define pGsiEnabled 										11901
#define pGsiInitialize									11902
#define pGsiSetLocation 								11903
#define pGsiSetShiftState 								11904

////////////////////////////////////////////////////////////
// Insertion Point Library, completed 6/6 functions now.(120)                349
////////////////////////////////////////////////////////////
#define pInsPtEnable 									12000
#define pInsPtEnabled 									12001
#define pInsPtGetHeight 								12002
#define pInsPtGetLocation 								12003
#define pInsPtSetHeight 								12004
#define pInsPtSetLocation 								12005

////////////////////////////////////////////////////////////
// Key Manager Library, completed 3/3 functions now.	(121)                 355
////////////////////////////////////////////////////////////
#define pKeyCurrentState 								12100
#define pKeyRates 								12101
#define pKeySetMask 								12102

////////////////////////////////////////////////////////////
// IR Library, completed 22/22 functions now.		(122)                 358
////////////////////////////////////////////////////////////
#define pIrAdvanceCredit								12200
#define pIrBind 								12201
#define pIrClose 								12202
#define pIrConnectIrLap 								12203
#define pIrConnectReq								12204
#define pIrConnectRsp								12205
#define pIrDataReq 								12206
#define pIrDisconnectIrLap								12207
#define pIrDiscoverReq 								12208
#define pIrIsIrLapConnected								12209
#define pIrIsMediaBusy								12210
#define pIrIsNoProgress 								12211
#define pIrIsRemoteBusy								12212
#define pIrLocalBusy								12213
#define pIrMaxRxSize 								12214
#define pIrMaxTxSize 								12215
#define pIrOpen 								12216
#define pIrSetConTypeLMP 								12217
#define pIrSetConTypeTTP								12218
#define pIrSetDeviceInfo								12219
#define pIrTestReq								12220
#define pIrUnbind								12221

////////////////////////////////////////////////////////////
// IAS Library, completed 14/14 functions now.			(123)          380
////////////////////////////////////////////////////////////
#define pIrIAS_Add								12300
#define pIrIAS_GetInteger 								12301
#define pIIrIAS_GetIntLsap 								12302
#define pIrIAS_GetObjectID 								12303
#define pIrIAS_GetOctetString 								12304
#define pIrIAS_GetOctetStringLen 								12305
#define pIrIAS_GetType 								12306
#define pIrIAS_GetUserString 								12307
#define pIrIAS_GetUserStringCharSet 								12308
#define pIrIAS_GetUserStringLen								12309
#define pIrIAS_Next 								12310
#define pIrIAS_Query 								12311
#define pIrIAS_SetDeviceName 								12312
#define pIrIAS_StartResult								12313

////////////////////////////////////////////////////////////
// List Handle Library, completed 17/17 functions now. (124)                394
////////////////////////////////////////////////////////////
#define pLstDrawList 									12400
#define pLstEraseList 									12401
#define pLstGetNumberOfItems 							12402
#define pLstGetSelection 								12403
#define pLstGetSelectionText 							12404
#define pLstGetVisibleItems 							12405
#define pLstHandleEvent 								12406
#define pLstMakeItemVisible 							12407
#define pLstNewList										12408
#define pLstPopupList									12409
#define pLstScrollList 									12410
#define pLstSetDrawFunction 							12411
#define pLstSetHeight 									12412
#define pLstSetListChoices 							12413
#define pLstSetPosition 								12414
#define pLstSetSelection 								12415
#define pLstSetTopItem 									12416

////////////////////////////////////////////////////////////
// Memory Manager Library, completed 44/44 functions now. (125)               411
////////////////////////////////////////////////////////////
#define pMemCardInfo 									12500
#define pMemCmp											12501
#define pMemDebugMode 									12502
#define pMemHandleCardNo 								12503
#define pMemHandleDataStorage 						12504
#define pMemHandleFree 									12505
#define pMemHandleHeapID 								12506
#define pMemHandleLock 									12507
#define pMemHandleNew 									12508
#define pMemHandleResize								12509
#define pMemHandleSetOwner 							12510
#define pMemHandleSize									12511
#define pMemHandleToLocalID 							12512
#define pMemHandleUnlock 								12513
#define pMemHeapCheck									12514
#define pMemHeapCompact 								12515
#define pMemHeapDynamic 								12516
#define pMemHeapFlags 									12517
#define pMemHeapFreeBytes 								12518
#define pMemHeapID 										12519
#define pMemHeapScramble 								12520
#define pMemHeapSize 									12521
#define pMemLocalIDKind 								12522
#define pMemLocaIDToGlobal								12523
#define pMemLocalIDToLockedPtr 						12524
#define pMemLocalIDToPtr 								12525
#define pMemMove 											12526
#define pMemNumCards 									12527
#define pMemNumHeaps 									12528
#define pMemNumRAMHeaps 								12529
#define pMemPtrCardNo 									12530
#define pMemPtrDataStorage 							12531
#define pMemPtrFree										12532
#define pMemPtrHeapID 									12533
#define pMemPtrNew										12534
#define pMemPtrRecoverHandle 							12535
#define pMemPtrResize 									12536
#define pMemPtrSetOwner 								12537
#define pMemPtrSize										12538
#define pMemPtrToLocalID 								12539
#define pMemPtrUnlock 									12540
#define pMemSet											12541
#define pMemSetDebugMode 								12542
#define pMemStoreInfo									12543

////////////////////////////////////////////////////////////
// Menu Processing Library, completed 14/14 functions now.(126)               455
////////////////////////////////////////////////////////////
#define pMenuAddItem 									12600
#define pMenuCmdBarAddButton 							12601
#define pMenuCmdBarDisplay 							12602
#define pMenuCmdBarGetButtonData 					12603
#define pMenuDispose 									12604
#define pMenuDrawMenu 									12605
#define pMenuEraseStatus 								12606
#define pMenuGetActiveMenu								12607
#define pMenuHandleEvent								12608
#define pMenuHideItem 									12609
#define pMenuInit 										12610
#define pMenuSetActiveMenu 							12611
#define pMenuSetActiveMenuRscID 						12612
#define pMenuShowItem									12613

////////////////////////////////////////////////////////////
// Miscellaneous System Library, completed 3/3 functions now.(127)            469
////////////////////////////////////////////////////////////
#define pCrc16CalcBlock							12700
#define pIntlGetRoutineAddress 						12701
#define pLocGetNumberSeparators									12702

////////////////////////////////////////////////////////////
// Modem Manager Library, completed 2/2 functions now.	(128)                  472
////////////////////////////////////////////////////////////
#define pMdmDial 							12800
#define pMdmHangUp						12801

////////////////////////////////////////////////////////////
// Net Library, completed 44/44 functions now.		(129)                 474
////////////////////////////////////////////////////////////
#define pNetHToNL 								12900
#define pNetHToNS								12901
#define pNetLibAddrAToIN									12902
#define pNetLibAddrINToA							12903
#define pNetLibClose										12904
#define pNetLibConnectionRefresh 							12905
#define pNetLibDmReceive							12906
#define pNetLibFinishCloseWait								12907
#define pNetLibGetHostByAddr								12908
#define pNetLibGetHostByName								12909
#define pNetLibGetMailExchangeByName									12910
#define pNetLibGetServByName							12911
#define pNetLibIFAttach										12912
#define pNetLibIFDetach 							12913
#define pNetLibIFDown							12914
#define pNetLibIFGet								12915
#define pNetLibIFSettingGet								12916
#define pNetLibIFSettingSet								12917
#define pNetLibIFUp								12918
#define pNetLibMaster									12919
#define pNetLibOpen 							12920
#define pNetLibOpenCount 										12921
#define pNetLibReceive 							12922
#define pNetLibReceivePB 							12923
#define pNetLibSelect								12924
#define pNetLibSend								12925
#define pNetLibSendPB 								12926
#define pNetLibSettingGet									12927
#define pNetLibSettingSet							12928
#define pNetLibSocketAccept										12929
#define pNetLibSocketAddr 							12930
#define pNetLibSocketBind 							12931
#define pNetLibSocketClose								12932
#define pNetLibSocketConnect								12933
#define pNetLibSocketListen 								12934
#define pNetLibSocketOpen									12935
#define pNetLibSocketOptionGet							12936
#define pNetLibSocketOptionSet										12937
#define pNetLibSocketShutdown 							12938
#define pNetLibTracePrintF							12939
#define pNetLibTracePutS								12940
#define pNetNToHL 								12941
#define pNetNToHS 								12942

////////////////////////////////////////////////////////////
// Network Utilities Library, completed 3/3 functions now.(130)               518
////////////////////////////////////////////////////////////
#define pNetUReadN								13000
#define pNetUTCPOpen								13001
#define pNetUWriteN								13002

////////////////////////////////////////////////////////////
// New Serial Manager Library, completed 21/21 functions now.(131)               521
////////////////////////////////////////////////////////////
#define pSrmClearErr								13100
#define pSrmClose								13101
#define pSrmControl 								13102
#define pSrmGetDeviceCount								13103
#define pSrmGetDeviceInfo 								13104
#define pSrmGetStatus								13105
#define pSrmOpen								13106
#define pSrmOpenBackground								13107
#define pSrmPrimeWakeupHandler 								13108
#define pSrmReceive								13109
#define pSrmReceiveCheck 								13110
#define pSrmReceiveFlush								13111
#define pSrmReceiveWait								13112
#define pSrmReceiveWindowClose								13113
#define pSrmReceiveWindowOpen								13114
#define pSrmSend								13115
#define pSrmSendCheck								13116
#define pSrmSendFlush								13117
#define pSrmSendWait								13118
#define pSrmSetReceiveBuffer 								13119
#define pSrmSetWakeupHandler								13120

////////////////////////////////////////////////////////////
// Notification Manager Library, completed 4/4 functions now.(132)              542
////////////////////////////////////////////////////////////
#define pSysNotifyBroadcast								13200
#define pSysNotifyBroadcastDeferred								13201
#define pSysNotifyRegister 								13202
#define pSysNotifyUnregister								13203

////////////////////////////////////////////////////////////
// Overlay Manager Library, completed 7/7 functions now.	(133)            546
////////////////////////////////////////////////////////////
#define pOmGetCurrentLocale								13300
#define pOmGetIndexedLocale 								13301
#define pOmGetRoutineAddress 								13302
#define pOmGetSystemLocale								133303
#define pOmLocaleToOverlayDBName								13304
#define pOmOverlayDBNameToLocale 								13305
#define pOmSetSystemLocale								13306

////////////////////////////////////////////////////////////
// Password Library, completed 4/4 functions now.		(134)        553
////////////////////////////////////////////////////////////
#define pPwdExists 										13400
#define pPwdRemove 										13401
#define pPwdSet 											13402
#define pPwdVerify 										13403

////////////////////////////////////////////////////////////
// Pen Manager Library, completed 2/2 functions now.		(135)         557
////////////////////////////////////////////////////////////
#define pPenCalibrate 									13500
#define pPenResetCalibrate 							13501

////////////////////////////////////////////////////////////
// Preferences Library, completed 9/9 functions now.		(136)          559
////////////////////////////////////////////////////////////
#define pPrefGetAppPreferences 						13600
#define pPrefGetAppPreferencesV10 					13601
#define pPrefGetPreference 							13602
#define pPrefGetPreferences 							13603
#define pPrefOpenPreferenceDBV10 							13604
#define pPrefSetAppPreferences 						13605
#define pPrefSetAppPreferencesV10 					13606
#define pPrefSetPreference 							13607
#define pPrefSetPreferences 							13608

///////////////////////////////////////////////////////////////////
// Private Records Processing Library, completed 2/2 functions now.(137)         568
///////////////////////////////////////////////////////////////////
#define pSecSelectViewStatus 							13700
#define pSecVerifyPW							13701

////////////////////////////////////////////////////////////
// Progress Manager Library, completed 6/6 functions now.	(138)            570
////////////////////////////////////////////////////////////
#define pPrgHandleEvent 							13800
#define pPrgStartDialog							13801
#define pPrgStartDialogV31 							13802
#define pPrgStopDialog							13803
#define pPrgUpdateDialog							13804
#define pPrgUserCancel 							13805

////////////////////////////////////////////////////////////
// Rectangle Library, completed 6/6 functions now.		(139)          576
////////////////////////////////////////////////////////////
#define pRctCopyRectangle								13900
#define pRctGetIntersection								13901
#define pRctInsetRectangle 								13902
#define pRctOffsetRectangle 								13903
#define pRctPtInRectangle 								13904
#define pRctSetRectangle 								13905

////////////////////////////////////////////////////////////
// Script Plugin Library, completed 1/1 functions now.	(140)                  582
////////////////////////////////////////////////////////////
#define pScriptPluginSelectorProc 								14000

////////////////////////////////////////////////////////////
// Scroll Bar Library, completed 4/4 functions now.		(141)          583
////////////////////////////////////////////////////////////
#define pSclDrawScrollBar 								14100
#define pSclGetScrollBar 								14101
#define pSclHandleEvent 								14102
#define pSclSetScrollBar 								14103

////////////////////////////////////////////////////////////
// Serail Driver-defined Library, completed 8/8 functions now.(142)               587
////////////////////////////////////////////////////////////
#define pDrvEntryPoint										14200
#define pSdrvClose 									14201
#define pSdrvControl											14202
#define pSdrvISP										14203
#define pSdrvOpen								14204
#define pSdrvReadChar								14205
#define pSdrvStatus											14206
#define pSdrvWriteChar									14207

////////////////////////////////////////////////////////////
// Serail Link Manager Library, completed 10/10 functions now.(143)                 595
////////////////////////////////////////////////////////////
#define pSlkClose										14300
#define pSlkCloseSocket 									14301
#define pSlkFlushSocket									14302
#define pSlkOpen											14303
#define pSlkOpenSocket 										14304
#define pSlkReceivePacket								14305
#define pSerReceiveFlush 								14306
#define pSlkSetSocketListener											14307
#define pSlkSocketPortID									14308
#define pSlkSocketSetTimeout											14309

////////////////////////////////////////////////////////////
// Serial Manager Library, completed 17/17 functions now.		(144)         605
////////////////////////////////////////////////////////////
#define pSerClearErr 										14400
#define pSerClose									14401
#define pSerControl								14402
#define pSerGetSettings											14403
#define pSerGetStatus 										14404
#define pSerOpen											14405
#define pSerReceive								14406
#define pSerReceive10											14407
#define pSerReceiveCheck									14408
#define pSerReceiveFlush										14409
#define pSerReceiveWait									14410
#define pSerSend										14411
#define pSerSend10								14412
#define pSerSendFlush								14413
#define pSerSendWait											14414
#define pSerSetReceiveBuffer									14415
#define pSerSetSettings									14416

////////////////////////////////////////////////////////////
// Serial Manager Queue Library, completed 4/4 functions now.(145)            622
////////////////////////////////////////////////////////////
#define pGetSize								14500
#define pGetSpace											14501
#define pWriteBlock									14502
#define pWriteByte								14503

////////////////////////////////////////////////////////////
// Sound Manager Library, completed 6/6 functions now.	(146)                  626
////////////////////////////////////////////////////////////
#define pSndCreateMidiList								14600
#define pSndDoCmd											14601
#define pSndGetDefaultVolume									14602
#define pSndPlaySmf								14603
#define pSndPlaySmfResource									14604
#define pSndPlaySystemSound									14605

////////////////////////////////////////////////////////////
// Standard IO Library, completed 5/5 functions now.		(147)             632
////////////////////////////////////////////////////////////
#define pSioClearScreen											14700
#define pSioExecCommand									14701
#define pSioFree								14702
#define pSioHandleEvent									14703
#define pSioInit									14704

////////////////////////////////////////////////////////////
// String Manager Library, completed 19/19 functions now.(148)                  637
////////////////////////////////////////////////////////////
#define pStrAToI											14800
#define pStrCaselessCompare 							14801
#define pStrCat 											14802
#define pStrChr											14803
#define pStrCompare 										14804
#define pStrCopy 											14805
#define pStrDelocalizeNumber							14806
#define pStrIToA											14807
#define pStrIToH											14808
#define pStrLen 											14809
#define pStrLocalizeNumber 							14810
#define pStrNCaselessCompare 							14811
#define pStrNCat 											14812
#define pStrNCompare 									14813
#define pStrNCopy 										14814
#define pStrPrintF										14815
#define pStrStr 											14816
#define pStrToLower 										14817
#define pStrVPrintF										14818

////////////////////////////////////////////////////////////
// System Dialogs Library, completed 3/3 functions now.(149)                 656
////////////////////////////////////////////////////////////
#define pSysAppLauncherDialog											14900
#define pSysFatalAlert										14901
#define pSysGraffitiReferenceDialogs										14902

//////////////////////////////////////////////////////////////
// System Event Manager Library, completed 25/25 functions now.(150)           659
//////////////////////////////////////////////////////////////
#define pEvtAddEventToQueue							15000
#define pEvtAddUniqueEventToQueue										15001
#define pEvtCopyEvent								15002
#define pEvtDequeuePenPoint										15003
#define pEvtDequeuePenStrokeInfo							15004
#define pEvtEnableGraffiti										15005
#define pEvtEnqueueKey								15006
#define pEvtEventAvail										15007
#define pEvtFlushKeyQueue							15008
#define pEvtFlushNextPenStroke										15009
#define pEvtFlushPenQueue								15010
#define pEvtGetEvent										15011
#define pEvtGetPen							15012
#define pEvtGetPenBtnList										15013
#define pEvtGetSilkscreenAreaList								15014
#define pEvtKeydownIsVirtual										15015
#define pEvtKeyQueueEmpty 							15016
#define pEvtKeyQueueSize										15017
#define pEvtPenQueueSize								15018
#define pEvtProcessSoftKeyStroke										15019
#define pEvtResetAutoOffTimer							15020
#define pEvtSetAutoOffTimer										15021
#define pEvtSetNullEventTick								15022
#define pEvtSysEventAvail										15023
#define pEvtWakeup								15024
////////////////////////////////////////////////////////////
// System Manager Library, completed 33/33 functions now.	(151)             684
////////////////////////////////////////////////////////////
#define pSysAppLaunch 									15100
#define pSysBatteryInfo 								15101
#define pSysBatteryInfoV20 							15102
#define pSysBinarySearch							15103
#define pSysBroadcastActionCode								15104
#define pSysCopyStringResource						15105
#define pSysCreateDataBaseList							15106
#define pSysCreatePanelList						15107
#define pSysCurAppDatabase										15108
#define pSysErrString 										15109
#define pSysFormPointerArrayToStrings 									15110
#define pSysGetOSVersionString 							15111
#define pSysGetROMToken								15112
#define pSysGetStackInfo									15113
#define pSysGetTrapAddress								15114
#define pSysGraffitiReferenceDialog 							15115
#define pSysGremlins							15116
#define pSysHandleEvent								15117
#define pSysInsertionSort						15118
#define pSysKeyboardDialog							15119
#define pSysKeyboardDialogV10						15120
#define pSysLibFind										15121
#define pSysLibLoad										15122
#define pSysLibRemove									15123
#define pSysQSort
#define pSysRandom							15124
#define pSysReset								15125
#define pSysSetAutoOffTime									15126
#define pSysSetTrapAddress								15127
#define pSysStringByIndex							15128
#define pSysTaskDelay								15129
#define pSysTicksPerSecond							15130
#define pSysUIAppSwitch							15131

////////////////////////////////////////////////////////////
// Table Library, completed 57/57 functions now.		(152)         717
////////////////////////////////////////////////////////////
#define pTblDrawTable 									15200
#define pTblEditing 										15201
#define pTblEraseTable 									15202
#define pTblFindRowData 								15203
#define pTblFindRowID 									15204
#define pTblGetBounds 									15205
#define pTblGetColumnSpacing 							15206
#define pTblGetColumnWidth 							15207
#define pTblGetCurrentField 							15208
#define pTblGetItemBounds 								15209
#define pTblGetItemFont 								15210
#define pTblGetItemInt 									15211
#define pTblGetItemPtr	 								15212
#define pTblGetLastUsableRow 							15213
#define pTblGetNumberOfRows 							15214
#define pTblGetRowData 									15215
#define pTblGetRowHeight								15216
#define pTblGetRowID 									15217
#define pTblGetSelection 								15218
#define pTblGrabFocus 									15219
#define pTblHandleEvent 								15220
#define pTblHasScrollBar 								15221
#define pTblInsertRow 									15222
#define pTblMarkRowInvalid 							15223
#define pTblMarkTableInvalid 							15224
#define pTblRedrawTable  								15225
#define pTblReleaseFocus 								15226
#define pTblRemoveRow  									15227
#define pTblReverseItem 								15228
#define pTblRowInvalid 									15229
#define pTblRowMasked 									15230
#define pTblRowSelectable 								15231
#define pTblRowUsable 									15232
#define pTblSelectItem  								15233
#define pTblSetBounds 									15234
#define pTblSetColumnEditIndicator 					15235
#define pTblSetColumnMasked 							15236
#define pTblSetColumnSpacing  						15237
#define pTblSetColumnUsable  							15238
#define pTblSetColumnWidth  							15239
#define pTblSetCustomDrawProcedure 					15240
#define pTblSetItemFont 								15241
#define pTblSetItemInt 									15242
#define pTblSetItemPtr 									15243
#define pTblSetItemStyle  								15244
#define pTblSetLoadDataProcedure  					15245
#define pTblSetRowData  								15246
#define pTblSetRowHeight  								15247
#define pTblSetRowID  									15248
#define pTblSetRowMasked  								15249
#define pTblSetRowSelectable  						15250
#define pTblSetRowStaticHeight  						15251
#define pTblSetRowUsable  								15252
#define pTblSetSaveDataProcedure  					15253
#define pTblUnhighlightSelection  					15254
#define pTableDrawItemFuncType						15255
#define pTableLoadDataFuncType						15256
#define pTableSaveDataFuncType 						15257

////////////////////////////////////////////////////////////
// Text Manager Library, completed 38/38 functions now.	(153)                   774
////////////////////////////////////////////////////////////
#define pTxtByteAttr										15300
#define pTxtCaselessCompare 								15301
#define pTxtCharAttr							15302
#define pTxtCharBounds							15303
#define pTxtCharEncoding										15304
#define pTxtCharIsAlNum 								15305
#define pTxtCharIsAlpha 								15306
#define pTxtCharIsCntrl 								15307
#define pTxtCharIsDelim 								15308
#define pTxtCharIsDigit 								15309
#define pTxtCharIsGraph 								15310
#define pTxtCharIsHardKey										15311
#define pTxtCharIsHex 									15312
#define pTxtCharIsLower 								15313
#define pTxtCharIsPrint 								15314
#define pTxtCharIsPunct										15315
#define pTxtCharIsSpace 								15316
#define pTxtCharIsUpper 								15317
#define pTxtCharIsValid										15318
#define pTxtCharSize 									15319
#define pTxtCharWidth										15320
#define pTxtCharXAttr								15321
#define pTxtCompare							15322
#define pTxtEncodingName							15323
#define pTxtFindString										15324
#define pTxtGetChar										15325
#define pTxtGetNextChar							15326
#define pTxtGetPreviousChar										15327
#define pTxtGetTruncationOffset										15328
#define pTxtMaxEncoding										15329
#define pTxtNextCharSize								15330
#define pTxtParamString 							15331
#define pTxtPreviousCharSize							15332
#define pTxtReplaceStr										15333
#define pTxtSetNextChar										15334
#define pTxtStrEncoding 							15335
#define pTxtTransliterate 										15336
#define pTxtWordBounds 										15337

////////////////////////////////////////////////////////////
// Time Manager Library, completed 17/17 functions now.(154)                       812
////////////////////////////////////////////////////////////
#define pDateAdjust										15400
#define pDateDaysToDate 								15401
#define pDateSecondsToDate 							15402
#define pDateTemplateToAscii 							15403
#define pDateToAscii										15404
#define pDateToDays 										15405
#define pDateToDOWDMFormat 							15406
#define pDayOfMonth 										15407
#define pDayOfWeek 										15408
#define pDaysInMonth										15409
#define pTimeAdjust 										15410
#define pTimDateTimeToSeconds 						15411
#define pTimGetSeconds 									15412
#define pTimGetTicks 									15413
#define pTimSecondsToDateTime 						15414
#define pTimSetSeconds 									15415
#define pTimeToAscii 									15416

////////////////////////////////////////////////////////////
// UI Color List Library, completed 3/3 functions now.	(155)                  829
////////////////////////////////////////////////////////////
#define pUIColorGetTableEntryIndex								15500
#define pUIColorGetTableEntryRGB									15501
#define pUIColorSetTableEntry								15502

////////////////////////////////////////////////////////////
// UI Controls Library, completed 3/3 functions now.	(156)                832
////////////////////////////////////////////////////////////
#define pUIBrightnessAdjust									15600
#define pUIContrastAdjust									15601
#define pUIPickColor									15602

////////////////////////////////////////////////////////////
// User Interface Library, completed 4/4 functions now.	(157)                 835
////////////////////////////////////////////////////////////
#define pPhoneNumberLookup								15700
#define pResLoadConstant									15701
#define pResLoadForm									15702
#define pResLoadMenu								15703

////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 6/6 functions now.(158)          839
////////////////////////////////////////////////////////////
#define pDrvEntryPointV10 									15800
#define pVdrvClose									15801
#define pVdrvControl									15802
#define pVdrvOpen									15803
#define pVdrvStatus									15804
#define pVdrvWrite 									15805

////////////////////////////////////////////////////////////
// Window function, completed 80/80 functions now.			(159)    845
////////////////////////////////////////////////////////////
#define pWinClipRectangle 									15900
#define pWinCopyRectangle									15901
#define pWinCreateBitmapWindow									15902
#define pWinCreateOffscreenWindow									15903
#define pWinCreateWindow									15904
#define pWinDeleteWindow 									15905
#define pWinDisplayToWindowPt									15906
#define pWinDrawBitmap 									15907
#define pWinDrawChar 									15908
#define pWinDrawChars 									15909
#define pWinDrawGrayLine 								15910
#define pWinDrawGrayRectangleFrame 					15911
#define pWinDrawInvertedChars 						15912
#define pWinDrawLine 									15913
#define pWinDrawPixel 									15914
#define pWinDrawRectangle								15915
#define pWinDrawRectangleFrame 						15916
#define pWinDrawTruncChars 							15917
#define pWinEraseChars 									15918
#define pWinEraseLine 									15919
#define pWinErasePixel 									15920
#define pWinEraseRectangle 							15921
#define pWinEraseRectangleFrame								15922
#define pWinEraseWindow 								15923
#define pWinFillLine 									15924
#define pWinFillRectangle 								15925
#define pWinGetActiveWindow							15926
#define pWinGetBitmap									15927
#define pWinGetClip 										15928
#define pWinGetDisplayExtent							15929
#define pWinGetDisplayWindow								15930
#define pWinGetDrawWindow							15931
#define pWinGetFirstWindow								15932
#define pWinGetFramesRectangle								15933
#define pWinGetPattern								15934
#define pWinGetPatternType								15935
#define pWinGetPixel 									15936
#define pWinGetWindowBounds							15937
#define pWinGetWindowExtent									15938
#define pWinGetWindowFrameRect								15939
#define pWinIndexToRGB								15940
#define pWinInvertChars									15941
#define pWinInvertLine								15942
#define pWinInvertPixel									15943
#define pWinInvertRectangle							15944
#define pWinInvertRectangleFrame							15945
#define pWinModal								15946
#define pWinPaintBitmap									15947
#define pWinPaintChar										15948
#define pWinPaintChars								15949
#define pWinPaintLine									15950
#define pWinPaintLines								15951
#define pWinPaintPixel									15952
#define pWinPaintPixels 								15953
#define pWinPaintRectangle 							15954
#define pWinPaintRectangleFrame									15955
#define pWinPalette									15956
#define pWinPopDrawState 								15957
#define pWinPushDrawState 								15958
#define pWinResetClip									15959
#define pWinRestoreBits								15960
#define pWinRGBToIndex									15861
#define pWinSaveBits										15962
#define pWinScreenLock									15963
#define pWinScreenMode								15964
#define pWinScreenUnlock								15965
#define pWinScrollRectangle									15966
#define pWinSetActiveWindow								15967
#define pWinSetBackColor 								15968
#define pWinSetClip 										15969
#define pWinSetDrawMode								15970
#define pWinSetDrawWindow									15971
#define pWinSetForeColor 								15972
#define pWinSetPattern									15973
#define pWinSetPatternType							15974
#define pWinSetTextColor									15975
#define pWinSetUnderlineMode							15976
#define pWinSetWindowBounds								15977
#define pWinValidateHandle									15978
#define pWinWindowToDisplayPt									15979

#define pVSetRCPFile										16000

#endif	// __APPLICATION_MANAGET_H__
