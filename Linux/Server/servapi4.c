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
// Font Processing Library, completed 18/18 functions now.
////////////////////////////////////////////////////////////
void PipeFntAverageCharWidth  (void)
{
        WriteParameter (FntAverageCharWidth, sizeof(void*), pFntAverageCharWidth);
}

void PipeFntCharHeight  (void)
{
	WriteParameter (FntCharHeight, sizeof(void*), pFntCharHeight);
}

void PipeFntCharsInWidth  (void)
{
	WriteParameter (FntCharsInWidth, sizeof(void*), pFntCharsInWidth);
}

void PipeFntCharsWidth (void)
{
	WriteParameter (FntCharsWidth, sizeof(void*), pFntCharsWidth);
}

void PipeFntCharWidth  (void)
{
	WriteParameter (FntCharWidth, sizeof(void*), pFntCharWidth);
}

void PipeFntGetFont  (void)
{
	WriteParameter (FntGetFont, sizeof(void*), pFntGetFont);
}

void PipeFntLineHeight  (void)
{
	WriteParameter (FntLineHeight, sizeof(void*), pFntLineHeight);
}

void PipeFntLineWidth  (void)
{
	WriteParameter (FntSetFont, sizeof(void*), pFntSetFont);
}

void PipeFntSetFont (void)
{
	WriteParameter (FntSetFont, sizeof(void*), pFntSetFont);
}

void PipeFntWordWrap (void)
{
	WriteParameter (FntWordWrap, sizeof(void*), pFntWordWrap);
}


void PipeFntBaseLine(void)
{
//	WriteParameter (FntBaseLine, sizeof(void*), pFntBaseLine);
}
void PipeFntDefineFont(void)
{
//	WriteParameter (FntDefineFont, sizeof(void*), pFntDefineFont);
}
void PipeFntGetFontPtr(void)
{
//	WriteParameter (FntGetFontPtr, sizeof(void*), pFntGetFontPtr);
}
void PipeFntGetScrollValues(void)
{
//	WriteParameter (FntGetScrollValues, sizeof(void*), pFntGetScrollValues);
}
void PipeFntWidthToOffset(void)
{
//	WriteParameter (FntWidthToOffset, sizeof(void*), pFntWidthToOffset);
}
void PipeFntWordWrapReverseNLines(void)
{
//	WriteParameter (FntWordWrapReverseNLines, sizeof(void*), pFntWordWrapReverseNLines);
}
void PipeFontSelect(void)
{
//	WriteParameter (FontSelect, sizeof(void*), pFontSelect);
}



////////////////////////////////////////////////////////////
// Form Processing Library, completed 65/65 functions now.
////////////////////////////////////////////////////////////
void PipeFrmAlert  (void)
{
	WriteParameter (FrmAlert, sizeof(void*), pFrmAlert);
}

void PipeFrmCloseAllForms  (void)
{
	WriteParameter (FrmCloseAllForms, sizeof(void*), pFrmCloseAllForms);
}

void PipeFrmCopyLabel (void)
{
	WriteParameter (FrmCopyLabel, sizeof(void*), pFrmCopyLabel);
}

void PipeFrmCopyTitle  (void)
{
	WriteParameter (FrmCopyTitle, sizeof(void*), pFrmCopyTitle);
}

void PipeFrmCustomAlert  (void)
{
	WriteParameter (FrmCustomAlert, sizeof(void*), pFrmCustomAlert);
}

void PipeFrmCustomResponseAlert  (void)
{
//	WriteParameter (FrmCustomResponseAlert, sizeof(void*), pFrmCustomResponseAlert);
}

void PipeFrmDeleteForm  (void)
{
	WriteParameter (FrmDeleteForm, sizeof(void*), pFrmDeleteForm);
}

void PipeFrmDispatchEvent (void)
{
	WriteParameter (FrmDispatchEvent, sizeof(void*), pFrmDispatchEvent);
}

void PipeFrmDoDialog  (void)
{
	WriteParameter (FrmDoDialog, sizeof(void*), pFrmDoDialog);
}

void PipeFrmDrawForm (void)
{
	WriteParameter (FrmDrawForm, sizeof(void*), pFrmDrawForm);
}

void PipeFrmEraseForm  (void)
{
	WriteParameter (FrmEraseForm, sizeof(void*), pFrmEraseForm);
}

void PipeFrmGetActiveForm  (void)
{
	WriteParameter (FrmGetActiveForm, sizeof(void*), pFrmGetActiveForm);
}

void PipeFrmGetActiveFormID (void)
{
	WriteParameter (FrmGetActiveFormID, sizeof(void*), pFrmGetActiveFormID);
}

void PipeFrmGetControlGroupSelection  (void)
{
//	WriteParameter (FrmGetControlGroupSelection , sizeof(void*), pFrmGetControlGroupSelection);
}

void PipeFrmGetControlValue (void)
{
	WriteParameter (FrmGetControlValue, sizeof(void*), pFrmGetControlValue);
}

void PipeFrmGetFirstForm  (void)
{
	WriteParameter (FrmGetFirstForm, sizeof(void*), pFrmGetFirstForm);
}

void PipeFrmGetFocus (void)
{
	WriteParameter (FrmGetFocus, sizeof(void*), pFrmGetFocus);
}

void PipeFrmGetFormBounds  (void)
{
	WriteParameter (FrmGetFormBounds, sizeof(void*), pFrmGetFormBounds);
}

void PipeFrmGetFormId  (void)
{
	WriteParameter (FrmGetFormId, sizeof(void*), pFrmGetFormId);
}

void PipeFrmGetFormPtr (void)
{
	WriteParameter (FrmGetFormPtr, sizeof(void*), pFrmGetFormPtr);
}

void PipeFrmGetGadgetData  (void)
{
	WriteParameter (FrmGetGadgetData, sizeof(void*), pFrmGetGadgetData);
}

void PipeFrmGetLabel  (void)
{
	WriteParameter (FrmGetLabel, sizeof(void*), pFrmGetLabel);
}

void PipeFrmGetNumberOfObjects (void)
{
	WriteParameter (FrmGetNumberOfObjects, sizeof(void*), pFrmGetNumberOfObjects);
}

void PipeFrmGetObjectBounds  (void)
{
	WriteParameter (FrmGetObjectBounds, sizeof(void*), pFrmGetObjectBounds);
}

void PipeFrmGetObjectId  (void)
{
	WriteParameter (FrmGetObjectId, sizeof(void*), pFrmGetObjectId);
}

void PipeFrmGetObjectIndex (void)
{
	WriteParameter (FrmGetObjectIndex, sizeof(void*), pFrmGetObjectIndex);
}

void PipeFrmGetObjectPosition (void)
{
	WriteParameter (FrmGetObjectPosition, sizeof(void*), pFrmGetObjectPosition);
}

void PipeFrmGetObjectPtr  (void)
{
	WriteParameter (FrmGetObjectPtr, sizeof(void*), pFrmGetObjectPtr);
}

void PipeFrmGetObjectType  (void)
{
	WriteParameter (FrmGetObjectType, sizeof(void*), pFrmGetObjectType);
}

void PipeFrmGetTitle  (void)
{
	WriteParameter (FrmGetTitle, sizeof(void*), pFrmGetTitle);
}

void PipeFrmGetWindowHandle  (void)
{
	WriteParameter (FrmGetWindowHandle, sizeof(void*), pFrmGetWindowHandle);
}

void PipeFrmGotoForm  (void)
{
	WriteParameter (FrmGotoForm, sizeof(void*), pFrmGotoForm);
}

void PipeFrmHandleEvent (void)
{
	WriteParameter (FrmHandleEvent, sizeof(void*), pFrmHandleEvent);
}

void PipeFrmHelp  (void)
{
	WriteParameter (FrmHelp, sizeof(void*), pFrmHelp);
}

void PipeFrmHideObject (void)
{
	WriteParameter (FrmHideObject, sizeof(void*), pFrmHideObject);
}

void PipeFrmInitForm (void)
{
	WriteParameter (FrmInitForm, sizeof(void*), pFrmInitForm);
}

void PipeFrmNewBitmap  (void)
{
//	WriteParameter (FrmNewBitmap, sizeof(void*), pFrmNewBitmap);
}

void PipeFrmNewForm  (void)
{      
	WriteParameter (FrmNewForm, sizeof(void*), pFrmNewForm);
}			
				  						 
void PipeFrmNewGadget (void)
{
//	WriteParameter (FrmNewGadget, sizeof(void*), pFrmNewGadget);
}

void PipeFrmNewGsi (void)
{
//	WriteParameter (FrmNewGsi, sizeof(void*), pFrmNewGsi);
}	

void PipeFrmNewLabel  (void)
{
	WriteParameter (FrmNewLabel, sizeof(void*), pFrmNewLabel);
}	
void PipeFrmPointInTitle  (void)
{
	WriteParameter (FrmPointInTitle, sizeof(void*), pFrmPointInTitle);
}	
void PipeFrmPopupForm  (void)
{
	WriteParameter (FrmPopupForm, sizeof(void*), pFrmPopupForm);
}	
void PipeFrmRemoveObject  (void)
{
	WriteParameter (FrmRemoveObject, sizeof(void*), pFrmRemoveObject);
}	
void PipeFrmRestoreActiveState  (void)
{
	WriteParameter (FrmRestoreActiveState, sizeof(void*), pFrmRestoreActiveState);
}	
void PipeFrmReturnToForm  (void)
{
	WriteParameter (FrmReturnToForm, sizeof(void*), pFrmReturnToForm);
}	
void PipeFrmSaveActiveState (void)
{
	WriteParameter (FrmSaveActiveState, sizeof(void*), pFrmSaveActiveState);
}	
void PipeFrmSaveAllForms (void)
{
	WriteParameter (FrmSaveAllForms, sizeof(void*), pFrmSaveAllForms);
}	
void PipeFrmSetActiveForm(void)
{
	WriteParameter (FrmSetActiveForm, sizeof(void*), pFrmSetActiveForm);
}	
void PipeFrmSetCategoryLabel (void)
{
	WriteParameter (FrmSetCategoryLabel, sizeof(void*), pFrmSetCategoryLabel);
}	
void PipeFrmSetControlGroupSelection (void)
{
	WriteParameter (FrmSetControlGroupSelection, sizeof(void*), pFrmSetControlGroupSelection);
}	
void PipeFrmSetControlValue (void)
{
	WriteParameter (FrmSetControlValue, sizeof(void*), pFrmSetControlValue);
}	
void PipeFrmSetEventHandler(void)
{
	WriteParameter (FrmSetEventHandler, sizeof(void*), pFrmSetEventHandler);
}	
void PipeFrmSetFocus(void)
{
	WriteParameter (FrmSetFocus, sizeof(void*), pFrmSetFocus);
}	

void PipeFrmSetGadgetData (void)
{
//	WriteParameter (FrmSetGadgetData, sizeof(void*), pFrmSetGadgetData);
}	

void PipeFrmSetGadgetHandler (void)
{
//	WriteParameter (FrmSetGadgetHandler, sizeof(void*), pFrmSetGadgetHandler);
}
	
void PipeFrmSetMenu (void)
{
	WriteParameter (FrmSetMenu, sizeof(void*), pFrmSetMenu);
}	
void PipeFrmSetObjectBounds (void)
{
	WriteParameter (FrmSetObjectBounds, sizeof(void*), pFrmSetObjectBounds);
}	
void PipeFrmSetObjectPosition (void)
{
	WriteParameter (FrmSetObjectPosition, sizeof(void*), pFrmSetObjectPosition);
}	
void PipeFrmSetTitle (void)
{
	WriteParameter (FrmSetTitle, sizeof(void*), pFrmSetTitle);
}	
void PipeFrmShowObject (void)
{
	WriteParameter (FrmShowObject, sizeof(void*), pFrmShowObject);
}	

void PipeFrmUpdateForm (void)
{
//	WriteParameter (FrmUpdateForm, sizeof(void*), pFrmUpdateForm);
}	

void PipeFrmUpdateScrollers (void)
{
//	WriteParameter (FrmUpdateScrollers, sizeof(void*), pFrmUpdateScrollers);
}									 

void PipeFrmValidatePtr (void)
{
	WriteParameter (FrmValidatePtr, sizeof(void*), pFrmValidatePtr);
}	
void PipeFrmVisible (void)
{
	WriteParameter (FrmVisible, sizeof(void*), pFrmVisible);
}	
