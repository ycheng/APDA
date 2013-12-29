#ifndef __SCROLLBAR_H__
#define __SCROLLBAR_H__

//#include <PalmTypes.h>
//#include <CoreTraps.h>

//#include <Rect.h>
//#include <Event.h>

typedef enum { sclUpArrow, sclDownArrow, sclUpPage, sclDownPage, sclCar } 
	ScrollBarRegionType;


typedef struct {
	UInt16 usable			:1;		// Set if part of ui 
	UInt16 visible			:1;		// Set if drawn, used internally
	UInt16 hilighted		:1;		// Set if region is hilighted
	UInt16 shown			:1;		// Set if drawn and maxValue > minValue
	UInt16 activeRegion	:4;		// ScrollBarRegionType
} ScrollBarAttrType;


typedef struct ScrollBarType {
	UInt16				id;
	RectangleType		bounds;
	ScrollBarAttrType	attr;
	Int16					value;
	Int16					minValue;
	Int16					maxValue;
	Int16					pageSize;
	Int16					penPosInCar;
	Int16					savePos;
} ScrollBarType;

typedef ScrollBarType *ScrollBarPtr;


#endif //__SCROLLBAR_H__
