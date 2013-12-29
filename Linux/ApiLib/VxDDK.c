#include <fcntl.h>
#include <stdio.h>
#include <linux/mman.h>
#include <linux/fb.h>
#include <errno.h>
#include <math.h>
//#include <unistd.h>

#include <VCommon.h>
#include <VParser.h>
#include <VPdaSDK.h>
#include <Networks.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#include <UI/helvr10.h>

// define calibrate variable
int	tPadDiffX=1513, tPadDiffY=1149;
int	tBaseX=13, tBaseY=19;

#define	CursorSize		10


// time ticks definitions
#define	SYSTEMTICKS			5
#define	MINSYSTICKS			2
#define	MAXSYSTICKS			200

// ascii definitions
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define	PIPESIZE			4096

int		DisplayDev, TouchPadDev;
Display	display;
unsigned char* pipe_ram;
Int16		lastScreenX=-1, lastScreenY=-1;
extern Int16	HitCtlIndex;


extern MWCFONT	*currentFont;
extern SYSHandle	sysHandle;
extern GrfStateType	grfState;

unsigned char	tColor=FOREGROUNDCOLOR;	// text color

unsigned char	roundX[] = 
	{	1,
		2, 2,
		2, 3, 3,
		2, 3, 4, 4,
		2, 4, 4, 5, 5,
		3, 4, 5, 6, 6, 6,
		3, 5, 6, 6, 7, 7, 7,
		3, 5, 6, 7, 7, 8, 8, 8,
		4, 6, 7, 7, 8, 8, 9, 9, 9,
		4, 6, 7, 8, 9, 9, 10, 10, 10 ,10,
		4, 6, 7, 8, 9, 10, 10, 11, 11, 11, 11,
		5, 6, 8, 9, 10, 10, 11, 11, 12, 12, 12, 12,
		5, 7, 8, 9, 10, 11, 12, 12, 12, 13, 13, 13, 13,
		5, 7, 9, 10, 11, 11, 12, 13, 13, 13, 14, 14, 14, 14,
		5, 7, 9, 10, 11, 12, 13, 13, 14, 14, 14, 15, 15, 15, 15,
		5, 8, 9, 10, 12, 12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 16,
		6, 8, 10, 11, 12, 13, 13, 14, 15, 15, 16, 16, 16, 17, 17, 17, 17,
		6, 8, 10, 11, 12, 13, 14, 15, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18,
		6, 9, 10, 11, 13, 14, 15, 15, 16, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19,
		6, 9, 10, 12, 13, 14, 15, 16, 17, 17, 18, 18, 19, 19, 19, 20, 20, 20, 20, 20,
	};


unsigned char *memBM[5];		// the handle bitmap of saved screen
UInt16		BitmapIndex=0;
EventType	*CurEvent;

Boolean			penDown=false;

#ifndef	_APM_SIMULATOR
extern DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags);
#endif

void VDrawLine (Coord StartX, Coord StartY, Coord EndX, Coord EndY, 
						UInt16 width, UInt32 color, Int penStyle);
void drawline (Coord x0, Coord y0, Coord x1, Coord y1);
extern Int16 WPushEvent (const EventType *event);
unsigned char VSetTextColor (unsigned char color);
void SetDrawMode (char mode);

// Below APIs are graphic relative API
////////////////////////////////////////////////////////////////////////
// FUNCTION:    WClearScreen
//
// DESCRIPTION: This routine clear screen.
//
// PARAMETERS:  (int) mode - clear screen mode,		
//										SCREEN_ALL for all screen, 
//										SCREEN_DISPLAY for display area
//										(keep system button and hw area)
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/25/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WClearScreen (int mode)
{ 
	if (display.pPrivate) {
		if ( mode == SCREEN_DISPLAY )
			memset ( display.pPrivate, 0, SCREENWIDTH*SCREENHEIGHT/8 );
		else if ( mode == SCREEN_ALL )
			memset ( display.pPrivate, 0, (SCREENWIDTH/8)*(SCREENHEIGHT*4/3) );
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VSaveRegion
//
// DESCRIPTION: This routine save the region
//
// PARAMETERS:  (const RectangleType *) rect - the region to save
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/15/01		Initial Revision
//			Jerry	3/21/01		Modify VRect to RectangleType
//			Jerry	3/29/01		Can save and redraw more than 1 region
//								add bitmap queue to system, use memBM[4]
//								to save client region.
////////////////////////////////////////////////////////////////////////
void VSaveRegion(const RectangleType *rP, int mode)
{
	int	x1, y1, x2, y2, index;
	RectangleType	rect;

	if ( mode == COORD_STRETCH )
		VPDAToSysRect (&rect, rP);
	else
		Vmemcpy (&rect, rP, sizeof(RectangleType));
	// not allocate screen memory, return with no save
	if ((!display.pPrivate))	return;

	x1 = rect.topLeft.x/8;
	y1 = rect.topLeft.y;

	x2 = (rect.extent.x+7)/8;
	if ( x2 < 30 )	x2++;
	y2 = rect.extent.y+1;

//	printf ("%d,%d,%d,%d\n", rect.topLeft.x, rect.topLeft.y, rect.extent.x, rect.extent.y);
//	printf ("%d,%d,%d,%d\n", x1, y1, x2, y2);
	if ( memBM[BitmapIndex] ) {
		memBM[BitmapIndex] = (unsigned char *)realloc (x2*y2);
	} else {
		memBM[BitmapIndex] = (unsigned char *)malloc (x2*y2);
	}

//	printf ("allocate = %d\n", x2*y2);
	if ( rP ) {	// redraw the rectangle
		for ( index = 0; index < y2; index++ ) {
			Vmemcpy ((memBM[BitmapIndex]+index*x2), display.pPrivate+(y1+index)*SCREENWIDTH/8+x1, x2);
		}
		BitmapIndex++;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VRedrawRegion
//
// DESCRIPTION: This routine repaint the saved region
//
// PARAMETERS:  (const RectangleType *) rect - the region to recdraw
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/15/01		Initial Revision
//			Jerry	3/21/01		Modify VRect to RectangleType
//			Jerry	3/29/01		Can save and redraw more than 1 region
//								add bitmap queue to system, use memBM[4]
//								to save client region.
////////////////////////////////////////////////////////////////////////
void VRedrawRegion(const RectangleType *rP, int mode) 
{
	int	x1, y1, x2, y2, index;
	RectangleType	rect;

	if ( mode == COORD_STRETCH )
		VPDAToSysRect (&rect, rP);
	else
		Vmemcpy (&rect, rP, sizeof(RectangleType));

	// not allocate screen memory, return with no save
	if (!display.pPrivate)	return;

	x1 = rect.topLeft.x/8;
	y1 = rect.topLeft.y;

	x2 = (rect.extent.x+7)/8;
	if ( x2 < 30 )	x2++;
	y2 = rect.extent.y+1;

	if ( rP ) {	// redraw the rectangle
		if ( BitmapIndex == 0 ) {	// No saved region, not redraw
			return;
		}
		BitmapIndex--;
		for ( index = 0; index < y2; index++ ) {
			Vmemcpy (display.pPrivate+(y1+index)*SCREENWIDTH/8+x1, (memBM[BitmapIndex]+index*x2), x2);
		}
		Vfree (memBM[BitmapIndex]);
		memBM[BitmapIndex] = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawBitmap
//
// DESCRIPTION: This routine draw a bitmap in speicfied position.
//
// PARAMETERS:  (int) x - The Left position of bitmap.
//					 (int) y - The Top position of bitmap.
//					 (char *) filename - filename of bitmap.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawBitmap (int x, int y, char *filename)
{
	FILE	*fp;
	unsigned char	byte;
//	IMAGEBITS *bits;
	int		i, j, k;
	WBitmap	bmp;
	unsigned char		*buffer;
	unsigned char		*bits;
	long		fileLength;
	long		lineWidth;
	unsigned short		offset;

	if ( fp = fopen (filename, "rb") ) {
		fseek (fp, 0x0a, SEEK_SET);
		fread (&(offset), 1, sizeof(unsigned short), fp);
		fseek (fp, 0x0f, SEEK_SET);
		fread (&(bmp.width), 1, sizeof(long), fp);
		bmp.width = VTransferUInt32 (bmp.width);
		fread (&(bmp.height), 1, sizeof(long), fp);
		bmp.height = VTransferUInt32 (bmp.height);

		fseek (fp, 0x19, SEEK_SET);
		fread (&(bmp.planes), 1, sizeof(short), fp);
		bmp.planes = VTransferUInt (bmp.planes);

		fseek (fp, 0, SEEK_END);
		fileLength = ftell (fp);
		lineWidth = (fileLength-offset)/(bmp.height);

		buffer = (unsigned char *) malloc ((fileLength-offset));
		if ( !buffer ) {
			fclose (fp);
			return;
		}

		fseek (fp, offset, SEEK_SET);
		fread (buffer, 1, (fileLength-offset), fp);
		bits = buffer;

		switch (bmp.planes) {
			case 1:
				for ( i = 0; i < bmp.height; i++ ) {
					for ( j = 0; j < lineWidth; j++, bits++) {
						byte = *bits;
						for ( k = 0; k < 8; k++ ) {
							if ( j*8+k >= bmp.width )
								break;
							if ( (byte & 0x80) ) {
								VDrawPixel (x+j*8+k, y+(bmp.height-i), tColor);
							}
							byte = byte << 1;
						}
					}
				}
				break;

			case 4:
				for ( i = 0; i < bmp.height; i++ ) {
					for ( j = 0; j < lineWidth/2; j++, bits++) {
						if ( j*2 < bmp.width ) {
							VDrawPixel (x+j*2, y+(bmp.height-i), ((*bits&0xf0)>>4)&0x0f);
							VDrawPixel (x+j*2+1, y+(bmp.height-i), *bits&0x0f);
						}
					}
				}
				break;

			case 8:
				for ( i = 0; i < bmp.height; i++ ) {
					for ( j = 0; j < lineWidth; j++, bits++) {
						if ( j < bmp.width )
							VDrawPixel (x+j, y+(bmp.height-i), *bits);
					}
				}
				break;
		}

		free (buffer);
		fclose (fp);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawChar
//
// DESCRIPTION: This routine draw a character in speicfied position.
//
// PARAMETERS:  (WChar) theChar - Character to draw.
//					 (Coord) x - The Left position of character.
//					 (Coord) y - The Top position of character.
//
// RETURNED:    Returns the width of character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 VDrawChar (WChar ch, Coord x, Coord y)
{
	unsigned short	offset;
	int		width;
	unsigned short	byte;
	IMAGEBITS *bits;
	int		i, j;

	offset = currentFont->offset[(ch-0x20)];
	width = currentFont->width[(ch-0x20)];
	bits = helvR10_bits + (ch-0x20)*12;

	for ( i = 0; i < currentFont->height; i++, bits++ ) {
		byte = ((*bits)&0xff00);
		if ( !byte )
			continue;
		for ( j = 0; j < 8; j++ ) {
			if ( byte & 0x8000 ) {
				VDrawPixel (x+j,y+i,tColor);
			}
			byte = byte << 1;
		}
	}

	return	width+1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawChars
//
// DESCRIPTION: This routine draw a character string in the speicfied 
//					 position.
//
// PARAMETERS:  (const Char *) chars - Pointer to character string.
//					 (Int16) len - length of character string.
//					 (Coord) x - The Left position of string.
//					 (Coord) y - The Top position of string.
//
// RETURNED:    Returns the width of character strings.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 VDrawChars (const Char *string, Int16 length, Coord x, Coord y, int mode)
{
	Int16		width=0;
	int		k;

	if ( mode == COORD_STRETCH ) {
		x = VPDAToSysXCoord (x);
		y = VPDAToSysXCoord (y);
	}
	for ( k = 0; k < length; k++ ) {
		// draw character
		if ( (string[k] < currentFont->firstchar) || 
			(string[k] > currentFont->size+currentFont->firstchar) ) 
			break;

		width += VDrawChar (string[k], x+width, y);
	}	// end of for (k)

	return	width;
}

int	oldX, oldY;
int	curCounts=0;
Boolean	cursorState=false;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawCursor
//
// DESCRIPTION: This routine draw a cursor in speicfied position.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//					 (int) mode - Mode of drawing cursor
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
//			Jerry	8/28/01	Add erase cursor function
//			Jerry	11/22/01	Add mode option
////////////////////////////////////////////////////////////////////////
void VDrawCursor (Coord x, Coord y, int mode)
{
	y = VPDAToSysYCoord (y);

	SetDrawMode (DRAW_XOR);

	VSetTextColor (FOREGROUNDCOLOR);

	// clear old cursor
	if ( (x!=oldX) || (y!=oldY) ) {
		if ( (oldX != -1) && (oldY != -1) && cursorState) {
			drawline (oldX, oldY, oldX, oldY+CursorSize);
			cursorState = !cursorState;
		}
		oldX = x;
		oldY = y;
	}

	if ( mode == CUR_CLEAR ) {
		if ( cursorState ) {
			cursorState = !cursorState;
			drawline (x, y, x, y+CursorSize);
		}
		oldX = x;
		oldY = y;
	} else if ( (curCounts == 0) ) {
		cursorState = !cursorState;
		drawline (x, y, x, y+CursorSize);
		oldX = x;
		oldY = y;
	}

	curCounts++;
	if ( curCounts == 20 ) {
		curCounts = 0;
	}
	SetDrawMode (DRAW_SET);

}

int	oldGrfState=-1;
void VDrawGrafState (Boolean drawMode)
{
	RectangleType	rect;

	if ( !drawMode ) {
		rect.topLeft.x = SysPanelVLine1+1;
		rect.topLeft.y = SysPanelEndY-12;
		rect.extent.x = 11;
		rect.extent.y = 11;
		VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_NORMAL, DRAW_SET);
		return;
	}

	if ( oldGrfState != grfState.sysTempShift ) {
		rect.topLeft.x = SysPanelVLine1+1;
		rect.topLeft.y = SysPanelEndY-12;
		rect.extent.x = 11;
		rect.extent.y = 11;
		VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_NORMAL, DRAW_SET);
		switch (grfState.sysTempShift) {
			case 0:
				VDrawChar ('a', rect.topLeft.x+1, rect.topLeft.y);
				break;
			case 1:
				VDrawChar ('A', rect.topLeft.x+1, rect.topLeft.y);
				break;
			case 9:
				VDrawChar ('S', rect.topLeft.x+1, rect.topLeft.y);
				break;
			default:
				break;
		}
	} 

	oldGrfState = grfState.sysTempShift;
}

void SetDrawMode (char mode)
{
	copyMode = mode;
}
/*
static UInt8 APDA_GetPixel2 (Display* display, int x, int y)
{ 
	if (display &&
      display->area.uLeft <= x && x <= display->area.uRight &&
      display->area.uTop  <= y && y <= display->area.uBottom) {
		register unsigned offset = (y << 5) - (y << 1) + (x >> 3);
		register unsigned char bit = 0x80 >> (x & 7), v = *((unsigned char*)(display->pPrivate) + offset);

		return	(v>>bit)&0x01;
	}
}

static UInt8 DSC21_GetPixel256 (Display* display, int x, int y)
{ 
	if (display &&
      display->area.uLeft <= x && x <= display->area.uRight &&
      display->area.uTop  <= y && y <= display->area.uBottom) {
		register unsigned offset, acc;
		offset = (acc = y << 3) << 1;
		offset = ((offset + acc - y) << 5) + x;

		return	*((unsigned char*)(display->pPrivate) + offset);
	}
}
*/
static void APDA_PutPixel2 (Display* display, int x, int y, int color)
{ 
	if (display &&
      display->area.uLeft <= x && x <= display->area.uRight &&
      display->area.uTop  <= y && y <= display->area.uBottom) {
		register unsigned offset = (y << 5) - (y << 1) + (x >> 3);
//		register unsigned char bit = 0x80 >> (x & 7), v = *((unsigned char*)(display->pZBuffer) + offset);
		register unsigned char bit = 0x80 >> (x & 7), v = *((unsigned char*)(display->pPrivate) + offset);
		color = (color & 1) << (7 - (x & 7));
		switch (copyMode) {
			case DRAW_SET : v &= ~bit;
			case DRAW_XOR : v ^= color;
		}
		*((unsigned char*)(display->pPrivate) + offset) = v;
	}
}

static void DSC21_PutPixel256 (Display* display, int x, int y, int color)
{ 
	if (display &&
      display->area.uLeft <= x && x <= display->area.uRight &&
      display->area.uTop  <= y && y <= display->area.uBottom) {
		register unsigned offset, acc;
		offset = (acc = y << 3) << 1;
		offset = ((offset + acc - y) << 5) + x;
		switch (copyMode) {
			case DRAW_SET :
				*((unsigned char*)(display->pPrivate) + offset) = color;
				break;
			case DRAW_XOR :
				*((unsigned char*)(display->pPrivate) + offset) ^= color;
		}
	}
}
/*
static void APDA_UpdateScreen (Display* display)
{
	Vmemcpy (display->pPrivate, display->pZBuffer, display->size);
}
*/
////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawPixel
//
// DESCRIPTION: This routine draw a pixel in speicfied position.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//					 (UInt32) color - The color of pixel.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawPixel (Coord x, Coord y, UInt32 color)
{
	(*display.pfnPutPixel)(&display,x,y,color);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetPixel
//
// DESCRIPTION: This routine get the color of specified pixel.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt8 VGetPixel (Coord x, Coord y)
{
	return	(*display.pfnGetPixel)(&display,x,y);
}

void VDrawCheck (Coord StartX, Coord StartY, Boolean Style)
{
	StartX = VPDAToSysXCoord (StartX);
	StartY = VPDAToSysXCoord (StartY);

	if ( Style ) {
		drawline (StartX+2, StartY+4, StartX+4, StartY+10);
		drawline (StartX+4, StartY+10, StartX+9, StartY);
		drawline (StartX+2, StartY+3, StartX+5, StartY+10);
		if ( StartY > 1 ) {
			drawline (StartX+5, StartY+10, StartX+10, StartY-1);
		} else {
			drawline (StartX+5, StartY+10, StartX+10, StartY);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    drawline
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (Coord) StartX - the X coordinate of start point
//					 (Coord) StartY - the Y coordinate of start point
//					 (Coord) EndX - the X coordinate of end point
//					 (Coord) EndY - the Y coordinate of end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void drawline (Coord x0, Coord y0, Coord x1, Coord y1)
{
	// Modified Bresenham's algorithm for all slopes and line directions
	register int dx, dy, xstep, ystep, dpr, dpru, p;

	if ( !(display.pPrivate) || !(display.pfnPutPixel) )
		return;
	if ((dx = x1 - x0) >= 0)
		xstep = 1;
	else dx = -dx, xstep = -1;
	if ((dy = y1 - y0) >= 0)
		ystep = 1;
	else dy = -dy, ystep = -1;
	if (dx >= dy) {
		dpr = dy << 1, dpru = dpr - (dx << 1), p = dpr - dx;
		for (; dx >= 0; dx--) {
			(*display.pfnPutPixel)(&display,x0,y0,tColor);
			if (p > 0)
				x0 += xstep, y0 += ystep, p += dpru;
			else
				x0 += xstep, p += dpr;
		}
	} else {
		dpr = dx << 1, dpru = dpr - (dy << 1), p = dpr - dy;
		for (; dy >= 0; dy--) {
			(*display.pfnPutPixel)(&display,x0,y0,tColor);
			if (p > 0)
				x0 += xstep, y0 += ystep, p += dpru;
			else
				y0 += ystep, p += dpr;
		}
	}

//	(*display.pfnUpdateScreen)(&display);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawLine
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (Coord) StartX - the X coordinate of start point
//					 (Coord) StartY - the Y coordinate of start point
//					 (Coord) EndX - the X coordinate of end point
//					 (Coord) EndY - the Y coordinate of end point
//					 (UInt16) width - The width of pen to draw
//					 (UInt32) color - the color of pen to draw
//					 (Int16) penStyle - the style of pen to draw
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/12/01	Initial Revision
//			Jerry 5/06/01	Add Color parameter
//			Jerry	8/09/01	Add width parameter
////////////////////////////////////////////////////////////////////////
void VDrawLine (Coord StartX, Coord StartY, Coord EndX, Coord EndY, UInt16 width, UInt32 color, Int penStyle)
{
	// Modified Bresenham's algorithm for all slopes and line directions
	register int dx, dy, xstep, ystep, dpr, dpru, p;
	int x0, y0, x1, y1;

	x0 = VPDAToSysXCoord(StartX);	
	y0 = VPDAToSysXCoord(StartY);
	x1 = VPDAToSysXCoord(EndX);	
	y1 = VPDAToSysXCoord(EndY);

	drawline (x0, y0, x1, y1);
//	(*display.pfnUpdateScreen)(&display);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawRect
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (RectangleType) rect - rectangle start point and width,Height.
//					 (Int16) penStyle - the style of pen to draw
//					 (UInt16) cornerDiam - Radius of rounded corners. Specify zero
//										for square corners.
//					 (Boolean) bBackground - TURE draw the background with normal
//										color(SRCCOPY), FALSE draw the background with 
//										reverse color (SRCINVERT)
//					 (int) mode -	RECT_NORMAL for no stretch
//										COORD_STRETCH for stretch all rectangle
//										RECT_PARTSTRETCH for stretch topleft point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/12/01	Initial Revision
//			Jerry	3/20/01	Modify VRect to RectangleType
//			Jerry	3/23/01	Add penstyle parameter
//			Jerry 5/07/01	Add cornerDiam parameter
//			Jerry 7/24/01	Active cornerDiam
//			Jerry	11/23/01	Add Background and mode option
//////////////////////////////////////////////////////////////////////////////
void VDrawRect (RectangleType *rP, UInt16 penStyle, UInt16 cornerDiam,
					 Boolean bBackground, char coordMode, char drawMode)
{
	int	x, y;
	unsigned char	oldColor;
	RectangleType	rect;

	SetDrawMode (drawMode);
	// strecth the rectangle size by input mode
	if (coordMode == COORD_STRETCH) {
		VPDAToSysRect (&rect, rP);
		cornerDiam = VPDAToSysXRes (cornerDiam);
	} else if ( coordMode == COORD_PARTSTRETCH ) {
		VPDAToSysPoint (&(rect.topLeft), &(rP->topLeft));
		Vmemcpy (&(rect.extent), &(rP->extent), sizeof(PointType));
	} else {
		Vmemcpy (&rect, rP, sizeof(RectangleType));
	}

	// maximum cornerDiam is 20
	if ( cornerDiam > 20 )	cornerDiam = 20;

	if ( bBackground ) {
		oldColor = VSetTextColor (BACKGROUNDCOLOR);
	} else {
		oldColor = VSetTextColor (FOREGROUNDCOLOR);
	}

	if ( cornerDiam == 0 ) {
		if ( penStyle == PS_SOLID ) {
			x = rect.topLeft.x;
			y = rect.topLeft.y;
			if (display.pPrivate && 
				display.area.uLeft <= x && x <= display.area.uRight &&
				display.area.uTop  <= y && y <= display.area.uBottom) {
				int	i, j;
		
				for ( j = 0; j <= rect.extent.y; j++ ) {
					drawline (x, y+j, x+rect.extent.x, y+j);
				}
			}
		} else {
			drawline (rect.topLeft.x, rect.topLeft.y, 
				rect.topLeft.x+rect.extent.x, rect.topLeft.y);
			drawline (rect.topLeft.x+rect.extent.x, rect.topLeft.y, 
				rect.topLeft.x+rect.extent.x, rect.topLeft.y+rect.extent.y);
			drawline (rect.topLeft.x+rect.extent.x, rect.topLeft.y+rect.extent.y, 
				rect.topLeft.x, rect.topLeft.y+rect.extent.y);
			drawline (rect.topLeft.x, rect.topLeft.y+rect.extent.y, 
				rect.topLeft.x, rect.topLeft.y);
		}
	} else {
		int	y, x1, x2;
		int	index=(cornerDiam*(cornerDiam-1)/2);

		if ( penStyle == PS_SOLID ) {		// draw a filled rectangle
			for ( y = 0; y < cornerDiam; y++ ) {
				x1 = roundX[index+y];

				// draw left top corner
				drawline ( rect.topLeft.x+(cornerDiam-x1), 
							  rect.topLeft.y+y,
							  rect.topLeft.x+cornerDiam-1, 
							  rect.topLeft.y+y);

				// draw right top corner
				drawline ( rect.topLeft.x+rect.extent.x-cornerDiam, 
							  rect.topLeft.y+y,
							  rect.topLeft.x+rect.extent.x-cornerDiam+x1, 
							  rect.topLeft.y+y);

				// draw left bottom corner
				drawline ( rect.topLeft.x+(cornerDiam-x1), 
							  rect.topLeft.y+rect.extent.y-y,
							  rect.topLeft.x+cornerDiam-1, 
							  rect.topLeft.y+rect.extent.y-y);

				// draw right bottom corner
				drawline ( rect.topLeft.x+rect.extent.x-cornerDiam, 
							  rect.topLeft.y+rect.extent.y-y,
							  rect.topLeft.x+rect.extent.x-cornerDiam+x1, 
							  rect.topLeft.y+rect.extent.y-y);
			}

			// draw other area
			for ( y = 0; y < cornerDiam; y++ ) {
				drawline ( (Coord)(rect.topLeft.x+cornerDiam), 
							  (Coord)(rect.topLeft.y+y),
							  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam-1),
							  (Coord)(rect.topLeft.y+y));
				drawline ( (Coord)(rect.topLeft.x+cornerDiam), 
							  (Coord)(rect.topLeft.y+rect.extent.y-y),
							  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam-1),
							  (Coord)(rect.topLeft.y+rect.extent.y-y));
			}

			for ( y = cornerDiam; y <= rect.extent.y-cornerDiam; y++ ) {
				drawline ( (Coord)(rect.topLeft.x), 
							  (Coord)(rect.topLeft.y+y),
							  (Coord)(rect.topLeft.x+rect.extent.x),
							  (Coord)(rect.topLeft.y+y));
			}
		} else {		// draw a outline rectangle
			// draw 4 lines
			drawline ( rect.topLeft.x+cornerDiam-roundX[index], 
						  rect.topLeft.y,
						  rect.topLeft.x+rect.extent.x-cornerDiam+roundX[index],
						  rect.topLeft.y);

			drawline ( rect.topLeft.x+cornerDiam-roundX[index], 
						  rect.topLeft.y+rect.extent.y,
						  rect.topLeft.x+rect.extent.x-cornerDiam+roundX[index],
						  rect.topLeft.y+rect.extent.y);

			drawline ( rect.topLeft.x, 
						  rect.topLeft.y+cornerDiam,
						  rect.topLeft.x,
						  rect.topLeft.y+rect.extent.y-cornerDiam);

			drawline ( rect.topLeft.x+rect.extent.x, 
						  rect.topLeft.y+cornerDiam,
						  rect.topLeft.x+rect.extent.x,
						  rect.topLeft.y+rect.extent.y-cornerDiam);

			// draw 4 corners
			for ( y = 0; y < cornerDiam-1; y++ ) {
				x1 = roundX[index+y];
				x2 = roundX[index+y+1];

				// draw left top corner
				drawline ( rect.topLeft.x+(cornerDiam-x1), 
							  rect.topLeft.y+y,
							  rect.topLeft.x+(cornerDiam-x2), 
							  rect.topLeft.y+y+1);

				// draw right top corner
				drawline ( rect.topLeft.x+rect.extent.x-cornerDiam+x1, 
							  rect.topLeft.y+y,
							  rect.topLeft.x+rect.extent.x-cornerDiam+x2, 
							  rect.topLeft.y+y+1);

				// draw left bottom corner
				drawline ( rect.topLeft.x+(cornerDiam-x1), 
							  rect.topLeft.y+rect.extent.y-y,
							  rect.topLeft.x+(cornerDiam-x2), 
							  rect.topLeft.y+rect.extent.y-y-1);

				// draw right bottom corner
				drawline ( rect.topLeft.x+rect.extent.x-cornerDiam+x1, 
							  rect.topLeft.y+rect.extent.y-y,
							  rect.topLeft.x+rect.extent.x-cornerDiam+x2, 
							  rect.topLeft.y+rect.extent.y-y-1);
			}
		}
	}

	// restore the origin pen color
	VSetTextColor (FOREGROUNDCOLOR);
	SetDrawMode (DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawUpArrow
//
// DESCRIPTION: This routine draw a up direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/26/01	Initial Revision
//			Jerry	8/09/01	Add SOLID_TAIL, SOLID_SMALL style
////////////////////////////////////////////////////////////////////////
void VDrawUpArrow (int x, int y, int style)
{
	int		i;

	x = VPDAToSysXCoord (x);
	y = VPDAToSysXCoord (y);
	if ( style == SOLID_LARGE ) {	// up direction solid triangle
		for ( i = 8; i >= 0; i-- ) {
			drawline ( x+8-i, y+i, x+10+i, y+i );
		}
 	} else if ( style == DASH_LARGE ) {	// up direction triangle
		for ( i = 8; i >= 0; i-=2 ) {
			drawline ( x+8-i, y+i, x+10+i, y+i );
		}
	} else if ( style == SOLID_SMALL ) {	// up direction solid triangle
		for ( i = 4; i >= 0; i-- ) {
			drawline ( x+4-i, y+i, x+6+i, y+i );
		}
	} else if ( style == SOLID_TAIL ) {	// up direction arrow (with tail)
		for ( i = 8; i >= 6; i-- ) {
			drawline ( x+6, y+i, x+12, y+i );
		}
		for ( i = 5; i >= 0; i-- ) {
			drawline ( x+8-i, y+i, x+10+i, y+i );
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawDownArrow
//
// DESCRIPTION: This routine draw a down direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/26/01	Initial Revision
//			Jerry	8/09/01	Add SOLID_TAIL, SOLID_SMALL style
////////////////////////////////////////////////////////////////////////
void VDrawDownArrow (int x, int y, int style)
{
	int		i;
	
	x = VPDAToSysXCoord (x);
	y = VPDAToSysXCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 0; i <= 8; i++ ) {
			drawline ( x+i, y+i, x+18-i, y+i );
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 0; i <= 8; i+=2 ) {
			drawline ( x+i, y+i, x+18-i, y+i );
		}
	} else if ( style == SOLID_SMALL ) {
		for ( i = 0; i <= 4; i++ ) {
			drawline ( x+i, y+i, x+10-i, y+i );
		}
	} else if ( style == SOLID_TAIL ) {	// up direction arrow (with tail)
		for ( i = 0; i < 3; i++ ) {
			drawline ( x+6, y+i, x+12, y+i );
		}
		for ( i = 3; i <= 8; i++ ) {
			drawline ( x+i, y+i, x+18-i, y+i );
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawLeftArrow
//
// DESCRIPTION: This routine draw a left direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawLeftArrow (int x, int y, int style)
{
	int		i;

	x = VPDAToSysXCoord (x);
	y = VPDAToSysXCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 8; i >= 0; i-- ) {
			drawline ( x+i, y+8-i, x+i, y+10+i );
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 8; i >= 0; i-=2 ) {
			drawline ( x+i, y+8-i, x+i, y+10+i );
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawRightArrow
//
// DESCRIPTION: This routine draw a right direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawRightArrow (int x, int y, int style)
{
	int		i;
	
	x = VPDAToSysXCoord (x);
	y = VPDAToSysXCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 0; i <= 8; i++ ) {
			drawline ( x+i, y+i, x+i, y+18-i );
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 0; i <= 8; i+=2 ) {
			drawline ( x+i, y+i, x+i, y+18-i );
		}
	}
}

unsigned char VSetTextColor (unsigned char color)
{
	unsigned char	oldColor = tColor;

	tColor = color;
	return	oldColor;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawString
//
// DESCRIPTION: This routine clear entire client window and draw
//					 PDA outline.
//
// PARAMETERS:  (UInt16) x - the left coordinate to draw string
//					 (UInt16) y - the top coordinate to draw string
//					 (Char *) str - the string to draw
//					 (UInt32) length - lenght of string
//					 (Boolean) singleline - true if it's a single line
//							control, false if multiline
//					 (Boolean) background - false if normal background
//							true if invert background
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision
//			Jerry 8/02/01	Modify buffer to variable size
//			Jerry	8/17/01	Cancel singleline function
////////////////////////////////////////////////////////////////////////
void VDrawString( Coord x, Coord y,
                  const char *str,
                  UInt32 length,
						Boolean singleline,
						Boolean background,
						int mode)
{
	UInt16	index = 0, bindex = 0, sindex = 0, maxLength;

	// if background, change the pen to background color
	if ( background ) {
		VSetTextColor (BACKGROUNDCOLOR);
	}

	// stretch the coordinate to proper value
	if ( mode == COORD_STRETCH ) {	
		x = VPDAToSysXCoord(x);
		y = VPDAToSysYCoord(y);
	}

	// parse the input text 
	while (index < length) {
		if ( str[index] == 0 ) {
			break;
		} else if ( str[index] != 0x0a ) {
			bindex++;
		} else {
			maxLength = FntWordWrap (str+sindex, SCREENWIDTH);
			if ( maxLength < bindex )
				bindex = maxLength;
			VDrawChars (str+sindex, bindex, (Coord)x, (Coord)y, COORD_NORMAL);
			sindex += bindex;
			bindex = 0;
			if ( singleline ) {
				if ( background ) {
					VSetTextColor (FOREGROUNDCOLOR);
				}
				return;
			} else {
				y += FntCharHeight();
			}
		}
		index++;
	};

	if ( bindex > 0 ) {
		maxLength = FntWordWrap (str+sindex, SCREENWIDTH);
		if ( maxLength < bindex )
			bindex = maxLength;
		VDrawChars (str+sindex, bindex, (Coord)x, (Coord)y, COORD_NORMAL);
	}

	VSetTextColor (FOREGROUNDCOLOR);
}
 
double Vexp (double x)
{
//	return	exp (x);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrToLower
//
// DESCRIPTION: This routine convert all the characters in a string
//				to lowercase.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* Vstrlwr (Char *dst, const Char* src)
{
//	dst = strlwr (src);
	return	dst;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstricmp
//
// DESCRIPTION: This routine compare two strings.
//					 (Not care of upper or lower case)
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//
// RETURNED:    Returns 0 if the strings match.
//					 Returns a positive number if s1 sorts after s2.
//					 Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 Vstricmp (const Char *dst, const Char* src)
{
	return	strcasecmp (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrnicmp
//
// DESCRIPTION: This routine compare two strings out to n characters.
//					 (Not care of upper or lower case)
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//					 (UInt32) n - Length in bytes of txt to compare.
//
// RETURNED:    Returns 0 if the strings match.
//					 Returns a positive number if s1 sorts after s2.
//					 Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 Vstrnicmp (const Char *dst, const Char* src, UInt32 n)
{
	return	strncasecmp (dst, src, n);
}

FILE	*tmpFp;
void *VfopenTempFile()
{
	tmpFp = fopen ("WISTMPFILE", "wb+");
	return	tmpFp;
//	return	tmpfile();
}

void VRemoveTempFile ()
{
	unlink ("WISTMPFILE");
//	_rmtmp ();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetCurrentDirectory
//
// DESCRIPTION: This routine Get the current directory.
//
// PARAMETERS:  (char *) directory - Pointer to the buffer to store
//										directory.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VGetCurrentDirectory (Char *directory)
{
//	GetCurrentDirectory(256, directory);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetSystemTime
//
// DESCRIPTION: This routine Get the system time.
//
// PARAMETERS:  (DateTimeType *) datetime - Pointer to the DateTimeType
//												structure.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VGetSystemTime (DateTimeType *datetime)
{
	time_t	ctime;

	time(&ctime);
	TimSecondsToDateTime ((UInt32)ctime, datetime);
}

void VSetSystemTime (const DateTimeType *datetime)
{
	time_t	ctime;

	ctime = TimDateTimeToSeconds (datetime);
//	time(&ctime);
}

void WCloseAll ()
{
	int	i;
	Vfree (CurEvent);
	if ( GlobalText ) {
		Vfree (GlobalText);
		GlobalText = NULL;
	}

	for ( i = 0; i < 5; i++ ) {
		if ( memBM[i] ) {
			Vfree (memBM[i]);
		}
	}
}

// Below APIs are system relative API, there are 4 functions now.

unsigned short	tPadX=0, tPadY=0, oldPadX=0, oldPadY=0;
////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetTouchPadInput
//
// DESCRIPTION: This routine get the touch pad input in touch pad 
//					 coordinate system.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	10/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean GetTouchPadInput ()
{
	unsigned int count;
	short data[3];
	int bytes_read, i;

	// get touch pad data
	bytes_read = read(TouchPadDev,data,sizeof(data));
	if (bytes_read != sizeof(data)) {
		if ( !penDown ) {
			tPadX = -1;
			tPadY = -1;
			return	false;
		} else
			penDown = false;
	} else {
		long	stime, ctime=0;
		penDown = true;

		tPadX = 0;
		stime = clock ();
		do {
			bytes_read = read(TouchPadDev,data,sizeof(data));
			if ( bytes_read == sizeof(data) ) {
				oldPadX = data[0]&0xff0;
				oldPadY = (0xfff-data[1])&0xff0;
				if (tPadX == 0) {
					tPadX = oldPadX;
					tPadY = oldPadY;
				}
				if ( (Vabs(tPadX-oldPadX)<150) && (Vabs(tPadY-oldPadY)<150) ){
					tPadX = oldPadX;
					tPadY = oldPadY;
				}
			} else {
				break;
			}

			ctime = clock ();
		} while ( ctime < (stime+MINSYSTICKS) );
	}

	return	true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WPeekEventsDDK
//
// DESCRIPTION: This routine peek system event
//
// PARAMETERS:  
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WPeekEventsDDK(void)
{
	Int16	id;

	// no tap event occur, return
	if (!GetTouchPadInput ())	return;

	CurEvent->screenX = VTPADToPDAXCoord(tPadX);
	CurEvent->screenY = VTPADToPDAYCoord(tPadY);

#ifndef	HANDERA
	CurEvent->screenX = VSysToPDAXRes(CurEvent->screenX);
	CurEvent->screenY = VSysToPDAXRes(CurEvent->screenY);
#endif

	WPeekMouseEvent (penDown);

	// save the tap coordinate
	lastScreenX = CurEvent->screenX;
	lastScreenY = CurEvent->screenY;
}

int InitializeDisplayDev ()
{
	char	*env;
	int	size;
	unsigned char* video_ram;//, *zBuffer;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;

	if (!(env = (char *)getenv("FRAMEBUFFER")))
		env = "/dev/fb0";
	if ((DisplayDev = open(env,O_RDWR)) < 0) {
//		printf("Error opening %s:. Check kernel config\n",env);
		return -1;
	}
	if (ioctl(DisplayDev,FBIOGET_FSCREENINFO,&fb_fix) == -1 ||
       ioctl(DisplayDev,FBIOGET_VSCREENINFO,&fb_var) == -1) {
//		printf("Error reading screen info.\n");
		close(DisplayDev);
		return -1;
	}

	// Get pipe file buffer herer
	size = fb_fix.line_length * fb_var.yres+PIPESIZE;
	if ((video_ram = (char *)mmap(NULL,size,PROT_READ | PROT_WRITE,0,DisplayDev,0)) == NULL) {
//		printf("Error mmaping %s:\n",env);
		close(DisplayDev);
		return -1;
	}
//	printf("%s: allocated %d bytes @ 0x%p from %s (%dx%d)\n",env,size,video_ram,fb_fix.id,fb_var.xres,fb_var.yres);

	// pipe_ram at the end of video_ram
	pipe_ram = video_ram+fb_fix.line_length * fb_var.yres;
//	zBuffer = Vmalloc (fb_fix.line_length * fb_var.yres);

	display.area.uLeft = 0, display.area.uRight  = fb_var.xres;
	display.area.uTop  = 0, display.area.uBottom = fb_var.yres;
	display.pfnPutPixel = (fb_var.bits_per_pixel == 8)? DSC21_PutPixel256 : APDA_PutPixel2;
//	display.pfnUpdateScreen = APDA_UpdateScreen;
	display.pPrivate = video_ram;
//	display.pZBuffer = zBuffer;
//	display.size = fb_fix.line_length * fb_var.yres;

	return	0;
}

int InitializeTouchPadDev ()
{
	TouchPadDev = open("/dev/ts", O_NONBLOCK);
	if (TouchPadDev < 0) {
//		printf("Error %d opening touch panel\n", errno);
		return -1;
	}

	return	0;
}

int Initialize_System ()
{
	if ( InitializeDisplayDev () != errNone ) {
//		printf ("Screen initialize error\n");
		return	-1;
	}
	if ( InitializeTouchPadDev () != errNone ) {
//		printf ("Touch pad initialize error\n");
		return	-1;
	}

	// reset system counter
	sysHandle.count = 0;
	formCount = 0;
	// set the default draw mode to DRAW_SET
	SetDrawMode (DRAW_SET);

	return 0;
}

void Finalize_System ()
{
//	Vfree (display.pZBuffer);
}

void Calibrate_Tablet ()
{
	EventType	event;
	int	x1, y1, x2, y2, x3, y3;
	int	diffX1, diffX2, diffY1, diffY2;

	// if the difference of (top-left and center point) and 
	//	(right-bottom and center point) is too large,
	//	re-get the coordinate of this three points
	do {
		// if the distance of top-left and right-bottom point is too large,
		//	re-get the coordinate of this two points
		do {	
			// Calibrate the left top postion
			WClearScreen (SCREEN_DISPLAY);
			VDrawLine ( 10, 20, 30, 20, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			VDrawLine ( 20, 10, 20, 30, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			do {
				EvtGetEvent (&event, -1);
			} while (event.eType!=penUpEvent);
			x1 = tPadX;
			y1 = tPadY;

			// Calibrate the right bottom postion
			WClearScreen (SCREEN_DISPLAY);
			VDrawLine ( 130, 140, 150, 140, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
			VDrawLine ( 140, 130, 140, 150, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

			do {
				EvtGetEvent (&event, -1);
			} while (event.eType != penUpEvent);
			x2 = tPadX;
			y2 = tPadY;

			diffX1 = Vabs (VTPADToPDAXCoord((x2-x1)));
			diffY1 = Vabs (VTPADToPDAYCoord((y2-y1)));
			diffX1 = VSysToPDAXRes(diffX1);
			diffY1 = VSysToPDAYRes(diffY1);
		} while ( (diffX1 < (PDAWIDTH/8*5)) || (diffY1 < (PDAHEIGHT/8*5)) ||
					(diffX1 > (PDAWIDTH/8*7)) || (diffY1 > (PDAHEIGHT/8*7)) );

		// Calibrate the center postion
		WClearScreen (SCREEN_DISPLAY);
		VDrawLine ( 70, 80, 90, 80, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);
		VDrawLine ( 80, 70, 80, 90, THICK_LINE, BACKGROUNDCOLOR, PS_SOLID);

		do {
			EvtGetEvent (&event, -1);
		} while (event.eType != penUpEvent);
		x3 = tPadX;
		y3 = tPadY;

		diffX1 = Vabs (VTPADToPDAXCoord((x3-x1)));
		diffX2 = Vabs (VTPADToPDAXCoord((x2-x3)));
		diffY1 = Vabs (VTPADToPDAYCoord((y3-y1)));
		diffY2 = Vabs (VTPADToPDAYCoord((y2-y3)));
		diffX1 = VSysToPDAXRes(diffX1);
		diffY1 = VSysToPDAYRes(diffY1);
		diffX2 = VSysToPDAXRes(diffX2);
		diffY2 = VSysToPDAYRes(diffY2);
	} while ( (Vabs(diffX1-diffX2) > (PDAWIDTH/16)) || (Vabs(diffY1-diffY2) > (PDAHEIGHT/16)) );

	//	Calculate the new tablet value
	tPadDiffX = ((x3-x1)+(x2-x3))*tPadCaliWidth/(VPDAToSysXRes(140)-VPDAToSysXRes(20));
	tPadDiffY = ((y3-y1)+(y2-y3))*tPadCaliHeight/(VPDAToSysYRes(140)-VPDAToSysYRes(20));

	tBaseX = (x1*tPadCaliWidth/tPadDiffX)-VPDAToSysXRes(20);
	tBaseY = (y1*tPadCaliHeight/tPadDiffY)-VPDAToSysYRes(20);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WEvtGetEvent
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
void WEvtGetEvent(EventType *event, Int32 timeout)
{
	long	ctime, stime, timediff;

	//	set time difference
	if ( timeout == evtWaitForever )	
		timediff = SYSTEMTICKS;
	else
		timediff = timeout/(200/SYSTEMTICKS);

	// restrict the timediff shuttle
	if (timediff <	MINSYSTICKS)
		timediff = MINSYSTICKS;
	if (timediff >	MAXSYSTICKS)
		timediff = MAXSYSTICKS;

	stime = clock();
	//	wait to the time to get event
	do {
		ctime = clock ();
	} while ( ctime < (stime+timediff) );

	WPeekEventsDDK();
	WPopEvent(event);
}

void FreeResourceMemory ()
{
	int	i;
	WDestroyForm();
	WDestroyMenu();
	// free system handle list memory
	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( sysHandle.handle[i] ) {
			Vfree (sysHandle.handle[i]);
			sysHandle.handle[i] = NULL;
		}
	}

	if ( GlobalText ) {
		Vfree (GlobalText);
		GlobalText = NULL;
	}
	VReleaseRecord ();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinMain
//
// DESCRIPTION: This routine is real main program of program.
//
// PARAMETERS:  (HINSTANCE) _hInst - the instance of program
//				(HINSTANCE) _hPrevInst - the instance of previous program
//				(LPSTR) _lpCmdLine - the command line parameter.
//				(int) _nCmdShow - the showing status of program
//
// RETURNED:    Returns 0 if normal terminated, others if abnormal.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01	Initial Revision
//			Jerry	5/17/01	reset the CurEvent variable
//			Jerry	8/15/01	Initial GlobalText to NULL
////////////////////////////////////////////////////////////////////////
int main (int argc, char** argv)
{
	Widget gw;
	RectangleType	rect;

	CurEvent = (EventType *) malloc (sizeof (EventType));
	if ( !CurEvent )	return	-1;
	memset (CurEvent, 0, sizeof (EventType));

	if ( Initialize_System () < 0 )
		return	-1;

        // draw startup screen
	WDrawStartUpScreen ();
	VDrawBitmap (40,40,"wiscore.bmp");

	// Initialize handwriting engine
	Vmemset (&gw, 0, sizeof(Widget));
	Initialize_recorder (gw);

        // run application manager
	ApplicationManager ();

        // finalize system
	Finalize_recorder ();
	Finalize_System ();

	WClearScreen (SCREEN_ALL);
	free (CurEvent);

	return	0;
}
