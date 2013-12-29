/*========================================================
  Window.c
  all routine is running with Platform non-related,
  simulated the Window function in Palm OS.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0208, 2001 by Jerry Chu
					 0525, 2001 by Jerry Chu, add 6 insertion
									point routines and 2 pen manager
									routines.
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


InsPtStateType		insPtState;
PenCalibrateType	penCalibrate;
DrawStateType		curDrawState;
DrawStateType		storedDrawState;


RectangleType		clipRect;
IndexedColorType	foregroundColor=255, backgroundColor=0;

// Below is insertion point relative function
////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtEnable
//
// DESCRIPTION: This routine enable or disable the insertion point. When
//					 the insertion point is disabled, it's invisible; when
//					 it's enabled, it blinks.
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
void InsPtEnable (Boolean enableIt)
{
	insPtState.enabled = enableIt;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtEnabled
//
// DESCRIPTION: This routine return true if the insertion point is 
//					 enabled or false if the insertion point is disabled.
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
Boolean InsPtEnabled (void)
{
	return	insPtState.enabled;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtGetHeight
//
// DESCRIPTION: This routine return the height of the insertion point.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the height of the insertion point, in pixels.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 InsPtGetHeight (void)
{
	return	insPtState.height;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtGetLocation
//
// DESCRIPTION: This routine return the screen-relative position of the
//					 insertion point.
//
// PARAMETERS:  (Int16 *) x, y - Pointer to top-left position of insertion
//											point's x and y coordinate.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void InsPtGetLocation (Int16 *x, Int16 *y)
{
	*x = insPtState.pos.x;
	*y = insPtState.pos.y;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtSetHeight
//
// DESCRIPTION: This routine set the height of the insertion point.
//
// PARAMETERS:  (const Int16) height - Height of the insertion point in
//													pixel.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void InsPtSetHeight (const Int16 height)
{
	insPtState.height = height;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InsPtSetLocation
//
// DESCRIPTION: This routine set the screen-relative position of the
//					 insertion point.
//
// PARAMETERS:  (const Int16) x, y - Number of pixels from the left side
//												(top) of the display.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void InsPtSetLocation (const Int16 x, const Int16 y)
{
	insPtState.pos.x = x;
	insPtState.pos.y = y;
}



// Below is windows relative function

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PenCalibrate
//
// DESCRIPTION: This routine set the calibration of the pen.
//
// PARAMETERS:  (PointType *) digTopLeftP - Digitizer output from 
//											top-left coordinate.
//					 (PointType *) digBotRightP - Digitizer output from 
//											bottom-right coordinate.
//					 (PointType *) scrTopLeftP - Screen coordinate near 
//											top-left coordinate.
//					 (PointType *) scrBotRightP - Screen coordinate near 
//											bottom-right coordinate.
//
// RETURNED:    Returns 0 if no error..
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err PenCalibrate (PointType *digTopLeftP, PointType *digBotRightP,
						PointType *scrTopLeftP, PointType *scrBotRightP)
{
	Vmemcpy ( &(penCalibrate.digTopLeftP), digTopLeftP, sizeof(PointType));
	Vmemcpy ( &(penCalibrate.digBotRightP), digBotRightP, sizeof(PointType));
	Vmemcpy ( &(penCalibrate.scrTopLeftP), scrTopLeftP, sizeof(PointType));
	Vmemcpy ( &(penCalibrate.scrBotRightP), scrBotRightP, sizeof(PointType));

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    PenResetCalibrate
//
// DESCRIPTION: This routine reset the calibration in preparation for 
//					 calibrating the pen again.
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
Err PenResetCalibrate (void)
{
	penCalibrate.digTopLeftP.x = PDASTARTX;
	penCalibrate.digTopLeftP.y = PDASTARTY;
	penCalibrate.digBotRightP.x = PDAWIDTH;
	penCalibrate.digBotRightP.y = PDAHEIGHT;
	penCalibrate.scrTopLeftP.x = PDASTARTX;
	penCalibrate.scrTopLeftP.y = PDASTARTY;
	penCalibrate.scrBotRightP.x = PDAWIDTH;
	penCalibrate.scrBotRightP.y = PDAHEIGHT;

	return	0;
}


// Below is windows relative function

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawBitmap
//
// DESCRIPTION: This routine draw a bitmap at the given coordinates in
//					 winPaint mode.
//
// PARAMETERS:  (BitmapPtr) bitmapP - Pointer to a bitmap.
//					 (Coord) x - The x coordinate of the top-left corner.
//					 (Coord) y - The y coordinate of the top-left corner.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawBitmap (BitmapPtr bitmapP, Coord x, Coord y)
{
	VDrawBitmap (x, y, bitmapP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawChar
//
// DESCRIPTION: This routine draw the specified character in the draw
//					 window
//
// PARAMETERS:  (WChar) theChar - The character to draw. This may be
//											either a single-byte character or a 
//											multi-byte character.
//					 (Coord) x - x coordinate of the location where the
//											character is to be drawn.
//					 (Coord) y - y coordinate of the location where the
//											character is to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawChar (WChar theChar, Coord x, Coord y)
{
	VDrawChar (theChar, x, y);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawChars
//
// DESCRIPTION: This routine draw the specified characters in the draw
//				window
//
// PARAMETERS:  (const Char *) chars - Pointer to the characters to draw
//				(Int16) len - Length in bytes of the characters to draw.
//				(Coord) x - x coordinate of the location where the
//							characters is to be drawn.
//				(Coord) y - y coordinate of the location where the
//							characters is to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawChars (const Char *chars, Int16 len, Coord x, Coord y)
{
	VDrawChars (chars, len, x, y, COORD_STRETCH);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawLine
//
// DESCRIPTION: This routine draw a line in the draw window using the 
//					 current foreground color.
//
// PARAMETERS:  (Coord) x1 - x coordinate of line start point
//					 (Coord) y1 - y coordinate of line start point
//              (Coord) x2 - x coordinate of line end point
//					 (Coord) y2 - y coordinate of line end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawLine (Coord x1, Coord y1, Coord x2, Coord y2)
{
	VDrawLine ( x1, y1, x2, y2, 
					THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawGrayLine
//
// DESCRIPTION: This routine draw a dash line in the draw window.
//
// PARAMETERS:  (Coord) x1 - x coordinate of line start point
//					 (Coord) y1 - y coordinate of line start point
//              (Coord) x2 - x coordinate of line end point
//					 (Coord) y2 - y coordinate of line end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawGrayLine (Coord x1, Coord y1, Coord x2, Coord y2)
{
	VDrawLine ( x1, y1, x2, y2, 
					THIN_LINE, FOREGROUNDCOLOR, PS_DOT);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawGrayRectangleFrame
//
// DESCRIPTION: This routine draw a gray rectangle frame in the draw 
//					 window.
//
// PARAMETERS:  (FrameType) frame - Type of frame to draw
//					 (RectangleType *) rP - Pointer to the rectangle to frame.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
//			Jerry 8/08/01	Modify to transfer rectangle resolution
////////////////////////////////////////////////////////////////////////
void WinDrawGrayRectangleFrame (FrameType frame, RectangleType *rP)
{
	switch (frame) {
		case noFrame :
			break;

		case simpleFrame:
//		case rectangleFrame:		// the same as simpleFrame
			VDrawRect (rP, PS_DASH, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
			break;

		case roundFrame:
			VDrawRect (rP, PS_DASH, 5, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
			break;

	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawTitleChars
//
// DESCRIPTION: This routine draw the specified characters inverted 
//					 (background color) in the draw window.
//
// PARAMETERS:  (const Char *) chars - Pointer to the characters to draw
//					 (Int16) len - Length in bytes of the characters to draw.
//					 (Coord) x - x coordinate of the location where the
//							characters is to be drawn.
//					 (Coord) y - y coordinate of the location where the
//							characters is to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
//			Jerry 8/08/01	Modify call VDrawString to draw the invert color
////////////////////////////////////////////////////////////////////////
void WinDrawTitleChars (const Char *chars, Int16 len, Coord x, Coord y)
{
	RectangleType	srcRect;

	srcRect.topLeft.x = x;
	srcRect.topLeft.y = y;
	srcRect.extent.x = FntCharsWidth (chars, len)+4;
	srcRect.extent.y = VPDAToSysYRes(FntLineHeight());

	VDrawRect (&srcRect, PS_SOLID, 0, CL_FOREGROUND, COORD_PARTSTRETCH, DRAW_SET);
	VDrawString ((Coord)(x+1), (Coord)(y+FntLineHeight()/4), 
					chars, len, SINGLELINE, CL_BACKGROUND, COORD_STRETCH);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawInvertedChars
//
// DESCRIPTION: This routine draw the specified characters inverted 
//					 (background color) in the draw window.
//
// PARAMETERS:  (const Char *) chars - Pointer to the characters to draw
//					 (Int16) len - Length in bytes of the characters to draw.
//					 (Coord) x - x coordinate of the location where the
//							characters is to be drawn.
//					 (Coord) y - y coordinate of the location where the
//							characters is to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
//			Jerry 8/08/01	Modify call VDrawString to draw the invert color
////////////////////////////////////////////////////////////////////////
void WinDrawInvertedChars (const Char *chars, Int16 len, Coord x, Coord y)
{
	RectangleType	srcRect;

	srcRect.topLeft.x = x;
	srcRect.topLeft.y = y;
	srcRect.extent.x = FntCharsWidth (chars, len)+4;
	srcRect.extent.y = FntLineHeight();

	VDrawRect (&srcRect, PS_SOLID, 0, CL_FOREGROUND, COORD_PARTSTRETCH, DRAW_SET);
	VDrawString ((Coord)(VPDAToSysXCoord(x)+2), (Coord)(VPDAToSysYCoord(y)+1), 
			chars, len, SINGLELINE, CL_BACKGROUND, COORD_NORMAL);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawPixel
//
// DESCRIPTION: This routine draw a pixel in the draw window using
//				the current foreground color.
//
// PARAMETERS:  (Coord) x - pointer to the x coordinate of a pixel
//				(Coord) y - pointer to the y coordinate of a pixel
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawPixel (Coord x, Coord y)
{
	VDrawPixel (x, y, FOREGROUNDCOLOR);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawRectangle
//
// DESCRIPTION: This routine draw a rectangle in the draw window using
//					 the current foreground color.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to the rectangle to draw
//					 (UInt16) cornerDiam - Radius of rounded corners. Specify
//										zero for square corners.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawRectangle (RectangleType *rP, UInt16 cornerDiam)
{
	VDrawRect (rP, PS_SOLID, cornerDiam, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawRectangleFrame
//
// DESCRIPTION: This routine draw a rectangle frame in the draw window
//					 using the current forgraound color.
//
// PARAMETERS:  (FrameType) frame - Type of frame to draw
//					 (RectangleType *) rP - Pointer to the rectangle to frame.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinDrawRectangleFrame (FrameType frame, RectangleType *rP)
{
	switch (frame) {
		case noFrame :
			break;

		case simpleFrame:
//		case rectangleFrame:
			VDrawRect (rP, PS_INSIDEFRAME, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
			break;

		case roundFrame:
			VDrawRect (rP, PS_INSIDEFRAME, 5, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
			break;

	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinDrawTruncChars
//
// DESCRIPTION: This routine draw the specified characters in the draw
//					 window, truncating the characters to the specified width.
//
// PARAMETERS:  (const Char *) chars - Pointer to the characters to draw
//					 (Int16) len - Length in bytes of the characters to draw.
//					 (Coord) x - x coordinate of the location where the
//							characters is to be drawn.
//					 (Coord) y - y coordinate of the location where the
//							characters is to be drawn.
//					 (Coord) maxWidth - Maximum width in pixel of the characters
//							that are to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
//			Jerry	9/13/01	Calculate the actual width instead of estimate
////////////////////////////////////////////////////////////////////////
void WinDrawTruncChars (const Char *chars, Int16 len, Coord x, Coord y, Coord maxWidth)
{
	int	strWidth = FntCharsWidth (chars, len);
	Int16	width=0, i, charWidth;

	if ( strWidth > maxWidth ) {
		for ( i = 0; i < len; i++ ) {
			charWidth = FntCharsWidth (&(chars[i]), 1);
			if ( (width + charWidth) > maxWidth ) 			
				break;
			else
				width += charWidth;
		}
	}

	VDrawChars (chars, i, x, y, COORD_STRETCH);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinEraseChars
//
// DESCRIPTION: This routine erase the specified characters in the draw
//					 window.
//
// PARAMETERS:  (const Char *) chars - Pointer to the characters to draw
//				(Int16) len - Length in bytes of the characters to draw.
//				(Coord) x - x coordinate of the location where the
//							characters is to be drawn.
//				(Coord) y - y coordinate of the location where the
//							characters is to be drawn.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
//			Jerry	9/13/01	Calculate actual width instead of estimate value
////////////////////////////////////////////////////////////////////////
void WinEraseChars (const Char *chars, Int16 len, Coord x, Coord y)
{
	RectangleType	srcRect;

	srcRect.topLeft.x = x;
	srcRect.topLeft.y = y;
	srcRect.extent.x = FntCharsWidth (chars, len);
	srcRect.extent.y = FntCharHeight();

	if ( (srcRect.topLeft.x+srcRect.extent.x) > PDAWIDTH ) {
		srcRect.extent.x = PDAWIDTH - srcRect.topLeft.x;
	}

	VDrawRect (&srcRect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinEraseLine
//
// DESCRIPTION: This routine draw a line in the draw window using the 
//					 current background color.
//
// PARAMETERS:  (Coord) x1 - x coordinate of line start point
//					 (Coord) y1 - y coordinate of line start point
//              (Coord) x2 - x coordinate of line end point
//					 (Coord) y2 - y coordinate of line end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinEraseLine (Coord x1, Coord y1, Coord x2, Coord y2)
{
	VDrawLine (x1, y1, x2, y2, THIN_LINE, BACKGROUNDCOLOR, PS_SOLID);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinErasePixel
//
// DESCRIPTION: This routine draw a pixel in the draw window using
//				the current background color.
//
// PARAMETERS:  (Coord) x - pointer to the x coordinate of a pixel
//					 (Coord) y - pointer to the y coordinate of a pixel
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinErasePixel (Coord x, Coord y)
{
	VDrawPixel (x, y, BACKGROUNDCOLOR);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinEraseRectangle
//
// DESCRIPTION: This routine draw a rectangle in the draw window using
//				the current background color.
//
// PARAMETERS:  (RectangleType *) rP - pointer to the rectangle to erase
//				(UInt16) corneDiam - Radius of rounded coners. Specify 
//							zero for square corners.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinEraseRectangle (RectangleType *rP, UInt16 corneDiam)
{
	VDrawRect (rP, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinEraseWindow
//
// DESCRIPTION: This routine earse the contents of the draw window.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinEraseWindow (void)
{
	RectangleType	eraseRect;

	RctSetRectangle (&eraseRect, 0, 0, 160, 160);
	WinEraseRectangle (&eraseRect,0);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinFillLine
//
// DESCRIPTION: This routine fill a line in the draw window with the 
//					 current pattern.
//
// PARAMETERS:  (Coord) x1 - x coordinate of line start point
//					 (Coord) y1 - y coordinate of line start point
//              (Coord) x2 - x coordinate of line end point
//					 (Coord) y2 - y coordinate of line end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinFillLine (Coord x1, Coord y1, Coord x2, Coord y2)
{
	VDrawLine (x1, y1, x2, y2, THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinFillRectangle
//
// DESCRIPTION: This routine draw a rectangle in the draw window with
//					 current pattern.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to the rectangle to draw
//					 (UInt16) cornerDiam - Radius of rounded corners. Specify
//										zero for square corners.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinFillRectangle (RectangleType *rP, UInt16 cornerDiam)
{
	VDrawRect (rP, PS_SOLID, cornerDiam, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinGetPixel
//
// DESCRIPTION: This routine return the color value of a pixel in the
//					 current draw window.
//
// PARAMETERS:  (Coord) x - pointer to the x coordinate of a pixel
//					 (Coord) y - pointer to the y coordinate of a pixel
//
// RETURNED:    Returns the indexed color value of the pixel.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01		Initial Revision
////////////////////////////////////////////////////////////////////////
IndexedColorType WinGetPixel (Coord x, Coord y)
{
	return	VGetPixel (x, y);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinGetClip
//
// DESCRIPTION: This routine get the clipping rectangle of the draw 
//					 window.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to a structure hold 
//													the clipping bounds.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinGetClip (RectangleType *rP)
{
	Vmemcpy (rP, &clipRect, sizeof(RectangleType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinInvertPixel
//
// DESCRIPTION: This routine draw a pixel in the draw window using
//				the current foreground color.
//
// PARAMETERS:  (Coord) x - pointer to the x coordinate of a pixel
//					 (Coord) y - pointer to the y coordinate of a pixel
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinInvertPixel (Coord x, Coord y)
{
	if ( VGetPixel (x, y) == 1 ) {	// FOREGROUNDCOLOR
		VDrawPixel (x, y, BACKGROUNDCOLOR);
	} else if ( VGetPixel (x, y) == 0 ) {	// BACKGROUNDCOLOR
		VDrawPixel (x, y, FOREGROUNDCOLOR);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinInvertRectangle
//
// DESCRIPTION: This routine invert a rectangle in the draw window.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to a structure hold 
//													the clipping bounds.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	10/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinInvertRectangle (RectangleType *rP, UInt16 cornerDim)
{
	VDrawRect (rP, PS_SOLID, cornerDim, CL_FOREGROUND, COORD_STRETCH, DRAW_XOR);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinPaintPixel
//
// DESCRIPTION: This routine render a pixel in the draw window using
//					 the current drawing state.
//
// PARAMETERS:  (Coord) x - pointer to the x coordinate of a pixel
//					 (Coord) y - pointer to the y coordinate of a pixel
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinPaintPixel (Coord x, Coord y)
{
	VDrawPixel (x, y, FOREGROUNDCOLOR);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinPaintPixels
//
// DESCRIPTION: This routine render several pixels in the draw window using
//					 the current drawing state.
//
// PARAMETERS:  (UInt16) numPoints - Number of pixels to paint.
//					 (PointType) pts - Array of pixels.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/29/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WinPaintPixels (UInt16 numPoints, PointType pts[])
{
	UInt16	index;

	for ( index = 0; index < numPoints; index++ ) 
		VDrawPixel (pts[index].x, pts[index].y, FOREGROUNDCOLOR);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinPaintRectangle
//
// DESCRIPTION: This routine draw a rectangle in the draw window using 
//					 the current drawing state.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to the rectangle to draw.
//					 (UInt16) cornerDiam - Radius of rounded corners. Specify
//										zero for square corners.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinPaintRectangle (RectangleType *rP, UInt16 cornerDiam)
{
	VDrawRect (rP, PS_SOLID, cornerDiam, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinPopDrawState
//
// DESCRIPTION: This routine restore the draw state values to the last
//					 saved set on the stack.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinPopDrawState ()
{
	Vmemcpy (&curDrawState, &storedDrawState, sizeof (DrawStateType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinPushDrawState
//
// DESCRIPTION: This routine save the current draw state values onto
//					 the draw state stack.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinPushDrawState ()
{
	Vmemcpy (&storedDrawState, &curDrawState, sizeof (DrawStateType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinResetClip
//
// DESCRIPTION: This routine reset the clipping rectangle of the draw
//				window to the portion of the draw window that is
//				winthin the bounds of the display.
//
// PARAMETERS:  
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinResetClip(void)
{
	clipRect.topLeft.x = 0;
	clipRect.topLeft.y = 0;
	clipRect.extent.x = PDAWIDTH;
	clipRect.extent.x = PDAHEIGHT;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinSetBackColor
//
// DESCRIPTION: This routine set the background color to use in 
//					 subsequent draw operations.
//
// PARAMETERS:  (IndexedColorType) backColor - Color to set.
//
// RETURNED:    Returns the previous background color index.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
IndexedColorType WinSetBackColor (IndexedColorType backColor)
{
	IndexedColorType	oldColor = backgroundColor;
	backgroundColor = backColor;

	return	oldColor;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinSetClip
//
// DESCRIPTION: This routine set the clipping rectangle of the draw 
//					 window.
//
// PARAMETERS:  (RectangleType *) rP - Pointer to a structure holding 
//													the clipping bounds.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WinSetClip (RectangleType *rP)
{
	Vmemcpy (&clipRect, rP, sizeof(RectangleType));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinSetForeColor
//
// DESCRIPTION: This routine set the foreground color to use in 
//					 subsequent draw operations.
//
// PARAMETERS:  (IndexedColorType) foreColor - Color to set.
//
// RETURNED:    Returns the previous foreground color index.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
IndexedColorType WinSetForeColor (IndexedColorType foreColor)
{
	IndexedColorType	oldColor = foregroundColor;
	foregroundColor = foreColor;

	return	oldColor;
}
