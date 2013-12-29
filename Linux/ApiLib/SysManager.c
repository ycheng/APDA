/*========================================================
  SYsManager.c
  all routine is running with Platform non-related,
  simulated the system manager function in Palm OS.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0528, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#define	OSVersion	"V0.5"
#define	BatteryKinds	7

extern void FormDisplayAlert (const Char *msg);

ClipboardItem	clipBoardItem;

UInt16	sysTicks = 200;
UInt32	sysDelay = 0;

// database
extern UInt16		curCardNo;
extern LocalID		curDBID;


// system battery information
SysBatteryKind	sysBatteryKind;
UInt16	sysBatteryCurrentVolts=396;

typedef struct {
	UInt16	warnThrehsold;
	UInt16	criticalThreshold;
	UInt16	maxTicks;
	Boolean	pluggedIn;
	UInt16	maxVolts;
} SysBatteryValue;

SysBatteryValue	sysBatteryValue[BatteryKinds]={	{200,160,100,0,300},
																	{226,160,100,0,250},
																	{362,331,100,0,396},
																	{235,160,100,0,300},
																	{232,160,100,0,265},
																	{362,331,100,0,396},
																	{362,331,100,0,396} };


// define for system preference panel
UInt16	sysPanelCount=0;
Char		*sysPanelIDs=NULL;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ClipboardAddItem
//
// DESCRIPTION: This routine add the item passed to the specified 
//					 clipboard. Replaces the current item(if any) of that type
//
// PARAMETERS:  (const ClipboardFormatType) format - Text, ink, bitmap, etc.
//					 (const void *) ptr - Pointer to the item to place on 
//												the clipboard.
//					 (UInt16) length - Size in bytes of the item to place on
//												the clipboard.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ClipboardAddItem (const ClipboardFormatType format, const void *ptr, UInt16 length)
{
	switch (format) {
		case clipboardText:
			clipBoardItem.item = ptr;
			clipBoardItem.length = length;
			break;
		case clipboardInk:
			clipBoardItem.item = ptr;
			clipBoardItem.length = length;
			break;
		case clipboardBitmap:
			clipBoardItem.item = ptr;
			clipBoardItem.length = length;
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ErrFatalDisplay
//
// DESCRIPTION: This routine displays an error alert dialog.
//
// PARAMETERS:  (Char *) msg - Error message text as a string.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ErrFatalDisplay (Char *msg)
{ 
	FormDisplayAlert (msg);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ErrFatalDisplayIf
//
// DESCRIPTION: This routine displays an error alert dialog if condition
//					 is true and error checking is set to partial or full.
//
// PARAMETERS:  (Boolean) condition - A Boolean value. If true, display
//										the error.
//					 (Char *) msg - Error message text as a string.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ErrFatalDisplayIf (Boolean condition, Char *msg)
{ 
	if ( condition ) {
		FormDisplayAlert (msg);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ErrNonFatalDisplayIf
//
// DESCRIPTION: This routine displays an error alert dialog if condition
//					 is true and error checking is set to full.
//
// PARAMETERS:  (Boolean) condition - A Boolean value. If true, display
//										the error.
//					 (Char *) msg - Error message text as a string.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ErrNonFatalDisplayIf (Boolean condition, Char *msg)
{ 
	if ( condition ) {
		FormDisplayAlert (msg);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FtrGet
//
// DESCRIPTION: This routine get a feature.
//
// PARAMETERS:  (UInt32) creator - Creator ID.
//					 (UInt16) featureNum - Feature number of the feature.
//					 (UInt32 *) valueP - Value of the feature is returned 
//												here.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FtrGet (UInt32 creator, UInt16 featureNum, UInt32 *valueP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysAppLaunch
//
// DESCRIPTION: This routine open an application from a specified 
//					 database and card, with the appropriate launch flags.
//					 Generally used to launch an application as a subroutine
//					 of the caller.
//
// PARAMETERS:  (UInt16) cardNo - cardNo identiy the application.
//					 (LocalID) dbID - dbID identiy the application.
//					 (UInt16) launchFlags - Set to 0.
//					 (UInt16) cmd - Launch code.
//					 (MemPtr) cmdPBP - Launch code parameter block.
//					 (UInt32 *) resultP - Pointer to what's returned by the
//										application's PilotMain routine.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SysAppLaunch (UInt16 cardNo, LocalID dbID, UInt16 launchFlags,
						  UInt16 cmd, MemPtr cmdPBP, UInt32 *resultP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysBatteryInfo
//
// DESCRIPTION: This routine retrieve settings for the batteries. Set 
//					 set to false to retrieve battery settings. (Applications
//					 should not change any of the settings).
//
// PARAMETERS:  (Boolean) set - If false, parameters with non-NULL 
//										pointers are retrieved. Nerver set this
//										parameter to true.
//					 (UInt16 *) warnThresholdP - Pointer to battery voltage 
//										warning threshold in volts*100, or NULL.
//					 (UInt16 *) criticalThresholdP - Pointer to the battery
//										voltage critical threshold in volts*100 
//										or NULL.
//					 (UInt16 *) maxTicksP - Pointer to the battery timeout,
//										or NULL.
//					 (SysBatteryKind) kindP - Pointer to the battery kind,
//										or NULL.
//					 (Boolean *) pluggedIn - Pointer to pluggedIn return value,
//										or NULL.
//					 (UInt8 *) percentP - Percentage of power remaining in the
//										battery.
//
// RETURNED:    Returns the current battery voltage in vlots*100.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 SysBatteryInfo (Boolean set, UInt16 *warnThresholdP,
								 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
								 SysBatteryKind *kindP, Boolean *pluggedIn, 
								 UInt8 *percentP)
{
	UInt8		percent;

	if ( !set ) {
		if ( kindP )	
			*kindP = sysBatteryKind;
		if ( warnThresholdP ) 
			*warnThresholdP = sysBatteryValue[sysBatteryKind].warnThrehsold;
		if ( criticalThresholdP )
			*criticalThresholdP = sysBatteryValue[sysBatteryKind].criticalThreshold;
		if ( maxTicksP ) 
			*maxTicksP = sysBatteryValue[sysBatteryKind].maxTicks;
		if ( pluggedIn ) 
			*pluggedIn = sysBatteryValue[sysBatteryKind].pluggedIn;
		if ( percentP ) {
			percent = (UInt8)(sysBatteryCurrentVolts*100/sysBatteryValue[sysBatteryKind].maxVolts);
			if ( percent > 100 )	percent = 100;
			*percentP = percent;
		}
	}

	return	sysBatteryCurrentVolts;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysBatteryInfoV20
//
// DESCRIPTION: This routine retrieve settings for the batteries. Set 
//					 set to false to retrieve battery settings. (Applications
//					 should not change any of the settings).
//
// PARAMETERS:  (Boolean) set - If false, parameters with non-NULL 
//										pointers are retrieved. Nerver set this
//										parameter to true.
//					 (UInt16 *) warnThresholdP - Pointer to battery voltage 
//										warning threshold in volts*100, or NULL.
//					 (UInt16 *) criticalThresholdP - Pointer to the battery
//										voltage critical threshold in volts*100 
//										or NULL.
//					 (UInt16 *) maxTicksP - Pointer to the battery timeout,
//										or NULL.
//					 (SysBatteryKind) kindP - Pointer to the battery kind,
//										or NULL.
//					 (Boolean *) pluggedIn - Pointer to pluggedIn return value,
//										or NULL.
//
// RETURNED:    Returns the current battery voltage in vlots*100.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 SysBatteryInfoV20 (Boolean set, UInt16 *warnThresholdP,
								 UInt16 *criticalThresholdP, UInt16 *maxTicksP,
								 SysBatteryKind *kindP, Boolean *pluggedIn)
{
	if ( !set ) {
		if ( kindP )	
			*kindP = sysBatteryKind;
		if ( warnThresholdP ) 
			*warnThresholdP = sysBatteryValue[sysBatteryKind].warnThrehsold;
		if ( criticalThresholdP )
			*criticalThresholdP = sysBatteryValue[sysBatteryKind].criticalThreshold;
		if ( maxTicksP ) 
			*maxTicksP = sysBatteryValue[sysBatteryKind].maxTicks;
		if ( pluggedIn ) 
			*pluggedIn = sysBatteryValue[sysBatteryKind].pluggedIn;
	}

	return	sysBatteryCurrentVolts;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysCreatePanelList
//
// DESCRIPTION: This routine generate a list of panels found on the 
//					 memory cards and return the result. Multiple versions 
//					 of a panel are listed once.
//
// PARAMETERS:  (UInt16 *) panelCount - Pointer to set to the number
//												of panels.
//					 (MemHandle *) panelIDs - Pointer to the handle 
//												containing a list of panels.
//
// RETURNED:    Returns false if no panels were found, true if panels
//					 were found. panelCount is updated to the number of 
//					 panels found; panelIDs is updated to the IDs of panels
//					 found.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean SysCreatePanelList (UInt16 *panelCount, MemHandle *panelIDs)
{
	if ( sysPanelCount ) {
		*panelCount = sysPanelCount;
		Vmemcpy (panelIDs, sysPanelIDs, sizeof(MemHandle)*sysPanelCount);

		return	true;
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysCurAppDatabase
//
// DESCRIPTION: This routine returns the card number and database ID of
//					 the current application's resource database.
//
// PARAMETERS:  (UInt16 *) cardNoP - Pointer to the card number; 0 or 1
//					 (LocalID *) dbIDP - Pointer to the database ID.
//
// RETURNED:    Returns 0 if no error, or SysErrParamErr if an error
//					 occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SysCurAppDatabase (UInt16 *cardNoP, LocalID *dbIDP)
{
	*cardNoP = curCardNo;
	*dbIDP =	curDBID;

	return	errNone;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysGetOSVersionString
//
// DESCRIPTION: This routine returns ther version number of the Wiscore
//					 operating system.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns a string such as "V. 1.0.".
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char *SysGetOSVersionString ()
{
	return	OSVersion;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysKeyboardDialog
//
// DESCRIPTION: This routine pop up the system keyboard if there is a 
//					 field object with the focus. The field object's text
//					 chunk is edited directly.
//
// PARAMETERS:  (KeyboardType) kbd - The keyboard type.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void SysKeyboardDialog (KeyboardType kbd)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysKeyboardDialogV10
//
// DESCRIPTION: This routine pop up the system keyboard if there is a 
//					 field object with the focus. The field object's text
//					 chunk is edited directly.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void SysKeyboardDialogV10 ()
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysLibFind
//
// DESCRIPTION: This routine returns number for a library that is
//					 already loaded, given its name.
//
// PARAMETERS:  (const Char *) nameP - Pointer to the name of a loaded
//												library.
//					 (UInt16 *) refNumP - Pointer to a variable for returning
//										the library reference number (on failure,
//										this variable is undefined)
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SysLibFind (const Char* nameP, UInt16 *refNumP)
{
	if ( (Vstrlen (nameP) >= 14) && (Vstrcmp (nameP, "Serial Library") == 0) ) {
		*refNumP = 1;
		return	0;
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysRandom
//
// DESCRIPTION: This routine returns a random number anywhere from
//					 0 to sysRandomMax.
//
// PARAMETERS:  (Int16) newSeed - New seed value, or 0 to use existing
//											seed.
//
// RETURNED:    Returns a random number.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 SysRandom (UInt32 newSeed)
{
	if ( newSeed )
		Vsrand (newSeed);

	return	(Int16)Vrand ();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysTaskDelay
//
// DESCRIPTION: This routine put the processor into doze mode for the
//					 specified number of ticks.
//
// PARAMETERS:  (Int32) delay - Number of ticks to wait.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SysTaskDelay (Int32 delay)
{
	sysDelay = delay;
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysTicksPerSecond
//
// DESCRIPTION: This routine returns the number of ticks per second. 
//					 This routine allows applications to be tolerant of 
//					 changes to the ticks per second rate in the system.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the number of ticks per second.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 SysTicksPerSecond (void)
{
	return	sysTicks;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysUIAppSwitch
//
// DESCRIPTION: This routine try to make the current UI application quit
//					 and the launch the UI application specified by card
//					 number and database ID.
//
// PARAMETERS:  (UInt16) cardNo - Card number for the new application;
//					 (LocadID) dbID - ID of the new application.
//					 (UInt16) cmd - Action code (launch code).
//					 (MemPtr) cmdPBP - Action code parameter block.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SysUIAppSwitch (UInt16 cardNo, LocalID dbID, UInt16 cmd, 
							 MemPtr cmdPBP)
{
	curCardNo = cardNo;
	curDBID = dbID;

	return	errNone;
}
