/*========================================================
  APM.c

  Application manager

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0511, 2001 by Jerry Chu
 =========================================================*/
#include <stdio.h>
#include <windows.h>

#define  _APM_SIMULATOR
#define	_WISIMPORTDLL

#include	<VCommon.h>
#include <VParser.h>
//#include <VPdaSdk.h>
#include <ApiDll.h>
#include <WisDll.h>
#include "comdlg.h"

#define true	TRUE
#define false	FALSE

#ifndef	ICONWIDTH
#define	ICONWIDTH	50
#endif

#ifndef	ICONHEIGHT
#define	ICONHEIGHT	35
#endif

#define	APPSONSCREEN	12

#define	ResourceFileName	"WisResource.h"
#pragma pack(2)

#include 	"APM.h"


//__declspec( dllexport ) DWord  ApplicationManager ();


//char	RCPFileName[] = "Preference.RCP";
#define	APMDBName						"APMDB"
#define	APMDBType						'DATA'
#define	APMCREATORID					'ChuJ'


#define	ItemPerRow				3

DmOpenRef	APMDB;		//  Memo database
Word						rowSelect=0;	// current select record
Word						colSelect=0;	// current select record
Word				numRecords=0;
UInt				CurrentCategory = dmAllCategories;	// currently displayed category
static char				CategoryName [dmCategoryLength];
MenuBarType				*menuP;
UInt				CurrentForm = MAINFORM;
Char				APM_Directory[256]="";
ScrollBarType	scrollBar;	// scroll bar to scroll screen to see more app.
UInt				appTopRowItem = 0, appTopColItem;

HMODULE				appInst=NULL;

HWND hwnd;

extern Boolean APM_AddApplication (const Char *szFileName, const Char *resourceFileName);
extern void APM_GetApplication (UInt index);
extern Boolean InstallApp ();
extern void DeleteApp ();
extern Boolean frmDelAppEventHander(EventPtr event);

typedef __declspec (dllimport) DWord (PilotMain) (Word, Ptr, Word);
typedef __declspec (dllimport) unsigned char *(GetResource) (unsigned char *index);
Boolean APM_AddApplication (const Char *szFileName, const Char *resourceFileName);


////////////////////////////////////////////////////////////////////////
// FUNCTION:    APMGetDatabase
//
// DESCRIPTION: This routine convert the date passed to formatted string.
//
// PARAMETERS:  (ULong) dbcreatorid - Hours.
//					 (Word) mode - Minutes.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err APMGetDatabase (ULong dbcreatorid)
{
	Err			error = 0;
	Word			cardNo=0;
	VoidHand		hAppInfo;	// CH.9 Handle to the app info block
	AppInfoType	*mem;
	LocalID 		dbID, appInfoID;
	UInt			i;
	Char			*name[4] = { "Unfiled", "Business", "Personal", "" };
	Word			mode = dmModeReadWrite;
	Char			DBFileName[256];

	strcpy (DBFileName, APM_Directory);
	strcat (DBFileName, "\\");
	strcat (DBFileName, APMDBName);
	// Find the application's data file.  If it doesn't exist create it.
	error = DmCreateDatabase (cardNo, DBFileName, dbcreatorid, APMDBType, false);

	if ((error == 0)||(error == dmErrAlreadyExists)) {
      APMDB = DmOpenDatabaseByTypeCreator(APMDBType,dbcreatorid,mode);
		
		if (!APMDB)
			return (1);
	}

	if ( error != dmErrAlreadyExists ) {
		DmOpenDatabaseInfo (APMDB, &dbID, NULL, NULL, &cardNo, NULL);
		DmDatabaseInfo (cardNo, dbID, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &appInfoID, NULL, NULL, NULL);

		if ( appInfoID == 0 ) {
			if ( (hAppInfo = DmNewHandle (APMDB, sizeof (AppInfoType)) ) == NULL )
				return -1;
			appInfoID = MemHandleToLocalID (hAppInfo);
			DmSetDatabaseInfo (cardNo, dbID, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &appInfoID, NULL, NULL, NULL);
			mem = MemLocalIDToLockedPtr (appInfoID, cardNo);
			DmSet (mem, 0, sizeof (AppInfoType), 0);
			WCategoryInitialize (mem);

			for ( i = 0; i < 3; i++ ) {
				CategorySetName (APMDB, i, name[i]);
			}

			for ( i = 3; i < 16; i++ ) {
				CategorySetName (APMDB, i, name[3]);
			}

			MemPtrUnlock (mem);

			// Add System default application
			APM_AddApplication ("MemoDll.dll", "memo.rcp");
			APM_AddApplication ("PhoneBookDll.dll", "PhoneBook.rcp");
		}
	}

	// CH.5 Get the number of records in the database
	rowSelect = numRecords = DmNumRecords( APMDB );

	return 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VCPDbCloseDB
//
// DESCRIPTION: This routine close an opened database
//
// PARAMETERS:  None.
//
// RETURNED:    Returns errNone if no error, or error code if an error occurs.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int VCPDbCloseDB()
{
	int rc;

	rc=DmCloseDatabase (APMDB);
	APMDB = NULL;
	WCategoryRelease ();

	return(rc);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_DrawScreen
//
// DESCRIPTION: This routine draw the start up screen of application
//					 manager.
//
// PARAMETERS:  (Boolean) beLoadDB - true for load database.
//
// RETURNED:    Returns none.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/05/01	Initial Revision
//			Jerry	8/30/01	Add scroll bar drawing
////////////////////////////////////////////////////////////////////////
void APM_DrawScreen (Boolean beLoadDB)
{
	RectangleType	rect;
	DateTimeType	datetime;
	Char	buffer[9];
	UInt	index, startItem, strWidth;

	WClearScreen (SCREEN_DISPLAY);

	// Get current time string
	VGetSystemTime (&datetime);
	TimeToAscii ((UInt8)(datetime.hour+8), (UInt8)(datetime.minute), tfColonAMPM, buffer);
	strWidth = FntCharsWidth (buffer, (short)Vstrlen(buffer));

	// Clear title area (display time)
	WinDrawTitleChars (buffer, (UInt16)Vstrlen(buffer), PDASTARTX, PDASTARTY);
	VDrawLine ( 0, 12, 158, 12, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

	// Draw battery
	WDrawBattery (100);

	// Draw installed application
	if ( beLoadDB ) {
		if( APMGetDatabase(APMCREATORID) ) 
			return;
	}

	// Get Installed application and draw icon on screen
	if ( numRecords > APPSONSCREEN ) {	// can't draw all app on one screen, add scrollbar
		scrollBar.bounds.topLeft.x = 150;
		scrollBar.bounds.topLeft.y = 20;
		scrollBar.bounds.extent.x = 7;
		scrollBar.bounds.extent.y = 135;
		scrollBar.minValue = 0;
		scrollBar.maxValue = ((numRecords+ItemPerRow-1)/ItemPerRow)-APPSONSCREEN/ItemPerRow;
		scrollBar.value = appTopRowItem;
		scrollBar.pageSize = APPSONSCREEN/ItemPerRow;
		SclDrawScrollBar (&scrollBar);
	}

	startItem = appTopRowItem*ItemPerRow;
	for ( index = appTopRowItem*ItemPerRow; 
			(index < numRecords)&&(index<(appTopRowItem*ItemPerRow+APPSONSCREEN)); 
			index++ ) {
		APM_GetApplication (index);
		// Draw a black block 1 instead of application icon (memo)
		rect.topLeft.x = (5+((index-startItem)%ItemPerRow)*ICONWIDTH);
		rect.topLeft.y = (20+((index-startItem)/ItemPerRow)*ICONHEIGHT);
		rect.extent.x = 15;
		rect.extent.y = 15;
		VDrawString (rect.topLeft.x, (Coord)(rect.topLeft.y+20),
			appList[index].appName,	Vstrlen (appList[index].appName), 
			SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_StartApplication
//
// DESCRIPTION: This routine initialize start up information and screen
//					 of application manager.
//
// PARAMETERS:  None.
//
// RETURNED:    Always returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int APM_StartApplication(void)
{
	// Get current Directory.
	GetCurrentDirectory(256, APM_Directory);
 
	APM_DrawScreen (true);

	// Initialize Menu of application manager
	menuP = WMenuInitialize ();

	// Add menu item for App category
	WMenuAddItem (0, -1, 1, MenuApp, "App");
	WMenuAddItem (0, 0, ItemInstall, 0, "Install");
	WMenuAddItem (0, 1, ItemDelete, 0, "Delete");
	WMenuAddItem (0, 2, ItemBeam, 0, "Beam");
	WMenuAddItem (0, 3, ItemCategory, 0, "Category");
	WMenuAddItem (0, 4, ItemInfo, 0, "Info");

	// Add menu item for Options category
	WMenuAddItem (1, -1, MenuOptions, 0, "Options");
	WMenuAddItem (1, 0, ItemPreference, 0, "Preference");
	WMenuAddItem (1, 1, ItemAbout, 0, "About Application");

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_StopApplication
//
// DESCRIPTION: This routine close all resource opened by application
//					 manager.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns none.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
static void APM_StopApplication(void)
{
	VCPDbCloseDB ();
	WMenuRelease (menuP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    frmPrefEventHander
//
// DESCRIPTION: This routine is the preference event handler
//
// PARAMETERS:  (EventPtr) event - Pointer to event structure.
//
// RETURNED:    Returns handle.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean frmPrefEventHander(EventPtr event)
{
	FormPtr  form;
	int      handled = 0;

	form = FrmGetActiveForm();

	switch (event->eType) {
		case frmOpenEvent:
			FrmDrawForm(form);
			handled = 1;
			break;
	}

	return handled;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CheckHitCtrl
//
// DESCRIPTION: This routine check is hitting on application icon.
//
// PARAMETERS:  (EventType) event - The current event.
//					 (Word) mode - Minutes.
//
// RETURNED:    Returns hitting appliction index if hitting on application
//					 Icon.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
//			Jerry	8/30/01	Add check hitting scroll bar
////////////////////////////////////////////////////////////////////////
UInt16 CheckHitCtrl (EventType *event)
{
	Boolean     handled = false;
	RectangleType r;
	Int16		index;
   
  
   // If the user taps in the RecordViewDisplay take them to the Edit View
	RctSetRectangle (&r, 5, 20, 155, 140);	// Control Panel block
	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {
		// Check is click on scrollBar
		if ( numRecords > APPSONSCREEN ) {	// can't draw all app on one screen, add scrollbar
			if ( event->screenX > 150 ) {
				event->eType = sclEnterEvent;
				
				return	handled;
			}
		}

		// calculate selected row with hit point
		rowSelect = (event->screenX-5)/ICONWIDTH;
		// calculate selected column with hit point
		colSelect = (event->screenY-20)/ICONHEIGHT;

		index = colSelect*ItemPerRow+rowSelect;
		RctSetRectangle (&r, (5+((index)%ItemPerRow)*ICONWIDTH),
								(20+((index/ItemPerRow)*ICONHEIGHT)),
								15, 15);

		if ( !RctPtInRectangle (event->screenX, event->screenY, &r) ) {
			rowSelect = -1;
			colSelect = -1;
		}

		if ( (rowSelect != -1) && (colSelect != -1) ) {
			handled = true;
		}
	}
      
	return handled;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Preference
//
// DESCRIPTION: This routine setting all preference about system.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void Preference ()
{
}

// define calibrate variable
#define	tPadCaliWidth		(Coord)100
#define	tPadCaliHeight		(Coord)100

int	tPadDiffX=1513, tPadDiffY=1149;
int	tBaseX=13, tBaseY=19;
short	tPadX=0, tPadY=0;

void Calibrate_Tablet ()
{
	EventType	event;
	int	x1, y1, x2, y2, x3, y3;
	int	diffX1, diffX2, diffY1, diffY2;

	// Calibrate the left top postion

	do {
		do {
			WClearScreen (SCREEN_DISPLAY);
			VDrawLine ( 10, 20, 30, 20, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			VDrawLine ( 20, 10, 20, 30, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			do {
				EvtGetEvent (&event, -1);
			} while (event.eType!=penUpEvent);
			x1 = event.screenX;
			y1 = event.screenY;

			// Calibrate the right bottom postion
			WClearScreen (SCREEN_DISPLAY);
			VDrawLine ( 130, 140, 150, 140, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			VDrawLine ( 140, 130, 140, 150, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

			do {
				EvtGetEvent (&event, -1);
			} while (event.eType != penUpEvent);
			x2 = event.screenX;
			y2 = event.screenY;

			diffX1 = Vabs (x2-x1);
			diffY1 = Vabs (y2-y1);
		} while ( (diffX1 < (PDAWIDTH/8*5)) || (diffY1 < (PDAHEIGHT/8*5)) ||
					(diffX1 > (PDAWIDTH/8*7)) || (diffY1 > (PDAHEIGHT/8*7)) );

		// Calibrate the center postion
		WClearScreen (SCREEN_DISPLAY);
		VDrawLine ( 70, 80, 90, 80, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
		VDrawLine ( 80, 70, 80, 90, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

		do {
			EvtGetEvent (&event, -1);
		} while (event.eType != penUpEvent);
		x3 = event.screenX;
		y3 = event.screenY;

		diffX1 = Vabs (x3-x1);
		diffX2 = Vabs (x2-x3);
		diffY1 = Vabs (y3-y1);
		diffY2 = Vabs (y2-y3);

		tPadDiffX = ((x3-x1)+(x2-x3))/2;
		tPadDiffY = ((y3-y1)+(y2-y3))/2;
	} while ( (Vabs(diffX1-diffX2) > (PDAWIDTH/16)) || (Vabs(diffY1-diffY2) > (PDAHEIGHT/16)) );

	tBaseX = (x1*tPadCaliWidth/tPadDiffX)-20;
	tBaseY = (y1*tPadCaliHeight/tPadDiffY)-20;
}

Boolean VSetResource (unsigned char *index, unsigned char *string)
{
	FormType	*formPtr, formP;
	int	formCount;

	sscanf (index, "%2d", &formCount);

	memcpy (&formP, string, sizeof(FormType));

	return	true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GoToApplication
//
// DESCRIPTION: This routine decide which application been select, 
//					 and change the control to specified application.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
//			Jerry	8/30/01	Add scrollbar, index change
////////////////////////////////////////////////////////////////////////
void GoToApplication ()
{
	PilotMain	*WISPilotMain;
	GetResource	*WISGetResource;
	unsigned char	*string, resIndex[1024];
	char			abx;
	int			index = colSelect*ItemPerRow+rowSelect+appTopRowItem*ItemPerRow;
/*
	if ( index == numRecords ) {
		WClearScreen (SCREEN_DISPLAY);
		Calibrate_Tablet ();
		APM_DrawScreen (true);
		WSetMenu (menuP);
		return;
	}
*/
	if ( !appInst && (index < numRecords) ) {
		appInst = LoadLibrary (appList[index].appFileName);
		if ( appInst ) {
			WISPilotMain = (PilotMain *) GetProcAddress(appInst, "PilotMain");
/*
			WISGetResource = (GetResource *) GetProcAddress (appInst, "GetResource");

			if ( WISPilotMain && WISGetResource ) {
				string = (WISGetResource) (resIndex);
				if ( VSetResource (resIndex, string) ) {
*/
			if ( WISPilotMain ) {
				if ( VSetRCPFile (appList[index].rscName) ) {
					VCPDbCloseDB ();
					WClearScreen (SCREEN_DISPLAY);
					(*WISPilotMain) ((Word)sysAppLaunchCmdNormalLaunch, &abx, (Word)0);
					FrmCloseAllForms ();
					APM_DrawScreen (true);
					WSetMenu (menuP);
				}
			}

			FreeLibrary (appInst);
			appInst = NULL;
		} else {
			DWORD	err = GetLastError ();
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetScrollBarPos
//
// DESCRIPTION: This routine calculate the new scroll bar position.
//
// PARAMETERS:  (UInt *) topRowItem - The row number of first icon.
//					 (UInt *) topColItem - The column number of first icon.
//					 (EventType *) evnet - Pointer to event structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GetScrollBarPos ( UInt *topRowItem, UInt *topColItem, EventType *event )
{
	UInt16	newValue;

	newValue = (event->screenY-scrollBar.bounds.topLeft.y)*(scrollBar.maxValue+APPSONSCREEN/ItemPerRow)/
					scrollBar.bounds.extent.y;
	if ( newValue > scrollBar.maxValue ) {
		newValue = scrollBar.maxValue;
	}
	event->data.sclExit.value = scrollBar.value;
	event->data.sclExit.newValue = newValue;
	event->eType = sclExitEvent;
}

/*************************************************************************
*  APM_EventLoop - Main event loop
*
*************************************************************************/
////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_EventLoop
//
// DESCRIPTION: This routine is application manager event loop routine.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
//			Jerry	8/30/01	Add sclEnterEvent
////////////////////////////////////////////////////////////////////////
static void APM_EventLoop(void)
{
	short		err;
	UInt	formID;
	FormPtr	form;
	EventType event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (SysHandleEvent(&event)) continue;
		if (MenuHandleEvent((void *)0, &event, &err)) continue;

		if ((CurrentForm == MAINFORM) && (event.eType == penUpEvent)) {
			if ( CheckHitCtrl (&event) ) {
				WResetEvent (&event);
				GoToApplication ();
			}
		} 

		if (event.eType == menuEvent) {
			MenuEraseStatus(0);
			switch (event.data.menu.itemID) {
				case ItemInstall:		// Press Install application menu item
					if ( InstallApp () ) {
						APM_DrawScreen (false);
					}
					break;
				case ItemDelete:		// Press Delete application menu item
					DeleteApp ();
//					FrmSetEventHandler(NULL, (FormEventHandlerPtr) frmDelAppEventHander);
//					CurrentForm = DELETEFORM;
//					WResetEvent (&event);
					break;
			}
/*
		} else if (event.eType == frmLoadEvent) {
			formID = (UInt) event.data.frmLoad.formID;
			form = FrmInitForm(formID);

			switch (formID) {  
				case GeneralForm:
					FrmSetEventHandler(form, (FormEventHandlerPtr) frmPrefEventHander);
					break;  
			}
			FrmSetActiveForm( form );
*/
		} else if (event.eType == sclEnterEvent) {
			GetScrollBarPos ( &appTopRowItem, &appTopColItem, &event );
			appTopRowItem = event.data.sclExit.newValue;
			APM_DrawScreen (false);
		}

		FrmDispatchEvent(&event);
	} while(event.eType!=appStopEvent);
}

/*************************************************************************
*  ApplicationManager - Main function
*
*************************************************************************/
DWord  ApplicationManager ()
{
	int error;
	
	error = APM_StartApplication();	// Application start code

	if (error) return error;
	APM_EventLoop();	// Event loop
	APM_StopApplication ();	// Application stop code

	return 0;
}

int APIENTRY WinMain(HINSTANCE _hInst,     // program instance
                     HINSTANCE _hPrevInst, // previous instance
                     LPSTR _lpCmdLine,     // command line
                     int _nCmdShow)
{
	hwnd = WisWinMain (_hInst, _hPrevInst, _lpCmdLine, _nCmdShow);
	ApplicationManager ();
	WCloseAll ();
	return	0;
}

