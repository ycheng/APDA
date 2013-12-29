#ifndef __FONT_H__
#define __FONT_H__

typedef struct {
	Int16 fontType; 			// font type
	Int16 firstChar; 			// ASCII code of first character
	Int16 lastChar; 			// ASCII code of last character
	Int16 maxWidth; 			// maximum character width
	Int16 kernMax; 			// negative of maximum character kern
	Int16 nDescent; 			// negative of descent
	Int16 fRectWidth; 		// width of font rectangle
	Int16 fRectHeight; 		// height of font rectangle
	Int16 owTLoc; 				// offset to offset/width table
	Int16 ascent; 				// ascent
	Int16 descent; 			// descent
	Int16 leading; 			// leading
	Int16 rowWords; 			// row width of bit image / 2
} FontType;

typedef FontType *FontPtr;

typedef FontPtr *FontTablePtr;


#endif // __FONT_H__

