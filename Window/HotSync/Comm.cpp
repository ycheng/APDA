
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

//---------------------------------------------------------------------------
//
//  Module: tty.c
//
//  Purpose:
//     The sample application demonstrates the usage of the COMM
//     API.  It implements the new COMM API of Windows 3.1.
//
//     NOTE:  no escape sequences are translated, only
//            the necessary control codes (LF, CR, BS, etc.)
//
//  Description of functions:
//     Descriptions are contained in the function headers.
//
//---------------------------------------------------------------------------
//
//  Written by Microsoft Product Support Services, Windows Developer Support.
//
//---------------------------------------------------------------------------

#include "stdafx.h"
#include <stdio.h>
#include "Comm.h"
#include "comdlg.h"

#define	NOTSYNC		0
#define	READDATA		1
#define	WRITEDATA	2
#define	BUFFERSIZE	512000


char			ReadingBuffer[BUFFERSIZE];
HMODULE		appInst=NULL;
HWND			hWnd;
char			installFileName[256];
BOOL			writeExclusive = FALSE, readExclusive = FALSE;
BYTE			syncStatus=NOTSYNC;
volatile int			headPtr=0, tailPtr=0;

void WaitResponse ()
{
	readExclusive = TRUE;
	while (!writeExclusive) {
	}
	writeExclusive = FALSE;
}

void WaitReadingResponse (int length)
{
	if ( headPtr >= tailPtr )
		while ( (headPtr-tailPtr) < length );
	else
		while ( (headPtr+BUFFERSIZE-tailPtr) < length);
}

void PushReadingBuffer (BYTE *abIn, int length)
{
	if ( (headPtr+length) < BUFFERSIZE ) {
		memcpy (&ReadingBuffer[headPtr], abIn, length);
		headPtr += length;
	}
}

void PopupReadingBuffer (char *buffer, int length)
{
	int	size;

	if ( (tailPtr+length) < BUFFERSIZE ) {
		memcpy (buffer, &ReadingBuffer[tailPtr], length);
		tailPtr += length;
	} else {
		memcpy (buffer, &ReadingBuffer[tailPtr], BUFFERSIZE-tailPtr);
		size = tailPtr+length-BUFFERSIZE;
		tailPtr = 0;
		memcpy (&buffer[BUFFERSIZE-tailPtr], &ReadingBuffer[tailPtr], size);
		tailPtr = size;
	} 
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

LRESULT NEAR CreateTTYInfo()
{
   NPTTYINFO   npTTYInfo ;
	long		value;

   if (NULL == (npTTYInfo =
                   (NPTTYINFO) LocalAlloc( LPTR, sizeof( TTYINFO ) )))
      return ( (LRESULT) -1 ) ;

   // initialize TTY info structure

   COMDEV( npTTYInfo )        = 0 ;
   CONNECTED( npTTYInfo )     = FALSE ;
   CURSORSTATE( npTTYInfo )   = CS_HIDE ;
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

   // clear screen space

   _fmemset( SCREEN( npTTYInfo ), ' ', MAXROWS * MAXCOLS ) ;

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

//---------------------------------------------------------------------------
//  BOOL NEAR OpenConnection()
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
BOOL NEAR OpenConnection()
{
   char       szPort[ 15 ], szTemp[ 10 ] ;
   BOOL       fRetVal ;
   HCURSOR    hOldCursor, hWaitCursor ;
   NPTTYINFO  npTTYInfo ;
   HANDLE        hCommWatchThread ;
   DWORD         dwThreadID ;
   COMMTIMEOUTS  CommTimeOuts ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

   // show the hourglass cursor
   hWaitCursor = LoadCursor( NULL, IDC_WAIT ) ;
   hOldCursor = SetCursor( hWaitCursor ) ;

   // load the COM prefix string and append port number

   LoadString( GETHINST( hWnd ), IDS_COMPREFIX, szTemp, sizeof( szTemp ) ) ;
   wsprintf( szPort, "%s%d", (LPSTR) szTemp, PORT( npTTYInfo ) ) ;

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
      // get any early notifications

      SetCommMask( COMDEV( npTTYInfo ), EV_RXCHAR ) ;
//      SetCommMask( COMDEV( npTTYInfo ), EV_TXEMPTY ) ;
      // setup device buffers
      SetupComm( COMDEV( npTTYInfo ), 4096, 4096 ) ;

      // purge any information in the buffer
      PurgeComm( COMDEV( npTTYInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

      // set up for overlapped I/O

      CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
      CommTimeOuts.ReadTotalTimeoutConstant = 0 ;
//      CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;
      // CBR_9600 is approximately 1byte/ms. For our purposes, allow
      // double the expected time per character for a fudge factor.
      CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/BAUDRATE( npTTYInfo ) ;
      CommTimeOuts.WriteTotalTimeoutConstant = 0 ;
      SetCommTimeouts( COMDEV( npTTYInfo ), &CommTimeOuts ) ;
   }

   fRetVal = SetupConnection() ;

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

   // restore cursor
   SetCursor( hOldCursor ) ;

   return ( fRetVal ) ;

} // end of OpenConnection()

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
BOOL NEAR SetupConnection()
{
   BOOL       fRetVal ;
   BYTE       bSet ;
   DCB        dcb ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

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


	// add for test
//   dcb.fParity = FALSE ;
//   dcb.fDtrControl = DTR_CONTROL_DISABLE ;
//	dcb.fRtsControl = RTS_CONTROL_DISABLE ;
	dcb.BaudRate = 19200;
//	dcb.fOutX = FALSE;
//	dcb.fInX = FALSE;
//	dcb.ByteSize = 4;


   fRetVal = SetCommState( COMDEV( npTTYInfo ), &dcb ) ;

   return ( fRetVal ) ;

} // end of SetupConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR CloseConnection( HWND hWnd )
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
BOOL NEAR CloseConnection()
{
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

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

   return ( TRUE ) ;

} // end of CloseConnection()

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
int NEAR ReadCommBlock(LPSTR lpszBlock, int nMaxLength )
{
   BOOL       fReadStat ;
   COMSTAT    ComStat ;
   DWORD      dwErrorFlags;
   DWORD      dwLength;
   DWORD      dwError;
   char       szError[ 10 ] ;
   NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

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
//                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
                  ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
                  if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo )) {
	                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//	                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
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
//	            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
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
BOOL NEAR WriteCommBlock(LPSTR lpByte , DWORD dwBytesToWrite)
{

   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
   NPTTYINFO   npTTYInfo ;
   DWORD       dwErrorFlags;
   DWORD   	dwError;
   DWORD       dwBytesSent=0;
   COMSTAT     ComStat;
   char        szError[ 128 ] ;


   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;

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
//               WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
               ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
               if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
               {
                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
//                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
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
//            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
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
   DWORD       dwEvtMask=0;
   NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;
	int			nLength;
   BYTE       abIn[1024] ;

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
		if ( syncStatus == NOTSYNC )
			break;

      WaitCommEvent( COMDEV( npTTYInfo ), &dwEvtMask, NULL );

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR) {
			while ((nLength = ReadCommBlock( (LPSTR) abIn, 1024 )) > 0) {
				if ( nLength ) 
					PushReadingBuffer (abIn, nLength);
			}
			dwEvtMask = 0;
      }
   }

   // get rid of event handle
   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")
   THREADID( npTTYInfo ) = 0 ;
   HTHREAD( npTTYInfo ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()


int PutCommChar (int ch)
{
   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
   NPTTYINFO   npTTYInfo ;
   DWORD       dwErrorFlags;
   DWORD   	dwError;
   DWORD       dwBytesSent=0;
   COMSTAT     ComStat;
   char        szError[ 128 ] ;



   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return 0;

   fWriteStat = WriteFile( COMDEV( npTTYInfo ), (char *)&ch, 1,
                           &dwBytesWritten, &WRITE_OS( npTTYInfo ) ) ;

   // Note that normally the code will not execute the following
   // because the driver caches write operations. Small I/O requests
   // (up to several thousand bytes) will normally be accepted
   // immediately and WriteFile will return true even though an
   // overlapped operation was specified

   if (!fWriteStat) {
      if((dwError=GetLastError()) == ERROR_IO_PENDING) {
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
               ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
               break;
            }
         }

//         OutputDebugString(szError);

      } else {
         // some other error occurred
         ClearCommError( COMDEV( npTTYInfo ), &dwErrorFlags, &ComStat ) ;
         if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo )) {
            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
         }
         return 0;
      }
   }

	return	1;
}

long	tCount=0;
int GetCommChar ()
{

	while ( tailPtr >= headPtr ) {
		tCount++;
		if ( tCount > 0x0fffffff )
			break;
	}

	tCount = 0;
	if ( tailPtr < headPtr ) {
		tailPtr++;

		return ReadingBuffer[tailPtr-1];
	} else
		return	-1;
}
