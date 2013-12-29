#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <linux/mman.h>
#include <linux/fb.h>
#include <sys/ipc.h>
#include <sys/sem.h>
//#include <unistd.h>

#include <Common.h>
#include "wisapi.h"

#define	false		FALSE
#define	true		TRUE

extern struct FuncCount funcCount[];



////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
#ifdef L_AlmGetAlarm
UInt32 AlmGetAlarm (UInt16 cardNo, LocalID dbID, UInt32 *refP)
{
	UInt32 (*AlmGetAlarmP) (UInt16 cardNo, LocalID dbID, UInt32 *refP);

	GetParameter (&AlmGetAlarmP, sizeof(void *), pAlmGetAlarm);
	return	(*AlmGetAlarmP) (cardNo, dbID, refP);
}
#endif

#ifdef L_AlmGetProcAlarm
UInt32 AlmGetProcAlarm (AlmAlarmProcPtr procP, UInt32 refP)
{
	UInt32 (*AlmGetProcAlarmP) (AlmAlarmProcPtr procP, UInt32 refP);

	GetParameter (&AlmGetProcAlarmP, sizeof(void *), pAlmGetProcAlarm);
	return	(*AlmGetProcAlarmP) (procP, refP);
}
#endif

#ifdef L_AlmSetAlarm
Err AlmSetAlarm (UInt16 cardNo, LocalID dbID, UInt32 ref,
								UInt32 alarmSeconds, Boolean quiet)
{
	Err (*AlmSetAlarmP) (UInt16 cardNo, LocalID dbID, UInt32 ref,
								UInt32 alarmSeconds, Boolean quiet);

	GetParameter (&AlmSetAlarmP, sizeof(void *), pAlmSetAlarm);
	return	(*AlmSetAlarmP) (cardNo, dbID, ref, alarmSeconds, quiet);

}
#endif

#ifdef L_AlmSetProcAlarm
Err AlmSetProcAlarm (AlmAlarmProcPtr procP, UInt32 ref, UInt32 alarmSeconds)
{
	Err (*AlmSetProcAlarmP) (AlmAlarmProcPtr procP, UInt32 ref, UInt32 alarmSeconds);

	GetParameter (&AlmSetProcAlarmP, sizeof(void *), pAlmSetProcAlarm);
	return	(*AlmSetProcAlarmP) (procP, ref, alarmSeconds);
}

#endif




////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_BmpCreate
 BitmapType *BmpCreate (Coord width, Coord height, UInt8 depth, ColorTableType *colortableP, UInt16 *error)
{
	BitmapType* (*BmpCreateP) (Coord width, Coord height, UInt8 depth, ColorTableType *colortableP, UInt16 *error);

	GetParameter (&BmpCreateP, sizeof(void *), pBmpCreate);
	return	    (*BmpCreateP) ( width,  height,  depth, colortableP, error);

}
#endif
*/
							
#ifdef L_BmpDelete
 Err BmpDelete (BitmapType *bitmapP)
{
        Err (*BmpDeleteP) (BitmapType *bitmapP);
	
	GetParameter (&BmpDeleteP, sizeof(void *), pBmpDelete);
	return	(*BmpDeleteP) (bitmapP);
	
}								
#endif
/*
#ifdef L_BmpCompress
 Err BmpCompress(BitmapType *bitmapP, BitmapCompressionType compType )
{
	Err (*BmpCompressP)(BitmapType *bitmapP, BitmapCompressionType compType );

	GetParameter (&BmpCompressP, sizeof(void *), pBmpCompress);
	return	(*BmpCompressP)(bitmapP,  compType );

}
#endif
*/
#ifdef L_BmpGetBits
 void *BmpGetBits(BitmapType *bitmapP)
{
	 void *(*BmpGetBitsP)(BitmapType *bitmapP);

	GetParameter (&BmpGetBitsP, sizeof(void *), pBmpGetBits);
	return	     (*BmpGetBitsP)(bitmapP);

								
}
#endif
/*
#ifdef L_BmpGetColortable
 ColorTableType *BmpGetColortable(BitmapType *bitmapP)
{
	 ColorTableType *(*BmpGetColortableP)(BitmapType *bitmapP);

	GetParameter (&BmpGetColortableP, sizeof(void *), pBmpGetColortable);
	return	(*BmpGetColortableP)(bitmapP);

}
#endif
 */
#ifdef L_BmpSize
 UInt16 BmpSize(BitmapType *bitmapP)
{
	 UInt16 (*BmpSizeP)(BitmapType *bitmapP);

	GetParameter (&BmpSizeP, sizeof(void *), pBmpSize);
	return	(*BmpSizeP)(bitmapP);
								
}
#endif
							
#ifdef L_BmpBitsSize
 UInt16 BmpBitsSize(BitmapType *bitmapP)
{
	 UInt16 (*BmpBitsSizeP)(BitmapType *bitmapP);

	GetParameter (&BmpBitsSizeP, sizeof(void *), pBmpBitsSize);
	return	 (*BmpBitsSizeP)(bitmapP);
								
}
#endif
							
#ifdef L_BmpColortableSize
 UInt16 BmpColortableSize(BitmapType *bitmapP)
{
	 UInt16 (*BmpColortableSizeP)(BitmapType *bitmapP);

	GetParameter (&BmpColortableSizeP, sizeof(void *), pBmpColortableSize);
	return	(*BmpColortableSizeP)(bitmapP);
								
}
#endif
/*
#ifdef L_ColorTableEntries
 RGBColorType*  ColorTableEntries(ColorTableType*  ctP)
{
	 RGBColorType*  (*ColorTableEntriesP)(ColorTableType*  ctP);

	GetParameter (&ColorTableEntriesP, sizeof(void *), pColorTableEntries);
	return	(*ColorTableEntriesP)(ctP);

}
#endif
*/

////////////////////////////////////////////////////////////
// Category Library, completed11/11 functions now.
////////////////////////////////////////////////////////////
#ifdef L_CategoryCreateList
void CategoryCreateList (DmOpenRef db, ListType *listP, UInt16 currentCategory,
						 Boolean showAll, Boolean showUneditables, 
						 UInt8 numUneditableCategories,
						 UInt32 editingStrID, Boolean resizeList)
{
	void (*CategoryCreateListP) (DmOpenRef db, ListType *listP, UInt16 currentCategory,
						 Boolean showAll, Boolean showUneditables, 
						 UInt8 numUneditableCategories,
						 UInt32 editingStrID, Boolean resizeList);

	GetParameter (&CategoryCreateListP, sizeof(void *), pCategoryCreateList);
	(*CategoryCreateListP) (db, listP, currentCategory, showAll, showUneditables, 
									numUneditableCategories, editingStrID, resizeList);
}
#endif

#ifdef L_CategoryEdit
Boolean CategoryEdit (DmOpenRef db, UInt16 *categoryP, UInt32 titleStrID,
					 UInt16 numUneditableCategories)
{
	Boolean (*CategoryEditP) (DmOpenRef db, UInt16 *categoryP, UInt32 titleStrID,
					 UInt16 numUneditableCategories);

	GetParameter (&CategoryEditP, sizeof(void *), pCategoryEdit);
	return	(*CategoryEditP) (db, categoryP, titleStrID, numUneditableCategories);
}
#endif

#ifdef L_CategoryFind
UInt16 CategoryFind (DmOpenRef db, char *name)
{
	UInt16 (*CategoryFindP) (DmOpenRef db, char *name);

	GetParameter (&CategoryFindP, sizeof(void *), pCategoryFind);
	return	(*CategoryFindP) (db, name);
}
#endif

#ifdef L_CategoryFreeList
void CategoryFreeList (DmOpenRef db, const ListType *listP, 
							  Boolean showAll, UInt32 editingStrID)
{
	void (*CategoryFreeListP) (DmOpenRef db, const ListType *listP, 
							  Boolean showAll, UInt32 editingStrID);

	GetParameter (&CategoryFreeListP, sizeof(void *), pCategoryFreeList);
	(*CategoryFreeListP) (db, listP, showAll, editingStrID);
}
#endif

#ifdef L_CategoryGetName
void CategoryGetName (DmOpenRef db, UInt16 index, char *name)
{
	void (*CategoryGetNameP) (DmOpenRef db, UInt16 index, char *name);

	GetParameter (&CategoryGetNameP, sizeof(void *), pCategoryGetName);
	(*CategoryGetNameP) (db, index, name);
}
#endif

#ifdef L_CategoryGetNext
UInt16 CategoryGetNext (DmOpenRef db, UInt16 index)
{
	UInt16 (*CategoryGetNextP) (DmOpenRef db, UInt16 index);

	GetParameter (&CategoryGetNextP, sizeof(void *), pCategoryGetNext);
	return	(*CategoryGetNextP) (db, index);
}
#endif

#ifdef L_CategoryInitialize
void CategoryInitialize (AppInfoPtr appInfoP, UInt16 localizedAppInfoStrID)
{
	void (*CategoryInitializeP) (AppInfoPtr appInfoP, UInt16 localizedAppInfoStrID);

	GetParameter (&CategoryInitializeP, sizeof(void *), pCategoryInitialize);
	(*CategoryInitializeP) (appInfoP, localizedAppInfoStrID);
}
#endif

#ifdef L_CategorySelect
Boolean CategorySelect (DmOpenRef db, const FormType *frm, UInt16 ctlID,
					 UInt16 lstID, Boolean title, UInt16 *categoryP,
					 char *categoryName, UInt8 numUneditableCategories,
					 UInt32 editingStrID)
{
	Boolean (*CategorySelectP) (DmOpenRef db, const FormType *frm, UInt16 ctlID,
					 UInt16 lstID, Boolean title, UInt16 *categoryP,
					 char *categoryName, UInt8 numUneditableCategories,
					 UInt32 editingStrID);

	GetParameter (&CategorySelectP, sizeof(void *), pCategorySelect);
	return	(*CategorySelectP) (db, frm, ctlID, lstID, title, categoryP,
					 categoryName, numUneditableCategories, editingStrID);
}
#endif

#ifdef L_CategorySetName
void CategorySetName (DmOpenRef db, UInt16 index, const char *name)
{
	void (*CategorySetNameP) (DmOpenRef db, UInt16 index, const char *name);

	GetParameter (&CategorySetNameP, sizeof(void *), pCategorySetName);
	(*CategorySetNameP) (db, index, name);
}
#endif

#ifdef L_CategorySetTriggerLabel
void CategorySetTriggerLabel (ControlType *ctl, Char *name)
{
	void (*CategorySetTriggerLabelP) (ControlType *ctl, Char *name);

	GetParameter (&CategorySetTriggerLabelP, sizeof(void *), pCategorySetTriggerLabel);
	(*CategorySetTriggerLabelP) (ctl, name);
}
#endif

#ifdef L_CategoryTruncateName
void CategoryTruncateName (Char *name, UInt16 maxWidth)
{
	void (*CategoryTruncateNameP) (Char *name, UInt16 maxWidth);

	GetParameter (&CategoryTruncateNameP, sizeof(void *), pCategoryTruncateName);
	(*CategoryTruncateNameP) (name, maxWidth);
}

#endif



////////////////////////////////////////////////////////////
// Character Attributes Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
#ifdef L_GetCharAttr
 UInt16 *GetCharAttr (void)
{
	 UInt16 *(*GetCharAttrP) (void);

	GetParameter (&GetCharAttrP, sizeof(void *), pGetCharAttr);
	return	(*GetCharAttrP) ();
								
}
#endif
		
#ifdef L_GetCharSortValue
 UInt8 *GetCharSortValue (void)
{
	 UInt8 *(*GetCharSortValueP) (void);

	GetParameter (&GetCharSortValueP, sizeof(void *), pGetCharSortValue);
	return	(*GetCharSortValueP) ();
								
}
#endif
			
#ifdef L_GetCharCaselessValue
 UInt8 *GetCharCaselessValue (void)
{
	 UInt8 *(*GetCharCaselessValueP) (void);

	GetParameter (&GetCharCaselessValueP, sizeof(void *), pGetCharCaselessValue);
	return	(*GetCharCaselessValueP) ();
								
}
#endif

#ifdef L_ChrNumericSpace			
 void  ChrNumericSpace(char *chP)
{
	 void  (*ChrNumericSpaceP)(char *chP);

	GetParameter (&ChrNumericSpaceP, sizeof(void *), pChrNumericSpace);
	(*ChrNumericSpaceP)(chP);	
								
}
#endif
 
#ifdef L_ChrHorizEllipsis
 void  ChrHorizEllipsis(char *chP) 			
{
	 void  (*ChrHorizEllipsisP)(char *chP) ;

	GetParameter (&ChrHorizEllipsisP, sizeof(void *), pChrHorizEllipsis);
	(*ChrHorizEllipsisP)(chP) ;

}
#endif

// 
#ifdef L_ChrHorizEllipsis
 Boolean  ChrIsHardKey (WChar ch)		
{
	 Boolean  (*ChrIsHardKeyP) (WChar ch) ;

	GetParameter (&ChrIsHardKeyP, sizeof(void *), pChrIsHardKey);
	(*ChrIsHardKeyP)(ch) ;
								
}
#endif

////////////////////////////////////////////////////////////
// Clipboad functions, completed 3/3 functions now.
////////////////////////////////////////////////////////////
#ifdef L_ClipboardAddItem
void ClipboardAddItem (const ClipboardFormatType format, const void *ptr, UInt16 length)
{
	void (*ClipboardAddItemP) (const ClipboardFormatType format, const void *ptr, 
										UInt16 length);

	GetParameter (&ClipboardAddItemP, sizeof(void *), pClipboardAddItem);
	(*ClipboardAddItemP) (format, ptr, length);
}
#endif

#ifdef L_ClipboardAppendItem
Err ClipboardAppendItem (const ClipboardFormatType format, const void *ptr, UInt16 length)
{
	Err (*ClipboardAppendItemP) (const ClipboardFormatType format, const void *ptr, 
											UInt16 length);

	GetParameter (&ClipboardAppendItemP, sizeof(void *), pClipboardAppendItem);
	return	(*ClipboardAppendItemP) (format, ptr, length);
}
#endif

#ifdef L_ClipboardGetItem
MemHandle ClipboardGetItem (const ClipboardFormatType format, UInt16 *length)
{
	MemHandle (*ClipboardGetItemP) (const ClipboardFormatType format, UInt16 *length);

	GetParameter (&ClipboardGetItemP, sizeof(void *), pClipboardGetItem);
	return	(*ClipboardGetItemP) (format, length);
}
#endif



////////////////////////////////////////////////////////////
// Connection Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
#ifdef L_CncGetProfileList
Err CncGetProfileList(Char *** nameListP, UInt16 *count)
{
	Err (*CncGetProfileListP)(Char *** nameListP, UInt16 *count);

	GetParameter (&CncGetProfileListP, sizeof(void *), pCncGetProfileList);
	return   (*CncGetProfileListP)(nameListP, count);	
								
}
#endif
		
#ifdef L_CncGetProfileInfo
Err CncGetProfileInfo(Char *name, UInt32 *port, UInt32 *baud, UInt16 *volume,
		UInt16 *handShake, Char *initString, Char *resetString,
		Boolean *isModem, Boolean *isPulse)
{
	Err (*CncGetProfileInfoP)(Char *name, UInt32 *port, UInt32 *baud, UInt16 *volume,
		UInt16 *handShake, Char *initString, Char *resetString,
		Boolean *isModem, Boolean *isPulse);

	GetParameter (&CncGetProfileInfoP, sizeof(void *), pCncGetProfileInfo);
	return 	 (*CncGetProfileInfoP)(name, port, baud, volume,handShake, initString, resetString,
		                        isModem, isPulse);
 	
								
}
#endif

#ifdef L_CncAddProfile
Err CncAddProfile(Char *name, UInt32 port, UInt32 baud, UInt16 volume,
	 UInt16 handShake, Char *initString, Char *resetString, Boolean isModem,
	 Boolean isPulse)
{
	Err (*CncAddProfileP)(Char *name, UInt32 port, UInt32 baud, UInt16 volume,
	 UInt16 handShake, Char *initString, Char *resetString, Boolean isModem,
	 Boolean isPulse);

	GetParameter (&CncAddProfileP, sizeof(void *), pCncAddProfile);
	return   (*CncAddProfileP)(name,  port,  baud,  volume,
	                            handShake, initString, resetString,  isModem,  isPulse);
	
								
}
#endif

#ifdef L_CncDeleteProfile	 
Err CncDeleteProfile(Char *name)
{
	Err (*CncDeleteProfileP)(Char *name);

	GetParameter (&CncDeleteProfileP, sizeof(void *), pCncDeleteProfile);
	return    (*CncDeleteProfileP)(name);
	
								
}
#endif


////////////////////////////////////////////////////////////
// Control Handle Library, completed 20/20 functions now.
////////////////////////////////////////////////////////////
#ifdef L_CtlDrawControl
void CtlDrawControl (ControlType *controlP)
{
	void (*CtlDrawControlP) (ControlType *controlP);

	GetParameter (&CtlDrawControlP, sizeof(void *), pCtlDrawControl);
	(*CtlDrawControlP) (controlP);
}
#endif

#ifdef L_CtlEnabled
Boolean CtlEnabled (const ControlType *controlP)
{
	Boolean (*CtlEnabledP) (const ControlType *controlP);

	GetParameter (&CtlEnabledP, sizeof(void *), pCtlEnabled);
	return	(*CtlEnabledP) (controlP);
}
#endif

#ifdef L_CtlEraseControl
void CtlEraseControl (ControlType *controlP)
{
	void (*CtlEraseControlP) (ControlType *controlP);

	GetParameter (&CtlEraseControlP, sizeof(void *), pCtlEraseControl);
	(*CtlEraseControlP) (controlP);
}
#endif

#ifdef L_CtlGetLabel
const Char *CtlGetLabel (const ControlType *controlP)
{

	const Char *(*CtlGetLabelP) (const ControlType *controlP);

	GetParameter (&CtlGetLabelP, sizeof(void *), pCtlGetLabel);
	return(*CtlGetLabelP) (controlP);
}
#endif

#ifdef L_CtlGetSliderValues
void CtlGetSliderValues (const ControlType *controlP, UInt16 *minValueP,
								  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP)
{
	void (*CtlGetSliderValuesP) (const ControlType *controlP, UInt16 *minValueP,
									  UInt16 *maxValueP, UInt16 *pageSizeP, UInt16 *valueP);

	GetParameter (&CtlGetSliderValuesP, sizeof(void *), pCtlGetSliderValues);
	(*CtlGetSliderValuesP) (controlP, minValueP,  maxValueP, pageSizeP, valueP);
}
#endif

#ifdef L_CtlGetValue
Int16 CtlGetValue (const ControlType *controlP)
{
	Int16 (*CtlGetValueP) (const ControlType *controlP);

	GetParameter (&CtlGetValueP, sizeof(void *), pCtlGetValue);
	return (*CtlGetValueP) (controlP);
}
#endif

#ifdef L_CtlHandleEvent
Boolean CtlHandleEvent (ControlType *controlP, EventType pEvent)
{
	Boolean (*CtlHandleEventP) (ControlType *controlP, EventType pEvent);

	GetParameter (&CtlHandleEventP, sizeof(void *), pCtlHandleEvent);
	return (*CtlHandleEventP) (controlP,  pEvent);
}
#endif

#ifdef L_CtlHideControl
void CtlHideControl (ControlType *controlP)
{
	void (*CtlHideControlP) (ControlType *controlP);

	GetParameter (&CtlHideControlP, sizeof(void *), pCtlHideControl);
	(*CtlHideControlP) (controlP);
}
#endif

#ifdef L_CtlHitControl
void CtlHitControl (const ControlType *controlP)
{
	void (*CtlHitControlP) (const ControlType *controlP);

	GetParameter (&CtlHitControlP, sizeof(void *), pCtlHitControl);
	(*CtlHitControlP) (controlP);
}
#endif

#ifdef L_CtlNewControl
ControlType *CtlNewControl (void **formPP, UInt16 ID, ControlStyleType style,
								   const Char *textP, Coord x, Coord y, Coord width,
								   Coord height, FontID font, UInt8 group, 
								   Boolean leftAnchor)
{
	ControlType *(*CtlNewControlP) (void **formPP, UInt16 ID, ControlStyleType style,
								   const Char *textP, Coord x, Coord y, Coord width,
								   Coord height, FontID font, UInt8 group, 
								   Boolean leftAnchor);

	GetParameter (&CtlNewControlP, sizeof(void *), pCtlNewControl);
	return(*CtlNewControlP) (formPP,  ID,  style,   textP,  x,  y,  width,  height,  font,  group, 
								    leftAnchor);
}
#endif

#ifdef L_CtlNewGraphicControl
GraphicControlType *CtlNewGraphicControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID bitmapID, 
								   DmResID selectedBitmapID, Coord x, Coord y, 
								   Coord width, Coord height, UInt8 group, 
								   Boolean leftAnchor)
{
	GraphicControlType *(*CtlNewGraphicControlP) (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID bitmapID, 
								   DmResID selectedBitmapID, Coord x, Coord y, 
								   Coord width, Coord height, UInt8 group, 
								   Boolean leftAnchor);

	GetParameter (&CtlNewGraphicControlP, sizeof(void *), pCtlNewGraphicControl);
	return(*CtlNewGraphicControlP) (formPP,  ID,  style,  bitmapID, selectedBitmapID,  x,  y, 
								    width,  height,  group, 
								    leftAnchor);
}
#endif

#ifdef L_CtlNewSliderControl
SliderControlType *CtlNewSliderControl (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID thumbID, 
								   DmResID backgroundID, Coord x, Coord y, 
								   Coord width, Coord height, UInt16 minValue,
								   UInt16 maxValue, UInt16 pageSize, UInt16 value)
{
	SliderControlType *(*CtlNewSliderControlP) (void **formPP, UInt16 ID, 
								   ControlStyleType style, DmResID thumbID, 
								   DmResID backgroundID, Coord x, Coord y, 
								   Coord width, Coord height, UInt16 minValue,
								   UInt16 maxValue, UInt16 pageSize, UInt16 value);

	GetParameter (&CtlNewSliderControlP, sizeof(void *), pCtlNewSliderControl);
	return(*CtlNewSliderControlP) (formPP,  ID,  style,  thumbID, 
								    backgroundID,  x,  y, 
								    width,  height,  minValue,
								    maxValue,  pageSize,  value);
}
#endif

#ifdef L_CtlSetEnabled
void CtlSetEnabled (ControlType *controlP, Boolean enable)
{
	void (*CtlSetEnabledP) (ControlType *controlP, Boolean enable);

	GetParameter (&CtlSetEnabledP, sizeof(void *), pCtlSetEnabled);
	(*CtlSetEnabledP) (controlP,  enable);
}
#endif

#ifdef L_CtlSetLabel
void CtlSetLabel (ControlType *controlP, const Char *newLabel)
{
	void (*CtlSetLabelP) (ControlType *controlP, const Char *newLabel);

	GetParameter (&CtlSetLabelP, sizeof(void *), pCtlSetLabel);
	(*CtlSetLabelP) (controlP,  newLabel);
}
#endif

#ifdef L_CtlSetGraphics
void CtlSetGraphics (ControlType *controlP, DmResID newBitmapID,
							  DmResID newSelectedBitmapID)
{
	void (*CtlSetGraphicsP) (ControlType *controlP, DmResID newBitmapID,
							  DmResID newSelectedBitmapID);

	GetParameter (&CtlSetGraphicsP, sizeof(void *), pCtlSetGraphics);
	(*CtlSetGraphicsP) (controlP, newBitmapID,   newSelectedBitmapID);
}
#endif

#ifdef L_CtlSetSliderValue 
void CtlSetSliderValue (ControlType *controlP, const UInt16 *minValueP,
								  const UInt16 *maxValueP, const UInt16 *pageSizeP, 
								  const UInt16 *valueP)
{
	void (*CtlSetSliderValueP) (ControlType *controlP, const UInt16 *minValueP,
								  const UInt16 *maxValueP, const UInt16 *pageSizeP, 
								  const UInt16 *valueP);

	GetParameter (&CtlSetSliderValueP, sizeof(void *), pCtlSetSliderValue);
	(*CtlSetSliderValueP) (controlP, minValueP,   maxValueP,  pageSizeP, 
								   valueP);
}
#endif

#ifdef L_CtlSetUsable
void CtlSetUsable (ControlType *controlP, Boolean usable)
{
	void(*CtlSetUsableP)  (ControlType *controlP, Boolean usable);

	GetParameter (&CtlSetUsableP, sizeof(void *), pCtlSetUsable);
	(*CtlSetUsableP)  (controlP, usable);
}
#endif

#ifdef L_CtlSetValue
void CtlSetValue (ControlType *controlP, Int16 newValue)
{
	void (*CtlSetValueP) (ControlType *controlP, Int16 newValue);

	GetParameter (&CtlSetValueP, sizeof(void *), pCtlSetValue);
	(*CtlSetValueP) (controlP,  newValue);
}
#endif

#ifdef L_CtlShowControl
void CtlShowControl (ControlType *controlP)
{
	void (*CtlShowControlP) (ControlType *controlP);

	GetParameter (&CtlShowControlP, sizeof(void *), pCtlShowControl);
	(*CtlShowControlP) (controlP);
}
#endif

#ifdef L_CtlValidatePointer
Boolean CtlValidatePointer (const ControlType *controlP)
{
	Boolean (*CtlValidatePointerP) (const ControlType *controlP);

	GetParameter (&CtlValidatePointerP, sizeof(void *), pCtlValidatePointer);
	return (*CtlValidatePointerP) ( controlP);
}
#endif




///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 6/6 functions now.
///////////////////////////////////////////////////////////////
/*
#ifdef L_DayHandleEvent
Boolean DayHandleEvent(const DaySelectorPtr pSelector,const EventType *pEvent)
{
	Boolean (*DayHandleEventP)(const DaySelectorPtr pSelector,const EventType *pEvent);

	GetParameter (&DayHandleEventP, sizeof(void *), pDayHandleEvent);
	return  (*DayHandleEventP)( pSelector,pEvent);

}
#endif
*/
/*
#ifdef L_SelectDay
Boolean SelectDay(const SelectDayType selectDayBy, Int16 *month,Int16 *day, Int16 *year, const Char *title)
{
	Boolean (*SelectDayP)(const SelectDayType selectDayBy, Int16 *month,Int16 *day, Int16 *year, const Char *title);

	GetParameter (&SelectDayP, sizeof(void *), pSelectDay);
	return  (*SelectDayP)( selectDayBy, month,day, year, title);
}
#endif
*/
#ifdef L_SelectDay
Boolean SelectDay (Int16 *month, Int16 *day,Int16 *year, const Char title)
{
	Boolean (*SelectDayP) (Int16 *month, Int16 *day,Int16 *year, const Char title);

	GetParameter (&SelectDayP, sizeof(void *), pSelectDay);
	return  (*SelectDayP) (month, day,year, title);	
}
#endif


#ifdef L_SelectOneTime
Boolean SelectOneTime (Int16 *hour, Int16 *minute,const Char *titleP)
{
	Boolean (*SelectOneTimeP) (Int16 *hour, Int16 *minute,const Char *titleP);

	GetParameter (&SelectOneTimeP, sizeof(void *), pSelectOneTime);
	return  (*SelectOneTimeP) (hour, minute, titleP);	
}
#endif

#ifdef L_SelectTime
Boolean SelectTime (TimeType * startTimeP,TimeType * endTimeP, Boolean untimed, const Char *titleP, Int16 startOfDay, Int16 endOfDay,Int16 startOfDisplay)
{
	Boolean (*SelectTimeP) (TimeType * startTimeP,TimeType * endTimeP, Boolean untimed, const Char *titleP, Int16 startOfDay, Int16 endOfDay,Int16 startOfDisplay);

	GetParameter (&SelectTimeP, sizeof(void *), pSelectTime);
	return  (*SelectTimeP) (startTimeP, endTimeP,  untimed,  titleP,  startOfDay,  endOfDay, startOfDisplay);	
}
#endif

#ifdef L_SelectTimeV33
Boolean SelectTimeV33 (TimeType *startTimeP,TimeType *EndTimeP, Boolean untimed, Char *title,Int16 startOfDay)
{
	Boolean (*SelectTimeV33P) (TimeType *startTimeP,TimeType *EndTimeP, Boolean untimed, Char *title,Int16 startOfDay);

	GetParameter (&SelectTimeV33P, sizeof(void *), pSelectTimeV33);
	return  (*SelectTimeV33P) (startTimeP,EndTimeP,  untimed, title, startOfDay);	
}
#endif




