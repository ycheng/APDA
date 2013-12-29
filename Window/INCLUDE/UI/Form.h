#ifndef __FORM_H__
#define __FORM_H__

#define	LABEL				3
#define BUTTON				4
#define CHECKBOX			5
#define POPUPTRIGGER		6
#define FIELD				7
#define TABLE				8
#define	REPEATBUTTON		10
#define	PUSHBUTTON			11
#define	SELECTORTRIGGER		12
#define	LIST				20

#define	MENU				100

#define noFocus 0xffff

// Types of object in a dialog box
enum formObjects {
	frmFieldObj,
	frmControlObj,
	frmListObj,
	frmTableObj,
	frmBitmapObj,
	frmLineObj,
	frmFrameObj,
	frmRectangleObj,
	frmLabelObj,
	frmTitleObj,
	frmPopupObj,
	frmGraffitiStateObj,
	frmGadgetObj,
	frmScrollBarObj };
typedef enum formObjects FormObjectKind;
	
typedef struct {
	Word usable			:1;	// Set if part of ui 
} FormObjAttrType;


typedef struct {
	FormObjAttrType			attr;
	PointType					pos;
	Word		     				rscID;
} FormBitmapType;

typedef struct {
	Word							id;
	PointType					pos;
	FormObjAttrType			attr;
	FontID						fontID;
	Char *						text;
} FormLabelType;


typedef struct {
	RectangleType				rect;
	Char *						text;
} FormTitleType;


typedef struct {
	Word							controlID;
	Word							listID;
} FormPopupType;


typedef struct {
	PointType					pos;
} FrmGraffitiStateType;

typedef struct {
	Word				id;
	FormObjAttrType			attr;
	RectangleType				rect;
	VoidPtr			     		data;
} FormGadgetType;

typedef union {
	void *                  ptr;
	FieldType *					field;
	ControlType *				control;
	ListType	*					list;
	TableType *					table;
	FormBitmapType *			bitmap;
//	FormLineType *				line;
//	FormFrameType *			frame;
//	FormRectangleType *		rectangle;
	FormLabelType *			label;
	FormTitleType *			title;	
	FormPopupType *			popup;
	FrmGraffitiStateType *  grfState;
	FormGadgetType *			gadget;
	ScrollBarType *			scrollBar;
} FormObjectType;

typedef struct {
	FormObjectKind				objectType;
	FormObjectType				object;
} FormObjListType;


typedef struct {
	Word usable				:1;	// Set if part of ui 
	Word enabled			:1;	// Set if interactable (not grayed out)
	Word visible			:1;	// Set if drawn, used internally
	Word dirty				:1;	// Set if dialog has been modified
	Word saveBehind		:1;	// Set if bits behind form are save when form ids drawn
	Word graffitiShift	:1;   // Set if graffiti shift indicator is supported
	Word reserved			:11;
} FormAttrType;


typedef Boolean FormEventHandlerType (EventPtr eventP);

typedef FormEventHandlerType * FormEventHandlerPtr;

typedef struct {
	Word							formId;
   FormAttrType				attr;
	Word							focus;
	Word							defaultButton;
	Word							helpRscId;
	Word							menuRscId;
	Word							numObjects;
	FormObjListType *			objects;
	WinHandle	       		bitsBehindForm;
	WindowType					window;
	FormEventHandlerPtr		handler;
} FormType;


typedef FormType * FormPtr;


typedef struct FormActiveStateType {
	UInt16	data[11];
} FormActiveStateType;


#endif // __FORM_H__
