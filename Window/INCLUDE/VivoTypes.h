#ifndef __VIVOTYPES_H__
#define __VIVOTYPES_H__

// Fixed size data types
typedef char				Char;
typedef signed char		Int8;

typedef signed short		Int;	
typedef signed short		Int16;	
typedef signed short		Coord;		// screen/window coordinate
typedef signed short		Short;

typedef signed long		Int32;
typedef signed long		Long;

typedef unsigned char	UInt8;
typedef unsigned char 	Byte;
typedef unsigned char 	BYTE;
typedef unsigned char	UChar;
typedef UInt8				IndexedColorType;

typedef unsigned short  UInt;
typedef unsigned short  UInt16;
typedef signed short		SWord;
typedef unsigned short  Word;
typedef unsigned short	Boolean;
typedef unsigned short	WChar;		// 'wide' int'l character type.
typedef unsigned short	Err;

#ifndef	LINUX
typedef unsigned short	u_short;
#endif

typedef unsigned long   UInt32;
typedef unsigned long   ULong;
typedef signed long		SDWord;
typedef unsigned long	LocalID;		// local (card relative) chunk ID
typedef unsigned long	DWord;

// Logical data types


typedef Char*			CharPtr;
typedef UChar*			UCharPtr;
typedef Byte*			BytePtr;
typedef Word*			WordPtr;

typedef	UInt16	DmResID;
// define for hand writing
typedef	Char *Widget;

typedef unsigned char	keycode;
typedef Boolean	WinDrectionType;
typedef Word		FrameType;
typedef UInt8		IndexColorType;
typedef void		*VHINSTANCE;
typedef void		*VHWND;

#ifndef TRUE
#define TRUE 		(0==0)
#define FALSE 		(0!=0)
#endif
#ifndef NULL
#define NULL    ((void *)0)
#endif

typedef void*		VoidPtr;
typedef VoidPtr*	MemHandle;	// global handle
typedef MemHandle	VoidHand;
typedef void*		MemPtr;		// global pointer
typedef char*		Ptr;					// global pointer
typedef Ptr*		Handle;				// global handle

enum fontID { 
	stdFont = 0x00,					// Small font used for the user's writing.  Shows a good amount
	boldFont, 							// Small font.  Bold for easier reading.  Used often for ui.
	largeFont,							// Larger font for easier reading.  Shows a lot less.
	symbolFont,							// Various ui images like check boxes and arrows
	symbol11Font, 						// Larger various ui images
	symbol7Font,						// Smaller various ui images
	ledFont,								// Calculator specific font
	largeBoldFont,						// A thicker version of the large font.  More readable.
	fntAppFontCustomBase = 0x80	// First available application-defined font ID
};

typedef enum fontID FontID;

typedef struct AbsRectType {
  Coord left;
  Coord top;
  Coord right;
  Coord bottom;
} AbsRectType;

typedef struct PointType {
  Coord x;
  Coord y;
} PointType;

typedef struct RectangleType {
  PointType  topLeft;
  PointType  extent;
} RectangleType;

typedef RectangleType		*RectanglePtr;


typedef struct WBitmap {
	long	offset;
	long	type;
	long	width;
	long	height;
	long	widthBytes;
	unsigned short	planes;
	unsigned short	bitsPixel;
} WBitmap;

// system handle structure
typedef struct SYSHandle {
	void		*handle[256];
	UInt32	size[256];
	UInt16	count;
	Boolean	locked[256];
} SYSHandle;

enum DrawMode {
  DRAW_SET = 0,
  DRAW_XOR,
} copyMode;


#endif // __VIVOTYPES_H__
