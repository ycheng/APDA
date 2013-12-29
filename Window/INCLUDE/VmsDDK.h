#ifndef __VMSDDK_H__
#define __VMSDDK_H__

// Total 65 functions now.

// Below APIs are File relative API, there are 16 functions now.
extern void VStartApplication ();
extern int Vfclose (void *stream);
extern int Vfeof (void *stream);
extern int Vfflush (void *stream);
extern char *Vfgets( char *string, int n, void *stream );
extern void *Vfopen (const char *filename, const char *mode);
extern void *VfopenTempFile();
extern int Vfread (void *buffer, int size, int count, void *stream);
//extern int *VGetProcAddress (VHINSTANCE hInst, char *modulename);
extern VHINSTANCE VLoadLibrary (Char *filename);
extern int Vfseek (void *stream, long offset, int origin);
//extern int Vfscanf( void *stream, const char *format ,... );

extern int Vfscanf3( void *stream, const char *format ,void *par1, void *par2, void *par3 );
extern int Vfscanf2( void *stream, const char *format ,void *par1, void *par2 );
extern int Vfscanf( void *stream, const char *format ,void *par1 );

extern int Vsscanf( const char *buffer, const char *format, void *par );
extern long Vftell (void *stream);
extern int Vfwrite (const void *buffer, int size, int count, void *stream);


// Below APIs are graphic relative API, there are 19 functions now.
extern void VDrawBackground ();
extern void VDrawBitmap (int x, int y, char *filename);
//extern void VDrawBattery (UInt16 energy);
extern Int16 VDrawChar (WChar theChar, Coord x, Coord y);
extern Int16 VDrawChars (const Char *chars, Int16 len, Coord x, Coord y, int mode);
extern void VDrawCheck (Coord StartX, Coord StartY, Boolean Style);
extern void VDrawCursor (Coord x, Coord y, int mode);
extern void VDrawDownArrow (int x, int y, int style);
extern void VDrawLeftArrow (int x, int y, int style);
extern void VDrawLine (Coord StartX, Coord StartY, Coord Width, Coord Height, UInt16 width, UInt32 color, Int penstyle);
extern void VDrawPixel (Coord x, Coord y, UInt32 color);
extern void VDrawRect (RectangleType *rect, UInt16 penStyle, UInt16 cornerDiam, Boolean bBackground, char coordMode, char drawMode);
extern void VDrawRightArrow (int x, int y, int style);
extern void VDrawString(Coord x, Coord y, const char *str, UInt32 length, Boolean singleline, Boolean background, int mode);
extern void VDrawUpArrow (int x, int y, int style);
extern UInt8 VGetPixel (Coord x, Coord y);
extern void VRedrawRegion (const RectangleType *rect, int mode);
extern void VSaveRegion (const RectangleType *rect, int mode);
extern void VUpdateWindow();


// Below APIs are math relative API, there are 3 functions now.
UInt32 Vrand ();
void Vsrand (UInt32 seed);
extern int Vabs (int n);
extern double Vexp (double x);
extern Char *Vgetenv (const Char *varname);


// Below APIs are memory relative API, there are 6 functions now.
extern void Vfree(void *str);
extern void *Vmalloc(UInt32 size);
extern void *Vrealloc(void *memblock, UInt32 size);
extern void *Vmemcpy (void *dst, const void *src, UInt32 length);
extern void *Vmemmove (void *dst, const void *src, UInt32 length);
extern void *Vmemset (void *str, int word, UInt32 length);


// Below APIs are network relative API, there are 6 functions now.
extern Boolean CloseConnection ();
extern UInt16 GetConnectionStatus (Boolean *ctsOnP, Boolean *dsrOnP);
extern Boolean OpenConnection (UInt16 port, UInt32 baud);
extern UInt32 ReadCommBlock (void *lpszBlock, UInt32 nMaxLength);
extern void SetupTimeout (UInt32 baud, Int32 timeout);
extern Boolean WriteCommBlock (void *lpByte , UInt32 dwBytesToWrite);


// Below APIs are string relative API, there are 14 functions now.
extern int		Vatoi(const char *word);
extern UInt32	Vsizeof (const void *str);
extern char		*Vstrcat (char *dst, const char *src);
extern Char		*Vstrchr (const Char *str, WChar chr);
extern int		Vstrcmp (const char *str1, const char *str2);
extern char		*Vstrcpy (char *dst, const char *src);
extern char		*Vstrdup( const char *strSource );
extern UInt32	Vstrlen (const char *str);
extern Char*	Vstrlwr (Char *dst, const Char* src);
extern Char*	Vstrncat (Char *dst, const Char* src, Int16 n);
extern Int16	Vstrncmp (const Char *dst, const Char* src, UInt32 n);
extern Int16	Vstricmp (const Char *dst, const Char* src);
extern Int16	Vstrnicmp (const Char *dst, const Char* src, UInt32 n);
extern char		*Vstrncpy (char *dst, const char *src, int size);
extern char *Vstrrchr( const char *string, unsigned char  c );


// Below APIs are time relative API, there are 2 functions now.
extern void VGetCurrentDirectory (Char *directory);
extern void VGetSystemTime (DateTimeType *datetime);
extern void VSetSystemTime (const DateTimeType *datetime);


// Below APIs are system relative API, there are 2 functions now.
extern void CreateWindows(char* appName, 
						  char* _caption, 
						  int X, 
						  int Y, 
						  int Width, 
						  int Height);
extern void WPeekEventsDDK(void);
extern void WResetEvent (EventType *event);

#endif	// __VMSDDK_H__
