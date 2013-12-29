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
// Time Manager Library, completed 17/17 functions now.
////////////////////////////////////////////////////////////

#ifdef L_DateAdjust
void DateAdjust (DatePtr dateP, Int32 adjustment)
{
	void (*DateAdjustP) (DatePtr dateP, Int32 adjustment);

	GetParameter (&DateAdjustP , sizeof(void *), pDateAdjust );
	(*DateAdjustP) ( dateP,  adjustment);
}
#endif

#ifdef L_DateDaysToDate
void DateDaysToDate (UInt32 days, DatePtr dateP)
{
	void (*DateDaysToDateP) (UInt32 days, DatePtr dateP);

	GetParameter (&DateDaysToDateP , sizeof(void *), pDateDaysToDate );
	(*DateDaysToDateP) ( days,  dateP);
}
#endif

#ifdef L_DateSecondsToDate
void DateSecondsToDate (UInt32 seconds, DatePtr dateP)
{
	void (*DateSecondsToDateP) (UInt32 seconds, DatePtr dateP);

	GetParameter (&DateSecondsToDateP , sizeof(void *), pDateSecondsToDate );
	(*DateSecondsToDateP) ( seconds,  dateP);
}
#endif

#ifdef L_DateTemplateToAscii
void DateTemplateToAscii (const Char *templateP, UInt8 months,UInt8 days, UInt16 years, Char *stringP,Int16 stringLen)
{
	void (*DateTemplateToAsciiP) (const Char *templateP, UInt8 months,UInt8 days, UInt16 years, Char *stringP,Int16 stringLen);

	GetParameter (&DateTemplateToAsciiP , sizeof(void *), pDateTemplateToAscii );
	(*DateTemplateToAsciiP) (templateP,  months, days,  years, stringP, stringLen);
}
#endif

#ifdef L_DateToAscii
void DateToAscii (UInt8 months, UInt8 days, UInt16 years, DateFormatType dateFormat, Char *pString)
{
	void (*DateToAsciiP) (UInt8 months, UInt8 days, UInt16 years, DateFormatType dateFormat, Char *pString);

	GetParameter (&DateToAsciiP , sizeof(void *), pDateToAscii );
	(*DateToAsciiP) ( months,  days,  years,  dateFormat, pString);
}
#endif

#ifdef L_DateToDays
UInt32 DateToDays (DateType date)
{
	UInt32 (*DateToDaysP) (DateType date);

	GetParameter (&DateToDaysP , sizeof(void *), pDateToDays );
	return (*DateToDaysP) (date);

}
#endif

#ifdef L_DateToDOWDMFormat
void DateToDOWDMFormat (UInt8 months, UInt8 days, UInt16 years,
								DateFormatType dateFormat, Char *pString)
{
	void (*DateToDOWDMFormatP) (UInt8 months, UInt8 days, UInt16 years,
									DateFormatType dateFormat, Char *pString);

	GetParameter (&DateToDOWDMFormatP , sizeof(void *), pDateToDOWDMFormat );
	(*DateToDOWDMFormatP) ( months,  days,  years, 	 dateFormat, pString);
}
#endif

#ifdef L_DayOfMonth
Int16 DayOfMonth (Int16 month, Int16 day, Int16 year)
{
	Int16 (*DayOfMonthP) (Int16 month, Int16 day, Int16 year);

	GetParameter (&DayOfMonthP , sizeof(void *), pDayOfMonth );
	return (*DayOfMonthP) ( month,  day,  year);
}
#endif

#ifdef L_DayOfWeek
Int16 DayOfWeek (Int16 month, Int16 day, Int16 year)
{
	Int16 (*DayOfWeekP) (Int16 month, Int16 day, Int16 year);

	GetParameter (&DayOfWeekP , sizeof(void *), pDayOfWeek );
	return(*DayOfWeekP) ( month,  day,  year);
}
#endif

#ifdef L_DaysInMonth
Int16 DaysInMonth (Int16 month, Int16 year)
{
	Int16 (*DaysInMonthP) (Int16 month, Int16 year);

	GetParameter (&DaysInMonthP , sizeof(void *), pDaysInMonth );
	return (*DaysInMonthP) ( month,  year);
}
#endif

#ifdef L_TimeAdjust
void TimeAdjust (DateTimePtr dateTimeP, Int32 adjustment)
{
	void (*TimeAdjustP) (DateTimePtr dateTimeP, Int32 adjustment);

	GetParameter (&TimeAdjustP , sizeof(void *), pTimeAdjust );
	(*TimeAdjustP) ( dateTimeP,  adjustment);
}
#endif

#ifdef L_TimDateTimeToSeconds
UInt32 TimDateTimeToSeconds (DateTimePtr dateTimeP)
{
	UInt32 (*TimDateTimeToSecondsP) (DateTimePtr dateTimeP);

	GetParameter (&TimDateTimeToSecondsP , sizeof(void *), pTimDateTimeToSeconds );
	return (*TimDateTimeToSecondsP) ( dateTimeP);
}
#endif

#ifdef L_TimGetSeconds
UInt32 TimGetSeconds (void)
{
	UInt32 (*TimGetSecondsP) (void);

	GetParameter (&TimGetSecondsP , sizeof(void *), pTimGetSeconds );
	return(*TimGetSecondsP) ();
}
#endif

#ifdef L_TimGetTicks
UInt32 TimGetTicks (void)
{
	UInt32 (*TimGetTicksP) (void);

	GetParameter (&TimGetTicksP , sizeof(void *), pTimGetTicks );
	return (*TimGetTicksP) ();
}
#endif

#ifdef L_TimSecondsToDateTime
void TimSecondsToDateTime (UInt32 seconds, DateTimePtr dateTimeP)
{
	void (*TimSecondsToDateTimeP) (UInt32 seconds, DateTimePtr dateTimeP);

	GetParameter (&TimSecondsToDateTimeP , sizeof(void *), pTimSecondsToDateTime );
	(*TimSecondsToDateTimeP) ( seconds,  dateTimeP);
}
#endif

#ifdef L_TimSetSeconds
void TimSetSeconds (UInt32 seconds)
{
	void (*TimSetSecondsP) (UInt32 seconds);

	GetParameter (&TimSetSecondsP , sizeof(void *), pTimSetSeconds );
	(*TimSetSecondsP) (seconds);
}
#endif

#ifdef L_TimeToAscii
void TimeToAscii (UInt8 hours, UInt8 minutes,
						 TimeFormatType timeFomrat, Char *pString)
{
	void (*TimeToAsciiP) (UInt8 hours, UInt8 minutes,
						 TimeFormatType timeFomrat, Char *pString);

	GetParameter (&TimeToAsciiP , sizeof(void *), pTimeToAscii );
	(*TimeToAsciiP) ( hours,  minutes,   timeFomrat, pString);
}
#endif

////////////////////////////////////////////////////////////
// Table Library, completed 57/57 functions now.
////////////////////////////////////////////////////////////
#ifdef L_TblDrawTable
void TblDrawTable (TableType *tableP)
{
	void (*TblDrawTableP) (TableType *tableP);

	GetParameter (&TblDrawTableP , sizeof(void *), pTblDrawTable );
	(*TblDrawTableP) (tableP);
}
#endif

#ifdef L_TblEditing
Boolean TblEditing (const TableType *tableP)
{
	Boolean (*TblEditingP)(const TableType *tableP);

	GetParameter (&TblEditingP , sizeof(void *), pTblEditing );
	return(*TblEditingP)( tableP);
}
#endif

#ifdef L_TblEraseTable
void TblEraseTable (TableType *tableP)
{
	void (*TblEraseTableP) (TableType *tableP);

	GetParameter (&TblEraseTableP , sizeof(void *), pTblEraseTable );
	(*TblEraseTableP) (tableP);
}
#endif

#ifdef L_TblFindRowData
Boolean TblFindRowData (const TableType *tableP, UInt32 data, Int16 *rowP)
{
	Boolean (*TblFindRowDataP) (const TableType *tableP, UInt32 data, Int16 *rowP);

	GetParameter (&TblFindRowDataP , sizeof(void *), pTblFindRowData );
	return (*TblFindRowDataP) (tableP,  data, rowP);
}
#endif

#ifdef L_TblFindRowID
Int16 TblFindRowID (const TableType *tableP, UInt16 id, Int16 *rowP)
{
	Int16 (*TblFindRowIDP) (const TableType *tableP, UInt16 id, Int16 *rowP);

	GetParameter (&TblFindRowIDP , sizeof(void *), pTblFindRowID );
	return (*TblFindRowIDP) (tableP,  id, rowP);
}
#endif

#ifdef L_TblGetBounds
void TblGetBounds (const TableType *tableP, RectangleType *r)
{
	void (*TblGetBoundsP) (const TableType *tableP, RectangleType *r);

	GetParameter (&TblGetBoundsP , sizeof(void *), pTblGetBounds );
	(*TblGetBoundsP) ( tableP, r);
}
#endif

#ifdef L_TblGetColumnSpacing
Int16 TblGetColumnSpacing (const TableType *tableP, Int16 column)
{
	Int16 (*TblGetColumnSpacingP) (const TableType *tableP, Int16 column);

	GetParameter (&TblGetColumnSpacingP , sizeof(void *), pTblGetColumnSpacing );
}
#endif

#ifdef L_TblGetColumnWidth
Int16 TblGetColumnWidth (const TableType *tableP, Int16 column)
{
	Int16 (*TblGetColumnWidthP) (const TableType *tableP, Int16 column);

	GetParameter (&TblGetColumnWidthP , sizeof(void *), pTblGetColumnWidth );
	return (*TblGetColumnWidthP) (tableP,  column);
}
#endif

#ifdef L_TblGetCurrentField
FieldPtr TblGetCurrentField (const TableType *tableP)
{
	FieldPtr (*TblGetCurrentFieldP) (const TableType *tableP);

	GetParameter (&TblGetCurrentFieldP , sizeof(void *), pTblGetCurrentField );
	return (*TblGetCurrentFieldP) (  tableP);
}
#endif

#ifdef L_TblGetItemBounds
void TblGetItemBounds (const TableType *tableP, Int16 row, Int16 column, RectangleType *r)
{
	void (*TblGetItemBoundsP) (const TableType *tableP, Int16 row, Int16 column, RectangleType *r);

	GetParameter (&TblGetItemBoundsP , sizeof(void *), pTblGetItemBounds );
	(*TblGetItemBoundsP) ( tableP,  row,  column, r);
}
#endif

#ifdef L_TblGetItemFont
FontID TblGetItemFont (const TableType *tableP, Int16 row, Int16 column)
{
	FontID (*TblGetItemFontP) (const TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblGetItemFontP , sizeof(void *), pTblGetItemFont );
	return (*TblGetItemFontP) (tableP,  row,  column);
}
#endif

#ifdef L_TblGetItemInt
Int16 TblGetItemInt (const TableType *tableP, Int16 row, Int16 column)
{
	Int16 (*TblGetItemIntP) (const TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblGetItemIntP , sizeof(void *), pTblGetItemInt );
}
#endif

#ifdef L_TblGetItemPtr
void *TblGetItemPtr (const TableType *tableP, Int16 row, Int16 column)
{
	void *(*TblGetItemPtrP) (const TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblGetItemPtrP , sizeof(void *), pTblGetItemPtr );
	return(*TblGetItemPtrP) (tableP,  row,  column);
}
#endif

#ifdef L_TblGetLastUsableRow
Int16 TblGetLastUsableRow (const TableType *tableP)
{
	Int16 (*TblGetLastUsableRowP) (const TableType *tableP);

	GetParameter (&TblGetLastUsableRowP , sizeof(void *), pTblGetLastUsableRow );
	return (*TblGetLastUsableRowP) ( tableP);
}
#endif

#ifdef L_TblGetNumberOfRows
Int16 TblGetNumberOfRows (const TableType *tableP)
{
	Int16 (*TblGetNumberOfRowsP) (const TableType *tableP);

	GetParameter (&TblGetNumberOfRowsP , sizeof(void *), pTblGetNumberOfRows );
	return(*TblGetNumberOfRowsP) (tableP);
}
#endif

#ifdef L_TblGetRowData
UInt32 TblGetRowData (const TableType *tableP, Int16 row)
{
	UInt32 (*TblGetRowDataP) (const TableType *tableP, Int16 row);

	GetParameter (&TblGetRowDataP , sizeof(void *), pTblGetRowData );
	return(*TblGetRowDataP) (tableP,  row);
}
#endif

#ifdef L_TblGetRowHeight
Coord TblGetRowHeight (const TableType *tableP, Int16 row)
{
	Coord (*TblGetRowHeightP) (const TableType *tableP, Int16 row);

	GetParameter (&TblGetRowHeightP , sizeof(void *), pTblGetRowHeight );
	return(*TblGetRowHeightP) ( tableP,  row);
}
#endif

#ifdef L_TblGetRowID
UInt16 TblGetRowID (const TableType *tableP, Int16 row)
{
	UInt16 (*TblGetRowIDP) (const TableType *tableP, Int16 row);

	GetParameter (&TblGetRowIDP , sizeof(void *), pTblGetRowID );
	return(*TblGetRowIDP) ( tableP,  row);
}
#endif

#ifdef L_TblGetSelection
Boolean TblGetSelection (const TableType *tableP, Int16 *rowP, Int16 *columnP)
{
	Boolean (*TblGetSelectionP) (const TableType *tableP, Int16 *rowP, Int16 *columnP);

	GetParameter (&TblGetSelectionP , sizeof(void *), pTblGetSelection );
	return (*TblGetSelectionP) (tableP, rowP, columnP);
}
#endif

#ifdef L_TblGrabFocus
void TblGrabFocus (TableType *tableP, Int16 row, Int16 column)
{
	void (*TblGrabFocusP) (TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblGrabFocusP , sizeof(void *), pTblGrabFocus );
	(*TblGrabFocusP) (tableP,  row,  column);
}
#endif

#ifdef L_TblHandleEvent
Boolean TblHandleEvent (TableType *tableP, EventType *event)
{     
	Boolean (*TblHandleEventP) (TableType *tableP, EventType *event);

	GetParameter (&TblHandleEventP , sizeof(void *), pTblHandleEvent );
	return(*TblHandleEventP) (tableP, event);
}
#endif

#ifdef L_TblHasScrollBar
void TblHasScrollBar (TableType *tableP, Boolean hasScrollBar)
{     
	void (*TblHasScrollBarP) (TableType *tableP, Boolean hasScrollBar);

	GetParameter (&TblHasScrollBarP , sizeof(void *), pTblHasScrollBar );
	(*TblHasScrollBarP) (tableP,  hasScrollBar);
}
#endif

#ifdef L_TblInsertRow
void TblInsertRow (TableType *tableP, Int16 row)
{     
	void (*TblInsertRowP) (TableType *tableP, Int16 row);

	GetParameter (&TblInsertRowP , sizeof(void *), pTblInsertRow );
	(*TblInsertRowP) (tableP,  row);
}
#endif

#ifdef L_TblMarkRowInvalid
void TblMarkRowInvalid (const TableType *tableP, Int16 row)
{     
	void (*TblMarkRowInvalidP) (const TableType *tableP, Int16 row);

	GetParameter (&TblMarkRowInvalidP , sizeof(void *), pTblMarkRowInvalid );
	(*TblMarkRowInvalidP) (tableP,  row);
}
#endif

#ifdef L_TblMarkTableInvalid
void TblMarkTableInvalid (const TableType *tableP)
{     
	void (*TblMarkTableInvalidP) (const TableType *tableP);

	GetParameter (&TblMarkTableInvalidP , sizeof(void *), pTblMarkTableInvalid );
	(*TblMarkTableInvalidP) ( tableP);
}
#endif

#ifdef L_TblRedrawTable
void TblRedrawTable (TableType *tableP)
{    
	void (*TblRedrawTableP) (TableType *tableP);

	GetParameter (&TblRedrawTableP , sizeof(void *), pTblRedrawTable );
	(*TblRedrawTableP) (tableP);
}
#endif

#ifdef L_TblReleaseFocus
void TblReleaseFocus (TableType *tableP)
{     
	void (*TblReleaseFocusP) (TableType *tableP);

	GetParameter (&TblReleaseFocusP , sizeof(void *), pTblReleaseFocus );
	(*TblReleaseFocusP) (tableP);
}
#endif

#ifdef L_TblRemoveRow
void TblRemoveRow (const TableType *tableP, Int16 row)
{     
	void (*TblRemoveRowP) (const TableType *tableP, Int16 row);

	GetParameter (&TblRemoveRowP , sizeof(void *), pTblRemoveRow );
	(*TblRemoveRowP) (tableP,  row);
}

#endif

#ifdef L_TblReverseItem
void TblReverseItem (TableType *tableP, Int16 row, Int16 column)
{
	void (*TblReverseItemP) (TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblReverseItemP , sizeof(void *), pTblReverseItem );
	(*TblReverseItemP) (tableP,  row,  column);
}
#endif

#ifdef L_TblRowInvalid
Boolean TblRowInvalid (const TableType *tableP, Int16 row)
{     
	Boolean (*TblRowInvalidP) (const TableType *tableP, Int16 row);

	GetParameter (&TblRowInvalidP , sizeof(void *), pTblRowInvalid );
	return (*TblRowInvalidP) ( tableP,  row);
}
#endif

#ifdef L_TblRowMasked
Boolean TblRowMasked (const TableType *tableP, Int16 row)
{     
	Boolean (*TblRowMaskedP) (const TableType *tableP, Int16 row);

	GetParameter (&TblRowMaskedP , sizeof(void *), pTblRowMasked );
	return (*TblRowMaskedP) (tableP,  row);
}
#endif

#ifdef L_TblRowSelectable
Boolean TblRowSelectable (const TableType *tableP, Int16 row)
{     
	Boolean (*TblRowSelectableP) (const TableType *tableP, Int16 row);

	GetParameter (&TblRowSelectableP , sizeof(void *), pTblRowSelectable );
	return(*TblRowSelectableP) (tableP,  row);
}
#endif

#ifdef L_TblRowUsable
Boolean TblRowUsable (TableType *tableP, Int16 row)
{     
	Boolean (*TblRowUsableP) (TableType *tableP, Int16 row);

	GetParameter (&TblRowUsableP , sizeof(void *), pTblRowUsable );
	return (*TblRowUsableP) (tableP,  row);
}
#endif

#ifdef L_TblSelectItem
void TblSelectItem (TableType *tableP, Int16 row, Int16 column)
{     
	void (*TblSelectItemP) (TableType *tableP, Int16 row, Int16 column);

	GetParameter (&TblSelectItemP , sizeof(void *), pTblSelectItem );
	(*TblSelectItemP) (tableP,  row,  column);
}
#endif

#ifdef L_TblSetBounds
void TblSetBounds (TableType *tableP, const RectangleType *rP)
{     
	void (*TblSetBoundsP) (TableType *tableP, const RectangleType *rP);

	GetParameter (&TblSetBoundsP , sizeof(void *), pTblSetBounds );
	(*TblSetBoundsP) (tableP, rP);
}
#endif

#ifdef L_TblSetColumnEditIndicator
void TblSetColumnEditIndicator (TableType *tableP, Int16 column, Boolean editIndicator)
{     
	void (*TblSetColumnEditIndicatorP) (TableType *tableP, Int16 column, Boolean editIndicator);

	GetParameter (&TblSetColumnEditIndicatorP , sizeof(void *), pTblSetColumnEditIndicator );
	(*TblSetColumnEditIndicatorP) (tableP,  column,  editIndicator);
}
#endif

#ifdef L_TblSetColumnMasked
void TblSetColumnMasked (TableType *tableP, Int16 column, Boolean masked)
{     
	void (*TblSetColumnMaskedP) (TableType *tableP, Int16 column, Boolean masked);

	GetParameter (&TblSetColumnMaskedP , sizeof(void *), pTblSetColumnMasked );
	(*TblSetColumnMaskedP) (tableP,  column,  masked);
}
#endif

#ifdef L_TblSetColumnSpacing
void TblSetColumnSpacing (TableType *tableP, Int16 column, Coord spacing)
{     
	void (*TblSetColumnSpacingP) (TableType *tableP, Int16 column, Coord spacing);
	
	GetParameter (&TblSetColumnSpacingP , sizeof(void *), pTblSetColumnSpacing );
	(*TblSetColumnSpacingP) (tableP,  column,  spacing);
}
#endif

#ifdef L_TblSetColumnUsable
void TblSetColumnUsable (TableType *tableP, Int16 column, Boolean usable)
{     
	void (*TblSetColumnUsableP) (TableType *tableP, Int16 column, Boolean usable);

	GetParameter (&TblSetColumnUsableP , sizeof(void *), pTblSetColumnUsable );
	(*TblSetColumnUsableP) (tableP,  column,  usable);
}
#endif

#ifdef L_TblSetColumnWidth
void TblSetColumnWidth (TableType *tableP, Int16 column, Coord width)
{     
	void (*TblSetColumnWidthP) (TableType *tableP, Int16 column, Coord width);

	GetParameter (&TblSetColumnWidthP , sizeof(void *), pTblSetColumnWidth );
	(*TblSetColumnWidthP) (tableP,  column,  width);
}
#endif

#ifdef L_TblSetCustomDrawProcedure
void TblSetCustomDrawProcedure (TableType *tableP, Int16 column, TableDrawItemFuncPtr drawCallback)
{     
	void (*TblSetCustomDrawProcedureP) (TableType *tableP, Int16 column, TableDrawItemFuncPtr drawCallback);
		
	GetParameter (&TblSetCustomDrawProcedureP , sizeof(void *), pTblSetCustomDrawProcedure );
	(*TblSetCustomDrawProcedureP) (tableP,  column,  drawCallback);
}
#endif

#ifdef L_TblSetItemFont
void TblSetItemFont (const TableType *tableP, Int16 row, Int16 column, FontID fontID)
{     
	void (*TblSetItemFontP) (const TableType *tableP, Int16 row, Int16 column, FontID fontID);

	GetParameter (&TblSetItemFontP , sizeof(void *), pTblSetItemFont );
	(*TblSetItemFontP) (tableP,  row,  column,  fontID);
}
#endif

#ifdef L_TblSetItemInt
void TblSetItemInt (TableType *tableP, Int16 row, Int16 column, Int16 value)
{     
	void (*TblSetItemIntP) (TableType *tableP, Int16 row, Int16 column, Int16 value);

	GetParameter (&TblSetItemIntP , sizeof(void *), pTblSetItemInt );
	(*TblSetItemIntP) (tableP,  row,  column,  value);
}
#endif

#ifdef L_TblSetItemPtr
void TblSetItemPtr (TableType *tableP, Int16 row, Int16 column, void *value)
{     
	void (*TblSetItemPtrP) (TableType *tableP, Int16 row, Int16 column, void *value);

	GetParameter (&TblSetItemPtrP , sizeof(void *), pTblSetItemPtr );
	(*TblSetItemPtrP) (tableP,  row,  column, value);
}
#endif

#ifdef L_TblSetItemStyle
void TblSetItemStyle (TableType *tableP, Int16 row, Int16 column, TableItemStyleType type)
{     
	void (*TblSetItemStyleP) (TableType *tableP, Int16 row, Int16 column, TableItemStyleType type);

	GetParameter (&TblSetItemStyleP , sizeof(void *), pTblSetItemStyle );
	(*TblSetItemStyleP) (tableP,  row,  column,  type);
}
#endif

#ifdef L_TblSetLoadDataProcedure
void TblSetLoadDataProcedure (TableType *tableP, Int16 column, TableLoadDataFuncPtr loadDataCallback)
{     
	void (*TblSetLoadDataProcedureP) (TableType *tableP, Int16 column, TableLoadDataFuncPtr loadDataCallback);

	GetParameter (&TblSetLoadDataProcedureP , sizeof(void *), pTblSetLoadDataProcedure );
	(*TblSetLoadDataProcedureP) (tableP,  column,  loadDataCallback);
}
#endif

#ifdef L_TblSetRowData
void TblSetRowData (TableType *tableP, Int16 row, UInt32 data)
{     
	void (*TblSetRowDataP) (TableType *tableP, Int16 row, UInt32 data);

	GetParameter (&TblSetRowDataP , sizeof(void *), pTblSetRowData );
	(*TblSetRowDataP) (tableP, row,  data);
}
#endif

#ifdef L_TblSetRowHeight
void TblSetRowHeight (TableType *tableP, Int16 row, Coord height)
{     
	void (*TblSetRowHeightP) (TableType *tableP, Int16 row, Coord height);

	GetParameter (&TblSetRowHeightP , sizeof(void *), pTblSetRowHeight );
	(*TblSetRowHeightP) (tableP,  row,  height);
}
#endif

#ifdef L_TblSetRowID
void TblSetRowID (TableType *tableP, Int16 row, UInt16 id)
{     
	void (*TblSetRowIDP) (TableType *tableP, Int16 row, UInt16 id);

	GetParameter (&TblSetRowIDP , sizeof(void *), pTblSetRowID );
	(*TblSetRowIDP) (tableP,  row,  id);
}
#endif

#ifdef L_TblSetRowMasked
void TblSetRowMasked (TableType *tableP, Int16 row, Boolean masked)
{     
	void (*TblSetRowMaskedP) (TableType *tableP, Int16 row, Boolean masked);

	GetParameter (&TblSetRowMaskedP , sizeof(void *), pTblSetRowMasked );
	(*TblSetRowMaskedP) (tableP,  row,  masked);
}
#endif

#ifdef L_TblSetRowSelectable
void TblSetRowSelectable (TableType *tableP, Int16 row, Boolean selectable)
{     
	void (*TblSetRowSelectableP) (TableType *tableP, Int16 row, Boolean selectable);

	GetParameter (&TblSetRowSelectableP , sizeof(void *), pTblSetRowSelectable );
	(*TblSetRowSelectableP) (tableP, row,  selectable);
}
#endif

#ifdef L_TblSetRowStaticHeight
void TblSetRowStaticHeight (TableType *tableP, Int16 row, Boolean staticHeight)
{     
	void (*TblSetRowStaticHeightP) (TableType *tableP, Int16 row, Boolean staticHeight);

	GetParameter (&TblSetRowStaticHeightP , sizeof(void *), pTblSetRowStaticHeight );
	(*TblSetRowStaticHeightP) (tableP,  row,  staticHeight);
}
#endif

#ifdef L_TblSetRowUsable
void TblSetRowUsable (TableType *tableP, Int16 row, Boolean usable)
{     
	void (*TblSetRowUsableP) (TableType *tableP, Int16 row, Boolean usable);

	GetParameter (&TblSetRowUsableP , sizeof(void *), pTblSetRowUsable );
	(*TblSetRowUsableP) (tableP,  row,  usable);
}
#endif

#ifdef L_TblSetSaveDataProcedure
void TblSetSaveDataProcedure (TableType *tableP, Int16 column, TableSaveDataFuncPtr saveDataCallback)
{     
	void (*TblSetSaveDataProcedureP) (TableType *tableP, Int16 column, TableSaveDataFuncPtr saveDataCallback);

	GetParameter (&TblSetSaveDataProcedureP , sizeof(void *), pTblSetSaveDataProcedure );
	(*TblSetSaveDataProcedureP) (tableP,  column,  saveDataCallback);
}
#endif

#ifdef L_TblUnhighlightSelection
void TblUnhighlightSelection (TableType *tableP)
{     
	void (*TblUnhighlightSelectionP) (TableType *tableP);

	GetParameter (&TblUnhighlightSelectionP , sizeof(void *), pTblUnhighlightSelection );
	(*TblUnhighlightSelectionP) (tableP);
}
#endif

/*
void TableDrawItemFuncType (void *tableP, Int16 row, Int16 column, RectangleType *bounds)
{     
	void (*TableDrawItemFuncTypeP) (void *tableP, Int16 row, Int16 column, RectangleType *bounds);

	GetParameter (&TableDrawItemFuncTypeP , sizeof(void *), pTableDrawItemFuncType );
	(*TableDrawItemFuncTypeP) (tableP,  row,  column, bounds);
}
*/
//Err TableLoadDataFuncType (void *tableP, Int16 row, Int16 column, Boolan editable,
//								  MemHandle *dataH, Int16 *dataOffset, Int16 *dataSize, 
//								  FieldPtr fld);
/*
Boolean TableSaveDataFuncType (void *tableP, Int16 row, Int16 column)
{     
	Boolean (*TableSaveDataFuncTypeP) (void *tableP, Int16 row, Int16 column);

	GetParameter (&TableSaveDataFuncTypeP , sizeof(void *), pTableSaveDataFuncType );
	(*TableSaveDataFuncTypeP) (tableP,  row,  column);
}
*/




////////////////////////////////////////////////////////////
// UI Color List Library, completed 0/3 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_UIColorGetTableEntryIndex
IndexedColorType UIColorGetTableEntryIndex(UIColorTableEntries which)
{
	IndexedColorType (*UIColorGetTableEntryIndexP)(UIColorTableEntries which);

	GetParameter (&UIColorGetTableEntryIndexP , sizeof(void *), pUIColorGetTableEntryIndex );
	return  (*UIColorGetTableEntryIndexP)(which);
}
#endif

#ifdef L_UIColorGetTableEntryRGB
void UIColorGetTableEntryRGB(UIColorTableEntries which, RGBColorType *rgbP)
{
	void (*UIColorGetTableEntryRGBP)(UIColorTableEntries which, RGBColorType *rgbP);

	GetParameter (&UIColorGetTableEntryRGBP , sizeof(void *), pUIColorGetTableEntryRGB );
	(*UIColorGetTableEntryRGBP)(which, rgbP);
}
#endif

#ifdef L_UIColorSetTableEntry
Err UIColorSetTableEntry(UIColorTableEntries which,const RGBColorType *rgbP)
{
	Err (*UIColorSetTableEntryP)(UIColorTableEntries which,const RGBColorType *rgbP);

	GetParameter (&UIColorSetTableEntryP , sizeof(void *), pUIColorSetTableEntry );
	return	(*UIColorSetTableEntryP)(which, rgbP);
}
#endif

*/
////////////////////////////////////////////////////////////
// UI Controls Library, completed 3/3 functions now.
////////////////////////////////////////////////////////////
#ifdef L_UIBrightnessAdjust
void UIBrightnessAdjust()
{
	void (*UIBrightnessAdjustP)();

	GetParameter (&UIBrightnessAdjustP , sizeof(void *), pUIBrightnessAdjust );
	(*UIBrightnessAdjustP)();
}
#endif

#ifdef L_UIContrastAdjust
void UIContrastAdjust()
{
	void (*UIContrastAdjustP)();

	GetParameter (&UIContrastAdjustP , sizeof(void *), pUIContrastAdjust );
	(*UIContrastAdjustP)();
}
#endif
 /*
#ifdef L_UIPickColor
Boolean UIPickColor (IndexedColorType *indexP,RGBColorType *rgbP, UIPickColorStartType start,const Char *titleP, const Char *tipP)
{
	Boolean (*UIPickColorP) (IndexedColorType *indexP,RGBColorType *rgbP, UIPickColorStartType start,const Char *titleP, const Char *tipP);

	GetParameter (&UIPickColorP , sizeof(void *), pUIPickColor );
	return	(*UIPickColorP) (indexP,rgbP,  start, titleP,  tipP);
}
#endif
 */

////////////////////////////////////////////////////////////
// User Interface Library, completed 4/4 functions now.
////////////////////////////////////////////////////////////
#ifdef L_PhoneNumberLookup
void PhoneNumberLookup (FieldType *fldP)
{     
	void (*PhoneNumberLookupP) (FieldType *fldP);

	GetParameter (&PhoneNumberLookupP , sizeof(void *), pPhoneNumberLookup );
	(*PhoneNumberLookupP) (fldP);
}
#endif

#ifdef L_ResLoadConstant
UInt32 ResLoadConstant (UInt16 rscID)
{     
	UInt32 (*ResLoadConstantP) (UInt16 rscID);

	GetParameter (&ResLoadConstantP , sizeof(void *), pResLoadConstant );
	return	(*ResLoadConstantP) (rscID);
}
#endif

#ifdef L_ResLoadForm
void* ResLoadForm (UInt16 rscID)
{     
	void* (*ResLoadFormP) (UInt16 rscID);

	GetParameter (&ResLoadFormP , sizeof(void *), pResLoadForm );
	return	(*ResLoadFormP) (rscID);
}
#endif

#ifdef L_ResLoadMenu
void* ResLoadMenu (UInt16 rscID)
{     
	void* (*ResLoadMenuP) (UInt16 rscID);

	GetParameter (&ResLoadMenuP , sizeof(void *), pResLoadMenu );
	return	(*ResLoadMenuP) (rscID);
}
#endif


////////////////////////////////////////////////////////////
// Virtual Driver-Defined Library, completed 6/6 functions now.
////////////////////////////////////////////////////////////
/*
#ifdef L_DrvEntryPoint
Err DrvEntryPoint(DrvrEntryOpCodeEnum opCode,void * uartData)
{
	Err (*DrvEntryPointP)(DrvrEntryOpCodeEnum opCode,void * uartData);

	GetParameter (&DrvEntryPointP , sizeof(void *), pDrvEntryPoint );
	return	(*DrvEntryPointP)(opCode, uartData);
}
#endif

#ifdef L_VdrvClose
Err VdrvClose(VdrvDataPtr drvrDataP)
{
	Err (*VdrvClosep)(VdrvDataPtr drvrDataP);

	GetParameter (&VdrvClosep , sizeof(void *), PVdrvClose );
	return	(*VdrvClosep)(drvrDataP);

}
#endif

#ifdef L_VdrvControl
Err *VdrvControl(VdrvDataPtr drvrDataP,VdrvCtlOpCodeEnum controlCode,void * controlDataP, UInt16 * controlDataLenP)
{
	Err * (*VdrvControlP)(VdrvDataPtr drvrDataP,VdrvCtlOpCodeEnum controlCode,void * controlDataP, UInt16 * controlDataLenP);

	GetParameter (&VdrvControlP , sizeof(void *), pVdrvControl );
	return	(*VdrvControlP)( drvrDataP, controlCode, controlDataP,  controlDataLenP);
}
#endif

#ifdef L_VdrvOpen
Err VdrvOpen(VdrvDataPtr* drvrDataP,UInt32 baudRate, DrvrHWRcvQPtr rcvQP)
{
	Err (*VdrvOpenP)(VdrvDataPtr* drvrDataP,UInt32 baudRate, DrvrHWRcvQPtr rcvQP);

	GetParameter (&VdrvOpenP , sizeof(void *), pVdrvOpen );
	return	(*VdrvOpenP)( drvrDataP, baudRate,  rcvQP);
}
#endif

#ifdef L_VdrvStatus
UInt16 VdrvStatus(VdrvDataPtr drvrDataP)
{
	UInt16 (*VdrvStatusP)(VdrvDataPtr drvrDataP);

	GetParameter (&VdrvStatusP , sizeof(void *), pVdrvStatus );
	return	(*VdrvStatusP)(drvrDataP);
}
#endif

#ifdef L_VdrvWrite
UInt32 VdrvWrite(VdrvDataPtr drvrDataP,void * bufP, UInt32 size, Err* errP)
{
	UInt32 (*VdrvWriteP)(VdrvDataPtr drvrDataP,void * bufP, UInt32 size, Err* errP);

	GetParameter (&VdrvWriteP , sizeof(void *), pVdrvWrite );
	return	(*VdrvWriteP)(drvrDataP, bufP,  size,  errP);
}
#endif

*/
////////////////////////////////////////////////////////////
// Window function, completed 80/80 functions now.
////////////////////////////////////////////////////////////
#ifdef L_WinClipRectangle
void WinClipRectangle (RectangleType *rP)
{     
	void (*WinClipRectangleP) (RectangleType *rP);

	GetParameter (&WinClipRectangleP , sizeof(void *), pWinClipRectangle );
	(*WinClipRectangleP) (rP);	
}
#endif

#ifdef L_WinCopyRectangle
void WinCopyRectangle (WinHandle srcWin,WinHandle dstWin, RectangleType *srcRect,Coord destX, Coord destY, WinDrawOperation mode)
{     
	void (*WinCopyRectangleP) (WinHandle srcWin,WinHandle dstWin, RectangleType *srcRect,Coord destX, Coord destY, WinDrawOperation mode);

	GetParameter (&WinCopyRectangleP , sizeof(void *), pWinCopyRectangle );
	(*WinCopyRectangleP) (srcWin, dstWin, srcRect, destX,  destY,  mode);
}
#endif

#ifdef L_WinCreateBitmapWindow
WinHandle WinCreateBitmapWindow(BitmapType *bitmapP, UInt16 *error)
{     
	WinHandle (*WinCreateBitmapWindowP)(BitmapType *bitmapP, UInt16 *error);

	GetParameter (&WinCreateBitmapWindowP , sizeof(void *), pWinCreateBitmapWindow );
	return	(*WinCreateBitmapWindowP)(bitmapP, error);	
}
#endif
   /*
#ifdef L_WinCreateOffscreenWindow
WinHandle WinCreateOffscreenWindow (Coord width,Coord height, WindowFormatType format,UInt16 *error)
{
	WinHandle (*WinCreateOffscreenWindowP) (Coord width,Coord height, WindowFormatType format,UInt16 *error);

	GetParameter (&WinCreateOffscreenWindowP , sizeof(void *), pWinCreateOffscreenWindow );
	return	(*WinCreateOffscreenWindowP) ( width, height,  format,error);
}
#endif
 */
#ifdef L_WinCreateWindow
WinHandle WinCreateWindow (RectangleType *bounds,FrameType frame, Boolean modal, Boolean focusable,UInt16 *error)
{
	WinHandle (*WinCreateWindowP) (RectangleType *bounds,FrameType frame, Boolean modal, Boolean focusable,UInt16 *error);

	GetParameter (&WinCreateWindowP , sizeof(void *), pWinCreateWindow );
	return	(*WinCreateWindowP) (bounds, frame,  modal,  focusable,error);
}
#endif

#ifdef L_WinDeleteWindow
void WinDeleteWindow (WinHandle winHandle,Boolean eraseIt)
{     
	void (*WinDeleteWindowP) (WinHandle winHandle,Boolean eraseIt);

	GetParameter (&WinDeleteWindowP , sizeof(void *), pWinDeleteWindow );
	(*WinDeleteWindowP) (winHandle, eraseIt);	
}
#endif

#ifdef L_WinDisplayToWindowPt
void WinDisplayToWindowPt (Coord *extentX,Coord *extentY)
{     
	void (*WinDisplayToWindowPtP) (Coord *extentX,Coord *extentY);

	GetParameter (&WinDisplayToWindowPtP , sizeof(void *), pWinDisplayToWindowPt );
	(*WinDisplayToWindowPtP) (extentX,extentY);
}
#endif



#ifdef L_WinDrawBitmap
void WinDrawBitmap (BitmapPtr bitmapP, Coord x, Coord y)
{     
	void (*WinDrawBitmapP) (BitmapPtr bitmapP, Coord x, Coord y);

	GetParameter (&WinDrawBitmapP , sizeof(void *), pWinDrawBitmap );
	(*WinDrawBitmapP) ( bitmapP,  x,  y);
}
#endif

#ifdef L_WinDrawChar
void WinDrawChar (WChar theChar, Coord x, Coord y)
{
	void (*WinDrawCharP) (WChar theChar, Coord x, Coord y);

	GetParameter (&WinDrawCharP , sizeof(void *), pWinDrawChar );
	(*WinDrawCharP) (theChar,  x,  y);
}
#endif

#ifdef L_WinDrawChars
void WinDrawChars (const Char *chars, Int16 len, Coord x, Coord y)
{     
	void (*WinDrawCharsP) (const Char *chars, Int16 len, Coord x, Coord y);

	GetParameter (&WinDrawCharsP , sizeof(void *), pWinDrawChars );
	(*WinDrawCharsP) (chars,  len,  x,  y);
}
#endif

#ifdef L_WinDrawGrayLine
void WinDrawGrayLine (Coord x1, Coord y1, Coord x2, Coord y2)
{     
	void (*WinDrawGrayLineP) (Coord x1, Coord y1, Coord x2, Coord y2);

	GetParameter (&WinDrawGrayLineP , sizeof(void *), pWinDrawGrayLine );
	(*WinDrawGrayLineP) ( x1,  y1,  x2,  y2);
}
#endif

#ifdef L_WinDrawGrayRectangleFrame
void WinDrawGrayRectangleFrame (FrameType frame, RectangleType *rP)
{     
	void (*WinDrawGrayRectangleFrameP) (FrameType frame, RectangleType *rP);
	
	GetParameter (&WinDrawGrayRectangleFrameP , sizeof(void *), pWinDrawGrayRectangleFrame );
	(*WinDrawGrayRectangleFrameP) ( frame, rP);
}
#endif

#ifdef L_WinDrawInvertedChars
void WinDrawInvertedChars (const Char *chars, Int16 len, Coord x, Coord y)
{     
	void (*WinDrawInvertedCharsP) (const Char *chars, Int16 len, Coord x, Coord y)	;

	GetParameter (&WinDrawInvertedCharsP , sizeof(void *), pWinDrawInvertedChars );
	(*WinDrawInvertedCharsP) (chars,  len,  x,  y)	;
}
#endif

#ifdef L_WinDrawLine
void WinDrawLine (Coord x1, Coord y1, Coord x2, Coord y2)
{     
	void (*WinDrawLineP) (Coord x1, Coord y1, Coord x2, Coord y2);

	GetParameter (&WinDrawLineP , sizeof(void *), pWinDrawLine );
	(*WinDrawLineP) ( x1,  y1,  x2,  y2);
}
#endif

#ifdef L_WinDrawPixel
void WinDrawPixel (Coord x, Coord y)
{     
	void (*WinDrawPixelP) (Coord x, Coord y);

	GetParameter (&WinDrawPixelP , sizeof(void *), pWinDrawPixel );
	(*WinDrawPixelP) ( x,  y);
}
#endif

#ifdef L_WinDrawRectangle
void WinDrawRectangle (RectangleType *rP, UInt16 cornerDiam)
{     
	void (*WinDrawRectangleP) (RectangleType *rP, UInt16 cornerDiam);

	GetParameter (&WinDrawRectangleP , sizeof(void *), pWinDrawRectangle );
	(*WinDrawRectangleP) (rP, cornerDiam);
}
#endif

#ifdef L_WinDrawRectangleFrame
void WinDrawRectangleFrame (FrameType frame, RectangleType *rP)
{     
	void (*WinDrawRectangleFrameP) (FrameType frame, RectangleType *rP);

	GetParameter (&WinDrawRectangleFrameP , sizeof(void *), pWinDrawRectangleFrame );
	(*WinDrawRectangleFrameP) ( frame, rP);
}
#endif

#ifdef L_WinDrawTruncChars
void WinDrawTruncChars (const Char *chars, Int16 len, Coord x, Coord y, Coord maxWidth)
{     	
	void (*WinDrawTruncCharsP) (const Char *chars, Int16 len, Coord x, Coord y, Coord maxWidth);

	GetParameter (&WinDrawTruncCharsP , sizeof(void *), pWinDrawTruncChars );
	(*WinDrawTruncCharsP) (chars,  len,  x,  y,  maxWidth);
}
#endif

#ifdef L_WinEraseChars
void WinEraseChars (const Char *chars, Int16 len, Coord x, Coord y)
{     
	void (*WinEraseCharsP) (const Char *chars, Int16 len, Coord x, Coord y);

	GetParameter (&WinEraseCharsP , sizeof(void *), pWinEraseChars );
	(*WinEraseCharsP) (chars,  len,  x,  y);
}
#endif

#ifdef L_WinEraseLine
void WinEraseLine (Coord x1, Coord y1, Coord x2, Coord y2)
{     
	void (*WinEraseLineP) (Coord x1, Coord y1, Coord x2, Coord y2);

	GetParameter (&WinEraseLineP , sizeof(void *), pWinEraseLine );
	(*WinEraseLineP) ( x1,  y1, x2,  y2);
}
#endif

#ifdef L_WinErasePixel
void WinErasePixel (Coord x, Coord y)
{     
	void (*WinErasePixelP) (Coord x, Coord y);

	GetParameter (&WinErasePixelP , sizeof(void *), pWinErasePixel );
	(*WinErasePixelP) ( x,  y);
}
#endif

#ifdef L_WinEraseRectangle
void WinEraseRectangle (RectangleType *rP, UInt16 cornerDiam)
{     
	void (*WinEraseRectangleP) (RectangleType *rP, UInt16 cornerDiam);

	GetParameter (&WinEraseRectangleP , sizeof(void *), pWinEraseRectangle );
	(*WinEraseRectangleP) (rP,  cornerDiam);
}
#endif

#ifdef L_WinEraseWindow
void WinEraseWindow (void)
{     
	void (*WinEraseWindowP) (void);

	GetParameter (&WinEraseWindowP , sizeof(void *), pWinEraseWindow );
	(*WinEraseWindowP) ();
}
#endif

#ifdef L_WinFillLine
void WinFillLine (Coord x1, Coord y1, Coord x2, Coord y2)
{     
	void (*WinFillLineP) (Coord x1, Coord y1, Coord x2, Coord y2);

	GetParameter (&WinFillLineP , sizeof(void *), pWinFillLine );
	(*WinFillLineP) ( x1,  y1,  x2,  y2);
}
#endif

#ifdef L_WinFillRectangle
void WinFillRectangle (RectangleType *rP, UInt16 cornerDiam)
{     
	void (*WinFillRectangleP) (RectangleType *rP, UInt16 cornerDiam);

	GetParameter (&WinFillRectangleP , sizeof(void *), pWinFillRectangle );
	(*WinFillRectangleP) (rP,  cornerDiam);
}
#endif

#ifdef L_WinGetActiveWindow
WinHandle WinGetActiveWindow (void)
{     
	WinHandle (*WinGetActiveWindowP) (void);

	GetParameter (&WinGetActiveWindowP , sizeof(void *), pWinGetActiveWindow );
	return	(*WinGetActiveWindowP) ();
}
#endif

#ifdef L_WinGetBitmap
BitmapType *WinGetBitmap (WinHandle winHandle)
{     
	BitmapType*  (*WinGetBitmapP) (WinHandle winHandle);

	GetParameter (&WinGetBitmapP , sizeof(void *), pWinGetBitmap );
	return	(*WinGetBitmapP) (winHandle);
}
#endif





#ifdef L_WinGetClip
void WinGetClip (RectangleType *rP)
{     
	void (*WinGetClipP) (RectangleType *rP);
 
	GetParameter (&WinGetClipP , sizeof(void *), pWinGetClip );
	(*WinGetClipP) (rP);
}
#endif


#ifdef L_WinGetDisplayExtent
void WinGetDisplayExtent (Coord *extentX,Coord *extentY)
{     
	void (*WinGetDisplayExtentP) (Coord *extentX,Coord *extentY);

	GetParameter (&WinGetDisplayExtentP , sizeof(void *), pWinGetDisplayExtent );
	(*WinGetDisplayExtentP) (extentX,extentY);	
}
#endif

#ifdef L_WinGetDisplayWindow
WinHandle WinGetDisplayWindow (void)
{     
	WinHandle (*WinGetDisplayWindowP) (void);

	GetParameter (&WinGetDisplayWindowP , sizeof(void *), pWinGetDisplayWindow );
	return	(*WinGetDisplayWindowP) ();
}
#endif

#ifdef L_WinGetDrawWindow
WinHandle WinGetDrawWindow (void)
{     
	WinHandle (*WinGetDrawWindowP) (void);

	GetParameter (&WinGetDrawWindowP , sizeof(void *), pWinGetDrawWindow );
	return	(*WinGetDrawWindowP) ();
}
#endif

#ifdef L_WinGetFirstWindow
WinHandle WinGetFirstWindow (void)
{     
	WinHandle (*WinGetFirstWindowP) (void);

	GetParameter (&WinGetFirstWindow , sizeof(void *), pWinGetFirstWindow );
	return	(*WinGetFirstWindowP) ();
}
#endif

#ifdef L_WinGetFramesRectangle
void WinGetFramesRectangle (FrameType frame,RectangleType *rP, RectangleType *obscuredRectP)
{     
	void (*WinGetFramesRectangleP) (FrameType frame,RectangleType *rP, RectangleType *obscuredRectP);

	GetParameter (&WinGetFramesRectangleP , sizeof(void *), pWinGetFramesRectangle );
	(*WinGetFramesRectangleP) ( frame,rP, obscuredRectP);
}
#endif

#ifdef L_WinGetPattern
void WinGetPattern (CustomPatternType *patternP)
{     
	void (*WinGetPatternP) (CustomPatternType *patternP);

	GetParameter (&WinGetPatternP , sizeof(void *), pWinGetPattern );
	(*WinGetPatternP) (patternP);	
}
#endif

#ifdef L_WinGetPatternType
PatternType WinGetPatternType (void)
{     
	PatternType (*WinGetPatternTypeP) (void);

	GetParameter (&WinGetPatternTypeP , sizeof(void *), pWinGetPatternType );
	return	(*WinGetPatternTypeP) ();
}
#endif




#ifdef L_WinGetPixel
IndexedColorType WinGetPixel (Coord x, Coord y)
{     
	IndexedColorType (*WinGetPixelP) (Coord x, Coord y);

	GetParameter (&WinGetPixelP , sizeof(void *), pWinGetPixel );
	return(*WinGetPixelP) ( x,  y);
}
#endif


#ifdef L_WinGetWindowBounds
void WinGetWindowBounds (RectangleType *rP)
{     
	void (*WinGetWindowBoundsP) (RectangleType *rP);

	GetParameter (&WinGetWindowBoundsP , sizeof(void *), pWinGetWindowBounds );
	(*WinGetWindowBoundsP) (rP);	
}
#endif

#ifdef L_WinGetWindowExtent
void WinGetWindowExtent (Coord *extentX,Coord *extentY)
{     
	void (*WinGetWindowExtentP) (Coord *extentX,Coord *extentY);

	GetParameter (&WinGetWindowExtentP , sizeof(void *), pWinGetWindowExtent );
	(*WinGetWindowExtentP) (extentX,extentY);
}
#endif

#ifdef L_WinGetWindowFrameRect
void WinGetWindowFrameRect (WinHandle winHandle,RectangleType *r)
{     
	void (*WinGetWindowFrameRectP) (WinHandle winHandle,RectangleType *r);

	GetParameter (&WinGetWindowFrameRectP , sizeof(void *), pWinGetWindowFrameRect );
	(*WinGetWindowFrameRectP) (winHandle,r);
}
#endif
      /*
#ifdef L_WinIndexToRGB
void WinIndexToRGB (IndexedColorType i,RGBColorType *rgbP)
{
	void (*WinIndexToRGBP) (IndexedColorType i,RGBColorType *rgbP);

	GetParameter (&WinIndexToRGBP , sizeof(void *), pWinIndexToRGB );
	(*WinIndexToRGBP) ( i,rgbP);
}
#endif
      */
#ifdef L_WinInvertChars
void WinInvertChars (const Char *chars, Int16 len,Coord x, Coord y)
{
	void (*WinInvertCharsP) (const Char *chars, Int16 len,Coord x, Coord y);

	GetParameter (&WinInvertCharsP , sizeof(void *), pWinInvertChars );
	(*WinInvertCharsP) (chars,  len, x,  y);
}
#endif

#ifdef L_WinInvertLine
void WinInvertLine (Coord x1, Coord y1, Coord x2,Coord y2)
{
	void (*WinInvertLineP) (Coord x1, Coord y1, Coord x2,Coord y2);

	GetParameter (&WinInvertLineP , sizeof(void *), pWinInvertLine );
	(*WinInvertLineP) ( x1,  y1,  x2, y2);
}
#endif





#ifdef L_WinInvertPixel
void WinInvertPixel (Coord x, Coord y)
{
	void (*WinInvertPixelP) (Coord x, Coord y);

	GetParameter (&WinInvertPixelP , sizeof(void *), pWinInvertPixel );
	(*WinInvertPixelP) ( x,  y);
}
#endif

#ifdef L_WinInvertRectangle
void WinInvertRectangle (RectangleType *rP, UInt16 cornerDim)
{
	void (*WinInvertRectangleP) (RectangleType *rP, UInt16 cornerDim);

	GetParameter (&WinInvertRectangleP , sizeof(void *), pWinInvertRectangle );
	(*WinInvertRectangleP) (rP, cornerDim);
}
#endif


#ifdef L_WinInvertRectangleFrame
void WinInvertRectangleFrame (FrameType frame,RectangleType *rP)
{     
	void (*WinInvertRectangleFrameP) (FrameType frame,RectangleType *rP);

	GetParameter (&WinInvertRectangleFrameP , sizeof(void *), pWinInvertRectangleFrame );
	(*WinInvertRectangleFrameP) ( frame,rP);	
}
#endif

#ifdef L_WinModal
Boolean WinModal (WinHandle winHandle)
{     
	Boolean (*WinModalP) (WinHandle winHandle);

	GetParameter (&WinModalP , sizeof(void *), pWinModal );
	return	(*WinModalP) (winHandle);
}
#endif

#ifdef L_WinPaintBitmap
void WinPaintBitmap (BitmapType *bitmapP, Coord x,Coord y)
{     
	void (*WinPaintBitmapP) (BitmapType *bitmapP, Coord x,Coord y);

	GetParameter (&WinPaintBitmapP , sizeof(void *), pWinPaintBitmap );
	(*WinPaintBitmapP) (bitmapP,  x, y);	
}
#endif

#ifdef L_WinPaintChar
void WinPaintChar (WChar theChar, Coord x,Coord y)
{     
	void (*WinPaintCharP) (WChar theChar, Coord x,Coord y);

	GetParameter (&WinPaintCharP , sizeof(void *), pWinPaintChar );
	(*WinPaintCharP) ( theChar,  x, y);	
}
#endif

#ifdef L_WinPaintChars
void WinPaintChars (const Char *chars, Int16 len,Coord x, Coord y)
{     
	void (*WinPaintCharsP) (const Char *chars, Int16 len,Coord x, Coord y);

	GetParameter (&WinPaintCharsP , sizeof(void *), pWinPaintChars );
	(*WinPaintCharsP) (chars,  len, x,  y);
}
#endif

#ifdef L_WinPaintLine
void WinPaintLine (Coord x1, Coord y1, Coord x2,Coord y2)
{     
	void (*WinPaintLineP) (Coord x1, Coord y1, Coord x2,Coord y2);

	GetParameter (&WinPaintLineP , sizeof(void *), pWinPaintLine );
	(*WinPaintLineP) ( x1,  y1,  x2, y2);
}
#endif
 /*
#ifdef L_WinPaintLines
void WinPaintLines (UInt16 numLines,WinLineType lines[])
{
	void (*WinPaintLinesP) (UInt16 numLines,WinLineType lines[]);

	GetParameter (&WinPaintLinesP , sizeof(void *), pWinPaintLines );
	(*WinPaintLinesP) ( numLines, lines[]);
}
#endif

*/


#ifdef L_WinPaintPixel
void WinPaintPixel (Coord x, Coord y)
{
	void (*WinPaintPixelP) (Coord x, Coord y);

	GetParameter (&WinPaintPixelP , sizeof(void *), pWinPaintPixel );
	(*WinPaintPixelP) ( x,  y);
}
#endif

#ifdef L_WinPaintPixels
void WinPaintPixels (UInt16 numPoints, PointType pts[])
{     
	void (*WinPaintPixelsP) (UInt16 numPoints, PointType pts[]);

	GetParameter (&WinPaintPixelsP , sizeof(void *), pWinPaintPixels );
	(*WinPaintPixelsP) ( numPoints, pts);
}
#endif

#ifdef L_WinPaintRectangle
void WinPaintRectangle (RectangleType *rP, UInt16 cornerDiam)
{     
	void (*WinPaintRectangleP) (RectangleType *rP, UInt16 cornerDiam);

	GetParameter (&WinPaintRectangleP , sizeof(void *), pWinPaintRectangle );
	(*WinPaintRectangleP) (rP,  cornerDiam);
}
#endif


#ifdef L_WinPaintRectangleFrame
void WinPaintRectangleFrame (FrameType frame,RectangleType *rP)
{     
	void (*WinPaintRectangleFrameP) (FrameType frame,RectangleType *rP);

	GetParameter (&WinPaintRectangleFrameP , sizeof(void *), pWinPaintRectangleFrame );
	(*WinPaintRectangleFrameP) (frame,rP);	
}
#endif
/*
#ifdef L_WinPalette
Err WinPalette (UInt8 operation, Int16 startIndex,UInt16 paletteEntries, RGBColorType *tableP)
{
	Err (*WinPaletteP) (UInt8 operation, Int16 startIndex,UInt16 paletteEntries, RGBColorType *tableP);

	GetParameter (&WinPaletteP , sizeof(void *), pWinPalette );
	return	 (*WinPaletteP) (operation,  startIndex, paletteEntries, tableP);
}
#endif

*/

#ifdef L_WinPopDrawState
void WinPopDrawState ()
{
	void (*WinPopDrawStateP) ();

	GetParameter (&WinPopDrawStateP , sizeof(void *), pWinPopDrawState );
	(*WinPopDrawStateP) ();
}
#endif

#ifdef L_WinPushDrawState
void WinPushDrawState ()
{
	void (*WinPushDrawStateP) ();

	GetParameter (&WinPushDrawStateP , sizeof(void *), pWinPushDrawState );
	(*WinPushDrawStateP) ();
}
#endif

#ifdef L_WinResetClip
void WinResetClip(void)
{
	void (*WinResetClipP)(void);

	GetParameter (&WinResetClipP , sizeof(void *), pWinResetClip );
	(*WinResetClipP)();
}
#endif

#ifdef L_WinRestoreBits
void WinRestoreBits (WinHandle winHandle,Coord destX, Coord destY)
{
	void (*WinRestoreBitsP) (WinHandle winHandle,Coord destX, Coord destY);

	GetParameter (&WinRestoreBitsP , sizeof(void *), pWinRestoreBits );
	(*WinRestoreBitsP) (winHandle, destX,  destY);
}
#endif
/*
#ifdef L_WinRGBToIndex
IndexedColorType WinRGBToIndex(const RGBColorType *rgbP)
{
	IndexedColorType (*WinRGBToIndexP)(const RGBColorType *rgbP);

	GetParameter (&WinRGBToIndexP , sizeof(void *), pWinRGBToIndex );
	return	(*WinRGBToIndexP)( rgbP);
}
#endif
*/
#ifdef L_WinSaveBits
WinHandle WinSaveBits (RectangleType *sourceP,UInt16 *error)
{
	WinHandle (*WinSaveBitsP) (RectangleType *sourceP,UInt16 *error);

	GetParameter (&WinSaveBitsP , sizeof(void *), pWinSaveBits );
	return	(*WinSaveBitsP) (sourceP,error);
}
#endif
/*
#ifdef L_WinScreenLock
UInt8* WinScreenLock (WinLockInitType initMode)
{
	UInt8* (*WinScreenLockP) (WinLockInitType initMode);

	GetParameter (&WinScreenLockP , sizeof(void *), pWinScreenLock );
	return	(*WinScreenLockP) (initMode);
}
#endif

#ifdef L_WinScreenMode
Err WinScreenMode(WinScreenModeOperation operation, UInt32 *widthP,UInt32 *heightP, UInt32 *depthP,Boolean *enableColorP)
{
	Err (*WinScreenModeP)(WinScreenModeOperation operation, UInt32 *widthP,UInt32 *heightP, UInt32 *depthP,Boolean *enableColorP);

	GetParameter (&WinScreenModeP , sizeof(void *), pWinScreenMode );
	return	(*WinScreenModeP)( operation, widthP,heightP, depthP,enableColorP);
}
#endif
*/
#ifdef L_WinScreenUnlock
void WinScreenUnlock (void)
{
	void (*WinScreenUnlockP) (void);

	GetParameter (&WinScreenUnlockP , sizeof(void *), pWinScreenUnlock );
	(*WinScreenUnlockP) ();
}
#endif

#ifdef L_WinScrollRectangle
void WinScrollRectangle (RectangleType *rP,WinDirectionType direction, Coord distance,RectangleType *vacatedP)
{
	void (*WinScrollRectangleP) (RectangleType *rP,WinDirectionType direction, Coord distance,RectangleType *vacatedP);

	GetParameter (&WinScrollRectangleP , sizeof(void *), pWinScrollRectangle );
	(*WinScrollRectangleP) (rP, direction,  distance,vacatedP);
}
#endif

#ifdef L_WinSetActiveWindow
void WinSetActiveWindow (WinHandle winHandle)
{     
	void (*WinSetActiveWindowP) (WinHandle winHandle);

	GetParameter (&WinSetActiveWindowP , sizeof(void *), pWinSetActiveWindow );
	return	(*WinSetActiveWindowP) (winHandle);
}
#endif




#ifdef L_WinSetBackColor
IndexedColorType WinSetBackColor (IndexedColorType backColor)
{     
	IndexedColorType (*WinSetBackColorP) (IndexedColorType backColor);

	GetParameter (&WinSetBackColorP , sizeof(void *), pWinSetBackColor );
	return (*WinSetBackColorP) (backColor);
}
#endif

#ifdef L_WinSetClip
void WinSetClip (RectangleType *rP)
{     
	void (*WinSetClipP) (RectangleType *rP);
 
	GetParameter (&WinSetClipP , sizeof(void *), pWinSetClip );
	(*WinSetClipP) (rP);
}
#endif

#ifdef L_WinSetDrawMode
WinDrawOperation WinSetDrawMode(WinDrawOperation newMode)
{     
	WinDrawOperation (*WinSetDrawModeP)(WinDrawOperation newMode);

	GetParameter (&WinSetDrawModeP , sizeof(void *), pWinSetDrawMode );
	return	(*WinSetDrawModeP)(newMode);
}
#endif

#ifdef L_WinSetDrawWindow
WinHandle WinSetDrawWindow (WinHandle winHandle)
{     
	WinHandle (*WinSetDrawWindowP) (WinHandle winHandle);

	GetParameter (&WinSetDrawWindowP , sizeof(void *), pWinSetDrawWindow );
	return	(*WinSetDrawWindowP) (winHandle);
}
#endif



#ifdef L_WinSetForeColor
IndexedColorType WinSetForeColor (IndexedColorType foreColor)
{     
	IndexedColorType (*WinSetForeColorP) (IndexedColorType foreColor);

	GetParameter (&WinSetForeColorP , sizeof(void *), pWinSetForeColor );
	return (*WinSetForeColorP) (foreColor);
}
#endif



#ifdef L_WinSetPattern
void WinSetPattern (const CustomPatternType*patternP)
{     
	void (*WinSetPatternP) (const CustomPatternType*patternP);

	GetParameter (&WinSetPatternP , sizeof(void *), pWinSetPattern );
	(*WinSetPatternP) ( patternP);
}
#endif

#ifdef L_WinSetPatternType
void WinSetPatternType (PatternType newPattern)
{
	void (*WinSetPatternTypeP) (PatternType newPattern);

	GetParameter (&WinSetPatternTypeP , sizeof(void *), pWinSetPatternType );
	(*WinSetPatternTypeP) (newPattern);
}
#endif

#ifdef L_WinSetTextColor
IndexedColorType WinSetTextColor(IndexedColorType textColor)
{
	IndexedColorType (*WinSetTextColorP)(IndexedColorType textColor);

	GetParameter (&WinSetTextColorP , sizeof(void *), pWinSetTextColor );
	return	(*WinSetTextColorP)(textColor);
}
#endif

#ifdef L_WinSetUnderlineMode
UnderlineModeType WinSetUnderlineMode(UnderlineModeType mode)
{
	UnderlineModeType (*WinSetUnderlineModeP)(UnderlineModeType mode);

	GetParameter (&WinSetUnderlineModeP , sizeof(void *), pWinSetUnderlineMode );
	return	(*WinSetUnderlineModeP)(mode);
}
#endif

#ifdef L_WinSetWindowBounds
void WinSetWindowBounds (WinHandle winHandle,RectangleType *rP)
{
	void (*WinSetWindowBoundsP) (WinHandle winHandle,RectangleType *rP);

	GetParameter (&WinSetWindowBoundsP , sizeof(void *), pWinSetWindowBounds );
	(*WinSetWindowBoundsP) (winHandle,rP);
}
#endif

#ifdef L_WinValidateHandle
Boolean WinValidateHandle (WinHandle winHandle)
{
	Boolean (*WinValidateHandleP) (WinHandle winHandle);

	GetParameter (&WinValidateHandleP , sizeof(void *), pWinValidateHandle );
	return	(*WinValidateHandleP) (winHandle);
}
#endif

#ifdef L_WinWindowToDisplayPt
void WinWindowToDisplayPt (Coord *extentX,Coord *extentY)
{
	void (*WinWindowToDisplayPtP) (Coord *extentX,Coord *extentY);

	GetParameter (&WinWindowToDisplayPtP , sizeof(void *), pWinWindowToDisplayPt );
	(*WinWindowToDisplayPtP) (extentX,extentY);
}
#endif


