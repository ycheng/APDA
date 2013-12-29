/*========================================================
  Graffiti.c
  all routine is running with Platform non-related,
  simulated the Graffiti manager function in Palm OS.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0511, 2001 by Jerry Chu
					 0525, 2001 by Jerry Chu, add 5 Graffiti-shift 
									routines and 6 Graffiti rountines.
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


Boolean	sysCapsLock=false;
Boolean	sysNumLock=false;
Boolean	sysUpperShift=false;
UInt16	sysTempShift=0;

GrfStateType	grfState;


////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfAddPoint
//
// DESCRIPTION: This routine add a point to the Graffiti point buffer.
//
// PARAMETERS:  (PointType *) pt - Pointer to point buffer.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfAddPoint (PointType *pt)
{
	if ( (lpts == NULL) || ((pt->x != currentPnt->x) && (pt->y != currentPnt->y)) ) {
		if ( lpts == NULL ) {
			lpts = (point_list *) Vmalloc (sizeof(point_list));
			lpts->npts = 1;
			lpts->pts = (pen_point *) Vmalloc (sizeof(pen_point));
		} else {
			lpts->npts++;
			lpts->pts = (pen_point *) Vrealloc (lpts->pts, lpts->npts*sizeof(pen_point));
		}

		lpts->pts[lpts->npts-1].x = pt->x;
		lpts->pts[lpts->npts-1].y = pt->y;
		currentPnt = &(lpts->pts[lpts->npts-1]);
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfCleanState
//
// DESCRIPTION: This routine remove any temporary shifts from the
//					 dictionary state.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfCleanState (void)
{
	sysTempShift = 0;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfFlushPoints
//
// DESCRIPTION: This routine dispose of all points in the Graffiti point
//					 buffer.
//
// PARAMETERS:  None.
//
// RETURNED:    Always Returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfFlushPoints (void)
{
	Vfree (lpts->pts);
	Vfree (lpts);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfGetNumPoints
//
// DESCRIPTION: This routine return the number of points in the point
//					 buffer.
//
// PARAMETERS:  (UInt16 *) numPtsP - Returned number of points.
//
// RETURNED:    Always Returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfGetNumPoints (UInt16 *numPtsP)
{
	if ( lpts ) 
		*numPtsP = lpts->npts;
	else
		*numPtsP = 0;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfGetPoint
//
// DESCRIPTION: This routine return a point out of the Graffiti point
//					 buffer.
//
// PARAMETERS:  (UInt16) index - Index of the point to get.
//					 (PointType *) pointP - Returned point.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfGetPoint (UInt16 index, PointType *pointP)
{
	pointP->x = lpts->pts[index].x;
	pointP->y = lpts->pts[index].y;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfGetState
//
// DESCRIPTION: This routine return the current Graffiti shift state
//
// PARAMETERS:  (Boolean) capsLock - Returns true if caps lock on.
//					 (Boolean) numLock - Returns true if num lock on.
//					 (UInt16) tempShiftP - Current temporary shift.
//					 (Boolean) upperShift - Returns true if shift not set
//										by the user but by the system.
//
// RETURNED:    Returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfGetState (Boolean *capsLockP, Boolean *numLockP, 
								UInt16 *tempShiftP, Boolean *autoShiftedP)
{
	*capsLockP = grfState.attr.sysCapsLock;
	*numLockP = grfState.attr.sysNumLock;
	*tempShiftP = grfState.sysTempShift;
	*autoShiftedP = grfState.attr.sysUpperShift;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfInitState
//
// DESCRIPTION: This routine Reinitialize the Graffiti dictionary state.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfInitState (void)
{
	Vmemset (&grfState, 0, sizeof(GrfStateType));

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfProcessStroke
//
// DESCRIPTION: This routine set the current shift state of Graffiti.
//
// PARAMETERS:  (PointType *) startPtP - Set to true to turn on caps lock.
//					 (PointType *) endPtP - Set to true to turn on num lock.
//					 (Boolean) upShift - Set to true to put into upper shift.
//
// RETURNED:    Returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfProcessStroke (PointType *startPtP, PointType *endPtP, Boolean upShift)
{
/*
	Char	*ch=NULL;

	ch = hwRecognizeStart (grfInputState);
	if ( upShift && (*ch >= 'a') && (*ch <= 'z') ) {
		*ch = (*ch - 'a') + 'A';
	}
*/
	return	0;
}


////////////////////////////////////////////////////////////////////////
// FUNCTION:    GrfSetState
//
// DESCRIPTION: This routine set the current shift state of Graffiti.
//
// PARAMETERS:  (Boolean) capsLock - Set to true to turn on caps lock.
//					 (Boolean) numLock - Set to true to turn on num lock.
//					 (Boolean) upperShift - Set to true to put into upper shift.
//
// RETURNED:    Returns 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err GrfSetState (Boolean capsLock, Boolean numLock, Boolean upperShift)
{
	grfState.attr.sysCapsLock = capsLock;
	grfState.attr.sysNumLock = numLock;
	grfState.attr.sysUpperShift = upperShift;

	return	0;
}


// Below is Graffiti Shift function

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GsiEnable
//
// DESCRIPTION: This routine enable or disable the Graffiti-shift state
//					 indicator.
//
// PARAMETERS:  (const Boolean) enableIt - true to enable, false to disable.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GsiEnable (const Boolean enableIt)
{
	grfState.attr.enabled = enableIt;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GsiEnabled
//
// DESCRIPTION: This routine return true if the Graffiti-shift state 
//					 indicator is enabled, or false if it's disabled.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns true if enabled, false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean GsiEnabled (void)
{
	return	grfState.attr.enabled;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GsiInitialize
//
// DESCRIPTION: This routine initialize the global variables used to
//					 manager the graffiti-shift state indicator.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GsiInitialize (void)
{
	Vmemset (&grfState, 0, sizeof(GrfStateType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GsiSetLocation
//
// DESCRIPTION: This routine set the display-relative position of the
//					 Graffiti-shift state indicator.
//
// PARAMETERS:  (const Int16) x, y - Coordinate of left side and top
//													of the indicator
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GsiSetLocation (const Int16 x, const Int16 y)
{
	grfState.pos.x = x;
	grfState.pos.y = y;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GsiSetShiftState
//
// DESCRIPTION: This routine set the Graffiti-shift state indicator.
//
// PARAMETERS:  (const UInt16) lockFlags - glfCapsLock or glfNumLock.
//					 (const UInt16) tempShift - The current tempopary shift.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GsiSetShiftState (const UInt16 lockFlags, const UInt16 tempShift)
{
	switch (lockFlags) {
		case glfCapsLock:
			grfState.attr.sysCapsLock = true;
			break;

		case glfNumLock:
			grfState.attr.sysNumLock = true;
			break;
	}

	grfState.sysTempShift = tempShift;
}
