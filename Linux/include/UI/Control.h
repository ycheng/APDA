#ifndef __CONTROL_H__
#define __CONTROL_H__

typedef struct {
	UInt16 usable         :1;		// set if part of ui 
	UInt16 enabled        :1;		// set if interactable (not grayed out)
	UInt16 visible        :1;		// set if drawn (set internally)
	UInt16 on             :1;		// set if on (checked)
	UInt16 leftAnchor     :1;		// set if bounds expand to the right
	                           // clear if bounds expand to the left
	UInt16 frame          :3;
} ControlAttrType;

enum controlStyles {buttonCtl, pushButtonCtl, checkboxCtl, popupTriggerCtl,
							 selectorTriggerCtl, repeatingButtonCtl, labelCtl };
typedef enum controlStyles ControlStyleType;


typedef struct {
	Word					id;
	RectangleType		bounds;
	ControlAttrType	attr;
	CharPtr				text;	
	ControlStyleType	style;
	FontID				font;
	Byte					group;
} ControlType;

typedef struct GraphicControlType {
	Word					id;
	RectangleType		bounds;
	DmResID				bitmapID;
	DmResID				selectedBitmapID;
	ControlAttrType	attr;
	ControlStyleType	style;
	FontID				unused;
	Byte					group;
	Byte					reserved;
} GraphicControlType;

typedef struct {
	Word					id;
	RectangleType		bounds;
	DmResID				thumbID;
	DmResID				backgroundID;
	ControlAttrType	attr;
	ControlStyleType	style;
	Byte					reserved;
	Int16					minValue;
	Int16					maxValue;
	Int16					pageSize;
	Int16					value;
	MemPtr				activeSliderP;
} SliderControlType;


typedef ControlType *ControlPtr;



#endif // __CONTROL_H__
