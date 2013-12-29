/***********************************************************************
 *
 *	Copyright (c) 1996-1997, Palm Computing Inc., All Rights Reserved
 *
 * PROJECT:  Pilot TCP/IP Library
 * FILE:     sys/types.h
 * AUTHOR:	 Ron Marianetti 2/14/96
 *
 * DESCRIPTION:
 *	  This module contains the Pilot equivalent of the "standard" unix
 * header file <sys/types.h>
 *
 **********************************************************************/
#ifndef 	__UNIXTYPES_H__
#define	__UNIXTYPES_H__

#include	<System\NetMgr.h>						// Include Pilot Net Manager equates

// Common Unix types
typedef	Byte		u_char;
typedef	Word		u_short;
typedef	UInt		u_int;
typedef	DWord		u_long;

typedef	Word		ushort;				/* System V compatibility */
typedef	UInt		uint;					/* System V compatibility */

typedef	DWord 		size_t;				// must be signed for some unix apps 
#define				__size_t__

#ifndef 			__DATETIME_H__		// avoid compiler warning
typedef	DWord 		time_t;				
#endif

typedef	Byte		FILE;


// Basic functions
#define	bcopy(b1,b2,len)		\
				MemMove(b2,b1,len)

#define	bzero(b,len)		\
				MemSet(b,len,0)
				
#define	bcmp(b1,b2,len) 	\
				MemCmp(b1,b2,len)
				
				

#endif  //__UNIXTYPES_H__