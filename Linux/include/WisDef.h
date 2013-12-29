#ifndef __WISDEF_H__
#define __WISDEF_H__


//////////////////////////////////////////////
//	Screen relative defination
//////////////////////////////////////////////
#define	PALMWIDTH				(Coord)160
#define	PALMHEIGHT				(Coord)160
#define	HANDERAWIDTH			(Coord)240
#define	HANDERAHEIGHT			(Coord)240

#ifdef	HANDERA
	#define	PDAWIDTH				HANDERAWIDTH
	#define	PDAHEIGHT			HANDERAHEIGHT
#else
	#define	PDAWIDTH				PALMWIDTH
	#define	PDAHEIGHT			PALMHEIGHT
#endif

#ifdef	LINUX
	#define	SCREENWIDTH			(Coord)240
	#define	SCREENHEIGHT		(Coord)240
	#define	SCREENXBASE			(Coord)0
	#define	SCREENYBASE			(Coord)0
#else
	#define	SCREENWIDTH			(Coord)320
	#define	SCREENHEIGHT		(Coord)320
	#define	SCREENXBASE			(Coord)63
	#define	SCREENYBASE			(Coord)60
#endif	//HANDERA


// resolution translate macro
#define	VPDAToSysXCoord(X)	(Coord)((X)*SCREENWIDTH/PDAWIDTH+SCREENXBASE)
#define	VPDAToSysYCoord(Y)	(Coord)((Y)*SCREENHEIGHT/PDAHEIGHT+SCREENYBASE)
#define	VPDAToSysXRes(X)		(Coord)((X)*SCREENWIDTH/PDAWIDTH)
#define	VPDAToSysYRes(Y)		(Coord)((Y)*SCREENHEIGHT/PDAHEIGHT)

// plus (resolution-1) prevent to shrink size 
#define	VSysToPDAXCoord(X)	(Coord)(((X)-SCREENXBASE)*PDAWIDTH/SCREENWIDTH)
#define	VSysToPDAYCoord(Y)	(Coord)(((Y)-SCREENYBASE)*PDAHEIGHT/SCREENHEIGHT)
#define	VSysToPDAXRes(X)		(Coord)((X)*PDAWIDTH/SCREENWIDTH)
#define	VSysToPDAYRes(Y)		(Coord)((Y)*PDAHEIGHT/SCREENHEIGHT)


// Screen Coordinate
#define	PDASTARTX				0
#define	PDASTARTY				0


//	Battery coordinate definition
#define	BATTERYSTARTX			40
#define	BATTERYSTARTY			1
#define	BATTERYWIDTH			30
#define	BATTERYHEIGHT			15
#define	BATTERYSEGMENT			3



//////////////////////////////////////////////
//	Character-Font relative defination
//////////////////////////////////////////////
#define	ArrowWidth				20
#define	TailArrowWidth			12
#define	TailArrowHeight		10
#define	CheckBoxWidth			10
#define	TitleHeight				13
#define	CORNERDIM				6

#ifndef	LINUX
	#define	CHARWIDTH			10
	#define	CharsPerLine		(UInt16)(PDAWIDTH/CHARWIDTH)
#endif

#define	FORMMINHEIGHT			60


/* Pen Styles */
#define PS_SOLID            0
#define PS_DASH             1       /* -------  */
#define PS_DOT              2       /* .......  */
#define PS_DASHDOT          3       /* _._._._  */
#define PS_DASHDOTDOT       4       /* _.._.._  */
#define PS_NULL             5
#define PS_INSIDEFRAME      6
#define PS_USERSTYLE        7
#define PS_ALTERNATE        8
#define PS_STYLE_MASK       0x0000000F

#define SOLID_LARGE			0		// large triangle
#define DASH_LARGE			1		// large triangle
#define SOLID_SMALL			2		// small triangle
#define DASH_SMALL			3		// small triangle
#define SOLID_TAIL			4		// arrow
#define DASH_TAIL				5		// arrow

#define	TAP_CHAR		'.'


//	define system area line coordinate
#define	SysPanelVLine1		(Coord)VPDAToSysXCoord(30)
#define	SysPanelVLine2		(Coord)VPDAToSysYCoord(130)

#define	SysPanelStartX		(Coord)VPDAToSysXCoord(0)
#define	SysPanelStartY		(Coord)VPDAToSysYCoord(162)
#define	SysPanelEndX		(Coord)VPDAToSysXCoord(159)
#define	SysPanelEndY		(Coord)VPDAToSysYCoord(212)

#define	SysPanelHLine1		(Coord)((SysPanelEndY-SysPanelStartY)/3+SysPanelStartY)
#define	SysPanelHLine2		(Coord)((SysPanelEndY-SysPanelStartY)*2/3+SysPanelStartY)

// define the hand writing input area
#define	HandWritingX1		(Coord)SysPanelVLine1
#define	HandWritingY1		(Coord)SysPanelStartY
#define	HandWritingX3		(Coord)SysPanelVLine2
#define	HandWritingX2		(Coord)((SysPanelVLine2-SysPanelVLine1)*3/5+SysPanelVLine1)
#define	HandWritingY2		(Coord)SysPanelEndY

#ifdef	LINUX
	#define	MENUSX			(Coord)VSysToPDAXRes(SysPanelStartX)
	#define	MENUSY			(Coord)VSysToPDAXRes(SysPanelHLine1)
	#define	MENUEX			(Coord)VSysToPDAXRes(SysPanelVLine1)
	#define	MENUEY			(Coord)VSysToPDAXRes(SysPanelHLine2)
#else
	#define	MENUSX			4
	#define	MENUSY			200
	#define	MENUEX			22
	#define	MENUEY			218
#endif

// defien for list scroll function
#define	NOSCROLL				0
#define	SCROLLUP				-1
#define	SCROLLDOWN			1

//	define the line width constant
#define	THIN_LINE			1
#define	THICK_LINE			2

// define system button resource
#define	SysButton1			9001
#define	SysButton2			9002
#define	SysButton3			9003
#define	SysButton4			9004
#define	SysButton5			9005
#define	SysButton6			9006

#define	SYSTEMTICKS		100
#define	MINSYSTICKS		5
#define	MAXSYSTICKS		200

// define system handle size
#define		NUMSYSHANDLE		256


// define control drawing mode
#define	DRAW_NORMAL		0
#define	DRAW_INVERT		1

// define draw string mode
#define	SINGLELINE			TRUE
#define	MULTIPLELINE		FALSE

#define	MOUSE_DOWN			0
#define	MOUSE_MOVE			1
#define	MOUSE_UP				2

#define	SCREEN_ALL			0
#define	SCREEN_DISPLAY		1

#define	COORD_NORMAL		0
#define	COORD_STRETCH		1
#define	COORD_PARTSTRETCH	2

#define	CL_BACKGROUND		TRUE
#define	CL_FOREGROUND		FALSE

#define	CUR_DRAW				0
#define	CUR_CLEAR			1

//	define special character
#define ASCII_LINK		0x05		// pen from left-bottom to right-up
#define ASCII_TEMPCAPS	0x06		// pen from bottom to up
#define ASCII_CAPS		0x07
#define ASCII_BS			0x08		// pen from right to left
#define ASCII_LF			0x0A
#define ASCII_CR			0x0D		// from fight-top to left-bottom

#endif	// __WISDEF_H__
