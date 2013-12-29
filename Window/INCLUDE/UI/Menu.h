#ifndef __MENU_H__
#define __MENU_H__


typedef struct {
	Word					id;				// id of the menu item
	Char					command;			// command key
	UInt8					hidden: 1;
	UInt8					reserved: 7;
	CharPtr					itemStr;			// string to be displayed
} MenuItemType;


typedef struct {
	WinHandle				menuWin;			// window of pull-down menu
	RectangleType			bounds;			// bounds of the pulldown
	WinHandle				bitsBehind;		// saving bits behind pull-down menu
	RectangleType			titleBounds;	// bounds of the title in menu bar
	CharPtr					title;			// menu title displayed in menu bar
	Word						numItems;		// number of items in the menu
	MenuItemType *			items;			// array of menu items
} MenuPullDownType;

typedef MenuPullDownType * MenuPullDownPtr;

typedef struct {
	Word visible			:1;			// Set if menu bar is drawn
	Word commandPending	:1;			// Set if next key is a command
	Word insPtEnabled	:1;			// Set if insPt was on when menu was drawn
} MenuBarAttrType;


typedef struct {
	WinHandle				barWin;			// window of menu bar
	WinHandle				bitsBehind;		// saving bits behind menu bar
	WinHandle				savedActiveWin;
	WinHandle				bitsBehindStatus;
	MenuBarAttrType 		attr;
	Word						id;
	SWord						curMenu;			// current menu or -1 if none
	SWord						curItem;			// current item in curMenu, -1 if none
	SDWord					commandTick;	//
	SWord						numMenus;		// number of menus
	MenuPullDownPtr  		menus;			// array of menus
} MenuBarType;

typedef MenuBarType * MenuBarPtr;


#endif // __MENU_H__
