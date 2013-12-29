#ifndef 	__NETMGR_H__
#define	__NETMGR_H__

// Type used to hold internet addresses
typedef	DWord			NetIPAddr;		// a 32-bit IP address.


//-----------------------------------------------------------------------------
// Enumeration of Socket domains and types passed to NetSocketOpen
//-----------------------------------------------------------------------------
typedef enum {
	netSocketAddrINET=2									// (AF_INET)
	} NetSocketAddrEnum;

typedef enum {
	netSocketTypeStream=1,								// (SOCK_STREAM)
	netSocketTypeDatagram=2,							// (SOCK_DGRAM)
	netSocketTypeRaw=3									// (SOCK_RAW)
	} NetSocketTypeEnum;


//-----------------------------------------------------------------------------
// Net error codes
//-----------------------------------------------------------------------------
#define	netErrAlreadyOpen					(netErrorClass | 1)
#define	netErrNotOpen						(netErrorClass | 2)
#define	netErrStillOpen					(netErrorClass | 3)
#define	netErrParamErr						(netErrorClass | 4)
#define	netErrNoMoreSockets				(netErrorClass | 5)
#define	netErrOutOfResources				(netErrorClass | 6)
#define	netErrOutOfMemory					(netErrorClass | 7)
#define	netErrSocketNotOpen				(netErrorClass | 8)
#define	netErrSocketBusy					(netErrorClass | 9)		//EINPROGRESS
#define	netErrMessageTooBig				(netErrorClass | 10)
#define	netErrSocketNotConnected 		(netErrorClass | 11)
#define	netErrNoInterfaces				(netErrorClass | 12)		//ENETUNREACH
#define	netErrBufTooSmall					(netErrorClass | 13)
#define	netErrUnimplemented				(netErrorClass | 14)
#define	netErrPortInUse					(netErrorClass | 15)		//EADDRINUSE
#define	netErrQuietTimeNotElapsed		(netErrorClass | 16)		//EADDRINUSE
#define	netErrInternal						(netErrorClass | 17)
#define	netErrTimeout						(netErrorClass | 18)		//ETIMEDOUT
#define	netErrSocketAlreadyConnected 	(netErrorClass | 19)		//EISCONN
#define	netErrSocketClosedByRemote 	(netErrorClass | 20)
#define	netErrOutOfCmdBlocks			 	(netErrorClass | 21)
#define	netErrWrongSocketType			(netErrorClass | 22)
#define	netErrSocketNotListening		(netErrorClass | 23)
#define	netErrUnknownSetting				(netErrorClass | 24)
#define	netErrInvalidSettingSize		(netErrorClass | 25)
#define	netErrPrefNotFound				(netErrorClass | 26)
#define	netErrInvalidInterface			(netErrorClass | 27)
#define	netErrInterfaceNotFound			(netErrorClass | 28)
#define	netErrTooManyInterfaces			(netErrorClass | 29)
#define	netErrBufWrongSize				(netErrorClass | 30)
#define	netErrUserCancel					(netErrorClass | 31)
#define	netErrBadScript					(netErrorClass | 32)
#define	netErrNoSocket						(netErrorClass | 33)
#define	netErrSocketRcvBufFull			(netErrorClass | 34)
#define	netErrNoPendingConnect			(netErrorClass | 35)
#define	netErrUnexpectedCmd				(netErrorClass | 36)
#define	netErrNoTCB							(netErrorClass | 37)
#define	netErrNilRemoteWindowSize		(netErrorClass | 38)
#define	netErrNoTimerProc					(netErrorClass | 39)
#define	netErrSocketInputShutdown		(netErrorClass | 40)		// EOF to sockets API
#define	netErrCmdBlockNotCheckedOut	(netErrorClass | 41)		 
#define	netErrCmdNotDone					(netErrorClass | 42)		 
#define	netErrUnknownProtocol			(netErrorClass | 43)		 
#define	netErrUnknownService				(netErrorClass | 44)		 
#define	netErrUnreachableDest			(netErrorClass | 45)	
#define	netErrReadOnlySetting			(netErrorClass | 46)	 
#define	netErrWouldBlock					(netErrorClass | 47)		//EWOULDBLOCK
#define	netErrAlreadyInProgress			(netErrorClass | 48)		//EALREADY
#define	netErrPPPTimeout					(netErrorClass | 49)
#define	netErrPPPBroughtDown				(netErrorClass | 50)
#define	netErrAuthFailure					(netErrorClass | 51)
#define	netErrPPPAddressRefused			(netErrorClass | 52)
// The following map into the Epilogue DNS errors declared in DNS.ep.h:
//  and MUST be kept in this order!!
#define	netErrDNSNameTooLong				(netErrorClass | 53)
#define	netErrDNSBadName					(netErrorClass | 54)
#define	netErrDNSBadArgs					(netErrorClass | 55)
#define	netErrDNSLabelTooLong			(netErrorClass | 56)
#define	netErrDNSAllocationFailure		(netErrorClass | 57)
#define	netErrDNSTimeout					(netErrorClass | 58)
#define	netErrDNSUnreachable				(netErrorClass | 59)
#define	netErrDNSFormat					(netErrorClass | 60)
#define	netErrDNSServerFailure			(netErrorClass | 61)
#define	netErrDNSNonexistantName		(netErrorClass | 62)
#define	netErrDNSNIY						(netErrorClass | 63)
#define	netErrDNSRefused					(netErrorClass | 64)
#define	netErrDNSImpossible				(netErrorClass | 65)
#define	netErrDNSNoRRS						(netErrorClass | 66)
#define	netErrDNSAborted					(netErrorClass | 67)
#define	netErrDNSBadProtocol				(netErrorClass | 68)
#define	netErrDNSTruncated				(netErrorClass | 69)
#define	netErrDNSNoRecursion				(netErrorClass | 70)
#define	netErrDNSIrrelevant				(netErrorClass | 71)
#define	netErrDNSNotInLocalCache		(netErrorClass | 72)
#define	netErrDNSNoPort					(netErrorClass | 73)
// The following map into the Epilogue IP errors declared in IP.ep.h:
//  and MUST be kept in this order!!
#define	netErrIPCantFragment				(netErrorClass | 74)
#define	netErrIPNoRoute					(netErrorClass | 75)
#define	netErrIPNoSrc						(netErrorClass | 76)
#define	netErrIPNoDst						(netErrorClass | 77)
#define	netErrIPktOverflow				(netErrorClass | 78)
// End of Epilogue IP errors
#define	netErrTooManyTCPConnections	(netErrorClass | 79)
#define  netErrNoDNSServers				(netErrorClass | 80)


//-----------------------------------------------------------------------------
// Basic Types
//-----------------------------------------------------------------------------
// Socket refnum
typedef	SWord			NetSocketRef;		

//-----------------------------------------------------------------------------
// Structures used for looking up a host by name or address (NetLibGetHostByName)
//-----------------------------------------------------------------------------

// Equates for DNS names, from RFC-1035
#define	netDNSMaxDomainName		255
#define	netDNSMaxDomainLabel		63

#define	netDNSMaxAliases			1				// max # of aliases for a host
#define	netDNSMaxAddresses		4				// max # of addresses for a host

// The actual results of NetLibGetHostByName() are returned in this structure.
// This structure is designed to match the "struct hostent" structure in Unix.
typedef struct  {
	CharPtr		nameP;								// official name of host
	CharPtr*		nameAliasesP;						// array of alias's for the name
	Word			addrType;							// address type of return addresses
	Word			addrLen;								// the length, in bytes, of the addresses
	BytePtr*		addrListP;							// array of ptrs to addresses in HBO
	} NetHostInfoType, *NetHostInfoPtr;
	

// "Buffer" passed to call as a place to store the results
typedef struct {
	NetHostInfoType	hostInfo;					// high level results of call are here

	// The following fields contain the variable length data that 
	//  hostInfo points to
	Char			name[netDNSMaxDomainName+1];			// hostInfo->name

	CharPtr		aliasList[netDNSMaxAliases+1];		// +1 for 0 termination.
	Char			aliases[netDNSMaxAliases][netDNSMaxDomainName+1];

	NetIPAddr*	addressList[netDNSMaxAddresses];
	NetIPAddr	address[netDNSMaxAddresses];

	} NetHostInfoBufType, *NetHostInfoBufPtr;

	
//-----------------------------------------------------------------------------
// Structures used for looking up a service (NetLibGetServByName)
//-----------------------------------------------------------------------------

// Equates for service names
#define	netServMaxName				15				// max # characters in service name
#define	netProtoMaxName			15				// max # characters in protocol name
#define	netServMaxAliases			1				// max # of aliases for a service


// The actual results of NetLibGetServByName() are returned in this structure.
// This structure is designed to match the "struct servent" structure in Unix.
typedef struct {
	CharPtr		nameP;								// official name of service
	CharPtr*		nameAliasesP;						// array of alias's for the name
	Word			port;									// port number for this service
	CharPtr		protoP;								// name of protocol to use
	} NetServInfoType, *NetServInfoPtr;
	
// "Buffer" passed to call as a place to store the results
typedef struct {
	NetServInfoType	servInfo;					// high level results of call are here

	// The following fields contain the variable length data that 
	//  servInfo points to
	Char			name[netServMaxName+1];					// hostInfo->name

	CharPtr		aliasList[netServMaxAliases+1];		// +1 for 0 termination.
	Char			aliases[netServMaxAliases][netServMaxName];
	Char			protoName[netProtoMaxName+1];

	} NetServInfoBufType, *NetServInfoBufPtr;
	

// Structure used to hold a generic socket address. This is a generic struct 
// designed to hold any type of address including internet addresses. This 
// structure directly maps to the BSD unix struct sockaddr.
typedef struct  NetSocketAddrType {
	SWord			family;					// Address family
	Byte			data[14];				// 14 bytes of address 
	} NetSocketAddrType;
	

#endif // __NETMGR_H__
