 /**********************************************************
 * Company     : Wiscore Inc                               * 
 *                                                         *  
 * Filename    : Date.c                                    *
 *                                                         * 
 * Description : Calendar AP		                   *	
 *		 				      	   *	
 * History     : 2001/10/24  by Vincent Chen	           *	
 *********************************************************/ 

//#pragma pack( 2 )

#include 	<Common.h>
//#include 	<System/SysAll.h>
//#include 	<UI/UIAll.h>

#include "date.h"
#include "dateRsc.h"
//----------------------------------------------
#define MonthCellStartX					1
#define MonthCellStartY					50
#define MonthCellWidth					120
#define MonthCellHeight		         90

#define daysInWeek				      7
#define maxWeeksInMonth					6

#define UpperLimitedYear            2099
#define LowerLimitedYear            1904
//----------------------------------------------

Word	currentYear, currentMonth, currentDay;
Char	*dayLabels[] = { "S", "M", "T", "W", "T", "F", "S" };
char	*monthLabel[] ={ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

//----------------------------------------------
Boolean DateViewForm1000HandleEvent(EventPtr  event);
//----------------------------------------------
//-----------------------------------------------

int StartApplication(void)
{

	Word				mode=dmModeReadWrite;
	DateTimeType	today;

	TimSecondsToDateTime(TimGetSeconds(), &today);
	currentYear = today.year;
	currentMonth = today.month;
	currentDay = today.day;
       
	FrmGotoForm(DateViewForm1000);
  
	return(0);
}


//-----------------------------------------------------

void EventLoop(void)
{
	short		err;
	Word		formID;
	FormPtr	        form;
	EventType       event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (SysHandleEvent(&event)) continue;
		if (MenuHandleEvent((void *)0, &event, &err)) continue;

		if (event.eType == frmLoadEvent) {
			formID = (Word) event.data.frmLoad.formID;
			form = FrmInitForm(formID);

			switch (formID) {  
				case    DateViewForm1000:
					FrmSetEventHandler(form, (FormEventHandlerPtr) DateViewForm1000HandleEvent);
					break;  

				
			}

			FrmSetActiveForm( form );
		} 

		FrmDispatchEvent(&event);
	} while(event.eType != appStopEvent);

}


//----------------------------------------------

void StopApplication(void)
{
	FrmCloseAllForms ();
	
}

//----------------------------------------------

Boolean   DateViewForm1000HandleEvent(EventPtr  event)
{ 
  	FormPtr		form=FrmGetActiveForm();
	ListPtr		list=FrmGetObjectPtr(form,FrmGetObjectIndex(form,MonthList1007));
	FieldPtr		field=FrmGetObjectPtr(form,FrmGetObjectIndex(form,YearField1011)); 
	SWord			selectedMonth;
	Word			year;
	Char			buffer[9];  
	Boolean		handled=false;
 
	if  ( event->eType == frmOpenEvent ) {    
		VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear));
		//CtlSetLabel(monthTrigger,monthLabel[currentMonth-1]);
		LstSetSelection(list,currentMonth-1);
		FrmDrawForm(form);
		DrawMonth (currentYear, currentMonth);  
		MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
		handled=true;
	} else  if ( event->eType == lstSelectEvent ) {            // use list UI
		selectedMonth=LstGetSelection(list);	
		currentMonth=selectedMonth+1; 
		DrawMonth (currentYear, currentMonth);	 
		MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
		FldReleaseFocus(field);
		handled=true;
	} else  if ( event->eType == ctlSelectEvent ) {
		switch (event->data.ctlSelect.controlID) {
       	case OKBtn1012:
        		year=GetYear(form,field);
        		if(year <= UpperLimitedYear && year >= LowerLimitedYear) {
					currentYear = year;
        			VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear)); 	 
        			DrawMonth (currentYear, currentMonth);
        			MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
				} else {
        			FrmAlert(IllegalAlert1100);
        		}     
        		FldFreeMemory(field);
        		FldDrawField(field);
        		FldGrabFocus(field);
				handled=true;               
				break;
 		}
	} else  if ( event->eType ==  ctlRepeatEvent) {    
		FldReleaseFocus(field);
		switch (event->data.ctlRepeat.controlID) {
			case LeftRepeatButton1002:
				currentYear--;
				if(currentYear < LowerLimitedYear)
					currentYear=LowerLimitedYear;
				VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear));
				DrawMonth (currentYear, currentMonth);
				MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
				handled = 0;
				break;

			case RightRepeatButton1003:
				currentYear++;
				if(currentYear > UpperLimitedYear)
					currentYear= UpperLimitedYear;
				VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear));
				DrawMonth (currentYear, currentMonth);
				MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
				handled = 0;
				break;

			case YearLeftRepeatButton1004:
				currentYear -= 10;
				if(currentYear < LowerLimitedYear)
					currentYear=LowerLimitedYear;
				VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear));
				DrawMonth (currentYear, currentMonth);
				MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
				handled = 0;
				break;

			case YearRightRepeatButton1005:
				currentYear +=10;
				if(currentYear > UpperLimitedYear)
					currentYear= UpperLimitedYear;
				VCPCtlSetLabel (YearLabel1001, StrIToA (buffer, currentYear));
				DrawMonth (currentYear, currentMonth);
				MonthDrawTodayInversionCell (currentYear, currentMonth, currentDay);
				handled = 0;
				break;

			default:
				break;
		}
				           
	}
	     
	return(handled);
}	

//--------------------------------------------------

void DrawMonth (int year, int month)
{
	SWord		i;
	SWord		cellWidth, cellHeight;
	SWord		dow, firstday, lastday;
	SWord		drawX, drawY;
	Char		dayInAscii[3];
	RectangleType	eraseRect;
	
	// Erase the rectangle of month,
	RctSetRectangle (&eraseRect, MonthCellStartX, MonthCellStartY, 
							MonthCellWidth, MonthCellHeight);
	WinEraseRectangle (&eraseRect, 0);

	// initial the width and height of day cell
	cellWidth = MonthCellWidth/daysInWeek;
	cellHeight = MonthCellHeight/maxWeeksInMonth;

	// draw week label
	drawX = 8;
	drawY = 40;
	for ( i = 0; i < daysInWeek; i++ ) {
		WinDrawChars (dayLabels[i], StrLen(dayLabels[i]), drawX, drawY);
		drawX += cellWidth;
	}

	// calculate the weekDay of the first day of current month
	firstday = DayOfWeek (month, 1, year);
	lastday = DaysInMonth (month, year);

	dow = firstday;
	drawY = MonthCellStartY+4;
	drawX = MonthCellStartX + 7 + (dow * cellWidth);
	for ( i = 1; i <= lastday; i++, dow++ ) {
		if (dow == daysInWeek) {
			drawX = MonthCellStartX + 7;
			drawY += cellHeight;
			dow = 0;
		}
		StrIToA (dayInAscii, i);
		WinDrawChars (dayInAscii, 
						  (i < 10) ? 1 : 2, 
						  drawX,
						  drawY);
		drawX += cellWidth;
	}
}




//----------------------------------------------

void VCPCtlSetLabel(Word id, char *s)
{
	FormPtr form;

	form=FrmGetActiveForm();
	FrmHideObject( form, FrmGetObjectIndex( form, id ) );
	FrmCopyLabel( form, id, s );
	FrmShowObject( form, FrmGetObjectIndex( form, id ) );
}


void MonthDrawTodayInversionCell (SWord year, SWord month, SWord day)
{
	RectangleType	rect;
	SWord		cellWidth, cellHeight;
	SWord           firstDay;
	DateTimeType     today;
	
	TimSecondsToDateTime(TimGetSeconds(), &today);    
	if((currentYear == today.year)&&(currentMonth == today.month)) {	
		firstDay= DayOfWeek(month,1,year);
		cellWidth = MonthCellWidth/daysInWeek;
		cellHeight = MonthCellHeight/maxWeeksInMonth;   
   	rect.topLeft.x = MonthCellStartX + ((day+firstDay-1)%daysInWeek)*cellWidth+4 ;
		rect.topLeft.y = MonthCellStartY + ((day+firstDay-1)/daysInWeek)*cellHeight+4 ;
		rect.extent.x = cellWidth-3;
		rect.extent.y = cellHeight-3;
          
		WinInvertRectangle (&rect, 4);
	} 
}

int  GetYear(FormPtr form,FieldPtr field)
{
	char*       yearTextP;
	Word       year;	
     
	yearTextP=FldGetTextPtr(field);
	FldReleaseFocus(field);
	if(yearTextP!=NULL) {  
		year=(Word)StrAToI(yearTextP);
		if( year > UpperLimitedYear || year < LowerLimitedYear)
			return (0);  
		return (year);
	}  

	return	0;
}


DWord PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags)
{
	int   error;
	
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		error = StartApplication();	
		if (error) return error;
		EventLoop();	
		StopApplication ();	
	}

	return 0;
}

