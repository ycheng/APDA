#ifndef __LIST_H__
#define __LIST_H__

#define noListSelection    		0x0ffff

typedef struct {
	UInt16 usable				:1;		// set if part of ui 
	UInt16 enabled				:1;		// set if interactable (not grayed out)
	UInt16 visible				:1;		// set if drawn
    UInt16 poppedUp			:1;     	// set if choices displayed in popup win.
	UInt16 hasScrollBar		:1;		// set if the list has a scroll bar
	UInt16 search				:1;		// set if incremental search is enabled
	UInt16 reserved			:2;
} ListAttrType;

// Load data callback routine prototype
typedef void ListDrawDataFuncType (Int16 itemNum, RectangleType *bounds, 
	Char **itemsText);
	
typedef ListDrawDataFuncType *ListDrawDataFuncPtr;

typedef struct ListType {
	UInt16					id;
	RectangleType			bounds;
	ListAttrType			attr;
	Char *					*itemsText;
	Int16						numItems;        		// number of choices in the list
	Int16 	  				currentItem;     		// currently display choice
	Int16   					topItem;         		// top item visible when poped up
	FontID           		font;						// font used to draw list
	UInt16 					reserved;
	WinHandle   			popupWin;				// used only by popup lists
	ListDrawDataFuncPtr	drawItemsCallback;	// 0 indicates no function
} ListType;

typedef ListType *ListPtr;


#endif // __LIST_H__
