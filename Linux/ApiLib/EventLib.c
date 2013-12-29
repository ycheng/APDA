#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#define	eventQueueSize		32

EventType	eventQueue[eventQueueSize];
Int16			eventHead=0;
Int16			eventTail=eventQueueSize-1;
UInt16		eventCount=0;


Int16			ActiveObjIndex = -1;
UInt8			grfInputState = grfNONE;
extern Int16	lastScreenX, lastScreenY;
extern Boolean			MenuActive;

Boolean WPushEvent (const EventType *event);
Boolean WPopEvent (EventType *event);
extern void WEvtGetEvent(EventType *event, Int32 timeout);
extern void VDrawGrafState (Boolean drawMode);
extern Boolean WWatchEvent (EventType *event);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    EvtAddEventToQueue
//
// DESCRIPTION: This routine add an event to the event queue.
//
// PARAMETERS:  (const EventType *) event - Pointer to the structure
//													that contains the event.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void EvtAddEventToQueue (const EventType *event)
{
	WPushEvent (event);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    EvtGetEvent
//
// DESCRIPTION: This routine return the next available event.
//
// PARAMETERS:  (EventType *) event - Pointer to the structure to hold
//											the event returned.
//              (Int32) timeout - Maximum number of ticks to wait before
//											an event is returned.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	5/17/01	Add handwriting recognition function
//			Jerry 7/31/01	use WPeekEventsDDK() instead of copy CurEvent 
//			Jerry	10/31/01	Modify to check timeout, and use WPushEvent and
//								WPopEvent to push and popup event
////////////////////////////////////////////////////////////////////////
void EvtGetEvent(EventType *event, Int32 timeout)
{
	WEvtGetEvent (event, timeout);
}

void EvtGetPen (Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown)
{
	EventType	event;
	int	count=0;

	do {
		WPeekEventsDDK();
		EvtGetEvent (&event, -1);
		count++;
	} while ( !((event.eType >= 1) && (event.eType <= 3)) && 
			(count < (eventQueueSize/2)) );

	if ( (event.eType >= 1) && (event.eType <= 3) ) {
		*pScreenX = event.screenX;
		*pScreenY = event.screenY;
		*pPenDown = event.penDown;
	} else {
		*pScreenX = 0;
		*pScreenY = 0;
		*pPenDown = 0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SysHandleEvent
//
// DESCRIPTION: This routine return the next available event.
//
// PARAMETERS:  (EventType *) event - Pointer to the structure to hold
//											the event returned.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry	7/04/01	Add push button control handler
//			Jerry 8/03/01	Add popSelectEvent
//			Jerry 8/07/01	Modify popSelectEvent to get the correct List
//			Jerry 8/08/01	Complete event->data.popSelect event
//			Jerry	8/09/01	Add frmListObj option
//			Jerry	8/28/01	Processing frmCloseEvent, blinking field cursor
//			Jerry	9/03/01	Clear control before redraw it
//			Jerry	9/12/01	Fixed push button showing problem
//			Jerry	9/13/01	Put the string on the center of control
////////////////////////////////////////////////////////////////////////
Boolean SysHandleEvent(EventType *event)
{
	if ( MenuActive || (!ActiveForm) || (ActiveObjIndex == -1) )
		return	0;

	// if current active control is fieldtype, draw cursor if editable
	if ( (ActiveForm->objects[ActiveObjIndex].objectType == frmFieldObj) &&
			(ActiveForm->objects[ActiveObjIndex].object.field->attr.editable) ) {
		VDrawCursor ( (Coord)(ActiveForm->objects[ActiveObjIndex].object.field->insPtXPos),
						  (Coord)(ActiveForm->objects[ActiveObjIndex].object.field->insPtYPos+2),
						  CUR_DRAW);
		VDrawGrafState (TRUE);
	} else {
		VDrawGrafState (FALSE);
	}

	// close current form, free all allocate memory on this form.
	if ( event->eType == ctlSelectEvent ) {
		if ( (ActiveForm->objects[ActiveObjIndex].objectType == frmControlObj) ) {
			if (ActiveForm->objects[ActiveObjIndex].object.control->style == checkboxCtl) {
				// CHECKBOX Style[0] is used for checked message
				ControlType *ctlP = ActiveForm->objects[ActiveObjIndex].object.control;

//				VSetCheckBox (ctlP, ctlP->attr.on);
				ctlP->attr.on = ~ctlP->attr.on;

				VRedrawControl (ActiveForm->objects[ActiveObjIndex]);
			} else if (ActiveForm->objects[ActiveObjIndex].object.control->style == pushButtonCtl) {
				// Press on push button, invert the push button
				ControlType *ctlP = ActiveForm->objects[ActiveObjIndex].object.control;
				RectangleType	rect;
				int			strWidth;

				if ( !ctlP->attr.on ) {
					int	i;

					rect.topLeft.x = (ctlP->bounds.topLeft.x+1);
					rect.topLeft.y = (ctlP->bounds.topLeft.y+1);
					// get the width of string
					strWidth = FntCharsWidth (ctlP->text, (Int16)Vstrlen(ctlP->text));

					if ( ctlP->bounds.extent.x == -1 ) {
						rect.extent.x = (UInt16)strWidth+2;
					} else {
						rect.extent.x = (ctlP->bounds.extent.x-3);
					}
					if ( ctlP->bounds.extent.y == -1 ) {
						rect.extent.y = FntCharHeight()-3;
					} else {
						rect.extent.y = (ctlP->bounds.extent.y-4);
					}

					VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_XOR);
/*
					VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

					// calculate string width (put the string on the center of control)
					VDrawString ((Coord)(ctlP->bounds.topLeft.x+((ctlP->bounds.extent.x-strWidth)/2)), 
									(ctlP->bounds.topLeft.y), 
									ctlP->text, 
									Vstrlen(ctlP->text), 
									SINGLELINE, CL_BACKGROUND, COORD_STRETCH);
*/
					ctlP->attr.on = 1;
	
					for ( i = 0; i < ActiveForm->numObjects; i++ ) {
						// if other same group push button is on, off it
						if ( (i != ActiveObjIndex) &&
							  (ActiveForm->objects[i].objectType == frmControlObj) &&
							  (ActiveForm->objects[i].object.control->style == pushButtonCtl) &&
							  (ActiveForm->objects[i].object.control->attr.on) ) {
							ctlP = ActiveForm->objects[i].object.control;
							rect.topLeft.x = (ctlP->bounds.topLeft.x+1);
							rect.topLeft.y = (ctlP->bounds.topLeft.y+1);
							// get the width of string
							strWidth = FntCharsWidth (ctlP->text, (Int16)Vstrlen(ctlP->text));
							if ( ctlP->bounds.extent.x == -1 ) {
								rect.extent.x = strWidth+2;
							} else {
								rect.extent.x = (ctlP->bounds.extent.x-3);
							}
							if ( ctlP->bounds.extent.y == -1 ) {
								rect.extent.y = FntCharHeight()-3;
							} else {
								rect.extent.y = (ctlP->bounds.extent.y-4);
							}
	
							VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_XOR);
/*
							VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

							VDrawString ((Coord)(ctlP->bounds.topLeft.x+((ctlP->bounds.extent.x-strWidth)/2)), 
											(ctlP->bounds.topLeft.y), 
											ctlP->text, 
											Vstrlen(ctlP->text), 
											SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
*/
							ctlP->attr.on = 0;
						}
					}
				}
			}
		} // end of	if ( (ActiveForm->objects[ActiveObjIndex].objectType == frmControlObj) ) {
/*
	} else if ( event->eType == popSelectEvent ) {
		Int16				theIndex, i, listObjIndex = -1;
		UInt16			hitObjIndex = ActiveObjIndex;
		UInt16			popupID = ActiveForm->objects[ActiveObjIndex].object.control->id;
		UInt16			listID=0;

		event->data.popSelect.controlP = (ControlType *)ActiveForm->objects[ActiveObjIndex].object.control;
		for ( i = 0; i < ActiveForm->numObjects; i++ ) {
			if ( (ActiveForm->objects[i].objectType == frmPopupObj) && 
					(popupID == ActiveForm->objects[i].object.popup->controlID) ) {
				listID = ActiveForm->objects[i].object.popup->listID;
				break;
			}
		}

		if ( listID ) {
			event->data.popSelect.listID = listID;
			for ( i = 0; i < ActiveForm->numObjects; i++ ) {
				if ( (ActiveForm->objects[i].objectType == frmListObj) && 
						(listID == ActiveForm->objects[i].object.list->id) ) {
					listObjIndex = i;
					event->data.popSelect.listP = ActiveForm->objects[ActiveObjIndex].object.list;
					break;
				}
			}

			if ( listObjIndex >= 0 ) {
				ListType *listP = (ListType *)ActiveForm->objects[listObjIndex].object.list;

				event->data.popSelect.priorSelection = LstGetSelection (listP);
				theIndex = LstPopupList(listP);

				if (theIndex >= 0) {
					RectangleType	rect;
					ControlType *controlP;
					int		strWidth;
						
					event->data.popSelect.selection = theIndex;
					ActiveObjIndex = hitObjIndex;
					controlP = (ControlType *)ActiveForm->objects[ActiveObjIndex].object.control;

					// clear the control first
					Vmemcpy (&rect, &(controlP->bounds), sizeof(RectangleType));

					strWidth = FntCharsWidth (controlP->text, (Int16)Vstrlen(controlP->text));
					// recalculate size if attribute is AUTO
					if ( controlP->bounds.extent.x == -1 ) {
						rect.extent.x = strWidth;
						if ( controlP->style == popupTriggerCtl ) 
							rect.extent.x += ArrowWidth;
					}
					if ( controlP->bounds.extent.y == -1 ) {
						rect.extent.y = FntCharHeight();
					}
					VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);

					// draw control
					CtlSetLabel (ActiveForm->objects[ActiveObjIndex].object.control, 
						LstGetSelectionText(listP,theIndex));
				}
			}
		}
*/
	} else if ( event->eType == keyDownEvent ) {
		// CHECKBOX Style[0] is used for checked message
		FormObjListType	object = ActiveForm->objects[ActiveObjIndex];
		switch (object.objectType) {
			case frmTableObj:
				{
					TableType	*tableP = object.object.table;
					UInt16	index = tableP->currentRow*tableP->numColumns+tableP->currentColumn;

					if ( !tableP->attr.editable )
						return	false;

					if ( tableP->items[index].ptr == NULL ) {
						tableP->items[index].ptr = (char *) Vmalloc(1);
						tableP->items[index].ptr[0] = 0;
					}
					tableP->items[index].ptr = 
						(char *) Vrealloc(tableP->items[index].ptr, Vstrlen(tableP->items[index].ptr)+2);
					VAppendStr (tableP->items[index].ptr, (UInt16)event->data.keyDown.keyCode);
					VRedrawControl (object);
				}
				break;
			case frmFieldObj:
				{
					FieldType *fldP = object.object.field;

					if ( !fldP->attr.editable )
						return	false;

					FldInsert (fldP, (char*)&(event->data.keyDown.chr), 1);
//					VRedrawControl (object);
					break;
				}
			default :
				{
/*
					ControlType *ctlP = object.object.control;

					if ( !ctlP->attr.enabled )
						return	false;

					if ( ctlP->text == NULL ) {
						ctlP->text = (char *) Vmalloc(1);
						ctlP->text[0] = 0;
					}
					ctlP->text = (char *) Vrealloc(ctlP->text, Vstrlen(ctlP->text)+2);
					VAppendStr (ctlP->text, (UInt16)event->data.keyDown.keyCode);
					VRedrawControl (object);
*/
					break;
				}
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WPushEvent
//
// DESCRIPTION: This routine push current event to the event queue.
//
// PARAMETERS:  (EventType *) event - Pointer to the structure to hold
//											the event returned.
//
// RETURNED:    Returns the index of the event in the queue.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean WPushEvent (const EventType *event)
{
	if ( eventCount < eventQueueSize ) {
		if ( eventHead == eventQueueSize )
			eventHead = 0;

		Vmemcpy (&(eventQueue[eventHead]), event, sizeof(EventType));
		eventHead++;
		eventCount++;

		return	true;
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WPopEvent
//
// DESCRIPTION: This routine pop up the event in the first position in
//					 the event queue.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the event in the queue.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean WPopEvent (EventType *event)
{
	if ( eventCount > 0 ) {
		if ( eventTail == (eventQueueSize-1) ) {
			eventTail = 0;
		} else {
			eventTail++;
		}
		
		eventCount--;
		Vmemcpy (event, &eventQueue[eventTail], sizeof(EventType));

		return	true;
	}

	Vmemset (event, 0, sizeof(EventType));

	return	false;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    WWatchEvent
//
// DESCRIPTION: This routine watch (no pop up) the event in the first position
//					 in the event queue.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the event in the queue.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/30/01	Initial Revision
//////////////////////////////////////////////////////////////////////////////
Boolean WWatchEvent (EventType *event)
{
	if ( eventCount > 0 ) {
		Vmemcpy (event, &eventQueue[eventTail], sizeof(EventType));

		return	true;
	}
	Vmemset (event, 0, sizeof(EventType));

	return	false;
}

void WResetEvent (EventType *event)
{
	Vmemset (CurEvent, 0, sizeof (EventType));
	Vmemset (event, 0, sizeof (EventType));
}

void WFlushEvent ()
{
	eventHead=0;
	eventTail=eventQueueSize-1;
	eventCount = 0;
}
