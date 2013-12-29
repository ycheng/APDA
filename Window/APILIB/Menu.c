#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#define	ALLMENU			0
#define	SUBMENU			1

Boolean			MenuActive = FALSE;
extern UInt16		menuCount;
extern MenuBarType		**menuPtr;
MenuBarType		*ActiveMenu=NULL;
Int16				lastMenuIndex, lastMenuItemIndex;

#define	menuItemWidth	35
#define	subMenuStartX	5


////////////////////////////////////////////////////////////////////////
// FUNCTION:    VCheckHitMenuItem (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check is the current mouse click on the
//				menu item
//
// PARAMETERS:  (UInt16) x - the current mouse click coordinate
//              (UInt16) y - the current mouse click coordinate
//
// RETURNED:    true if click on the menu item, false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/29/01	Initial Revision
//			Jerry 5/15/01	Modify to use ActiveMenu
////////////////////////////////////////////////////////////////////////
Boolean VCheckHitMenuItem(UInt16 x, UInt16 y)
{
	UInt16		curMenu=ActiveMenu->curMenu, curItem;
	UInt16		StartX, StartY, EndX, EndY;

	lastMenuItemIndex = ActiveMenu->curItem;
	if ( (y > 0) && (y < ActiveMenu->menus[curMenu].bounds.topLeft.y) ) {
		if ( (x > subMenuStartX) && 
			(x < ActiveMenu->numMenus*menuItemWidth+subMenuStartX) ) {
			lastMenuIndex = ActiveMenu->curMenu;
			ActiveMenu->curMenu = (x-subMenuStartX)/menuItemWidth;
			ActiveMenu->curItem = -1;

			return	TRUE;
		}
	} else {
		y = VPDAToSysYCoord (y);
		StartX = ActiveMenu->menus[curMenu].bounds.topLeft.x;
		StartY = VPDAToSysYCoord((ActiveMenu->menus[curMenu].bounds.topLeft.y+FntLineHeight()/4));
		EndX = StartX + ActiveMenu->menus[curMenu].bounds.extent.x;
		EndY = StartY + ActiveMenu->menus[curMenu].bounds.extent.y+VPDAToSysYCoord((FntLineHeight()/4));

		if ( (x > StartX) && (x < EndX) &&
			 (y > StartY) && (y < EndY) ) {
			curItem = (y-StartY)/FntLineHeight();
			if ( curItem >= ActiveMenu->menus[curMenu].numItems )
				curItem = ActiveMenu->menus[curMenu].numItems-1;
			if ( Vstricmp (ActiveMenu->menus[curMenu].items[curItem].itemStr, "SEPARATOR")!=0 ) {
				ActiveMenu->curItem = curItem;
				return	TRUE;
			} else {
				ActiveMenu->curItem = -1;
				return	TRUE;
			}
		}
	}

	ActiveMenu->curItem = -1;
	return	FALSE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VCheckHitMenu (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine check is the current mouse click on the
//				menu button.
//
// PARAMETERS:  (UInt16) x - the current mouse click coordinate
//              (UInt16) y - the current mouse click coordinate
//
// RETURNED:    true if click on the menu button, false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/09/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean VCheckHitMenu(UInt16 x, UInt16 y)
{
	if ((x>=MENUSX)&&(y>=MENUSY)&&(x<=MENUEX)&&(y<=MENUEY) ) {
		return	TRUE;
	}

	return	FALSE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WDestroyMenu (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine returns the menu of the current form
//
// PARAMETERS:  (UInt16) fIndex - the index of the current form
//
// RETURNED:    Return the menu of the current form
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/05/01	Initial Revision
//			Jerry	11/10/01	Use MenuBarType instead of MenuLink type
////////////////////////////////////////////////////////////////////////
void WDestroyMenu ()
{
	int		index, i, j;

	for ( index = 0; index < menuCount; index++ ) {
		for ( i = 0; i < menuPtr[index]->numMenus; i++ ) {
			for ( j = 0; j < menuPtr[index]->menus[i].numItems; j++ ) {
				Vfree (menuPtr[index]->menus[i].items[j].itemStr);
				menuPtr[index]->menus[i].items[j].itemStr = NULL;
			}
			if ( menuPtr[index]->menus[i].items )
				Vfree (menuPtr[index]->menus[i].items);
			if ( menuPtr[index]->menus[i].title )
				Vfree (menuPtr[index]->menus[i].title);
		}
		if ( menuPtr[index]->menus )
			Vfree (menuPtr[index]->menus);
		Vfree (menuPtr[index]);
		menuPtr[index] = NULL;
	}

	if ( menuPtr ) {
		Vfree (menuPtr);
		menuPtr = NULL;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDisplayMenu (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine display the mune of the current form.
//
// PARAMETERS:  
//
// RETURNED:    
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/09/01	Initial Revision
//			Jerry	3/29/01	Save the region of menu to clipboard.
//			Jerry 5/15/01	Modify to use ActiveMenu
//			Jerry	8/15/01	Add check if no active menu, return
////////////////////////////////////////////////////////////////////////
void VDisplayMenu (Boolean	bDisplaySubMenu)
{
	RectangleType	rect, subRect;
	UInt16		i;

	if ( MenuActive || !ActiveMenu )
		return;

	if ( !bDisplaySubMenu ) {
		rect.topLeft.x = PDASTARTX;
		rect.topLeft.y = PDASTARTY;
		rect.extent.x = PDAHEIGHT;
		rect.extent.y = TitleHeight;

		// Clear the title menu rectangle area
		VSaveRegion (&rect, COORD_STRETCH);
		VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
		VDrawRect (&rect, PS_INSIDEFRAME, 5, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

		// Display title menu
		for ( i = 0; i < ActiveMenu->numMenus; i++ ) {
			VDrawString ((Coord)(ActiveMenu->menus[i].bounds.topLeft.x+5),
							(Coord)2,
							ActiveMenu->menus[i].title, 
							Vstrlen(ActiveMenu->menus[i].title), 
							SINGLELINE, CL_FOREGROUND, COORD_STRETCH);
		}
	}

	// Clear the submenu rectangle area
	VPDAToSysPoint (&(subRect.topLeft), 
		&(ActiveMenu->menus[ActiveMenu->curMenu].bounds.topLeft));
	Vmemcpy (&(subRect.extent), 
		&(ActiveMenu->menus[ActiveMenu->curMenu].bounds.extent), 
		sizeof(PointType));
	subRect.extent.x = VPDAToSysXRes (subRect.extent.x);
	subRect.extent.y += (FntLineHeight()*2/3+ActiveMenu->menus[ActiveMenu->curMenu].numItems);

	VSaveRegion (&subRect, COORD_NORMAL);
	VDrawRect (&subRect, PS_SOLID, 0, CL_BACKGROUND, COORD_NORMAL, DRAW_SET);
	VDrawRect (&subRect, PS_INSIDEFRAME, 5, CL_FOREGROUND, COORD_NORMAL, DRAW_SET);

	// Diaplay the submenu
	for ( i = 0; i < ActiveMenu->menus[ActiveMenu->curMenu].numItems; i++ ) {
		if ( Vstricmp (ActiveMenu->menus[ActiveMenu->curMenu].items[i].itemStr, "SEPARATOR")==0 )
			VDrawLine (VSysToPDAXCoord(subRect.topLeft.x), 
							VSysToPDAYCoord((subRect.topLeft.y+i*(FntLineHeight()+1)+FntLineHeight())),
							VSysToPDAXCoord((subRect.topLeft.x+subRect.extent.x)),
							VSysToPDAYCoord((subRect.topLeft.y+i*(FntLineHeight()+1)+FntLineHeight())),
							THIN_LINE, FOREGROUNDCOLOR, PS_SOLID);
		else
			VDrawString ((Coord)(subRect.topLeft.x+5),
							(Coord)(i*(FntLineHeight()+1)+subRect.topLeft.y+FntLineHeight()/3),
							ActiveMenu->menus[ActiveMenu->curMenu].items[i].itemStr,
							Vstrlen(ActiveMenu->menus[ActiveMenu->curMenu].items[i].itemStr),
							SINGLELINE, CL_FOREGROUND, COORD_NORMAL);
	}

	MenuActive = TRUE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VInvertMenuItem (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine invert current select item.
//
// PARAMETERS:  
//
// RETURNED:    
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	12/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VInvertMenuItem ()
{
	RectangleType	rect;
	Coord		y;

	// calculate the invert rectangle size and position
	VPDAToSysPoint (&(rect.topLeft), 
		&(ActiveMenu->menus[ActiveMenu->curMenu].bounds.topLeft));
	Vmemcpy (&(rect.extent), 
		&(ActiveMenu->menus[ActiveMenu->curMenu].bounds.extent), 
		sizeof(PointType));
	rect.topLeft.x += 2;
	rect.extent.x = VPDAToSysXRes (rect.extent.x)-4;
	rect.extent.y = FntLineHeight()*4/3;

	//	clear last select item first
	if ( lastMenuItemIndex != -1 ) {
		y = rect.topLeft.y;
		rect.topLeft.y += lastMenuItemIndex*(FntLineHeight()+1)+2;
		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_NORMAL, DRAW_XOR);
		rect.topLeft.y = y;
	}

	// invert the current select item
	if ( ActiveMenu->curItem != -1 ) {
		rect.topLeft.y += ActiveMenu->curItem*(FntLineHeight()+1)+2;

		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_NORMAL, DRAW_XOR);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VCloseMenu (WISCORE OS used only, add by Jerry Chu)
//
// DESCRIPTION: This routine close the mune of the current form.
//
// PARAMETERS:  (int) menuIndex - The menu index that open last time.
//
// RETURNED:    
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/29/01	Initial Revision
//			Jerry 6/15/01	Add menuIndex parameter
////////////////////////////////////////////////////////////////////////
void VCloseMenu (int menuIndex, Boolean bCloseSubMenu)
{
	RectangleType	rect, subRect;

	// Clear the submenu rectangle area
	VPDAToSysPoint (&(subRect.topLeft), 
		&(ActiveMenu->menus[menuIndex].bounds.topLeft));
	Vmemcpy (&(subRect.extent), 
		&(ActiveMenu->menus[menuIndex].bounds.extent), 
		sizeof(PointType));
	subRect.extent.x = VPDAToSysXRes (subRect.extent.x);
	subRect.extent.y += (FntLineHeight()*2/3+ActiveMenu->menus[menuIndex].numItems);
	VRedrawRegion (&subRect, COORD_NORMAL);

	if ( !bCloseSubMenu ) {
		rect.topLeft.x = PDASTARTX;
		rect.topLeft.y = PDASTARTY;
		rect.extent.x = PDAWIDTH;
		rect.extent.y = TitleHeight;
		VRedrawRegion (&rect, COORD_STRETCH);
		MenuActive = FALSE;
	} else 
		MenuActive = TRUE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VSetMenu
//
// DESCRIPTION: This routine set the current menu.
//
// PARAMETERS:  (UInt16) menuID - Menu ID to set active.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/29/01	Initial Revision
//			Jerry	8/15/01	Add MenuLinkPtr NULL checking
////////////////////////////////////////////////////////////////////////
void VSetMenu ( UInt16 menuID )
{
	int	index;

	ActiveMenu = NULL;

	for ( index = 0; index < menuCount; index++ ) {
		if ( menuPtr[index]->id == menuID ) {
			ActiveMenu = menuPtr[index];
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuAddItem
//
// DESCRIPTION: This routine add an item to the currently active menu.
//
// PARAMETERS:  (UInt16) positionID - ID of an existing menu item. The
//										new menu item is added after this menu
//										item.
//					 (UInt16) id - ID value to use for the new menu item.
//					 (Char) cmd - Shortcut key.
//					 (const Char *) textP - Pointer to the text to display
//										for this menu item, including the shortcut
//										key.
//
// RETURNED:    Returns 0 upon success.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Err MenuAddItem (UInt16 positionID, UInt16 id, Char cmd, const Char *textP)
{
	UInt16	index, count, i;

	for ( index = 0; index < ActiveMenu->numMenus; index++ ) {
		for ( count = 0; count < ActiveMenu->menus[index].numItems; count++ ) {
			if ( positionID == ActiveMenu->menus[index].items[count].id ) {
				ActiveMenu->menus[index].numItems++;
				ActiveMenu->menus[index].items = Vrealloc (ActiveMenu->menus[index].items,
						sizeof(MenuItemType) * ActiveMenu->menus[index].numItems);
				for ( i = ActiveMenu->menus[index].numItems-1; i > count; i++ ) {
					Vmemmove (&(ActiveMenu->menus[index].items[i]), 
							 	 &(ActiveMenu->menus[index].items[i-1]),
								 sizeof (ActiveMenu->menus[index].items[i-1]));
				}
				ActiveMenu->menus[index].items[count].itemStr = Vmalloc (sizeof(textP));
				Vstrcpy (ActiveMenu->menus[index].items[count].itemStr, textP);
				ActiveMenu->menus[index].items[count].id = id;
				ActiveMenu->menus[index].items[count].command = cmd;

				return	0;
			}
		}
	}

	return	 -1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuDispose
//
// DESCRIPTION: This routine release any menory allocated to the menu and
//					 the command status and restore any saved bits to the screen.
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to a MenuBarType.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void MenuDispose (MenuBarType *menuP)
{
	UInt16	i,j;

	// if menu is active, close it
	if ( MenuActive == TRUE ) {
		VCloseMenu (ActiveMenu->curMenu, ALLMENU);
	}

	// release the allocation memory for menu
	for ( i = 0; i < menuP->numMenus; i++ ) {

		for ( j = 0; j < menuP->menus[i].numItems; j++ ) {
			menuP->menus[i].items[j].itemStr = Vrealloc (menuP->menus[i].items[j].itemStr, 0);
		}

		menuP->menus[i].title = Vrealloc (menuP->menus[i].title, 0);
		Vfree (menuP->menus[i].items);
		menuP->menus[i].items = NULL;
	}

	Vfree (menuP->menus);
	menuP->menus = NULL;
	Vfree (menuP);
	menuP = NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuDrawMenu
//
// DESCRIPTION: This routine draw the current menu bar and the last
//				pull-down that was visile.
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to a MenuBarType.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void MenuDrawMenu (MenuBarType *menuP)
{
	ActiveMenu = menuP;

	VDisplayMenu (ALLMENU);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuEraseStatus
//
// DESCRIPTION: This routine erase the menu command stauts
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to a MenuBarType or
//									NULl for the current menu.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/14/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
void MenuEraseStatus(MenuBarType *menuP)
{

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuGetActiveMenu
//
// DESCRIPTION: This routine returns a pointe to the currently active
//				menu.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns a pointer to the currently active menu, or NULL
//				if there is none.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/04/01	Initial Revision as NULL
//			Jerry	11/10/01	Modify to return ActiveMenu
////////////////////////////////////////////////////////////////////////
MenuBarType *MenuGetActiveMenu (void)
{
	return	ActiveMenu;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuHandleEvent
//
// DESCRIPTION: This routine set a callback functioin to draw each item
//				instead of drawing the item's text string.
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to the list structure
//				(EventType *) event - 
//				(UInt16 *) error -
//
// RETURNED:    
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/09/01	Initial Revision
//			Jerry	3/29/01	Checking click on menu item.
//			Jerry	12/06/06	Checking penDownEvent and penMoveEvnet
////////////////////////////////////////////////////////////////////////
Boolean MenuHandleEvent(MenuBarType *menuP, EventType *event, UInt16 *error) 
{
	if ( MenuActive ) {
		// if MenuActive and press "Menu", close it
		if ( event->eType == menuOpenEvent ) {
			// not select in the Menu box, close the menu
			VCloseMenu(lastMenuIndex, ALLMENU);
			MenuActive = false;

			return	1;
		} if ((event->eType == ctlSelectEvent)||(event->eType == penUpEvent)) {
			if ( VCheckHitMenuItem (event->screenX, event->screenY) ) {
				if ( ActiveMenu->curItem != -1 ) {
					event->eType = menuEvent;
					event->data.menu.itemID = ActiveMenu->menus[ActiveMenu->curMenu].items[ActiveMenu->curItem].id;
					VCloseMenu(ActiveMenu->curMenu, ALLMENU);
					MenuActive = FALSE;

					return	0;
				}
			} else {
				event->eType = 0;
			}
		} else if ( event->eType == penDownEvent ) {
			if ( VCheckHitMenuItem (event->screenX, event->screenY) ) {
				if ( ActiveMenu->curItem != -1 ) {
					VInvertMenuItem ();
				} else {
					if ( lastMenuIndex != ActiveMenu->curMenu) {
						VCloseMenu(lastMenuIndex, SUBMENU);
						MenuActive = false;
						VDisplayMenu (SUBMENU);
					}

					return	1;
				}
			} else {
				// not select in the Menu box, close the menu
				VCloseMenu(lastMenuIndex, ALLMENU);
				MenuActive = false;

				return	1;
			}
		} else if ( event->eType == penMoveEvent ) {
			if ( VCheckHitMenuItem (event->screenX, event->screenY) ||
				((ActiveMenu->curItem == -1) && (lastMenuItemIndex != -1)) ) {
				if ( lastMenuIndex == ActiveMenu->curMenu ) 
					// if move on menu item, change the invert item
					VInvertMenuItem ();
				else {	// if move on menu title bar, change the submenu
					VCloseMenu(lastMenuIndex, SUBMENU);
					MenuActive = false;
					VDisplayMenu (SUBMENU);
					lastMenuIndex = ActiveMenu->curMenu;
				}
			}
		}
	} else {
		if (event->eType == menuOpenEvent && ActiveMenu) {
			ActiveMenu->curItem	= lastMenuItemIndex = -1;
			VDisplayMenu (ALLMENU);

			return	1;
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuHideItem
//
// DESCRIPTION: This routine hide a menu item.
//
// PARAMETERS:  (UInt16) id - ID of the menu item to hide
//
// RETURNED:    Returns true if the menu item was hidden; false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/04/01	Initial Revision
//			Jerry
////////////////////////////////////////////////////////////////////////
Boolean MenuHideItem (UInt16 id)
{
	UInt16		i,j;

	for ( i = 0; i < ActiveMenu->numMenus; i++ ) {
		for ( j = 0; j < ActiveMenu->menus[i].numItems; j++ ) {
			if ( ActiveMenu->menus[i].items[j].id == id ) {
				ActiveMenu->menus[i].items[j].hidden = TRUE;
				return	true;
			}
		}
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuInit
//
// DESCRIPTION: This routine load a menu resource from a resource file.
//
// PARAMETERS:  (UInt16) resourceID - ID that identifies the menu resource
//
// RETURNED:    Returns the pointer to a memory block allocated to hold
//					 the menu resource.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
MenuBarType *MenuInit (UInt16 resourceID)
{
	return	ActiveMenu;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuSetActiveMenu
//
// DESCRIPTION: This routine set the current menu.
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to the list structure
//
// RETURNED:    Returns a pointer to the menu that was active before
//					 the new menu was set.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
MenuBarType *MenuSetActiveMenu (MenuBarType *menuP)
{
	MenuBarType	*oldMenu = ActiveMenu;

	ActiveMenu = menuP;

	return	oldMenu;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MenuShowItem
//
// DESCRIPTION: This routine display a menu item that is currently hidden
//
// PARAMETERS:  (UInt16) id - ID of the menu item to display
//
// RETURNED:    Returns true if the menu item was successfully displayed,
//				false otherwise
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/04/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean MenuShowItem (UInt16 id)
{
	UInt16		i,j;

	for ( i = 0; i < ActiveMenu->numMenus; i++ ) {
		for ( j = 0; j < ActiveMenu->menus[i].numItems; j++ ) {
			if ( ActiveMenu->menus[i].items[j].id == id ) {
				ActiveMenu->menus[i].items[j].hidden = FALSE;
				MenuDrawMenu (ActiveMenu);

				return	true;
			}
		}
	}

	return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WMenuAddItem
//
// DESCRIPTION: This routine add an item to the currently active menu.
//
// PARAMETERS:  (UInt16) menuIndex - The index of menu.
//					 (UInt16) subMenuIndex - The index of sub menu, -1
//										denote current added is menu.
//					 (UInt16) id - ID value to use for the new menu item.
//					 (Char) cmd - Shortcut key.
//					 (const Char *) textP - Pointer to the text to display
//										for this menu item, including the shortcut
//										key.
//
// RETURNED:    Returns 0 upon success.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err WMenuAddItem (UInt16 menuIndex, Int16 subMenuIndex, UInt16 id, Char cmd, const Char *textP)
{
	UInt16	i, strWidth, strLen=(UInt16)Vstrlen(textP);

	if ( ActiveMenu->numMenus == 0 ) {	// no menu exist, allocate one.
		ActiveMenu->menus = Vmalloc (sizeof(MenuPullDownType));
		Vmemset (ActiveMenu->menus, 0, sizeof(MenuPullDownType));

		// set title menu position
		ActiveMenu->menus[0].bounds.topLeft.x = subMenuStartX;
		ActiveMenu->menus[0].bounds.topLeft.y = TitleHeight+1;
		ActiveMenu->menus[0].bounds.extent.x = menuItemWidth;
		ActiveMenu->numMenus++;
	} else if ( menuIndex >= ActiveMenu->numMenus) {
		// if menuIndex large than number of menu, denote add one new menu.
		menuIndex = ActiveMenu->numMenus;
		ActiveMenu->numMenus++;
		ActiveMenu->menus = Vrealloc (ActiveMenu->menus, ActiveMenu->numMenus*sizeof(MenuPullDownType));
		Vmemset (&(ActiveMenu->menus[menuIndex]), 0, sizeof(MenuPullDownType));

		// set title menu position
		ActiveMenu->menus[menuIndex].bounds.topLeft.x = menuItemWidth*menuIndex+subMenuStartX;
		ActiveMenu->menus[menuIndex].bounds.topLeft.y = TitleHeight+1;
		ActiveMenu->menus[menuIndex].bounds.extent.x = menuItemWidth;
	}

	if ( subMenuIndex == -1 ) {	// current added is a menu.
		ActiveMenu->menus[menuIndex].title = Vmalloc (strLen+1);
		Vstrcpy (ActiveMenu->menus[menuIndex].title, textP);

		return	0;
	} else {		// current added is a submenu
		ActiveMenu->menus[menuIndex].numItems++;
		ActiveMenu->menus[menuIndex].items = Vrealloc (ActiveMenu->menus[menuIndex].items,
				sizeof(MenuItemType) * ActiveMenu->menus[menuIndex].numItems);
		Vmemset (&(ActiveMenu->menus[menuIndex].items[ActiveMenu->menus[menuIndex].numItems-1]), 0, sizeof(MenuItemType));
		for ( i = ActiveMenu->menus[menuIndex].numItems-1; i > subMenuIndex; i++ ) {
			Vmemmove (&(ActiveMenu->menus[menuIndex].items[i]), 
					 	 &(ActiveMenu->menus[menuIndex].items[i-1]),
						 sizeof (ActiveMenu->menus[menuIndex].items[i-1]));
		}
		ActiveMenu->menus[menuIndex].items[subMenuIndex].itemStr = Vmalloc (strLen+1);
		Vstrcpy (ActiveMenu->menus[menuIndex].items[subMenuIndex].itemStr, textP);
		ActiveMenu->menus[menuIndex].items[subMenuIndex].id = id;
		ActiveMenu->menus[menuIndex].items[subMenuIndex].command = cmd;

		// calculate the new rectangle boundary
		ActiveMenu->menus[menuIndex].bounds.extent.y = 
			(ActiveMenu->menus[menuIndex].numItems)*FntLineHeight();

		strWidth = FntCharsWidth (textP, strLen);
		if ( strWidth > (UInt32)ActiveMenu->menus[menuIndex].bounds.extent.x ) {
			ActiveMenu->menus[menuIndex].bounds.extent.x = (Int16)(strWidth);
		}
		return	0;
	}

	return	 -1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WMenuInitialize
//
// DESCRIPTION: This routine load a menu resource from a resource file.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the pointer to a memory block allocated to hold
//					 the menu resource.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
MenuBarType *WMenuInitialize ()
{
	ActiveMenu = (MenuBarType *) Vmalloc (sizeof(MenuBarType));
	Vmemset (ActiveMenu, 0, sizeof(MenuBarType));

	return	ActiveMenu;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WMenuRelease
//
// DESCRIPTION: This routine release the memory allocated for a menu 
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to MenuBarType.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WMenuRelease (MenuBarType *menuP)
{
	MenuDispose (menuP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WSetMenu
//
// DESCRIPTION: This routine set the current menu.
//
// PARAMETERS:  (MenuBarType *) menuP - Pointer to MenuBarType.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WSetMenu (MenuBarType *menuP)
{
	ActiveMenu = menuP;
}
