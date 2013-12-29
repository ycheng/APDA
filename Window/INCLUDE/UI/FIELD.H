#ifndef __FIELD_H__
#define __FIELD_H__


typedef struct {
	UInt16 usable			:1;	// Set if part of ui 
	UInt16 editable		:1;	// Set if editable
	UInt16 visible			:1;	// Set if drawn, used internally
	UInt16 singleLine		:1;	// Set if only a single line is displayed
	UInt16 hasFocus      :1;   // Set if the field has the focus
	UInt16 dynamicSize	:1;   // Set if height expands as text is entered
	UInt16 insPtVisible	:1;	// Set if the ins pt is scolled into view
	UInt16 dirty			:1;	// Set if user modified
	UInt16 underlined		:2;	// text underlined mode
	UInt16 justification	:2;	// text alignment
	UInt16 autoShift		:1;	// Set if auto case shift
	UInt16 hasScrollBar	:1;	// Set if the field has a scroll bar
	UInt16 numeric			:1;	// Set if numeric, digits and secimal separator only
} FieldAttrType;

typedef FieldAttrType *FieldAttrPtr;

typedef struct {
  UInt16	start;			// position in text string of first char.
  UInt16	length;			// number of character in the line
} LineInfoType;

typedef LineInfoType *LineInfoPtr;

typedef struct FieldType {
	UInt16				id;
	RectangleType		rect;
	FieldAttrType		attr;
	Char 					*text;					// pointer to the start of text string 
	MemHandle			textHandle;				// block the contains the text string
	LineInfoPtr			lines;
	UInt16				textLen;
	UInt16				textBlockSize;
	UInt16				maxChars;
	UInt16				selFirstPos;
	UInt16				selLastPos;
	UInt16				insPtXPos;
	UInt16				insPtYPos;
	UInt16				firstLine;
	FontID				fontID;
	UInt8 				reserved;
} FieldType;


typedef FieldType *FieldPtr;					// deprecated, use FieldType *

#endif // __FIELD_H__
