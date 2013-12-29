# Copyright (C) 1995,1996 Robert de Bath <rdebath@cix.compulink.co.uk>
# This file is part of the Linux-8086 C library and is distributed
# under the GNU Library General Public License.

CLIENTLIBDIR    =       ../ClientLib/
LIBC=$(CLIENTLIBDIR)libclient9.a

include ./make.rules

LIB9SRC=lib9.c
LIB9OBJ=TblDrawTable.o		\
TblEditing.o			\
TblEraseTable.o			\
TblFindRowData.o		\
TblFindRowID.o			\
TblGetBounds.o			\
TblGetColumnSpacing.o	\
TblGetColumnWidth.o	\
TblGetCurrentField.o	\
TblGetItemBounds.o	\
TblGetItemFont.o	\
TblGetItemInt.o		\
TblGetItemPtr.o		\
TblGetLastUsableRow.o	\
TblGetNumberOfRows.o	\
TblGetRowData.o		\
TblGetRowHeight.o	\
TblGetRowID.o		\
TblGetSelection.o	\
TblGrabFocus.o		\
TblHandleEvent.o	\
TblHasScrollBar.o	\
TblInsertRow.o		\
TblMarkRowInvalid.o	\
TblMarkTableInvalid.o	\
TblRedrawTable.o	\
TblReleaseFocus.o	\
TblRemoveRow.o		\
TblReverseItem.o	\
TblRowInvalid.o		\
TblRowMasked.o		\
TblRowSelectable.o	\
TblRowUsable.o		\
TblSelectItem.o		\
TblSetBounds.o		\
TblSetColumnEditIndicator.o	\
TblSetColumnMasked.o		\
TblSetColumnSpacing.o	\
TblSetColumnUsable.o	\
TblSetColumnWidth.o	\
TblSetCustomDrawProcedure.o	\
TblSetItemFont.o		\
TblSetItemInt.o			\
TblSetItemPtr.o			\
TblSetItemStyle.o		\
TblSetLoadDataProcedure.o	\
TblSetRowData.o			\
TblSetRowHeight.o		\
TblSetRowID.o			\
TblSetRowMasked.o		\
TblSetRowSelectable.o		\
TblSetRowStaticHeight.o		\
TblSetRowUsable.o		\
TblSetSaveDataProcedure.o	\
TblUnhighlightSelection.o	\
TableDrawItemFuncType.o		\
TableLoadDataFuncType.o		\
TableSaveDataFuncType.o		\
DateAdjust.o			\
DateDaysToDate.o		\
DateSecondsToDate.o		\
DateTemplateToAscii.o		\
DateToAscii.o			\
DateToDays.o			\
DateToDOWDmFormat.o		\
DayOfMonth.o			\
DayOfWeek.o			\
DaysInMonth.o			\
TimeAdjust.o			\
TimDateTimeToSeconds.o		\
TimGetSeconds.o			\
TimGetTicks.o			\
TimSecondsToDateTime.o		\
TimSetSeconds.o			\
TimeToAscii.o			\
UIColorGetTableEntryIndex.o	\
UIColorGetTableEntryRGB.o	\
UIColorSetTableEntry.o		\
UIBrightnessAdjust.o		\
UIContrastAdjust.o		\
UIPickColor.o			\
PhoneNumberLookup.o		\
ResLoadConstant.o		\
ResLoadForm.o			\
ResLoaDmenu.o			\
DrvEntryPoint.o			\
VdrvClose.o			\
VdrvControl.o			\
VdrvOpen.o			\
VdrvStatus.o			\
VdrvWrite.o			\
WinClipRectangle.o		\
WinCopyRectangle.o		\
WinCreateBitmapWindow.o		\
WinCreateOffscreenWindow.o	\
WinCreateWindow.o		\
WinDeleteWindow.o		\
WinDisplayToWindowPt.o		\
WinDrawBitmap.o			\
WinDrawChar.o			\
WinDrawChars.o			\
WinDrawGrayLine.o		\
WinDrawGrayRectangleFrame.o	\
WinDrawInvertedChars.o	\
WinDrawLine.o		\
WinDrawPixel.o		\
WinDrawRectangle.o	\
WinDrawRectangleFrame.o	\
WinDrawTruncChars.o	\
WinEraseChars.o		\
WinEraseLine.o		\
WinErasePixel.o		\
WinEraseRectangle.o	\
WinEraseRectangleFrame.o	\
WinEraseWindow.o		\
WinFillLine.o			\
WinFillRectangle.o		\
WinGetActiveWindow.o		\
WinGetBitmap.o			\
WinGetClip.o			\
WinGetDisplayExtent.o		\
WinGetDisplayWindow.o		\
WinGetDrawWindow.o		\
WinGetFirstWindow.o		\
WinGetFramesRectangle.o		\
WinGetPattern.o			\
WinGetPatternType.o		\
WinGetWindowBounds.o		\
WinGetWindowExtent.o		\
WinGetWindowFrameRect.o		\
WinIndexToRGB.o			\
WinInvertChars.o		\
WinInvertLine.o			\
WinGetPixel.o			\
WinInvertPixel.o		\
WinInvertRectangle.o		\
WinInvertRectangleFrame.o	\
WinModal.o			\
WinPaintBitmap.o		\
WinPaintChar.o			\
WinPaintChars.o			\
WinPaintLine.o			\
WinPaintLines.o			\
WinPaintPixel.o			\
WinPaintPixels.o		\
WinPaintRectangle.o		\
WinPaintRectangleFrame.o	\
WinPalette.o			\
WinPopDrawState.o		\
WinPushDrawState.o		\
WinResetClip.o			\
WinRestoreBits.o		\
WinRGBToIndex.o			\
WinSaveBits.o			\
WinScreenLock.o			\
WinScreenMode.o			\
WinScreenUnlock.o		\
WinScrollRectangle.o		\
WinSetActiveWindow.o		\
WinSetBackColor.o		\
WinSetClip.o			\
WinSetDrawMode.o		\
WinSetDrawWindow.o		\
WinSetForeColor.o		\
WinSetPattern.o			\
WinSetPatternType.o		\
WinSetTextColor.o		\
WinSetUnderlineMode.o		\
WinSetWindowBounds.o		\
WinValidateHandle.o		\
WinWindowToDisplayPt.o		\
VSetRCPFile.o






OBJ=  $(LIB9OBJ)

#CFLAGS=$(ARCH) $(CCFLAGS) $(DEFS)

all: 	$(LIBC)
	@$(RM) $(OBJ)

$(LIBC): $(LIBC)($(OBJ))


$(LIBC)($(LIB9OBJ)): $(LIB9SRC)
	$(CC) $(CFLAGS) -DL_$* $< -c -o $*.o
	$(AR) $(ARFLAGS) $@ $*.o


transfer:
	-@rm -f ../include/stdio.h
	cp -p stdio.h ../include/.

transfer2:
	cp -p ../include/stdio.h .

clean:
	rm -f *.o $(CLIENTLIBDIR)libclient9.a

#$(LIBC)($(OBJ)): transfer2 stdio.h

