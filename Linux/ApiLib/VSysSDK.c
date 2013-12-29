#include <stdio.h>

#include <VCommon.h>
#include "VParser.h"
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#include <apidll.h>
#include <WisDll.h>

Int16	HitCtlIndex=-1;
Int16	PenDownID = -1;

Boolean		HandWritingStart=FALSE;
extern UInt16		sysBitmapCount;
extern BitmapLink	*sysBitmapPtr;
extern Int16		lastScreenX, lastScreenY;
extern Boolean		MenuActive;
extern GrfStateType	grfState;

extern Boolean WPushEvent (const EventType *event);
extern Int16 LstCheckListHit(ListType *listP, Int16 x, Int16 y);
extern void WClearScreen (int mode);
extern void drawline (Coord x0, Coord y0, Coord x1, Coord y1);
extern void VDrawGrafState (Boolean drawMode);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VClearControl
//
// DESCRIPTION: This routine clear control's frame from the screen.
//
// PARAMETERS:  (ControlType *)controlP - pointer to control object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01	Initial Revision
//			Jerry	9/03/01	If extent.x or .y equal -1, it's AUTO attribute,
//								recalculat width and height
////////////////////////////////////////////////////////////////////////
void VClearControl (ControlType *controlP)
{
	RectangleType	rect;
	int	strWidth;

	Vmemcpy (&rect, &(controlP->bounds), sizeof(RectangleType));
	if ( controlP->bounds.extent.x == -1 ) {
		strWidth = FntCharsWidth (controlP->text, (Int16)Vstrlen(controlP->text));
		rect.extent.x = strWidth;
	}
	if ( controlP->bounds.extent.y == -1 ) {
		rect.extent.y = FntCharHeight()+2;
	}
	VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WDrawBattery
//
// DESCRIPTION: This routine draw the battery bitmap on the top of 
//					 screen, and show the remain energy of battery.
//	
// PARAMETERS:  (UInt16) energy - The remain energy of battery.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WDrawBattery (UInt16 energy)
{
	RectangleType	rect;
	Char	buffer[5];

	// Draw the battery outline
	VDrawLine ( BATTERYSTARTX, 
					BATTERYSTARTY, 
					(BATTERYSTARTX+BATTERYWIDTH), 
					BATTERYSTARTY, 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH),
					BATTERYSTARTY, 
					(BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+BATTERYSEGMENT), 
					(BATTERYSTARTX+BATTERYWIDTH+BATTERYSEGMENT), 
					(BATTERYSTARTY+BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH+BATTERYSEGMENT), 
					(BATTERYSTARTY+BATTERYSEGMENT), 
					(BATTERYSTARTX+BATTERYWIDTH+BATTERYSEGMENT), 
					(BATTERYSTARTY+2*BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH+BATTERYSEGMENT), 
					(BATTERYSTARTY+2*BATTERYSEGMENT), 
					(BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+2*BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+2*BATTERYSEGMENT), 
					(BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+3*BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( (BATTERYSTARTX+BATTERYWIDTH), 
					(BATTERYSTARTY+3*BATTERYSEGMENT), 
					BATTERYSTARTX, 
					(BATTERYSTARTY+3*BATTERYSEGMENT), 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
	VDrawLine ( BATTERYSTARTX, 
					(BATTERYSTARTY+3*BATTERYSEGMENT), 
					BATTERYSTARTX, 
					BATTERYSTARTY, 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);

	// Draw the battery remain energy block
	rect.topLeft.x = VPDAToSysXCoord(BATTERYSTARTX)+2;
	rect.topLeft.y = VPDAToSysYCoord(BATTERYSTARTY)+2;
	rect.extent.x = VPDAToSysXRes(((BATTERYWIDTH)*energy/100))-3;
	rect.extent.y = VPDAToSysYRes((BATTERYSTARTY+3*BATTERYSEGMENT))-
						VPDAToSysYRes(BATTERYSTARTY)-4;
	VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_NORMAL, DRAW_SET);

	// Draw the text of remain energy
	StrIToA (buffer, energy);
	Vstrcat (buffer, "%");
	VDrawString ( (BATTERYSTARTX+BATTERYWIDTH+2*BATTERYSEGMENT),
					  (BATTERYSTARTY+1),
					  buffer,
					  Vstrlen(buffer),
					  SINGLELINE,
					  CL_FOREGROUND, 
					  COORD_STRETCH);
}

void VSetCheckBox(const ControlType *ctlP, Boolean style)
{
	VDrawCheck ( ctlP->bounds.topLeft.x, 
					 (Coord)(ctlP->bounds.topLeft.y+4), 
					 style);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VPDAToSysRect
//
// DESCRIPTION: This routine convert the PDA rectangle resolution 
//				to system rectangle resolution
//
// PARAMETERS:  (RectangleType *) dstRect - the destination rectangle
//				(RectangleType *) srcRect - the source rectangle
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void VPDAToSysRect(RectangleType *dstRect, const RectangleType *srcRect)
{
	dstRect->topLeft.x = VPDAToSysXCoord(srcRect->topLeft.x);
	dstRect->topLeft.y = VPDAToSysYCoord(srcRect->topLeft.y);
	dstRect->extent.x = VPDAToSysXRes(srcRect->extent.x);
	dstRect->extent.y = VPDAToSysYRes(srcRect->extent.y);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VPDAToSysPoint
//
// DESCRIPTION: This routine convert the PDA PointType resolution 
//				to system PointType resolution
//
// PARAMETERS:  (PointType *) dstPoint - the destination rectangle
//				(PointType *) srcPoint - the source rectangle
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void VPDAToSysPoint(PointType *dstPoint, const PointType *srcPoint)
{
	dstPoint->x = VPDAToSysXCoord(srcPoint->x);
	dstPoint->y = VPDAToSysYCoord(srcPoint->y);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawControl
//
// DESCRIPTION: This routine draw the control on the screen
//
// PARAMETERS:  (UInt16) type - the type of control
//					 (void *) control - Pointer to control structure
//					 (int) mode - Drawing mode, DRAW_NORMAL for normal, 
//										DRAW_INVERT for invert
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/12/01	Initial Revision
//			Jerry	3/20/01	Modify to ControlModal free routine
//			Jerry 5/04/01	Modify to FormModal free routine
//			Jerry 7/04/01	Add pushButtonCtl drawing
//			Jerry 8/02/01	Prevent to clear over boundary (label control)
//			Jerry 8/09/01	Add draw arrow function in LIST control
//			Jerry	8/16/01	Add checking fldP->attr.underlined attribute
//			Jerry	8/17/01	Modify Field to have multiline function
//			Jerry	8/22/01	Add frmBitmapObj
//			Jerry	8/28/01	Setting field insPtXPos, insPtYPos
//			Jerry	8/31/01	Prevent list box boundary exceed the screen
//			Jerry	9/13/01	Put the string on the center of control
//			Jerry	9/20/01	Add NULL control judgement
//			Jerry	11/04/01	Add visible attribute checking, drawing control
//								if visible bit set.
////////////////////////////////////////////////////////////////////////
void VDrawControl (FormObjectKind type, const void *controlP, int mode)
{
	RectangleType	rect;
	
	if ( !controlP )	return;

	switch (type) {
		case frmBitmapObj:
			{
				FormBitmapType	*bmpP = (FormBitmapType *) controlP;
				int	i;

				for ( i = 0; i < sysBitmapCount; i++ ) {
					if ( bmpP->rscID == sysBitmapPtr[i].ID ) {
						VDrawBitmap (bmpP->pos.x, 
										 bmpP->pos.y, 
										 sysBitmapPtr[i].fileName);
						break;
					}
				}
				break;
			}

		case frmLabelObj:
			{
				FormLabelType	*labelP = (FormLabelType *) controlP;
				int				strWidth;

				Vmemcpy (&(rect.topLeft), &(labelP->pos), sizeof(PointType));
				strWidth = FntCharsWidth (labelP->text, (Int16)Vstrlen(labelP->text));
				rect.extent.y = FntCharHeight();
				rect.extent.x = strWidth;

				VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_PARTSTRETCH, DRAW_SET);
				VDrawString (rect.topLeft.x, rect.topLeft.y, 
								 labelP->text, Vstrlen(labelP->text), 
								 SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
				break;
			}

		case frmListObj:
			LstDrawList ((ListType *)controlP);
			break;

		case frmFieldObj:
			FldDrawField ((FieldType *)controlP);
			break;
			
		case frmControlObj:
			{
				ControlType	*ctlP = (ControlType *) controlP;
				int	width, height, strWidth;

				// calculate string width (put the string on the center of control)
				strWidth = FntCharsWidth (ctlP->text, (Int16)Vstrlen(ctlP->text));
				// calculate the current width and height
				if ( ctlP->bounds.extent.x == -1 ) {
					width = strWidth;
				} else {
					width = ctlP->bounds.extent.x;
				}

				if ( ctlP->bounds.extent.y == -1 ) {
					height = FntCharHeight();
				} else {
					height = ctlP->bounds.extent.y;
				}

				switch (ctlP->style) {
					case buttonCtl:
						Vmemcpy (&(rect), &(ctlP->bounds), sizeof(RectangleType));

						// if auto size, add the string size with CORNERDIM*2
						if ( ctlP->bounds.extent.x == -1 )
							rect.extent.x = width+CORNERDIM/2;
						if ( ctlP->bounds.extent.y == -1 ) 
							rect.extent.y = height+CORNERDIM/2;

						if ( ctlP->attr.enabled )
							VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);

						// draw the text of button control if visible.
						if( ctlP->attr.visible) {
							VDrawString ( (Coord)((VPDAToSysXCoord(rect.topLeft.x)+((VPDAToSysXRes(rect.extent.x)-strWidth)/2))), 
											  (Coord)(VPDAToSysYCoord(rect.topLeft.y)+((VPDAToSysYRes(rect.extent.y)-FntCharHeight())/2)),
											  ctlP->text, 
											  Vstrlen(ctlP->text), 
											  SINGLELINE, CL_FOREGROUND, COORD_NORMAL);

							if ( ctlP->attr.frame ) {
								if ( mode == DRAW_NORMAL )
									VDrawRect (&rect, PS_INSIDEFRAME, CORNERDIM, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
								else
									VDrawRect (&rect, PS_SOLID, CORNERDIM, CL_FOREGROUND, COORD_STRETCH, DRAW_XOR);
							} 

						}
						break;

					case pushButtonCtl:
						Vmemcpy (&(rect), &(ctlP->bounds), sizeof(RectangleType));
						rect.extent.x = (width-1);
						rect.extent.y = (height-1);

						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
						// draw the text of push button control if visible.
						if( ctlP->attr.visible) {
							if ( ctlP->attr.frame ) 
								VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
	
							VDrawString ((Coord)(VPDAToSysXCoord(rect.topLeft.x)+((VPDAToSysXRes(width)-strWidth)/2)), 
											(Coord)(VPDAToSysYCoord(rect.topLeft.y)+((VPDAToSysYRes(rect.extent.y)-FntCharHeight())/2)), 
											ctlP->text, 
											Vstrlen(ctlP->text), 
											SINGLELINE, CL_FOREGROUND, COORD_NORMAL);
						}
						break;

					case labelCtl:
						Vmemcpy (&(rect.topLeft), &(ctlP->bounds.topLeft), sizeof(PointType));
	
						rect.extent.y = FntCharHeight();
						rect.extent.x = strWidth;

						if ( (rect.topLeft.x + rect.extent.x) > PDAWIDTH ) {
							rect.extent.x = PDAWIDTH-rect.topLeft.x-2;
						}
						if( ctlP->attr.visible && ctlP->attr.usable ) {
							VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
							// draw the text of label control if visible.
							VDrawString (rect.topLeft.x, rect.topLeft.y, 
								ctlP->text, Vstrlen(ctlP->text), 
								SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
						}
						break;
				
					case checkboxCtl:
						rect.topLeft.x = ctlP->bounds.topLeft.x;
						rect.topLeft.y = ctlP->bounds.topLeft.y+4;
						rect.extent.x = 7;
						rect.extent.y = 7;

						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
						// draw the text of checkbox control if visible.
						if( ctlP->attr.visible) {
							VDrawRect (&rect, PS_INSIDEFRAME, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
	
							VDrawString ((Coord)(rect.topLeft.x+CheckBoxWidth), 
											(Coord)(rect.topLeft.y-2), 
											ctlP->text, 
											Vstrlen(ctlP->text),
											SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
							VSetCheckBox (controlP, ctlP->attr.on);
						}
						break;

					case popupTriggerCtl:
						VPDAToSysPoint (&(rect.topLeft), &(ctlP->bounds.topLeft));
						if ( (rect.topLeft.x+ArrowWidth+strWidth+5) > VPDAToSysXCoord(PDAWIDTH) )
							rect.topLeft.x = VPDAToSysXCoord(PDAWIDTH)-ArrowWidth-strWidth-5;
						rect.extent.x = (width-1);
						rect.extent.y = (height-1);
						if ( rect.extent.x < (ArrowWidth+strWidth+3) )
							rect.extent.x = ArrowWidth+strWidth+3;

						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_PARTSTRETCH, DRAW_SET);
						// draw the text of popuptrigger control if visible.
						if( ctlP->attr.visible) {
							VDrawDownArrow (VSysToPDAXCoord(rect.topLeft.x), 
												VSysToPDAYCoord((rect.topLeft.y+(FntCharHeight()/2))), 
												SOLID_LARGE);
							VDrawString ((Coord)(rect.topLeft.x+ArrowWidth), 
											(Coord)(rect.topLeft.y+((VPDAToSysYRes(rect.extent.y)-FntCharHeight())/2)), 
											ctlP->text, 
											Vstrlen(ctlP->text), 
											SINGLELINE, CL_FOREGROUND, COORD_NORMAL);
						}
						break;

					case selectorTriggerCtl:
						Vmemcpy (&(rect.topLeft), &(ctlP->bounds.topLeft), sizeof(PointType));
						rect.extent.x = (width-1);
						rect.extent.y = (height-1);

						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
						VDrawRect (&rect, PS_INSIDEFRAME, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

						// draw the text of selector control if visible.
						if( ctlP->attr.visible) {
							VDrawString ((Coord)(VPDAToSysXCoord(rect.topLeft.x)+((VPDAToSysXRes(width)-strWidth)/2)), 
											(Coord)(VPDAToSysYCoord(rect.topLeft.y)+((VPDAToSysYRes(rect.extent.y)-FntCharHeight())/2)), 
											ctlP->text, 
											Vstrlen(ctlP->text), 
											SINGLELINE, CL_FOREGROUND, COORD_NORMAL);
						}
						break;

					case repeatingButtonCtl:
						Vmemcpy (&(rect.topLeft), &(ctlP->bounds.topLeft), sizeof(PointType));
					
						rect.extent.y = (height-1);

						// draw the text of repeatbutton control if visible.
						if( ctlP->attr.visible) {
							if ((Vstrcmp (ctlP->text, "\\001") == 0) || (Vstrcmp (ctlP->text, "\x01") == 0)) {
						rect.extent.x = VPDAToSysXRes (10);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawUpArrow (rect.topLeft.x, rect.topLeft.y, SOLID_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\002") == 0) || (Vstrcmp (ctlP->text, "\x02") == 0)) {
						rect.extent.x = VPDAToSysXRes (10);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawDownArrow (rect.topLeft.x, rect.topLeft.y, SOLID_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\003") == 0) || (Vstrcmp (ctlP->text, "\x03") == 0)) {
						rect.extent.x = VPDAToSysXRes (10);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawUpArrow (rect.topLeft.x, rect.topLeft.y, DASH_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\004") == 0) || (Vstrcmp (ctlP->text, "\x04") == 0)) {
						rect.extent.x = VPDAToSysXRes (10);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawDownArrow (rect.topLeft.x, rect.topLeft.y, DASH_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\005") == 0) || (Vstrcmp (ctlP->text, "\x05") == 0)) {
						rect.extent.x = VPDAToSysXRes (5);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawLeftArrow (rect.topLeft.x, rect.topLeft.y, SOLID_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\006") == 0) || (Vstrcmp (ctlP->text, "\x06") == 0)) {
						rect.extent.x = VPDAToSysXRes (5);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawRightArrow (rect.topLeft.x, rect.topLeft.y, SOLID_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\007") == 0) || (Vstrcmp (ctlP->text, "\x07") == 0)) {
						rect.extent.x = VPDAToSysXRes (5);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawLeftArrow (rect.topLeft.x, rect.topLeft.y, DASH_LARGE);
							} else if ((Vstrcmp (ctlP->text, "\\008") == 0) || (Vstrcmp (ctlP->text, "\x08") == 0)) {
						rect.extent.x = VPDAToSysXRes (5);
						VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
								VDrawRightArrow (rect.topLeft.x, rect.topLeft.y, DASH_LARGE);
							}
						}
						break;
				}
			}
			break;

		case frmScrollBarObj:
			SclDrawScrollBar ((ScrollBarType *) controlP);
			break;

		case frmTableObj:
			TblDrawTable ((TableType *)controlP);
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VRedrawControl
//
// DESCRIPTION: This routine redraw the control
//
// PARAMETERS:  (ControlModal) control - Pointer to the ControlModal
//								 structure
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/13/01		Initial Revision
//			Jerry	3/19/01		Update VRect structure
////////////////////////////////////////////////////////////////////////
void VRedrawControl (const FormObjListType controlP)
{
	VDrawControl (controlP.objectType, controlP.object.ptr, DRAW_NORMAL);
}

void VDrawNoteMark (Coord x, Coord y)
{
	x = VPDAToSysXCoord (x);
	y = VPDAToSysYCoord (y);
	VDrawLine (x, 
			   y, 
			   (Coord)(x+5), 
			   y, 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);
	VDrawLine ((Coord)(x+5), 
			   y, 
			   (Coord)(x+5), 
			   (Coord)(y+5), 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);
	VDrawLine ((Coord)(x+5), 
			   (Coord)(y+5), 
			   (Coord)(x+3), 
			   (Coord)(y+7), 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);
	VDrawLine ((Coord)(x+3), 
			   (Coord)(y+7), 
			   x, 
			   (Coord)(y+7), 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);
	VDrawLine (x, 
			   (Coord)(y+7), 
			   x, 
			   y, 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);

	VDrawLine ((Coord)(x+5), 
			   (Coord)(y+5), 
			   (Coord)(x+3), 
			   (Coord)(y+5), 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);
	VDrawLine ((Coord)(x+3), 
			   (Coord)(y+5), 
			   (Coord)(x+3), 
			   (Coord)(y+7), 
				THIN_LINE, 
				FOREGROUNDCOLOR, 
			   PS_SOLID);

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawTable
//
// DESCRIPTION: This routine draw a table.
//
// PARAMETERS:  (UInt16) x - The x coordinate of left top point
//					 (UInt16) y - The y coordinate of left top point
//					 (TableItemPtr) item - The table item to be drawn
//					 (Coord) width - The width of current field of table
//					 (Coord) height - The height of current field of table
//
// RETURNED:    nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/1/01	Initial Revision
//			Jerry 8/08/01	Modify to drawn in the correct coordinate
////////////////////////////////////////////////////////////////////////
void VDrawTable ( UInt16 x, UInt16 y, TableItemPtr item, Coord width, Coord height)
{
	RectangleType	rect;

	switch (item->itemType) {
		case checkboxTableItem:
			{
			Char	word[3];

			rect.topLeft.x = x;
			rect.topLeft.y = (y+4);
			rect.extent.x = 5;
			rect.extent.y = 5;

			VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

			StrIToA (word, item->intValue);
			VDrawString ((Coord)(rect.topLeft.x+10), 
				(Coord)(rect.topLeft.y-2), word, Vstrlen(word), 
				SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
			break;
			}
		case customTableItem:
		case dateTableItem:
		case labelTableItem:
		case numericTableItem:
		case popupTriggerTableItem:
		case textTableItem:
			rect.topLeft.x = x;
			rect.topLeft.y = y;
			rect.extent.x = width;
			rect.extent.y = height;

			VDrawLine (rect.topLeft.x, (Coord)(rect.topLeft.y+rect.extent.y-1), 
					   (Coord)(rect.topLeft.x+rect.extent.x-1), 
						(Coord)(rect.topLeft.y+rect.extent.y-1), 
						THIN_LINE, FOREGROUNDCOLOR, PS_DOT);
			break;
		case textWithNoteTableItem:
			rect.topLeft.x = x;
			rect.topLeft.y = y;
			rect.extent.x = width-8;
			rect.extent.y = height;

			VDrawLine (rect.topLeft.x, (Coord)(rect.topLeft.y+rect.extent.y-1), 
					   (Coord)(rect.topLeft.x+rect.extent.x-1), 
						(Coord)(rect.topLeft.y+rect.extent.y-1), 
						THIN_LINE, FOREGROUNDCOLOR, PS_DOT);
			// Here Must modify
			VDrawString (rect.topLeft.x, rect.topLeft.y, item->ptr, Vstrlen(item->ptr), 
				SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
			VDrawNoteMark ((Coord)(rect.extent.x+2), (Coord)(rect.topLeft.y+2));
			break;
		case timeTableItem:
		case narrowTextTableItem:
		default:
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CheckControlEvent
//
// DESCRIPTION: This routine check which control have been tapped.
//
// PARAMETERS:  (Int16) id - The id of control beeen tapped.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/13/01	Initial Revision
//			Jerry	11/29/01	Setting ActiveForm->focus
////////////////////////////////////////////////////////////////////////
void CheckControlEvent (Int16 id)
{
	if ( !ActiveForm || MenuActive )	return;

	CurEvent->data.ctlEnter.controlID = id;

	if ( ActiveObjIndex != -1 ) {
		// set the focus of form to activeobject
		ActiveForm->focus = ActiveObjIndex;
		switch (ActiveForm->objects[ActiveObjIndex].objectType) {
			case frmFieldObj:
				CurEvent->eType = fldEnterEvent;
				CurEvent->data.fldEnter.fieldID = id;
				CurEvent->data.fldEnter.pField = ActiveForm->objects[ActiveObjIndex].object.field;
				ActiveForm->objects[ActiveObjIndex].object.field->attr.hasFocus = true;
				break;

			case frmListObj:
				CurEvent->eType = lstSelectEvent;
				CurEvent->data.lstSelect.listID = id;
				CurEvent->data.lstSelect.pList = ActiveForm->objects[ActiveObjIndex].object.list;
				CurEvent->data.lstSelect.selection = LstCheckListHit (CurEvent->data.lstSelect.pList, CurEvent->screenX, CurEvent->screenY);
				ActiveForm->objects[ActiveObjIndex].object.list->currentItem = CurEvent->data.lstSelect.selection;
				VRedrawControl (ActiveForm->objects[ActiveObjIndex]);
				break;

			case frmControlObj:
				if( ActiveForm->objects[ActiveObjIndex].object.control->attr.enabled ) {
				switch (ActiveForm->objects[ActiveObjIndex].object.control->style ) {
					case repeatingButtonCtl:
						CurEvent->eType = ctlRepeatEvent;
						CurEvent->data.ctlRepeat.controlID = id;
						break;

					case buttonCtl:
						CurEvent->eType = ctlSelectEvent;
						CurEvent->data.ctlSelect.controlID = id;
						break;
/*												
					case popupTriggerCtl:
						CurEvent->eType = popSelectEvent;
						CurEvent->data.ctlEnter.controlID = id;
						break;
*/		
					default:
						CurEvent->eType = ctlSelectEvent;
						CurEvent->data.ctlSelect.controlID = id;
						break;
				}
				}
				break;

			case frmTableObj:
				// Place current selectd row & column 
				// from event->screenX & event->screenY
				{
					TableType	*tblP = ActiveForm->objects[ActiveObjIndex].object.table;
					UInt		rowHeight=tblP->bounds.extent.y/tblP->numRows;
					UInt		ix;
					UInt		offset=0;
					UInt		sx = CurEvent->screenX;

//					CurEvent->data.tblEnter.pTable = (TableType *)tblP;
					CurEvent->data.tblEnter.row = (CurEvent->screenY-tblP->bounds.topLeft.y)/rowHeight;
					for ( ix = 0; ix < tblP->numColumns; ix++) {
						if ( (sx >= tblP->bounds.topLeft.x+offset) && 
							(sx <= (tblP->bounds.topLeft.x+offset+tblP->columnAttrs[ix].width))) {
							break;
						}
						offset += tblP->columnAttrs[ix].width;
					}
					CurEvent->data.tblEnter.column = ix;
					CurEvent->eType = tblEnterEvent;
					break;
				}

			case frmScrollBarObj:
				{
					ScrollBarType	*barP = ActiveForm->objects[ActiveObjIndex].object.scrollBar;
					UInt16	newValue;

					newValue = (CurEvent->screenY-barP->bounds.topLeft.y)*(barP->maxValue+barP->pageSize)/barP->bounds.extent.y;
					if ( newValue > barP->maxValue )
						newValue = barP->maxValue;
					CurEvent->data.sclExit.value = barP->value;
					CurEvent->data.sclExit.newValue = newValue;
					CurEvent->eType = sclRepeatEvent;
					break;
				}

			default:
//				CurEvent->eType = ctlSelectEvent;
//				CurEvent->data.ctlSelect.controlID = id;
				break;
		}	// end of switch
	}

	WPushEvent (CurEvent);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WFieldSelPos
//
// DESCRIPTION: This routine check the position 
//
// PARAMETERS:  (Int16) id - The id of control beeen tapped.
//					 (int) mode - 1 if clock on, 0 if leave
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 WFieldSelPos (Coord x, Coord y, FieldType *fldP)
{
	Int16		i, charWidth, line=-1, strWidth=0, strLen=0;
	RectangleType	rect;

	Vmemcpy (&rect, &(fldP->rect), sizeof(RectangleType));
	rect.topLeft.x = VPDAToSysXCoord(rect.topLeft.x);
	rect.extent.x = VPDAToSysXRes(rect.extent.x);
	x = VPDAToSysXCoord (x);
	//	check is point on texture area
	if ( (y > rect.topLeft.y) && ( y < (rect.topLeft.y+(fldP->reserved-fldP->firstLine)*FntLineHeight()))) {
		line = ((y-rect.topLeft.y)/FntLineHeight())+fldP->firstLine;
		if ( line >= fldP->reserved )
			return	0xFFFF;
		strLen = (fldP->lines[line].start+fldP->lines[line].length);
		if ( fldP->attr.justification == rightAlign ) {
		} else {
			if ( (x > rect.topLeft.x) && (x < (rect.topLeft.x+rect.extent.x)) ) {
				for ( i = fldP->lines[line].start; i < strLen; i++ ) {
					charWidth = FntCharWidth(fldP->text[i]);
					if ( x < (rect.topLeft.x+strWidth+charWidth) ) {
						if ( x < (rect.topLeft.x+strWidth+(charWidth/2)) )
							return	i;
						else
							return	i+1;
					}
					strWidth += charWidth;
				}
			}
		}
	}

	if ( (line != -1) && (strLen > 0) ) {
		if ( fldP->text[strLen-1] == 0x0a ) 
			return	fldP->lines[line].start+fldP->lines[line].length-1;
		else
			return	fldP->lines[line].start+fldP->lines[line].length;
	} else
		return	0xFFFF;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WGetFieldTextCoord
//
// DESCRIPTION: This routine check the position 
//
// PARAMETERS:  (Int16) id - The id of control beeen tapped.
//					 (int) mode - 1 if clock on, 0 if leave
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WGetFieldTextCoord (FieldType *fldP, UInt16 textPos, Coord *x, Coord *y, UInt16 *line)
{
	Int16		i, strWidth;

	if ( !fldP )
		return;
	for ( i = 0; i < fldP->reserved; i++ ) {
		if ( (textPos >= fldP->lines[i].start) && 
				(textPos < (fldP->lines[i].start+fldP->lines[i].length)) )
				break;
	}

	if ( i >= fldP->reserved )
		i = fldP->reserved-1;
	*line = i;
	//	check is point on texture area
	if ( fldP->attr.justification == rightAlign ) {
	} else {
		if ( textPos == 0xFFFF )
			textPos = fldP->lines[i].length;
		if ( fldP->text ) {
			strWidth = FntCharsWidth (&(fldP->text[fldP->lines[i].start]), 
											(short)(textPos-fldP->lines[i].start));
			*y = VPDAToSysYCoord((fldP->rect.topLeft.y+i*FntLineHeight()+2));
			*x = VPDAToSysXCoord(fldP->rect.topLeft.x) + strWidth;
		} else {
			*x = VPDAToSysXCoord (fldP->rect.topLeft.x);
			*y = VPDAToSysYCoord (fldP->rect.topLeft.y);
		}
	}
}

void WDrawStartUpScreen ()
{
	// draw startup bitmap
	Int16		strWidth;
	WClearScreen (SCREEN_ALL);

	// draw system control area box
	drawline (SysPanelStartX,SysPanelStartY,SysPanelEndX,SysPanelStartY);
	drawline (SysPanelStartX,SysPanelEndY,SysPanelEndX,SysPanelEndY);
	drawline (SysPanelStartX,SysPanelStartY,SysPanelStartX,SysPanelEndY);
	drawline (SysPanelEndX,SysPanelStartY,SysPanelEndX,SysPanelEndY);

	// draw the system panel split line
	drawline (SysPanelVLine1, SysPanelStartY, SysPanelVLine1, SysPanelEndY);
	drawline (SysPanelVLine2, SysPanelStartY, SysPanelVLine2, SysPanelEndY);

	// draw Application button
	strWidth = FntCharsWidth ("StartUp", (short)Vstrlen("StartUp"));
	VDrawChars ("StartUp", (short)Vstrlen("StartUp"), 
				(short)(SysPanelStartX+(((SysPanelVLine1-SysPanelStartX)-strWidth)/2)),
				(short)(SysPanelStartY+(((SysPanelHLine1-SysPanelStartY)-FntCharHeight())/2)),
				COORD_NORMAL);
	drawline (SysPanelStartX, SysPanelHLine1, SysPanelVLine1, SysPanelHLine1);

	// draw Menu button
	strWidth = FntCharsWidth ("Menu", (short)Vstrlen("Menu"));
	VDrawChars ("Menu", (short)Vstrlen("Menu"), 
				(short)(SysPanelStartX+(((SysPanelVLine1-SysPanelStartX)-strWidth)/2)),
				(short)(SysPanelHLine1+(((SysPanelHLine2-SysPanelHLine1)-FntCharHeight())/2)),
				COORD_NORMAL);
	drawline (SysPanelStartX, SysPanelHLine2, SysPanelVLine1, SysPanelHLine2);

	// draw Exit button
	strWidth = FntCharsWidth ("Exit", (short)Vstrlen("Exit"));
	VDrawChars ("Exit", (short)Vstrlen("Exit"), 
				(short)(SysPanelStartX+(((SysPanelVLine1-SysPanelStartX)-strWidth)/2)),
				(short)(SysPanelHLine2+(((SysPanelEndY-SysPanelHLine2)-FntCharHeight())/2)),
				COORD_NORMAL);

	// draw ??? button
	drawline (SysPanelVLine2, SysPanelHLine1, SysPanelEndX, SysPanelHLine1);

	// draw ??? button
	drawline (SysPanelVLine2, SysPanelHLine2, SysPanelEndX, SysPanelHLine2);

	// draw HandWriting split line
	drawline (HandWritingX2, HandWritingY1, HandWritingX2, HandWritingY2);
}

void WDrawFieldString (FieldType *fldP, UInt16 selfirst, UInt16 sellast, Boolean Background)
{
	RectangleType	rect;
	Coord		x, y;
	UInt16	startLine, endLine;
	UInt16	sFirst, sLast, i;

	WGetFieldTextCoord (fldP, selfirst, &x, &y, &startLine);
	rect.topLeft.x = x;
	rect.topLeft.y = y;
	WGetFieldTextCoord (fldP, (UInt16)(sellast), &x, &y, &endLine);
	rect.extent.x = (x-rect.topLeft.x-1);
	rect.extent.y = (y-rect.topLeft.y+FntLineHeight());

	if ( startLine != endLine ) {
		// select multiple line
		sFirst = selfirst;
		for ( i = startLine; i <= endLine; i++ ) {
			if ( i != endLine )
				sLast = fldP->lines[i].start+fldP->lines[i].length-1;
			else 
				sLast = sellast;
			WGetFieldTextCoord (fldP, sFirst, &x, &y, &startLine);
			rect.topLeft.x = x;
			rect.topLeft.y = y;
			WGetFieldTextCoord (fldP, (UInt16)(sLast), &x, &y, &startLine);
			rect.extent.x = (x-rect.topLeft.x);
			rect.extent.y = (y-rect.topLeft.y+FntLineHeight());
			VDrawRect (&rect, PS_SOLID, 0, (Boolean)(!Background), COORD_NORMAL, DRAW_SET);
			VDrawString (rect.topLeft.x, rect.topLeft.y, 
							&(fldP->text[sFirst]), 
							(sLast-sFirst),
							SINGLELINE, Background, COORD_NORMAL);

			if ( i+1 < fldP->reserved )
				sFirst = fldP->lines[i+1].start;
		}
	} else {
		// select single line
		VDrawRect (&rect, PS_SOLID, 0, (Boolean)(!Background), COORD_NORMAL, DRAW_SET);

		VDrawString (rect.topLeft.x, rect.topLeft.y, 
						&(fldP->text[selfirst]), 
						(sellast-selfirst),
						SINGLELINE, Background, COORD_NORMAL);

	}
//	sysSelFirst = selfirst;
//	sysSelLast = sellast;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WClickOnControl
//
// DESCRIPTION: This routine draw the control in properly mode when 
//					 click on control.
//
// PARAMETERS:  (Int16) id - The id of control beeen tapped.
//					 (int) mode - 1 if clock on, 0 if leave
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WClickOnControl (Coord x, Coord y, int mode)
{
	if ( MenuActive )
		return;

	if ( mode == MOUSE_DOWN )
		HitCtlIndex = ActiveObjIndex;

	if ( HitCtlIndex != -1 ) {
		switch (ActiveForm->objects[HitCtlIndex].objectType) {
			case frmFieldObj:
				{	
					FieldType	*fldP = ActiveForm->objects[HitCtlIndex].object.field;
					UInt16	selFPos, selLPos=0xFFFF;

					if ( mode == MOUSE_DOWN ) {
						selFPos = WFieldSelPos (x, y, fldP);
						if ( (fldP->selFirstPos != 0xFFFF) && (fldP->selLastPos != 0xFFFF) ) {
							// clear selection text
							if ( fldP->selFirstPos > fldP->selLastPos ) {
								WDrawFieldString (fldP, fldP->selLastPos, fldP->selFirstPos, CL_FOREGROUND);
							} else {
								WDrawFieldString (fldP, fldP->selFirstPos, fldP->selLastPos, CL_FOREGROUND);
							}
						}
						fldP->selFirstPos = selFPos;
						fldP->selLastPos = 0xFFFF;
					} else if ( (mode == MOUSE_MOVE) && (fldP->selFirstPos != 0xFFFF) )
						selLPos = WFieldSelPos (x, y, fldP);

						// if select characters, invert the string
					if ( (fldP->selFirstPos != selLPos) &&
							(fldP->selFirstPos != 0xFFFF) && 
							(selLPos != 0xFFFF) ) {
						//	if previous select texts, clear if select less than previous
						if ( fldP->selLastPos != 0xFFFF ) {
							if ( (fldP->selFirstPos > fldP->selLastPos) && (selLPos > fldP->selLastPos) ) {
								WDrawFieldString (fldP, fldP->selLastPos, selLPos, CL_FOREGROUND);
							} else if ( selLPos < fldP->selLastPos ) {
								WDrawFieldString (fldP, selLPos, fldP->selLastPos, CL_FOREGROUND);
							}
						}

						fldP->selLastPos = selLPos;
						if ( fldP->selFirstPos > fldP->selLastPos ) {
							WDrawFieldString (fldP, fldP->selLastPos, fldP->selFirstPos, CL_BACKGROUND);
						} else {
							WDrawFieldString (fldP, fldP->selFirstPos, fldP->selLastPos, CL_BACKGROUND);
						}
					} else if ( (fldP->selFirstPos == fldP->selLastPos) && 
								(fldP->selFirstPos == selLPos) ) {
						if ( (fldP->selFirstPos != fldP->selLastPos) && 
							(fldP->selFirstPos!=0xFFFF) && (fldP->selLastPos!=0xFFFF) ) {
							// clear selection text
							if ( fldP->selFirstPos > fldP->selLastPos ) {
								WDrawFieldString (fldP, fldP->selLastPos, fldP->selFirstPos, CL_FOREGROUND);
							} else {
								WDrawFieldString (fldP, fldP->selFirstPos, fldP->selLastPos, CL_FOREGROUND);
							}
						}
						fldP->selLastPos = 0xFFFF;
					}

					break;
				}

			case frmListObj:
				break;

			case frmControlObj:
				{
				ControlType	*ctlP = ActiveForm->objects[HitCtlIndex].object.control;
				switch (ActiveForm->objects[HitCtlIndex].object.control->style) {
					case repeatingButtonCtl:
						break;

					case buttonCtl:
						{
							if ( ctlP->attr.usable ) {
								if ( mode==MOUSE_DOWN )
									VDrawControl (frmControlObj, ctlP, DRAW_INVERT);
								else if ( (mode==MOUSE_UP )|| ((mode==MOUSE_MOVE) && (ActiveObjIndex != HitCtlIndex)) )
									VDrawControl (frmControlObj, ctlP, DRAW_NORMAL);
							}
						}
						break;
												
					case popupTriggerCtl:
						break;
		
					default:
						break;
				}
				break;
				}

			case frmTableObj:
				// Place current selectd row & column 
				// from event->screenX & event->screenY
				break;

			case frmScrollBarObj:
				break;

			default:
				break;
		}	// end of switch
	}

	if ( mode == MOUSE_UP ) {
		if (ActiveForm && (HitCtlIndex != -1) &&
			(ActiveForm->objects[HitCtlIndex].objectType==frmFieldObj) &&
			(ActiveForm->objects[HitCtlIndex].object.field->selLastPos == 0xFFFF)) {
			FieldType	*fldP = ActiveForm->objects[HitCtlIndex].object.field;
			UInt16	selPos;

			fldP->selFirstPos = 0xFFFF;
			selPos = WFieldSelPos (x, y, fldP);
			if ( selPos == 0xFFFF )
				FldSetInsertionPoint (fldP, fldP->textLen);
			else
				FldSetInsertionPoint (fldP, selPos);
		}
		HitCtlIndex = -1;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CheckInBoundary (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check is the current mouse click on the
//				menu button.
//
// PARAMETERS:  (const RectangleType *) rect - Pointer to RectangleType
//					 (UInt16) x - the current mouse click coordinate
//              (UInt16) y - the current mouse click coordinate
//
// RETURNED:    true if click on the rectangle region, false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/09/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean CheckInBoundary(const RectangleType *rect, UInt16 x, UInt16 y)
{
	UInt16	MinX, MinY, MaxX, MaxY;

	MinX = rect->topLeft.x;
	MinY = rect->topLeft.y;

	if ( rect->extent.x == 0 ) {
		MaxX = PDAWIDTH;
	} else {
		MaxX = rect->topLeft.x+rect->extent.x;
	}

	if ( rect->extent.y == -1 ) {
		MaxY = rect->topLeft.y+FntLineHeight();
	} else {
		MaxY = rect->topLeft.y+rect->extent.y;
	}

	if ( (x>=MinX) && (x<MaxX) && (y>=MinY) && (y<MaxY) ) {
		return	TRUE;
	} else {
		return	FALSE;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CheckHitOnControl (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check which control is hitten by pen
//
// PARAMETERS:  (UInt16) x - The x coordinate which pen hit.
//              (UInt16) y - The y coordinate which pen hit.
//
// RETURNED:    Returns the Control Id hitten by pen
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	8/09/01	Add frmListObj type
//			Jerry	9/03/01	If width or height is AUTO, recalculate it
//			Jerry	11/29/01	Setting ActiveForm->focus
////////////////////////////////////////////////////////////////////////
Int16 CheckHitOnControl(UInt16 x, UInt16 y)
{
	UInt16	i;
	Int16		lastActiveObjIndex = ActiveObjIndex, id = -1;

	if ( MenuActive || (VPDAToSysYCoord(y) > SysPanelStartY) )	return	-1;

	ActiveObjIndex = -1;

	if ( (formCount == 0) || (ActiveForm == NULL) )
		return	ActiveObjIndex;

	for ( i = 0; i < ActiveForm->numObjects; i++ ) {
		switch ( ActiveForm->objects[i].objectType ) {
			case frmFieldObj:
				if ( ActiveForm->objects[i].object.field->attr.usable &&
					CheckInBoundary (&(ActiveForm->objects[i].object.field->rect), x, y) ) {
					ActiveForm->objects[i].object.field->attr.hasFocus = true;
					ActiveObjIndex = i;

					id = ActiveForm->objects[i].object.field->id;
				}
				break;

			case frmControlObj:
				{
					RectangleType	rect;
					int		strWidth;
					ControlType	*ctlP = ActiveForm->objects[i].object.control;

					// size is AUTO, recalculate it
					Vmemcpy (&rect, &(ActiveForm->objects[i].object.control->bounds), sizeof(RectangleType));
					if ( rect.extent.x == -1 ) {
						strWidth = FntCharsWidth (ctlP->text, (Int16) Vstrlen(ctlP->text));
						rect.extent.x = strWidth;
						if ( ActiveForm->objects[i].object.control->style == popupTriggerCtl ) 
							rect.extent.x += ArrowWidth;
					}
					if ( rect.extent.y == -1 ) 
						rect.extent.y = FntCharHeight();

					// check box size is hardcode now, must modify later.
					if ( ctlP->style == checkboxCtl ) {
						rect.extent.x = 7;
						rect.extent.y = 7;
					}
					// if hit on control rectangle boundary, return object index
					if ( CheckInBoundary (&rect, x, y) ) {
						ActiveObjIndex = i;

						id = ctlP->id;
					}
				}
				break;

			case frmListObj:
				if ( ActiveForm->objects[i].object.list->attr.usable &&
						CheckInBoundary (&(ActiveForm->objects[i].object.list->bounds), x, y) ) {
					ActiveObjIndex = i;

					id = ActiveForm->objects[i].object.list->id;
				}
				break;

			case frmTableObj:
				if ( CheckInBoundary (&(ActiveForm->objects[i].object.table->bounds), x, y) ) {
					ActiveObjIndex = i;

					id = ActiveForm->objects[i].object.table->id;
				}
				break;

			case frmScrollBarObj:
				if ( CheckInBoundary (&(ActiveForm->objects[i].object.scrollBar->bounds), x, y) ) {
					ActiveObjIndex = i;

					id = ActiveForm->objects[i].object.scrollBar->id;
				}
				break;

		}
	}

	// check if active object is not the same as last, disable the action on last one
	if ( (lastActiveObjIndex != -1) && ActiveForm && (lastActiveObjIndex != ActiveObjIndex) ) {
		if ( ActiveForm->objects[lastActiveObjIndex].objectType == frmFieldObj ) {
			FieldType	*fldP = ActiveForm->objects[lastActiveObjIndex].object.field;
		
			// clear the cursor and graffiti state
			fldP->attr.hasFocus = false;
			if ( fldP->attr.editable ) {
				VDrawCursor ( (Coord)(fldP->insPtXPos), (Coord)(fldP->insPtYPos+2),
									CUR_CLEAR);
				if (!((ActiveObjIndex != -1)&&(ActiveForm->objects[ActiveObjIndex].objectType==frmFieldObj)))
					VDrawGrafState (FALSE);
			}
			// if select text, unselect it
			if ( (fldP->selFirstPos != fldP->selLastPos) &&
					(fldP->selFirstPos != 0xFFFF) && 
					(fldP->selLastPos != 0xFFFF) ) {
				//	if previous select texts, clear if select less than previous
				if ( fldP->selFirstPos > fldP->selLastPos ) {
					WDrawFieldString (fldP, fldP->selLastPos, fldP->selFirstPos, CL_FOREGROUND);
				} else {
					WDrawFieldString (fldP, fldP->selFirstPos, fldP->selLastPos, CL_FOREGROUND);
				}
			}
		} else if ( ActiveForm->objects[lastActiveObjIndex].objectType == frmControlObj ) {
			ControlType	*ctlP = ActiveForm->objects[lastActiveObjIndex].object.control;

			if ( ctlP->style == buttonCtl ) {
				VDrawControl (frmControlObj, ctlP, DRAW_NORMAL);
			}

		}
	}

	return	id;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ChechHitSystemButton (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check which control is hitten by pen
//
// PARAMETERS:  (UInt16) x - The x coordinate which pen hit.
//              (UInt16) y - The y coordinate which pen hit.
//
// RETURNED:    Returns the Control Id hitten by pen
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision
//			Jerry 5/04/01	Modify to FormType structure
//			Jerry	8/09/01	Add frmListObj type
//			Jerry	9/03/01	If width or height is AUTO, recalculate it
////////////////////////////////////////////////////////////////////////
Int16 CheckHitSystemButton(UInt16 x, UInt16 y)
{
	if ( y > SysPanelStartY ) {
		// Hit on system button area
		if ( x < SysPanelVLine1 ) {
			if ( y < SysPanelHLine1 ) {
				return	SysButton1;
			} else if ( y < SysPanelHLine2 ) {
				return	SysButton2;
			} else {
				return	SysButton3;
			}
		} else if ( x > SysPanelVLine2 ) {
			if ( y < SysPanelHLine1 ) {
				return	SysButton4;
			} else if ( y < SysPanelHLine2 ) {
				return	SysButton5;
			} else {
				return	SysButton6;
			}
		}
	}

	return	-1;
}

void WPeekMouseEvent (Boolean penDown)
{
	Int16	id;
	RectangleType	PDARect;

	RctSetRectangle (&PDARect, SCREENXBASE, SCREENYBASE, 
							SCREENWIDTH, SCREENHEIGHT);
	// push event to event queue
	if ( penDown ) {
		if ( CurEvent->penDown ) {	// pen Move Event
			CurEvent->eType = penMoveEvent;

			if ( HandWritingStart ) {
				hwAddPoint (CurEvent->screenX, CurEvent->screenY);	// Add point into point list.
			} else {
				WPushEvent (CurEvent);
				id = CheckHitOnControl (CurEvent->screenX, CurEvent->screenY);
				// Mouse move to different control, redraw control
				if ( id != -1 ) 
					WClickOnControl (CurEvent->screenX, CurEvent->screenY, MOUSE_MOVE);
			}
		} else {	// Pen Down Event
			RectangleType	handrect;

			CurEvent->eType = penDownEvent;
			CurEvent->penDown = true;

			RctSetRectangle (&handrect, HandWritingX1, HandWritingY1, 
									HandWritingX3-HandWritingX1, 
									HandWritingY2-HandWritingY1);
			if ( !HandWritingStart && RctPtInRectangle (VPDAToSysXCoord(CurEvent->screenX), 
						VPDAToSysYCoord(CurEvent->screenY), &handrect) ) {
				HandWritingStart = true;
				if ( grfInputState == grfNONE ) {
					if ( VPDAToSysXCoord(CurEvent->screenX) < HandWritingX2 ) {
						grfInputState = grfLETTERS;
					} else {
						grfInputState = grfDIGITS;
					}
				}
				hwAddPoint (CurEvent->screenX, CurEvent->screenY);	// Add point into point list.
			} else if ( RctPtInRectangle (VPDAToSysXCoord(CurEvent->screenX), 
						VPDAToSysYCoord(CurEvent->screenY), &PDARect) ) {
				WPushEvent (CurEvent);
				// click on control, invert this control
				PenDownID = CheckHitOnControl (CurEvent->screenX, CurEvent->screenY);
				// Mouse click on control
				if ( PenDownID != -1 ) {
					WClickOnControl (CurEvent->screenX, CurEvent->screenY, MOUSE_DOWN);
				}	
			}
		}
	} else {
		// check if click on any control, redraw it
		WClickOnControl (CurEvent->screenX, CurEvent->screenY, MOUSE_UP);
		CurEvent->penDown = false;
		CurEvent->eType = penUpEvent;

		// end handwriting, recognize the pen writing tracking
		if ( HandWritingStart ) {
			hwAddPoint (CurEvent->screenX, CurEvent->screenY);	// Add point into point list.
			if ( grfInputState != grfNONE ) {
				Char	ch;
				ch = hwRecognizeStart (grfInputState);
				if ( ch ) {
					if ( (ch == TAP_CHAR) && (grfInputState != grfPUNC) ) {
						grfInputState = grfPUNC;
						grfState.sysTempShift = 9;
					} else if ( ch == ASCII_TEMPCAPS ) {
						grfState.sysTempShift = 1;
					} else {
						if ( grfState.sysTempShift == 1 ) {
							if ( (grfInputState == grfLETTERS) && (ch >= 'a') &&
								(ch <= 'z') )
								ch = (char)(ch-'a'+'A');
							grfState.sysTempShift = 0;
						} else if ( grfState.sysTempShift != 2 )
							grfState.sysTempShift = 0;
						CurEvent->eType = keyDownEvent;

						CurEvent->data.keyDown.chr = (WChar) ch;
						CurEvent->data.keyDown.keyCode = (WChar) ch;
						WPushEvent (CurEvent);
						grfInputState = grfNONE;
					}
				} else {
					grfInputState = grfNONE;
				}
			}
			// handwriting end, disable flag
			HandWritingStart = false;
		} else if ( (id=CheckHitSystemButton (VPDAToSysXCoord(CurEvent->screenX), 
					VPDAToSysYCoord(CurEvent->screenY))) > 0 ) {
			// Hit on system button area
			switch (id) {
				case SysButton1:
					CurEvent->eType = appStopEvent;
					WPushEvent (CurEvent);
					break;
				case SysButton2:
					CurEvent->eType = menuOpenEvent;
					WPushEvent (CurEvent);
					break;
				case SysButton3:
					CurEvent->eType = appStopEvent;
					WPushEvent (CurEvent);
					CurEvent->eType = sysExitEvent;
					WPushEvent (CurEvent);
					break;
				case SysButton4:
					break;
				case SysButton5:
					break;
				case SysButton6:
					break;
			}
		} else {
			// check which control been tapped 
			// check if tap on the control, rise a control relative event
			WPushEvent (CurEvent);
			id = CheckHitOnControl (CurEvent->screenX, CurEvent->screenY);
			// Mouse click on control
			if ( id != -1 && (id == PenDownID) ) {
				CheckControlEvent (id);
			}	// end of check hit id
		}
	}	// end of if (penDown)
}