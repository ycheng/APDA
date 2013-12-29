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
// Font Processing Library, completed 18/18 functions now.
////////////////////////////////////////////////////////////
#ifdef L_FntAverageCharWidth
Int16 FntAverageCharWidth (void)
{
	Int16 (*FntAverageCharWidthP) (void);

	GetParameter (&FntAverageCharWidthP, sizeof(void *), pFntAverageCharWidth);
	return (*FntAverageCharWidthP) ();
}
#endif

#ifdef L_FntCharHeight
Int16 FntCharHeight (void)
{
	Int16 (*FntCharHeightP) (void);
	
	GetParameter (&FntCharHeightP, sizeof(void *), pFntCharHeight);
	return (*FntCharHeightP) ();
}
#endif

#ifdef L_FntCharsInWidth
void FntCharsInWidth (Char const *string, Int16 *stringWidthP,
                        Int16 *stringLengthP, Boolean *fitWithinWidth)
{
	void (*FntCharsInWidthP) (Char const *string, Int16 *stringWidthP,
	                Int16 *stringLengthP, Boolean *fitWithinWidth);

	GetParameter (&FntCharsInWidthP, sizeof(void *), pFntCharsInWidth);
	(*FntCharsInWidthP) (string, stringWidthP,stringLengthP, fitWithinWidth);
}
#endif

#ifdef L_FntCharsWidth
Int16 FntCharsWidth (const Char *chars, Int16 len)
{
	Int16 (*FntCharsWidthP) (const Char *chars, Int16 len);

	GetParameter (&FntCharsWidthP, sizeof(void *), pFntCharsWidth);
	return (*FntCharsWidthP) ( chars,  len);
}
#endif

#ifdef L_FntCharWidth
Int16 FntCharWidth (Char ch)
{
	Int16 (*FntCharWidthP) (Char ch);

	GetParameter (&FntCharWidthP, sizeof(void *), pFntCharWidth);
	return (*FntCharWidthP) (ch);
}
#endif

#ifdef L_FntGetFont
FontID FntGetFont (void)
{
	FontID (*FntGetFontP) (void);

	GetParameter (&FntGetFontP, sizeof(void *), pFntGetFont);
	return(*FntGetFontP) ();
}
#endif

#ifdef L_FntLineHeight
Int16 FntLineHeight (void)
{
	Int16 (*FntLineHeightP) (void);

	GetParameter (&FntLineHeightP, sizeof(void *), pFntLineHeight);
	return (*FntLineHeightP) ();
}
#endif

#ifdef L_FntLineWidth
Int16 FntLineWidth (Char const *pChar, UInt16 length)
{
	Int16 (*FntLineWidthP) (Char const *pChar, UInt16 length);

	GetParameter (&FntLineWidthP, sizeof(void *), pFntLineWidth);
	return (*FntLineWidthP) (pChar,  length);
}
#endif

#ifdef L_FntSetFont
FontID FntSetFont (FontID font)
{
	FontID (*FntSetFontP) (FontID font);

	GetParameter (&FntSetFontP, sizeof(void *), pFntSetFont);
	return (*FntSetFontP) ( font);
}
#endif

#ifdef L_FntWordWrap
UInt16 FntWordWrap (const Char *chars, UInt16 maxWidth)
{
	UInt16 (*FntWordWrapP) (const Char *chars, UInt16 maxWidth);

	GetParameter (&FntWordWrapP, sizeof(void *), pFntWordWrap);
	return (*FntWordWrapP) (chars, maxWidth);
}
#endif



#ifdef L_FntGetFontPtr
FontPtr FntGetFontPtr (void)
{
	FontPtr (*FntGetFontPtrP) (void);
	
	GetParameter (&FntGetFontPtrP, sizeof(void *), pFntGetFontPtr);
	return 		(*FntGetFontPtrP) ();
}
#endif
							
#ifdef L_FntBaseLine
Int16 FntBaseLine (void)
{
	Int16 (*FntBaseLineP) (void);

	GetParameter (&FntBaseLineP, sizeof(void *), pFntBaseLine);
	return 	(*FntBaseLineP) ();
}
#endif





#ifdef L_FntWidthToOffset
Int16 FntWidthToOffset (Char const *pChars, UInt16 length,
	Int16 pixelWidth, Boolean *leadingEdge, Int16 *truncWidth)
{
	Int16 (*FntWidthToOffsetP) (Char const *pChars, UInt16 length,
				Int16 pixelWidth, Boolean *leadingEdge, Int16 *truncWidth);

	GetParameter (&FntWidthToOffsetP, sizeof(void *), pFntWidthToOffset);
	return (*FntWidthToOffsetP) ( pChars,  length,
				 pixelWidth, leadingEdge, truncWidth);
}
#endif
							

#ifdef L_FntDescenderHeight
Int16 FntDescenderHeight (void)
{
	Int16 (*FntDescenderHeightP) (void);

	GetParameter (&FntDescenderHeightP, sizeof(void *), pFntDescenderHeight);
	return 	(*FntDescenderHeightP) ();
}
#endif


#ifdef L_FntWordWrapReverseNLines
void FntWordWrapReverseNLines (Char const *const chars,
	UInt16 maxWidth, UInt16 *linesToScrollP, UInt16 *scrollPosP)
{

	void (*FntWordWrapReverseNLinesP) (Char const *const chars,
				UInt16 maxWidth, UInt16 *linesToScrollP, UInt16 *scrollPosP);

	GetParameter (&FntWordWrapReverseNLinesP, sizeof(void *), pFntWordWrapReverseNLines);
	(*FntWordWrapReverseNLinesP) (  chars, maxWidth, linesToScrollP, scrollPosP);
}
#endif

#ifdef L_FntGetScrollValues
void FntGetScrollValues (Char const *chars, UInt16 width,
	UInt16 scrollPos, UInt16 *linesP, UInt16 *topLine)
{
	void (*FntGetScrollValuesP) (Char const *chars, UInt16 width,
			UInt16 scrollPos, UInt16 *linesP, UInt16 *topLine);

	GetParameter (&FntGetScrollValuesP, sizeof(void *), pFntGetScrollValues);
	(*FntGetScrollValuesP) ( chars,  width,
			 scrollPos, linesP, topLine);
}
#endif

#ifdef L_FntDefineFont
Err FntDefineFont (FontID font, FontPtr fontP)
{
	Err (*FntDefineFontP) (FontID font, FontPtr fontP);

	GetParameter (&FntDefineFontP, sizeof(void *), pFntDefineFont);
	return 	(*FntDefineFontP) ( font,  fontP);
}
#endif
							
#ifdef L_FontSelect
FontID FontSelect (FontID fontID)
{
	FontID (*FontSelectP) (FontID fontID);

	GetParameter (&FontSelectP, sizeof(void *), pFontSelect);
	return  (*FontSelectP) (fontID);
}
#endif


////////////////////////////////////////////////////////////
// Form Processing Library, completed 65/65 functions now.
////////////////////////////////////////////////////////////
#ifdef L_FrmAlert
UInt16 FrmAlert (UInt16 alertID)
{
	UInt16 (*FrmAlertP) (UInt16 alertID);

	GetParameter (&FrmAlertP, sizeof(void *), pFrmAlert);
	return (*FrmAlertP) ( alertID);
}
#endif

#ifdef L_FrmCloseAllForms
void FrmCloseAllForms (void)
{
	void (*FrmCloseAllFormsP) (void);

	GetParameter (&FrmCloseAllFormsP, sizeof(void *), pFrmCloseAllForms);
	(*FrmCloseAllFormsP) ();
}
#endif

#ifdef L_FrmCopyLabel
void FrmCopyLabel(FormType *formP, UInt16 labelID, char *newLabel)
{
	void (*FrmCopyLabelP)(FormType *formP, UInt16 labelID, char *newLabel);

	GetParameter (&FrmCopyLabelP, sizeof(void *), pFrmCopyLabel);
	(*FrmCopyLabelP)(formP,  labelID, newLabel);
}
#endif

#ifdef L_FrmCopyTitle
void FrmCopyTitle (FormType *formP, const Char *newTitle)
{
	void (*FrmCopyTitleP) (FormType *formP, const Char *newTitle);

	GetParameter (&FrmCopyTitleP, sizeof(void *), pFrmCopyTitle);
	(*FrmCopyTitleP) (formP, newTitle);
}
#endif

#ifdef L_FrmCustomAlert
UInt16 FrmCustomAlert (UInt16 alertID, const Char *s1, const Char *s2, const Char *s3)
{
	UInt16 (*FrmCustomAlertP) (UInt16 alertID, const Char *s1, const Char *s2, const Char *s3);

	GetParameter (&FrmCustomAlertP, sizeof(void *), pFrmCustomAlert);
	return (*FrmCustomAlertP) ( alertID,  s1,  s2, s3);
}
#endif

/*
UInt16 FrmCustomResponseAlert (UInt16 alertID, const Char *s1, const Char *s2,
							   const Char *s3, Char *entryStringBuf,
							   UInt16 entryStringBufLength, FormCheckResponseFuncPtr callback)
{
	UInt16 (*FrmCustomResponseAlertP) (UInt16 alertID, const Char *s1, const Char *s2,
							   const Char *s3, Char *entryStringBuf,
							   UInt16 entryStringBufLength, FormCheckResponseFuncPtr callback);

	GetParameter (&FrmCustomResponseAlertP, sizeof(void *), pFrmCustomResponseAlert);
	return (*FrmCustomResponseAlertP) ( alertID,  s1, s2,  s3, entryStringBuf,
							    entryStringBufLength,  callback);
}
*/
#ifdef L_FrmDeleteForm
void FrmDeleteForm (FormType *formP)
{
	void (*FrmDeleteFormP) (FormType *formP);

	GetParameter (&FrmDeleteFormP, sizeof(void *), pFrmDeleteForm);
	(*FrmDeleteFormP) (formP);
}
#endif

#ifdef L_FrmDispatchEvent
Boolean FrmDispatchEvent(EventType *eventP)
{
	Boolean (*FrmDispatchEventP)(EventType *eventP);

	GetParameter (&FrmDispatchEventP, sizeof(void *), pFrmDispatchEvent);
	return (*FrmDispatchEventP)(eventP);
}
#endif

#ifdef L_FrmDoDialog
UInt16 FrmDoDialog (FormType *formP)
{
	UInt16 (*FrmDoDialogP) (FormType *formP);

	GetParameter (&FrmDoDialogP, sizeof(void *), FrmDoDialogP);
	return (*FrmDoDialogP) (formP);
}
#endif

#ifdef L_FrmDrawForm
void FrmDrawForm(FormType *formP)
{
	void (*FrmDrawFormP)(FormType *formP);

	GetParameter (&FrmDrawFormP, sizeof(void *), pFrmDrawForm);
	(*FrmDrawFormP)(formP);
}
#endif

#ifdef L_FrmEraseForm
void FrmEraseForm (FormType *formP)
{
	void (*FrmEraseFormP) (FormType *formP);

	GetParameter (&FrmEraseFormP, sizeof(void *), pFrmEraseForm);
	(*FrmEraseFormP) (formP);
}
#endif

#ifdef L_FrmGetActiveForm
FormType *FrmGetActiveForm ()
{
	FormType *(*FrmGetActiveFormP) ();

	GetParameter (&FrmGetActiveFormP, sizeof(void *), pFrmGetActiveForm);
	return (*FrmGetActiveFormP) ();
}
#endif

#ifdef L_FrmGetActiveFormID
UInt16 FrmGetActiveFormID (void)
{
	UInt16 (*FrmGetActiveFormIDP) (void);

	GetParameter (&FrmGetActiveFormIDP, sizeof(void *), pFrmGetActiveFormID);
	return (*FrmGetActiveFormIDP) ();
}
#endif

#ifdef L_FrmGetControlGroupSelection
UInt16 FrmGetControlGroupSelection (FormType *formP, UInt8 groupNum)
{
	UInt16 (*FrmGetControlGroupSelectionP) (FormType *formP, UInt8 groupNum);

	GetParameter (&FrmGetControlGroupSelectionP, sizeof(void *), pFrmGetControlGroupSelection);
	return	(*FrmGetControlGroupSelectionP) (formP, groupNum);
}
#endif

#ifdef L_FrmGetControlValue
Int16 FrmGetControlValue (const FormType *formP, UInt16 controlID)
{
	Int16 (*FrmGetControlValueP) (const FormType *formP, UInt16 controlID);

	GetParameter (&FrmGetControlValueP, sizeof(void *), pFrmGetControlValue);
	return (*FrmGetControlValueP) (formP,  controlID);
}
#endif

#ifdef L_FrmGetFirstForm
FormType *FrmGetFirstForm (void)
{
	FormType *(*FrmGetFirstFormP) (void);

	GetParameter (&FrmGetFirstFormP, sizeof(void *), pFrmGetFirstForm);
	return(*FrmGetFirstFormP) ();
}
#endif

#ifdef L_FrmGetFocus
UInt16 FrmGetFocus (const FormType *formP)
{
	UInt16 (*FrmGetFocusP) (const FormType *formP);

	GetParameter (&FrmGetFocusP, sizeof(void *), pFrmGetFocus);
	return (*FrmGetFocusP) (formP);
}
#endif

#ifdef L_FrmGetFormBounds
void FrmGetFormBounds (const FormType *formP, RectangleType *rP)
{
	void (*FrmGetFormBoundsP) (const FormType *formP, RectangleType *rP);

	GetParameter (&FrmGetFormBoundsP, sizeof(void *), pFrmGetFormBounds);
	(*FrmGetFormBoundsP) (formP, rP);
}
#endif

#ifdef L_FrmGetFormId
UInt16 FrmGetFormId (FormType *formP)
{
	UInt16 (*FrmGetFormIdP) (FormType *formP);

	GetParameter (&FrmGetFormIdP, sizeof(void *), pFrmGetFormId);
	return (*FrmGetFormIdP) (formP);
}
#endif

#ifdef L_FrmGetFormPtr
FormType *FrmGetFormPtr (UInt16 formId)
{
	FormType *(*FrmGetFormPtrP) (UInt16 formId);

	GetParameter (&FrmGetFormPtrP, sizeof(void *), pFrmGetFormPtr);
	return(*FrmGetFormPtrP) ( formId);
}
#endif

#ifdef L_FrmGetGadgetData
void *FrmGetGadgetData (const FormType *formP, UInt16 objIndex)
{
	void *(*FrmGetGadgetDataP) (const FormType *formP, UInt16 objIndex);

	GetParameter (&FrmGetGadgetDataP, sizeof(void *), pFrmGetGadgetData);
	return(*FrmGetGadgetDataP) (formP,  objIndex);
}
#endif

#ifdef L_FrmGetLabel
const Char *FrmGetLabel (FormType *formP, UInt16 labelID)
{
	Char *(*FrmGetLabelP) (FormType *formP, UInt16 labelID);

	GetParameter (&FrmGetLabelP, sizeof(void *), pFrmGetLabel);
	return(*FrmGetLabelP) (formP,  labelID);
}
#endif

#ifdef L_FrmGetNumberOfObjects
UInt16 FrmGetNumberOfObjects (const FormType *formP)
{
	UInt16 (*FrmGetNumberOfObjectsP) (const FormType *formP);

	GetParameter (&FrmGetNumberOfObjectsP, sizeof(void *), pFrmGetNumberOfObjects);
	return (*FrmGetNumberOfObjectsP) ( formP);
}
#endif

#ifdef L_FrmGetObjectBounds
void FrmGetObjectBounds (const FormType *formP, UInt16 ObjIndex, RectangleType *rP)
{
	void (*FrmGetObjectBoundsP) (const FormType *formP, UInt16 ObjIndex, RectangleType *rP);

	GetParameter (&FrmGetObjectBoundsP, sizeof(void *), pFrmGetObjectBounds);
	(*FrmGetObjectBoundsP) (formP,  ObjIndex, rP);
}
#endif

#ifdef L_FrmGetObjectId
UInt16 FrmGetObjectId (const FormType *formP, UInt16 objIndex)
{
	UInt16 (*FrmGetObjectIdP) (const FormType *formP, UInt16 objIndex);

	GetParameter (&FrmGetObjectIdP, sizeof(void *), pFrmGetObjectId);
	return (*FrmGetObjectIdP) (formP,  objIndex);
}
#endif

#ifdef L_FrmGetObjectIndex
UInt16 FrmGetObjectIndex(const FormType *formP, UInt16 id)
{
	UInt16 (*FrmGetObjectIndexP)(const FormType *formP, UInt16 id);

	GetParameter (&FrmGetObjectIndexP, sizeof(void *), pFrmGetObjectIndex);
	return (*FrmGetObjectIndexP)(formP,  id);
}
#endif

#ifdef L_FrmGetObjectPosition
void FrmGetObjectPosition (const FormType *formP, UInt16 objIndex, Coord *x, Coord *y)
{
	void (*FrmGetObjectPositionP) (const FormType *formP, UInt16 objIndex, Coord *x, Coord *y);

	GetParameter (&FrmGetObjectPositionP, sizeof(void *), pFrmGetObjectPosition);
	(*FrmGetObjectPositionP) (formP,  objIndex, x, y);
}
#endif

#ifdef L_FrmGetObjectPtr
void *FrmGetObjectPtr (const FormType *formP, UInt16 objIndex)
{
	void *(*FrmGetObjectPtrP) (const FormType *formP, UInt16 objIndex);

	GetParameter (&FrmGetObjectPtrP, sizeof(void *), pFrmGetObjectPtr);
	return(*FrmGetObjectPtrP) (formP,  objIndex);
}
#endif

#ifdef L_FrmGetObjectType
FormObjectKind FrmGetObjectType (const FormType *formP, UInt16 objIndex)
{
	FormObjectKind (*FrmGetObjectTypeP) (const FormType *formP, UInt16 objIndex);

	GetParameter (&FrmGetObjectTypeP, sizeof(void *), pFrmGetObjectType);
	return (*FrmGetObjectTypeP) (formP,  objIndex);
}
#endif

#ifdef L_FrmGetTitle
const Char *FrmGetTitle (const FormType *formP)
{
        Char *(*FrmGetTitleP) (const FormType *formP);

	GetParameter (&FrmGetTitleP, sizeof(void *), pFrmGetTitle);
        return(*FrmGetTitleP) (formP);
}
#endif

#ifdef L_FrmGetWindowHandle
WinHandle FrmGetWindowHandle (const FormType *formP)
{
	WinHandle (*FrmGetWindowHandleP) (const FormType *formP);

	GetParameter (&FrmGetWindowHandleP, sizeof(void *), pFrmGetWindowHandle);
	return (*FrmGetWindowHandleP) (formP);
}
#endif

#ifdef L_FrmGotoForm
void FrmGotoForm (UInt16 fIndex)
{
	void (*FrmGotoFormP) (UInt16 fIndex);

	GetParameter (&FrmGotoFormP, sizeof(void *), pFrmGotoForm);
	(*FrmGotoFormP) ( fIndex);
}
#endif

#ifdef L_FrmHandleEvent
Boolean FrmHandleEvent (FormType *formP, EventType *eventP)
{
	Boolean (*FrmHandleEventP) (FormType *formP, EventType *eventP);

	GetParameter (&FrmHandleEventP, sizeof(void *), pFrmHandleEvent);
	return (*FrmHandleEventP) (formP, eventP);
}
#endif

#ifdef L_FrmHelp
void FrmHelp (UInt16 helpMsgId)
{
	void (*FrmHelpP) (UInt16 helpMsgId);

	GetParameter (&FrmHelpP, sizeof(void *), pFrmHelp);
	(*FrmHelpP) (helpMsgId);
}
#endif

#ifdef L_FrmHideObject
void FrmHideObject(FormType *formP, UInt16 objIndex)
{
	void (*FrmHideObjectP)(FormType *formP, UInt16 objIndex);

	GetParameter (&FrmHideObjectP, sizeof(void *), pFrmHideObject);
	(*FrmHideObjectP)(formP,  objIndex);
}
#endif

#ifdef L_FrmInitForm
FormType *FrmInitForm(UInt16 formID)
{
	FormType *(*FrmInitFormP)(UInt16 formID);

	GetParameter (&FrmInitFormP, sizeof(void *), pFrmInitForm);
	return (*FrmInitFormP)( formID);
}
#endif

#ifdef L_FrmNewBitmap
FormBitmapType *FrmNewBitmap (FormType **formPP, UInt16 ID, UInt16 rscID, Coord x, Coord y)
{
	FormBitmapType *(*FrmNewBitmapP) (FormType **formPP, UInt16 ID, UInt16 rscID, Coord x, Coord y);

	GetParameter (&FrmNewBitmapP, sizeof(void *), pFrmNewBitmap);
	return(*FrmNewBitmapP) (formPP,  ID,  rscID,  x,  y);
}
#endif

#ifdef L_FrmNewForm
FormType *FrmNewForm (UInt16 formID, const Char *titleStrP, Coord x, Coord y,
							 Coord width, Coord height, Boolean modal, UInt16 defaultButton,
							 UInt16 helpRscID, UInt16 menuRscID)
{
	FormType *(*FrmNewFormP) (UInt16 formID, const Char *titleStrP, Coord x, Coord y,
							 Coord width, Coord height, Boolean modal, UInt16 defaultButton,
							 UInt16 helpRscID, UInt16 menuRscID);

	GetParameter (&FrmNewFormP, sizeof(void *), pFrmNewForm);
	return(*FrmNewFormP) ( formID, titleStrP,  x,  y,  width,  height,  modal,  defaultButton,
							  helpRscID,  menuRscID);
}
#endif

/*
FromGadgetType *FrmNewGadget (FormType **formPP, UInt16 id, Coord x, Coord y,
										Coord width, Coord height)
{
	FromGadgetType *(*FrmNewGadgetP) (FormType **formPP, UInt16 id, Coord x, Coord y,
										Coord width, Coord height);

	GetParameter (&FrmNewGadgetP, sizeof(void *), pFrmNewGadget);
	return(*FrmNewGadgetP) (formPP,  id,  x,  y,	 width,  height);
}

FrmGraffitiStateType *FrmNewGsi (FromType **formPP, Coord x, Coord y)
{
	FrmGraffitiStateType *(*FrmNewGsip) (FromType **formPP, Coord x, Coord y);
	
	GetParameter (&FrmNewGsip, sizeof(void *), PFrmNewGsi);
	return(*FrmNewGsip) (formPP,  x,  y);
}
*/
#ifdef L_FrmNewLabel
FormLabelType *FrmNewLabel (FormType **formPP, UInt16 ID, const Char *textP, Coord x, Coord y, FontID font)
{
	FormLabelType *(*FrmNewLabelP) (FormType **formPP, UInt16 ID, const Char *textP, Coord x, Coord y, FontID font);

	GetParameter (&FrmNewLabelP, sizeof(void *), pFrmNewLabel);
	return(*FrmNewLabelP) (formPP,  ID,  textP,  x,  y,  font);
}
#endif

#ifdef L_FrmPointInTitle
Boolean FrmPointInTitle (const FormType *formP, Coord x, Coord y)
{
	Boolean (*FrmPointInTitleP) (const FormType *formP, Coord x, Coord y);

	GetParameter (&FrmPointInTitleP, sizeof(void *), pFrmPointInTitle);
	return (*FrmPointInTitleP) (formP,  x,  y);
}
#endif

#ifdef L_FrmPopupForm
void FrmPopupForm (UInt16 fIndex)
{
	void (*FrmPopupFormP) (UInt16 fIndex);

	GetParameter (&FrmPopupFormP, sizeof(void *), pFrmPopupForm);
	(*FrmPopupFormP) ( fIndex);
}
#endif

#ifdef L_FrmRemoveObject
Err FrmRemoveObject (FormType **formPP, UInt16 objIndex)
{
	Err (*FrmRemoveObjectP) (FormType **formPP, UInt16 objIndex);

	GetParameter (&FrmRemoveObjectP, sizeof(void *), pFrmRemoveObject);
	return (*FrmRemoveObjectP) (formPP,  objIndex);
}
#endif

#ifdef L_FrmRestoreActiveState
Boolean FrmRestoreActiveState (FormActiveStateType stateP)
{
	Boolean (*FrmRestoreActiveStateP) (FormActiveStateType stateP);

	GetParameter (&FrmRestoreActiveStateP, sizeof(void *), pFrmRestoreActiveState);
	return (*FrmRestoreActiveStateP) ( stateP);
}
#endif

#ifdef L_FrmReturnToForm
void FrmReturnToForm (UInt16 fIndex)
{
	void (*FrmReturnToFormP) (UInt16 fIndex);

	GetParameter (&FrmReturnToFormP, sizeof(void *), pFrmReturnToForm);
	(*FrmReturnToFormP) ( fIndex);
}
#endif

#ifdef L_FrmSaveActiveState
Boolean FrmSaveActiveState (FormActiveStateType stateP)
{
	Boolean (*FrmSaveActiveStateP) (FormActiveStateType stateP);

	GetParameter (&FrmSaveActiveStateP, sizeof(void *), pFrmSaveActiveState);
	return (*FrmSaveActiveStateP) ( stateP);
}
#endif

#ifdef L_FrmSaveAllForms
void FrmSaveAllForms (void)
{
	void (*FrmSaveAllFormsP) (void);

	GetParameter (&FrmSaveAllFormsP, sizeof(void *), pFrmSaveAllForms);
	(*FrmSaveAllFormsP) ();
}
#endif

#ifdef L_FrmSetActiveForm
void FrmSetActiveForm(FormType *formP)
{
	void (*FrmSetActiveFormP)(FormType *formP);

	GetParameter (&FrmSetActiveFormP, sizeof(void *), pFrmSetActiveForm);
	(*FrmSetActiveFormP)(formP);
}
#endif

#ifdef L_FrmSetCategoryLabel
void FrmSetCategoryLabel (FormType *formP, UInt16 objIndex, Char *newLabel)
{
	void (*FrmSetCategoryLabelP) (FormType *formP, UInt16 objIndex, Char *newLabel);

	GetParameter (&FrmSetCategoryLabelP, sizeof(void *), pFrmSetCategoryLabel);
	(*FrmSetCategoryLabelP) (formP,  objIndex, newLabel);
}
#endif

#ifdef L_FrmSetControlGroupSelection
void FrmSetControlGroupSelection (const FormType *formP, UInt8 groupNum, UInt16 controlID)
{
	void (*FrmSetControlGroupSelectionP) (const FormType *formP, UInt8 groupNum, UInt16 controlID);

	GetParameter (&FrmSetControlGroupSelectionP, sizeof(void *), pFrmSetControlGroupSelection);
	(*FrmSetControlGroupSelectionP) (formP,  groupNum,  controlID);
}
#endif

#ifdef L_FrmSetControlValue
void FrmSetControlValue (FormType *formP, UInt16 objIndex, Int16 newValue)
{
	void (*FrmSetControlValueP) (FormType *formP, UInt16 objIndex, Int16 newValue);

	GetParameter (&FrmSetControlValueP, sizeof(void *), pFrmSetControlValue);
	(*FrmSetControlValueP) (formP,  objIndex,  newValue);
}
#endif

#ifdef L_FrmSetEventHandler
void FrmSetEventHandler(FormType *formP, FormEventHandlerType *handler)
{
	void (*FrmSetEventHandlerP)(FormType *formP, FormEventHandlerType *handler);

	GetParameter (&FrmSetEventHandlerP, sizeof(void *), pFrmSetEventHandler);
	(*FrmSetEventHandlerP)(formP, handler);
}
#endif

#ifdef L_FrmSetGadgetData
void FrmSetFocus(FormType *formP, UInt16 fieldIndex)
{
	void (*FrmSetFocusP)(FormType *formP, UInt16 fieldIndex);

	GetParameter (&FrmSetFocusP, sizeof(void *), pFrmSetFocus);
	(*FrmSetFocusP)(formP,  fieldIndex);
}
#endif

#ifdef L_FrmSetGadgetData
void FrmSetGadgetData (FormType *formP, UInt16 objIndex, const void *data)
{
	void (*FrmSetGadgetDataP) (FormType *formP, UInt16 objIndex, const void *data);

	GetParameter (&FrmSetGadgetDataP, sizeof(void *), pFrmSetGadgetData);
	(*FrmSetGadgetDataP) (formP,  objIndex, data);
}
#endif

/*
void FrmSetGadgetHandler (FormType *formP, UInt16 objIndex, FormGadgetHandlerType *attrP)
{
	void (*FrmSetGadgetHandlerP) (FormType *formP, UInt16 objIndex, FormGadgetHandlerType *attrP);

	GetParameter (&FrmSetGadgetHandlerP, sizeof(void *), pFrmSetGadgetHandler);
	(*FrmSetGadgetHandlerP) (formP,  objIndex, attrP);
}
*/
#ifdef L_FrmSetMenu
void FrmSetMenu (FormType *formP, UInt16 menuRscID)
{
	void (*FrmSetMenuP) (FormType *formP, UInt16 menuRscID);

	GetParameter (&FrmSetMenuP, sizeof(void *), pFrmSetMenu);
	(*FrmSetMenuP) (formP,  menuRscID);
}
#endif

#ifdef L_FrmSetObjectBounds
void FrmSetObjectBounds (FormType *formP, UInt16 objIndex, const RectangleType *bounds)
{
	void (*FrmSetObjectBoundsP) (FormType *formP, UInt16 objIndex, const RectangleType *bounds);

	GetParameter (&FrmSetObjectBoundsP, sizeof(void *), pFrmSetObjectBounds);
	(*FrmSetObjectBoundsP) (formP,  objIndex,  bounds);
}
#endif

#ifdef L_FrmSetObjectPosition
void FrmSetObjectPosition (FormType *formP, UInt16 objIndex, Coord x, Coord y)
{
	void (*FrmSetObjectPositionP) (FormType *formP, UInt16 objIndex, Coord x, Coord y);

	GetParameter (&FrmSetObjectPositionP, sizeof(void *), pFrmSetObjectPosition);
	(*FrmSetObjectPositionP) (formP,  objIndex,  x,  y);
}
#endif

#ifdef L_FrmSetTitle
void FrmSetTitle (FormType *formP, Char *newTitle)
{
	void (*FrmSetTitleP) (FormType *formP, Char *newTitle);

	GetParameter (&FrmSetTitleP, sizeof(void *), pFrmSetTitle);
	(*FrmSetTitleP) (formP, newTitle);
}
#endif

#ifdef L_FrmShowObject
void FrmShowObject (FormType *formP, UInt16 objIndex)
{
	void (*FrmShowObjectP) (FormType *formP, UInt16 objIndex);

	GetParameter (&FrmShowObjectP, sizeof(void *), pFrmShowObject);
	(*FrmShowObjectP) (formP,  objIndex);
}
#endif

#ifdef L_FrmUpdateForm
void FrmUpdateForm (UInt16 formId, UInt16 updateCode)
{
	void (*FrmUpdateFormP) (UInt16 formId, UInt16 updateCode);

	GetParameter (&FrmUpdateFormP, sizeof(void *), pFrmUpdateForm);
	(*FrmUpdateFormP) ( formId,  updateCode);
}
#endif

#ifdef L_FrmUpdateScrollers
void FrmUpdateScrollers (FormType *formP, UInt16 upIndex, UInt16 downIndex,
								 Boolean scrollableUp, Boolean scrollableDown)
{
	void (*FrmUpdateScrollersP) (FormType *formP, UInt16 upIndex, UInt16 downIndex,
								 Boolean scrollableUp, Boolean scrollableDown);

	GetParameter (&FrmUpdateScrollersP, sizeof(void *), pFrmUpdateScrollers);
	(*FrmUpdateScrollersP) (formP,  upIndex,  downIndex,  scrollableUp,  scrollableDown);
}
#endif

#ifdef L_FrmValidatePtr
Boolean FrmValidatePtr (const FormType *formP)
{
	Boolean (*FrmValidatePtrP) (const FormType *formP);

	GetParameter (&FrmValidatePtrP, sizeof(void *), pFrmValidatePtr);
	return (*FrmValidatePtrP) ( formP);
}
#endif

#ifdef L_FrmVisible
Boolean FrmVisible (const FormType *formP)
{
	Boolean (*FrmVisibleP)(const FormType *formP);

	GetParameter (&FrmVisibleP , sizeof(void *), pFrmVisible );
	return (*FrmVisibleP)(formP);
}
#endif



