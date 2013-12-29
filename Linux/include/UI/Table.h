#ifndef __TABLE_H__
#define __TABLE_H__

// Display style of a table item
//
enum tableItemStyles { checkboxTableItem, 
                       customTableItem, 
                       dateTableItem, 
                       labelTableItem,
                       numericTableItem,
                       popupTriggerTableItem,
                       textTableItem,
                       textWithNoteTableItem,
                       timeTableItem,
                       narrowTextTableItem
                       };
typedef enum tableItemStyles TableItemStyleType;

typedef struct {
	TableItemStyleType	itemType;		
	FontID				fontID;		// font for drawing text
	Int16				intValue;
	Char				*ptr;
} TableItemType;
typedef TableItemType *TableItemPtr;


// Draw item callback routine prototype, used only by customTableItem.
typedef void TableDrawItemFuncType  
		(void *tableP, Int16 row, Int16 column, RectangleType *bounds);

typedef TableDrawItemFuncType *TableDrawItemFuncPtr;

// Load data callback routine prototype
typedef Err TableLoadDataFuncType 
		(void *tableP, Int16 row, Int16 column, Boolean editable, 
		MemHandle * dataH, Int16 *dataOffset, Int16 *dataSize, FieldPtr fld);

typedef TableLoadDataFuncType *TableLoadDataFuncPtr;


// Save data callback routine prototype
typedef	Boolean TableSaveDataFuncType
		(void *tableP, Int16 row, Int16 column);

typedef TableSaveDataFuncType *TableSaveDataFuncPtr;


typedef struct {
	Coord						width;					// width in pixels
	Coord						spacing;					// space after column
	UInt32						reserved1 		: 13;
	UInt32						masked			: 1;  // if both row + column masked, draw only grey box
	UInt32						editIndicator	: 1;
	UInt32						usable 			: 1;
	UInt32						reserved2		: 16;
	TableDrawItemFuncPtr		drawCallback;
	TableLoadDataFuncPtr		loadDataCallback;
	TableSaveDataFuncPtr		saveDataCallback;

} TableColumnAttrType;


typedef struct {
	UInt16						id;
	Coord						height;					// row height in pixels
	UInt32						data;

	UInt16						reserved1		: 7;
	UInt16						usable			: 1;
	UInt16						reserved2		: 4;
	UInt16						masked			: 1;  // if both row + column masked, draw only grey box
	UInt16						invalid			: 1;	// true if redraw needed
	UInt16 						staticHeight	: 1;  // Set if height does not expands as text is entered
	UInt16						selectable		: 1;

	UInt16						reserved3;
} TableRowAttrType;


typedef struct {
	UInt16 						visible:1;			// Set if drawn, used internally
    UInt16 						editable:1;			// Set if editable
	UInt16 						editing:1;			// Set if in edit mode
	UInt16 						selected:1;			// Set if the current item is selected
	UInt16						hasScrollBar:1;	// Set if the table has a scroll bar
	UInt16						reserved:11;
} TableAttrType;


typedef struct TableType {
	UInt16					id;
	RectangleType			bounds;
	Int16					numColumns;
	Int16					numRows;
	Int16					currentRow;
	Int16					currentColumn;
	Int16					topRow;
	TableColumnAttrType *	columnAttrs;
	TableRowAttrType *    	rowAttrs;
	TableItemPtr			items;
	TableAttrType			attr;
	FieldType				currentField;
} TableType;

typedef TableType *TablePtr;

#endif	// __TABLE_H__
