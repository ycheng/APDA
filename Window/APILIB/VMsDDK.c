#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <math.h>

#include <VCommon.h>
#include <VPdaSDK.h>
#include <VMsDDK.h>
#include <Networks.h>

#define	APIClassName	"APITEST"
#define	CursorSize		12
#define	PDABMPNAME		"Pda.bmp"

#define	ScreenWidth		440
#define	ScreenHeight	670

// constant definitions
#define GWL_NPTTYINFO        0

// Flow control flags
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13


typedef struct tagTTYINFO
{
   HANDLE  idComDev ;
   BYTE    bPort;
   BOOL    fConnected, fXonXoff, fLocalEcho, fNewLine, fAutoWrap,
           fUseCNReceive, fDisplayErrors;
   BYTE    bByteSize, bFlowCtrl, bParity, bStopBits ;
   DWORD   dwBaudRate ;
   HFONT   hTTYFont ;
   LOGFONT lfTTYFont ;
   DWORD   rgbFGColor ;
   int     xSize, ySize, xScroll, yScroll, xOffset, yOffset,
           nColumn, nRow, xChar, yChar ;
   HANDLE      hPostEvent, hWatchThread, hWatchEvent ;
   HWND        hTermWnd ;
   DWORD       dwThreadID ;
   OVERLAPPED  osWrite, osRead ;
} TTYINFO, NEAR *NPTTYINFO ;

NPTTYINFO   npTTYInfo ;

// macros ( for easier readability )
#define GETHINST( x )  ((HINSTANCE) GetWindowLong( x, GWL_HINSTANCE ))
#define GETNPTTYINFO( x ) ((NPTTYINFO) GetWindowLong( x, GWL_NPTTYINFO ))
#define SETNPTTYINFO( x, y ) SetWindowLong( x, GWL_NPTTYINFO, (LONG) y )

#define COMDEV( x ) (x -> idComDev)
#define PORT( x )   (x -> bPort)
#define SCREEN( x ) (x -> abScreen)
#define CONNECTED( x ) (x -> fConnected)
#define XONXOFF( x ) (x -> fXonXoff)
#define LOCALECHO( x ) (x -> fLocalEcho)
#define NEWLINE( x ) (x -> fNewLine)
#define AUTOWRAP( x ) (x -> fAutoWrap)
#define BYTESIZE( x ) (x -> bByteSize)
#define FLOWCTRL( x ) (x -> bFlowCtrl)
#define PARITY( x ) (x -> bParity)
#define STOPBITS( x ) (x -> bStopBits)
#define BAUDRATE( x ) (x -> dwBaudRate)
#define HTTYFONT( x ) (x -> hTTYFont)
#define LFTTYFONT( x ) (x -> lfTTYFont)
#define FGCOLOR( x ) (x -> rgbFGColor)
#define XSIZE( x ) (x -> xSize)
#define YSIZE( x ) (x -> ySize)
#define XSCROLL( x ) (x -> xScroll)
#define YSCROLL( x ) (x -> yScroll)
#define XOFFSET( x ) (x -> xOffset)
#define YOFFSET( x ) (x -> yOffset)
#define COLUMN( x ) (x -> nColumn)
#define ROW( x ) (x -> nRow)
#define XCHAR( x ) (x -> xChar)
#define YCHAR( x ) (x -> yChar )
#define USECNRECEIVE( x ) (x -> fUseCNReceive)
#define DISPLAYERRORS( x ) (x -> fDisplayErrors)

#define POSTEVENT( x ) (x -> hPostEvent)
#define TERMWND( x ) (x -> hTermWnd)
#define HTHREAD( x ) (x -> hWatchThread)
#define THREADID( x ) (x -> dwThreadID)
#define WRITE_OS( x ) (x -> osWrite)
#define READ_OS( x ) (x -> osRead)

#define SET_PROP( x, y, z )  SetProp( x, MAKEINTATOM( y ), z )
#define GET_PROP( x, y )     GetProp( x, MAKEINTATOM( y ) )
#define REMOVE_PROP( x, y )  RemoveProp( x, MAKEINTATOM( y ) )

DWORD    BaudTable[] =
         {
            CBR_110, CBR_300, CBR_600, CBR_1200, CBR_2400,
            CBR_4800, CBR_9600, CBR_14400, CBR_19200, CBR_38400,
            CBR_56000, CBR_128000, CBR_256000
         } ;


HINSTANCE	vHInst = 0;                     // the handle instance for the program
HWND			hwnd;
HDC			hdc, memDC;
HBITMAP		memBM[5];		// the handle bitmap of saved screen
UInt16		BitmapIndex=0;

EventType	*CurEvent;
// key maps
keycode		vKeyMap[256];


// Using by Network function
char	WisHeader[] = "Wiscore OS Header";
char	WisTailer[] = "Wiscore OS Tailer";
char	CISBMPNAME[256];

BOOL			writeExclusive = FALSE, readExclusive = FALSE;
Int16			lastScreenX=0, lastScreenY=0;
UInt32	tColor=FOREGROUNDCOLOR;	// text color
extern GrfStateType	grfState;

#ifndef	_APM_SIMULATOR
extern DWord  PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags);
#endif

void VDrawLine (Coord StartX, Coord StartY, Coord EndX, Coord EndY, 
						UInt16 width, UInt32 color, Int penStyle);
extern Int16 WPushEvent (const EventType *event);
extern Boolean WPopEvent (EventType *event);
extern void drawline (Coord x0, Coord y0, Coord x1, Coord y1);
extern Int16 LstCheckListHit(ListType *listP, Int16 x, Int16 y);
extern void WDestroyForm();
extern void WDestroyMenu();
extern SYSHandle	sysHandle;
extern Int16 CheckHitOnControl(UInt16 x, UInt16 y);
extern void CheckControlEvent (Int16 id);
extern void WClickOnControl (int x, int y, int mode);
extern void WPeekMouseEvent (Boolean PenDown);
extern void WDrawStartUpScreen ();


unsigned char	roundX[] = 
	{	1,
		2, 2,
		2, 3, 3,
		2, 3, 4, 4,
		2, 4, 4, 5, 5,
		3, 4, 5, 6, 6, 6,
		3, 5, 6, 6, 7, 7, 7,
		3, 5, 6, 7, 7, 8, 8, 8,
		4, 6, 7, 7, 8, 8, 9, 9, 9,
		4, 6, 7, 8, 9, 9, 10, 10, 10 ,10,
		4, 6, 7, 8, 9, 10, 10, 11, 11, 11, 11,
		5, 6, 8, 9, 10, 10, 11, 11, 12, 12, 12, 12,
		5, 7, 8, 9, 10, 11, 12, 12, 12, 13, 13, 13, 13,
		5, 7, 9, 10, 11, 11, 12, 13, 13, 13, 14, 14, 14, 14,
		5, 7, 9, 10, 11, 12, 13, 13, 14, 14, 14, 15, 15, 15, 15,
		5, 8, 9, 10, 12, 12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 16,
		6, 8, 10, 11, 12, 13, 13, 14, 15, 15, 16, 16, 16, 17, 17, 17, 17,
		6, 8, 10, 11, 12, 13, 14, 15, 16, 16, 17, 17, 17, 18, 18, 18, 18, 18,
		6, 9, 10, 11, 13, 14, 15, 15, 16, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19,
		6, 9, 10, 12, 13, 14, 15, 16, 17, 17, 18, 18, 19, 19, 19, 20, 20, 20, 20, 20,
	};

// Below APIs are Network relative API

UInt16 GetConnectionStatus (Boolean *ctsOnP, Boolean *dsrOnP)
{
   DCB        dcb ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

   dcb.DCBlength = sizeof( DCB ) ;

   GetCommState( COMDEV( npTTYInfo ), &dcb ) ;

	*ctsOnP = (Boolean) dcb.fOutxCtsFlow;
	*dsrOnP = (Boolean) dcb.fOutxDsrFlow;

	return	0;
}

//---------------------------------------------------------------------------
//  BOOL NEAR SetupConnection( HWND hWnd )
//
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Win-32 requires a slightly different processing of the DCB.
//       Changes were made for configuration of the hardware handshaking
//       lines.
//
//---------------------------------------------------------------------------
BOOL NEAR SetupConnection ()
{
   BOOL       fRetVal ;
   BYTE       bSet ;
   DCB        dcb ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

   dcb.DCBlength = sizeof( DCB ) ;

   GetCommState( COMDEV( npTTYInfo ), &dcb ) ;

   dcb.BaudRate = BAUDRATE( npTTYInfo ) ;
   dcb.ByteSize = BYTESIZE( npTTYInfo ) ;
   dcb.Parity = PARITY( npTTYInfo ) ;
   dcb.StopBits = STOPBITS( npTTYInfo ) ;

   // setup hardware flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_DTRDSR) != 0) ;
   dcb.fOutxDsrFlow = bSet ;
   if (bSet)
      dcb.fDtrControl = DTR_CONTROL_HANDSHAKE ;
   else
      dcb.fDtrControl = DTR_CONTROL_ENABLE ;

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_RTSCTS) != 0) ;
	dcb.fOutxCtsFlow = bSet ;
   if (bSet)
      dcb.fRtsControl = RTS_CONTROL_HANDSHAKE ;
   else
      dcb.fRtsControl = RTS_CONTROL_ENABLE ;

   // setup software flow control

   bSet = (BYTE) ((FLOWCTRL( npTTYInfo ) & FC_XONXOFF) != 0) ;

   dcb.fInX = dcb.fOutX = bSet ;
   dcb.XonChar = ASCII_XON ;
   dcb.XoffChar = ASCII_XOFF ;
   dcb.XonLim = 100 ;
   dcb.XoffLim = 100 ;

   // other various settings

   dcb.fBinary = TRUE ;
   dcb.fParity = TRUE ;

   fRetVal = SetCommState( COMDEV( npTTYInfo ), &dcb ) ;

   return ( fRetVal ) ;

} // end of SetupConnection()

void SetupTimeout (UInt32 baud, Int32 timeout)
{
   COMMTIMEOUTS  CommTimeOuts ;

	// get any early notifications
	SetCommMask( COMDEV( npTTYInfo ), EV_RXCHAR ) ;

	// setup device buffers
	SetupComm( COMDEV( npTTYInfo ), 4096, 4096 ) ;

	// purge any information in the buffer
	PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
                        PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

	// set up for overlapped I/O
	CommTimeOuts.ReadIntervalTimeout = timeout ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;
	// CBR_9600 is approximately 1byte/ms. For our purposes, allow
	// double the expected time per character for a fudge factor.
	CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/baud;
	CommTimeOuts.WriteTotalTimeoutConstant = 0 ;
	SetCommTimeouts( COMDEV( npTTYInfo ), &CommTimeOuts ) ;
}

//---------------------------------------------------------------------------
//  int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided buffer.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------
UInt32 ReadCommBlock (void *lpszBlock, UInt32 nMaxLength)
{
   BOOL       fReadStat ;
   COMSTAT    ComStat ;
   DWORD      dwErrorFlags;
   DWORD      dwLength;
   DWORD      dwError;
   char       szError[ 10 ] ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

   // only try to read number of bytes in queue
   ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
   dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;

   if (dwLength > 0) {
      fReadStat = ReadFile( COMDEV( npTTYInfo ), lpszBlock,
		                    dwLength, &dwLength, &READ_OS( npTTYInfo ) ) ;
      if (!fReadStat) {
         if (GetLastError() == ERROR_IO_PENDING) {
            OutputDebugString("\n\rIO Pending");
            // We have to wait for read to complete.
            // This function will timeout according to the
            // CommTimeOuts.ReadTotalTimeoutConstant variable
            // Every time it times out, check for port errors
            while(!GetOverlappedResult( COMDEV( npTTYInfo ),
               &READ_OS( npTTYInfo ), &dwLength, TRUE )) {
               dwError = GetLastError();
               if(dwError == ERROR_IO_INCOMPLETE)
                  // normal result if not finished
                  continue;
               else {
                  // an error occurred, try to recover
                  wsprintf( szError, "<CE-%u>", dwError ) ;
//                  WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
                  ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
                  if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo )) {
	                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//	                  WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
                  }
                  break;
               }

            }

	      } else {
            // some other error occurred
            dwLength = 0 ;
            ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
            if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo )) {
	            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//	            WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
            }
         }
      }
   }

   return ( dwLength ) ;

} // end of ReadCommBlock()

//---------------------------------------------------------------------------
//  BOOL NEAR WriteCommBlock( HWND hWnd, BYTE *pByte )
//
//  Description:
//     Writes a block of data to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE *pByte
//        pointer to data to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------
Boolean WriteCommBlock (LPSTR lpByte , UInt32 dwBytesToWrite)
{
   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
//   NPTTYINFO   npTTYInfo ;
   DWORD       dwErrorFlags;
   DWORD   	dwError;
   DWORD       dwBytesSent=0;
   COMSTAT     ComStat;
   char        szError[ 128 ] ;


//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

   fWriteStat = WriteFile( COMDEV( npTTYInfo ), lpByte, dwBytesToWrite,
                           &dwBytesWritten, &WRITE_OS( npTTYInfo ) ) ;

   // Note that normally the code will not execute the following
   // because the driver caches write operations. Small I/O requests
   // (up to several thousand bytes) will normally be accepted
   // immediately and WriteFile will return true even though an
   // overlapped operation was specified

   if (!fWriteStat) {
      if(GetLastError() == ERROR_IO_PENDING) {
         // We should wait for the completion of the write operation
         // so we know if it worked or not

         // This is only one way to do this. It might be beneficial to
         // place the write operation in a separate thread
         // so that blocking on completion will not negatively
         // affect the responsiveness of the UI

         // If the write takes too long to complete, this
         // function will timeout according to the
         // CommTimeOuts.WriteTotalTimeoutMultiplier variable.
         // This code logs the timeout but does not retry
         // the write.

         while(!GetOverlappedResult( COMDEV( npTTYInfo ),
            &WRITE_OS( npTTYInfo ), &dwBytesWritten, TRUE )) {
            dwError = GetLastError();
            if(dwError == ERROR_IO_INCOMPLETE) {
               // normal result if not finished
               dwBytesSent += dwBytesWritten;
               continue;
            } else {
               // an error occurred, try to recover
               wsprintf( szError, "<CE-%u>", dwError ) ;
//               WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
               ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
               if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
               {
                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//                  WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
               }
               break;
            }
         }

         dwBytesSent += dwBytesWritten;

         if( dwBytesSent != dwBytesToWrite )
             wsprintf(szError,"\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
         else
             wsprintf(szError,"\n%ld bytes written", dwBytesSent);

         OutputDebugString(szError);

      } else {
         // some other error occurred
         ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
         if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo )) {
            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//            WriteTTYBlock( hwnd, szError, lstrlen( szError ) ) ;
         }
         return ( FALSE );
      }
   }
   return ( TRUE ) ;

} // end of WriteCommBlock()

//************************************************************************
//  DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
//
//  Description:
//     A secondary thread that will watch for COMM events.
//
//  Parameters:
//     LPSTR lpData
//        32-bit pointer argument
//
//  Win-32 Porting Issues:
//     - Added this thread to watch the communications device and
//       post notifications to the associated window.
//
//************************************************************************
DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
{
   DWORD       dwEvtMask ;
   NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;
	UInt32			nLength;
	UInt32			hLength = strlen (WisHeader), tLength = strlen (WisTailer) ;
//   BYTE       abIn[ MAXBLOCK + 1] ;
   BYTE       abIn[ 512 + 1] ;

   memset( &os, 0, sizeof( OVERLAPPED ) ) ;

   // create I/O event used for overlapped read

   os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
   if (os.hEvent == NULL) {
      MessageBox( NULL, "Failed to create event for thread!", "TTY Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
      return ( FALSE ) ;
   }

   if (!SetCommMask( COMDEV( npTTYInfo ), EV_RXCHAR ))
      return ( FALSE ) ;

   while ( CONNECTED( npTTYInfo ) ) {
      dwEvtMask = 0 ;

      WaitCommEvent( COMDEV( npTTYInfo ), &dwEvtMask, NULL );

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR) {
			if ( readExclusive ) {	// send data now
				if (nLength = ReadCommBlock((LPSTR) abIn, 2 )) {
					if ( (abIn[0] == 0xFA) && (abIn[1] == 0xAF) ) {
						writeExclusive = TRUE;
						readExclusive = FALSE;
					}
				}
			} else {		// receive data now
				if (nLength = ReadCommBlock((LPSTR) abIn, hLength )) {
//					WriteTTYBlock( hwnd, (LPSTR) abIn, nLength ) ;
					if ( (nLength == hLength) && (!strncmp (abIn, WisHeader, nLength)) ){
						// hand shaking successful, set handShaking flag
						// hand shaking successful, start receive data here
//						ReceiveData ();
					}
				}
			}
      }
   }

   // get rid of event handle
   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")
   THREADID( npTTYInfo ) = 0 ;
   HTHREAD( npTTYInfo ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()

//---------------------------------------------------------------------------
//  BOOL CloseConnection( HWND hWnd )
//
//  Description:
//     Closes the connection to the port.  Resets the connect flag
//     in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to stop secondary thread.  SetCommMask() will signal the
//       WaitCommEvent() event and the thread will halt when the
//       CONNECTED() flag is clear.
//     - Use new PurgeComm() API to clear communications driver before
//       closing device.
//
//---------------------------------------------------------------------------
Boolean CloseConnection()
{
   HMENU      hMenu ;
//   NPTTYINFO  npTTYInfo ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

   // set connected flag to FALSE
   CONNECTED( npTTYInfo ) = FALSE ;

   // disable event notification and wait for thread
   // to halt
   SetCommMask( COMDEV( npTTYInfo ), 0 ) ;

   // block until thread has been halted
   while(THREADID(npTTYInfo) != 0);

   // drop DTR
   EscapeCommFunction( COMDEV( npTTYInfo ), CLRDTR ) ;

   // purge any outstanding reads/writes and close device handle
   PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                   PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   CloseHandle( COMDEV( npTTYInfo ) ) ;

   // change the selectable items in the menu
   hMenu = GetMenu( hwnd ) ;
   EnableMenuItem( hMenu, IDM_DISCONNECT,
                   MF_GRAYED | MF_DISABLED | MF_BYCOMMAND ) ;
   EnableMenuItem( hMenu, IDM_CONNECT,
                   MF_ENABLED | MF_BYCOMMAND ) ;

   return ( TRUE ) ;

} // end of CloseConnection()

//---------------------------------------------------------------------------
//  BOOL OpenConnection( HWND hWnd )
//
//  Description:
//     Opens communication port specified in the TTYINFO struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - OpenComm() is not supported under Win-32.  Use CreateFile()
//       and setup for OVERLAPPED_IO.
//     - Win-32 has specific communication timeout parameters.
//     - Created the secondary thread for event notification.
//
//---------------------------------------------------------------------------
Boolean OpenConnection(UInt16 port, UInt32 baud)
{
   char       szPort[ 15 ];
   BOOL       fRetVal ;
//   NPTTYINFO  npTTYInfo ;
   HANDLE        hCommWatchThread ;
   DWORD         dwThreadID ;

//   if (NULL == (npTTYInfo = GETNPTTYINFO( hwnd )))
//      return ( FALSE ) ;

	BAUDRATE( npTTYInfo ) = baud;

   // load the COM prefix string and append port number
   PORT (npTTYInfo) = (BYTE)port;
   wsprintf( szPort, "COM%d", PORT( npTTYInfo ) ) ;

   // open COMM device
   if ((COMDEV( npTTYInfo ) =
      CreateFile( szPort, GENERIC_READ | GENERIC_WRITE,
                  0,                    // exclusive access
                  NULL,                 // no security attrs
                  OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL |
                  FILE_FLAG_OVERLAPPED, // overlapped I/O
                  NULL )) == (HANDLE) -1 )
      return ( FALSE ) ;
   else {
		SetupTimeout (baud, 0xFFFFFFFF);
   }

   fRetVal = SetupConnection () ;

   if (fRetVal) {
      CONNECTED( npTTYInfo ) = TRUE ;

      // Create a secondary thread
      // to watch for an event.

      if (NULL == (hCommWatchThread =
                      CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
                                    0,
                                    (LPTHREAD_START_ROUTINE) CommWatchProc,
                                    (LPVOID) npTTYInfo,
                                    0, &dwThreadID ))) {
         CONNECTED( npTTYInfo ) = FALSE ;
         CloseHandle( COMDEV( npTTYInfo ) ) ;
         fRetVal = FALSE ;
      } else {
         THREADID( npTTYInfo ) = dwThreadID ;
         HTHREAD( npTTYInfo ) = hCommWatchThread ;

         // assert DTR
         EscapeCommFunction( COMDEV( npTTYInfo ), SETDTR ) ;
      }
   } else {
      CONNECTED( npTTYInfo ) = FALSE ;
      CloseHandle( COMDEV( npTTYInfo ) ) ;
   }

   return ( fRetVal ) ;
} // end of OpenConnection()

// Below APIs are graphic relative API
/*
void SetDrawMode (char mode)
{
	copyMode = mode;
}

unsigned char VSetTextColor (unsigned char color)
{
	unsigned char	oldColor = tColor;

	tColor = color;
	return	oldColor;
}
*/
////////////////////////////////////////////////////////////////////////
// FUNCTION:    WClearScreen
//
// DESCRIPTION: This routine clear screen.
//
// PARAMETERS:  (int) mode - clear screen mode,		
//										SCREEN_ALL for all screen, 
//										SCREEN_DISPLAY for display area
//										(keep system button and hw area)
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/25/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WClearScreen (int mode)
{ 
	RectangleType	rect;

	rect.topLeft.x = PDASTARTX;
	rect.topLeft.y = PDASTARTY;

	if ( mode == SCREEN_DISPLAY ) {
		rect.extent.x = PDAWIDTH;
		rect.extent.y = PDAHEIGHT;
	} else if ( mode == SCREEN_ALL) {
		rect.extent.x = PDAWIDTH;
		rect.extent.y = PDAHEIGHT*4/3;
	}

	VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VSaveRegion
//
// DESCRIPTION: This routine save the region
//
// PARAMETERS:  (const RectangleType *) rect - the region to save
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/15/01		Initial Revision
//			Jerry	3/21/01		Modify VRect to RectangleType
//			Jerry	3/29/01		Can save and redraw more than 1 region
//								add bitmap queue to system, use memBM[4]
//								to save client region.
////////////////////////////////////////////////////////////////////////
void VSaveRegion(const RectangleType *rP, int mode)
{
	HBITMAP		oldbitmap;
	RectangleType	rect;


	if ( rP ) {	// redraw the rectangle
		if ( mode == COORD_STRETCH )
			VPDAToSysRect (&rect, rP);
		else
			Vmemcpy (&rect, rP, sizeof(RectangleType));
		memBM[BitmapIndex] = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight );
		oldbitmap = SelectObject(memDC, memBM[BitmapIndex]);
		BitBlt (memDC, rect.topLeft.x, rect.topLeft.y, rect.extent.x+1, 
				rect.extent.y+1, hdc, rect.topLeft.x, rect.topLeft.y, SRCCOPY);
		BitmapIndex++;
	} else {		// redraw the entire screen
		memBM[4] = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight );
		oldbitmap = SelectObject(memDC, memBM[4]);
		BitBlt (memDC, 0, 0, ScreenWidth, ScreenHeight, hdc, 0, 0, SRCCOPY);
	}

	SelectObject(memDC, oldbitmap);
	DeleteObject (oldbitmap);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VRedrawRegion
//
// DESCRIPTION: This routine repaint the saved region
//
// PARAMETERS:  (const RectangleType *) rect - the region to recdraw
//
// RETURNED:    Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/15/01		Initial Revision
//			Jerry	3/21/01		Modify VRect to RectangleType
//			Jerry	3/29/01		Can save and redraw more than 1 region
//								add bitmap queue to system, use memBM[4]
//								to save client region.
////////////////////////////////////////////////////////////////////////
void VRedrawRegion(const RectangleType *rP, int mode) 
{
	HBITMAP oldbitmap;
	RectangleType	rect;

	if ( rP ) {	// redraw the rectangle
		if ( mode == COORD_STRETCH )
			VPDAToSysRect (&rect, rP);
		else
			Vmemcpy (&rect, rP, sizeof(RectangleType));
		if ( BitmapIndex == 0 ) {
			return;
		}
		oldbitmap = (HBITMAP)SelectObject (memDC, memBM[--BitmapIndex]);
		BitBlt (hdc, rect.topLeft.x, rect.topLeft.y, rect.extent.x+1, 
				rect.extent.y+1, memDC, rect.topLeft.x, rect.topLeft.y, SRCCOPY);
		DeleteObject (memBM[BitmapIndex]);
	} else {		// redraw the entire screen
		oldbitmap = (HBITMAP)SelectObject (memDC, memBM[4]);
		BitBlt (hdc, 0, 0, ScreenWidth, ScreenHeight, memDC, 0, 0, SRCCOPY);
		DeleteObject (memBM[4]);
	}

	SelectObject (memDC, oldbitmap);
	DeleteObject (oldbitmap);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawBackground
//
// DESCRIPTION: This routine clear entire client window and draw
//					 PDA outline.
//
// PARAMETERS:  
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawBackground ()
{
	HBITMAP oldbitmap, bitmap;

	bitmap = (HBITMAP)LoadImage( NULL,
                                 CISBMPNAME,
                                 IMAGE_BITMAP,
                                 0,
                                 0,
                                 LR_LOADFROMFILE | LR_CREATEDIBSECTION );

	oldbitmap = (HBITMAP)SelectObject (memDC, bitmap);
	BitBlt (hdc, 0, 0, ScreenWidth, ScreenHeight, memDC, 0, 0, SRCCOPY);
	SelectObject (memDC, oldbitmap);
	DeleteObject (oldbitmap);
	DeleteObject (bitmap);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawBitmap
//
// DESCRIPTION: This routine draw a bitmap in speicfied position.
//
// PARAMETERS:  (int) x - The Left position of bitmap.
//					 (int) y - The Top position of bitmap.
//					 (char *) filename - filename of bitmap.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawBitmap (int x, int y, char *filename)
{
	HBITMAP oldbitmap, bitmap;
	BITMAP	bmp;

	bitmap = (HBITMAP)LoadImage( NULL,
                                 filename,
                                 IMAGE_BITMAP,
                                 0,
                                 0,
                                 LR_LOADFROMFILE | LR_CREATEDIBSECTION );

	GetObject (bitmap, sizeof(BITMAP), &bmp);
	oldbitmap = (HBITMAP)SelectObject (memDC, bitmap);
	StretchBlt (hdc, VPDAToSysXCoord(x), VPDAToSysYCoord(y), 
					VPDAToSysXRes(bmp.bmWidth), VPDAToSysYRes(bmp.bmHeight), 
					memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCAND);
	SelectObject (memDC, oldbitmap);
	DeleteObject (oldbitmap);
	DeleteObject (bitmap);
}

Int16 VDrawChar (WChar ch, Coord x, Coord y)
{
	unsigned short	offset;
	int		width;
	unsigned short	byte;
	IMAGEBITS *bits;
	int		i, j;

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, WRGB(200, 200, 200));
	offset = currentFont->offset[(ch-0x20)];
	width = currentFont->width[(ch-0x20)];
	bits = helvR10_bits + (ch-0x20)*12;

	for ( i = 0; i < currentFont->height; i++, bits++ ) {
		byte = ((*bits)&0xff00);
		if ( !byte )
			continue;
		for ( j = 0; j < 8; j++ ) {
			if ( byte & 0x8000 ) {
				VDrawPixel ((Coord)(x+j),(Coord)(y+i),tColor);
			}
			byte = byte << 1;
		}
	}

	return	width+1;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawChars
//
// DESCRIPTION: This routine draw a cursor in speicfied position.
//
// PARAMETERS:  (const Char *) chars - Pointer to character string.
//					 (Int16) len - length of character string.
//					 (Coord) x - The Left position of string.
//					 (Coord) y - The Top position of string.
//					 (int) mode - Mode of coordinate system.
//
// RETURNED:    Returns the width of characters. (In pixels)
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
//			Jerry	11/25/01	Add mode option
//////////////////////////////////////////////////////////////////////////////
Int16 VDrawChars (const Char *string, Int16 length, Coord x, Coord y, int mode)
{
	Int16	width=0;
	int	k;

	SetBkMode(hdc, TRANSPARENT);
	if ( mode == COORD_STRETCH ) {
		x = VPDAToSysXCoord (x);
		y = VPDAToSysXCoord (y);
	}

	for ( k = 0; k < length; k++ ) {
		// draw character
		if ( (string[k] < currentFont->firstchar) || 
			(string[k] > currentFont->size+currentFont->firstchar) ) 
			continue;

		width += (VDrawChar (string[k], (Coord)(x+width), y));
	}	// end of for (k)

	return	width;
}

int	curCounts=0;
Coord	oldX=-20,oldY=-20;
Boolean	cursorState=false;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawCursor
//
// DESCRIPTION: This routine draw a cursor in speicfied position.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//					 (int) mode - Mode of drawing cursor
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
//			Jerry	8/28/01	Add erase cursor function
//			Jerry	11/22/01	Add mode option
////////////////////////////////////////////////////////////////////////
void VDrawCursor (Coord x, Coord y, int mode)
{
	HPEN	pen, oldpen;

	x = x+SCREENXBASE;
	y = VPDAToSysYCoord (y);

	// if Cursor exists, clear cursor
	//	clear previous cursor
	pen = CreatePen(PS_SOLID, 1, WRGB(123, 140, 90) );
	oldpen = (HPEN)SelectObject (hdc, pen);
	MoveToEx (hdc, oldX, oldY, NULL);
	LineTo (hdc, oldX, oldY+CursorSize);
	SelectObject (hdc, oldpen);
	DeleteObject(pen);
	DeleteObject(oldpen);

	if ( cursorState && (mode == CUR_DRAW) ) {
		// draw current cursor
		pen = CreatePen(PS_SOLID, 1, WRGB(0, 0, 0) );
		oldpen = SelectObject (hdc, pen);
		MoveToEx (hdc, x, y, NULL);
		LineTo (hdc, x, y+CursorSize);
		SelectObject (hdc, oldpen);
		DeleteObject(pen);
		DeleteObject(oldpen);
		oldX = x;
		oldY = y;
	}

	curCounts++;
	if ( curCounts == 3 ) {
		cursorState = !cursorState;
		curCounts = 0;
	}
}

int	oldGrfState=-1;
void VDrawGrafState (Boolean drawMode)
{
	RectangleType	rect;

	if ( !drawMode ) {
		rect.topLeft.x = SysPanelVLine1+1;
		rect.topLeft.y = SysPanelEndY-12;
		rect.extent.x = 11;
		rect.extent.y = 11;
		VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_NORMAL, DRAW_SET);
		return;
	}

	if ( oldGrfState != grfState.sysTempShift ) {
		rect.topLeft.x = SysPanelVLine1+1;
		rect.topLeft.y = SysPanelEndY-12;
		rect.extent.x = 11;
		rect.extent.y = 11;
		VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_NORMAL, DRAW_SET);
		switch (grfState.sysTempShift) {
			case 0:
				VDrawChar ('a', (Coord)(rect.topLeft.x+1), rect.topLeft.y);
				break;
			case 1:
				VDrawChar ('A', (Coord)(rect.topLeft.x+1), rect.topLeft.y);
				break;
			case 9:
				VDrawChar ('S', (Coord)(rect.topLeft.x+1), rect.topLeft.y);
				break;
			default:
				break;
		}
	} 

	oldGrfState = grfState.sysTempShift;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawPixel
//
// DESCRIPTION: This routine draw a pixel in speicfied position.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//					 (UInt32) color - The color of pixel.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawPixel (Coord x, Coord y, UInt32 color)
{

	SetPixel (hdc, x, y, color);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetPixel
//
// DESCRIPTION: This routine get the color of specified pixel.
//
// PARAMETERS:  (Coord) x - The Left position of cursor.
//					 (Coord) y - The Top position of cursor.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt8 VGetPixel (Coord x, Coord y)
{
	UInt32	color;

	color = GetPixel (hdc, x, y);

	if ( color == FOREGROUNDCOLOR ) {
		return	1;
	} else if ( color == BACKGROUNDCOLOR ) {
		return	0;
	}

	return	0;
}

void VDrawCheck (Coord StartX, Coord StartY, Boolean Style)
{
	StartX = VPDAToSysXCoord (StartX);
	StartY = VPDAToSysYCoord (StartY);
	if ( Style ) {
		MoveToEx (hdc, StartX+2, StartY+4, NULL);
		LineTo (hdc, StartX+6, StartY+12);
		LineTo (hdc, StartX+12, StartY);
		
		MoveToEx (hdc, StartX+3, StartY+3, NULL);
		LineTo (hdc, StartX+7, StartY+12);
		if ( StartY > 1 ) {
			LineTo (hdc, StartX+13, StartY-1);
		} else {
			LineTo (hdc, StartX+13, StartY);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    drawline
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (Coord) StartX - the X coordinate of start point
//					 (Coord) StartY - the Y coordinate of start point
//					 (Coord) EndX - the X coordinate of end point
//					 (Coord) EndY - the Y coordinate of end point
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	9/25/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void drawline (Coord x0, Coord y0, Coord x1, Coord y1)
{
	MoveToEx (hdc, x0, y0, NULL);
	LineTo (hdc, x1, y1);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawLine
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (Coord) StartX - the X coordinate of start point
//					 (Coord) StartY - the Y coordinate of start point
//					 (Coord) EndX - the X coordinate of end point
//					 (Coord) EndY - the Y coordinate of end point
//					 (UInt16) width - The width of pen to draw
//					 (UInt32) color - the color of pen to draw
//					 (Int16) penStyle - the style of pen to draw
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/12/01	Initial Revision
//			Jerry 5/06/01	Add Color parameter
//			Jerry	8/09/01	Add width parameter
////////////////////////////////////////////////////////////////////////
void VDrawLine (Coord StartX, Coord StartY, Coord EndX, Coord EndY, 
					 UInt16 width, UInt32 color, Int penStyle)
{
	HPEN	pen = CreatePen(penStyle, 1, color);
	HPEN	oldpen = (HPEN)SelectObject (hdc, pen);
	int	i;
 

	if ( StartX == EndX ) {
		for ( i = 0; i < width; i++ ) {
			MoveToEx (hdc, VPDAToSysXCoord(StartX)+i, VPDAToSysYCoord(StartY), NULL);
			LineTo (hdc, VPDAToSysXCoord(EndX)+i, VPDAToSysYCoord(EndY));
		}
	} else {
		for ( i = 0; i < width; i++ ) {
			MoveToEx (hdc, VPDAToSysXCoord(StartX), VPDAToSysYCoord(StartY)+i, NULL);
			LineTo (hdc, VPDAToSysXCoord(EndX), VPDAToSysYCoord(EndY)+i);
		}
	}
	SelectObject (hdc, oldpen);
	DeleteObject(pen);
	DeleteObject(oldpen);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawRect
//
// DESCRIPTION: This routine draw a rectangle on the screen
//
// PARAMETERS:  (RectangleType) rect - rectangle start point and width,Height.
//					 (Int16) penStyle - the style of pen to draw
//					 (UInt16) cornerDiam - Radius of rounded corners. Specify zero
//										for square corners.
//					 (Boolean) bBackground - TURE draw the background with normal
//										color(SRCCOPY), FALSE draw the background with 
//										reverse color (SRCINVERT)
//					 (int) mode -	RECT_NORMAL for no stretch
//										COORD_STRETCH for stretch all rectangle
//										RECT_PARTSTRETCH for stretch topleft point
// 
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/12/01	Initial Revision
//			Jerry	3/20/01	Modify VRect to RectangleType
//			Jerry	3/23/01	Add penstyle parameter
//			Jerry 5/07/01	Add cornerDiam parameter
//			Jerry 7/24/01	Active cornerDiam
//			Jerry	11/23/01	Add Background and mode option
//////////////////////////////////////////////////////////////////////////////
void VDrawRect (RectangleType *rP, UInt16 penStyle, UInt16 cornerDiam, 
					 Boolean bBackground, char coordMode, char drawMode)
{
	HBITMAP		dcBitmap, oldBitmap;
	HPEN			pen, oldpen;
	RectangleType	rect;
	unsigned long	color;

	if ( penStyle == PS_SOLID ) {
		dcBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight );
		oldBitmap = SelectObject (memDC, dcBitmap);
	}

	// strecth the rectangle size by input mode
	if (coordMode == COORD_STRETCH) {
		VPDAToSysRect (&rect, rP);
		cornerDiam = VPDAToSysXRes (cornerDiam);
	} else if ( coordMode == COORD_PARTSTRETCH ) {
		VPDAToSysPoint (&(rect.topLeft), &(rP->topLeft));
		Vmemcpy (&(rect.extent), &(rP->extent), sizeof(PointType));
	} else {
		Vmemcpy (&rect, rP, sizeof(RectangleType));
	}

	// maximum cornerDiam is 20
	if ( cornerDiam > 20 )	cornerDiam = 20;

	// decide the color by input bBackground color
	if ( bBackground )
		color = WRGB(123, 140, 90);
	else
		color = WRGB(0, 0, 0);

	// DRAW_XOR mode, clear the background with white color first
	if ( drawMode == DRAW_XOR ) {
		int	y;

		color = WRGB(0, 0, 0);
		pen = CreatePen(penStyle, 1, color);
		oldpen = (HPEN)SelectObject (memDC, pen);
		for ( y = 0; y <= rect.extent.y; y++ ) {
			MoveToEx (memDC, rect.topLeft.x, rect.topLeft.y+y, NULL);
			LineTo (memDC, (rect.topLeft.x+rect.extent.x+1), rect.topLeft.y+y);
		}
		(HPEN)SelectObject (memDC, oldpen);
		DeleteObject (oldpen);
		DeleteObject (pen);
		color = WRGB(123, 140, 90);
	} else {
		int	y;
		unsigned long	tColor;

		tColor = WRGB(123, 140, 90);
		pen = CreatePen(penStyle, 1, tColor);
		oldpen = (HPEN)SelectObject (memDC, pen);
		for ( y = 0; y <= rect.extent.y; y++ ) {
			MoveToEx (memDC, rect.topLeft.x, rect.topLeft.y+y, NULL);
			LineTo (memDC, (rect.topLeft.x+rect.extent.x+1), rect.topLeft.y+y);
		}
		(HPEN)SelectObject (memDC, oldpen);
		DeleteObject (oldpen);
		DeleteObject (pen);
	}

	pen = CreatePen(penStyle, 1, color);
	if ( penStyle == PS_SOLID )
		oldpen = (HPEN)SelectObject (memDC, pen);
	else
		oldpen = (HPEN)SelectObject (hdc, pen);

	if ( cornerDiam == 0 ) {
		if ( penStyle == PS_SOLID ) {		// draw a filled rectangle
			int	y;
			
			for ( y = 0; y <= rect.extent.y; y++ ) {
				MoveToEx (memDC, rect.topLeft.x, rect.topLeft.y+y, NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x), rect.topLeft.y+y);
			}
		} else {
			MoveToEx (hdc, rect.topLeft.x, rect.topLeft.y, NULL);
			LineTo (hdc, rect.topLeft.x+rect.extent.x, rect.topLeft.y);
			LineTo (hdc, rect.topLeft.x+rect.extent.x, rect.topLeft.y+rect.extent.y);
			LineTo (hdc, rect.topLeft.x, rect.topLeft.y+rect.extent.y);
			LineTo (hdc, rect.topLeft.x, rect.topLeft.y);
		}
	} else {
		int	y, x1, x2;
		int	index=(cornerDiam*(cornerDiam-1)/2);

		if ( penStyle == PS_SOLID ) {		// draw a filled rectangle
			// draw four corner
			for ( y = 0; y <= cornerDiam; y++ ) {
				x1 = roundX[index+y];

				// draw the four corners of rectangle
				MoveToEx (memDC, (rect.topLeft.x+(cornerDiam-x1)), rect.topLeft.y+y, NULL);
				LineTo (memDC, (rect.topLeft.x+cornerDiam), rect.topLeft.y+y);
				MoveToEx (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+1), rect.topLeft.y+y, NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+x1+1), rect.topLeft.y+y);
				MoveToEx (memDC, (rect.topLeft.x+(cornerDiam-x1)), (rect.topLeft.y+rect.extent.y-y), NULL);
				LineTo (memDC, (rect.topLeft.x+cornerDiam), (rect.topLeft.y+rect.extent.y-y));
				MoveToEx (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+1), (rect.topLeft.y+rect.extent.y-y), NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+x1+1), (rect.topLeft.y+rect.extent.y-y));

			}

			// draw other area
			for ( y = 0; y <= cornerDiam; y++ ) {
				MoveToEx (memDC, (rect.topLeft.x+cornerDiam-1), rect.topLeft.y+y, NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+1), rect.topLeft.y+y);
				MoveToEx (memDC, (rect.topLeft.x+cornerDiam-1), (rect.topLeft.y+rect.extent.y-y), NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x-cornerDiam+1), (rect.topLeft.y+rect.extent.y-y));
			}

			for ( y = cornerDiam; y <= rect.extent.y-cornerDiam; y++ ) {
				MoveToEx (memDC, (rect.topLeft.x), rect.topLeft.y+y, NULL);
				LineTo (memDC, (rect.topLeft.x+rect.extent.x+1), rect.topLeft.y+y);
			}
		} else {		// draw a outline rectangle
			// draw 4 lines
			drawline ( (Coord)(rect.topLeft.x+cornerDiam-roundX[index]), 
						  (Coord)(rect.topLeft.y),
						  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+roundX[index]),
						  (Coord)(rect.topLeft.y));

			drawline ( (Coord)(rect.topLeft.x+cornerDiam-roundX[index]), 
						  (Coord)(rect.topLeft.y+rect.extent.y),
						  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+roundX[index]),
						  (Coord)(rect.topLeft.y+rect.extent.y));

			drawline ( (Coord)(rect.topLeft.x), 
						  (Coord)(rect.topLeft.y+cornerDiam-1),
						  (Coord)(rect.topLeft.x),
						  (Coord)(rect.topLeft.y+rect.extent.y-cornerDiam+2));

			drawline ( (Coord)(rect.topLeft.x+rect.extent.x), 
						  (Coord)(rect.topLeft.y+cornerDiam-1),
						  (Coord)(rect.topLeft.x+rect.extent.x),
						  (Coord)(rect.topLeft.y+rect.extent.y-cornerDiam+2));

			// draw 4 corners
			for ( y = 0; y < cornerDiam-1; y++ ) {
				x1 = roundX[index+y];
				x2 = roundX[index+y+1];

				// draw left top corner
				drawline ( (Coord)(rect.topLeft.x+(cornerDiam-x1)), 
							  (Coord)(rect.topLeft.y+y),
							  (Coord)(rect.topLeft.x+(cornerDiam-x2)), 
							  (Coord)(rect.topLeft.y+y+1));

				// draw right top corner
				drawline ( (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+x1), 
							  (Coord)(rect.topLeft.y+y),
							  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+x2), 
							  (Coord)(rect.topLeft.y+y+1));

				// draw left bottom corner
				drawline ( (Coord)(rect.topLeft.x+(cornerDiam-x1)), 
							  (Coord)(rect.topLeft.y+rect.extent.y-y),
							  (Coord)(rect.topLeft.x+(cornerDiam-x2)), 
							  (Coord)(rect.topLeft.y+rect.extent.y-y-1));

				// draw right bottom corner
				drawline ( (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+x1), 
							  (Coord)(rect.topLeft.y+rect.extent.y-y),
							  (Coord)(rect.topLeft.x+rect.extent.x-cornerDiam+x2), 
							  (Coord)(rect.topLeft.y+rect.extent.y-y-1));
			}
		}
	}

	// set the drawing mode
	if ( penStyle == PS_SOLID ) {
	if ( drawMode == DRAW_XOR ) {
		BitBlt (hdc, rect.topLeft.x, rect.topLeft.y, rect.extent.x+1, 
				rect.extent.y+1, memDC, rect.topLeft.x, rect.topLeft.y, SRCINVERT);
	} else {
		BitBlt (hdc, rect.topLeft.x, rect.topLeft.y, rect.extent.x+1, 
				rect.extent.y+1, memDC, rect.topLeft.x, rect.topLeft.y, SRCCOPY);
	}

	SelectObject (memDC, oldBitmap);
	SelectObject (memDC, oldpen);
	DeleteObject (dcBitmap);
	DeleteObject (oldBitmap);
	}
	DeleteObject(pen);
	DeleteObject(oldpen);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawUpArrow
//
// DESCRIPTION: This routine draw a up direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/26/01	Initial Revision
//			Jerry	8/09/01	Add SOLID_TAIL, SOLID_SMALL style
////////////////////////////////////////////////////////////////////////
void VDrawUpArrow (int x, int y, int style)
{
	int		i;

	x = VPDAToSysXCoord (x);
	y = VPDAToSysYCoord (y);
	if ( style == SOLID_LARGE ) {	// up direction solid triangle
		for ( i = 8; i >= 0; i-- ) {
			MoveToEx (hdc, x+8-i, y+i, NULL);
			LineTo (hdc, x+10+i, y+i);
		}
 	} else if ( style == DASH_LARGE ) {	// up direction triangle
		for ( i = 8; i >= 0; i-=2 ) {
			MoveToEx (hdc, x+8-i, y+i, NULL);
			LineTo (hdc, x+10+i, y+i);
		}
	} else if ( style == SOLID_SMALL ) {	// up direction solid triangle
		for ( i = 6; i >= 0; i-- ) {
			MoveToEx (hdc, x+6-i, y+i, NULL);
			LineTo (hdc, x+8+i, y+i);
		}
	} else if ( style == SOLID_TAIL ) {	// up direction arrow (with tail)
		for ( i = 8; i >= 6; i-- ) {
			MoveToEx (hdc, x+6, y+i, NULL);
			LineTo (hdc, x+12, y+i);
		}
		for ( i = 5; i >= 0; i-- ) {
			MoveToEx (hdc, x+8-i, y+i, NULL);
			LineTo (hdc, x+10+i, y+i);
		}
	}

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawDownArrow
//
// DESCRIPTION: This routine draw a down direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/26/01	Initial Revision
//			Jerry	8/09/01	Add SOLID_TAIL, SOLID_SMALL style
////////////////////////////////////////////////////////////////////////
void VDrawDownArrow (int x, int y, int style)
{
	int		i;
	
	x = VPDAToSysXCoord (x);
	y = VPDAToSysYCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 0; i <= 8; i++ ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+18-i, y+i);
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 0; i <= 8; i+=2 ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+18-i, y+i);
		}
	} else if ( style == SOLID_SMALL ) {
		for ( i = 0; i <= 6; i++ ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+14-i, y+i);
		}
	} else if ( style == SOLID_TAIL ) {	// up direction arrow (with tail)
		for ( i = 0; i < 3; i++ ) {
			MoveToEx (hdc, x+6, y+i, NULL);
			LineTo (hdc, x+12, y+i);
		}
		for ( i = 3; i <= 8; i++ ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+18-i, y+i);
		}
	}

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawLeftArrow
//
// DESCRIPTION: This routine draw a left direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawLeftArrow (int x, int y, int style)
{
	int		i;
	
	x = VPDAToSysXCoord (x);
	y = VPDAToSysYCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 8; i >= 0; i-- ) {
			MoveToEx (hdc, x+i, y+8-i, NULL);
			LineTo (hdc, x+i, y+10+i);
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 8; i >= 0; i-=2 ) {
			MoveToEx (hdc, x+i, y+8-i, NULL);
			LineTo (hdc, x+i, y+10+i);
		}
	}

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawRightArrow
//
// DESCRIPTION: This routine draw a right direction arrow (triangle) 
//					 on the screen.
//
// PARAMETERS:  (int) x - The x coordinate of top left point.
//					 (int) y - The y coordinate of top left point.
//					 (int) style - The style of arrow (triangle).
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VDrawRightArrow (int x, int y, int style)
{
	int		i;
	
	x = VPDAToSysXCoord (x);
	y = VPDAToSysYCoord (y);
	if ( style == SOLID_LARGE ) {
		for ( i = 0; i <= 8; i++ ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+i, y+18-i);
		}
	} else if ( style == DASH_LARGE ) {
		for ( i = 0; i <= 8; i+=2 ) {
			MoveToEx (hdc, x+i, y+i, NULL);
			LineTo (hdc, x+i, y+18-i);
		}
	}

}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VDrawString
//
// DESCRIPTION: This routine clear entire client window and draw
//					 PDA outline.
//
// PARAMETERS:  (UInt16) x - the left coordinate to draw string
//					 (UInt16) y - the top coordinate to draw string
//					 (Char *) str - the string to draw
//					 (UInt32) length - lenght of string
//					 (Boolean) singleline - true if it's a single line
//							control, false if multiline
//					 (Boolean) background - false if normal background
//							true if invert background
//					 (int) mode - RECT_NORMAL for no stretch
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/15/01	Initial Revision
//			Jerry 8/02/01	Modify buffer to variable size
//			Jerry	8/17/01	Cancel singleline function
//			Jerry	11/20/01	Add mode option
////////////////////////////////////////////////////////////////////////
void VDrawString( Coord x, Coord y,
                  const char *str,
                  UInt32 length,
						Boolean singleline,
						Boolean background,
						int mode)
{
	UInt16	index = 0, bindex = 0, sindex = 0, maxLength;

	SetBkMode(hdc, TRANSPARENT);
	// if background, change the pen to background color
	if ( background ) {
		SetTextColor (hdc, WRGB(123, 140, 90));
		tColor = WRGB(123, 140, 90);
	}

	// stretch the coordinate to proper value
	if ( mode == COORD_STRETCH ) {	
		x = VPDAToSysXCoord(x);
		y = VPDAToSysYCoord(y);
	}

	// parse the input text 
	while (index < length) {
		if ( str[index] == 0 ) {
			break;
		} else if ( str[index] != 0x0a ) {
			bindex++;
		} else {
			maxLength = FntWordWrap (str+sindex, (UInt16)(SCREENWIDTH-(x-SCREENXBASE)));
			if ( maxLength < bindex )
				bindex = maxLength;
			VDrawChars (str+sindex, bindex, (Coord)x, (Coord)y, COORD_NORMAL);
			sindex += bindex;
			bindex = 0;
			if ( singleline ) {
				if ( background ) {
					SetTextColor (hdc, WRGB(0, 0, 0));
				}
				return;
			} else {
				y += FntCharHeight();
			}
		}
		index++;
	};

	if ( bindex > 0 ) {
		maxLength = FntWordWrap (str+sindex, (UInt16)(SCREENWIDTH-(x-SCREENXBASE)));
		if ( maxLength < bindex )
			bindex = maxLength;
		VDrawChars (str+sindex, bindex, (Coord)x, (Coord)y, COORD_NORMAL);
	}

	if ( background ) {
		SetTextColor (hdc, WRGB(0, 0, 0));
		tColor = FOREGROUNDCOLOR;
	}

}
 
////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetCurrentDirectory
//
// DESCRIPTION: This routine Get the current directory.
//
// PARAMETERS:  (char *) directory - Pointer to the buffer to store
//										directory.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VGetCurrentDirectory (Char *directory)
{
	GetCurrentDirectory(256, directory);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    VGetSystemTime
//
// DESCRIPTION: This routine Get the system time.
//
// PARAMETERS:  (DateTimeType *) datetime - Pointer to the DateTimeType
//												structure.
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void VGetSystemTime (DateTimeType *datetime)
{
	SYSTEMTIME	systemtime;

	GetSystemTime (&systemtime);

	datetime->second = systemtime.wSecond;
	datetime->minute = systemtime.wMinute;
	datetime->hour = systemtime.wHour;
	datetime->day = systemtime.wDay;
	datetime->month = systemtime.wMonth;
	datetime->year = systemtime.wYear;
	datetime->weekDay = systemtime.wDayOfWeek;
}

void VSetSystemTime (const DateTimeType *datetime)
{
	SYSTEMTIME	systemtime;

	systemtime.wSecond = datetime->second;
	systemtime.wMinute = datetime->minute;
	systemtime.wHour = datetime->hour;
	systemtime.wDay = datetime->day;
	systemtime.wMonth = datetime->month;
	systemtime.wYear = datetime->year;
	systemtime.wDayOfWeek = datetime->weekDay;

	SetSystemTime (&systemtime);
}

/*----------------------------------
  match a keycode for hotkey system
  C.C.Wang 0725, 1999
 -----------------------------------*/
keycode VMatchKeyCode(WPARAM _wParam)
{
   return (keycode) vKeyMap[_wParam];
}

void WCloseAll ()
{
	int	i;
	Vfree (CurEvent);
	if ( GlobalText ) {
		Vfree (GlobalText);
		GlobalText = NULL;
	}

	for ( i = 0; i < 5; i++ ) {
		if ( memBM[i] ) {
			DeleteObject (memBM[i]);
		}
	}

	Finalize_recorder ();
	DeleteDC (memDC);
	ReleaseDC (hwnd, hdc);
}

double Vexp (double x)
{
	return	exp (x);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrToLower
//
// DESCRIPTION: This routine convert all the characters in a string
//				to lowercase.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* Vstrlwr (Char *dst, const Char* src)
{
//	dst = strlwr (src);
	return	dst;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstricmp
//
// DESCRIPTION: This routine compare two strings.
//					 (Not care of upper or lower case)
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//
// RETURNED:    Returns 0 if the strings match.
//					 Returns a positive number if s1 sorts after s2.
//					 Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 Vstricmp (const Char *dst, const Char* src)
{
	return	_stricmp (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrnicmp
//
// DESCRIPTION: This routine compare two strings out to n characters.
//					 (Not care of upper or lower case)
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//					 (UInt32) n - Length in bytes of txt to compare.
//
// RETURNED:    Returns 0 if the strings match.
//					 Returns a positive number if s1 sorts after s2.
//					 Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/23/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 Vstrnicmp (const Char *dst, const Char* src, UInt32 n)
{
	return	_strnicmp (dst, src, n);
}

void *VfopenTempFile()
{
	return	tmpfile();
}

void VRemoveTempFile ()
{
	_rmtmp ();
}

// Below APIs are system relative API, there are 4 functions now.
LRESULT NEAR CreateTTYInfo( HWND hWnd );
////////////////////////////////////////////////////////////////////////
// FUNCTION:    TimeDiff
//
// DESCRIPTION: This routine calculate the difference in millsecond 
//					 of two time.
//
// PARAMETERS:  (SYSTEMTIME *) time1 - The first time
//					 (SYSTEMTIME *) time2 - The second time
//
// RETURNED:    Returns the difference in millsecond of two time.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/01/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 TimeDiff (SYSTEMTIME *time1, SYSTEMTIME *time2)
{
	Int32	millSecond;
	
	millSecond = time1->wYear-time2->wYear;
	millSecond = millSecond*12 + (time1->wMonth-time2->wMonth);
	millSecond = millSecond*30 + (time1->wDay-time2->wDay);
	millSecond = millSecond*24 + (time1->wHour-time2->wHour);
	millSecond = millSecond*60 + (time1->wMinute-time2->wMinute);
	millSecond = millSecond*60 + (time1->wSecond-time2->wSecond);
	millSecond = millSecond*1000 + time1->wMilliseconds-time2->wMilliseconds;

	return	millSecond;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    MainProc
//
// DESCRIPTION: This routine is main window procedure to handle all event
//
// PARAMETERS:  (HWND) _hwnd - the handle of window
//					 (UINT) _msg - The ID of message
//				 	 (WPARAM) _wParam - The fisrt message parameter
//					 (LPARAM) _lParam - The second message parameter
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01	Initial Revision
//			Jerry	5/17/01	Add penDown option to Event
//			Jerry 7/31/01	Move event judgement to this routine.
//			Jerry	8/28/01	Modify to push the event to the queue
//			Jerry	8/29/01	Add push appStopEvent when receieve WM_DESTROY
////////////////////////////////////////////////////////////////////////
long FAR PASCAL MainProc(HWND _hwnd,      // window handle
                             UINT _msg,       // message ID
                             WPARAM _wParam,  // message parameter
                             LPARAM _lParam)  // message parameter
{
	static Boolean	redraw=false;
	static Boolean saved=false;
	static Boolean penDown=false;
	switch (_msg) {
		case WM_CREATE:
			CreateTTYInfo( _hwnd );
			break;

		case WM_CHAR:
			if ( ((WChar)_wParam >= 0x20)||((WChar)_wParam == 0x08) ) {
				CurEvent->eType = keyDownEvent;
				CurEvent->data.keyDown.chr = (WChar) _wParam;
				CurEvent->data.keyDown.keyCode = (WChar) _wParam;
				WPushEvent (CurEvent);
			} else if ( (WChar)_wParam == 0x0d ) {
				CurEvent->eType = keyDownEvent;
				CurEvent->data.keyDown.chr = (WChar) 0x0a;
				CurEvent->data.keyDown.keyCode = (WChar) 0x0a;
				WPushEvent (CurEvent);
			} else {
				return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
			}
			break;

		case WM_LBUTTONDOWN:
			if ( penDown ) {
				break;
			}
			// put left mouse button processing procedure here
			CurEvent->screenX = VSysToPDAXCoord(GET_X_LPARAM(_lParam)); 
			CurEvent->screenY = VSysToPDAYCoord(GET_Y_LPARAM(_lParam)); 
			penDown = true;

			WPeekMouseEvent (penDown);

			lastScreenX = CurEvent->screenX;
			lastScreenY = CurEvent->screenY;
			break;

		case WM_LBUTTONUP:
			if ( !penDown ) {
				break;
			}

			penDown = false;
			// put left mouse button processing procedure here
			CurEvent->screenX = VSysToPDAXCoord((GET_X_LPARAM(_lParam))); 
			CurEvent->screenY = VSysToPDAYCoord((GET_Y_LPARAM(_lParam))); 

			WPeekMouseEvent (penDown);
			lastScreenX = CurEvent->screenX;
			lastScreenY = CurEvent->screenY;
         break;

		case WM_MOUSEMOVE:
			if ( penDown ) {
				CurEvent->screenX = VSysToPDAXCoord(GET_X_LPARAM(_lParam)); 
				CurEvent->screenY = VSysToPDAYCoord(GET_Y_LPARAM(_lParam)); 
				
				WPeekMouseEvent (penDown);

				lastScreenX = CurEvent->screenX;
				lastScreenY = CurEvent->screenY;
			}
			break;

		case WM_COMMAND:
			break;

		case WM_CLOSE:
		case WM_DESTROY:
			CurEvent->eType = appStopEvent;
			WPushEvent (CurEvent);

			// post quit message to the window system
			PostQuitMessage(0);
			break;

		default :
			return DefWindowProc(_hwnd, _msg, _wParam, _lParam);
	}

	return 0L;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    CreateWindows
//
// DESCRIPTION: This routine cascades the specified child windows of 
//				the specified parent window.
//
// PARAMETERS:  (char *) appName - the application name of window
//				(char *) _caption - The caption of window
//				(int) X - the X coordinate of the window in the screen
//				(int) Y - the Y coordinate of the window in the screen
//				(int) Width - The width of window
//				(int) Height - The height of window
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void CreateWindows(char *appName, char* _caption, int X, int Y, int Width, int Height)
{
/*
	hwnd = CreateWindow(appName, _caption,
						WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE | WS_DLGFRAME,
						X, Y, Width, Height,
						NULL, NULL, vHInst, NULL);
*/
	hwnd = CreateWindowEx(WS_EX_TOPMOST, appName, _caption,
						WS_SYSMENU | WS_CLIPCHILDREN | WS_VISIBLE | WS_DLGFRAME,
						X, Y, Width, Height,
						NULL, NULL, vHInst, NULL);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WPeekInputsDDK
//
// DESCRIPTION: This routine peek system event
//
// PARAMETERS:  
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WPeekInputsDDK(void)
{
   MSG msg;

   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
			CurEvent->eType = appStopEvent;
			WPushEvent (CurEvent);
			return;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WPeekEventsDDK
//
// DESCRIPTION: This routine peek system event
//
// PARAMETERS:  
//
// RETURNED:    Returns Nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void WPeekEventsDDK(void)
{
	SYSTEMTIME	ctime, stime;
	long			timediff;

	timediff = MINSYSTICKS;

	GetSystemTime (&stime);
	do {
		GetSystemTime (&ctime);
	} while ( TimeDiff(&ctime,&stime)<timediff );

	WPeekInputsDDK();
}

void Initialize_System (HINSTANCE _hInst, int _nCmdShow)
{
	WNDCLASSEX wc;
	ATOM	atom;
	HFONT	newfont;

	// register window class for 3D windows
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wc.lpfnWndProc = MainProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInst;
	wc.hIcon = LoadIcon(_hInst, MAKEINTRESOURCE(1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APIClassName;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hIconSm = NULL;
	atom = RegisterClassEx(&wc);

	CreateWindows(APIClassName, "ApiTest", 0, 0, ScreenWidth, ScreenHeight);

	//	Get the global DC for drawing
	hdc = GetDC(hwnd);
	memDC = CreateCompatibleDC (hdc);
	newfont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, OEM_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, "PalmText12");
	SelectObject (hdc, newfont);



	ShowWindow(hwnd, _nCmdShow);
	UpdateWindow(hwnd);
	VDrawBackground();
	VSaveRegion(NULL, COORD_STRETCH);
}

//---------------------------------------------------------------------------
//  LRESULT NEAR CreateTTYInfo( HWND hWnd )
//
//  Description:
//     Creates the tty information structure and sets
//     menu option availability.  Returns -1 if unsuccessful.
//
//  Parameters:
//     HWND  hWnd
//        Handle to main window.
//
//  Win-32 Porting Issues:
//     - Needed to initialize TERMWND( npTTYInfo ) for secondary thread.
//     - Needed to create/initialize overlapped structures used in reads &
//       writes to COMM device.
//
//---------------------------------------------------------------------------

LRESULT NEAR CreateTTYInfo( HWND hWnd )
{
	long			value;

   if (NULL == (npTTYInfo =
                   (NPTTYINFO) LocalAlloc( LPTR, sizeof( TTYINFO ) )))
      return ( (LRESULT) -1 ) ;

   // initialize TTY info structure

   COMDEV( npTTYInfo )        = 0 ;
   CONNECTED( npTTYInfo )     = FALSE ;
   LOCALECHO( npTTYInfo )     = FALSE ;
   AUTOWRAP( npTTYInfo )      = TRUE ;
   PORT( npTTYInfo )          = 1 ;
   BAUDRATE( npTTYInfo )      = CBR_9600 ;
   BYTESIZE( npTTYInfo )      = 8 ;
   //FLOWCTRL( npTTYInfo )      = FC_RTSCTS ;
   FLOWCTRL( npTTYInfo )      = FC_XONXOFF ;
   PARITY( npTTYInfo )        = NOPARITY ;
   STOPBITS( npTTYInfo )      = ONESTOPBIT ;
   XONXOFF( npTTYInfo )       = FALSE ;
   XSIZE( npTTYInfo )         = 0 ;
   YSIZE( npTTYInfo )         = 0 ;
   XSCROLL( npTTYInfo )       = 0 ;
   YSCROLL( npTTYInfo )       = 0 ;
   XOFFSET( npTTYInfo )       = 0 ;
   YOFFSET( npTTYInfo )       = 0 ;
   COLUMN( npTTYInfo )        = 0 ;
   ROW( npTTYInfo )           = 0 ;
   HTTYFONT( npTTYInfo )      = NULL ;
   FGCOLOR( npTTYInfo )       = RGB( 0, 0, 0 ) ;
   USECNRECEIVE( npTTYInfo )  = TRUE ;
   DISPLAYERRORS( npTTYInfo ) = TRUE ;
   WRITE_OS( npTTYInfo ).Offset = 0 ;
   WRITE_OS( npTTYInfo ).OffsetHigh = 0 ;
   READ_OS( npTTYInfo ).Offset = 0 ;
   READ_OS( npTTYInfo ).OffsetHigh = 0 ;
   TERMWND( npTTYInfo ) =       hWnd ;

   // create I/O event used for overlapped reads / writes

   READ_OS( npTTYInfo ).hEvent = CreateEvent( NULL,    // no security
                                              TRUE,    // explicit reset req
                                              FALSE,   // initial event reset
                                              NULL ) ; // no name
   if (READ_OS( npTTYInfo ).hEvent == NULL) {
      LocalFree( npTTYInfo ) ;
      return ( -1 ) ;
   }
   WRITE_OS( npTTYInfo ).hEvent = CreateEvent( NULL,    // no security
                                               TRUE,    // explicit reset req
                                               FALSE,   // initial event reset
                                               NULL ) ; // no name
   if (NULL == WRITE_OS( npTTYInfo ).hEvent) {
      CloseHandle( READ_OS( npTTYInfo ).hEvent ) ;
      LocalFree( npTTYInfo ) ;
      return ( -1 ) ;
   }

   // setup default font information
   LFTTYFONT( npTTYInfo ).lfHeight =         9 ;
   LFTTYFONT( npTTYInfo ).lfWidth =          0 ;
   LFTTYFONT( npTTYInfo ).lfEscapement =     0 ;
   LFTTYFONT( npTTYInfo ).lfOrientation =    0 ;
   LFTTYFONT( npTTYInfo ).lfWeight =         0 ;
   LFTTYFONT( npTTYInfo ).lfItalic =         0 ;
   LFTTYFONT( npTTYInfo ).lfUnderline =      0 ;
   LFTTYFONT( npTTYInfo ).lfStrikeOut =      0 ;
   LFTTYFONT( npTTYInfo ).lfCharSet =        OEM_CHARSET ;
   LFTTYFONT( npTTYInfo ).lfOutPrecision =   OUT_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo ).lfClipPrecision =  CLIP_DEFAULT_PRECIS ;
   LFTTYFONT( npTTYInfo ).lfQuality =        DEFAULT_QUALITY ;
   LFTTYFONT( npTTYInfo ).lfPitchAndFamily = FIXED_PITCH | FF_MODERN ;
   lstrcpy( LFTTYFONT( npTTYInfo ).lfFaceName, "FixedSys" ) ;

   // set TTYInfo handle before any further message processing.
//   SETNPTTYINFO( hWnd, npTTYInfo ) ;
	value = SetWindowLong( hWnd, GWL_NPTTYINFO, (LONG) npTTYInfo );

   return ( (LRESULT) TRUE ) ;
} // end of CreateTTYInfo()

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WEvtGetEvent
//
// DESCRIPTION: This routine return the next available event.
//
// PARAMETERS:  (EventType *) event - Pointer to the structure to hold
//											the event returned.
//              (Int32) timeout - Maximum number of ticks to wait before
//											an event is returned.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void WEvtGetEvent(EventType *event, Int32 timeout)
{
	SYSTEMTIME	ctime, stime;
	long			timediff;

	//	set time difference
	if ( timeout == evtWaitForever )	
		timediff = SYSTEMTICKS;
	else
		timediff = timeout/(200/SYSTEMTICKS);

	// restrict the timediff shuttle
	if (timediff <	MINSYSTICKS)
		timediff = MINSYSTICKS;
	if (timediff >	MAXSYSTICKS)
		timediff = MAXSYSTICKS;

	GetSystemTime (&stime);
	do {
		GetSystemTime (&ctime);
	} while ( TimeDiff(&ctime,&stime)<timediff );

	WPeekInputsDDK();
	WPopEvent(event);
}

void FreeResourceMemory ()
{
	int	i;

	WDestroyForm ();
	WDestroyMenu ();
	// free system handle list memory
	for ( i = 0; i < sysHandle.count; i++ ) {
		if ( sysHandle.handle[i] ) {
			Vfree (sysHandle.handle[i]);
			sysHandle.handle[i] = NULL;
		}
	}

	if ( GlobalText ) {
		Vfree (GlobalText);
		GlobalText = NULL;
	}
	VReleaseRecord ();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WinMain
//
// DESCRIPTION: This routine is real main program of program.
//
// PARAMETERS:  (HINSTANCE) _hInst - the instance of program
//				(HINSTANCE) _hPrevInst - the instance of previous program
//				(LPSTR) _lpCmdLine - the command line parameter.
//				(int) _nCmdShow - the showing status of program
//
// RETURNED:    Returns 0 if normal terminated, others if abnormal.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01	Initial Revision
//			Jerry	5/17/01	reset the CurEvent variable
//			Jerry	8/15/01	Initial GlobalText to NULL
////////////////////////////////////////////////////////////////////////
#ifndef	_APM_SIMULATOR
int APIENTRY WinMain(HINSTANCE _hInst,     // program instance
                     HINSTANCE _hPrevInst, // previous instance
#else
VHWND WisWinMain(VHINSTANCE _hInst,     // program instance
                     VHINSTANCE _hPrevInst, // previous instance
#endif
                     Char *_lpCmdLine,     // command line
                     int _nCmdShow)
{
	Widget gw;

	// backup system data
	vHInst = _hInst;

	// Set the background bitmap name
	VGetCurrentDirectory (CISBMPNAME);
	Vstrcat (CISBMPNAME, "\\");
	Vstrcat (CISBMPNAME, PDABMPNAME);

	Initialize_System (_hInst, _nCmdShow);

	CurEvent = (EventType *) malloc (sizeof (EventType));
	memset (CurEvent, 0, sizeof (EventType));

	GlobalText = (Char *) malloc (1);
	GlobalText[0] = 0;

	WDrawStartUpScreen ();

	// Initialize handwriting engine
	Vmemset (&gw, 0, sizeof(Widget));
	Initialize_recorder (gw);	// not check

#ifndef	_APM_SIMULATOR
	if ( WGetResourceFileName("", word) ) {
		char	word[50];

		VSetRCPFile (word);
		PilotMain (0, NULL, 0);
		Finalize_recorder ();
	}
#endif

	return hwnd;
}
