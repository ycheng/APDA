/*========================================================
  FrmDDK.c
  all routine is running with Platform non-related,
  simulated the form control function in Palm OS.
  Current status is ControlModal relatived funtion.

  Only UpdateForm and DestroyForm is Palm non-related function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0314, 2001 by Jerry Chu
					 0504, 2001 by Jerry Chu modify to FormModal free
					 0525, 2001 by Jerry Chu, add 6 routines.
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

void UpdateForm (FormType *form);
void formDeleteForm (FormType *formP);
void FrmGotoForm (UInt16 formId);
void FrmDrawForm(FormType *form);
void FrmReleaseObjectMem (FormType *formP, UInt16 index);

UInt16		ActiveFormID=0;
FormType		*ActiveForm;
UInt16		SaveFormID=0xFFFF;
FormType		*SaveForm=NULL;
Int16			SaveObjIndex;
MenuBarType		*SaveMenu;
extern MenuBarType		*ActiveMenu;
extern Int16	ActiveObjIndex;
extern FormType	**formPtr;
extern UInt16	menuCount;
extern Char		*RCPFileName;
extern Boolean	cursorState;
extern int	oldGrfState;

FormActiveStateType	frmActiveState;

extern void VSetMenu ( UInt16 menuID );
extern void EvtGetEvent(EventType *event, Int32 timeout);
extern void FormDisplayCustomAlert (const Char *s1, const Char *s2, const Char *s3);
extern Boolean SysHandleEvent(EventType *event);
extern Int16 WPushEvent (const EventType *event);
extern void FreeResourceMemory ();
extern void WFlushEvent ();

void WDrawFormTitle (FormType	*formP, UInt16 index)
{
	RectangleType	rect;
	UInt16	strWidth;

	Vmemcpy ( &rect, &(formP->window.windowBounds), sizeof(RectangleType) );

	if ( formP->window.windowFlags.modal ) {
		rect.extent.y = FntLineHeight ();
		strWidth = FntCharsWidth (formP->objects[index].object.title->text,
						(short)Vstrlen(formP->objects[index].object.title->text));
		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

		VDrawString ( (Coord)(VPDAToSysXCoord(rect.topLeft.x)+((VPDAToSysXRes(PDAWIDTH)-strWidth)/2)), 
							(Coord)(VPDAToSysYCoord(rect.topLeft.y)+((VPDAToSysYRes(rect.extent.y)-FntCharHeight())/2)),
							formP->objects[index].object.title->text, 
							Vstrlen(formP->objects[index].object.title->text), 
							SINGLELINE, 
							CL_BACKGROUND,
							COORD_NORMAL);
	} else {
		WinDrawTitleChars (formP->objects[index].object.title->text, 
								(UInt16)Vstrlen(formP->objects[index].object.title->text), 
								rect.topLeft.x, 
								rect.topLeft.y);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DestroyForm (VIVO OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine destory all allocation memory of each form
//
// PARAMETERS:  None
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WDestroyForm()
{
	UInt	i;

	// Destroy all locate Form memory
	for ( i = 0; i < formCount; i++ ) {
		// Destroy all locate Control memory
		formDeleteForm (formPtr[i]);
	}

	if ( formPtr ) {
		Vfree (formPtr);
		formPtr = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    formDeleteForm
//
// DESCRIPTION: This routine release the memory occupied by a form. Any
//					 memory allocated to objects in the form is also released.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
//			Jerry	8/13/01	Add frmScrollBarObj and frmPopupObj control
////////////////////////////////////////////////////////////////////////
void formDeleteForm (FormType *formP)
{
	UInt16	j;

	for ( j = 0; j < formP->numObjects; j++ ) {
		FrmReleaseObjectMem (formP, j);
	}

	if ( formP->objects )
		Vfree (formP->objects);
	Vfree (formP);
	formP = NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmAlert
//
// DESCRIPTION: This routine create a modal dialog from an alert 
//					 resource and display it until the user selects a button 
//					 in the dialog.
//
// PARAMETERS:  (UInt16) alertID - ID of the alert resource
//
// RETURNED:    Returns the item number of the button the user selected.
//					 A button's item number is determined by its order in the
//					 alert dialog; the first button has the item number 0.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision
//			Jerry	8/28/01	Modify to push the event to the queue
//			Jerry	8/29/01	Add judge is ActiveForm a NULL form
//			Jerry	9/20/01	Modify to only popup alert instead of unsing 
//								frmGotoForm
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
UInt16 FrmAlert (UInt16 alertID)
{
	FormType		*saveForm;
	Int16			saveObjIndex;
	int			i, selection;

	// set active form to alertID;
	for ( i = 0; i < formCount; i++ ) {
		if ( (formPtr[i]->attr.reserved) && (formPtr[i]->formId == alertID) ) {
			saveForm = ActiveForm;
			saveObjIndex = ActiveObjIndex;
			ActiveObjIndex = -1;
			ActiveForm = formPtr[i];

			break;
		}
	}

	// Save the area which alert form will use
	if ( ActiveForm ) {
		VSaveRegion (&(ActiveForm->window.windowBounds), COORD_STRETCH);
	}

   FrmDrawForm (ActiveForm);
	
	// Peek the event occurs in alert form.
	WResetEvent (CurEvent);
	do {
		WPeekEventsDDK();
		// Check mouse click region here and set controlID
	} while ( (CurEvent->eType!=ctlSelectEvent) && (CurEvent->eType!=appStopEvent) );

	if ( CurEvent->eType == ctlSelectEvent ) {
		selection = CurEvent->data.ctlSelect.controlID;
		WFlushEvent ();
	}
	VRedrawRegion (&(ActiveForm->window.windowBounds), COORD_STRETCH);
	ActiveForm = saveForm;
	ActiveObjIndex = saveObjIndex;

	return	selection;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmCloseAllForms
//
// DESCRIPTION: This routine send a frmCloseEvent to all open forms.
//
// PARAMETERS:  
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmCloseAllForms (void)
{
	FreeResourceMemory ();
	if ( RCPFileName ) {
		Vfree (RCPFileName);
		RCPFileName = NULL;
	}
	ActiveForm = NULL;
	ActiveObjIndex = -1;
	menuCount = formCount = ActiveFormID = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmCopyLabel
//
// DESCRIPTION: This routine copy the passed string into the data
//				structure of the specified label object in the active 
//				form
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//				(UInt16) labelID - ID of form label object
//				(const Char *) newLabel - Pointer to a NULL-terminated
//									string.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry 6/28/01	Add frmControlObj type
////////////////////////////////////////////////////////////////////////
void FrmCopyLabel(FormType *formp, UInt16 labelID, char *newLabel )
{
	UInt16	i;
	UInt16	length = (UInt16)Vstrlen (newLabel);

	for ( i = 0; i < formp->numObjects; i++ ) {
		switch ( formp->objects[i].objectType ) {
			case frmLabelObj:
				if ( formp->objects[i].object.label->id == labelID ) {
					formp->objects[i].object.label->text = (char *)
						Vrealloc (formp->objects[i].object.label->text, length+1);
					Vmemcpy (formp->objects[i].object.label->text, newLabel, length);
					formp->objects[i].object.label->text[length] = 0;

					return;
				}
			case frmControlObj:
				if ( formp->objects[i].object.label->id == labelID ) {
					if ( !formp->objects[i].object.control->text ) {
						formp->objects[i].object.control->text = (char *)
							Vmalloc (length+1);
					} else if ( length != Vstrlen (formp->objects[i].object.control->text) ) {
						formp->objects[i].object.control->text = (char *)
							Vrealloc (formp->objects[i].object.control->text, length+1);
					}
					Vmemcpy (formp->objects[i].object.control->text, newLabel, length);
					formp->objects[i].object.control->text[length] = 0;

					return;
				}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmCopyTitle
//
// DESCRIPTION: This routine copy a new title over the form's current 
//					 title. If the form is visile, the new title is drawn.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (const Char *) newTitle - Pointer to a NULL-terminated
//									string.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry 7/05/01	Add redraw title function
////////////////////////////////////////////////////////////////////////
void FrmCopyTitle (FormType *formP, const Char *newTitle)
{
	UInt16	i;

	for ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].objectType == frmTitleObj ) {
			formP->objects[i].object.title->text = (char *)
				Vrealloc (formP->objects[i].object.title->text, (Vstrlen (newTitle)+1));
			Vmemcpy (formP->objects[i].object.title->text, newTitle, Vstrlen(newTitle));

			WDrawFormTitle (formP, i);
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmCustomAlert
//
// DESCRIPTION: This routine create modal dialog from an alert resource
//					 and display the dialog until the user taps a button in
//					 the alert dialog.
//
// PARAMETERS:  (UInt16) alertId - Resource ID of the alert.
//					 (const Char *) s1, s2, s3 - Strings to replace ^1, ^2
//												and ^3.
//
// RETURNED:    Returns the number of the button the user tapped(the
//					 first button is zero).
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmCustomAlert (UInt16 alertID, const Char *s1, const Char *s2, const Char *s3)
{
	FormDisplayCustomAlert (s1, s2, s3);

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmDeleteForm
//
// DESCRIPTION: This routine release the memory occupied by a form. Any
//					 memory allocated to objects in the form is also released.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
//			Jerry 7/25/01	Modify to do nothing, original move to 
//								formDeleteForm.
//			Jerry 7/26/01	Add goto activeform
////////////////////////////////////////////////////////////////////////
void FrmDeleteForm (FormType *formP)
{
	if ( ActiveForm != formP ) 
		FrmGotoForm (ActiveFormID);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmDispatchEvent
//
// DESCRIPTION: This routine dispatch an event to the application's 
//				handler fo the form
//
// PARAMETERS:  (EventType *) eventP - Pointer to an event.
//
// RETURNED:    Returns the Boolean value returned by the form's event
//				handler or FrmHandleEvent. false if the form specified
//				in the event is invalid.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmDispatchEvent(EventType *eventP)
{
	if ( ActiveForm && ActiveForm->handler ) {
		(*ActiveForm->handler)(eventP);
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmDoDialog
//
// DESCRIPTION: This routine display a modal dialog until the user taps
//					 a button in the dialog.
//
// PARAMETERS:  (FormType *) formp - Pointer to the form object
//
// RETURNED:    Returns the resource ID of the button the user tapped.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
//			Jerry 7/25/01	Add get event loop, and return the correct ID
////////////////////////////////////////////////////////////////////////
UInt16 FrmDoDialog (FormType *formP)
{
	EventType		event;

	VDrawRect (&(formP->window.windowBounds), PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
	UpdateForm (formP);

	do {
		EvtGetEvent(&event, 200);
		SysHandleEvent(&event);
	} while ( !((event.eType == ctlSelectEvent)&&
		(ActiveForm->objects[ActiveObjIndex].object.control->style==buttonCtl)) );

	return	event.data.ctlSelect.controlID;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmDrawForm
//
// DESCRIPTION: This routine draw all objects in a form and the
//				frame around the form
//
// PARAMETERS:  (FormType *) formp - Pointer to the form object
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01		Initial Revision
//			Jerry	3/15/01		Change clear client windows to form
//								boundary rectangle
//			Jerry	3/20/01		Modify VRect to RectangleType
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
void FrmDrawForm(FormType *form)
{
	if (!form)	return;

	VDrawRect (&(form->window.windowBounds), PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
	UpdateForm (form);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmEraseForm
//
// DESCRIPTION: This routine erase a form from the display.
//
// PARAMETERS:  (FormType *) formp - Pointer to the form object
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
void FrmEraseForm (FormType *form)
{
	VDrawRect (&(form->window.windowBounds), PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetActiveForm
//
// DESCRIPTION: This routine return the index of an object in the
//				form's object list.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//				(UInt16) objID - ID of an object in the form
//
// RETURNED:    Returns the index of the object
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01		Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
FormType *FrmGetActiveForm ()
{
	return	ActiveForm;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetActiveFormID
//
// DESCRIPTION: This routine return the ID of the currently active form.
//
// PARAMETERS:  
//
// RETURNED:    Returns the index of the object
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetActiveFormID (void)
{
	return	ActiveFormID;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetControlValue
//
// DESCRIPTION: This routine return the current value of a control.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns the current value of the control. For most 
//					 controls the return value is either 0(off) or 1(on).
//					 For sliders, this function returns the value of the
//					 the value field.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FrmGetControlValue (const FormType *formP, UInt16 controlID)
{
	UInt	i;

	for ( i = 0; i < formP->numObjects; i++ ) {
		switch (formP->objects[i].objectType) {
			case frmControlObj:
				if (formP->objects[i].object.control->id == controlID) {
					return	formP->objects[i].object.control->attr.on;
				}
				break;
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetFirstForm
//
// DESCRIPTION: This routine return the first form in the window list.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns a pointer to a form object, or NULL if there 
//					 are no forms.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FormType *FrmGetFirstForm (void)
{
	return	formPtr[0];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetFocus
//
// DESCRIPTION: This routine return the item index number of the object
//					 that has the focus.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns the index of the object that has the focus,
//					 or returns noFocus if none does.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetFocus (const FormType *formp)
{
	if ( formp->focus < formp->numObjects ) 
		return	formp->focus;
	else
		return	noFocus;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetFormBounds
//
// DESCRIPTION: This routine return the visual bounds of the form; the 
//					 region returned includes the form's frame.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (RectangleType *) rP - Pointer to a RectangleTypes 
//												structure where the bounds is returned.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
void FrmGetFormBounds (const FormType *formP, RectangleType *rP)
{
	*rP = formP->window.windowBounds;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetFormId
//
// DESCRIPTION: This routine return the resource ID of a form.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns form resource ID.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetFormId (FormType *formP)
{
	return	formP->formId;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetFormPtr
//
// DESCRIPTION: This routine return a pointer to the form that has
//					 the specified ID.
//
// PARAMETERS:  (UInt16) formId - Form ID number
//
// RETURNED:    Returns a pointer to the form object, or NULL if 
//					 the form is not in memory.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
FormType *FrmGetFormPtr (UInt16 formId)
{
	UInt16	index;

	for ( index = 0; index < formCount; index++ ) {
		if ( !(formPtr[index]->attr.reserved) && (formPtr[index]->formId == formId) ) {
			return	formPtr[index];
		}
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetGadgetData
//
// DESCRIPTION: This routine return the value stored in the data field
//					 of the gadget object.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) objIndex - Index of the gadget object in the form
//									object's data structure.
//
// RETURNED:    Returns a pointer to the custom gadget's data.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void *FrmGetGadgetData (const FormType *formP, UInt16 objIndex)
{
	return	formP->objects[objIndex].object.gadget->data;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetControlValue
//
// DESCRIPTION: This routine return pointer to the text of the specified 
//					 label object in the specified form.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) labelID - ID of the label object.
//
// RETURNED:    Returns a pointer to the label string.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
const Char *FrmGetLabel (FormType *formP, UInt16 labelID)
{
	UInt16	i;

	for ( i = 0; i < formP->numObjects; i++ ) {
		if (formP->objects[i].objectType == frmLabelObj) {
			if ( formP->objects[i].object.label->fontID == labelID ) {
				return	formP->objects[i].object.label->text;
			}
		}
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetNumberOfObjects
//
// DESCRIPTION: This routine return the number of objects in a form.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns the number of objects in the specified form.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetNumberOfObjects (const FormType *formP)
{
	return	formP->numObjects;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectBounds
//
// DESCRIPTION: This routine return the bounds of an object given its
//					 form and index.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//					 (RectangleType *) rP - Pointer to a RectangleType structure
//												where the object bounds are returned.
//
// RETURNED:    Returns a pointer to the form object of the active form
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmGetObjectBounds (const FormType *formP, UInt16 ObjIndex, RectangleType *rP)
{
	switch (formP->objects[ObjIndex].objectType) {
		case frmFieldObj:
			*rP = formP->objects[ObjIndex].object.field->rect;
			break;

		case frmControlObj:
			*rP = formP->objects[ObjIndex].object.control->bounds;
			break;

	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectId
//
// DESCRIPTION: This routine return the ID of the specified object.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//
// RETURNED:    Returns the ID number of an object or frmInvalidObjectId 
//					 if the objIndex parameter is invalid.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetObjectId (const FormType *formP, UInt16 objIndex)
{
	if ( objIndex < formP->numObjects ) {
		return formP->objects[objIndex].object.control->id;
/*
		switch (formP->objects[objIndex].objectType) {
			case frmFieldObj:
				return formP->objects[objIndex].object.field->id;
				break;

			case frmControlObj:
				return formP->objects[objIndex].object.control->id;
				break;
		}
*/
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectIndex
//
// DESCRIPTION: This routine return the index of an object in the form
//					 objects list.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) objID - ID of an object in the form.
//
// RETURNED:    Returns the index of the object.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	8/13/01	Add frmScrollBarObj object
////////////////////////////////////////////////////////////////////////
UInt16 FrmGetObjectIndex(const FormType *formP, UInt16 id)
{
	UInt16	i;

	if ( !formP )
		return	0;

	for ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].object.control->id == id )
			return	i;
	}

	return	formP->numObjects;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectPosition
//
// DESCRIPTION: This routine return the coordinates of the specified
//					 object relative to the form.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//					 (Coord *) x,y - Pointers where the window-relative x and
//										y positions of the object are returned.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmGetObjectPosition (const FormType *formP, UInt16 objIndex, Coord *x, Coord *y)
{
	if ( objIndex < formP->numObjects ) {
		switch (formP->objects[objIndex].objectType) {
			case frmFieldObj:
				*x = formP->objects[objIndex].object.field->rect.topLeft.x;
				*y = formP->objects[objIndex].object.field->rect.topLeft.y;
				break;

			case frmControlObj:
				*x = formP->objects[objIndex].object.control->bounds.topLeft.x;
				*y = formP->objects[objIndex].object.control->bounds.topLeft.y;
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectPtr
//
// DESCRIPTION: This routine return a pointer to the data structure
//				of an object in a form
//
// PARAMETERS:  (const FormType *) formp - Pointer to the form object
//				(UInt16) objIndex - Index of an object in the form
//
// RETURNED:    Returns a pointer to an object in the form
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01		Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry 7/23/01	Modify if objectType is frmFieldObj, pointer
//								textHandle to text. (Should delete this code later)
////////////////////////////////////////////////////////////////////////
void *FrmGetObjectPtr (const FormType *formP, UInt16 objIndex)
{
	if ( !formP ) return	NULL;

	if ( objIndex < formP->numObjects ) {
		return	formP->objects[objIndex].object.ptr;
	} else {
		return	NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectPtrById (add by Jerry Chu) 
//
// DESCRIPTION: This routine return a pointer to the data structure
//				of an object in a form
//
// PARAMETERS:  (UInt16) objID - ID of an object in the form.
//
// RETURNED:    Returns a pointer to an object in the form
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/04/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FormObjListType FrmGetObjectPtrById(UInt16 id)
{
	UInt16	i, j;

	for ( j = 0; j < formCount; j++ ) {
		for ( i = 0; i < formPtr[j]->numObjects; i++ ) {
			if ( formPtr[j]->objects[i].object.control->id == id )
				return	formPtr[j]->objects[i];
		}
	}

	return	formPtr[0]->objects[0];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetObjectType
//
// DESCRIPTION: This routine return the type of an object.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//
// RETURNED:    Returns FormObjectKind of the item specified.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FormObjectKind FrmGetObjectType (const FormType *formP, UInt16 objIndex)
{
	if ( objIndex >= formP->numObjects ) {
		return	-1;
	} else {
		return formP->objects[objIndex].objectType;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetTitle
//
// DESCRIPTION: This routine return a pointer to the title string of a 
//					 form.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns a pointer to the title string, or NULL if there
//					 is no title string or there is an error finding it.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
const Char *FrmGetTitle (const FormType *formP)
{
	UInt16	i;

	for  ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].objectType == frmTitleObj ) {
			return formP->objects[i].object.title->text;
		}
	}

	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGetWindowHandle
//
// DESCRIPTION: This routine return the window handle of a form.
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns the handle of the memory block that contains the
//					 form data structure.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
WinHandle FrmGetWindowHandle (const FormType *formP)
{
	return	formP->bitsBehindForm;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmGotoForm
//
// DESCRIPTION: This routine send a frmCloseEvent to the curent form;
//				send a frmLoadEvent and a frmOpenEvent to the specified
//				form.
//
// PARAMETERS:  (UInt16) formId - ID of the form to display
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	8/28/01	Modify to push the event to the queue, 
//								Push frmCloseForm, frmLoadEvent, frmOpenEvent to
//								the queue
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
void FrmGotoForm (UInt16 formId)
{
	UInt16	i;

	for ( i = 0; i < formCount; i++ ) {
		if ( formPtr[i] ) {
			if ( (!formPtr[i]->attr.reserved) && (formPtr[i]->formId == formId) ) {
				CurEvent->eType = frmCloseEvent;
				WPushEvent (CurEvent);

				CurEvent->eType = frmLoadEvent;
				CurEvent->data.frmLoad.formID = formId;

				WPushEvent (CurEvent);
				CurEvent->eType = frmOpenEvent;
				WPushEvent (CurEvent);
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmHandleEvent
//
// DESCRIPTION: This routine handle the event that has occurred in the 
//					 form.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (EventType *) eventP - Pointer to the event data structure.
//
// RETURNED:    Returns true if the event was handled.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
Boolean FrmHandleEvent (FormType *formP, EventType *eventP)
{
	if ( formP && formP->handler ) {
		(*formP->handler)(eventP);
		return	true;
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmHelp
//
// DESCRIPTION: This routine display the specified help message until
//					 the user taps the Done button in the help dialog.
//
// PARAMETERS:  (UInt16) helpMsgId - Resource ID of help message string.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
void FrmHelp (UInt16 helpMsgId)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmHideObject
//
// DESCRIPTION: This routine erase the specified object and set its
//				attribute data (usable bit) so that it does not redraw
//				or respond to the pen
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//				(UInt16) objIndex - Index of an object in the form
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision as NULL
//			Jerry 5/04/01	Completed
//			Jerry	11/04/01	Clear the control rectangle
////////////////////////////////////////////////////////////////////////
void FrmHideObject(FormType *formP, UInt16 objIndex)
{
	if ( objIndex < formP->numObjects ) {
		switch (formP->objects[objIndex].objectType) {
			case frmFieldObj:
				formP->objects[objIndex].object.field->attr.usable = false;
				formP->objects[objIndex].object.field->attr.visible = false;
				VRedrawControl (formP->objects[objIndex]);
//				formP->objects[objIndex].object.field->attr.visible = true;
				break;

			case frmControlObj:
				formP->objects[objIndex].object.control->attr.usable = false;
				formP->objects[objIndex].object.control->attr.visible = false;
				VRedrawControl (formP->objects[objIndex]);
//				formP->objects[objIndex].object.control->attr.visible = true;
//				formP->objects[objIndex].object.control->attr.usable = true;
				break;

			case frmListObj:
				formP->objects[objIndex].object.list->attr.usable = false;
				formP->objects[objIndex].object.list->attr.visible = false;
				VRedrawControl (formP->objects[objIndex]);
//				formP->objects[objIndex].object.list->attr.visible = true;
				break;

			case frmLabelObj:
				formP->objects[objIndex].object.label->attr.usable = false;
				VRedrawControl (formP->objects[objIndex]);
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmInitForm
//
// DESCRIPTION: This routine load and initialize a form resource
//
// PARAMETERS:  (UInt16) formId - ID of the form
//
// RETURNED:    Returns a pointer to the form data structure
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
FormType *FrmInitForm(UInt16 formId)
{
	UInt16	i, j;

	// initial grafiti state off
	oldGrfState = -1;
	// initial cursor disappear
	cursorState=false;

	for ( i = 0; i < formCount; i++ ) {
		if ( !(formPtr[i]->attr.reserved) && (formPtr[i]->formId == formId) ) {
			for ( j = 0; j < formPtr[i]->numObjects; j++ ) {
				if ( formPtr[i]->objects[j].objectType == frmFieldObj ) {
					FieldType	*fldP = formPtr[i]->objects[j].object.field;
					if ( !fldP->textHandle ) {
						if ( fldP->textLen ) {
							Vfree (fldP->text);
						}
					}
					if ( fldP->lines ) {
						Vfree (fldP->lines);
						fldP->lines = NULL;
					}
					fldP->textHandle = NULL;
					fldP->text = NULL;
					fldP->textLen = 0;
					fldP->reserved = 0;
					fldP->textBlockSize = 0;

					fldP->insPtXPos = VPDAToSysXRes(fldP->rect.topLeft.x);
					fldP->insPtYPos = fldP->rect.topLeft.y;
					fldP->selFirstPos = fldP->selLastPos = 0xFFFF;
					fldP->firstLine = 0;
				}
			}
			return	formPtr[i];
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmNewForm
//
// DESCRIPTION: This routine create a new form object dynamically
//
// PARAMETERS:  (UInt16) formID - Symbolic ID of the form.
//					 (const Char *) titleStrP - Pointer to a string that
//									is the title of the form.
//					 (Coord) x - Horizontal coordinate of the upper-left
//									corner of the form's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left
//									corner of the form's boundaries.
//					 (Coord) width - Width of the form.
//					 (Coord) height - Height of the form.
//					 (Boolean) modal - true specifies that the form ignores
//									pen events outside its boundaries.
//					 (UInt16) defaultButton - Symbolic ID of the button that
//									provides the form's default action.
//					 (UInt16) helpRscID - Symbolic ID of the resource that
//									provides the fomr's online help.
//					 (UInt16) menuRscID - Symbolic ID of the resource that
//									provides the form's menu.
//
// RETURNED:    Returns a pointer to the new form object.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FormType *FrmNewForm (UInt16 formID, const Char *titleStrP, Coord x, Coord y,
							 Coord width, Coord height, Boolean modal, UInt16 defaultButton,
							 UInt16 helpRscID, UInt16 menuRscID)
{
	if ( formCount == 0 ) {
		formPtr = (FormType **) Vmalloc (sizeof(FormType *)*(formCount+1));
	} else {
		formPtr = (FormType **) Vrealloc (formPtr, sizeof(FormType *)*(formCount+1));
	}

	formPtr[formCount] = (FormType *) Vmalloc (sizeof(FormType));
	Vmemset (formPtr[formCount], 0, sizeof(FormType));

	formPtr[formCount]->formId = formID;

	formPtr[formCount]->window.windowBounds.topLeft.x = x;
	formPtr[formCount]->window.windowBounds.topLeft.y = y;
	formPtr[formCount]->window.windowBounds.extent.x = width;
	formPtr[formCount]->window.windowBounds.extent.y = height;
	formPtr[formCount]->numObjects = 0;
	formPtr[formCount]->objects = Vmalloc (sizeof(FormObjListType *));

	formPtr[formCount]->window.windowFlags.modal = modal;
	formPtr[formCount]->defaultButton = defaultButton;
	formPtr[formCount]->helpRscId = helpRscID;
	formPtr[formCount]->menuRscId = menuRscID;
	// set reserved to 0 to denote a Form
	formPtr[formCount]->attr.reserved = 0;

	formCount++;
	return	formPtr[formCount-1];
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmNewLabel
//
// DESCRIPTION: This routine create a new label object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (FormType **) formPP - Pointer to a pointer to the form
//											in which the new label is installed.
//					 (UInt) ID - Symbolic ID of the label.
//					 (const Char *) textP - Pointer to a string that provides
//											the label text.
//					 (Coord) x - Horizontal coordinate of the upper-left
//									corner of the form's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left
//									corner of the form's boundaries.
//					 (FontID) font - Font with which to draw the label text.
//
// RETURNED:    Returns a pointer to the new label object or 0 if the
//					 call didn't succeed..
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FormLabelType *FrmNewLabel (FormType **formPP, UInt16 ID, const Char *textP, Coord x, Coord y, FontID font)
{
	FormType	*formP = (FormType *) *formPP;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmLabelObj;
	formP->objects[formP->numObjects].object.label = 
			(FormLabelType *) Vmalloc (sizeof(FormLabelType));
	formP->objects[formP->numObjects].object.label->text = (char *)
				Vmalloc (sizeof (textP));
	Vmemcpy (formP->objects[formP->numObjects].object.label->text, textP, sizeof(textP));
	formP->objects[formP->numObjects].object.label->pos.x = x;
	formP->objects[formP->numObjects].object.label->pos.x = y;
  
	formP->numObjects++;

	return	formP->objects[formP->numObjects-1].object.label;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmPointInTitle
//
// DESCRIPTION: This routine check if a coordinate is within the bounds
//					 of the form's title.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (Coord) x, y - Window-relative x and y coordinates.
//
// RETURNED:    Returns true if the specified coordinate is in the form's
//					 title.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmPointInTitle (const FormType *formP, Coord x, Coord y)
{
	UInt16	i;
	UInt16	minX, maxX, minY, maxY;

	for  ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].objectType == frmTitleObj ) {
			minX = formP->objects[i].object.title->rect.topLeft.x;
			minY = formP->objects[i].object.title->rect.topLeft.y;
			maxX = formP->objects[i].object.title->rect.extent.x;
			maxY = formP->objects[i].object.title->rect.extent.y;

			if ( (x >= minX) && (x <= maxX) && (y >= minY) && (y <= maxY) ) {
				return	true;
			}
			return	false;
		}
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmPopupForm
//
// DESCRIPTION: This routine queues a frmLoadEvent and a frmOpenEvent
//					 for the specified form.
//
// PARAMETERS:  (UInt16) formId - ID of the form to display
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/17/01	Initial Revision
//			Jerry 5/04/01	Add ActiveForm
//			Jerry	8/28/01	Modify to push the event to the queue
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
void FrmPopupForm (UInt16 formId)
{
	UInt16	i;

	for ( i = 0; i < formCount; i++ ) {
		if ( (!formPtr[i]->attr.reserved) && (formPtr[i]->formId == formId) ) {
			SaveForm = ActiveForm;
			SaveFormID = ActiveFormID;
			SaveObjIndex = ActiveObjIndex;
			SaveMenu = ActiveMenu;
			VSaveRegion (&(ActiveForm->window.windowBounds), COORD_STRETCH);
			ActiveForm = formPtr[i];
			ActiveFormID = formId;
			CurEvent->eType = frmLoadEvent;
			CurEvent->data.frmLoad.formID = ActiveFormID;

			WPushEvent (CurEvent);
			CurEvent->eType = frmOpenEvent;
			WPushEvent (CurEvent);
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmReleaseObjectMem (Wiscore only)
//
// DESCRIPTION: This routine release the memory occupied by a object.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) index - Index of object.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmReleaseObjectMem (FormType *formP, UInt16 index)
{
	UInt16	k;

	switch ( formP->objects[index].objectType ) {
		case frmFieldObj:
			if ( !formP->objects[index].object.field->textHandle ) {
				if ( formP->objects[index].object.field->textLen )
					Vfree (formP->objects[index].object.field->text);
			}
			if ( formP->objects[index].object.field->lines )
				Vfree (formP->objects[index].object.field->lines);
			Vfree (formP->objects[index].object.field);
			formP->objects[index].object.field = NULL;
			break;
				
		case frmControlObj:
			if ( formP->objects[index].object.control->text )
				Vfree (formP->objects[index].object.control->text);
			Vfree (formP->objects[index].object.control);
			formP->objects[index].object.control = NULL;
			break;

		case frmListObj:
			for ( k = 0; k < formP->objects[index].object.list->numItems; k++ )
				Vfree (formP->objects[index].object.list->itemsText[k]);
			if ( formP->objects[index].object.list->itemsText )
				Vfree (formP->objects[index].object.list->itemsText);
			Vfree (formP->objects[index].object.list);
			formP->objects[index].object.list = NULL;
			break;

		case frmTableObj:
			Vfree (formP->objects[index].object.table->columnAttrs);
			Vfree (formP->objects[index].object.table->rowAttrs);
			Vfree (formP->objects[index].object.table->items);
			Vfree (formP->objects[index].object.table);
			break;

		case frmLabelObj:
			if ( formP->objects[index].object.label->text )
				Vfree (formP->objects[index].object.label->text);
			Vfree (formP->objects[index].object.label);
			break;

		case frmTitleObj:
			if ( formP->objects[index].object.title->text ) {
				Vfree (formP->objects[index].object.title->text);
			}
			Vfree (formP->objects[index].object.title);
			formP->objects[index].object.title = NULL;
			break;

		case frmScrollBarObj:
			Vfree (formP->objects[index].object.scrollBar);
			break;

		case frmPopupObj:
			Vfree (formP->objects[index].object.popup);
			break;

		default:
			Vfree (formP->objects[index].object.ptr);
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmRemoveObject
//
// DESCRIPTION: This routine remove the specified object from the 
//					 specified form.
//
// PARAMETERS:  (FormType **) formPP - Pointer to a pointer to the form
//											in which the new label is installed.
//					 (UInt16) ojbIndex - The object to remove, specified as
//											an index into the list of objects 
//											installed in the form.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err FrmRemoveObject (FormType **formPP, UInt16 objIndex)
{
	FormType	*formP = (FormType *) *formPP;

	FrmReleaseObjectMem (formP, objIndex);

	if ( (formP->numObjects-1) != objIndex ) {	
		// move the last object to the removed position, and release
		// the allocated memory.
		Vmemcpy (&(formP->objects[objIndex]), &(formP->objects[formP->numObjects-1]),
					sizeof (formP->objects[formP->numObjects-1]));
	}
	formP->objects = Vrealloc (formP->objects, 
		sizeof(FormObjListType)*(formP->numObjects-1));

	formP->numObjects--;
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmRestoreActiveState
//
// DESCRIPTION: This routine restores the active window and form state.
//
// PARAMETERS:  (FormActiveStateType) stateP - A pointer to a 
//								FomrActiveStateType structure that is used to
//								save the state.
//
// RETURNED:    Returns 0 on success.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmRestoreActiveState (FormActiveStateType stateP)
{
	Vmemcpy (&frmActiveState, &stateP, sizeof (FormActiveStateType));

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmReturnToForm
//
// DESCRIPTION: This routine erase and delete the currently active form
//					 and make the specified form the active form
//
// PARAMETERS:  (UInt16) formId - ID of the form to display
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/17/01	Initial Revision
//			Jerry 5/04/01	Add ActiveForm
//			Jerry	8/28/01	Modify to push the event to the queue
//			Jerry	11/10/01	Add reserved byte to denote a form or a alert
////////////////////////////////////////////////////////////////////////
void FrmReturnToForm (UInt16 formId)
{
	UInt16	i;

	for ( i = 0; i < formCount; i++ ) {
		if ( (!formPtr[i]->attr.reserved) && (formPtr[i]->formId == formId) ) {
			ActiveForm = formPtr[i];
			ActiveFormID = formId;

			CurEvent->eType = frmCloseEvent;
			WPushEvent (CurEvent);
			ActiveForm = SaveForm;
			ActiveFormID = SaveFormID;
			ActiveObjIndex = SaveObjIndex;
			ActiveMenu = SaveMenu;
			VRedrawRegion (&(ActiveForm->window.windowBounds), COORD_STRETCH);
/*
			CurEvent->eType = frmLoadEvent;
			CurEvent->data.frmLoad.formID = ActiveFormID;

			WPushEvent (CurEvent);
			CurEvent->eType = frmOpenEvent;
			WPushEvent (CurEvent);
*/
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSaveActiveState
//
// DESCRIPTION: This routine saves the active window and form state.
//
// PARAMETERS:  (FormActiveStateType) stateP - A pointer to a 
//								FomrActiveStateType structure that is used to
//								save the state.
//
// RETURNED:    Returns 0 on success.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmSaveActiveState (FormActiveStateType stateP)
{
	Vmemcpy (&stateP, &frmActiveState, sizeof (FormActiveStateType));

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSaveAllForms
//
// DESCRIPTION: This routine send a frmSaveEvent to all open forms.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
void FrmSaveAllForms (void)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetActiveForm
//
// DESCRIPTION: This routine set the active form. All input (key and pen)
//				is directed to the active form and all drawing occurs
//				there.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Add ActiveForm
//			Jerry 7/26/01	Add reserved previous form
////////////////////////////////////////////////////////////////////////
void FrmSetActiveForm(FormType *formP)
{
	if ( formP ) {
		ActiveForm = formP;
		ActiveFormID = formP->formId;
		ActiveForm->focus = 0;
		ActiveObjIndex = -1;
		VSetMenu (formP->menuRscId);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetCategoryLabel
//
// DESCRIPTION: This routine set the category label displayed on the
//					 title line of a form. If the form's visible attribute is
//					 set, redraw the label.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) objIndex - Index of the gadget object in the form
//									object's data structure. 
//					 (Char *) newLabel - Pointer to the name of the new category.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetCategoryLabel (FormType *formP, UInt16 objIndex, Char *newLabel)
{
	if ( formP->objects[objIndex].objectType == frmLabelObj ) {
		formP->objects[objIndex].object.label->text = newLabel;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetControlGroupSelection
//
// DESCRIPTION: This routine set the selected control in a group of 
//					 controls
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt8) groupNum - Control group number.
//					 (UInt16) controlID - ID of control to set.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/17/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetControlGroupSelection (const FormType *formP, UInt8 groupNum, UInt16 controlID)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetControlValue
//
// DESCRIPTION: This routine set the current value of a control. If the
//					 control is visile, it's redrawn.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) objIndex - Index of the gadget object in the form
//									object's data structure. 
//					 (Char *) newValue - New value to set for the control.
//									For sliders, specify a value between the 
//									slider's minimum and maximum.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetControlValue (FormType *formP, UInt16 objIndex, Int16 newValue)
{
	switch (formP->objects[objIndex].objectType) {
		case frmControlObj:
//			if (formP->objects[objIndex].object.control->id == controlID) {
				formP->objects[objIndex].object.control->attr.on = newValue;
//			}
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetEventHandler
//
// DESCRIPTION: This routine registers the event handler callback routine
//				for the specified form
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object
//				(FormEventHandlerType *) handler - Address to the form
//												object.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01		Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
void FrmSetEventHandler(FormType *formP, FormEventHandlerType *handler)
{
	if ( formP != NULL ) {
		formP->handler = handler;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetFocus
//
// DESCRIPTION: This routine set the focus of a form to the specified 
//				object
//
// PARAMETERS:  (FormType *) formp - Pointer to the form object
//				(UInt16) fieldIndex - Index of the object to get the
//							focus in the form.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision as NULL
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	8/27/01	Assign ActiveObjIndex to the focused object
//			Jerry	12/05/01	Set the field hasFocus attribute bit
////////////////////////////////////////////////////////////////////////
void FrmSetFocus(FormType *formP, UInt16 fieldIndex)
{

	formP->focus = fieldIndex;
	ActiveObjIndex = fieldIndex;
	if ( fieldIndex < formP->numObjects )
		formP->objects[fieldIndex].object.field->attr.hasFocus = true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetMenu
//
// DESCRIPTION: This routine change a form's menu bar and make the new
//					 menu active.
//
// PARAMETERS:  (FormType *) formp - Pointer to the form object
//					 (UInt16) menuRscID - Resoure ID of the menu.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
void FrmSetMenu (FormType *formP, UInt16 menuRscID)
{
	if ( formP ) {
		formP->menuRscId = menuRscID;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetObjectBounds
//
// DESCRIPTION: This routine set the bounds or position of an object.
//
// PARAMETERS:  (FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//					 (RectangleType *) rP - Pointer to a RectangleType structure
//												where the object bounds are returned.
//
// RETURNED:    Returns a pointer to the form object of the active form
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetObjectBounds (FormType *formP, UInt16 objIndex, const RectangleType *bounds)
{
	switch (formP->objects[objIndex].objectType) {
		case frmFieldObj:
			formP->objects[objIndex].object.field->rect = *bounds;
			break;

		case frmControlObj:
			formP->objects[objIndex].object.control->bounds = *bounds;
			break;

	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetObjectPosition
//
// DESCRIPTION: This routine set the position of an object
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (UInt16) ObjIndex - Index of an object in the form.
//					 (Coord *) x,y - Pointers where the window-relative x and
//										y positions of the object are returned.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetObjectPosition (FormType *formP, UInt16 objIndex, Coord x, Coord y)
{
	if ( objIndex >= formP->numObjects ) {
		return;
	} else {
		switch (formP->objects[objIndex].objectType) {
			case frmFieldObj:
				formP->objects[objIndex].object.field->rect.topLeft.x = x;
				formP->objects[objIndex].object.field->rect.topLeft.y = y;
				break;

			case frmControlObj:
				formP->objects[objIndex].object.control->bounds.topLeft.x = x;
				formP->objects[objIndex].object.control->bounds.topLeft.y = y;
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmSetTitle
//
// DESCRIPTION: This routine set the title of a form. If the form is
//					 visible, draw the new title
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//					 (Char *) newTitle - Pointer to the new title string.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FrmSetTitle (FormType *formP, Char *newTitle)
{
	UInt16	i;

	for  ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].objectType == frmTitleObj ) {
			formP->objects[i].object.title->text = newTitle;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmShowObject
//
// DESCRIPTION: This routine show the control object on the screen
//
// PARAMETERS:  (FormType *) formp - Pointer to the form structure
//				(UInt16) objIndex - the object index of control
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01		Initial Revision as NULL
//			Jerry	3/14/01		Complete the routine
////////////////////////////////////////////////////////////////////////
void FrmShowObject(FormType *formP, UInt16 objIndex)
{
	if ( objIndex < formP->numObjects ) {
		switch (formP->objects[objIndex].objectType) {
			case frmFieldObj:
				formP->objects[objIndex].object.field->attr.usable = true;
				formP->objects[objIndex].object.field->attr.visible = true;
				VRedrawControl (formP->objects[objIndex]);
				break;

			case frmControlObj:
				formP->objects[objIndex].object.control->attr.usable = true;
				formP->objects[objIndex].object.control->attr.visible = true;
				VRedrawControl (formP->objects[objIndex]);
				break;

			case frmListObj:
				formP->objects[objIndex].object.list->attr.usable = true;
				formP->objects[objIndex].object.list->attr.visible = true;
				VRedrawControl (formP->objects[objIndex]);
				break;

			case frmLabelObj:
				formP->objects[objIndex].object.label->attr.usable = true;
				VRedrawControl (formP->objects[objIndex]);
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    UpdateForm (VIVO OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine redraw the current form
//
// PARAMETERS:  (FormType *) from - Pointer to form structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
////////////////////////////////////////////////////////////////////////
void UpdateForm (FormType *formP)
{
	UInt16	i;

	if ( formP->window.frameType.bits.width )
		VDrawRect (&(formP->window.windowBounds), PS_INSIDEFRAME, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

	for ( i = 0; i < formP->numObjects; i++ ) {
		if ( formP->objects[i].objectType == frmTitleObj ) {
			WDrawFormTitle (formP, i);
		} else {
			VDrawControl(formP->objects[i].objectType, formP->objects[i].object.ptr, DRAW_NORMAL);
		}
	};
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmValidatePtr
//
// DESCRIPTION: This routine return true if the form is visible (is drawn).
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns true if the form is visible, false if it is not
//					 visible.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmValidatePtr (const FormType *formP)
{
	if ( formP ) 
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FrmVisible
//
// DESCRIPTION: This routine return true if the form is visible (is drawn).
//
// PARAMETERS:  (const FormType *) formP - Pointer to the form object.
//
// RETURNED:    Returns true if the form is visible, false if it is not
//					 visible.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FrmVisible (const FormType *formP)
{
	return	formP->attr.visible;
}
