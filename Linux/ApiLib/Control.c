/*========================================================
  Control.c
  all routine is running with Platform non-related,
  simulated the Control function in Palm OS.
  Current status is ControlModal free funtion.

  All is Palm related function.
  Completed 10 of 19 Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0327, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


extern Int16 WPushEvent (const EventType *event);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlDrawControl
//
// DESCRIPTION: This routine draw a control object
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01	Initial Revision
//			Jerry	9/03/01	If size attribute is AUTO, recalculate it
//			Jerry	11/24/01	Call VDrawControl directly
////////////////////////////////////////////////////////////////////////
void CtlDrawControl (ControlType *controlP)
{
	VDrawControl (frmControlObj, controlP, DRAW_NORMAL);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlEnabled
//
// DESCRIPTION: This routine return true if the control respond to the
//				pen.
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns return true if the control respond to the pen;
//				false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean CtlEnabled (const ControlType *controlP)
{
	return	controlP->attr.enabled;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlEraseControl
//
// DESCRIPTION: This routine erase a usable and visible control object
//				and its frame from the screen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlEraseControl (ControlType *controlP)
{
	controlP->attr.visible = FALSE;
	VClearControl (controlP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlGetLabel
//
// DESCRIPTION: This routine return a character ponter to a control's
//				text label.
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns a pointer to a null-terminated string
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/1/01	Initial Revision
////////////////////////////////////////////////////////////////////////
const Char *CtlGetLabel (const ControlType *controlP)
{
/*
	if ( controlP->text != NULL ) {
		return	controlP->text;
	} else {
		return	NULL;
	}
*/

	return	controlP->text;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlGetSliderValues
//
// DESCRIPTION: This routine return the current value by a slider control.
//
// PARAMETERS:  (const ControlType *) controlP - pointer to control object
//					 (UInt16 *) minValueP - The slider's minimum value. Pass 
//										NULL if you don't want to retrieve this value.
//					 (UInt16 *) maxValueP - The slider's maximum value. Pass 
//										NULL if you don't want to retrieve this value.
//					 (UInt16 *) pageSizeP - The slider's page size value. Pass 
//										NULL if you don't want to retrieve this value.
//					 (UInt16 *) valueP - The slider's current value. Pass 
//										NULL if you don't want to retrieve this value.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlGetSliderValues (const ControlType *controlP, UInt16 *minValueP,
								  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP)
{
	SliderControlType *ctlP = (SliderControlType *) controlP;

	if ( minValueP ) 
		*minValueP = ctlP->minValue;
	if ( maxValueP ) 
		*maxValueP = ctlP->maxValue;
	if ( pageSizeP ) 
		*pageSizeP = ctlP->pageSize;
	if ( valueP ) 
		*valueP = ctlP->value;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlGetValue
//
// DESCRIPTION: This routine return the current value of the specified
//				control.
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns the current value of the control. For most controls
//				the return value is eithe 0(off) or 1(on). For sliders,
//				this function returns the value of the value field.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/1/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 CtlGetValue (const ControlType *controlP)
{
	if ( !controlP )
		return	0;
	if ( controlP->text )
		return	Vatoi(controlP->text);
	else
		return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlHideControl
//
// DESCRIPTION: This routine set a control's usable attribute to false
//				and ease the control from the screen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlHideControl (ControlType *controlP)
{
	controlP->attr.usable = FALSE;
	VClearControl (controlP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlHitControl
//
// DESCRIPTION: This routine simulate tapping a control. This function
//				adds a ctlSelectEvent to the event Queue.
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01	Initial Revision
//			Jerry	8/28/01	Modify to push the event to the queue
////////////////////////////////////////////////////////////////////////
void CtlHitControl (const ControlType *controlP)
{
	CurEvent->data.ctlEnter.controlID = controlP->id;

	if ( controlP->style == repeatingButtonCtl ) {
		CurEvent->eType = ctlRepeatEvent;
	} else {
		CurEvent->eType = ctlSelectEvent;
	}

	WPushEvent (CurEvent);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlNewControl
//
// DESCRIPTION: This routine create a new control object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (void *) formPP - Pointer to the pointer to the form in
//										which the new list is installed.
//					 (UInt16) ID - Symbolic ID of the control.
//					 (ControlStyleType) style - A ControlStyleType value
//										specifying the kind of control to create.
//					 (const Char *) textP - Pointer to the control's label
//										text.
//					 (Coord) x - Horizontal coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) width - Width of the control, expressed in pixels.
//					 (Coord) height - Height of the control, expressed in pixels.
//					 (FontID) font - Font used to draw the control's label.
//					 (Int8) group - Group ID of a push button or a check box
//										that is part of an exclusive group.
//					 (Boolean) leftAnchor - true specifies that the left 
//										bound of this control is fixed.
//
// RETURNED:    Returns a pointer to the new control.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
ControlType *CtlNewControl (void **formPP, UInt16 ID, ControlStyleType style,
								   const Char *textP, Coord x, Coord y, Coord width,
								   Coord height, FontID font, UInt8 group, 
								   Boolean leftAnchor)
{
	ControlType	*ctlP;
	FormType		*formP = (FormType *) *formPP;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmControlObj;
	ctlP = formP->objects[formP->numObjects].object.control = 
			(ControlType *) Vmalloc (sizeof(ControlType));

	Vmemset (ctlP, 0, sizeof (ControlType));
	ctlP->style = style;

	ctlP->text = (char *) Vmalloc(Vstrlen(textP)+1);
	Vstrcpy (ctlP->text, textP);

	ctlP->id = ID;
	ctlP->attr.enabled = TRUE;
	ctlP->attr.visible = TRUE;
	ctlP->attr.leftAnchor = leftAnchor;

	ctlP->bounds.topLeft.x = x;
	ctlP->bounds.topLeft.y = y;
	ctlP->bounds.extent.x = width;
	ctlP->bounds.extent.y = height;
  
	return	formP->objects[formP->numObjects++].object.control;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlNewGraphicControl
//
// DESCRIPTION: This routine create a new control object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (void *) formPP - Pointer to the pointer to the form in
//										which the new list is installed.
//					 (UInt16) ID - Symbolic ID of the control.
//					 (ControlStyleType) style - A ControlStyleType value
//										specifying the kind of control to create.
//					 (DmResID) bitmapID - Resource ID of the bitmap to display
//										on the control
//					 (DmResID) selectedBitmapID - Resource ID of the bitmap to
//										display when the control is selected.
//					 (Coord) x - Horizontal coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) width - Width of the control, expressed in pixels.
//					 (Coord) height - Height of the control, expressed in pixels.
//					 (UInt8) group - Group ID of a push button or a check box
//										that is part of an exclusive group.
//					 (Boolean) leftAnchor - true specifies that the left 
//										bound of this control is fixed.
//
// RETURNED:    Returns a pointer to the new graphic control.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
GraphicControlType *CtlNewGraphicControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID bitmapID, 
								   DmResID selectedBitmapID, Coord x, Coord y, 
								   Coord width, Coord height, UInt8 group, 
								   Boolean leftAnchor)
{
	GraphicControlType	*ctlP;
	FormType	*formP = (FormType *) *formPP;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmControlObj;
	ctlP = (GraphicControlType *)formP->objects[formP->numObjects].object.control = 
			(ControlType *) Vmalloc (sizeof(ControlType));

	Vmemset (ctlP, 0, sizeof (ControlType));
	ctlP->style = style;

	ctlP->id = ID;
	ctlP->attr.enabled = TRUE;
	ctlP->attr.visible = TRUE;
	ctlP->attr.leftAnchor = leftAnchor;

	ctlP->bitmapID = bitmapID;
	ctlP->selectedBitmapID = selectedBitmapID;

	ctlP->bounds.topLeft.x = x;
	ctlP->bounds.topLeft.y = y;
	ctlP->bounds.extent.x = width;
	ctlP->bounds.extent.y = height;
  
	ctlP->group = group;

	return	(GraphicControlType *)formP->objects[formP->numObjects++].object.control;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlNewSliderControl
//
// DESCRIPTION: This routine create a new control object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (void *) formPP - Pointer to the pointer to the form in
//										which the new list is installed.
//					 (UInt16) ID - Symbolic ID of the control.
//					 (ControlStyleType) style - A ControlStyleType value
//										specifying the kind of control to create.
//					 (DmResID) thumbID - Resource ID of the bitmap to display
//										as the slider thumb.
//					 (DmResID) backgroundID - Resource ID of the bitmap to
//										display as the slider background.
//					 (Coord) x - Horizontal coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left corner
//										of the control's boundaries.
//					 (Coord) width - Width of the control, expressed in pixels.
//					 (Coord) height - Height of the control, expressed in pixels.
//					 (UInt16) minValue - Value of the slider when its thumb is
//										all the way to the left.
//					 (UInt16) maxValue - Value of the slider when its thumb is
//										all the way to the right.
//					 (UInt16) pageSize - Amount by which to increase or decrease 
//										the slider's value when the user clicks to
//										the right or left of the thumb.
//					 (UInt16) value - The initial value to display in the slider.
//
// RETURNED:    Returns a pointer to the new slider control.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
SliderControlType *CtlNewSliderControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID thumbID, 
								   DmResID backgroundID, Coord x, Coord y, 
								   Coord width, Coord height, UInt16 minValue,
								   UInt16 maxValue, UInt16 pageSize, UInt16 value)
{
	SliderControlType	*ctlP;
	FormType	*formP = (FormType *) *formPP;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmControlObj;
	ctlP = (SliderControlType *)formP->objects[formP->numObjects].object.control = 
			(ControlType *) Vmalloc (sizeof(ControlType));

	Vmemset (ctlP, 0, sizeof (ControlType));
	ctlP->style = style;

	ctlP->id = ID;
	ctlP->attr.enabled = TRUE;
	ctlP->attr.visible = TRUE;
	ctlP->thumbID = thumbID;
	ctlP->backgroundID = backgroundID;

	ctlP->bounds.topLeft.x = x;
	ctlP->bounds.topLeft.y = y;
	ctlP->bounds.extent.x = width;
	ctlP->bounds.extent.y = height;

	ctlP->minValue = minValue;
	ctlP->maxValue = maxValue;
	ctlP->pageSize = pageSize;
	ctlP->value = value;
  
	return	(SliderControlType *)formP->objects[formP->numObjects++].object.control;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetEnabled
//
// DESCRIPTION: This routine set a control as enabled or disabled.
//				Disabled controls do not respond to the pen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//				(Boolean) enable - true to enable the control;
//								false to disable the control
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlSetEnabled (ControlType *controlP, Boolean enable)
{
	controlP->attr.enabled = enable;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetLabel
//
// DESCRIPTION: This routine set the current label for the specified 
//				control object and redraw the control if it is visible
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//				(const Char *newlabel) newLabel - Pointer to the new 
//											text label. Must be a 
//											NULL-terminated string.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
//			Jerry 5/09/01	Modify to realloc memory for text buffer
////////////////////////////////////////////////////////////////////////
void CtlSetLabel (ControlType *controlP, const Char *newLabel)
{
	controlP->text = Vrealloc (controlP->text, Vstrlen(newLabel)+1);
	Vstrcpy (controlP->text, newLabel);

	if ( controlP->attr.visible )
		CtlDrawControl (controlP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetGraphics
//
// DESCRIPTION: This routine set the bitmaps for a graphical control and
//					 redraw the control if it is visible.
//
// PARAMETERS:  (const ControlType *) controlP - pointer to control object
//					 (DmResID) newBitmapID - Resource ID of a new bitmap to
//										display on the control, or NULL to use the
//										current bitmap.
//					 (DmResID) newSelectBitmapID - Resource ID of a new bitmap
//										to	display when the control is selected, 
//										or NULL to use the current bitmap. 
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlSetGraphics (ControlType *controlP, DmResID newBitmapID,
							  DmResID newSelectedBitmapID)
{
	GraphicControlType	*ctlP = (GraphicControlType *)controlP;

	if ( newBitmapID ) {
		ctlP->bitmapID = newBitmapID;
	}
	if ( newSelectedBitmapID ) {
		ctlP->bitmapID = newSelectedBitmapID;
	}

	if ( ctlP->attr.visible ) {
		CtlDrawControl (controlP);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetSliderValues
//
// DESCRIPTION: This routine change a slider control's values and redraw
//					 the slider if it is visible.
//
// PARAMETERS:  (const ControlType *) controlP - pointer to control object
//					 (const UInt16 *) minValueP - Pointer to a new value to use
//												for the slider's minimum or NULL if
//												you don't want to change this value.
//					 (const UInt16 *) maxValueP - Pointer to a new value to use
//												for the slider's maximum or NULL if
//												you don't want to change this value.
//					 (const UInt16 *) pageSizeP - Pointer to a new value to use
//												for the slider's page size or NULL if
//												you don't want to change this value.
//					 (const UInt16 *) valueP - Pointer to a new value to use
//												for the slider's current value or NULL if
//												you don't want to change this value.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlSetSliderValues (const ControlType *controlP, UInt16 *minValueP,
								  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP)
{
	SliderControlType *ctlP = (SliderControlType *) controlP;

	if ( minValueP ) 
		ctlP->minValue = *minValueP;
	if ( maxValueP ) 
		ctlP->maxValue = *maxValueP;
	if ( pageSizeP ) 
		ctlP->pageSize = *pageSizeP;
	if ( valueP ) 
		ctlP->value = *valueP;

	if ( ctlP->attr.visible ) {
		CtlDrawControl ((ControlType *)ctlP);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetUsable
//
// DESCRIPTION: This routine set a control as enabled or disabled.
//				Disabled controls do not respond to the pen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//				(Boolean) usable - true to have the control be usable;
//								false to have the control be not usable.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlSetUsable (ControlType *controlP, Boolean usable)
{
	controlP->attr.usable = usable;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlSetValue
//
// DESCRIPTION: This routine set the current value of the specified 
//				control. If the control is visible, it's redrawn.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//				(Int16) newValue - New value to set for the control.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01	Initial Revision
//			Jerry	8/16/01	Add Checking control style, if checkbox, setting
//								enabled attribute
////////////////////////////////////////////////////////////////////////
void CtlSetValue (ControlType *controlP, Int16 newValue)
{
	char word[10];

	if ( controlP->style == checkboxCtl ) {
		controlP->attr.enabled = newValue;
	} else {
		StrIToA (word, newValue);
		StrCopy (controlP->text, word);
	}

	if ( controlP->attr.visible ) {
		CtlDrawControl (controlP);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlShowControl
//
// DESCRIPTION: This routine set a control's usable attibute to true
//				and draw the control on the screen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CtlShowControl (ControlType *controlP)
{
	controlP->attr.usable = TRUE;
	CtlDrawControl (controlP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CtlValidatePointer
//
// DESCRIPTION: This routine returns true if the specified pointer 
//					 references a valid control object.
//
// PARAMETERS:  (const ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns true when passed a valid pointer to a control;
//					 otherwise, returns false.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean CtlValidatePointer (const ControlType *controlP)
{
/*
	if ( controlP ) 
		return	true;
	else
		return	false;
*/
	return	(controlP!=NULL);
}
