#ifndef __VCOMMON_H__
#define __VCOMMON_H__

//	System will crash if application using #pragma pack(2),
//	use #pragma pack (4) to force system alignment to 4 bytes
// to prevent system crash.
//#pragma pack (4)

#include <VivoTypes.h>
#include <WisDef.h>
#include <System/DataMgr.h>
#include <bitmap.h>
#include <Font.h>
#include <System/datetime.h>
#include <Category.h>
#include <HandWriting.h>
#include <Preference.h>

#include <System/SysAll.h>
#include <UI/UIAll.h>

#define true	TRUE
#define false	FALSE

#define	WRGB(r, g ,b)  ((UInt32) (((BYTE) (r) | ((UInt16) (g) << 8)) | (((UInt32) (BYTE) (b)) << 16)))


//#define	BACKGROUNDCOLOR	WRGB(256, 256, 256)
//#define	FOREGROUNDCOLOR	WRGB(0, 0, 0)

#define	BACKGROUNDCOLOR		0
#define	FOREGROUNDCOLOR		1

#define	GRAY_COLOR			WRGB(128, 128, 128)


/************************************************************
 * Error Classes for each manager
 *************************************************************/
#define	errNone						0x0000	// No error

#define	memErrorClass				0x0100	// Memory Manager
#define	dmErrorClass				0x0200	// Data Manager
#define	serErrorClass				0x0300	// Serial Manager
#define	slkErrorClass				0x0400	// Serial Link Manager
#define	sysErrorClass				0x0500	// System Manager
#define	fplErrorClass				0x0600	// Floating Point Library
#define	flpErrorClass				0x0680	// New Floating Point Library
#define	evtErrorClass				0x0700  	// System Event Manager
#define	sndErrorClass				0x0800  	// Sound Manager
#define	almErrorClass				0x0900  	// Alarm Manager
#define	timErrorClass				0x0A00  	// Time Manager
#define	penErrorClass				0x0B00  	// Pen Manager
#define	ftrErrorClass				0x0C00  	// Feature Manager
#define	cmpErrorClass				0x0D00  	// Connection Manager (HotSync)
#define	dlkErrorClass				0x0E00	// Desktop Link Manager
#define	padErrorClass				0x0F00	// PAD Manager
#define	grfErrorClass				0x1000	// Graffiti Manager
#define	mdmErrorClass				0x1100	// Modem Manager
#define	netErrorClass				0x1200	// Net Library
#define	htalErrorClass				0x1300	// HTAL Library
#define	inetErrorClass				0x1400	// INet Library
#define	exgErrorClass				0x1500	// Exg Manager
#define	fileErrorClass				0x1600	// File Stream Manager
#define	rfutErrorClass				0x1700	// RFUT Library
#define	txtErrorClass				0x1800	// Text Manager
#define	tsmErrorClass				0x1900	// Text Services Library
#define	webErrorClass				0x1A00	// Web Library
#define	secErrorClass				0x1B00	// Security Library
#define	emuErrorClass				0x1C00	// Emulator Control Manager
#define	flshErrorClass				0x1D00	// Flash Manager
#define	pwrErrorClass				0x1E00	// Power Manager
#define	cncErrorClass				0x1F00	// Connection Manager (Serial Communication)
#define	actvErrorClass				0x2000	// Activation application
#define	radioErrorClass				0x2100	// Radio Manager (Library)
#define	dispErrorClass				0x2200	// Display Driver Errors.
#define	bltErrorClass				0x2300	// Blitter Driver Errors.
#define	winErrorClass				0x2400	// Window manager.
#define	omErrorClass				0x2500	// Overlay Manager
#define	menuErrorClass				0x2600	// Menu Manager

#define	oemErrorClass				0x7000	// OEM/Licensee errors (0x7000-0x7EFF shared among ALL partners)
#define  errInfoClass				0x7F00	// special class shows information w/o error code
#define	appErrorClass				0x8000	// Application-defined errors

typedef	void*		DmOpenRef;
typedef	void*		FileHand;
/************************************************************
 * Structures used by the sorting routines
 *************************************************************/
/************************************************************
 * Database manager error codes
 * the constant dmErrorClass is defined in ErrorBase.h
 *************************************************************/
#define	dmErrMemError				(dmErrorClass | 1)
#define	dmErrIndexOutOfRange		(dmErrorClass | 2)
#define	dmErrInvalidParam			(dmErrorClass | 3)
#define	dmErrReadOnly				(dmErrorClass | 4)
#define	dmErrDatabaseOpen			(dmErrorClass | 5)
#define	dmErrCantOpen				(dmErrorClass | 6)
#define	dmErrCantFind				(dmErrorClass | 7)
#define	dmErrRecordInWrongCard		(dmErrorClass | 8)
#define	dmErrCorruptDatabase		(dmErrorClass | 9)
#define	dmErrRecordDeleted			(dmErrorClass | 10)
#define	dmErrRecordArchived			(dmErrorClass | 11)
#define	dmErrNotRecordDB			(dmErrorClass | 12)
#define	dmErrNotResourceDB			(dmErrorClass | 13)
#define	dmErrROMBased				(dmErrorClass | 14)
#define	dmErrRecordBusy				(dmErrorClass | 15)
#define	dmErrResourceNotFound		(dmErrorClass | 16)
#define	dmErrNoOpenDatabase			(dmErrorClass | 17)
#define	dmErrInvalidCategory		(dmErrorClass | 18)
#define	dmErrNotValidRecord			(dmErrorClass | 19)
#define	dmErrWriteOutOfBounds		(dmErrorClass | 20)
#define	dmErrSeekFailed				(dmErrorClass | 21)
#define	dmErrAlreadyOpenForWrites	(dmErrorClass | 22)
#define	dmErrOpenedByAnotherTask	(dmErrorClass | 23)
#define dmErrUniqueIDNotFound		(dmErrorClass | 24)
#define dmErrAlreadyExists			(dmErrorClass | 25)
#define	dmErrInvalidDatabaseName	(dmErrorClass | 26)
#define	dmErrDatabaseProtected		(dmErrorClass | 27)
#define	dmErrDatabaseNotProtected	(dmErrorClass | 28)

/************************************************************
 * Mode flags passed to DmOpenDatabase
 *************************************************************/
#define	dmModeReadOnly				0x0001		// read  access
#define	dmModeWrite					0x0002		// write access
#define	dmModeReadWrite				0x0003		// read & write access
#define	dmModeLeaveOpen				0x0004		// leave open when app quits
#define	dmModeExclusive				0x0008		// don't let anyone else open it
#define	dmModeShowSecret			0x0010		// force show of secret records

typedef struct {
	UInt8			attributes;							// record attributes;
	UInt8			uniqueID[3];						// unique ID of record
	} SortRecordInfoType;

typedef SortRecordInfoType *SortRecordInfoPtr;

typedef Int16 DmComparF (void *, void *, Int16 other, SortRecordInfoPtr, 
								SortRecordInfoPtr, VoidHand);


#define	sysAppLaunchCmdNormalLaunch		0	// Normal Launch

//------------------------------------------------------------------------
// SysAppLaunch flags (passed to PilotMain)
//------------------------------------------------------------------------

#define	sysAppLaunchFlagNewThread		0x01	// create a new thread for application
															//  - implies sysAppLaunchFlagNewStack
#define	sysAppLaunchFlagNewStack		0x02	// create separate stack for application
#define	sysAppLaunchFlagNewGlobals		0x04	// create new globals world for application
															//  - implies new owner ID for Memory chunks
#define	sysAppLaunchFlagUIApp			0x08	// notifies launch routine that this is a UI app being
															//  launched.
#define	sysAppLaunchFlagSubCall			0x10	// notifies launch routine that the app is calling it's
															//  entry point as a subroutine call. This tells the launch
															//  code that it's OK to keep the A5 (globals) pointer valid 
															//  through the call.
#define sysAppLaunchFlagDataRelocated	0x80	// global data (static ptrs) have been "relocated"
															//  by either SysAppStartup or StartupCode.c

#define	appErrorClass				0x8000	// Application-defined errors

/************************************************************
 * System Errors
 *************************************************************/
#define	sysErrTimeout				(sysErrorClass | 1)
#define	sysErrParamErr				(sysErrorClass | 2)
#define	sysErrNoFreeResource		(sysErrorClass | 3)
#define	sysErrNoFreeRAM			(sysErrorClass | 4)
#define	sysErrNotAllowed			(sysErrorClass | 5)
#define	sysErrSemInUse				(sysErrorClass | 6)
#define	sysErrInvalidID			(sysErrorClass | 7)
#define	sysErrOutOfOwnerIDs		(sysErrorClass | 8)
#define	sysErrNoFreeLibSlots		(sysErrorClass | 9)
#define	sysErrLibNotFound			(sysErrorClass | 10)
#define	sysErrDelayWakened		(sysErrorClass | 11)		// SysTaskDelay wakened by SysTaskWake before delay completed.
#define	sysErrRomIncompatible	(sysErrorClass | 12)


// Clipboard.h
#define numClipboardForamts 	3
#define cbdMaxTextLength		1000


//typedef Boolean FormEventHandlerType (EventType *eventP);
//typedef FormEventHandlerType *FormEventHandlerPtr;

#ifndef _WISIMPORTDLL
#define _WISEXPORTDLL
#include "apidll.h"
#include "WisDll.h"
#endif

#endif // __VCOMMON_H__
