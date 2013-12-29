#ifndef __DATETIME_H__
#define __DATETIME_H__


// Time zone define
#define	TaipeiZone			8

#define	hoursInADay			24
#define	minutesInAHour		60
#define	secondsInAMinute	60
#define	secondsInAHour		(minutesInAHour*secondsInAMinute)
#define	secondsInADay		(secondsInAHour*hoursInADay)


/************************************************************
 * Date Time Constants
 *************************************************************/

// Maximum lengths of strings return by the date and time formating
// routine DateToAscii and TimeToAscii.
#define timeStringLength		9
#define dateStringLength		9
#define longDateStrLength		15
#define dowDateStringLength	19
#define dowLongDateStrLength	25



typedef struct SysAlarmTriggeredParamType {
	DWord				ref;				// --> alarm reference value passed by caller;
	ULong				alarmSeconds;	// --> alarm date/time in seconds since 1/1/1904;
	Boolean			purgeAlarm;		// <-- if set to true on return, this alarm will
											// be removed from the alarm table and the display
											// notification will NOT be generated for it.
											// If your application does not require the
											// sysAppLaunchCmdDisplayAlarm action code, setting
											// this field to true is a good optimization.
} SysAlarmTriggeredParamType;

typedef void (AlmAlarmProcType) (UInt16 almProcCmd, SysAlarmTriggeredParamType *paramP);
typedef AlmAlarmProcType *AlmAlarmProcPtr;


typedef enum {
	tfColon,
	tfColonAMPM,		// 1:00 pm
	tfColon24h,			// 13:00
	tfDot,
	tfDotAMPM,			// 1.00 pm
	tfDto24h,			// 13.00
	tfHoursAMPM,		// 1 pm
	tfHours24h,			// 13
	tfComma24h			// 13,00
} TimeFormatType;

typedef TimeFormatType *TimeFormatPtr;

typedef enum {
	dfMDYWithSlashes,		// 12/31/95
	dfDMYWithSlashes,		// 31/12/95
	dfDMYithDots,			// 31.12.95
	dfDMYWithDashes,		// 31-12-95
	dfYMDWithSlases,		// 95/12/31
	dfYMDWithDots,			// 95.12.31
	dfYMDWithDashes,		// 95-12-31

	dfMDYLongWithComma,	// Dec 31, 1995
	dfDMYLong,				// 31 Dec 1995
	dfDMYLongWithDot,		// 31. Dec 1995
	dfDMYLongNoDay,		// Dec 1995
	dfDMYLongWithComma,	// 31 Dec, 1995
	dfYMDLongWithDot,		// 1995.12.31
	dfYMDLongWithSpace,	// 1995 Dec 31
	dfMYMed,					// Dec '95
	dfMYMedNoPost			// Dec 95
} DateFormatType;


typedef struct {
	Int16		second;
	Int16		minute;
	Int16		hour;
	Int16		day;
	Int16		month;
	Int16		year;
	Int16		weekDay;
} DateTimeType;

typedef DateTimeType *DateTimePtr;


typedef struct {
	UInt8		hours;
	UInt8		minutes;
} TimeType;

typedef TimeType *TimePtr;


typedef struct {
	UInt16	year:7;
	UInt16	month:4;
	UInt16	day:5;
} DateType;

typedef DateType *DatePtr;


// Values returned by DoyOfMonth routine.
typedef enum {
	dom1stSun, dom1stMon, dom1stTue, dom1stWen, dom1stThu, dom1stFri, dom1stSat,
	dom2ndSun, dom2ndMon, dom2ndTue, dom2ndWen, dom2ndThu, dom2ndFri, dom2ndSat,
	dom3rdSun, dom3rdMon, dom3rdTue, dom3rdWen, dom3rdThu, dom3rdFri, dom3rdSat,
	dom4thSun, dom4thMon, dom4thTue, dom4thWen, dom4thThu, dom4thFri, dom4thSat,
	domLastSun, domLastMon, domLastTue, domLastWen, domLastThu, domLastFri, 
	domLastSat
} DayOfWeekType;


#endif 	//__DATETIME_H__
