#ifndef 	__UNIXNETDB_H__
#define	__UNIXNETDB_H__

/*
 * Structures returned by network data base library.
 * All addresses are supplied in host order, and
 * returned in network order (suitable for use in system calls).
 */

struct	hostent {
	Char	*h_name;						/* official name of host */
	Char	**h_aliases;				/* alias list */
	Word	h_addrtype;					/* host address type */
	Word	h_length;					/* length of address */
	Char	**h_addr_list;				/* list of addresses from name server */
#define	h_addr	h_addr_list[0]	/* address, for backward compatiblity */
};


// Supported calls
#define	gethostbyname(nameP) 	\
				((struct hostent*)NetLibGetHostByName(AppNetRefnum, nameP,&AppHostInfo,AppNetTimeout,&h_errno))



#endif	//	__UNIXNETDB_H__