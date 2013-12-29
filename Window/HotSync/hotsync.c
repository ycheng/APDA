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
 * Date: $Date: 2001/11/29 14:09:03 $
 * Version: $Revision: 1.8 $
 */

/* Uncomment the following two lines if you are to compile under VC++ */
/*
#include <stdafx.h>
#define VC 
*/

#ifdef	VC
#include <io.h>
#else
#include <unistd.h>
#endif

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

/* Uncomment the following line if you want the program to open ttyS0 itself */
/* #define OPENTTY */

/* Uncomment the following line if you want ACK,
 * note: this part is not tested yet! */
/* #define ACK */

/* Uncomment the following line if you want debug mode */
/* #define DEBUG */

/* Uncomment the following line if you want to abort immediately 
 * whenever an error occures, provided that DEBUG mode is used */
/* #define CRITICAL */

/* -- End of Configuration part -- */

/* Directory to hold slave files */
#define SLAVEDIR	"/data"

/* Packet size */
#ifndef	MAXBYTE
#define MAXBYTE		255
#endif
#define MAX_PKTLEN	MAXBYTE

/* Size of 'short packet' */
#define SHORT_PACKET	5

/* Number of sending for short packet */
#define NUM_SEND	3

/* Length of packet to add a check sum 
 * better less than SHORT_PACK * NUM_SEND */
#define CHK_LEN		(SHORT_PACKET * 2 / 3)

/* Path of device ttyS0 */
#define	TTYS0		"/dev/ttyS0"

/* Physical packet head & tail */
#define CHAR_HEAD	'~'
#define CHAR_TAIL	':'
#define CHAR_LF		0x0a
#define CHAR_CR		0x0d

/* Packet type */
typedef enum pktype_s {
	/* value 0 is used to mean all kind of packet */
	PKTYPE_REQUEST	=	1,
	PKTYPE_OPENFILE,
	PKTYPE_FINISH,
	PKTYPE_NORMAL,
	PKTYPE_INTERNALACK,	/* Send/RecvPacketAck use only */
	PKTYPE_OOB,
} pktype_t;

/* SubPacket type */
typedef enum subtype_s {
	SUBTYPE_SENDFILE,
	SUBTYPE_RECVFILE,
	SUBTYPE_EOF,
	SUBTYPE_CONTENT,
	SUBTYPE_ABORT,
	SUBTYPE_STOP,
	SUBTYPE_RESET
} subtype_t;

/* note: number of each type must be < 256 */ 

/* Path delimitor */
#ifdef	WIN32
#define CHAR_PATH_DLMTR	'\\'
#else
#define CHAR_PATH_DLMTR	'/'
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
		fprintf(stderr, "Error: %s, %d: %d (%s)\n",	\
			__FILE__, __LINE__, (retcode), #code);	\
		exit((retcode));				\
	} else							\
		return (retcode);				\
}
#else
#define RETURN(code) { return (code); }
#endif

/* Output trace info */
#ifndef	VC
#define TRACE(msg...) {				\
	fprintf(stderr, ## msg); 		\
	fflush(stderr); 			\
}
#endif

#else

#define RETURN(code) { return (code); }

#ifndef	VC
#define TRACE(msg...)
#endif

#endif

/* Get a char from the stream and check for error */
#define GETCH(c, GetCh)	{				\
	errcode_t i;					\
							\
	if ((i = (errcode_t)(GetCh)()) < 0) {		\
		TRACE("Error GetCh: '%c'(%d)",		\
			(byte_t)i, (int)i);		\
		RETURN(ERR_GETCH);			\
	}						\
	*(c) = (byte_t)i;				\
	TRACE("%c", *c); 				\
}

/* Put a char to the stream and check for error */
#define PUTCH(c, PutCh)	{				\
	if ((PutCh)((c)) < 0) {				\
		TRACE("Error PutCh: '%c'(%d)",		\
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
#define CHKSUM(chksum, byte)				\
	((chksum) = (byte_t)((chksum) + (byte)))

/* Convert a 0-15 decimal value into its hex letter */
static errcode_t Halfbyte2Hexchar(byte_t* x, byte_t halfbyte) { 
	if (/* 0 <= halfbyte && */ halfbyte <= 9)
		*x = halfbyte + '0';
	else if (10 <= halfbyte && halfbyte <= 15)
		*x = halfbyte - 10 + 'a';
	else
		RETURN(ERR_BYTE2HEX);

	return (errcode_t)0;
}

/* Convert a hex letter into its decimal value (0-15) */
static errcode_t Hexchar2Halfbyte(byte_t* halfbyte, byte_t x) { 
	if (isdigit(x))
		*halfbyte = x - '0';
	else if ('a' <= x && x <= 'f')
		*halfbyte = x - 'a' + 10;
	else if ('A' <= x && x <= 'F')
		*halfbyte = x - 'A' + 10;
	else
		RETURN(ERR_HEX2BYTE);

	return (errcode_t)0;
}

/* Convert a byte into its hex string 'byte_t hexbyte[2]' */
static errcode_t Byte2Hexbyte(byte_t* hexbyte, byte_t c) { 
	byte_t hi, lo;
	
	if (!hexbyte) RETURN(ERR_MEMORY);

	hi = c >> 4; 
	lo = c & 0x0f;
	
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

	*byte = (hi << 4 | lo);

	return (errcode_t)0;
}

/* Put a byte into the stream by PutCh */
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

/* Get a byte from the stream by GetCh */
static errcode_t GetByte(byte_t* byte, int (*GetCh)()) {
	byte_t hexbyte[2];

	/* get two char from the stream */
	GETCH(&hexbyte[0], GetCh);
	GETCH(&hexbyte[1], GetCh);

	// TRACE(",");

	/* convert it into a byte */
	return Hexbyte2Byte(byte, hexbyte);
}

/* Send a packet into the stream */
static errcode_t SendPacket(pktype_t type, byte_t order, byte_t *buf, int size, 
		int (*PutCh)(int c)) 
{
	int i, j, num_send = (size <= SHORT_PACKET) ? NUM_SEND : 1;

	if (!PutCh || (size > 0 && !buf)) RETURN(ERR_MEMORY);

	if (size > MAX_PKTLEN) RETURN(ERR_LEN);

	for (j = 0; j < num_send; j++) {
		byte_t chksum = 0;

		/* put Physical Packet Head */
		PUTCH(CHAR_HEAD, PutCh);

		/* put packet type */
		PUTBYTE((byte_t)type, PutCh);
		CHKSUM(chksum, (byte_t)(type));

		/* put packet type */
		PUTBYTE(order, PutCh);
		CHKSUM(chksum, order);

		/* put length of the packet */
		PUTBYTE((byte_t)size, PutCh);
		CHKSUM(chksum, (byte_t)size);

		/* put the packet body, compute check sum by the way */
		for (i = 0; i < size; i++) {
			PUTBYTE(buf[i], PutCh);
			CHKSUM(chksum, buf[i]);

			/* put checksum every CHK_LEN */
			if (i % CHK_LEN) { PUTBYTE(chksum, PutCh); }
		}

		/* put checksum */
		PUTBYTE(chksum, PutCh);

		/* put Physical Packet Tail */
		PUTCH(CHAR_TAIL, PutCh);

		/* put Physical Packet CR */
		PUTCH(CHAR_LF, PutCh);
		PUTCH(CHAR_CR, PutCh);

		fflush(0);
	}

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
	int oob = 0;
	byte_t pktlen, i, c, chksum = 0;

	if (!GetCh || !type || !order) RETURN(ERR_MEMORY);

	if (buf && size < 0) RETURN(ERR_LEN);
	
	while (1) {
		/* get Physical Packet Head */
		do { GETCH(&c, GetCh); } while (c != CHAR_HEAD);

		/* get type of the packet */
		GETBYTE(&c, GetCh);

#ifdef SLAVE
		/* check if this is an out-of-bound message, only for slave */
		if ((pktype_t)c == PKTYPE_OOB) {
			TRACE("Get an OOB packet\n");
			*type = (pktype_t)c;
			oob = 1; /* enter OOB mode */
			break;
		}
#endif

		/* check if type is specified */
		if (*type <= 0) {	/* accept any type of packet */
			*type = (pktype_t)c;
			break;
		} else if (*type == c)	/* type matched */
			break;

		TRACE("Type (%d) mismatch with asked (%d), skip it\n",
				(int)c, (int)*type);
		/* type not matched, proceed to next packet */
	}

	CHKSUM(chksum, (byte_t)*type);

	/* get type of the packet */
	GETBYTE(order, GetCh);
	CHKSUM(chksum, *order);

	/* get length of the packet */
	GETBYTE(&pktlen, GetCh);
	CHKSUM(chksum, pktlen);

	if (pktlen > MAX_PKTLEN || (buf && pktlen > size)) {
		TRACE("Buf size not enough (pktlen=%d, bufsize=%d)\n", 
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
		if (i % CHK_LEN) {
			GETBYTE(&c, GetCh);
			if (chksum != c) RETURN(ERR_CHKSUM);
		}
	}

	/* get checksum */
	GETBYTE(&c, GetCh);
	if (chksum != c) RETURN(ERR_CHKSUM);

	/* get Physical Packet Tail */
	GETCH(&c, GetCh);
	if (c != CHAR_TAIL) RETURN(ERR_FORMAT);

	/* OOB must be taken care of in upper level, 
	 * otherwise, it's viewed as an error */
	if (oob) { TRACE("RecvPacket return ERR_OOB\n"); }
	RETURN(oob ? ERR_OOB : (errcode_t)pktlen);
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

/* Send packet with ACK to guarantee ok */
static errcode_t SendPacketAck(pktype_t type, byte_t *buf, int size, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
#ifdef	ACK
	static byte_t order = 0; /* must be protected for multithread */

	byte_t ack[2], rorder;
	signed char* status = (signed char*)ack;
	errcode_t retcode;

	do {
		order++;

		TRACE("Send a packet (type=%d, order=%d)\n", 
				(int)type, (int)order);

		while ((retcode = SendPacket(type, order, buf, size, PutCh)) 
				< 0) 
		{
			TRACE("Error on sending packet (type=%d, order=%d)\n",
					(int)type, (int)order);
		}

		/* receive the ACK */
		do {
			errcode_t rcode;

			while ((rcode = RecvPacketMatch(PKTYPE_INTERNALACK, 
						&rorder, ack, 2, GetCh)) < 0)
			{
				if (rcode == ERR_OOB) {
					TRACE("OOB breaks SendPacketAck\n");
					RETURN(retcode);
				}

				TRACE("Error getting internal ack, try next\n");
			}

			TRACE("Get internal ack (value=%d/%d, order=%d)\n",
					(int)*status,(int)ack[1], (int)rorder);

			if (rorder != order) {
				TRACE("Ack Out-of-Order (%d, but expect %d), "
					"try next\n", rorder, order);
			} else {
				TRACE("Ack obtained (order=%d)\n", order);
			}
		} while (rorder != order);

		if (*status < 0) TRACE("Need to resend the packet\n");

	} while (*status < 0);

	/* ack[1] contains the received size */
	assert(size == ack[1]);

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
	errcode_t pktlen;

	do {
		byte_t ack[2];
		signed char* status = (signed char*)ack;
	       
		pktlen = RecvPacketMatch(type, &order, buf, size, GetCh);

		/* deal with OOB */
		if (pktlen == ERR_OOB) {
			TRACE("OOB breaks RecvPacketAck\n");
			break;
		}

		TRACE("Receive a packet (type=%d, order=%d)\n", 
				(int)type, (int)order);

		*status = (pktlen < 0) ? (signed char)pktlen : 0;
		ack[1] = (pktlen > 0) ? (byte_t)pktlen : 0;

		/* reply with ACK */
		TRACE("Send an internal acks (value=%d/%d, order=%d)\n", 
				(int)*status, (int)ack[1], (int)order);
		while (SendPacket(PKTYPE_INTERNALACK, order, 
					ack, 2, PutCh) < 0) {
			TRACE("Error on sending ack "
				"(value=%d/%d, order=%d)\n",
				(int)*status, (int)ack[1], (int)order);
		}	
	} while (pktlen < 0);

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
		SendPacketAck(PKTYPE_NORMAL, buf, 1, GetCh, PutCh);
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
		TRACE("Send a packet of file content, fsize=%d\n", fsize); 
		SendPacketAck(PKTYPE_NORMAL, buf, n + 1, GetCh, PutCh);

#ifdef MASTER
		printf("\015Send %d bytes", fsize); 
#endif
	} while (n > 0);

	TRACE("End of sending file contents, fsize=%d\n", fsize); 
	RETURN((errcode_t)fsize);
}

/* Receive the file 'fname' through GetCh */
static errcode_t RecvFileContent(int fd, 
		int (*GetCh)(void), int (*PutCh)(int c)) 
{
	byte_t buf[MAX_PKTLEN];
	int fsize = 0;

	if (!GetCh || !PutCh) RETURN(ERR_MEMORY);

	TRACE("Start to receive file\n"); 
	
	/* get the body of the file */
	while (1) {
		int len = 0, size;

		/* get a packet through GetCh */
		size = RecvPacketAck(PKTYPE_NORMAL, buf, MAX_PKTLEN, 
				GetCh, PutCh);

		/* size == 1 meaning EOF or error */
		if (size < 0 || --size == 0 || buf[0] != SUBTYPE_CONTENT) 
			break;

		fsize += size;

		TRACE("Get a packet of file content, fsize=%d\n", fsize); 

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
			TRACE("End of receiving file contents, fsize=%d\n",
					fsize); 
			return (errcode_t)fsize;
		case SUBTYPE_ABORT:
			TRACE("Get an ERR_ABORT message at fsize=%d\n", fsize); 
			RETURN(ERR_ABORT);
		default:
			TRACE("Get an ERR_FORMAT message at fsize=%d\n", fsize); 
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
	basename = strrchr(fname, CHAR_PATH_DLMTR);
	basename = basename ? (basename + 1) : (char*) fname;

	/* send the packet header */
	size = strlen(basename) + 2;	/* subtype & \0 */
	if (size > MAX_PKTLEN) RETURN(ERR_LEN);

	buf[0] = type;
	strcpy((char*)(buf + 1), (char*)basename);

	TRACE("Issue a request (type=%d)\n", (int)type); 

	RETURN(SendPacketAck(PKTYPE_REQUEST, buf, size, GetCh, PutCh));
}

/* Send the file 'fname' through PutCh 
 * Return file size on success
 */
errcode_t SendFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c)) {
	int fd, size;

	if (!fname || !GetCh || !PutCh) RETURN(ERR_MEMORY);

	/* open the file to send */
	if ((fd = open(fname, O_RDONLY)) < 0) RETURN(ERR_OPEN);

	/* send 'send file' request */
	SendRequest(SUBTYPE_SENDFILE, fname, GetCh, PutCh);

#ifdef	ACK
	{
		errcode_t retcode;
		signed char status;

		/* wait for an ACK */
		retcode = RecvPacketAck(PKTYPE_OPENFILE, (byte_t*)&status, 
				1, GetCh, PutCh);

		if (retcode < 0) RETURN(retcode);

		TRACE("Get an status %d from the receiver\n", (int)status);

		if (status < 0) RETURN((errcode_t)status);
	}
#endif

	/* send the file contents */
	size = SendFileContent(fd, GetCh, PutCh);

	/* close the opened file */
	if (close(fd) < 0) RETURN(ERR_CLOSE);

	RETURN((errcode_t)size);
}

/* Receive the file 'fname' through GetCh 
 * Return file size on success
 */
errcode_t RecvFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c)) {
	int fd, size;

	if (!fname || !GetCh || !GetCh) RETURN(ERR_MEMORY);
	
	/* send 'send file' request */
	SendRequest(SUBTYPE_RECVFILE, fname, GetCh, PutCh);

#ifdef	ACK
	{
		errcode_t retcode;
		signed char status;

		/* wait for an ACK */
		retcode = RecvPacketAck(PKTYPE_OPENFILE, (byte_t*)&status, 1, GetCh, PutCh);

		if (retcode < 0) RETURN(retcode);

		TRACE("Get an status %d from the receiver\n", (int)status);

		if (status < 0) RETURN((errcode_t)status);
	}
#endif

	/* open file for write */
	if ((fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) 
		RETURN(ERR_OPEN);

	/* send the file contents */
	size = RecvFileContent(fd, GetCh, PutCh);

	/* close the opened file */
	if (close(fd) < 0) RETURN(ERR_CLOSE);

	if (size < 0) unlink(fname);

	RETURN((errcode_t)size);
}

/* Reset slave */
errcode_t ResetSlave(int (*GetCh)(), int (*PutCh)(int c)) {
	byte_t stype = SUBTYPE_RESET;

	TRACE("Send Reset OOB\n");
	RETURN(SendPacket(PKTYPE_OOB, 0, &stype, 1, PutCh));
}

#ifdef	OPENTTY

/* Implement getchar & putchar for ttyS0 */
static int ttys0 = -1;

/* Open ttyS0 */
static int OpenTtyS0() {
	/* open ttyS0 */
	if ((ttys0 = open(TTYS0, O_RDWR | O_SYNC)) < 0) {
		perror("OpenTtyS0");
		exit(2);
	}

	return ttys0;
}

/* Close ttyS0 */
static int CloseTtyS0() {
	return close(ttys0);
}

/* Get a char from ttyS0 */
static int GettyS0(void) {
	byte_t c;
	int n = read(ttys0, &c ,1);

	/* implement the semantic of getchar */
	if (n <= 0) return EOF;
	else return c;

	/* may need to consider n == 0 & INTR case */
}

/* Put a char into ttyS0 */
static int PuttyS0(int c) {
	int n = write(ttys0, &c ,1);

	/* implement the semantic of putchar */
	if (n <= 0) return EOF;
	else return c;
}

#else

#define GettyS0	getchar
#define PuttyS0	putchar
#define OpenTtyS0()
#define CloseTtyS0()

#endif /* OPENTTY */

/* Master main */

#ifdef	MASTER

static void ChkParam(int argc, char *argv[], int required) {
	if (argc < required) {
		TRACE("Usage: %s <s|r> <file>\n", argv[0]);
		exit(1);
	}
}

int main(int argc, char *argv[]) {
	byte_t c;
	subtype_t stype;

	ChkParam(argc, argv, 2);

	/* open tty S0 */
	OpenTtyS0();

	/* reset slave */
	ResetSlave(GettyS0, PuttyS0);

	/* issue command */
	switch (*argv[1]) {
		case 's':
		case 'S':
			ChkParam(argc, argv, 3);
			stype = SUBTYPE_SENDFILE;
			SendFile(argv[2], GettyS0, PuttyS0);
			break;
		case 'r':
		case 'R':
			ChkParam(argc, argv, 3);
			stype = SUBTYPE_RECVFILE;
			RecvFile(argv[2], GettyS0, PuttyS0);
			break;
		case 'q':
		case 'Q':
			c = stype = SUBTYPE_STOP;
			SendPacketAck(PKTYPE_REQUEST, &c, 1, 
					GettyS0, PuttyS0);
			break;
		default:
			ChkParam(argc, argv, 0);
			return 1;
	}

#ifdef	ACK
	{
		byte_t type;

		RecvPacketAck(PKTYPE_FINISH, &type, 1, GettyS0, PuttyS0);

		if (type == stype) {
			TRACE("Job finishes.\n");
		} else {
			RETURN(ERR_FORMAT);
		}
	}
#endif

	CloseTtyS0();

	return 0;
}
#endif

/* Slave main */

#ifdef	SLAVE
int main(int argc, char *argv[]) {
	int stop = 0;

	/* change working directory to SLAVEDIR */
	if (chdir(SLAVEDIR) != 0) {
		fprintf(stderr, "Error changing working directory "SLAVEDIR"\n");
		exit(1);
	}

	/* open tty S0 */
	OpenTtyS0();

	/* service loop */
	do {
		char buf[MAX_PKTLEN], *fname = buf + 1;
		int fd;

		TRACE("Ready to receive requests\n");
		RecvPacketAck(PKTYPE_REQUEST, buf, MAX_PKTLEN, GettyS0, PuttyS0);

		switch (buf[0]) {
			case SUBTYPE_RESET:
				continue;
			case SUBTYPE_SENDFILE:
				TRACE("Request = SENDFILE '%s'\n", fname);
				if ((fd = open(fname, 
					O_WRONLY|O_CREAT|O_TRUNC, 0644)) < 0) 
				{
					buf[0] = (byte_t)ERR_OPEN;
				}
#ifdef	ACK
				if (SendPacketAck(PKTYPE_OPENFILE, buf, 1, 
						GettyS0, PuttyS0) < 0)
					break;

				TRACE("Send an ack (%d) to the sender\n", 
						(int)buf[0]);
#endif
				if (RecvFileContent(fd, GettyS0, PuttyS0) < 0)
					break;
				break;
			case SUBTYPE_RECVFILE:
				TRACE("Request = RECVFILE '%s'\n", fname);
				if ((fd = open(fname, O_RDONLY)) < 0) 
					buf[0] = (byte_t)ERR_OPEN;
#ifdef	ACK
				if (SendPacketAck(PKTYPE_OPENFILE, buf, 1, 
						GettyS0, PuttyS0) < 0)
					break;

				TRACE("Send an ack (%d) to the sender\n", 
						(int)buf[0]);
#endif
				if (SendFileContent(fd, GettyS0, PuttyS0) < 0)
					break;
				break;
			case SUBTYPE_STOP:
				TRACE("Request = STOP\n");
				stop = 1;
				break;
			default:
				RETURN(ERR_FORMAT);
		}

#ifdef	ACK
		/* signal after completing a command */
		TRACE("Send an request finished ACK to host\n");
		SendPacketAck(PKTYPE_FINISH, buf, 1, GettyS0, PuttyS0);
#endif
	} while (!stop);

	CloseTtyS0();

	return 0;
}
#endif

