/*========================================================
  Time.c
  all routine is running with Platform non-related,
  simulated the Time function in Palm OS.

  All is Palm related function.
  Completed 15 of 17 Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0510, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VParser.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#ifdef LINUX
	#define	SYSSTARTYEAR	1970
#else
	#define	SYSSTARTYEAR	1904
#endif

UInt8	daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
Char *cMonth[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
						 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

UInt8 timeZoneHour[24] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 
									12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

void DateDaysToDate (UInt32 days, DatePtr Date);
UInt32 DateToDays (DateType date);
UInt32 TimDateTimeToSeconds (DateTimePtr dateTimeP);
void TimSecondsToDateTime (UInt32 seconds, DateTimePtr dateTimeP);

UInt32	alarmTime=0;
AlmAlarmProcPtr	alarmProc=NULL;
UInt8		timeZoneDiff = TaipeiZone;
UInt32	sysSecondsAfterReset=0;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    AlmGetAlarm
//
// DESCRIPTION: This routine return the date and time for the application's
//					 alarm, if one is set.
//
// PARAMETERS:  (UInt16) cardNo - Number of the storage card on which
//										the application resides.
//					 (LocalID) dbID - Local ID of the application.
//					 (UInt32 *) refP - The alarm's reference value is returned
//										here.
//
// RETURNED:    Returns the date and time the alarm will trigger, given
//					 in second since 1/1/1904; if no alarm is active for the
//					 application, 0 i returned for the alarm seconds.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 AlmGetAlarm (UInt16 cardNo, LocalID dbID, UInt32 *refP)
{
	return	alarmTime;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    AlmGetProcAlarm
//
// DESCRIPTION: This routine return the date and time that a procedure
//					 alarm will trigger. Also returns the caller-defined
//					 alarm reference value.
//
// PARAMETERS:  (AlmAlarmProcPtr) proc - Pointer to a function that should
//										be called when alarm is triggered.
//					 (UInt32) refP - The alarm's reference value is returned
//										here.
//
// RETURNED:    Returns the date and time the alarm will trigger, given
//					 in second since 1/1/1904; if no alarm is active for the
//					 application, 0 i returned for the alarm seconds.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 AlmGetProcAlarm (AlmAlarmProcPtr procP, UInt32 refP)
{
	return	alarmTime;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    AlmSetAlarm
//
// DESCRIPTION: This routine set or cancel an alarm for the given 
//					 application.
//
// PARAMETERS:  (UInt16) cardNo - Number of the storage card on which
//										the application resides.
//					 (LocalID) dbID - Local ID of the application.
//					 (UInt32) refP - Caller-defined value. The value is 
//										passed with the launch code that notifies
//										the application that the alarm has been 
//										triggered.
//					 (UInt32) alarmSeconds - Alarm date/time in seconds since
//										1/1/1904, or 0 to cancel the current alarm.
//					 (Boolean) quiet - Reserved for future upgrade. This value
//										is not currently used.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err AlmSetAlarm (UInt16 cardNo, LocalID dbID, UInt32 ref,
								UInt32 alarmSeconds, Boolean quiet)
{
	alarmTime = alarmSeconds;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    AlmSetProcAlarm
//
// DESCRIPTION: This routine set or cancel a procedure alarm.
//
// PARAMETERS:  (AlmAlarmProcPtr) proc - Pointer to a function that should
//										be called when alarm is triggered.
//					 (UInt32) refP - Caller-defined value. The value is 
//										passed with the launch code that notifies
//										the application that the alarm has been 
//										triggered.
//					 (UInt32) alarmSeconds - Alarm date/time in seconds since
//										1/1/1904, or 0 to cancel the current alarm.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err AlmSetProcAlarm (AlmAlarmProcPtr proc, UInt32 ref, UInt32 alarmSeconds)
{
	alarmProc = proc;
	alarmTime = alarmSeconds;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateAdjust
//
// DESCRIPTION: This routine return a new date +/- the days adjustment.
//
// PARAMETERS:  (DatePtr) dateP - A DateType structure with the date to
//										be adjusted.
//					 (Int32) adjustment - The Adjustment in number of days.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void DateAdjust (DatePtr dateP, Int32 adjustment)
{
	UInt32	days;

	days = DateToDays (*dateP);
	days += adjustment;
	DateDaysToDate (days, dateP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateDaysToDate
//
// DESCRIPTION: This routine returns the date, given days.
//
// PARAMETERS:  (UInt32) days - Days since 1/1/1904.
//					 (DatePtr) date - Pointer to DateType structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
//			Jerry 7/05/01	Fixed Febuary bug.
////////////////////////////////////////////////////////////////////////
void DateDaysToDate (UInt32 days, DatePtr Date)
{
	UInt16	year = SYSSTARTYEAR;
	Date->month = 1;

	while (days > 366) {
		year++;
		if ( !(year % 4) && ((year % 100) || !(year%400)) ) {
			days -= 366;
		} else {
			days -= 365;
		}
	}

	while (days) {
		if ( Date->month != 2 ) {
			if ((days > daysInMonth[Date->month])) {
				days -= daysInMonth[Date->month];
				Date->month++;
			} else {
				break;
			}
		} else {
			if ( !(year % 4) && ((year % 100)||!(year%400)) ) {
				if ((days > (UInt32)(daysInMonth[Date->month]+1))) {
					days -= (daysInMonth[Date->month]+1);
					Date->month++;
				} else {
					break;
				}
			} else {
				if ((days > (UInt32)(daysInMonth[Date->month]))) {
					days -= (daysInMonth[Date->month]);
					Date->month++;
				} else {
					break;
				}
			}
		}
		if ( Date->month > 12 ) {
			year++;
			Date->month = 1;
		}
	}

	Date->year = year-SYSSTARTYEAR;
	Date->day = (UInt16)days;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateSecondsToDate
//
// DESCRIPTION: This routine returns the date, given seconds.
//
// PARAMETERS:  (UInt32) seconds - seconds since 1/1/1904.
//					 (DatePtr) date - Pointer to DateType structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void DateSecondsToDate (UInt32 seconds, DatePtr date)
{
	UInt32	days = seconds/secondsInADay;

	DateDaysToDate (days, date);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateToAscii
//
// DESCRIPTION: This routine convert the date passed to a string using
//					 the format specified by the dateFormat parameter.
//
// PARAMETERS:  (UInt8) months - Months.
//					 (UInt8) days - Days
//					 (UInt16) years - Years
//					 (DateFormatType) dateFormat - Any DateFormatType format.
//					 (Char *) pString - Pointer to string which gets the result.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void DateToAscii (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString)
{
	char	buffer[5];
	char	spliter[2];

	switch (dateFormat) {
		case dfMDYWithSlashes:		// 12/31/95
			StrIToA (buffer, months);
			Vstrcpy (pString, buffer);
			Vstrcat (pString, "//");
			StrIToA (buffer, days);
			Vstrcat (pString, buffer);
			Vstrcat (pString, "//");
			StrIToA (buffer, (years%100));
			Vstrcat (pString, buffer);
			break;

		case dfDMYWithSlashes:		// 31/12/95
		case dfDMYithDots:			// 31.12.95
		case dfDMYWithDashes:		// 31-12-95
			if ( dateFormat == dfDMYWithSlashes ) {
				Vstrcpy (spliter, "//");
			} else if ( dateFormat == dfDMYithDots ) {
				Vstrcpy (spliter, ".");
			} else {
				Vstrcpy (spliter, "-");
			}
			StrIToA (buffer, days);
			Vstrcpy (pString, buffer);
			Vstrcat (pString, spliter);
			StrIToA (buffer, months);
			Vstrcat (pString, buffer);
			Vstrcat (pString, spliter);
			StrIToA (buffer, (years%100));
			Vstrcat (pString, buffer);
			break;

		case dfYMDWithSlases:		// 95/12/31
		case dfYMDWithDots:			// 95.12.31
		case dfYMDWithDashes:		// 95-12-31
			if ( dateFormat == dfYMDWithSlases ) {
				Vstrcpy (spliter, "//");
			} else if ( dateFormat == dfYMDWithDots ) {
				Vstrcpy (spliter, ".");
			} else {
				Vstrcpy (spliter, "-");
			}
			StrIToA (buffer, (years%100));
			Vstrcpy (pString, buffer);
			Vstrcat (pString, spliter);
			StrIToA (buffer, months);
			Vstrcat (pString, buffer);
			Vstrcat (pString, spliter);
			StrIToA (buffer, days);
			Vstrcat (pString, buffer);
			break;


		case dfMDYLongWithComma:	// Dec 31, 1995
		case dfDMYLongNoDay:		// Dec 1995
			Vstrcpy (pString, cMonth[months-1]);
			Vstrcat (pString, " ");
			if ( dateFormat == dfMDYLongWithComma ) {
				StrIToA (buffer, days);
				Vstrcat (pString, buffer);
				Vstrcat (pString, ", ");
			}
			StrIToA (buffer, years);
			Vstrcat (pString, buffer);
			break;

		case dfDMYLong:				// 31 Dec 1995
		case dfDMYLongWithDot:		// 31. Dec 1995
		case dfDMYLongWithComma:	// 31 Dec, 1995
			StrIToA (buffer, days);
			Vstrcat (pString, buffer);
			if ( dateFormat == dfDMYLongWithComma ) {
				Vstrcat (pString, ".");
			}
			Vstrcat (pString, " ");
			Vstrcpy (pString, cMonth[months-1]);
			if ( dateFormat == dfDMYLongWithComma ) {
				Vstrcat (pString, ",");
			}
			Vstrcat (pString, " ");
			StrIToA (buffer, years);
			Vstrcat (pString, buffer);
			break;

		case dfYMDLongWithDot:		// 1995.12.31
			StrIToA (buffer, years);
			Vstrcpy (pString, buffer);
			Vstrcat (pString, ".");
			StrIToA (buffer, months);
			Vstrcat (pString, buffer);
			Vstrcat (pString, ".");
			StrIToA (buffer, days);
			Vstrcat (pString, buffer);
			break;

		case dfYMDLongWithSpace:	// 1995 Dec 31
			StrIToA (buffer, years);
			Vstrcpy (pString, buffer);
			Vstrcat (pString, " ");
			Vstrcat (pString, cMonth[months]-1);
			Vstrcat (pString, " ");
			StrIToA (buffer, days);
			Vstrcat (pString, buffer);
			break;

		case dfMYMed:					// Dec '95
		case dfMYMedNoPost:			// Dec 95
			Vstrcpy (pString, cMonth[months]-1);
			Vstrcat (pString, " ");
			if ( dateFormat == dfMYMed ) {
				Vstrcat (pString, "'");
			}
			StrIToA (buffer, (years%100));
			Vstrcat (pString, buffer);
			break;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateToDays
//
// DESCRIPTION: This routine return the date in days since 1/1/1904.
//
// PARAMETERS:  (DateType) date - DateType structure.
//
// RETURNED:    Returns the days since 1/1/1904.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
//			Jerry 7/05/01	Fixed Febuary bug.
////////////////////////////////////////////////////////////////////////
UInt32 DateToDays (DateType date)
{
	UInt16	number;
	UInt32	days=0;
	UInt16	year=(date.year+SYSSTARTYEAR);

	number = year-1;
	while ( number >= SYSSTARTYEAR ) {
		if ( !(number%4) && ((number%100)||!(number%400)) ) {
			days += 366;
		} else {
			days += 365;
		}
		number--;
	}

	number = 1;
	while ( number < date.month ) {
		if ( number != 2 ) {
			days += daysInMonth[number];
		} else {
			if ( !(year%4) && ((year%100)||!(year%400)) ) {
				days += (daysInMonth[number]+1);
			} else {
				days += (daysInMonth[number]);
			}
		}
		number++;
	}
	
	days += date.day;

	return	days;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DateToDOWDMFormat
//
// DESCRIPTION: This routine convert a date passed to a formatted string 
//					 using the format specified by the dateFormat parameter.
//					 The string passed must include the name of the day of
//					 week.
//
// PARAMETERS:  (UInt8) months - Months.
//					 (UInt8) days - Days
//					 (UInt16) years - Years
//					 (DateFormatType) dateFormat - Any DateFormatType format.
//					 (Char *) pString - Pointer to string which gets the result.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void DateToDOWDMFormat (UInt8 months, UInt8 days, UInt16 years,
								 DateFormatType dateFormat, Char *pString)
{
	DateToAscii (months, days, years, dateFormat, pString);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DayOfMonth
//
// DESCRIPTION: This routine return the day of a month on which the
//					 specified date occurs.
//
// PARAMETERS:  (UInt16) months - Months.
//					 (UInt16) days - Days
//					 (UInt16) years - Years
//
// RETURNED:    Returns the day of the month.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 DayOfMonth (Int16 month, Int16 day, Int16 year)
{
	return	day;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DayOfWeek
//
// DESCRIPTION: This routine return the day of the week
//
// PARAMETERS:  (UInt16) months - Months.
//					 (UInt16) days - Days
//					 (UInt16) years - Years
//
// RETURNED:    Returns the day of the week.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/05/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 DayOfWeek (Int16 month, Int16 day, Int16 year)
{
	DateType	date;

	date.year = (year-SYSSTARTYEAR);
	date.month = month;
	date.day = day;

#ifdef LINUX
	return	(Int16)(((DateToDays (date)-1)+4)%7);	// 1970/1/1 is Thursday(4).
#else
	return	(Int16)(((DateToDays (date)-1)+5)%7);	// 1904/1/1 is Friday(5).
#endif
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    DaysInMonth
//
// DESCRIPTION: This routine return the number of days in the month
//
// PARAMETERS:  (UInt16) months - Months.
//					 (UInt16) years - Years
//
// RETURNED:    Returns the number of days of the month for that year.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 DaysInMonth (Int16 month, Int16 year)
{
	if ( month != 2 ) {
		return	daysInMonth[month];
	} else {
		if ( !(year%4) && ((year%100)||!(year%400)) )
			return	(daysInMonth[month]+1);
		else
			return	daysInMonth[month];
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimeAdjust
//
// DESCRIPTION: This routine return a new date +/- the time adjustment.
//
// PARAMETERS:  (DateTimePtr) datetimeP - A DateType structure.
//					 (Int32) adjustment - The Adjustment in seconds.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void TimeAdjust (DateTimePtr datetimeP, Int32 adjustment)
{
	UInt32	seconds;

	seconds = TimDateTimeToSeconds(datetimeP);
	seconds += adjustment;
	TimSecondsToDateTime (seconds, datetimeP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimDateTimeToSeconds
//
// DESCRIPTION: This routine return the number of seconds since 1/1/1904
//					 to the passed date and time.
//
// PARAMETERS:  (DateTimePtr) dateTimeP - Pointer to a DateTimeType structure.
//
// RETURNED:    Returns the time in seconds since 1/1/1904.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 TimDateTimeToSeconds (DateTimePtr dateTimeP)
{
	DateType	date;
	UInt32	seconds=0;

	date.year = (dateTimeP->year-SYSSTARTYEAR);
	date.month = dateTimeP->month;
	date.day = dateTimeP->day;

	seconds = (DateToDays (date)-1) * secondsInADay ;
	seconds += (dateTimeP->hour+timeZoneDiff)*secondsInAHour;
	seconds += dateTimeP->minute*secondsInAMinute;
	seconds += dateTimeP->minute;

	return	seconds;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimGetSeconds
//
// DESCRIPTION: This routine return the current date and time of the
//					 device in seconds since 1/1/1904 12AM.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the current time in seconds since 1/1/1904.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 TimGetSeconds (void)
{
	DateTimeType	dateTime;

	VGetSystemTime (&dateTime);
	return	TimDateTimeToSeconds (&dateTime);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimGetTicks
//
// DESCRIPTION: This routine return the tick count since the last reset.
//					 The tick count does not advance while the device is in
//					 sleep mode.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the tick count.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 TimGetTicks (void)
{
	UInt32	currentSeconds = TimGetSeconds ();

	return	currentSeconds-sysSecondsAfterReset;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimSecondsToDateTime
//
// DESCRIPTION: This routine returns the date and time, given seconds.
//
// PARAMETERS:  (UInt32) seconds - Seconds since 1/1/1904.
//					 (DateTimePtr) dateTimeP - Pointer to DateTimeType structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
//			Jerry 7/05/01	Completed weekDay 
////////////////////////////////////////////////////////////////////////
void TimSecondsToDateTime (UInt32 seconds, DateTimePtr dateTimeP)
{
	UInt32	days = (UInt32)(seconds/secondsInADay);
	DateType	date;

	DateDaysToDate (days, &date);
	dateTimeP->year = date.year+SYSSTARTYEAR;
	dateTimeP->month = date.month;
	dateTimeP->day = date.day;
#ifdef	LINUX
	dateTimeP->weekDay = (Int16)(((days-1)+4)%7);	// 1970/1/1 is Thursday(4).
#else
	dateTimeP->weekDay = (Int16)(((days-1)+5)%7);	// 1904/1/1 is Friday(5).
#endif
	seconds = seconds % secondsInADay;
	dateTimeP->hour = (Int16) (seconds/secondsInAHour);
	seconds = seconds % secondsInAHour;

	dateTimeP->minute = (Int16) seconds/secondsInAMinute;
	dateTimeP->second = (Int16) seconds % secondsInAMinute;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimSetSeconds
//
// DESCRIPTION: This routine set the clock of the device to the date 
//					 and time passed as the number of seconds since 1/1/1904
//
// PARAMETERS:  (UInt32) seconds - Seconds since 1/1/1904.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void TimSetSeconds (UInt32 seconds)
{
	DateTimeType	dateTime;

	TimSecondsToDateTime (seconds, &dateTime);
	VSetSystemTime (&dateTime);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimeToAscii
//
// DESCRIPTION: This routine convert the date passed to formatted string.
//
// PARAMETERS:  (UInt8) hours - Hours.
//					 (UInt8) minutes - Minutes.
//					 (TimeFormatType) timeFomrat - Any TimeFormatType format.
//					 (Char *) pString - Pointer to string which gets the result.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
//			Jerry	11/17/01	Modify 0:0 to 12:00
////////////////////////////////////////////////////////////////////////
void TimeToAscii (UInt8 hours, UInt8 minutes, 
								 TimeFormatType timeFormat, Char *pString)
{
	Char	buffer[3];
	UInt8	thours;

	switch (timeFormat) {
		case tfColonAMPM:		// 1:00 pm
		case tfDotAMPM:		// 1.00 pm
		case tfHoursAMPM:		// 1 pm
			thours = hours%12;
			if ( thours == 0 )
				thours = 12;
			StrIToA (buffer, thours);
			Vstrcpy (pString, buffer);
			if ( timeFormat == tfColonAMPM )
				Vstrcat (pString, ":");
			else if ( timeFormat == tfDotAMPM )
				Vstrcat (pString, ".");

			if ( timeFormat != tfHoursAMPM ) {
				StrIToA (buffer, minutes);
				if ( minutes < 10 )
					Vstrcat (pString, "0");
				Vstrcat (pString, buffer);
			}
			Vstrcat (pString, " ");
			if ( hours >= 12 )
				Vstrcat (pString, "pm");
			else
				Vstrcat (pString, "am");
			break;

		case tfColon24h:		// 13:00
		case tfDto24h:			// 13.00
		case tfHours24h:		// 13
		case tfComma24h:		// 13,00
			StrIToA (buffer, hours);
			Vstrcpy (pString, buffer);
			if ( timeFormat == tfColonAMPM )
				Vstrcat (pString, ":");
			else if ( timeFormat == tfDotAMPM )
				Vstrcat (pString, ".");
			else if ( timeFormat == tfComma24h )
				Vstrcat (pString, ",");

			if ( timeFormat != tfHours24h ) {
				StrIToA (buffer, minutes);
				Vstrcat (pString, buffer);
			}
			break;
	}
}
