/*
 * hotsync.c
 *
 * Description:
 *   Sync files between the host and the PDA
 *
 * Exported Function:
 *   SendFile(const char* filename, int (*PutCh)(int c));
 *   RecvFile(const char* filename, int (*GetCh)());
 *
 * Note:
 *   . PutCh and GetCh have the same calling convention as putchar 
 *     and getchar, respectively.
 *   . Assume PutCh and GetCh guarantee the delivery.
 *   . Most function return ERR_* on fail.
 *
 * Todo:
 *   . Split/Concatenate packet in SendPacket/RecvPacket automatically
 *   . Flow control & retransmission
 *   . Time-out problem
 *
 * Copyright (C) 2001 by William Liang @ Wiscore Inc.
 *
 * Date: $Date: 2001/12/06 07:40:09 $
 * Version: $Revision: 1.15 $
 */

/* Uncomment the following two lines if you are to compile under VC++ */
#include <stdafx.h>

#ifdef	VC
#include <io.h>
#include <time.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/time.h>
#endif

#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include "hotsync.h"

/* -- Start of Configurable part -- */

/* NOTE: 
 *  It's suggested to use compiler option to control these parameters.
 *  Refer to the provided script 'build'.
 */

/* Uncomment one the following line to select compiling master or slave */
/* #define MASTER */
/* #define SLAVE */

/* Uncomment the following line if you want the program to open ttyS itself */
/* #define OPENTTY */

/* Uncomment the following line if you want ACK */
/* #define ACK */

/* Uncomment the following line if you want to use new encoding mechanism */
/* #define RAWDATA */

/* Uncomment the following line if you want debug mode */
/* #define DEBUG */

/* Uncomment the following line if you want to abort immediately 
 * whenever an error occures, provided that DEBUG mode is used */
/* #define CRITICAL */

/* -- End of Configuration part -- */

/* Directory to hold slave files */
#define SLAVEDIR	"/xapm"

/* Number of sending for short packet */
#ifdef	SLAVE
#define NUM_ACK		2
#else
#define NUM_ACK		2
#endif	/* SLAVE */

/* Number of sending for short packet */
#define NUM_PADS	3

/* Length of packet to add a check sum */
#define CHK_LEN		20

/* Maximal number of allowed resend */
#define	MAX_RESEND	20

/* Time out value for read (sec) */
#define	TIME_OUT	2

/* Packet size */
#ifndef	MAXBYTE
#define MAXBYTE		255
#endif
#define MAX_PKTLEN	MAXBYTE

/* Path of device ttyS */
#ifdef	USETTYS1
#define	TTYS		"/dev/ttyS1"
#else
#define	TTYS		"/dev/ttyS0"
#endif	/* USERTTYS1 */

/* Physical packet head & tail */
#define MARK_HEAD	'^'
#define MARK_TYPE	'-'
#define MARK_TAIL	'$'
#define MARK_RANGE1	'@'
#define MARK_RANGE2	'*'
#define MARK_RANGE3	'%'
#define MARK_ESC	'\\'
// #define MARK_LF		0x0a
// #define MARK_CR		0x0d

/* Length of each internal ACK, DON'T change except you know what you're doing! */
#define ACK_LEN		3	/* 1 for status + 2 for len */

#ifndef	VC
/* Define O_BINARY which is used by VC */
#ifndef	O_BINARY
#define	O_BINARY	0
#endif
#endif

/* Packet type */
typedef enum pktype_s {
	/* value 0 is used to mean all kind of packet */
	PKTYPE_ALLTYPE,
	/* below is sent by master, received by slave */
	PKTYPE_MASTER_REQUEST,
	PKTYPE_MASTER_OPENFILE,
	PKTYPE_MASTER_NORMAL,
	PKTYPE_MASTER_RESET,
	PKTYPE_MASTER_ACK,	/* Send/RecvPacketAck use only, for master */
	PKTYPE_MASTER_FINISH,
	/* below is sent by slave, received by master */
	PKTYPE_SLAVE_REQUEST,
	PKTYPE_SLAVE_OPENFILE,
	PKTYPE_SLAVE_NORMAL,
	PKTYPE_SLAVE_RESET,
	PKTYPE_SLAVE_ACK,	/* Send/RecvPacketAck use only, for slave */
	PKTYPE_SLAVE_FINISH,
	/* max number of type */
	PKTYPE_MAXTYPE
} pktype_t;
/* !!! NOTE: currently only max 14 (1~14) types are allowed */

#ifdef	SLAVE
/* slave/send */
#define	PKTYPE_SEND_REQUEST	PKTYPE_SLAVE_REQUEST
#define	PKTYPE_SEND_OPENFILE	PKTYPE_SLAVE_OPENFILE
#define	PKTYPE_SEND_RESET	PKTYPE_SLAVE_RESET
#define	PKTYPE_SEND_ACK		PKTYPE_SLAVE_ACK
#define	PKTYPE_SEND_NORMAL	PKTYPE_SLAVE_NORMAL
#define	PKTYPE_SEND_FINISH	PKTYPE_SLAVE_FINISH
/* slave/recv */
#define	PKTYPE_RECV_REQUEST	PKTYPE_MASTER_REQUEST
#define	PKTYPE_RECV_OPENFILE	PKTYPE_MASTER_OPENFILE
#define	PKTYPE_RECV_RESET	PKTYPE_MASTER_RESET
#define	PKTYPE_RECV_ACK		PKTYPE_MASTER_ACK
#define	PKTYPE_RECV_NORMAL	PKTYPE_MASTER_NORMAL
#define	PKTYPE_RECV_FINISH	PKTYPE_MASTER_FINISH
#else
/* master/send */
#define	PKTYPE_SEND_REQUEST	PKTYPE_MASTER_REQUEST
#define	PKTYPE_SEND_OPENFILE	PKTYPE_MASTER_OPENFILE
#define	PKTYPE_SEND_RESET	PKTYPE_MASTER_RESET
#define	PKTYPE_SEND_ACK		PKTYPE_MASTER_ACK
#define	PKTYPE_SEND_NORMAL	PKTYPE_MASTER_NORMAL
#define	PKTYPE_SEND_FINISH	PKTYPE_MASTER_FINISH
/* master/recv */
#define	PKTYPE_RECV_REQUEST	PKTYPE_SLAVE_REQUEST
#define	PKTYPE_RECV_OPENFILE	PKTYPE_SLAVE_OPENFILE
#define	PKTYPE_RECV_RESET	PKTYPE_SLAVE_RESET
#define	PKTYPE_RECV_ACK		PKTYPE_SLAVE_ACK
#define	PKTYPE_RECV_NORMAL	PKTYPE_SLAVE_NORMAL
#define	PKTYPE_RECV_FINISH	PKTYPE_SLAVE_FINISH

#endif

/* SubPacket type */
typedef enum subtype_s {
	SUBTYPE_SENDFILE,
	SUBTYPE_RECVFILE,
	SUBTYPE_EOF,
	SUBTYPE_CONTENT,
	SUBTYPE_ABORT,
	SUBTYPE_STOP
} subtype_t;

/* note: number of each type must be < 256 */ 

/* Path delimitor */
#ifdef	WIN32
#define PATH_DLMTR	'\\'
#else
#define PATH_DLMTR	'/'
#endif /* WIN32 */

/* Defined type */
typedef unsigned char byte_t;

/* Debug mode selection */

#ifdef	DEBUG

/* Define RETURN to return or exit on < 0 */
#ifdef	CRITICAL
#define RETURN(code) {						\
	errcode_t retcode = (code);				\
	if ((retcode) < 0) {					\
		fprintf(stderr, "Error: %s, %d: %d (%s,%s)\n",	\
			__FILE__, __LINE__, (retcode), #code,	\
			ErrString(retcode));			\
		exit((retcode));				\
	} else							\
		return (retcode);				\
}
#else	/* CRITICAL */
#define RETURN(code) {						\
	if ((code) < 0) 					\
		TRACE("\nError: %s\n", ErrString((code)));	\
	return (code);						\
}
#endif	/* CRITICAL */

/* Output trace info */
#ifndef	VC
#define TRACE(msg...) {				\
	fprintf(stderr, ## msg); 		\
	fflush(stderr); 			\
}
#endif	/* VC */

#else	/* DEBUG */

#define RETURN(code) { return (code); }

#ifndef	VC
#define TRACE(msg...)
#endif	/* VC */

#endif	/* DEBUG */

/* Get a char from the stream and check for error */
#define GETCH(c, GetCh)	{				\
	errcode_t i;					\
							\
	if ((i = (errcode_t)(GetCh)()) < 0) {		\
		TRACE("\nError GetCh: '%02x'(%d)\n",	\
			(byte_t)i, (int)i);		\
		RETURN(ERR_GETCH);			\
	}						\
	*(c) = (byte_t)i;				\
	TRACE("%c", *c); 				\
}

/* Put a char to the stream and check for error */
#define PUTCH(c, PutCh)	{				\
	if ((PutCh)((c)) < 0) {				\
		TRACE("\nError PutCh: '%02x'(%d)\n",	\
			c, (int)c);			\
		RETURN(ERR_PUTCH);			\
	}						\
	TRACE("%c", c); 				\
}

/* Convert then put a byte to the stream and check for error */
#define PUTBYTE(byte, PutCh) {				\
	errcode_t retcode;				\
	if ((retcode = PutByte((byte), (PutCh))) < 0) 	\
		RETURN(retcode);			\
}

/* Convert then put a byte to the stream and check for error */
#define GETBYTE(byte, GetCh) {				\
	errcode_t retcode;				\
	if ((retcode = GetByte((byte), (GetCh))) < 0) 	\
		RETURN(retcode);			\
}

/* Calculate chksum */
#define CHKSUM(chksum, byte)	((chksum) = (byte_t)((chksum) + (byte)))

/* 2 bytes to integer */
#define BYTES2INT(b)	((int)(b[0] << 8 | b[1]))

/* Integer to 2 bytes */
#define INT2BYTES(b, i)	((b)[0] = (byte_t)((i) >> 8), (b)[1] = (byte_t)(i))

/* Static global variable, must be protected for multithread */
static byte_t g_sorder = 0; 
static byte_t g_rorder = 0;
static int self_resend_count = 0;
static int peer_resend_count = 0;

/* Convert a 0-15 decimal value into its hex letter */
static errcode_t Halfbyte2Hexchar(byte_t* x, byte_t halfbyte) { 
	if (/* 0 <= halfbyte && */ halfbyte <= 9)
		*x = (byte_t)(halfbyte + '0');
	else if (10 <= halfbyte && halfbyte <= 15)
		*x = (byte_t)(halfbyte - 10 + 'a');
	else
		RETURN(ERR_BYTE2HEX);

	return (errcode_t)0;
}

/* Convert a hex letter into its decimal value (0-15) */
static errcode_t Hexchar2Halfbyte(byte_t* halfbyte, byte_t x) { 
	if (isdigit(x))
		*halfbyte = (byte_t)(x - '0');
	else if ('a' <= x && x <= 'f')
		*halfbyte = (byte_t)(x - 'a' + 10);
	else if ('A' <= x && x <= 'F')
		*halfbyte = (byte_t)(x - 'A' + 10);
	else
		RETURN(ERR_HEX2BYTE);

	return (errcode_t)0;
}

#ifndef	RAWDATA
/* Convert a byte into its hex string 'byte_t hexbyte[2]' */
static errcode_t Byte2Hexbyte(byte_t* hexbyte, byte_t c) { 
	byte_t hi, lo;
	
	if (!hexbyte) RETURN(ERR_MEMORY);

	hi = (byte_t)(c >> 4); 
	lo = (byte_t)(c & 0x0f);
	
	if (Halfbyte2Hexchar(hexbyte, hi) < 0) RETURN(ERR_BYTE2HEX);
	if (Halfbyte2Hexchar(hexbyte+1, lo) < 0) RETURN(ERR_BYTE2HEX);

	return (errcode_t)0;
}

/* Convert the hex string 'byte_t hexbyte[2]' into its decimal value */
static errcode_t Hexbyte2Byte (byte_t* byte, byte_t* hexbyte) { 
	byte_t hi, lo;
	
	if (!hexbyte || !byte) RETURN(ERR_MEMORY);

	if (Hexchar2Halfbyte(&hi, hexbyte[0]) < 0) RETURN(ERR_HEX2BYTE);
	if (Hexchar2Halfbyte(&lo, hexbyte[1]) < 0) RETURN(ERR_HEX2BYTE);

	*byte = (byte_t)(hi << 4 | lo);

	return (errcode_t)0;
}
#endif

/* Put a byte into the stream by PutCh, 
 * map all bytes into the range between 0x20 and 0x7e */
#ifdef	RAWDATA
static errcode_t PutByte(byte_t c, int (*PutCh)(int c)) {
	if (c < 0x20) {
		PUTCH(MARK_RANGE1, PutCh);
		c += 0x20;
	} else if (0x7e < c && c <= 0xc0) {
		PUTCH(MARK_RANGE2, PutCh);
		c = c - 0x7f + 0x20;
	} else if (0xc0 < c) {
		PUTCH(MARK_RANGE3, PutCh);
		c = c - 0xc1 + 0x20;
	} else {
		switch (c) {
			case MARK_HEAD:
			case MARK_TYPE:
			case MARK_TAIL:
			case MARK_RANGE1:
			case MARK_RANGE2:
			case MARK_RANGE3:
			case MARK_ESC:
				PUTCH(MARK_ESC, PutCh);
				break;
		}
	}

	PUTCH(c, PutCh);

	return (errcode_t)0;
}
#else
static errcode_t PutByte(byte_t c, int (*PutCh)(int c)) {
	byte_t hexbyte[2];

	/* convert it into hex bytes */
	Byte2Hexbyte(hexbyte, c);

	/* put two char into the stream */
	PUTCH(hexbyte[0], PutCh);
	PUTCH(hexbyte[1], PutCh);

	// TRACE(",");

	return (errcode_t)0;
}
#endif	/* RAWDATA */

/* Get a byte from the stream by GetCh */
#ifdef	RAWDATA
/* GetByte2 is invoked by GetByte, 'byte' must contain the previous read byte */
static errcode_t GetByte2(byte_t* byte, int (*GetCh)()) {
	switch (*byte) {
		case MARK_ESC: 
			GETCH(byte, GetCh);
			switch (*byte) {
				case MARK_HEAD:
				case MARK_TYPE:
				case MARK_TAIL:
				case MARK_RANGE1:
				case MARK_RANGE2:
				case MARK_RANGE3:
				case MARK_ESC:
					return (errcode_t)0;
				default:
					TRACE("\n** '%c'(%02x) should not be "
							"escaped\n", 
							*byte, *byte);
					RETURN(ERR_GETBYTE);
			}
		case MARK_HEAD:
		case MARK_TYPE:
		case MARK_TAIL:
			TRACE("\n** Special character '%c'(0x%02x) is not "
					"expected here\n", *byte, *byte);
			RETURN(ERR_GETBYTE);
		case MARK_RANGE1:
			GETCH(byte, GetCh);
			*byte -= 0x20;
			/* check range */
			if (*byte >= 0x20) {
				TRACE("\n** '%c'(0x%02x) must be < 0x20\n",
						*byte, *byte);
				RETURN(ERR_RANGE);
			}
			return (errcode_t)0;
		case MARK_RANGE2:
			GETCH(byte, GetCh);
			*byte = *byte - 0x20 + 0x7f;
			/* check range */
			if (0x7e >= *byte || *byte > 0xc0) {
				TRACE("\n** '%c'(0x%02x) must be > 0x7e & "
						"<= 0xc0\n", *byte, *byte);
				RETURN(ERR_RANGE);
			}
			return (errcode_t)0;
		case MARK_RANGE3:
			GETCH(byte, GetCh);
			*byte = *byte - 0x20 + 0xc1;
			/* check range */
			if (0xc0 >= *byte) {
				TRACE("\n** '%c'(0x%02x) must be > 0xc0\n",
						*byte, *byte);
				RETURN(ERR_RANGE);
			}
			return (errcode_t)0;
		default:
			return (errcode_t)0;
	}
}

static errcode_t GetByte(byte_t* byte, int (*GetCh)()) {
	GETCH(byte, GetCh);
	RETURN(GetByte2(byte, GetCh));
}
#else
static errcode_t GetByte(byte_t* byte, int (*GetCh)()) {
	byte_t hexbyte[2];

	/* get two char from the stream */
	GETCH(&hexbyte[0], GetCh);
	GETCH(&hexbyte[1], GetCh);

	// TRACE(",");

	/* convert it into a byte */
	return Hexbyte2Byte(byte, hexbyte);
}
#endif	/* RAWDATA */

/* Send a packet into the stream */
static errcode_t SendPacket(pktype_t type, byte_t order, byte_t *buf, int size, 
		int (*PutCh)(int c)) 
{
	int i, k;
	byte_t chksum = 0;

	if (!PutCh || (size > 0 && !buf)) RETURN(ERR_MEMORY);

	if (size > MAX_PKTLEN) RETURN(ERR_LEN);

	/* put Physical Packet Head */
	for (k = 0; k < NUM_PADS; k++) { PUTCH(MARK_HEAD, PutCh); }

	/* put packet type */
	// PUTBYTE((byte_t)type, PutCh);
	{
		byte_t c;
		Halfbyte2Hexchar(&c, (byte_t)type);
		for (k = 0; k < NUM_PADS; k++) { PUTCH(c, PutCh); }
		for (k = 0; k < NUM_PADS; k++) { PUTCH(MARK_TYPE, PutCh);}
	}
	CHKSUM(chksum, (byte_t)(type));

	/* put packet type */
	PUTBYTE(order, PutCh);
	CHKSUM(chksum, order);

	/* put length of the packet */
	PUTBYTE((byte_t)(size>>8), PutCh);	/* high byte */
	CHKSUM(chksum, (byte_t)(size>>8));
	PUTBYTE((byte_t)size, PutCh);		/* low byte */
	CHKSUM(chksum, (byte_t)size);

	/* put the packet body, compute check sum by the way */
	for (i = 0; i < size; i++) {
		PUTBYTE(buf[i], PutCh);
		CHKSUM(chksum, buf[i]);

		/* put checksum every CHK_LEN */
		if ((i % CHK_LEN) == 0) { PUTBYTE(chksum, PutCh); }
	}

	/* put checksum */
	PUTBYTE(chksum, PutCh);

	/* put Physical Packet Tail */
	for (k = 0; k < NUM_PADS; k++) { PUTCH(MARK_TAIL, PutCh); }

	/* put Physical Packet CR */
	// PUTCH(MARK_LF, PutCh);
	// PUTCH(MARK_CR, PutCh);

	fflush(0);

	return (errcode_t)size;
}

/* Receive a packet from the stream 
 * Note: buf == NULL means to absorb the packet, otherwise size must be > 0;
 *       *type == 0 means to accept any kind of packet, otherwise packet
 *       different from *type will be ignored.
 */
static errcode_t RecvPacket(pktype_t* type, byte_t* order, byte_t* buf, int size, 
		int (*GetCh)(void)) 
{
	int pktlen; 
	byte_t i, c, t, chksum = 0, h[2];

	if (!GetCh || !type || !order) RETURN(ERR_MEMORY);

	if (buf && size < 0) RETURN(ERR_LEN);
	
	while (1) {
		/* get Physical Packet Head & Type record */
		do { GETCH(h, GetCh); } while (*h != MARK_HEAD);
		do { GETCH(&t, GetCh); } while (t == MARK_HEAD);
		do { GETCH(h, GetCh); } while (*h == t);
		if (*h != MARK_TYPE) RETURN(ERR_FORMAT);
		do { GETCH(h, GetCh); } while (*h == MARK_TYPE);
		if (Hexchar2Halfbyte(&c, t) < 0) RETURN(ERR_HEX2BYTE);

		/* check if this is an out-of-bound message, only for slave */
		if ((pktype_t)c == PKTYPE_RECV_RESET) {
			TRACE("\n<= Get an RESET packet\n");
			*type = (pktype_t)c;
			g_rorder = g_sorder = 0; /* reset message order */
			RETURN(ERR_RESET); // break;
		}

		/* check if type is specified */
		if (*type <= 0) {	/* accept any type of packet */
			*type = (pktype_t)c;
			break;
		} else if (*type == c)	/* type matched */
			break;

		TRACE("\n** Type %d mismatch with asked %d, skip it\n",
				(int)c, (int)*type);
		/* type not matched, proceed to next packet */
	}
	CHKSUM(chksum, (byte_t)*type);

	/* get type of the packet */
	// GETBYTE(order, GetCh);
#ifdef	RAWDATA
	{
		errcode_t retcode;
		if ((retcode = GetByte2(h, GetCh)) < 0) RETURN(retcode);
		*order = *h;
	}
#else
	GETCH(h + 1, GetCh);
	if (Hexbyte2Byte(order, h) < 0) { RETURN(ERR_HEX2BYTE); }
#endif	/* RAWDATA */
	CHKSUM(chksum, *order);

	/* get length of the packet */
	GETBYTE(&c, GetCh);	/* high byte */
	CHKSUM(chksum, c);
	GETBYTE(&t, GetCh);	/* low byte */
	CHKSUM(chksum, t);
	pktlen = (c << 8 | t);

	if (pktlen > MAX_PKTLEN || (buf && pktlen > size)) {
		TRACE("\n** Buf size not enough (pktlen=%d, bufsize=%d)\n", 
				(int)pktlen, (int)size);
		RETURN(ERR_LEN);
	}

	/* get the packet body, compute check sum by the way */
	for (i = 0; i < pktlen; i++) {
		if (buf) {
			GETBYTE(&buf[i], GetCh);
			CHKSUM(chksum, buf[i]);
		} else {	/* absorb the packet if buf == NULL */
			GETBYTE(&c, GetCh);
			CHKSUM(chksum, c);
		}

		/* get checksum every CHK_LEN */
		if ((i % CHK_LEN) == 0) {
			GETBYTE(&c, GetCh);
			if (chksum != c) RETURN(ERR_CHKSUM);
		}
	}

	/* get checksum */
	GETBYTE(&c, GetCh);
	if (chksum != c) RETURN(ERR_CHKSUM);

	/* get Physical Packet Tail */
	GETCH(&c, GetCh);
	if (c != MARK_TAIL) RETURN(ERR_FORMAT);

	RETURN((errcode_t)pktlen);
}
/* Receive a packet from the stream with type 'type'
 * Packets of unmatched types are discarded 
 */
static errcode_t RecvPacketMatch(pktype_t type, byte_t* order, byte_t* buf, 
		int size, int (*GetCh)(void)) 
{
	if (type <= 0) RETURN(ERR_PKTYPE);

	RETURN(RecvPacket(&type, order, buf, size, GetCh));
}

/* Reset message */
errcode_t Reset(pktype_t type, int (*PutCh)(int c)) {
	/* reset message order */
	g_rorder = g_sorder = 0;

	TRACE("\n=> Send Reset RESET\n");
	RETURN(SendPacket(type, 0, NULL, 0, PutCh));
}

/* Send packet with ACK to guarantee ok */
static errcode_t SendPacketAck(pktype_t type, byte_t *buf, int size, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
#ifdef	ACK
	byte_t ack[ACK_LEN], *len = ack + 1, order;
	signed char* status = (signed char*)ack;

	errcode_t retcode;
	pktype_t rtype = PKTYPE_RECV_ACK;

	while (1) {
		TRACE("\n=> To send a packet (type=%d,order=%d,size=%d)\n", 
				(int)type, (int)g_sorder, size);

		while ((retcode = SendPacket(type, g_sorder, buf, size, PutCh)) 
				< 0)
		{
			TRACE("\n** Error on sending a packet (type=%d,order=%d), "
					"try again\n", (int)type, (int)g_sorder);
		}

		/* receive the ACK */
		while (1) {
			errcode_t rcode;

			TRACE("\n<= Wait for send-ack (type=%d)\n", rtype);

			rcode = RecvPacketMatch(rtype, &order, ack, ACK_LEN, 
					GetCh);

			/* deal with RESET */
			if (rcode == ERR_RESET) {
				TRACE("\n** RESET breaks SendPacketAck\n");
				RETURN(ERR_RESET);
			} 
			/* error receiving the ack */
			else if (rcode < 0) {
				TRACE("\n** Error getting an internal ack, "
						"try next\n");
			}
			/* check for order */
			else if (order != g_sorder) {
				TRACE("\n<= Receive an internal ack (type=%d), "
						"out of order (%d, expect %d), "
						"try next\n", (int)rtype, 
						(int)order, (int)g_sorder);
			}
			else {
				TRACE("\n<= Receive an internal ack (type=%d,"
						"value=%d/%d,order=%d)\n",
						(int)rtype, (int)*status, 
						BYTES2INT(len), (int)order);
				break;
			}
		} 

		if (*status >= 0) break;

		TRACE("\n** Need to resend the packet\n");

		self_resend_count++;
	}

	g_sorder++;

	assert(size == BYTES2INT(len)); /* ack[1] contains the received size */

	RETURN(retcode);
#else
	/* order is not used */
	RETURN(SendPacket(type, 1, buf, size, PutCh));
#endif
	/* todo: deal with fails on Send & Recv themself */
}

/* Send packet with ACK to guarantee ok */
static errcode_t RecvPacketAck(pktype_t type, byte_t* buf, int size, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
	byte_t order;

#ifdef	ACK
	byte_t ack[ACK_LEN], *len = ack + 1;
	signed char* status = (signed char*)ack;

	int num_resend = 0;
	errcode_t pktlen;

	while (1) {
		pktype_t rtype = (pktype_t)0;
		byte_t rbuf[MAX_PKTLEN];
		int i;
	       
		TRACE("\n<= To receive a packet (type=%d,bufsize=%d)\n", 
				(int)rtype, size);

		// pktlen = RecvPacketMatch(type, &order, buf, size, GetCh);
		pktlen = RecvPacket(&rtype, &order, rbuf, MAX_PKTLEN, GetCh);

		/* deal with RESET */
		if (pktlen == ERR_RESET) {
			TRACE("\n** RESET breaks RecvPacketAck\n");
			RETURN(ERR_RESET);
		} 
		/* check if type matches */
		else if (0 < rtype && rtype < PKTYPE_MAXTYPE && rtype != type) {
			TRACE("\n** Type %d mismatch with expected %d, skip it\n",
					(int)rtype, (int)type);
			continue;
		}
		/* deal with error getting packet */
		else if (pktlen < 0) {
			TRACE("\n** Error receiving a packet (type=%d), "
					"ask for resend\n", rtype);

			order = g_rorder; /* prevent error getting 'order' */
			*status = (signed char)pktlen;
			INT2BYTES(len, 0);
			peer_resend_count++;
		}
		/* successfully getting a packet, check the order */
		else if (order != g_rorder) {
			TRACE("\n<== Receive a packet (type=%d) out of expected order "
					"(%d, expect %d), try next\n", 
					(int)type, (int)order, (int)g_rorder);
			continue;
		}
		/* check length */
		else if (pktlen > size) {
			TRACE("\n<== Receive a packet (type=%d,order=%d) with "
					"larget size %d (expect %d)\n", 
					(int)type, (int)order, (int)pktlen, size);
			RETURN(ERR_LEN);
		}
		/* successfully getting a packet, with correct order */
		else {
			TRACE("\n<== Receive a packet (type=%d,order=%d)\n", 
					(int)type, (int)order);
			*status = 0;
			INT2BYTES(len, pktlen);
			/* copy packet */
			memcpy(buf, rbuf, pktlen);
		}

		/* reply with ACK */
		rtype = PKTYPE_SEND_ACK;

		TRACE("\n=> Send internal ack(s) (type=%d,value=%d/%d,order=%d)\n",
				(int)rtype, (int)*status, BYTES2INT(len),
				(int)order);

		for (i = 0; i < NUM_ACK; i++) {
			while (SendPacket(rtype, order, ack, ACK_LEN, PutCh) < 0) 
			{
				TRACE("\n** Error on sending internal ack(s) "
						"(type=%d,value=%d/%d, order=%d),"
						" try again\n",
						(int)rtype, (int)*status, 
						BYTES2INT(len), (int)order);
			}	
		}

		if (pktlen >= 0) break;

		/* if num_resend > MAX_RESEND, it's an critical error */
		if (++num_resend > MAX_RESEND) {
			Reset(PKTYPE_SEND_RESET, PutCh);
			RETURN(ERR_RESET);
		}

	}

	/* advance to next number */
	g_rorder++;

	RETURN(pktlen);
#else
	RETURN(RecvPacketMatch(type, &order, buf, size, GetCh));
#endif
	/* todo: deal with fails on Send & Recv themself */
}

/* Send the content of the file fd through PutCh */
static errcode_t SendFileContent(int fd, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
	int fsize = 0, n;
	byte_t buf[MAX_PKTLEN];

	if (!GetCh || !PutCh) RETURN(ERR_MEMORY);
	
	/* if error, set subtype to EOF or ? */
	if (fd < 0) {
		buf[0] = SUBTYPE_EOF;
		if (SendPacketAck(PKTYPE_SEND_NORMAL, buf, 1, GetCh, PutCh) 
				== ERR_RESET)
		{
			RETURN(ERR_RESET);
		}
		RETURN(ERR_OPEN);
	}

	/* transfer the file */
	do {
		/* Get a block of data from the file to be sent */
		n = read(fd, buf + 1, MAX_PKTLEN - 1);

		if (n < 0) {
			/* error occure, set subtype to ABORT */
			buf[0] = SUBTYPE_ABORT;
			n = 0;
			fsize = ERR_READ;
		} else if (n == 0) {
			/* EOF, set subtype to EOF */
			buf[0] = SUBTYPE_EOF;
		} else	{
			/* normal content */
			buf[0] = SUBTYPE_CONTENT;
			fsize += n;
		}

		/* Send the packet by PutCh */
		TRACE("\n=> Send a packet of file content (size=%d,fsize=%d)\n", 
				n, fsize); 
		if (SendPacketAck(PKTYPE_SEND_NORMAL, buf, n + 1, GetCh, PutCh)
				== ERR_RESET) 
		{
			RETURN(ERR_RESET);
		}

#ifdef MASTER
		printf("\015Send %d bytes", fsize); 
#endif
	} while (n > 0);

	TRACE("\n=> End of sending file contents, fsize=%d\n", fsize); 
	RETURN((errcode_t)fsize);
}

/* Receive the file 'fname' through GetCh */
static errcode_t RecvFileContent(int fd, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
	byte_t buf[MAX_PKTLEN];
	int fsize = 0;

	if (!GetCh || !PutCh) RETURN(ERR_MEMORY);

	TRACE("\n<= Start to receive file\n"); 
	
	/* get the body of the file */
	while (1) {
		int len = 0, size;

		/* get a packet through GetCh */
		size = RecvPacketAck(PKTYPE_RECV_NORMAL, buf, MAX_PKTLEN, 
				GetCh, PutCh);

		/* check for RESET first */
		if (size == (int)ERR_RESET) RETURN(ERR_RESET);

		/* size == 1 meaning EOF or error */
		if (size < 0 || --size == 0 || buf[0] != SUBTYPE_CONTENT) 
			break;

		fsize += size;

		TRACE("\n<= Get a packet of file content (size=%d,fsize=%d)\n", 
				size, fsize); 

#ifdef MASTER
		printf("\015Receive %d bytes", fsize); 
#endif

		/* write the packet to the file */
		if (fd >= 0) {
			do {
				int n = write(fd, buf + 1 + len, size - len);

				if (n < 0) RETURN(ERR_WRITE);

				len += n;

			} while (len < size);
		}
	}

	switch (buf[0]) {
		case SUBTYPE_EOF: 
			TRACE("\n<= End of receiving file contents, fsize=%d\n",
					fsize); 
			return (errcode_t)fsize;
		case SUBTYPE_ABORT:
			TRACE("\n<= Get an ERR_ABORT message at fsize=%d\n", fsize); 
			RETURN(ERR_ABORT);
		default:
			TRACE("\n<= Get an ERR_FORMAT message at fsize=%d\n", fsize); 
			RETURN(ERR_FORMAT);
	}
}

/* Send request */
static errcode_t SendRequest(subtype_t type, const char *fname, 
		int (*GetCh)(), int (*PutCh)(int c)) 
{
	int size;
	char *basename;
	byte_t buf[MAX_PKTLEN];

	if (!fname || !GetCh || !PutCh) RETURN(ERR_MEMORY);

	/* get the base file name */
	basename = strrchr(fname, PATH_DLMTR);
	basename = basename ? (basename + 1) : (char*) fname;

	/* send the packet header */
	size = strlen(basename) + 2;	/* subtype & \0 */
	if (size > MAX_PKTLEN) RETURN(ERR_LEN);

	buf[0] = (byte_t)type;
	strcpy((char*)(buf + 1), (char*)basename);

	/* reset slave first */
	if (Reset(PKTYPE_SEND_RESET, PutCh) == ERR_RESET) 
		RETURN(ERR_RESET);

	TRACE("\n=> Issue a request (subtype=%d)\n", (int)type); 

	RETURN(SendPacketAck(PKTYPE_SEND_REQUEST, buf, size, GetCh, PutCh));
}

/* Send the file 'fname' through PutCh 
 * Return file size on success
 */
errcode_t SendFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c)) {
	int fd, size;

	if (!fname || !GetCh || !PutCh) RETURN(ERR_MEMORY);

	/* open the file to send */
	if ((fd = open(fname, O_RDONLY|O_BINARY)) < 0) RETURN(ERR_OPEN);

	/* send 'send file' request */
	if (SendRequest(SUBTYPE_SENDFILE, fname, GetCh, PutCh) == ERR_RESET) {
		close(fd);
		RETURN(ERR_RESET);
	}

#ifdef	ACK
	{
		errcode_t retcode;
		signed char status;

		/* wait for an ACK */
		retcode = RecvPacketAck(PKTYPE_RECV_OPENFILE, (byte_t*)&status, 
				1, GetCh, PutCh);

		if (retcode < 0) {
			close(fd);
			RETURN(retcode);
		}

		TRACE("\n<= Get a status %d from the receiver\n", (int)status);

		if (status < 0) {
			close(fd);
			RETURN((errcode_t)status);
		}
	}
#endif

	/* send the file contents */
	size = SendFileContent(fd, GetCh, PutCh);

	/* close the opened file */
	if (close(fd) < 0) { RETURN(ERR_CLOSE); }

	RETURN((errcode_t)size);
}

/* Receive the file 'fname' through GetCh 
 * Return file size on success
 */
errcode_t RecvFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c)) {
	int fd, size;

	if (!fname || !GetCh || !GetCh) RETURN(ERR_MEMORY);
	
	/* send 'send file' request */
	if (SendRequest(SUBTYPE_RECVFILE, fname, GetCh, PutCh) == ERR_RESET)
		RETURN(ERR_RESET);

#ifdef	ACK
	{
		errcode_t retcode;
		signed char status;

		/* wait for an ACK */
		retcode = RecvPacketAck(PKTYPE_RECV_OPENFILE, (byte_t*)&status, 
				1, GetCh, PutCh);

		if (retcode < 0) RETURN(retcode);

		TRACE("\n<= Get a status %d from the receiver\n", (int)status);

		if (status < 0) RETURN((errcode_t)status);
	}
#endif

	/* open file for write */
	if ((fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0644)) < 0) 
		RETURN(ERR_OPEN);

	/* send the file contents */
	size = RecvFileContent(fd, GetCh, PutCh);

	/* close the opened file */
	if (close(fd) < 0) RETURN(ERR_CLOSE);

	if (size < 0) unlink(fname);

	RETURN((errcode_t)size);
}

/* Ask slave to stop */
errcode_t StopHotsync(int (*GetCh)(), int (*PutCh)(int c)) {
	RETURN(SendRequest(SUBTYPE_STOP, "", GetCh, PutCh));
}

/* Return error string for a retcode */
const char *ErrString(errcode_t code) {
	switch (code) {
		case ERR_MEMORY:
			return "Pointer parameter error";
		case ERR_LEN:
			return "Packet length error";
		case ERR_FORMAT:
			return "Packet format error";
		case ERR_OPEN:
			return "File open error";
		case ERR_CLOSE:
			return "File close error";
		case ERR_READ:
			return "File read error";
		case ERR_WRITE:
			return "File write error";
		case ERR_PUTCH:
			return "Data sending error";
		case ERR_GETCH :
			return "Data receiving error";
		case ERR_BYTE2HEX:
			return "Byte2Hex conversion error";
		case ERR_HEX2BYTE:
			return "Hex2Byte conversion error";
		case ERR_CHKSUM:
			return "Check sum error";
		case ERR_ABORT:
			return "Transmission abort error";
		case ERR_PROTOCOL:
			return "Protocol error";
		case ERR_UNKNOWN:
			return "Unknown error";
		case ERR_PKTYPE:
			return "Packet type error";
		case ERR_RESET:
			return "Transmission is reseted";
		case ERR_TIMEOUT:
			return "Timeout occours";
		case ERR_GETBYTE:
			return "Data receiving error";
		case ERR_PUTBYTE:
			return "Data sending error";
		case ERR_RANGE:
			return "Data range error";
		default:
			return "Unknown error code";
	}
}

#if	defined(MASTER) || defined(SLAVE)

/* Implement getchar & putchar for ttySin & ttySout */
static int ttySin = 0;	/* default to stdin */
static int ttySout = 1;	/* default to stdout */

/* Open ttySin & ttySout */
static int OpenTtys() {
#ifdef	OPENTTY
	/* open ttySin & ttySout */
	if ((ttySin = ttySout = open(TTYS, O_RDWR | O_SYNC)) < 0) {
		perror("OpenTtys");
		exit(2);
	}
#endif

	return ttySin;
}

/* Close ttySin & ttySout */
static int CloseTtys() {
#ifdef	OPENTTY
	return close(ttySin);
#else
	return 1;
#endif
}

#ifdef	TIMEOUT
/* Listen on ttySin for 'TIME_OUT' period */
static errcode_t ListenTtyS() {
	/* implement time-out */
	fd_set rfds;
	struct timeval tv;

	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&rfds);
	FD_SET(ttySin, &rfds);

	/* set time out value */
	tv.tv_sec = TIME_OUT;
	tv.tv_usec = 0;

	if (select(1, &rfds, NULL, NULL, &tv) != 1)
		return ERR_TIMEOUT;	/* time out */

	return (errcode_t)0;
}
#endif	/* TIMEOUT */

/* Get a char from ttySin */
static int GettyS(void) {
	byte_t c;
	int n;

#ifdef	TIMEOUT
	if (ListenTtyS() < 0) return EOF;
#endif	/* TIMEOUT */
		
	n = read(ttySin, &c ,1);

	/* implement the semantic of getchar */
	if (n <= 0) return EOF;
	else return c;

	/* may need to consider n == 0 & INTR case */
}

/* Put a char into ttySout */
static int PuttyS(int c) {
	int n = write(ttySout, &c ,1);

	/* implement the semantic of putchar */
	if (n <= 0) return EOF;
	else return c;
}
#endif	/* defined(MASTER) || defined(SLAVE) */

#ifdef	MASTER

static void ChkParam(int argc, char *argv[], int required) {
	if (argc < required) {
		fprintf(stderr, "Usage: %s <s|r> <file>\n", argv[0]);
		exit(1);
	}
}

/* Master main */
int main(int argc, char *argv[]) {
	errcode_t retcode;

	ChkParam(argc, argv, 2);

	/* open tty S0 */
	OpenTtys();

	/* issue command */
	switch (*argv[1]) {
		case 's':
		case 'S':
			ChkParam(argc, argv, 3);
			retcode = SendFile(argv[2], GettyS, PuttyS);
			break;
		case 'r':
		case 'R':
			ChkParam(argc, argv, 3);
			retcode = RecvFile(argv[2], GettyS, PuttyS);
			break;
		case 'q':
		case 'Q':
			retcode = StopHotsync(GettyS, PuttyS);
			break;
		default:
			ChkParam(argc, argv, 0);
			return 1;
	}

	if (retcode == ERR_RESET)
		printf("\nMaster is reseted!\n");
	else if (retcode < 0)
		printf("\nError occurs!\n");
	else
		printf("\nJob finishes.\n");

	CloseTtys();

	printf("Resend count: master = %d, slave = %d, retcode = %d\n", 
			self_resend_count, peer_resend_count, (int)retcode);

	return (int)retcode;
}
#endif	/* MASTER */

/* Slave main & utilities */

#ifdef	SLAVE

/* Turn off echoing */
static struct termios EchoOff(int tty) {
	struct termios old, new;

        tcgetattr(tty, (void *) &old);

        memcpy(&new, &old, sizeof(struct termios));

        new.c_lflag &= ~(ICANON | ECHO | ECHONL);

        tcsetattr(tty, TCSANOW, (void *) &new);

        return old;
}

/* Restore terminal setting */
static int RestoreTios(int tty, struct termios old) {
        tcsetattr(tty, TCSANOW, (void *) &old);

        return 1;
}

/* Slave main */
int main(int argc, char *argv[]) {
	int stop = 0;
	char *datapath;
	int tty;
	struct termios old_tios;

	/* set data directory */
	if (argc < 2) 
		datapath = SLAVEDIR;
	else
		datapath = argv[1];

	/* change working directory to datapath */
	mkdir(datapath, 0755);
	if (chdir(datapath) != 0) {
		fprintf(stderr, "Error changing working directory %s\n", 
				datapath);
		exit(1);
	}

	/* open tty S0 */
	tty = OpenTtys();
	
	/* echo off */
	old_tios = EchoOff(tty);

	/* service loop */
	while (!stop) {
		char buf[MAX_PKTLEN], *fname = buf + 1;
		int fd;
		errcode_t retcode = 0;

#ifdef	TIMEOUT
		while (ListenTtyS() < 0);
#endif	/* TIMEOUT */

		TRACE("\n<= Ready to receive requests\n");
		if (RecvPacketAck(PKTYPE_RECV_REQUEST, buf, MAX_PKTLEN, 
					GettyS, PuttyS) < 0) 
		{
			continue;
		}

		switch (buf[0]) {
			case SUBTYPE_SENDFILE:
				TRACE("\n<= Request = SENDFILE '%s'\n", fname);
				if ((fd = open(fname, 
					O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) 
				{
					TRACE("\n** Fail open file\n");
					buf[0] = (byte_t)ERR_OPEN;
				}
#ifdef	ACK
				TRACE("\n=> Send an ack (%d) to the sender\n", 
						(int)buf[0]);
				retcode = SendPacketAck(PKTYPE_SEND_OPENFILE, 
						buf, 1, GettyS, PuttyS);
				if (retcode < 0 || fd < 0) break;
#endif
				retcode = RecvFileContent(fd, GettyS, PuttyS);
				close(fd);
				break;
			case SUBTYPE_RECVFILE:
				TRACE("\n<= Request = RECVFILE '%s'\n", fname);
				if ((fd = open(fname, O_RDONLY)) < 0) {
					TRACE("\n** Fail open file\n");
					buf[0] = (byte_t)ERR_OPEN;
				}
#ifdef	ACK
				TRACE("\n=> Send an ack (%d) to the sender\n", 
						(int)buf[0]);
				retcode = SendPacketAck(PKTYPE_SEND_OPENFILE, buf, 1, 
						GettyS, PuttyS);
				if (retcode < 0 || fd < 0) break;
#endif
				retcode = SendFileContent(fd, GettyS, PuttyS);
				close(fd);
				break;
			case SUBTYPE_STOP:
				TRACE("\n<= Request = STOP\n");
				stop = 1;
				break;
			default:
				Reset(PKTYPE_SEND_RESET, PuttyS);
				continue;
		}
	}

	/* restore terminal setting */
	RestoreTios(tty, old_tios);

	CloseTtys();

	return 0;
}
#endif	/* SLAVE */

