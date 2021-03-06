#ifndef __UICOMMON_H__
#define __UICOMMON_H__

enum justifications { leftAlign, centerAlign, rightAlign };
typedef enum justifications JustificationType;

//------------------------------------------------------------
// System functions 
//------------------------------------------------------------
#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))



//------------------------------------------------------------
// Temporary resource routines 
//------------------------------------------------------------

#define strRsc 								'tSTR'
#define ainRsc 								'tAIN'
#define iconType								'tAIB'
#define bitmapRsc 							'Tbmp'
#define alertRscType   						'Talt'
#define kbdRscType							'tkbd'
#define MenuRscType							'MBAR'
#define fontRscType							'NFNT'
#define verRsc									'tver'
#define appInfoStringsRsc					'tAIS'


// Application version string ID
#define appVersionID							1
#define ainID									1000

// System Default app icon (for apps missing a tAIB)
#define defaultAppIconBitmap				10000

//	System version string ID - this is hidden in
//	the SystemVersion.rsrc resource, because the 'system' resources
//	don't have ResEdit formats.
#define systemVersionID						10000

// System bitmaps
#define palmLogoBitmap						10000
#define keyboardBackspaceBitmap			10001
#define keyboardTabBitmap					10002
#define keyboardReturnBitmap				10003
#define InformationAlertBitmap 			10004
#define ConfirmationAlertBitmap			10005
#define WarningAlertBitmap					10006
#define ErrorAlertBitmap					10007
#define keyboardShiftBitmap				10008
#define keyboardCapBitmap					10009


// System string resources
#define daysOfWeekStrID						10000
#define dayFullNamesStrID					10001
#define monthNamesStrID						10002
#define monthFullNamesStrID				10003
#define categoryAllStrID					10004
#define categoryEditStrID  				10005
#define menuCommandStrID					10006
#define launcherBatteryStrID				10007
#define systemNameStrID						10008
#define phoneLookupTitleStrID				10009
#define phoneLookupAddStrID				10010
#define phoneLookupFormatStrID			10011


// System Alerts
#define SelectACategoryAlert				10000

// This alert broke 1.0 applications and is now disabled until later.
// It is redefined below (10015).
//#define RemoveCategoryAlert				10001
//#define RemoveCategoryRecordsButton		0
//#define RemoveCategoryNameButton			1
//#define RemoveCategoryCancelButton		2

#define LowBatteryAlert						10002
#define VeryLowBatteryAlert				10003
#define UndoAlert								10004
#define UndoCancelButton					1

#define MergeCategoryAlert					10005
#define MergeCategoryYes					0
#define MergeCategoryNo						1

#define privateRecordInfoAlert			10006

#define ClipboardLimitAlert				10007

#define CategoryExistsAlert				10012

#define DeviceFullAlert						10013

#define categoryAllUsedAlert				10014

#define RemoveCategoryAlert				10015		// See alert 10001
#define RemoveCategoryYes					0
#define RemoveCategoryNo					1

#define DemoUnitAlert						10016



// System Menu Bar and Menus
#define sysEditMenuID						10000
#define sysEditMenuUndoCmd					10000
#define sysEditMenuCutCmd					10001
#define sysEditMenuCopyCmd					10002
#define sysEditMenuPasteCmd				10003
#define sysEditMenuSelectAllCmd			10004
#define sysEditMenuSeparator				10005
#define sysEditMenuKeyboardCmd			10006
#define sysEditMenuGraffitiCmd			10007


// Keyboard Menu Bar and Menus
#define sysKeyboardMenuID					10100
#define sysKeyboardEditUndoCmd			100
#define sysKeyboardEditCutCmd				101
#define sysKeyboardEditCopyCmd			102
#define sysKeyboardEditPasteCmd			103
#define sysKeyboardEditSelectAllCmd		104


// Note View Menu Bar and Menus
#define noteMenuID							10200
#define noteUndoCmd							10000
#define noteCutCmd							10001
#define noteCopyCmd							10002
#define notePasteCmd							10003
#define noteSelectAllCmd					10004
#define noteSeparator						10005
#define noteKeyboardCmd						10006
#define noteGraffitiCmd						10007
#define noteTopOfPageCmd					10200
#define noteBottomOfPageCmd				10201
#define notePhoneLookupCmd					10202


// System Keyboard Dialog
#define SystemKeyboardID					10000


// Categories Edit Dialog
#define CategoriesEditForm					10000
#define CategoriesEditList					10002
#define CategoriesEditOKButton			10003
#define CategoriesEditNewButton			10004
#define CategoriesEditRenameButton		10005
#define CategoriesEditDeleteButton		10006


// Date Selector Dialog
#define DateSelectorForm					10100
#define DateSelectorYearLabel				10102
#define DateSelectorPriorYearButton		10103
#define DateSelectorNextYearButton		10104
#define DateSelectorTodayButton			10118
#define DateSelectorCancelButton			10119
#define DateSelectorDayGadget				10120
#define DateSelectorThisWeekButton		10121
#define DateSelectorThisMonthButton		10122


// Time Selector Dialog
#define TimeSelectorForm					10200
#define TimeSelectorStartTimeButton		10204
#define TimeSelectorEndTimeButton		10205
#define TimeSelectorHourList				10206
#define TimeSelectorMinuteList			10207
#define TimeSelectorOKButton				10208
#define TimeSelectorCancelButton			10209
#define TimeSelectorNoTimeButton			10210


// Onscreen Keyboard
#define KeyboardForm							10300
#define KeyboardGadget						10310


// Help Dialog
#define HelpForm								10400
#define HelpField								10402
#define HelpDoneButton						10403
#define HelpUpButton							10404
#define HelpDownButton						10405


// Find Dialog
#define FindDialog							10500
#define FindStrField							10503
#define FindOKButton							10504


// Find Results Dialog
#define FindResultsDialog					10600
#define FindResultsMsgLabel				10602
#define FindResultsTable					10603
#define FindResultsGoToButton				10604
#define FindResultsCancelButton			10605
#define FindResultsMoreButton				10606
#define FindResultsStopButton				10607

#define FindResultsSearchingStr			10607
#define FindResultsMatchesStr				10608
#define FindResultsNoMatchesStr			10609
#define FindResultsContinueStr			10610


// Note View (used by Datebook, To Do, and Address apps)
#define NoteView								10900
#define NoteField								10901
#define NoteDoneButton						10902
#define NoteSmallFontButton				10903
#define NoteLargeFontButton				10904
#define NoteDeleteButton					10905
#define NoteUpButton							10906
#define NoteDownButton						10907
#define NoteScrollBar						10908
#define NoteFontGroup						1


//	About Box - used by Datebook, Memo, Address, To Do, & others
#define aboutDialog							11000
#define aboutNameLabel						11001
#define aboutVersionLabel					11002
#define aboutErrorStr						11003


// Category New Name Dialog (used for new and renamed categories)
#define categoryNewNameDialog				11100
#define categoryNewNameField				11103
#define categoryNewNameOKButton			11104


// Graffiti Reference Dialog
#define graffitiReferenceDialog			11200
#define graffitiReferenceDoneButton		11202
#define graffitiReferenceUpButton		11203
#define graffitiReferenceDownButton		11204
#define graffitiReferenceFirstBitmap	11205


// Net Library Serial Net Interface dialogs. These don't really have to
// have ID's in the system range except in the Emulator. When running on 
// the device, the interface's resource file is opened up just to get these
// resources so that the ID's don't have to be unique with the application's
// resource IDs.
#define	netSerStringList					11300			// String list resource ID

// Net Serial Progress Dialog
#define  netSerProgressFrm					11300			// progress form ID
#define	netSerProgressLabelStage		11302			// Label ID
#define	netSerProgressBtnCancel			11303			// Cancel button ID
#define	netSerPictPhone					11300			// resource ID of phone picture
#define	netSerPictHandshake				11301			// resource ID of handshake picture
#define	netSerPictBook						11302			// resource ID of book picture
#define	netSerPictError					11303			// resource ID of error picture

// Net Serial Prompt Dialog
#define	netSerPromptFrm					11400			// Prompt for string form ID
#define	netSerPromptAsk					11402			// Label - ask string
#define	netSerPromptField					11403			// answer field
#define	netSerPromptBtnOK					11404			// OK button ID
#define	netSerPromptBtnCancel			11405			// Cancel button ID


// Launcher Dialog
#define launcherDialog						11500
#define launcherGadget						11501


//------------------------------------------------------------
// Temporary debugging routines 
//------------------------------------------------------------
//extern Boolean HeapDump (void);


#endif //__UICOMMON_H__
