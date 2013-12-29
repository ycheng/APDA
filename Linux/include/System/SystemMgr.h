#ifndef 	__SYSTEMMGR_H__
#define	__SYSTEMMGR_H__

// System SysAppLaunch Commands
#define	sysAppLaunchCmdNormalLaunch		0	// Normal Launch

#define	sysAppLaunchCmdFind					1	// Find string

#define	sysAppLaunchCmdGoTo					2	// Launch and go to a particular record

#define	sysAppLaunchCmdSyncNotify			3  // Sent to apps whose databases changed during
															// HotSync after the sync has been completed,
															// including when the app itself has been installed
															// by HotSync. The data database(s) must have the
															// same creator ID as the application for this
															// mechanism to function correctly. This is a
															// good opportunity to update/initialize/validate
															// the app's data, such as resorting records,
															// setting alarms, etc.
															//
															// Parameter block: None.
															// Restrictions: No accessing of global or
															//		static variables; no User Interface calls.
															// Notes: This action code is sent via a
															//		direct function call into the app's
															//		PilotMain function from the background
															//		thread of the HotSync application.


#define	sysAppLaunchCmdTimeChange			4  // Sent to all applications and preference
															// panels when the system time is changed.
															// This notification is the right place to
															// update alarms and other time-related
															// activities and resources.
															//
															// Parameter block: None.
															// Restrictions: No accessing of global or
															//		static variables; no User Interface calls.
															// Notes: This action code is sent via a direct
															//		function call into the app's PilotMain
															//		function without "launching" the app.

#define	sysAppLaunchCmdSystemReset			5  // Sent to all applications and preference
															// panels when the system is either soft-reset
															// or hard-reset.  This notification is the
															// right place to initialize and/or validate
															// your application's preferences/features/
															// database(s) as well as to update alarms and
															// other time-related activities and resources.
															//
															// Parameter block: SysAppLaunchCmdSystemResetType
															// Restrictions: No accessing of global or
															//		static variables; no User Interface calls.
															// Notes: This action code is sent via a direct
															//		function call into the app's PilotMain
															//		function without "launching" the app.

#define	sysAppLaunchCmdAlarmTriggered		6  // Sent to an application at the time its
															// alarm time expires (even when another app
															// is already displaying its alarm dialog box).
															// This call is intended to allow the app to
															// perform some very quick activity, such as
															// scheduling the next alarm or performing a
															// quick maintenance task.  The handler for
															// sysAppLaunchCmdAlarmTriggered must take as
															// little time as possible and is *not* allowed
															// to block (this would delay notification for
															// alarms set by other applications).  
															//
															// Parameter block: SysAlarmTriggeredParamType
															//		(defined in AlarmMgr.h)
															// Restrictions: No accessing of global or
															//		static variables unless sysAppLaunchFlagSubCall
															//		flag is set, as discussed above.
															// Notes: This action code is sent via a direct
															//		function call into the app's PilotMain
															//		function without "launching" the app.

#define	sysAppLaunchCmdDisplayAlarm		7  // Sent to an application when it is time
															// to display the alarm UI. The application
															// is responsible for making any alarm sounds
															// and for displaying the alarm UI.
															// sysAppLaunchCmdDisplayAlarm calls are ordered
															// chronoligically and are not overlapped.
															// This means that your app will receive
															// sysAppLaunchCmdDisplayAlarm only after
															// all earlier alarms have been displayed.
															//
															// Parameter block: SysDisplayAlarmParamType
															//		(defined in AlarmMgr.h)
															// Restrictions: No accessing of global or
															//		static variables unless sysAppLaunchFlagSubCall
															//		flag is set, as discussed above.  UI calls are
															//		allowed to display the app's alarm dialog.
															// Notes: This action code is sent via a direct
															//		function call into the app's PilotMain
															//		function without "launching" the app.

#define	sysAppLaunchCmdCountryChange		8  // The country has changed

#define	sysAppLaunchCmdSyncRequestLocal	9  // Sent to the HotSync application to request a
															// local HotSync.  ("HotSync" button was pressed.)

#define	sysAppLaunchCmdSyncRequest			sysAppLaunchCmdSyncRequestLocal	// for backward compatibility

#define	sysAppLaunchCmdSaveData			  	10 // Sent to running app before sysAppLaunchCmdFind
															// or other action codes that will cause data
															// searches or manipulation.

#define	sysAppLaunchCmdInitDatabase	  	11	// Sent to an application when a database with
															// a matching Creator ID is created during
															// HotSync (in response to a "create db"
															// request). This allows the application to
															// initialize a newly-created database during
															// HotSync.  This might include creating some
															// default records, setting up the database's
															// application and sort info blocks, etc.
															//
															// Parameter block: SysAppLaunchCmdInitDatabaseType
															// Restrictions: No accessing of global or
															//		static variables; no User Interface calls.
															// Notes: This action code is sent via a
															//		direct function call into the app's
															//		PilotMain function from the background
															//		thread of the HotSync application.

#define	sysAppLaunchCmdSyncCallApplicationV10	12 // Used by DesktopLink Server command "call application";
																	// Pilot v1.0 only!!!
																		
//------------------------------------------------------------------------
// New launch codes defined for PalmOS 2.0
//------------------------------------------------------------------------

#define	sysAppLaunchCmdPanelCalledFromApp	13 // The panel should display a done
																// button instead of the pick list.
																// The Done button will return the user
																// to the last app.

#define	sysAppLaunchCmdReturnFromPanel		14	// A panel returned to this app

#define	sysAppLaunchCmdLookup				  	15	// Lookup info managed by an app

#define	sysAppLaunchCmdSystemLock			  	16	// Lock the system until a password is entered.

#define	sysAppLaunchCmdSyncRequestRemote		17	// Sent to the HotSync application to request
																// a remote HotSync.  ("Remote HotSync" button
																// was pressed.)

#define	sysAppLaunchCmdHandleSyncCallApp		18 // Pilot v2.0 and greater.  Sent by DesktopLink Server to an application to handle
																// the "call application" command; use DlkControl with
																// control code dlkCtlSendCallAppReply to send the reply(see DLServer.h).
																// This action code replaces the v1.0 code sysAppLaunchCmdSyncCallApplication.
																// vmk 11/26/96

#define sysAppLaunchCmdAddRecord					19	// Add a record to an applications's database. 

#define sysAppLaunchCmdFailedAppNotify			24	// An app just switched to failed. 

	
//#define	sysTicksPerSecond				100				// 100/sec on Pilot
#define	sysTicksPerSecond				1000				// 1000/sec on Windows PC


/************************************************************
 * System Types
 *************************************************************/
 

// Types of batteries installed.
typedef enum {
	sysBatteryKindAlkaline=0,
	sysBatteryKindNiCad,
	sysBatteryKindLiIon,
	sysBatteryKindRechAlk,
	sysBatteryKindNiMH,
	sysBatteryKindLiIon1400,
	sysBatteryKindLithium,
	sysBatteryKindLast=0xFF
} SysBatteryKind;


// SysCreateDataBaseList can generate a list of database.
typedef struct 
	{
	Char			name[dmDBNameLength];
	ULong			creator;
	ULong			type;
	UInt			version;
	LocalID		dbID;
	UInt 			cardNo;
	BitmapPtr	iconP;
	} SysDBListItemType;
	


// ROM/OS stage numbers
#define sysROMStageDevelopment	(0)
#define sysROMStageAlpha			(1)
#define sysROMStageBeta				(2)
#define sysROMStageRelease			(3)

// MACRO: sysMakeROMVersion
//
// Builds a ROM version value from the major, minor, fix, stage, and build numbers
//
#define sysMakeROMVersion(major, minor, fix, stage, buildNum)			\
		(																					\
		(((DWord)((Byte)(major) & 0x0FF)) << 24) |							\
		(((DWord)((Byte)(minor) & 0x00F)) << 20) |							\
		(((DWord)((Byte)(fix)   & 0x00F)) << 16) |							\
		(((DWord)((Byte)(stage) & 0x00F)) << 12) |							\
		(((DWord)((Word)(buildNum) & 0x0FFF)))									\
		)

#define	sysFileCSystem						'psys'	// Creator type for System files
#define	sysFileTApplication				'appl'	// File type for applications
#define	sysFileCPreferences				'pref'	// Creator type for Preferences App


/************************************************************
 * System Features
 *************************************************************/
#define	sysFtrCreator			sysFileCSystem		// Feature Creator
#define	sysFtrNumROMVersion	1						// ROM Version
			// 0xMMmfsbbb, where MM is major version, m is minor version
			// f is bug fix, s is stage: 3-release,2-beta,1-alpha,0-development,
			// bbb is build number for non-releases 
			// V1.12b3   would be: 0x01122003
			// V2.00a2   would be: 0x02001002
			// V1.01     would be: 0x01013000
#define	sysFtrNumProductID	2						// Product id
			// 0xMMMMRRRR, where MMMM is the model and RRRR
			// is the revision.
#define	sysFtrNumBacklight	3						// Backlight
			// bit 0:	1 if present. 0 if Feature does not exist or backlight is not present
#define	sysFtrNumEncryption	4						// Which encryption schemes are present
#define	sysFtrNumEncryptionMaskDES		0x00000001 // bit 0:	1 if DES is present

			


#endif // __SYSTEMMGR_H__
