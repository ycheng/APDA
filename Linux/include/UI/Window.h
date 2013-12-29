#ifndef __WINDOW_H__
#define __WINDOW_H__


enum directions { up = 0, down, left, right };
typedef enum directions DirectionType;
typedef DirectionType	WinDirectionType;

// transfer modes for color drawing
typedef enum {winPaint, winErase, winMask, winInvert, winOverlay, winPaintInverse, winSwap} WinDrawOperation;

typedef enum { blackPattern, whitePattern, grayPattern, customPattern } PatternType;

// grayUnderline means dotted current foreground color
// solidUnderline means solid current foreground color
// colorUnderline redundant, use solidUnderline instead
typedef enum { noUnderline, grayUnderline, solidUnderline, colorUnderline } UnderlineModeType;

typedef UInt8 CustomPatternType [8];		// 8x8 1-bit deep pattern

//  Standard Frame Types
#define noFrame         0
#define simpleFrame     1
#define rectangleFrame  1
#define roundFrame      0x0401          // corner = 7, frame = 1
#define boldRoundFrame  0x0702          // corner = 7, frame = 2
#define popupFrame      0x0205          // corner = 2,  frame = 1, shadow = 1
#define dialogFrame     0x0302          // corner = 3,  frame = 2
#define menuFrame       popupFrame

//-----------------------------------------------
// Draw state structures.
//-----------------------------------------------
typedef struct DrawStateType {
	WinDrawOperation	transferMode;
	PatternType			pattern;
	UnderlineModeType	underlineMode;
	FontID				fontId;
	FontPtr				font;
	CustomPatternType	patternData;
	IndexedColorType	foreColor;
	IndexedColorType	backColor;
	IndexedColorType	textColor;
	UInt8					reserved;	
} DrawStateType;


typedef union FrameBitsType {
	struct {
		UInt16 cornerDiam		: 8;				// corner diameter, max 38
		UInt16 reserved_3		: 3; 
		UInt16 threeD			: 1;				// Draw 3D button    
		UInt16 shadowWidth	: 2;				// Width of shadow
		UInt16 width			: 2;				// Width frame
	} bits;
	UInt16 word;									// IMPORTANT: INITIALIZE word to zero before setting bits!
} FrameBitsType;

typedef struct WindowFlagsType {
	UInt16 format:1;      // window format:  0=screen mode; 1=generic mode
	UInt16 offscreen:1;   // offscreen flag: 0=onscreen ; 1=offscreen
	UInt16 modal:1;       // modal flag:     0=modeless window; 1=modal window
	UInt16 focusable:1;   // focusable flag: 0=non-focusable; 1=focusable
	UInt16 enabled:1;     // enabled flag:   0=disabled; 1=enabled
	UInt16 visible:1;     // visible flag:   0-invisible; 1=visible
	UInt16 dialog:1;      // dialog flag:    0=non-dialog; 1=dialog
	UInt16 freeBitmap:1;	 // free bitmap w/window: 0=don't free, 1=free
	UInt16 reserved :8;
} WindowFlagsType;

typedef struct WindowType {
  Coord							displayWidthV20;		// use WinGetDisplayExtent instead
  Coord							displayHeightV20;		// use WinGetDisplayExtent instead
  void *							displayAddrV20;		// use the drawing functions instead
  WindowFlagsType				windowFlags;
  RectangleType				windowBounds;
  AbsRectType					clippingBounds;
  BitmapPtr						bitmapP;
  FrameBitsType   			frameType;
  DrawStateType *				drawStateP;				// was GraphicStatePtr
  struct WindowType *		nextWindow;
} WindowType;

typedef WindowType *WinPtr;
typedef WindowType *WinHandle;




typedef struct InsPtStateType {
	Boolean		enabled;
	Int16			height;
	PointType	pos;
} InsPtStateType;

typedef struct PenCalibrateType {
	PointType	digTopLeftP;
	PointType	digBotRightP;
	PointType	scrTopLeftP;
	PointType	scrBotRightP;
} PenCalibrateType;


#endif		// __WINDOW_H__
