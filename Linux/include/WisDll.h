/*========================================================
  Apilib.h
  This file list all current supported function 
  compitable with Palm OS.

  Current status completed 351 functions.
  Total List 381 functions.
  508 funtions not list below.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0507, 2001 by Jerry Chu
 =========================================================*/
#ifndef __WISDLL_H__
#define __WISDLL_H__

#ifndef _WISIMP

#if defined(_WISEXPORTDLL)
#define _WISIMP __declspec (dllexport)
#elif defined(_WISIMPORTDLL)
#define _WISIMP __declspec (dllimport)
#endif

#endif


_WISIMP void WCategoryInitialize (AppInfoPtr appInfoP);
_WISIMP void WCategoryRelease ();
_WISIMP void WClearScreen (int mode);
_WISIMP Err WMenuAddItem (UInt16 menuIndex, Int16 subMenuIndex, UInt16 id, Char cmd, const Char *textP);
_WISIMP MenuBarType *WMenuInitialize ();
_WISIMP void WDrawBattery (UInt16 energy);
_WISIMP void VDrawLine (Coord StartX, Coord StartY, Coord EndX, Coord EndY, 
								UInt16 width, UInt32 color, Int penStyle);
_WISIMP void VDrawRect (RectangleType *rect, UInt16 penStyle, UInt16 cornerDiam, Boolean bBackground, char coordMode, char drawMode);
_WISIMP void VDrawString( Coord x, Coord y,
                  const char *str,
                  UInt32 length,
						Boolean singleline,
						Boolean background,
						int mode);
_WISIMP UInt32 Vstrlen (const char *str);
_WISIMP int Vabs (int n);
_WISIMP void VGetSystemTime (DateTimeType *datetime);
_WISIMP void WMenuRelease (MenuBarType *menuP);
_WISIMP VHWND WisWinMain(VHINSTANCE _hInst,     // program instance
                     VHINSTANCE _hPrevInst, // previous instance
                     Char* _lpCmdLine,     // command line
                     int _nCmdShow);
_WISIMP void WCloseAll ();
_WISIMP Boolean VCheckQuit(void);
_WISIMP void WResetEvent (EventType *event);
_WISIMP Char *WGetApplicationName (const Char *szFileName, Char *appName);
_WISIMP Char *WGetFileDirectory (const Char *szFileName, Char *Directory);
_WISIMP Int32 WGetFileSize (const char *filename);
_WISIMP Boolean WGetResourceFileName (Char *directory, char *filename);
_WISIMP void WSetMenu (MenuBarType *menuP);
_WISIMP void		WResetEvent (EventType *event);
_WISIMP void WinDrawTitleChars (const Char *chars, Int16 len, Coord x, Coord y);


#endif // __WISDLL_H__
