#ifndef __NETINETIN_H__
#define __NETINETIN_H__

struct in_addr {
	union {
		struct { Byte s_b1,s_b2,s_b3,s_b4; } S_un_b;
		struct { Word s_w1,s_w2; } S_un_w;
		DWord S_addr;
	} S_un;
#define	s_addr	S_un.S_addr				/* should be used for all code */
#define	s_host	S_un.S_un_b.s_b2		/* OBSOLETE: host on imp */
#define	s_net	S_un.S_un_b.s_b1			/* OBSOLETE: network */
#define	s_imp	S_un.S_un_w.s_w2			/* OBSOLETE: imp */
#define	s_impno	S_un.S_un_b.s_b4		/* OBSOLETE: imp # */
#define	s_lh	S_un.S_un_b.s_b3			/* OBSOLETE: logical host */
};

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	short	sin_family;
	u_short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};


#define	htons(x)	(x)

#endif /*!__NETINETIN_H__*/
