/*========================================================
  Category.c
  all routine is running with Platform non-related,
  simulated the Category function in Palm OS.
  Current status is ControlModal free funtion.

  All is Palm related function.
  Completed 6 of 11 Category function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0327, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#define	CATEGORYSTARTX		95
#define	CATEGORYSTARTY		1
#define	CATEGORYWIDTH		50
#define	CATEGORYHEIGHT		12

ListType	*catList;


////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryCreateList
//
// DESCRIPTION: This routine read a database's categories and store them
//				in a list.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(ListType *) listP - A pointer to the list of category
//								names.
//				(UInt16) currentCategory - Category to select
//				(Boolean) showAll - true to have an "ALL" categories
//				(Boolean) showUneditables - true to show uneditable
//								categories.
//				(UInt8) numUneditableCategories - This is the number of
//								categories, starting with the first one
//								at zero.
//				(UInt32) editingStrID - The resource ID os a string to
//								use with the "Edit Categories" list item.
//				(Boolean) resizeList - true to resize the list to the
//								number of categories. Set to true for 
//								pop-ups, false otherwise
//	
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/13/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CategoryCreateList (DmOpenRef db, ListType *listP, UInt16 currentCategory,
						 Boolean showAll, Boolean showUneditables, 
						 UInt8 numUneditableCategories,
						 UInt32 editingStrID, Boolean resizeList)
{
	UInt16	index=0, k, offset=0;
	Char		word[16];

	if ( !VGetCategoryName (db, 0, word) ) {
		for ( ; index < listP->numItems; index++ ) {
			VWriteCategory ( db, index, listP->itemsText[index], Vstrlen(listP->itemsText[index]) ) ;
		}
	} else {
		// release old listP text memory
		for ( k = 0; k < listP->numItems; k++ ) {
			if ( listP->itemsText[k]);
				Vfree (listP->itemsText[k]);
		}
		if ( listP->itemsText )
			Vfree (listP->itemsText);
		listP->itemsText = NULL;

		// if showAll, add the "ALL" item to the list
		listP->itemsText = (Char **) Vrealloc (listP->itemsText,
								(sizeof(Char *)*(listP->numItems+1)));
		if (showAll) {
			listP->itemsText[index] = (Char*) Vmalloc (4);
			Vstrcpy (listP->itemsText[index++], "All");
			offset = 1;
		}

		do {
			listP->itemsText[index] = (Char*) Vmalloc (Vstrlen(word)+1);
			Vstrcpy (listP->itemsText[index++], word);
		} while ( VGetCategoryName (db, (UInt16)(index-offset), word) );
		listP->numItems = index;
		if ( resizeList ) {
			listP->bounds.extent.y = listP->numItems*FntLineHeight();
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryFind
//
// DESCRIPTION: This routine return the unique ID of the category that
//				matches the name passed.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(char *) name - Category name. 
//
// RETURNED:    Returns the category index.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/19/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 CategoryFind (DmOpenRef db, char *name)
{
	Char			word[16];
	UInt16		index=0;

	while ( VGetCategoryName (db, index++, word) )
		if ( Vstrcmp (word, name) == 0 )
			return	index-1;

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryFreeList
//
// DESCRIPTION: This routine unlocks or frees memory locked or allocated
//					 by CategoryCreateList.
//
// PARAMETERS:  (DmOpenRef) db - Categories database.
//					 (const ListType *) listP - Pointer to the category list.
//					 (Boolean) showAll - true if the list was created with
//										an "All" category.
//					 (UInt32) editingStrID - The editingStrID should be the
//										same as that passed to CategoryCreateList.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void CategoryFreeList (DmOpenRef db, const ListType *listP, 
							  Boolean showAll, UInt32 editingStrID)
{
//	Vfree (catList);
	catList = NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryGetName
//
// DESCRIPTION: This routine return the name of the specified category
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Category index.
//				(char *) name - Buffer to hold category name. Buffe should
//							be dmCategoryLength in size.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/19/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CategoryGetName (DmOpenRef db, UInt16 index, char *name)
{
	if ( index == dmAllCategories ) {
		Vstrcpy (name, "All");
	} else {
		char	buffer[16];

		VGetCategoryName (db, index, buffer);
		Vstrcpy (name, buffer);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryGetNext
//
// DESCRIPTION: This routine given a category index, this function returns
//					 the index of the next category. Note that categories are
//					 not stores sequentially.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//					 (UInt16) index - Category index.
//
// RETURNED:    Returns category index of next category.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 CategoryGetNext (DmOpenRef db, UInt16 index)
{
/*
	if ( index < catList->numItems ) {
		return	index+1;
	} else {
		return	index;
	}
*/
	return	(index<catList->numItems)?index+1:index;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryInitialize
//
// DESCRIPTION: This routine initialize the category names, IDs, and flags
//
// PARAMETERS:  (AppInfoPtr) appInfoP - Application info pointer.
//					 (UInt16) localizedAppInfoStrID - Resource ID of the
//									localized category names.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	4/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CategoryInitialize (AppInfoPtr appInfoP, UInt16 localizedAppInfoStrID)
{
	UInt16	i;

	catList = (FrmGetObjectPtrById (localizedAppInfoStrID)).object.list;
	for ( i = 0; i < catList->numItems; i++ ) {
		VCategorySetName (currentDBP, i, catList->itemsText[i]);
	}
//	catList->numItems = 0;
//	catList->itemsText = (Char **) Vmalloc (sizeof(Char *)*(catList->numItems+1));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategorySelect
//
// DESCRIPTION: This routine process the selection and editing of 
//				categories. Usually you call this when the user taps
//				the category pop-up trigger.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(FormType *) frm - Form that contains the category popup list.
//				(UInt16) ctlID - ID of the popup trigger
//				(UInt16) lstID - ID of the popup list
//				(Boolean) title - true if the popup trigger is on the title
//							line, which mans that an "All" choice should be
//							added to the list. Pass false if the popup 
//							tigger appears in a form where a specific record
//							is being modified or any where else the "All"
//							choice should not appear.
//				(UInt16 *) categoryP - Current category (pointer into db
//							structure).
//				(char *) categoryName - Name of the current category 
//				(UInt8) numUneditableCategories - This is the number
//							categories, starting with the first one at
//							zero, that may not have their names edited
//							by the user.
//				(UInt32) editingStrID - The resource ID of a string to 
//							use with the "Edit Categories" list item.
//
// RETURNED:    Returns true if any of the following conditions are true:
//					.The current category is renamed.
//					.The current category is deleted.
//					.The current category is merged with another category.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/16/01	Initial Revision
//			Jerry	3/19/01	Initial Revision
//			Jerry 5/05/01	Modify to use Global LIST catList
////////////////////////////////////////////////////////////////////////
Boolean CategorySelect (DmOpenRef db, const FormType *frm, UInt16 ctlID,
					 UInt16 lstID, Boolean title, UInt16 *categoryP,
					 char *categoryName, UInt8 numUneditableCategories,
					 UInt32 editingStrID)
{
	ControlPtr	ctlP;
	ListType		*listP;
	UInt16		maxlength = 0;
	Int16			theIndex, lastIndex = *categoryP;

	ctlP = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, ctlID));
	listP = FrmGetObjectPtr (frm, FrmGetObjectIndex (frm, lstID));
	if ( !ctlP || !listP )	return	FALSE;
	Vmemcpy (&(listP->bounds), &(ctlP->bounds), sizeof(RectangleType));
	CategoryCreateList (db, listP, *categoryP, title,TRUE, TRUE, 0, TRUE);
	if ( title ) {
		if (*categoryP == dmAllCategories)
			listP->currentItem = 0;
		else
			listP->currentItem = *categoryP+1;
	} else
		listP->currentItem = *categoryP;
	theIndex = LstPopupList(listP);

	if (theIndex >= 0) {
		Vstrcpy (categoryName, LstGetSelectionText(listP,theIndex));
		CtlSetLabel (ctlP, categoryName);
		if ( title ) {
			if ( !theIndex ) 
				*categoryP = dmAllCategories;
			else
				*categoryP = theIndex-1;
		} else
			*categoryP = theIndex;
		return	FALSE;
	} else {
		if ( *categoryP == dmAllCategories ) 
			Vstrcpy (categoryName, LstGetSelectionText(listP,0));
//		*categoryP = dmAllCategories;

		return	FALSE;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategorySetName
//
// DESCRIPTION: This routine set the category name and rename bits.
//				A NULL pointer removes the category name.
//
// PARAMETERS:  (DmOpenRef) db - Opened database containing category info.
//				(UInt16) index - Index of category to set.
//				(const char *) name - A Category name (null-terminated) or 
//									NULL pointe to remove the category.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CategorySetName (DmOpenRef db, UInt16 index, const char *name)
{
	if ( index < catList->numItems ) { // change current item to new text
		catList->itemsText[index] = (char *) Vrealloc (catList->itemsText[index], Vstrlen(name)+1);
		Vstrcpy (catList->itemsText[index], name);
	} else if ( Vstrlen(name) ) { // add a new item text
		catList->itemsText = (Char **) Vrealloc (catList->itemsText, sizeof(Char *)*(catList->numItems+1));
		catList->itemsText[catList->numItems] = (char *) Vmalloc(Vstrlen(name)+1);
		Vstrcpy (catList->itemsText[catList->numItems], name);
		catList->numItems++;
	}
	VCategorySetName (db, index, name);
/*
	UInt16		size=0;
	Char		word[16];
	UInt16		maxlength = 0;
//	UInt16		*category = VGetRecord (db, index, 0);

	while ( VGetCategoryName (db, catList->numItems, word) ) {
		catList->itemsText = (Char **) Vrealloc (catList->itemsText, sizeof(Char *)*(catList->numItems+1));
		size += (UInt16)(Vstrlen(word)+1);
		catList->itemsText[catList->numItems] = (char *) Vmalloc(size);
		Vstrcpy (catList->itemsText[catList->numItems], word);
		if ( Vstrlen (word) > maxlength ) {
			maxlength = (UInt16) Vstrlen(word);
		}
		catList->numItems++;
	};

//	if ( *category == dmAllCategories ) {
//		*category = 0;
//	}
	Vstrcpy (catList->itemsText[index], name);
*/
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategorySetTriggerLabel
//
// DESCRIPTION: This routine set the label displayed by the category
//				trigger. The category name is truncated if it is larger
//				than the system default maximum width.
//
// PARAMETERS:  (ControlType *) ctl - OPointer to control object to relabel
//				(char *) name - Pointer to the name of the new category. 
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
extern void CategorySetTriggerLabel (ControlType *ctl, Char *name)
{
	CtlSetLabel (ctl, name);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CategoryTruncateName
//
// DESCRIPTION: This routine truncate a category name so that it's short
//					 enough to display. The category name is truncated if it's
//					 longer than maxWidth.
//
// PARAMETERS:  (char *) name - Category name to truncate.
//					 (UInt16) maxWidth - Maximum size, in pixels
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/04/01	Initial Revision
////////////////////////////////////////////////////////////////////////
extern void CategoryTruncateName (Char *name, UInt16 maxWidth)
{
	UInt16	length = maxWidth/5;

	if ( length < Vstrlen (name) ) {
		name = Vrealloc (name, length+1);
		name[length] = 0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WCategoryInitialize (Wiscore used only)
//
// DESCRIPTION: This routine initialize the category names, IDs, and flags
//
// PARAMETERS:  (AppInfoPtr) appInfoP - Application info pointer.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01	Initial Revision
//			Jerry	10/09/01	Remove category position hardcore
////////////////////////////////////////////////////////////////////////
void WCategoryInitialize (AppInfoPtr appInfoP)
{
	catList = (ListType *) Vmalloc (sizeof(ListType));

	Vmemset (catList, 0, sizeof (ListType));

	catList->numItems = 0;

	catList->bounds.topLeft.x = CATEGORYSTARTX;
	catList->bounds.topLeft.y = CATEGORYSTARTY;
	catList->bounds.extent.x = CATEGORYWIDTH;
	catList->bounds.extent.y = CATEGORYHEIGHT;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WCategoryRelease (Wiscore used only)
//
// DESCRIPTION: This routine initialize the category names, IDs, and flags
//
// PARAMETERS:  None.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WCategoryRelease ()
{
//	Vfree (catList);
	catList = NULL;
}
