/*========================================================
  Network.c
  all routine is running with Platform non-related,
  simulated the Serial Manager function in Palm OS.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0713, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#include <System/NetMgr.h>

UInt16	sysRefNum = 0;
UInt16	sysPort = 1;
UInt32	sysBaud = 9600;
UInt32	receiveBytes = 0;
Int32		sysTimeout = -1;
Err		netError = 0;

UInt16	OpenLibRefNum=0;


////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibAddrAToIN
//
// DESCRIPTION: This routine converts an ASCII string representing a 
//					 dotted decimal IP address into a 32-bit IP address in 
//					 network byte order.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (Char *) a - Buffer to ASCII dotted decimal string.
//
// RETURNED:    Returns a 32-bit network byte order IP address or -1
//					 if a doesn't represent a dotted decimal IP address.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
NetIPAddr NetLibAddrAToIN (UInt16 libRefNum, Char *a)
{
	NetIPAddr	inet=-1;

//	StrAToI (a);
	return	inet;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibAddrINToA
//
// DESCRIPTION: This routine converts an IP address from 32-bit network
//					 byte order into a dotted decimal ASCII string.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (NetIPAddr) inet - 32-bit IP address in network byte order.
//					 (Char *) spaceP - Buffer used to hold the return value.
//
// RETURNED:    Returns in spaceP the dotted decimal ASCII string
//					 representation of the IP address.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char *NetLibAddrINToA (UInt16 libRefNum, NetIPAddr inet, Char *spaceP)
{
	Char	buffer[4];

	StrIToA (buffer, ((inet>>24)&0xFF));
	Vstrcpy (spaceP, buffer);
	Vstrcat (spaceP, ".");
	StrIToA (buffer, ((inet>>16)&0xFF));
	Vstrcat (spaceP, buffer);
	Vstrcat (spaceP, ".");
	StrIToA (buffer, ((inet>8)&0xFF));
	Vstrcat (spaceP, buffer);
	Vstrcat (spaceP, ".");
	StrIToA (buffer, (inet&0xFF));
	Vstrcat (spaceP, buffer);
	Vstrcat (spaceP, ".");

	return	spaceP;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibClose
//
// DESCRIPTION: This routine closes the net library.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (UInt16 *) netIFErrP - IF true, library will shut down
//										immediately. If false, library will shut
//										down only if close timer expires before
//										another NetLibOpen is issued.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err NetLibClose (UInt16 libRefNum, UInt16 immediate)
{
	if ( OpenLibRefNum == libRefNum ) {
		return	0;
	}

	return	netErrNotOpen;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibGetHostByName
//
// DESCRIPTION: This routine Opens and initializes the net library.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (UInt16 *) nameP - Name of host to look up.
//					 (NetHostInfoBufPtr) bufP - Pointer to a NetHostInfoBufByte
//										struct in which to store the results of
//										the lookup.
//					 (Int32) timeout - Maximum timeout in system ticks; -1 
//											means wait forever.
//					 (Err *) errP - Contains an error code if the return 
//											value is not 0.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision as NULL
////////////////////////////////////////////////////////////////////////
NetHostInfoPtr NetLibGetHostByName (UInt16 libRefNum, Char *nameP,
											NetHostInfoBufPtr bufP, Int32 timeout, Err *errP)
{
	return	NULL;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibOpen
//
// DESCRIPTION: This routine Opens and initializes the net library.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (UInt16 *) netIFErrP - First error encountered when
//										bringing up network interfaces.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err NetLibOpen (UInt16 libRefNum, UInt16 *netIFErrP)
{
	OpenLibRefNum = libRefNum;

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibSocketClose
//
// DESCRIPTION: This routine close a socket.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (NetSocketRef) socket - Descriptor for the open socket.
//					 (Int16) timeout - Maximum timeout in system ticks; -1
//												means wait forever.
//					 (Err *) errP - First error encountered when
//										bringing up network interfaces.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 NetLibSocketClose (UInt16 libRefNum, NetSocketRef socket,
									Int32 timeout, Err* errP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibSocketConnect
//
// DESCRIPTION: This routine assign a destination address to a socket
//					 and initiate three-way handshake if it's stream based.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (NetSocketRef) socket - Descriptor for the open socket.
//					 (NetSocketAddrType *) sockAddrP - Pointer to address to
//											connect to.
//					 (Int16) addrLen - Length of address in *sockAddrP.
//					 (Int16) timeout - Maximum timeout in system ticks; -1
//												means wait forever.
//					 (Err *) errP - First error encountered when
//										bringing up network interfaces.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 NetLibSocketConnect (UInt16 libRefNum, NetSocketRef socket,
								  NetSocketAddrType *sockAddrP, Int16 addrLen,
								  Int32 timeout, Err *errP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    NetLibSocketOpen
//
// DESCRIPTION: This routine Opens and initializes the net library.
//
// PARAMETERS:  (UInt16) libRefNum - Reference number of the net library.
//					 (NetSocketAddrEnum) domain - Address domain.
//					 (NetSocketTypeEnum) type - Desired type of connection.
//					 (Int16) protocol - Protocol to use. This parameter is
//												currently ignored.
//					 (Int16) timeout - Maximum timeout in system ticks; -1
//												means wait forever.
//					 (Err *) errP - First error encountered when
//										bringing up network interfaces.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
NetSocketRef NetLibSocketOpen (UInt16 libREfNum, NetSocketAddrEnum domain,
											NetSocketTypeEnum type, Int16 protocol, 
											Int32 timeout, Err *errP)
{
	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerClose
//
// DESCRIPTION: This routine release the serial port previously acquired
//					 by SerOpen.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SerClose (UInt16 refNum)
{
	return	CloseConnection ();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerGetStatus
//
// DESCRIPTION: This routine Acquire and open a serial port with given
//					 baud rate and default.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (Boolean *) ctsOnP - Pointer to location for storing
//										a Boolean value.
//					 (Boolean *) dsrOnP - Pointer to location for storing
//										a Boolean value.
//
// RETURNED:    Returns any combination of the forllowing constants,
//					 bitwise ORed together.
//						serLineErrorParity		parity error.
//						serLineErrorHWOverrun	Hardware overrun.
//						serLineErrorFraming		Framing error.
//						serLineErrorBreak			Break signal detected.
//						serLineErrorHShake		Line handshake error.
//						serLineErrorSWOverrun	Software overrun.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 SerGetStatus (UInt16 refNum, Boolean *ctsOnP, Boolean *dsrOnP)
{
	return	GetConnectionStatus (ctsOnP, dsrOnP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerOpen
//
// DESCRIPTION: This routine Acquire and open a serial port with given
//					 baud rate and default.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (UInt16) port - Port number.
//					 (UInt32) baud - Baud rate.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SerOpen (UInt16 refNum, UInt16 port, UInt32 baud)
{
	sysPort = port;
	sysBaud = baud;

	return	OpenConnection (port, baud);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerReceive
//
// DESCRIPTION: This routine receive size bytes worth of data or returns
//					 with error if a line error or timeout is encountered.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (void *) bufP - Buffer for receiving data
//					 (UInt32) count - Number of bytes to receive.
//					 (Int32) timeout - Interbyte timeout in ticks,
//										0 for none, -1 forever.
//					 (Err *) errP - For returning error code.
//
// RETURNED:    Returns number of bytes received.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 SerReceive (UInt16 refNum, void *bufP, UInt32 count,
						 Int32 timeout, Err *errP)
{
	if (timeout != sysTimeout) {
		sysTimeout = timeout;
		SetupTimeout (sysBaud, timeout);
	}
	receiveBytes =	ReadCommBlock (bufP, count);

	return	receiveBytes;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerReceiveCheck
//
// DESCRIPTION: This routine return the count of bytes presently in
//					 the receive queue.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (UInt32 *) numBytesP - Pointer to location for returning
//										the byte count.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SerReceiveCheck (UInt16 refNum, UInt32 *numBytesP)
{
	*numBytesP = receiveBytes;

	return	netError;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerReceiveFlush
//
// DESCRIPTION: This routine discard all data presently in the receive
//					 queue and flush bytes coming into the serial port.
//					 Clear the saved error status.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (Int32) timeout - Interbyte timeout in ticks,
//										0 for none, -1 forever.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void SerReceiveFlush (UInt16 refNum, Int32 timeout)
{
	sysTimeout = timeout;
	SetupTimeout (sysBaud, timeout);
	netError = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerSend
//
// DESCRIPTION: This routine send one or more bytes of data over the
//					 serial port.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//					 (void *) bufP - Pointer to data to send.
//					 (UInt32) count - Number of bytes to sned.
//					 (Err *) errP - For returning error code.
//
// RETURNED:    Returns number of bytes transferred.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 SerSend (UInt16 refNum, void *bufP, UInt32 count, Err *errP)
{
	return	WriteCommBlock (bufP, count);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    SerSendFlush
//
// DESCRIPTION: This routine discard all data presently in the transmit
//					 queue.
//
// PARAMETERS:  (UInt16) refNum - Serial library reference number.
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/13/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Err SerSendFlush (UInt16 refNum)
{
	SetupTimeout (sysBaud, sysTimeout);

	return	0;
}