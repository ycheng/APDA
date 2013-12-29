#ifndef __EVENT_H__
#define __EVENT_H__

// keyDownEvent modifers
#define shiftKeyMask			0x0001
#define capsLockMask			0x0002
#define numLockMask			0x0004
#define commandKeyMask		0x0008
#define optionKeyMask		0x0010
#define controlKeyMask		0x0020
#define autoRepeatKeyMask	0x0040		// True if generated due to auto-repeat
#define doubleTapKeyMask	0x0080		// True if this is a double-tap event
#define poweredOnKeyMask	0x0100		// True if this is a double-tap event

// Event timeouts
#define 	evtWaitForever		-1


//#define EventPtr	Word *
//#define EventType	Word

typedef struct VRect {
   Coord left;
   Coord top;
   Coord right;
   Coord bottom;
} VRect;



typedef struct _GenericEventType {
	UInt16         datum[8];
   }_GenericEventType;

struct _PenUpEventType {
   PointType      start;            // display coord. of stroke start
   PointType      end;              // display coord. of stroke start
   };

typedef struct _KeyDownEventType {
   WChar          chr;              // ascii code
   UInt16         keyCode;          // virtual key code
   UInt16         modifiers;
   }_KeyDownEventType;

struct _WinEnterEventType {
   WinHandle      enterWindow;
   WinHandle      exitWindow;
   };

struct _WinExitEventType {
   WinHandle      enterWindow;
   WinHandle      exitWindow;
   };

struct _TSMConfirmType {
	Char *			yomiText;
	UInt16			formID;
   };

struct _TSMFepButtonType {
	UInt16			buttonID;
   };

struct _TSMFepModeEventType {
	UInt16         mode;					// DOLATER kwk - use real type for mode?
   };


typedef enum eventsEnum {
	nilEvent = 0,				// system level
	penDownEvent,				// system level
	penUpEvent,					// system level
	penMoveEvent,				// system level
	keyDownEvent,				// system level
	winEnterEvent,				// system level
	winExitEvent,				// system level
	ctlEnterEvent,
	ctlExitEvent,
	ctlSelectEvent,
	ctlRepeatEvent,
	lstEnterEvent,
	lstSelectEvent,
	lstExitEvent,
	popSelectEvent,
	fldEnterEvent,
	fldHeightChangedEvent,
	fldChangedEvent,
	tblEnterEvent,
	tblSelectEvent,
	daySelectEvent,
	menuEvent,
	appStopEvent = 22,			// system level
	frmLoadEvent,
	frmOpenEvent,
	frmGotoEvent,
	frmUpdateEvent,
	frmSaveEvent,
	frmCloseEvent,
	frmTitleEnterEvent,
	frmTitleSelectEvent,
	tblExitEvent,
	sclEnterEvent,
	sclExitEvent,
	sclRepeatEvent,
	tsmConfirmEvent = 35,		// system level
	tsmFepButtonEvent,			// system level
	tsmFepModeEvent,				// system level
	
	// add future UI level events in this numeric space
	// to save room for new system level events
	menuCmdBarOpenEvent = 0x0800,
	menuOpenEvent,
	menuCloseEvent,
	frmGadgetEnterEvent,
	frmGadgetMiscEvent,

	// <chg 2-25-98 RM> Equates added for library events
	firstINetLibEvent = 0x1000,
	firstWebLibEvent = 0x1100,
	
	// <chg 10/9/98 SCL> Changed firstUserEvent from 32767 (0x7FFF) to 0x6000
	// Enums are signed ints, so 32767 technically only allowed for ONE event.
	firstUserEvent = 0x6000,
	sysExitEvent = 0x9999
} eventsEnum;

// The event record.
typedef struct EventType {
   eventsEnum		eType;
   Boolean		penDown;
   UInt8        tapCount;
   Int16        screenX;
   Int16        screenY;
   union data {

      struct _GenericEventType		generic;
      struct _PenUpEventType        penUp;
      struct _KeyDownEventType      keyDown;
      struct _WinEnterEventType     winEnter;
      struct _WinExitEventType      winExit;
      struct _TSMConfirmType			tsmConfirm;
      struct _TSMFepButtonType		tsmFepButton;
      struct _TSMFepModeEventType	tsmFepMode;

      struct ctlRepeat {
         char				*pControl;
         UInt16				controlID;
         UInt32				time;
         UInt16				value;		// used for slider controls only
         } ctlRepeat;

      struct ctlEnter {
         UInt16				controlID;
         ControlType		*pControl;
         } ctlEnter;

      struct ctlSelect {
         UInt16				controlID;
         struct ControlType *pControl;
         Boolean			on;
         UInt8				reserved1;
         UInt16				value;		// used for slider controls only
         } ctlSelect;

      struct fldEnter {
         UInt16				fieldID;
         struct FieldType 	*pField;
         } fldEnter;

      struct fldHeightChanged {
         UInt16				fieldID;
         struct FieldType 	*pField;
         Int16				newHeight;
         UInt16				currentPos;
         } fldHeightChanged;

      struct fldChanged {
         UInt16				fieldID;
         struct FieldType 	*pField;
         } fldChanged;

      struct fldExit {
         UInt16				fieldID;
         struct FieldType	*pField;
         } fldExit;

      struct lstEnter {
         UInt16				listID;
         struct ListType 	*pList;
         Int16				selection;
         } lstEnter;

      struct lstExit {
         UInt16				listID;
         struct ListType 	*pList;
         } lstExit;

      struct lstSelect {
         UInt16				listID;
         struct ListType 	*pList;
         Int16				selection;
         } lstSelect;

      struct tblEnter {
         UInt16     tableID;
         TableType	*pTable;
         Int16      row;
         Int16      column;
         } tblEnter;

      struct tblExit {
         UInt16				tableID;
         struct TableType 	*pTable;
         Int16				row;
         Int16				column;
         } tblExit;

      struct tblSelect {
         UInt16				tableID;
         struct TableType 	*pTable;
         Int16				row;
         Int16				column;
         } tblSelect;

      struct frmLoad {
         UInt16				formID;
         } frmLoad;

      struct frmOpen {
         UInt16				formID;
         } frmOpen;

      struct frmGoto {
         UInt16				formID;
         UInt16				recordNum;        // index of record that contain a match
         UInt16				matchPos;         // postion in record of the match.
         UInt16				matchLen;         // length of match.
         UInt16				matchFieldNum;    // field number string was found int
         UInt32				matchCustom;      // application specific info
         } frmGoto;

      struct frmClose {
         UInt16				formID;
         } frmClose;

      struct frmUpdate {
         UInt16				formID;
         UInt16				updateCode;       // Application specific
         } frmUpdate;

      struct frmTitleEnter {
         UInt16				formID;
         } frmTitleEnter;

      struct frmTitleSelect {
         UInt16				formID;
         } frmTitleSelect;

      struct daySelect {
         struct DaySelectorType *pSelector;
         Int16             selection;
         Boolean           useThisDate;
         UInt8             reserved1;
         } daySelect;

      struct menu {
         UInt16            itemID;
         } menu;

      struct popSelect {
         UInt16				controlID;
         ControlType *controlP;
         UInt16				listID;
         ListType 	*listP;
         Int16				selection;
         Int16				priorSelection;
         } popSelect;

      struct sclEnter {
         UInt16				scrollBarID;
         struct ScrollBarType *pScrollBar;
         } sclEnter;

      struct sclExit {
         UInt16            scrollBarID;
         struct ScrollBarType *pScrollBar;
         Int16             value;
         Int16             newValue;
         } sclExit;

      struct sclRepeat {
         UInt16            scrollBarID;
         struct ScrollBarType *pScrollBar;
         Int16             value;
         Int16             newValue;
         Int32             time;
         } sclRepeat;

		struct menuCmdBarOpen {
			Boolean preventFieldButtons;  // set to stop the field from automatically adding cut/copy/paste
			UInt8   reserved;					// alignment padding
			} menuCmdBarOpen;
		
		struct menuOpen {
			UInt16				menuRscID;
			struct MenuBarType *pMenu;
			Int16				cause;
			} menuOpen;
/*		
		struct gadgetEnter {
         UInt16            gadgetID;			// must be same as gadgetMisc
         struct FormGadgetType *	gadgetP;		// must be same as gadgetMisc
			} gadgetEnter;
			
		struct gadgetMisc {
         UInt16            gadgetID;			// must be same as gadgetEnter
         struct FormGadgetType *	gadgetP;		// must be same as gadgetEnter
         UInt16				selector;
         void *				dataP;
			} gadgetMisc;
*/			
      } data;

} EventType;

typedef EventType *EventPtr;

#endif // __EVENT_H__
