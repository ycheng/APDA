/*========================================================
  APM.c

  Application manager

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0511, 2001 by Jerry Chu
 =========================================================*/

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

#define	DeleteAppItemStartX	2
#define	DeleteAppItemStartY	20

#pragma pack(2)

#include 	"APM.h"

extern DmOpenRef	APMDB;		//  Memo database
extern Word			numRecords;
extern Word			rowSelect;	// current select record
extern UInt			CurrentCategory;	// currently displayed category
extern UInt			CurrentForm;
extern Char			*APM_Directory;

extern void APM_DrawScreen (Boolean beLoadDB);
static Boolean RecordViewHandlePen (EventType * event);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_AddApplication
//
// DESCRIPTION: This routine add application information into database.
//
// PARAMETERS:  (const Char *) szFileName - Pointer to application file 
//													name string.
//					 (const Char *) resourceFileName - Pointer to resource
//													file name string.
//
// RETURNED:    Returns true if install successful, false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean APM_AddApplication (const Char *szFileName, const Char *resourceFileName)
{
	VoidHand		hrecord;
	VoidPtr		precord;		// Pointer to the record
	UInt			recAttrs;	// The record's attributes
	UInt			appLength, rscLength, recLength = 0;
	Char			Directory[256];
	Char			rscFileName[256];
	Int32			appSize;

	appLength = (UInt) Vstrlen (szFileName);

	if ( resourceFileName == NULL ) {
		WGetFileDirectory (szFileName, Directory);
		// if resource file not found, skip install application.
		if ( !WGetResourceFileName (Directory, rscFileName) )
			return	false;
	} else {
		strcpy (rscFileName, resourceFileName);
	}

	rscLength = (UInt) strlen (rscFileName);
	recLength = appLength + rscLength + 2*sizeof(UInt) + sizeof(Int32);

	appSize = WGetFileSize (szFileName) + WGetFileSize (rscFileName);

	// Create the database record and get a handle to it
	if( (hrecord = DmNewRecord( APMDB, &numRecords, recLength)) == NULL ) {
		return	false;
	}
	
	// Lock down the record to modify it
	precord = MemHandleLock( hrecord );
	
	// Clear the record
	DmSet (precord, 0, recLength, 0);
	
	// write file length and file name
	DmWrite (precord, 0, &appSize, sizeof(Int32));
	DmWrite (precord, sizeof(Int32), &appLength, sizeof(UInt));
	DmWrite (precord, sizeof(Int32)+sizeof(UInt), szFileName, appLength);
	DmWrite (precord, appLength+sizeof(UInt)+sizeof(Int32), &rscLength, sizeof(UInt));
	DmWrite (precord, appLength+2*sizeof(UInt)+sizeof(Int32), rscFileName, rscLength);

	// Unlock the record
	MemHandleUnlock (hrecord);
	
	// Clear the busy bit and set the dirty bit
	DmReleaseRecord (APMDB, numRecords, true);
	
	// Get the record attribute bits
	DmRecordInfo (APMDB, numRecords, &recAttrs, NULL, NULL);
	
	// Clear the category bits
	recAttrs &= ~dmRecAttrCategoryMask;
	
	// Set the category to the appropriate category
	if( CurrentCategory == dmAllCategories )
		recAttrs |= dmUnfiledCategory;
	else
		recAttrs |= CurrentCategory;
	
	// Set the record attributes
	DmSetRecordInfo(APMDB, rowSelect, &recAttrs, NULL);
						
	// Increment the total record count
	numRecords++;

	return	true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_RemoveApplication
//
// DESCRIPTION: This routine remove application information from database.
//
// PARAMETERS:  (UInt) index - The index of application which would be
//									remove
//
// RETURNED:    Returns true if remove successful, false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err APM_RemoveApplication (UInt	index)
{
	return	DmRemoveRecord (APMDB, rowSelect);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    APM_GetApplication
//
// DESCRIPTION: This routine get installed application name from database
//
// PARAMETERS:  (UInt) index - The index of application information that
//										to be got.
//
// RETURNED:    Returns none.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void APM_GetApplication (UInt index)
{
	VoidHand		h = DmQueryRecord (APMDB, index);
	VoidPtr		precord;	// CH.6 Points to a database record
	Int			length, offset=0;

	if (h) {
		precord = MemHandleLock(h);

		// Get application size
		MemMove(&appList[index].appSize, ((char*)precord+offset), sizeof(Int32));
		offset += sizeof(Int32);

		// Get application file name
		MemMove(&length, ((char*)precord+offset), sizeof(UInt));
		offset += sizeof(UInt);

		if ( length ) {
			MemMove(appList[index].appFileName, ((char*)precord+offset), length);
			offset += length;
		}

		// Get resource file name
		MemMove(&length, ((char*)precord+offset), sizeof(UInt));
		offset += sizeof(UInt);

		if ( length ) {
			MemMove(appList[index].rscName, ((char*)precord+offset), length);
			offset += length;
		}

		// Get the application name
		WGetApplicationName (appList[index].appFileName, appList[index].appName);

		MemHandleUnlock(h);
		DmReleaseRecord (APMDB, index, true);
/*
		DmRecordInfo (APMDB, index, &recAttrs, NULL, NULL);
		recAttrs &= dmRecAttrCategoryMask;
		CategoryGetName (APMDB, recAttrs, catName);
		CurrentCategory = recAttrs;
		CategorySetTriggerLabel (GetObjectPtr(SELKIND), catName);
*/
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InstallApp
//
// DESCRIPTION: This routine display the Install appliaction dialog and 
//					 install application information into database.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns true if install successful, flase if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean InstallApp ()
{
	char		szFileName[256];
	Boolean	result = false;
      
	COMDLG_ComDlgGetFileName ( COMDLG_ACTION_FILEOPEN, szFileName );

	if ( Vstrlen (szFileName) ) {
		result =	APM_AddApplication (szFileName, NULL);
		numRecords = DmNumRecords( APMDB );
	}

	return	result;	
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DeleteApp
//
// DESCRIPTION: This routine display the delete appliaction screen and 
//					 delete application information from database.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns None.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void DeleteApp ()
{
	RectangleType	rect;
	UInt	index;
	Char	buffer[10];
	EventType	event;

	WinEraseWindow ();

	WinDrawTitleChars ("Delete", (UInt16)Vstrlen("Delete"), PDASTARTX, PDASTARTY);
	VDrawLine ( PDASTARTX, 12, PDAWIDTH, 12, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
	VDrawLine ( PDASTARTX, 13, PDAWIDTH, 13, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

	rect.topLeft.x = DeleteAppItemStartX;
	rect.topLeft.y = DeleteAppItemStartY;
	// Get Installed application and draw icon on screen
	for ( index = 0; index < numRecords; index++ ) {
		APM_GetApplication (index);
		// Draw a black block 1 instead of application icon (memo)
		VDrawString (rect.topLeft.x, rect.topLeft.y+index*(FntCharHeight()+2), 
			appList[index].appName,	Vstrlen (appList[index].appName), 
			SINGLELINE, CL_FOREGROUND, COORD_STRETCH);

		StrIToA (buffer, (appList[index].appSize/1024));
		strcat (buffer, "K");
		VDrawString (140, rect.topLeft.y+index*(FntCharHeight()+2), 
			buffer,	Vstrlen (buffer), SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
	}

	do {
		EvtGetEvent (&event, -1);
	} while ((event.eType!=penUpEvent) && (event.eType!=appStopEvent));

	RecordViewHandlePen (&event);
}

static Boolean RecordViewHandlePen (EventType * event)
{
	Boolean			handled = false;
	RectangleType	r;
	Word				x, y;
	Boolean			penDown;
   
   // If the user taps in the RecordViewDisplay take them to the Edit View
	RctSetRectangle (&r, 0, 15, 160, 114);
	if (RctPtInRectangle (event->screenX, event->screenY, &r)) {

		do {
			PenGetPoint (&x, &y, &penDown);
		} while (penDown);
      
		if (RctPtInRectangle (x, y, &r)) {
			x = event->screenX;
			y = event->screenY;
			rowSelect = (UInt)((y-DeleteAppItemStartY)/(FntCharHeight()+2));
			APM_RemoveApplication (rowSelect);
			numRecords = DmNumRecords( APMDB );
			CurrentForm = MAINFORM;
		}
         
		handled = true;
	}
      
	APM_DrawScreen (false);
	return handled;
}

/*************************************************************************
*   frmAboutEventHander - About form start handler
*
*************************************************************************/
Boolean frmDelAppEventHander(EventPtr event)
{
	int      handled = 0;

	switch (event->eType) {
		case penUpEvent:
         handled = RecordViewHandlePen(event);
         break;
    
		case nilEvent:
			handled = 1;
			break;
	}

	return handled;
}