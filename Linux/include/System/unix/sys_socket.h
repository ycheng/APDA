#ifndef 	__SOCKET_H__
#define	__SOCKET_H__

// Include the Pilot Net Manager defines
#include <System/NetMgr.h>
#include <System/Unix/unix_netdb.h>
#include <System/Unix/arpa_inet.h>
#include <System/Unix/unix_string.h>


/*
 * Address families.
 */
#define	AF_INET		netSocketAddrINET				/* internetwork: UDP, TCP, etc. */

/*
 * Types
 */
#define	SOCK_STREAM		netSocketTypeStream			/* stream socket */
#define	SOCK_DGRAM		netSocketTypeDatagram		/* datagram socket */
#define	SOCK_RAW			netSocketTypeRaw				/* raw-protocol interface */


#define	close(socket) 												\
				NetLibSocketClose(AppNetRefnum, socket,AppNetTimeout,&errno)

#define	connect(socket,addr,addrlen)							\
				NetLibSocketConnect(AppNetRefnum, socket,(void*)addr,addrlen,AppNetTimeout,&errno)

#define	socket(domain,type,protocol)							\
				NetLibSocketOpen(AppNetRefnum, domain,type,protocol,AppNetTimeout,&errno)


#endif /*!__SOCKET_H__*/
