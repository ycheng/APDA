/*========================================================
  List.c
  all routine is running with Platform non-related,
  simulated the list control function in Palm OS.
  Current status is ControlModal free funtion.

  Only LstCheckListHit is Palm non-related function.
  Completed 12 of 17 List Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0327, 2001 by Jerry Chu
					 0525, 2001 by Jerry Chu, add 2 new routines.
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


Int16 LstPopupList (ListType *listP);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstCheckListHit (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check is the hit point inner the list 
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//				(Int16) x - the x coordination of hit point
//				(Int16) y - the y coordination of hit point
//
// RETURNED:    Returns the item's text
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/16/01	Initial Revision
//			Jerry	3/14/01	Change ControlLink type to ListType
//			Jerry 8/09/01	Add update listP->currentItem value function
//			Jerry	8/31/01	Prevent list box boundary exceed the screen
////////////////////////////////////////////////////////////////////////
Int16 LstCheckListHit(ListType *listP, Int16 x, Int16 y)
{
	RectangleType	rect;

	if ( !listP )	return	-1;

	if ( (listP->bounds.topLeft.y+listP->bounds.extent.y) > PDAHEIGHT ) {
		rect.topLeft.y = PDAHEIGHT-listP->bounds.extent.y;
	} else {
		rect.topLeft.y = listP->bounds.topLeft.y;
	}
	rect.topLeft.x = listP->bounds.topLeft.x;
	rect.extent.x = rect.topLeft.x+listP->bounds.extent.x;
	rect.extent.y = rect.topLeft.y+listP->numItems*(FntLineHeight());

	if ( (x>rect.topLeft.x) && (x<rect.extent.x) && 
			(y>rect.topLeft.y) && (y<rect.extent.y) ) {
		listP->currentItem = listP->topItem+(y-rect.topLeft.y)/FntLineHeight();
		return	listP->currentItem;
	} else {
		return	-1;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstDrawList
//
// DESCRIPTION: This routine draw the list object if it's usable. Set
//				its visible attribute to true.
//
// PARAMETERS:  (ListType *)listP - pointer to list object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01	Initial Revision
//			Jerry 7/26/01	Add call callback function
//			Jerry	8/31/01	Move drawing function to VDrawControl
////////////////////////////////////////////////////////////////////////
void LstDrawList (ListType *listP)
{
	if ( !listP )	return;

	// if define draw callback function, call it
	if ( listP->drawItemsCallback ) {
		UInt	i;

		for ( i = 0; i < listP->numItems; i++ ) {
			listP->drawItemsCallback ( i, &listP->bounds, listP->itemsText);
		}
	} else {
		listP->attr.visible = TRUE;

		if ( listP->attr.usable ) {
			UInt16	i, maxY, y;
			RectangleType	rect;

			if ( listP->attr.usable ) {
				Vmemcpy (&(rect), &(listP->bounds), sizeof(RectangleType));

				if ( rect.extent.y == -1 ) {
					rect.extent.y = listP->numItems*FntLineHeight();
				}
				// prevent the bounds exceed the screen
				if ( (rect.topLeft.y+rect.extent.y) > PDAHEIGHT ) {
					rect.topLeft.y = PDAHEIGHT-rect.extent.y;
				}

				VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
				VDrawRect (&rect, PS_INSIDEFRAME, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
				maxY = rect.topLeft.y + rect.extent.y;

				y = rect.topLeft.y;
				i = listP->topItem;

				// the top Item is not begin from 0, draw a up arrow
				if ( i > 0 ) {
					VDrawUpArrow ( rect.topLeft.x+rect.extent.x-(TailArrowWidth+3), 
						rect.topLeft.y+3, SOLID_TAIL );
				}
				while ( i < listP->numItems ) {
					if ( (y + FntLineHeight()) > maxY ) {
						// more than 1 items not shown, draw a down arrow
						if ( i < listP->numItems ) {	
							VDrawDownArrow ( rect.topLeft.x+rect.extent.x-(TailArrowWidth+3), 
								rect.topLeft.y+rect.extent.y-FntCharHeight()-3, SOLID_TAIL );
						}
						break;
					}
					VDrawString ((Coord)(rect.topLeft.x+1), 
									(Coord)(y+FntLineHeight()/4),
									listP->itemsText[i], Vstrlen(listP->itemsText[i]), 
									SINGLELINE, CL_FOREGROUND, COORD_STRETCH);

					// if item is current item, reverse the background
					if ( i == listP->currentItem ) {
						RectangleType	currentItemRect;
							// not adjust, maybe have problem
						currentItemRect.topLeft.x = rect.topLeft.x+1;
						currentItemRect.topLeft.y = y+1;
						currentItemRect.extent.x = rect.extent.x-2;
						currentItemRect.extent.y = FntLineHeight()-2;
						VDrawRect (&currentItemRect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_XOR);
					}
					y += FntLineHeight();
					i++;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstEraseList
//
// DESCRIPTION: This routine erase a list object
//
// PARAMETERS:  (ListType *)listP - pointer to list object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstEraseList (ListType *listP)
{
	if ( !listP )	return;

	listP->attr.visible = FALSE;
	VClearControl ((ControlType *)listP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstGetNumberOfItems
//
// DESCRIPTION: This routine return the number of items in a list.
//
// PARAMETERS:  (const ListType *) listP - Pointer to the list structure
//
// RETURNED:    Returns the number of items in a list.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 LstGetNumberOfItems (const ListType *listP)
{
	if ( listP )
		return	listP->numItems;
	else
		return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstGetSelection
//
// DESCRIPTION: This routine return the currently selected choice in
//				the list
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//
// RETURNED:    Returns the item number of the current list choice.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 LstGetSelection (ListType *listP)
{
	if ( listP )
		return	listP->currentItem;
	else
		return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstGetSelectionText
//
// DESCRIPTION: This routine get the item's text from item list
//
// PARAMETERS:  (const ListType *) listP - Pointer to the list structure
//				(Int16) itemNum - the item's text which to retrieve
//
// RETURNED:    Returns the item's text
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/16/01		Initial Revision
//			Jerry	3/14/01		Change ControlLink type to ListType
////////////////////////////////////////////////////////////////////////
Char *LstGetSelectionText (const ListType *listP, Int16 itemNum)
{
	if ( listP )
		return	listP->itemsText[itemNum];
	else
		return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstGetVisibleItems
//
// DESCRIPTION: This routine return the number of visible items
//
// PARAMETERS:  (const ListType *) listP - Pointer to the list structure
//
// RETURNED:    Returns the number of items visible.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 LstGetVisibleItems (const ListType *listP)
{
	if ( listP )
		return	listP->bounds.extent.y/(FntCharHeight());
	else
		return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstMakeItemVisible
//
// DESCRIPTION: This routine make an item visible, preferabley at the
//				top. If the item is already visible, make no changes.
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//				(Int16) itemNum - Item to select(0 = first item in list)
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstMakeItemVisible (ListType *listP, Int16 itemNum)
{
	if ( listP )
		listP->topItem = itemNum;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstNewList
//
// DESCRIPTION: This routine create a new list object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (void *) formPP - Pointer to the pointer to the form in
//										which the new list is installed.
//					 (UInt16) id - Symbolic ID of the list, specified by the
//										developer.
//					 (Coord) x - Horizontal coordinate of the upper-left corner
//										of the list's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left corner
//										of the list's boundaries.
//					 (Coord) width - Width of the list, expressed in pixels.
//					 (Coord) height - Height of the list, expressed in pixels.
//					 (FontID) font - Font ID of the list.
//					 (Int16) visibleItems - Number of list items that can be
//										viewed together.
//					 (Int16) triggerID - Symbolic ID of the popup trigger 
//										associated with the new list.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err LstNewList (void **formPP, UInt16 id, Coord x, Coord y,
						 Coord width, Coord height, FontID font,
						 Int16 visibleItems, Int16 triggerID)
{
	ListType	*listP;
	FormType	*formP = (FormType *) *formPP;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmListObj;
	listP = formP->objects[formP->numObjects++].object.list = (ListType *) Vmalloc (sizeof(ListType));

	Vmemset (listP, 0, sizeof (ListType));

	listP->numItems = 0;
	listP->id = id;
	listP->font = font;

	listP->bounds.topLeft.x = x;
	listP->bounds.topLeft.y = y;
	listP->bounds.extent.x = width;
	listP->bounds.extent.y = height;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstPopupList
//
// DESCRIPTION: This routine display a modal window that contains the
//				items in the list.
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//
// RETURNED:    Returns the list item selected, or -1 if no item was 
//				selected
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/16/01	Initial Revision
//			Jerry	3/14/01	Change some ControlLink type to ListType
//			Jerry 8/01/01	Clear pen down event after get selection
//			Jerry	8/09/01	Modify to call LstDrawList function and add
//								hit on up or down arrow action
//			Jerry	8/31/01	Prevent list box boundary exceed the screen
////////////////////////////////////////////////////////////////////////
Int16 LstPopupList (ListType *listP)
{
	UInt16			visibleItems = LstGetVisibleItems (listP);
	RectangleType	rect;
	Int16				selection, usable;
	Int16		direction=NOSCROLL;	// push on the scroll up or down arrow
	Int16		x, y, i, maxStrLen=0, strLen;
	Int16		minX, maxX;
	Int16		minUpArrowY, maxUpArrowY, minDownArrowY, maxDownArrowY;
	EventType	event;
	Boolean	bHasScroll=FALSE;

	if ( !listP )	return	-1;

	usable = listP->attr.usable;
	listP->attr.usable = true;

	listP->bounds.topLeft.x --;
	Vmemcpy ( &rect, &(listP->bounds), sizeof (RectangleType) ) ;
	// prevent the bounds exceed the screen

	if ( rect.extent.y == -1 ) {
		rect.extent.y = listP->numItems*FntLineHeight();
	}
	if ( (rect.topLeft.y+rect.extent.y) > PDAHEIGHT ) {
		rect.topLeft.y = PDAHEIGHT-rect.extent.y;
	}

	// calculate the max string length, and set the proper x coordinate
	for ( i = 0; i < listP->numItems; i++ ) {
		strLen = FntCharsWidth (listP->itemsText[i], (Int16)Vstrlen (listP->itemsText[i]));
		if ( strLen > maxStrLen )
			maxStrLen = strLen;
	}

	if ( (rect.topLeft.x+rect.extent.x) > VSysToPDAXRes((maxStrLen-6)) ) {
		listP->bounds.extent.x = rect.extent.x = VSysToPDAXRes((maxStrLen+6));
		listP->bounds.topLeft.x = rect.topLeft.x = PDAWIDTH-rect.extent.x-1;
	}

	VSaveRegion (&rect, COORD_STRETCH);

	LstDrawList (listP);

	// set the bounds of list
	minX = rect.topLeft.x+rect.extent.x-(Int16)(TailArrowWidth*1.2);
	maxX = minX+TailArrowWidth;

	if ( listP->numItems > (rect.extent.y/FntLineHeight()) ) {
		minUpArrowY = rect.topLeft.y+3;
		maxUpArrowY = minUpArrowY+TailArrowHeight;
		minDownArrowY = rect.topLeft.y+rect.extent.y-TailArrowHeight-3;
		maxDownArrowY = minDownArrowY+TailArrowHeight;
		bHasScroll = TRUE;
	}
	while (1) {
//		WPeekEventsDDK();
		EvtGetEvent(&event, 200);

		// Check mouse click region here and set controlID
		if ( event.eType == penUpEvent ) {
			x = event.screenX;
			y = event.screenY;

			if ( bHasScroll && (x >= minX) && (x <= maxX) ) {
				if ( (y >= minUpArrowY) && (y <= maxUpArrowY) ) {
					direction = SCROLLUP;
				} else if ( (y >= minDownArrowY) && (y <= maxDownArrowY) ) {
					direction = SCROLLDOWN;
				}
			}

			if ( direction ) {	// hit on up or down arrow
				LstScrollList (listP, direction, visibleItems);
				direction=NOSCROLL;
				LstDrawList (listP);
				continue;
			} else {		// Select one item in List control
				selection = LstCheckListHit (listP, CurEvent->screenX, CurEvent->screenY);
				if ( selection >= 0 ) {
					listP->currentItem = selection;
				} 
				VRedrawRegion (&rect, COORD_STRETCH);
			}

			// clear penDownEvent, penUpEvent in event queue
			listP->attr.usable = usable;
			return	selection;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstScrollList
//
// DESCRIPTION: This routine scroll the list up or down a number of imtes
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure.
//					 (WinDrectionType) direction - Direction to scroll.
//					 (Int16) itemCount - Items to scroll in direction.
//
// RETURNED:    Returns true when the list is actually scrolled.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean LstScrollList (ListType *listP, WinDrectionType direction,
								Int16 itemCount)
{
	UInt16	visibleItems = LstGetVisibleItems (listP);

	if ( !listP )	return	false;

	if ( direction ) {	// scroll down
		listP->topItem += (direction*itemCount);
		if ( listP->topItem > listP->numItems )
			listP->topItem = listP->numItems-visibleItems;
		else if ( listP->topItem < 0 )
			listP->topItem = 0;
	}

	return	true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetDrawFunction
//
// DESCRIPTION: This routine set a callback functioin to draw each item
//				instead of drawing the item's text string.
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//				(ListDrawDataFuncPtr) func - Pointer to function which
//											draws items.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstSetDrawFunction (ListType *listP, ListDrawDataFuncPtr func)
{
	if ( !listP )	return;

	listP->drawItemsCallback = func;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetHeight
//
// DESCRIPTION: This routine set the number of items visible in a list
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//				(Int16) visibleItems - Number of choices visible at once
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstSetHeight (ListType *listP, Int16 visibleItems)
{
	if ( !listP )	return;

	listP->bounds.extent.y = visibleItems*(FntCharHeight());
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetListChoices
//
// DESCRIPTION: This routine set the items of a list to the array of 
//					 text strings passed to this function. This function
//					 doesn't affect the display of the list. If the list is
//					 visible, erases the old list items.
//
// PARAMETERS:  (ListType *) listP - Pointer to the list object.
//					 (Char **) itemText - Pointer to an array of text strings.
//					 (Int16) numItems - Number of choices in the list.
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
//			Jerry 7/25/01	Set listP->numItems to numItems
////////////////////////////////////////////////////////////////////////
void LstSetListChoices (ListType *listP, Char **itemsText, UInt16 numItems)
{
	Int	index, textLen;

	if ( !listP )	return;

//	Vfree (listP->itemsText);
	listP->numItems = numItems;
	listP->itemsText = Vrealloc (listP->itemsText, numItems*sizeof(Char *));

	for ( index = 0; index < numItems; index++ ) {
			textLen = (Int) Vstrlen(itemsText[index]);
			listP->itemsText[index] = Vmalloc (textLen+1);
			Vmemcpy (listP->itemsText[index], itemsText[index], textLen+1);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetPosition
//
// DESCRIPTION: This routine set the position of a list
//
// PARAMETERS:  (ListType *) listP - Pointer to the list structure
//					 (Coord) x - Left bound of list
//					 (Coord) y - Top bound of list
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/16/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstSetPosition (ListType *listP, Coord x, Coord y)
{
	if ( !listP )	return;

	listP->bounds.topLeft.x = x;
	listP->bounds.topLeft.y = y;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetSelection
//
// DESCRIPTION: This routine set the selection for a list
//
// PARAMETERS:  (ListType *) listP - Pointer to list object
//					 (Int16) itemNum - Item to select
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstSetSelection (ListType *listP, Int16 itemNum)
{
	if ( !listP )	return;

	if ( itemNum < listP->numItems ) {
		listP->currentItem = itemNum;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    LstSetTopItem
//
// DESCRIPTION: This routine set the item visible. The item cannot
//				become the top item if it's on the last page.
//
// PARAMETERS:  (ListType *) listP - Pointer to list object
//					 (Int16) itemNum - Item to select
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/16/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void LstSetTopItem (ListType *listP, Int16 itemNum)
{
	if ( !listP )	return;

	if ( itemNum < listP->numItems ) {
		listP->topItem = itemNum;
	}
}


#define	ScrollBarWidth			7

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SclDrawScrollBar
//
// DESCRIPTION: This routine draw a scrollbar.
//
// PARAMETERS:  (const ScrollBarPtr *) bar - Pointer to a scroll bar
//										structure.
//
// RETURNED:    Retures nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/09/01	Initial Revision
//			Jerry	8/13/01	Add draw the entity bar and add judgementation
////////////////////////////////////////////////////////////////////////
void SclDrawScrollBar (const ScrollBarPtr barP)
{
	RectangleType	rect;
	UInt16	barStartY, barEndY;

	if ( !barP )	return;

	// if no maxValue, skip draw scroll bar
//	if ( (barP->maxValue == 0) || (barP->maxValue < barP->pageSize) )
	if ( (barP->maxValue <= 0) )
		return;

	Vmemcpy ( &rect, &(barP->bounds), sizeof(RectangleType) );
	VDrawRect (&(barP->bounds), PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);

	if ( rect.extent.x == -1 ) {
		rect.extent.x = ScrollBarWidth;
	}
	VDrawLine ( (Coord)((rect.topLeft.x) + rect.extent.x/2-1),
					(Coord)(rect.topLeft.y+FntLineHeight()/4), 
					(Coord)((rect.topLeft.x) + rect.extent.x/2-1),
					(Coord)(rect.topLeft.y+rect.extent.y-FntCharHeight()),
					THIN_LINE,
					FOREGROUNDCOLOR,
					PS_SOLID);
	VDrawLine ( (Coord)((rect.topLeft.x) + rect.extent.x/2+2),
					(Coord)(rect.topLeft.y+FntLineHeight()/4), 
					(Coord)((rect.topLeft.x) + rect.extent.x/2+2),
					(Coord)(rect.topLeft.y+rect.extent.y-FntCharHeight()),
					THIN_LINE,
					FOREGROUNDCOLOR,
					PS_SOLID);

	VDrawUpArrow ( rect.topLeft.x, rect.topLeft.y, SOLID_SMALL ) ;
	VDrawDownArrow ( rect.topLeft.x, 
						  rect.topLeft.y+rect.extent.y-FntCharHeight(), 
						  SOLID_SMALL ) ;

	// calculate the start and end of vertical coordinate of entity bar
	barStartY = (rect.extent.y-FntCharHeight()*3/2)*barP->value/
		(barP->maxValue+barP->pageSize)+rect.topLeft.y;
	if ( barStartY == rect.topLeft.y )	
		barStartY = rect.topLeft.y+FntLineHeight()/4;
	barEndY = (rect.extent.y-FntCharHeight())*(barP->value+barP->pageSize)/
		(barP->maxValue+barP->pageSize)+rect.topLeft.y;
	if ( barEndY > (rect.topLeft.y+rect.extent.y-FntCharHeight()) )
		barEndY = (rect.topLeft.y+rect.extent.y-FntCharHeight());

	VDrawLine ( (Coord)((rect.topLeft.x) + rect.extent.x/2),
					(Coord)barStartY, 
					(Coord)((rect.topLeft.x) + rect.extent.x/2),
					(Coord)barEndY,
					THICK_LINE,
					FOREGROUNDCOLOR,
					PS_SOLID);

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SclGetScrollBar
//
// DESCRIPTION: This routine retrieve a scroll bar's current position,
//					 its range, and the size of a page.
//
// PARAMETERS:  (const ScrollBarPtr *) bar - Pointer to a scroll bar
//										structure.
//					 (Int16 *) valueP - A value representing the scroll bar's
//										current position.
//					 (Int16 *) minP - A value representing the top of the 
//										user interface object.
//					 (Int16 *) maxP - A value representing the bottom of the
//										user interface object.
//					 (Int16 *) pageSizeP - Pointer to size of a page.
//
// RETURNED:    Retures nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void SclGetScrollBar (const ScrollBarPtr barP, Int16 *valueP,
							Int16 *minP, Int16 *maxP, Int16 *pageSizeP)
{
	if ( barP ) {
		*valueP = barP->value;
		*minP = barP->minValue;
		*maxP = barP->maxValue;
		*pageSizeP = barP->pageSize;
	} else {
		*valueP = 0;
		*minP = 0;
		*maxP = 0;
		*pageSizeP = 0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SclSetScrollBar
//
// DESCRIPTION: This routine set the scroll bar's current position,
//					 its range, and the size of a page. If the scroll bar
//					 is visible and its minimum and maximum values are not
//					 equal, it's redrawn.
//
// PARAMETERS:  (const ScrollBarPtr *) bar - Pointer to a scroll bar
//										structure.
//					 (Int16) value - The position the scroll bar should move
//										to.
//					 (Int16) min - Minimum value.
//					 (Int16) max - Maximum value.
//					 (Int16) pageSize - Number of lines of text that can be 
//										displayed on the screen at one time.
//
// RETURNED:    Retures nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void SclSetScrollBar (const ScrollBarPtr barP, Int16 value, const Int16 min,
							 const Int16 max, const Int16 pageSize)
{
	if ( !barP )	return;

	barP->value = value;
	barP->minValue = min;
	barP->maxValue = max;
	barP->pageSize = pageSize;

	VDrawControl (frmScrollBarObj, barP, DRAW_NORMAL);
}
