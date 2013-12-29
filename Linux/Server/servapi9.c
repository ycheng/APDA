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
// Time Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////
void PipeDateAdjust(void)
{
	WriteParameter (DateAdjust, sizeof(void*), pDateAdjust);
}
void PipeDateDaysToDate (void)
{
	WriteParameter (DateDaysToDate, sizeof(void*), pDateDaysToDate);
}
void PipeDateSecondsToDate (void)
{
	WriteParameter (DateSecondsToDate, sizeof(void*), pDateSecondsToDate);
}

void PipeDateTemplateToAscii (void)
{
//	WriteParameter (DateTemplateToAscii, sizeof(void*), pDateTemplateToAscii);
}

void PipeDateToAscii(void)
{
	WriteParameter (DateToAscii, sizeof(void*), pDateToAscii);
}

void PipeDateToDays (void)
{
	WriteParameter (DateToDays, sizeof(void*), pDateToDays);
}
void PipeDateToDOWDMFormat (void)
{
	WriteParameter (DateToDOWDMFormat, sizeof(void*), pDateToDOWDMFormat);

}
void PipeDayOfMonth (void)
{
	WriteParameter (DayOfMonth, sizeof(void*), pDayOfMonth);
}
void PipeDayOfWeek (void)
{
	WriteParameter (DayOfWeek, sizeof(void*), pDayOfWeek);
}
void PipeDaysInMonth(void)
{
	WriteParameter (DaysInMonth, sizeof(void*), pDaysInMonth);
}
void PipeTimeAdjust (void)
{
	WriteParameter (TimeAdjust, sizeof(void*), pTimeAdjust);
}
void PipeTimDateTimeToSeconds (void)
{
	WriteParameter (TimDateTimeToSeconds, sizeof(void*), pTimDateTimeToSeconds);
}
void PipeTimGetSeconds (void)
{
	WriteParameter (TimGetSeconds, sizeof(void*), pTimGetSeconds);
}
void PipeTimGetTicks (void)
{
	WriteParameter (TimGetTicks, sizeof(void*), pTimGetTicks);
}
void PipeTimSecondsToDateTime (void)
{
	WriteParameter (TimSecondsToDateTime, sizeof(void*), pTimSecondsToDateTime);
}
void PipeTimSetSeconds (void)
{
	WriteParameter (TimSetSeconds, sizeof(void*), pTimSetSeconds);
}
void PipeTimeToAscii (void)
{
	WriteParameter (TimeToAscii, sizeof(void*), pTimeToAscii);
}


////////////////////////////////////////////////////////////
// Table Library, completed 57/57 functions now.
////////////////////////////////////////////////////////////
void PipeTblDrawTable (void)
{
	WriteParameter (TblDrawTable, sizeof(void*), pTblDrawTable);
}
void PipeTblEditing (void)
{
	WriteParameter (TblEditing, sizeof(void*), pTblEditing);
}
void PipeTblEraseTable (void)
{
	WriteParameter (TblEraseTable, sizeof(void*), pTblEraseTable);

}

void PipeTblFindRowData (void)
{
//	WriteParameter (TblFindRowData, sizeof(void*), pTblFindRowData);
}

void PipeTblFindRowID (void)
{
	WriteParameter (TblFindRowID, sizeof(void*), pTblFindRowID);
}
void PipeTblGetBounds (void)
{
	WriteParameter (TblGetBounds, sizeof(void*), pTblGetBounds);

}
void PipeTblGetColumnSpacing (void)
{
	WriteParameter (TblGetColumnSpacing, sizeof(void*), pTblGetColumnSpacing);
}
void PipeTblGetColumnWidth (void)
{
	WriteParameter (TblGetColumnWidth, sizeof(void*), pTblGetColumnWidth);
}
void PipeTblGetCurrentField (void)
{
	WriteParameter (TblGetCurrentField, sizeof(void*), pTblGetCurrentField);

}

void PipeTblGetItemBounds (void)
{
//	WriteParameter (TblGetItemBounds, sizeof(void*), pTblGetItemBounds);
}

void PipeTblGetItemFont (void)
{
	WriteParameter (TblGetItemFont, sizeof(void*), pTblGetItemFont);
}
void PipeTblGetItemInt (void)
{
	WriteParameter (TblGetItemInt, sizeof(void*), pTblGetItemInt);
}

void PipeTblGetItemPtr (void)
{
	WriteParameter (TblGetItemPtr, sizeof(void*), pTblGetItemPtr);
}
void PipeTblGetLastUsableRow (void)
{
	WriteParameter (TblGetLastUsableRow, sizeof(void*), pTblGetLastUsableRow);
}
void PipeTblGetNumberOfRows (void)
{
	WriteParameter (TblGetNumberOfRows, sizeof(void*), pTblGetNumberOfRows);
}
void PipeTblGetRowData (void)
{
	WriteParameter (TblGetRowData, sizeof(void*), pTblGetRowData);
}
void PipeTblGetRowHeight(void)
{
	WriteParameter (TblGetRowHeight, sizeof(void*), pTblGetRowHeight);
}
void PipeTblGetRowID (void)
{
	WriteParameter (TblGetRowID, sizeof(void*), pTblGetRowID);
}
void PipeTblGetSelection (void)
{
	WriteParameter (TblGetSelection, sizeof(void*), pTblGetSelection);
}
void PipeTblGrabFocus (void)
{
	WriteParameter (TblGrabFocus, sizeof(void*), pTblGrabFocus);

}

void PipeTblHandleEvent (void)
{
//	WriteParameter (TblHandleEvent, sizeof(void*), pTblHandleEvent);
}

void PipeTblHasScrollBar (void)
{
	WriteParameter (TblHasScrollBar, sizeof(void*), pTblHasScrollBar);
}

void PipeTblInsertRow (void)
{
//	WriteParameter (TblInsertRow, sizeof(void*), pTblInsertRow);
}

void PipeTblMarkRowInvalid (void)
{
	WriteParameter (TblMarkRowInvalid, sizeof(void*), pTblMarkRowInvalid);
}
void PipeTblMarkTableInvalid (void)
{
	WriteParameter (TblMarkTableInvalid, sizeof(void*), pTblMarkTableInvalid);
}

void PipeTblRedrawTable  (void)
{
//	WriteParameter (TblRedrawTable, sizeof(void*), pTblRedrawTable);
}

void PipeTblReleaseFocus (void)
{
//	WriteParameter (TblReleaseFocus, sizeof(void*), pTblReleaseFocus);
}

void PipeTblRemoveRow  (void)
{
//	WriteParameter (TblRemoveRow, sizeof(void*), pTblRemoveRow);
}

void PipeTblReverseItem (void)
{
	WriteParameter (TblReverseItem, sizeof(void*), pTblReverseItem);

}
void PipeTblRowInvalid (void)
{
	WriteParameter (TblRowInvalid, sizeof(void*), pTblRowInvalid);
}
void PipeTblRowMasked (void)
{
	WriteParameter (TblRowMasked, sizeof(void*), pTblRowMasked);
}

void PipeTblRowSelectable (void)
{
	WriteParameter (TblRowSelectable, sizeof(void*), pTblRowSelectable);

}
void PipeTblRowUsable (void)
{
	WriteParameter (TblSelectItem, sizeof(void*), pTblRowUsable);
}
void PipeTblSelectItem  (void)
{
	WriteParameter (TblSelectItem, sizeof(void*), pTblSelectItem);

}
void PipeTblSetBounds (void)
{
	WriteParameter (TblSetBounds, sizeof(void*), pTblSetBounds);

}
void PipeTblSetColumnEditIndicator (void)
{
	WriteParameter (TblSetColumnEditIndicator, sizeof(void*), pTblSetColumnEditIndicator);
}
void PipeTblSetColumnMasked (void)
{
	WriteParameter (TblSetColumnMasked, sizeof(void*), pTblSetColumnMasked);

}
void PipeTblSetColumnSpacing  (void)
{
	WriteParameter (TblSetColumnSpacing, sizeof(void*), pTblSetColumnSpacing);
}
void PipeTblSetColumnUsable  (void)
{
	WriteParameter (TblSetColumnUsable, sizeof(void*), pTblSetColumnUsable);

}
void PipeTblSetColumnWidth  (void)
{
	WriteParameter (TblSetColumnWidth, sizeof(void*), pTblSetColumnWidth);
}
void PipeTblSetCustomDrawProcedure (void)
{
	WriteParameter (TblSetCustomDrawProcedure, sizeof(void*), pTblSetCustomDrawProcedure);

}
void PipeTblSetItemFont (void)
{
	WriteParameter (TblSetItemFont, sizeof(void*), pTblSetItemFont);
}
void PipeTblSetItemInt (void)
{
	WriteParameter (TblSetItemInt, sizeof(void*), pTblSetItemInt);
}
void PipeTblSetItemPtr (void)
{
	WriteParameter (TblSetItemPtr, sizeof(void*), pTblSetItemPtr);

}
void PipeTblSetItemStyle  (void)
{
	WriteParameter (TblSetItemStyle , sizeof(void*), pTblSetItemStyle);

}
void PipeTblSetLoadDataProcedure  (void)
{
	WriteParameter (TblSetLoadDataProcedure, sizeof(void*), pTblSetLoadDataProcedure);
}
void PipeTblSetRowData (void)
{
	WriteParameter (TblSetRowData, sizeof(void*), pTblSetRowData);
}
void PipeTblSetRowHeight  (void)
{
	WriteParameter (TblSetRowHeight, sizeof(void*), pTblSetRowHeight);
}
void PipeTblSetRowID  (void)
{
	WriteParameter (TblSetRowID, sizeof(void*), pTblSetRowID);
}
void PipeTblSetRowMasked  (void)
{
	WriteParameter (TblSetRowMasked, sizeof(void*), pTblSetRowMasked);

}
void PipeTblSetRowSelectable  (void)
{
	WriteParameter (TblSetRowSelectable, sizeof(void*), pTblSetRowSelectable);

}
void PipeTblSetRowStaticHeight  (void)
{
	WriteParameter (TblSetRowStaticHeight, sizeof(void*), pTblSetRowStaticHeight);
}
void PipeTblSetRowUsable  (void)
{
	WriteParameter (TblSetRowUsable, sizeof(void*), pTblSetRowUsable);

}
void PipeTblSetSaveDataProcedure  (void)
{
	WriteParameter (TblSetSaveDataProcedure, sizeof(void*), pTblSetSaveDataProcedure);

}

void PipeTblUnhighlightSelection  (void)
{
//	WriteParameter (TblUnhighlightSelection, sizeof(void*), pTblUnhighlightSelection);
}

void PipeTableDrawItemFuncType (void)
{
//	WriteParameter (TableDrawItemFuncType, sizeof(void*), pTableDrawItemFuncType);
}

void PipeTableLoadDataFuncType(void)
{
//	WriteParameter (TableLoadDataFuncType, sizeof(void*), pTableLoadDataFuncType);
}
void PipeTableSaveDataFuncType (void)
{
//	WriteParameter (TableSaveDataFuncType, sizeof(void*), pTableSaveDataFuncType);
}

////////////////////////////////////////////////////////////
// UI Color List Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeUIColorGetTableEntryIndex (void)
{
//	WriteParameter (UIColorGetTableEntryIndex, sizeof(void*), pUIColorGetTableEntryIndex);
}
void PipeUIColorGetTableEntryRGB(void)
{
//	WriteParameter (UIColorGetTableEntryRGB, sizeof(void*), pUIColorGetTableEntryRGB);
}
void PipeUIColorSetTableEntry(void)
{
//	WriteParameter (UIColorSetTableEntry, sizeof(void*), pUIColorSetTableEntry);
}



////////////////////////////////////////////////////////////
// UI Controls Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
void PipeUIBrightnessAdjust (void)
{
//	WriteParameter (UIBrightnessAdjust , sizeof(void*), pUIBrightnessAdjust );
}
void PipeUIContrastAdjust (void)
{
//	WriteParameter (UIContrastAdjust, sizeof(void*), pUIContrastAdjust);
}
void PipeUIPickColor(void)
{
//	WriteParameter (UIPickColor, sizeof(void*), pUIPickColor);
}



////////////////////////////////////////////////////////////
// User Interface Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
void PipePhoneNumberLookup (void)
{
//	WriteParameter (PhoneNumberLookup , sizeof(void*), pPhoneNumberLookup );
}
void PipeResLoadConstant (void)
{
//	WriteParameter (ResLoadConstant , sizeof(void*), pResLoadConstant );
}
void PipeResLoadForm (void)
{
//	WriteParameter (ResLoadForm , sizeof(void*), pResLoadForm );
}
void PipeResLoadMenu (void)
{
//	WriteParameter (ResLoadMenu, sizeof(void*), pResLoadMenu);
}



////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
void PipeDrvEntryPointV10 (void)
{
//	WriteParameter (DrvEntryPoint, sizeof(void*), pDrvEntryPoint);
}
void PipeVdrvClose (void)
{
//	WriteParameter (VdrvClose, sizeof(void*), pVdrvClose);
}
void PipeVdrvControl(void)
{
//	WriteParameter (VdrvControl, sizeof(void*), pVdrvControl);
}
void PipeVdrvOpen (void)
{
//	WriteParameter (VdrvOpen, sizeof(void*), pVdrvOpen);
}
void PipeVdrvStatus (void)
{
//	WriteParameter (VdrvStatus, sizeof(void*), pVdrvStatus);
}
void PipeVdrvWrite(void)
{
//	WriteParameter (VdrvWrite, sizeof(void*), pVdrvWrite);
}


////////////////////////////////////////////////////////////
// Window function, completed 80/80 functions now.
////////////////////////////////////////////////////////////
void PipeWinDrawBitmap (void)
{
	WriteParameter (WinDrawBitmap, sizeof(void*), pWinDrawBitmap);
}
void PipeWinDrawChar (void)
{
	WriteParameter (WinDrawChar, sizeof(void*), pWinDrawChar);
}
void PipeWinDrawChars (void)
{
	WriteParameter (WinDrawChars, sizeof(void*), pWinDrawChars);
}
void PipeWinDrawGrayLine (void)
{
	WriteParameter (WinDrawGrayLine, sizeof(void*), pWinDrawGrayLine);
}
void PipeWinDrawGrayRectangleFrame (void)
{
	WriteParameter (WinDrawGrayRectangleFrame, sizeof(void*), pWinDrawGrayRectangleFrame);
}
void PipeWinDrawInvertedChars (void)
{
	WriteParameter (WinDrawInvertedChars, sizeof(void*), pWinDrawInvertedChars);
}
void PipeWinDrawLine (void)
{
	WriteParameter (WinDrawLine, sizeof(void*), pWinDrawLine);
}
void PipeWinDrawPixel (void)
{
	WriteParameter (WinDrawPixel, sizeof(void*), pWinDrawPixel);
}
void PipeWinDrawRectangle(void)
{
	WriteParameter (WinDrawRectangle, sizeof(void*), pWinDrawRectangle);
}
void PipeWinDrawRectangleFrame (void)
{
	WriteParameter (WinDrawRectangleFrame, sizeof(void*), pWinDrawRectangleFrame);
}
void PipeWinDrawTruncChars (void)
{
	WriteParameter (WinDrawTruncChars, sizeof(void*), pWinDrawTruncChars);
}
void PipeWinEraseChars (void)
{
	WriteParameter (WinEraseChars, sizeof(void*), pWinEraseChars);
}
void PipeWinEraseLine (void)
{
	WriteParameter (WinEraseLine, sizeof(void*), pWinEraseLine);
}
void PipeWinErasePixel (void)
{
	WriteParameter (WinErasePixel, sizeof(void*), pWinErasePixel);
}
void PipeWinEraseRectangle (void)
{
	WriteParameter (WinEraseRectangle, sizeof(void*), pWinEraseRectangle);
}
void PipeWinEraseWindow (void)
{
	WriteParameter (WinEraseWindow, sizeof(void*), pWinEraseWindow);
}
void PipeWinFillLine (void)
{
	WriteParameter (WinFillLine, sizeof(void*), pWinFillLine);
}
void PipeWinFillRectangle (void)
{
	WriteParameter (WinFillRectangle, sizeof(void*), pWinFillRectangle);
}
void PipeWinGetClip (void)
{
	WriteParameter (WinGetClip, sizeof(void*), pWinGetClip);
}
void PipeWinGetPixel (void)
{
	WriteParameter (WinGetPixel, sizeof(void*), pWinGetPixel);
}
void PipeWinInvertPixel(void)
{
	WriteParameter (WinInvertPixel, sizeof(void*), pWinInvertPixel);
}
void PipeWinInvertRectangle (void)
{
	WriteParameter (WinInvertRectangle , sizeof(void*), pWinInvertRectangle);
}

void PipeWinPaintPixel(void)
{
	WriteParameter (WinPaintPixel, sizeof(void*), pWinPaintPixel);
}
void PipeWinPaintPixels (void)
{
	WriteParameter (WinPaintPixels, sizeof(void*), pWinPaintPixels);
}
void PipeWinPaintRectangle (void)
{
	WriteParameter (WinPaintRectangle, sizeof(void*), pWinPaintRectangle);
}
void PipeWinPopDrawState (void)
{
	WriteParameter (WinPopDrawState, sizeof(void*), pWinPopDrawState);
}
void PipeWinPushDrawState (void)
{
	WriteParameter (WinPushDrawState, sizeof(void*), pWinPushDrawState);
}
void PipeWinResetClip(void)
{
	WriteParameter (WinResetClip, sizeof(void*), pWinResetClip);
}
void PipeWinSetBackColor (void)
{
	WriteParameter (WinSetBackColor, sizeof(void*), pWinSetBackColor);
}
void PipeWinSetClip (void)
{
	WriteParameter (WinSetClip, sizeof(void*), pWinSetClip);
}
void PipeWinSetForeColor (void)
{
	WriteParameter (WinSetForeColor, sizeof(void*), pWinSetForeColor);
}



void PipeWinClipRectangle (void)
{
//	WriteParameter (WinClipRectangle , sizeof(void*), pWinClipRectangle );
}
void PipeWinCopyRectangle (void)
{
//	WriteParameter (WinCopyRectangle, sizeof(void*), pWinCopyRectangle);
}
void PipeWinCreateBitmapWindow(void)
{
//	WriteParameter (WinCreateBitmapWindow, sizeof(void*), pWinCreateBitmapWindow);
}
void PipeWinCreateOffscreenWindow(void)
{
//	WriteParameter (WinCreateOffscreenWindow, sizeof(void*), pWinCreateOffscreenWindow);
}
void PipeWinCreateWindow (void)
{
//	WriteParameter (WinCreateWindow, sizeof(void*), pWinCreateWindow);
}
void PipeWinDeleteWindow(void)
{
//	WriteParameter (WinDeleteWindow, sizeof(void*), pWinDeleteWindow);
}
void PipeWinDisplayToWindowPt(void)

{
//	WriteParameter (WinDisplayToWindowPt, sizeof(void*), pWinDisplayToWindowPt);
}
void PipeWinEraseRectangleFrame(void)
{
//	WriteParameter (WinEraseRectangleFrame, sizeof(void*), pWinEraseRectangleFrame);
}
void PipeWinGetActiveWindow(void)
{
//	WriteParameter (WinGetActiveWindow, sizeof(void*), pWinGetActiveWindow);
}
void PipeWinGetBitmap(void)
{
//	WriteParameter (WinGetBitmap, sizeof(void*), pWinGetBitmap);
}
void PipeWinGetDisplayExtent (void)
{
//	WriteParameter (WinGetDisplayExtent , sizeof(void*), pWinGetDisplayExtent );
}
void PipeWinGetDisplayWindow (void)
{
//	WriteParameter (WinGetDisplayWindow, sizeof(void*), pWinGetDisplayWindow);
}
void PipeWinGetDrawWindow (void)
{
//	WriteParameter (WinGetDrawWindow, sizeof(void*), pWinGetDrawWindow);
}
void PipeWinGetFirstWindow (void)
{
//	WriteParameter (WinGetFirstWindow, sizeof(void*), pWinGetFirstWindow);
}
void PipeWinGetFramesRectangle (void)
{
//	WriteParameter (WinGetFramesRectangle, sizeof(void*), pWinGetFramesRectangle);
}
void PipeWinGetPattern (void)
{
//	WriteParameter (WinGetPattern, sizeof(void*), pWinGetPattern);
}
void PipeWinGetPatternType (void)
{
//	WriteParameter (WinGetPatternType, sizeof(void*), pWinGetPatternType);
}
void PipeWinGetWindowBounds(void)
{
//	WriteParameter (WinGetWindowBounds, sizeof(void*), pWinGetWindowBounds);
}
void PipeWinGetWindowExtent(void)
{
//	WriteParameter (WinGetWindowExtent, sizeof(void*), pWinGetWindowExtent);
}
void PipeWinGetWindowFrameRect(void)
{
//	WriteParameter (WinGetWindowFrameRect, sizeof(void*), pWinGetWindowFrameRect);
}
void PipeWinIndexToRGB(void)
{
//	WriteParameter (WinIndexToRGB, sizeof(void*), pWinIndexToRGB);
}
void PipeWinInvertChars(void)
{
//	WriteParameter (WinInvertChars, sizeof(void*), pWinInvertChars);
}
void PipeWinInvertLine(void)
{
//	WriteParameter (WinInvertLine, sizeof(void*), pWinInvertLine);
}
void PipeWinInvertRectangleFrame(void)
{
//	WriteParameter (WinInvertRectangleFrame, sizeof(void*), pWinInvertRectangleFrame);
}
void PipeWinModal(void)
{
//	WriteParameter (WinModal, sizeof(void*), pWinModal);
}
void PipeWinPaintBitmap(void)
{
//	WriteParameter (WinPaintBitmap, sizeof(void*), pWinPaintBitmap);
}
void PipeWinPaintChar(void)
{
//	WriteParameter (WinPaintChar, sizeof(void*), pWinPaintChar);
}
void PipeWinPaintChars(void)
{
//	WriteParameter (WinPaintChars, sizeof(void*), pWinPaintChars);
}
void PipeWinPaintLine(void)
{
//	WriteParameter (WinPaintLine, sizeof(void*), pWinPaintLine);
}
void PipeWinPaintLines(void)
{
//	WriteParameter (WinPaintLines, sizeof(void*), pWinPaintLines);
}
void PipeWinPaintRectangleFrame(void)
{
//	WriteParameter (WinPaintRectangleFrame, sizeof(void*), pWinPaintRectangleFrame);
}
void PipeWinPalette(void)
{
//	WriteParameter (WinPalette, sizeof(void*), pWinPalette);
}
void PipeWinRestoreBits(void)
{
//	WriteParameter (WinRestoreBits, sizeof(void*), pWinRestoreBits);
}
void PipeWinRGBToIndex(void)
{
//	WriteParameter (WinRGBToIndex, sizeof(void*), pWinRGBToIndex);
}
void PipeWinSaveBits(void)
{
//	WriteParameter (WinSaveBits, sizeof(void*), pWinSaveBits);
}
void PipeWinScreenLock(void)
{
//	WriteParameter (WinScreenLock, sizeof(void*), pWinScreenLock);
}
void PipeWinScreenMode(void)
{
//	WriteParameter (WinScreenMode, sizeof(void*), pWinScreenMode);
}
void PipeWinScreenUnlock(void)
{
//	WriteParameter (WinScreenUnlock, sizeof(void*), pWinScreenUnlock);
}
void PipeWinScrollRectangle(void)
{
//	WriteParameter (WinScrollRectangle, sizeof(void*), pWinScrollRectangle);
}
void PipeWinSetActiveWindow(void)
{
//	WriteParameter (WinSetActiveWindow, sizeof(void*), pWinSetActiveWindow);
}
void PipeWinSetDrawMode (void)
{
//	WriteParameter (WinSetDrawMode, sizeof(void*), pWinSetDrawMode);
}
void PipeWinSetDrawWindow (void)
{
//	WriteParameter (WinSetDrawWindow , sizeof(void*), pWinSetDrawWindow );
}
void PipeWinSetPattern(void)
{
//	WriteParameter (WinSetPattern, sizeof(void*), pWinSetPattern);
}
void PipeWinSetPatternType(void)
{
//	WriteParameter (WinSetPatternType, sizeof(void*), pWinSetPatternType);
}
void PipeWinSetTextColor(void)
{
//	WriteParameter (WinSetTextColor, sizeof(void*), pWinSetTextColor);
}
void PipeWinSetUnderlineMode(void)
{
//	WriteParameter (WinSetUnderlineMode, sizeof(void*), pWinSetUnderlineMode);
}
void PipeWinSetWindowBounds(void)
{
//	WriteParameter (WinSetWindowBounds, sizeof(void*), pWinSetWindowBounds);
}
void PipeWinValidateHandle(void)
{
//	WriteParameter (WinValidateHandle, sizeof(void*), pWinValidateHandle);
}
void PipeWinWindowToDisplayPt(void)
{
//	WriteParameter (WinWindowToDisplayPt, sizeof(void*), pWinWindowToDisplayPt);
}
