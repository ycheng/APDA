#ifndef __PARSE_H__
#define __PARSE_H__

#define	IDID					0
#define	ENDID					1
#define	AUTOID				2
#define	FORMID				3
#define	MENUID				4	
#define	LISTID				5
#define	BEGINID				6
#define	ALERTID				7
#define	FIELDID				8
#define	LABELID				9
#define	TABLEID				10
#define	TITLEID				11
#define	BITMAPID				12
#define	BUTTONID				13
#define	INCLUDEID			14
#define	BUTTONSID			15
#define	CHECKBOXID			16
#define	POPUPLISTID			17
#define	SCROLLBARID			18
#define	PUSHBUTTONID		19
#define	FORMBITMAPID		20
#define	POPUPTRIGGERID		21
#define	REPEATBUTTONID		22
#define	SELECTORTRIGGERID	23	

#define	UNKNOWNID			99

typedef struct BitmapLink {
	UInt16	ID;
	Char		*fileName;
} BitmapLink;

#endif // __PARSE_H__
