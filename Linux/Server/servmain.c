/*
 * Copyright (c) 1999, 2000 Greg Haerr <greg@censoft.com>
 * Copyright (c) 1991 David I. Bell
 * Permission is granted to use, distribute, or modify this source,
 * provided that this copyright notice remains intact.
 *
 * Main module of graphics server.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#include <Common.h>
#include <vxddk.h>
#include "wisapi.h"
#include "pipeapi.h"
#include "pipefunc.h"



#ifndef	ICONWIDTH
#define	ICONWIDTH	50
#endif

#ifndef	ICONHEIGHT
#define	ICONHEIGHT	35
#endif

#define	ICONSTARTX		5
#define	ICONSTARTY		20

#define	ICONRECTWIDTH	20
#define	ICONRECTHEIGHT	20

#define	APPSONSCREEN	12
#define	ITEMSPERROW		3
#define	ITEMSPERCOL		4

#define	NumAPIFunctions		923


#define	MAINFORM		9999


#define	MenuApp					1
#define	ItemInstall				11
#define	ItemDelete				12
#define	ItemBeam					13
#define	ItemCategory			14
#define	ItemInfo					15

#define	MenuOptions				2
#define	ItemPreference			21
#define	ItemAbout				22


struct FuncCount {
	int	index;
	int	count;
} funcCount[] = {
	{ 100, 0 },
   { 101, 4 },
   { 102, 13 },
   { 103, 29 },
   { 104, 35 },
   { 105, 38 },
   { 106, 42 },
   { 107, 62 },
   { 108, 68 },
   { 109, 136 },
   { 110, 142 },
   { 111, 151 },
   { 112, 158 },
   { 113, 210 },
   { 114, 226 },
   { 115, 230 },
   { 116, 242 },
   { 117, 259 },
   { 118, 324 },
   { 119, 343 },
   { 120, 348 },
   { 121, 354 },
   { 122, 357 },
   { 123, 379 },
   { 124, 393 },
   { 125, 410 },
   { 126, 454 },
   { 127, 468 },
   { 128, 471 },
   { 129, 473 },
   { 130, 514 },
   { 131, 517 },
   { 132, 538 },
   { 133, 542 },
   { 134, 549 },
   { 135, 553 },
   { 136, 555 },
   { 137, 564 },
   { 138, 566 },
   { 139, 572 },
   { 140, 578 },
   { 141, 579 },
   { 142, 583 },
   { 143, 591 },
   { 144, 601 },
   { 145, 618 },
   { 146, 622 },
   { 147, 628 },
   { 148, 633 },
   { 149, 652 },
   { 150, 655 },
   { 151, 680 },
   { 152, 713 },
   { 153, 771 },
   { 154, 809 },
   { 155, 826 },
   { 156, 829 },
   { 157, 832 },
   { 158, 836 },
   { 159, 842 },
	{ 160, 922 }
};


#define	WTransFunction(type)		(funcCount[(type/100-100)].count+(type%100))
//
// External definitions defined here.
//
static void APM_ReceiveAPICallLoop(void);
void APM_DrawScreen (Boolean beLoadDB);
extern Boolean VSetRCPFile (Char *filename);
extern void Calibrate_Tablet ();


Boolean	StopReceiveAPICall=false;
MenuBarType				*menuP;
extern unsigned char *pipe_ram;
extern EventType	*CurEvent;
int sem_callid;

struct AppList {
	Char	appName[16];
	Char	appFileName[32];
	Char	rscName[32];
	int	appSize;
} appList[] = {
	{ "Calibrate", "digichek", "digichek.rcp", 10},
	{ "Date", "date", "date.rcp", 10},
	{ "Memo", "memo", "memo.rcp", 10},
	{ "5x5", "5x5", "5x5.rcp", 10},
	{ "calculator", "calculator", "calculator.rcp", 10},
	{ "Address", "address", "address.rcp", 10}, 
	{ "Mail", "pmail", "pmail.rcp", 10},
};

Int16				rowSelect=0;	// current select record
Int16				colSelect=0;	// current select record
Word				numRecords=sizeof(appList)/sizeof(struct AppList);
UInt				appTopRowItem = 0;
UInt				CurrentForm = MAINFORM;
Int16				sysHancleCount = 0;
extern int		DisplayDev, TouchPadDev;

Boolean WriteParameter (void *ptr, int length, int offset)
{
	memcpy (&(pipe_ram[APIADDRESSOFFSET+WTransFunction(offset)*sizeof(void *)]), &ptr, length);
}

void PipeVSetRCPFile (void)
{
	WriteParameter (VSetRCPFile, sizeof(void*), pVSetRCPFile);
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
void GoToApplication (Word index)
{
	char			abx;
	RectangleType	rect;

	WClearScreen (1);

	// index == 0, calibrate the tablet
	if ( index == 0 ) {
		Calibrate_Tablet ();
		APM_DrawScreen (true);
		WSetMenu (menuP);
		return;
	}

	if ( vfork () == 0) {
		char	*args[4];

		args[0] = appList[index].appFileName;
		args[1] = appList[index].rscName;
		args[2] = NULL;
		args[3] = NULL;

		if ( execv (appList[index].appFileName, args) == -1 ) {
			if( semctl( sem_callid, 0, SETVAL, 1) != 0 ) {
				perror( "SERVER: semctl" );
			}
		}

		exit (1);
	} else {
		struct sembuf lock_sembuf[1];

		// set semaphore operation option
		lock_sembuf[0].sem_num   =  0;
		lock_sembuf[0].sem_op    =  -1;
		lock_sembuf[0].sem_flg   =  0;

		// wait client finished
		if( semop( sem_callid, lock_sembuf, 1) == -1 ) {
			perror("SERVER: semop");
		}

//			FrmCloseAllForms ();
		APM_DrawScreen (true);
		WSetMenu (menuP);
	}
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
	DateTimeType	datetime;
	char		buffer[12];
	UInt		index, startItem, strWidth;
	RectangleType	rect;

	WClearScreen (SCREEN_DISPLAY);

	VGetSystemTime (&datetime);

	TimeToAscii ((UInt8)(datetime.hour+8), (UInt8)(datetime.minute), tfColonAMPM, buffer);
	strWidth = FntCharsWidth (buffer, (short)strlen(buffer));

	// Clear title area (display time)
	rect.topLeft.x = PDASTARTX;
	rect.topLeft.y = PDASTARTY;
	rect.extent.x = strWidth+4;
	rect.extent.y = TitleHeight;
	VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_PARTSTRETCH, DRAW_SET);

	VDrawString( 2, 2, buffer, Vstrlen(buffer), SINGLELINE, CL_BACKGROUND, COORD_PARTSTRETCH);


	VDrawLine ( 0, 12, 160, 12, 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( 0, 13, 160, 13, 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);

	// Draw battery
	WDrawBattery (100);
/*
	// Draw installed application
	if ( beLoadDB ) {
		if( APMGetDatabase(APMCREATORID) ) 
			return;
	}

	// Get Installed application and draw icon on screen
	if ( numRecords > APPSONSCREEN ) {	// can't draw all app on one screen, add scrollbar
		scrollBar.bounds.topLeft.x = 150;
		scrollBar.bounds.topLeft.y = 20;
		scrollBar.bounds.extent.x = 10;
		scrollBar.bounds.extent.y = 135;
		scrollBar.minValue = 0;
		scrollBar.maxValue = ((numRecords+ItemPerRow-1)/ItemPerRow);
		scrollBar.value = appTopRowItem;
		scrollBar.pageSize = APPSONSCREEN/ItemPerRow;
		SclDrawScrollBar (&scrollBar);
	}
*/
	startItem = appTopRowItem*ITEMSPERROW;
	for ( index = appTopRowItem*ITEMSPERROW; 
			(index < numRecords)&&(index<(appTopRowItem*ITEMSPERROW+APPSONSCREEN));
			index++ ) {
//		APM_GetApplication (index);
		// Draw a black block 1 instead of application icon (memo)
		rect.topLeft.x = (ICONSTARTX+((index-startItem)%ITEMSPERROW)*ICONWIDTH+(ICONWIDTH-ICONRECTWIDTH)/2);
		rect.topLeft.y = (ICONSTARTY+((index-startItem)/ITEMSPERROW)*ICONHEIGHT);
		rect.extent.x = ICONRECTWIDTH;
		rect.extent.y = ICONRECTHEIGHT;
		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
		VDrawString (rect.topLeft.x, rect.topLeft.y+20, 
			appList[index].appName,	Vstrlen (appList[index].appName), 
			SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
	}

//	FrmSetEventHandler(NULL, (FormEventHandlerPtr) NULL);

}


////////////////////////////////////////////////////////////////////////
// FUNCTION:    MappingAPIFunction
//
// DESCRIPTION: This routine mapping all API function address to shared
//					 memory
//
// PARAMETERS:  None.
//
// RETURNED:    None.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void MappingAPIFunction ()
{
	int	index;

	for ( index = 0; index < NumAPIFunctions; index++ ) {
		GrFunctions[index].func ();
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
//	GetCurrentDirectory(256, APM_Directory);

	// Get semaphore key
	if( (sem_callid = semget( sem_callkey, 1, IPC_CREAT )) == -1 ) {
//		perror( "SERVER: semget" );
		return	-1;
	}

	MappingAPIFunction ();
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
	close (DisplayDev);
	close (TouchPadDev);
//	VCPDbCloseDB ();
	WMenuRelease (menuP);
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
Int16 CheckHitCtrl (EventType *event)
{
	RectangleType r;
	Int16			item;
   
   // If the user taps in the RecordViewDisplay take them to the Edit View
	RctSetRectangle (&r, ICONSTARTX+(ICONWIDTH-ICONRECTWIDTH)/2, ICONSTARTY, 
							ICONSTARTX+ICONWIDTH*(ITEMSPERROW-1)+ICONRECTWIDTH+(ICONWIDTH-ICONRECTWIDTH)/2, 
							ICONSTARTY+ICONHEIGHT*(ITEMSPERCOL-1)+ICONRECTHEIGHT);

	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {
		// Check is click on scrollBar
		if ( numRecords > APPSONSCREEN ) {	// can't draw all app on one screen, add scrollbar
			if ( event->screenX > 150 ) {
				event->eType = sclEnterEvent;
				
				return	-1;
			}
		}

		// calculate selected row with hit point
		rowSelect = (event->screenX-ICONSTARTX-(ICONWIDTH-ICONRECTWIDTH)/2)/ICONWIDTH;

		if ( event->screenX > (rowSelect*ICONWIDTH+ICONRECTWIDTH+ICONSTARTX+(ICONWIDTH-ICONRECTWIDTH)/2) ) {
			rowSelect = -1;
		}

		// calculate selected column with hit point
		colSelect = (event->screenY-ICONSTARTY)/ICONHEIGHT;
		if ( event->screenY > (colSelect*ICONHEIGHT+ICONRECTHEIGHT+ICONSTARTY) ) {
			colSelect = -1;
		}

		item = colSelect*ITEMSPERROW+rowSelect;

//printf ("Goto Application[%d],(%d,%d)\n", item, rowSelect, colSelect);
		if ( (rowSelect != -1) && (colSelect != -1) && (item < numRecords) ) {
			return	item;
		}
	}
      
	return	-1;
}

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
	EventType	event;
	Int16			item;
	short		err;

	do {
		if ( CurrentForm = MAINFORM ) {
			EvtGetEvent(&event, evtWaitForever);

			if (SysHandleEvent(&event)) continue;
			MenuHandleEvent((void *)0, &event, &err);;

			if ( (event.eType == penUpEvent) ) {
				if ( (item = CheckHitCtrl (&event)) >= 0) {
					CurrentForm = 1009;
					WFlushEvent ();
					GoToApplication (item);
					CurrentForm = MAINFORM;
				}
			}
		}
	} while(event.eType != sysExitEvent);

}

//
// This is the main server loop which initialises the server, services
// the clients, and shuts the server down when there are no more clients.
//
int
ApplicationManager()
{
	int	error;
	char	abx;

	error = APM_StartApplication();	// Application start code

	if (error) return error;
	APM_EventLoop();	// Event loop

	APM_StopApplication ();	// Application stop code

	return 0;
}
