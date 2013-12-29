#ifndef __UNIXINET_H__
#define __UNIXINET_H__

#include <System/Unix/netinet_in.h>

//===========================================================================
// Macros that convert Unix calls into native Pilot calls.
//===========================================================================
// Convert a dotted decimal string representation into an IP address.
// return -1 on error 
#define	inet_addr(s)			\
						NetLibAddrAToIN(AppNetRefnum, s)

#endif /*__UNIXINET_H__*/





