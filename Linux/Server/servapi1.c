#include <VCommon.h>
#include <VParser.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#include "wisapi.h"

////////////////////////////////////////////////////////////
// Alarm Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeAlmGetAlarm (void)
{
	WriteParameter (AlmGetAlarm, sizeof(void*), pAlmGetAlarm);
}

void PipeAlmGetProcAlarm (void)
{
	WriteParameter (AlmGetProcAlarm, sizeof(void*), pAlmGetProcAlarm);
}

void PipeAlmSetAlarm (void)
{
	WriteParameter (AlmSetAlarm, sizeof(void*), pAlmSetAlarm);
}

void PipeAlmSetProcAlarm (void)
{
	WriteParameter (AlmSetProcAlarm, sizeof(void*), pAlmSetProcAlarm);
}


////////////////////////////////////////////////////////////
// Bitmap Processing Library, completed 9/9 functions now.
////////////////////////////////////////////////////////////
void PipeBmpBitsSize (void)
{
//	WriteParameter (BmpBitsSize, sizeof(void*), pBmpBitsSize);
}
void PipeBmpColortableSize (void)
{
//	WriteParameter (BmpColortableSize, sizeof(void*), pBmpColortableSize);
}
void PipeBmpCompress (void)
{
//	WriteParameter (BmpCompress, sizeof(void*), pBmpCompress);
}
void PipeBmpCreate (void)
{
//	WriteParameter (BmpCreate, sizeof(void*), pBmpCreate);
}
void PipeBmpDelete (void)
{
//	WriteParameter (BmpDelete, sizeof(void*), pBmpDelete);
}
void PipeBmpGetBits (void)
{
//	WriteParameter (BmpGetBits, sizeof(void*), pBmpGetBits);
}
void PipeBmpGetColortable (void)
{
//	WriteParameter (BmpGetColortable, sizeof(void*), pBmpGetColortable);
}
void PipeBmpSize (void)
{
//	WriteParameter (BmpSize, sizeof(void*), pBmpSize);
}
void PipeColorTableEntries (void)
{
//	WriteParameter (ColorTableEntries , sizeof(void*), pColorTableEntries );
}



////////////////////////////////////////////////////////////
// Category Library, completed 16/16 functions now.
////////////////////////////////////////////////////////////
void PipeCategoryCreateList (void)
{
	WriteParameter (CategoryCreateList, sizeof(void*), pCategoryCreateList);

}

void PipeCategoryEdit (void)
{
//	WriteParameter (CategoryEdit, sizeof(void*), pCategoryEdit);
}

void PipeCategoryFind (void)
{
	WriteParameter (CategoryFind, sizeof(void*), pCategoryFind);
}

void PipeCategoryFreeList (void)
{
	WriteParameter (CategoryFreeList, sizeof(void*), pCategoryFreeList);
}

void PipeCategoryGetName (void)
{
	WriteParameter (CategoryGetName, sizeof(void*), pCategoryGetName);
}

void PipeCategoryGetNext (void)
{
	WriteParameter (CategoryGetNext, sizeof(void*), pCategoryGetNext);
}

void PipeCategoryInitialize (void)
{
	WriteParameter (CategoryInitialize, sizeof(void*), pCategoryInitialize);
}

void PipeCategorySelect (void)
{
	WriteParameter (CategorySelect, sizeof(void*), pCategorySelect);
}

void PipeCategorySetName (void)
{
	WriteParameter (CategorySetName, sizeof(void*), pCategorySetName);
}

void PipeCategorySetTriggerLabel (void)
{
	WriteParameter (CategorySetTriggerLabel, sizeof(void*), pCategorySetTriggerLabel);
}

void PipeCategoryTruncateName (void)
{
	WriteParameter (CategoryTruncateName, sizeof(void*), pCategoryTruncateName);
}



void PipeCategoryCreateListV10(void)
{
//	WriteParameter (CategoryCreateListV10, sizeof(void*), pCategoryCreateListV10);
}
void PipeCategoryEditV20 (void)
{
//	WriteParameter (CategoryEditV20, sizeof(void*), pCategoryEditV20);
}
void PipeCategoryEditV10(void)
{
//	WriteParameter (CategoryEditV10, sizeof(void*), pCategoryEditV10);
}
void PipeCategoryFreeListV10 (void)
{
//	WriteParameter (CategoryFreeListV10, sizeof(void*), pCategoryFreeListV10);
}
void PipeCategorySelectV10 (void)
{
//	WriteParameter (CategorySelectV10, sizeof(void*), pCategorySelectV10);
}

////////////////////////////////////////////////////////////
// Character Attributes Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeChrHorizEllipsis (void)
{
//	WriteParameter (ChrHorizEllipsis, sizeof(void*), pChrHorizEllipsis);
}
void PipeChrIsHardKey(void)
{
//	WriteParameter (ChrIsHardKey, sizeof(void*), pChrIsHardKey);
}
void PipeChrNumericSpace (void)
{
//	WriteParameter (ChrNumericSpace, sizeof(void*), pChrNumericSpace);
}
void PipeGetCharAttr (void)
{
//	WriteParameter (GetCharAttr, sizeof(void*), pGetCharAttr);
}
void PipeGetCharCaselessValue (void)
{
//	WriteParameter (GetCharCaselessValue, sizeof(void*), pGetCharCaselessValue);
}
void PipeGetCharSortValue (void)
{
//	WriteParameter (GetCharSortValue, sizeof(void*), pGetCharSortValue);
}



////////////////////////////////////////////////////////////
// Clipboad functions, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeClipboardAddItem (void)
{
	WriteParameter (ClipboardAddItem, sizeof(void*), pClipboardAddItem);
}

void PipeClipboardAppendItem (void)
{
//	WriteParameter (ClipboardAppendItem, sizeof(void*), pClipboardAppendItem);
}

void PipeClipboardGetItem (void)
{
//	WriteParameter (ClipboardGetItem, sizeof(void*), pClipboardGetItem);
}



////////////////////////////////////////////////////////////
// Connection Manager Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipeCncAddProfile(void)
{
//	WriteParameter (CncAddProfile, sizeof(void*), pCncAddProfile);
}
void PipeCncDeleteProfile(void)
{
//	WriteParameter (CncDeleteProfile, sizeof(void*), pCncDeleteProfile);
}
void PipeCncGetProfileInfo(void)
{
//	WriteParameter (CncGetProfileInfo, sizeof(void*), pCncGetProfileInfo);
}
void PipeCncGetProfileList(void)
{
//	WriteParameter (CncGetProfileList, sizeof(void*), pCncGetProfileList);
}



////////////////////////////////////////////////////////////
// Control Handle Library, completed 20/20 functions now.
////////////////////////////////////////////////////////////
void PipeCtlDrawControl (void)
{
	WriteParameter (CtlDrawControl, sizeof(void*), pCtlDrawControl);
}

void PipeCtlEnabled (void)
{
	WriteParameter (CtlEnabled, sizeof(void*), pCtlEnabled);
}

void PipeCtlEraseControl (void)
{
	WriteParameter (CtlEraseControl, sizeof(void*), pCtlEraseControl);
}

void PipeCtlGetLabel (void)
{
	WriteParameter (CtlGetLabel, sizeof(void*), pCtlGetLabel);
}

void PipeCtlGetSliderValues (void)
{
	WriteParameter (CtlGetSliderValues, sizeof(void*), pCtlGetSliderValues);
}

void PipeCtlGetValue (void)
{
	WriteParameter (CtlGetValue, sizeof(void*), pCtlGetValue);
}

void PipeCtlHandleEvent (void)
{
//	WriteParameter (CtlHandleEvent, sizeof(void*), pCtlHandleEvent);
}

void PipeCtlHideControl (void)
{
	WriteParameter (CtlHideControl, sizeof(void*), pCtlHideControl);
}

void PipeCtlHitControl (void)
{
	WriteParameter (CtlHitControl, sizeof(void*), pCtlHitControl);
}

void PipeCtlNewControl (void)
{
	WriteParameter (CtlNewControl, sizeof(void*), pCtlNewControl);
}

void PipeCtlNewGraphicControl (void)
{
	WriteParameter (CtlNewGraphicControl, sizeof(void*), pCtlNewGraphicControl);
}

void PipeCtlNewSliderControl (void)
{
	WriteParameter (CtlNewSliderControl, sizeof(void*), pCtlNewSliderControl);
}

void PipeCtlSetEnabled (void)
{
	WriteParameter (CtlSetEnabled, sizeof(void*), pCtlSetEnabled);
}

void PipeCtlSetLabel (void)
{
	WriteParameter (CtlSetLabel, sizeof(void*), pCtlSetLabel);
}

void PipeCtlSetGraphics (void)
{
	WriteParameter (CtlSetGraphics, sizeof(void*), pCtlSetGraphics);
}

void PipeCtlSetSliderValue (void)
{
//	WriteParameter (CtlSetSliderValue, sizeof(void*), pCtlSetSliderValue);
}

void PipeCtlSetUsable (void)
{
	WriteParameter (CtlSetUsable, sizeof(void*), pCtlSetUsable);
}

void PipeCtlSetValue (void)
{
	WriteParameter (CtlSetValue, sizeof(void*), pCtlSetValue);
}

void PipeCtlShowControl (void)
{
	WriteParameter (CtlShowControl, sizeof(void*), pCtlShowControl);
}

void PipeCtlValidatePointer (void)
{
	WriteParameter (CtlValidatePointer, sizeof(void*), pCtlValidatePointer);
}




///////////////////////////////////////////////////////////////
// Date and Time Selector Library, completed 6/6 functions now.
///////////////////////////////////////////////////////////////

void PipeDayHandleEvent (void)
{
//	WriteParameter (DayHandleEvent, sizeof(void*), pDayHandleEvent);
}
void PipeSelectDay (void)
{
//	WriteParameter (SelectDay, sizeof(void*), pSelectDay);
}
void PipeSelectDayV10 (void)
{
//	WriteParameter (SelectDayV10, sizeof(void*), pSelectDayV10);
}
void PipeSelectOneTime (void)
{
//	WriteParameter (SelectOneTime, sizeof(void*), pSelectOneTime);
}
void PipeSelectTime (void)
{
//	WriteParameter (SelectTime, sizeof(void*), pSelectTime);
}
void PipeSelectTimeV33 (void)
{
//	WriteParameter (SelectTimeV33 , sizeof(void*), pSelectTimeV33 );
}

