/*
 * hotsync.h
 *
 * Description:
 *   Header file for hotsync.c
 *
 * Author:
 *   William Liang @ Wiscore Inc.
 *
 * Date: $Date: 2001/12/05 07:04:45 $
 * Version: $Revision: 1.3 $
 */

/* Error codes */
typedef enum errcode_s {
	ERR_MEMORY	= -1,
	ERR_LEN		= -2,
	ERR_FORMAT	= -4,
	ERR_OPEN	= -5,
	ERR_CLOSE	= -6,
	ERR_READ	= -7,
	ERR_WRITE	= -8,
	ERR_PUTCH	= -9,
	ERR_GETCH	= -10,
	ERR_BYTE2HEX	= -11,
	ERR_HEX2BYTE	= -12,
	ERR_CHKSUM	= -13,
	ERR_ABORT	= -14,
	ERR_PROTOCOL	= -15,
	ERR_UNKNOWN	= -16,
	ERR_PKTYPE	= -17,
	ERR_RESET	= -18,
	ERR_TIMEOUT	= -19,
	ERR_GETBYTE	= -20,
	ERR_PUTBYTE	= -21,
	ERR_RANGE	= -22
} errcode_t;

extern errcode_t SendFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c));
extern errcode_t RecvFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c));
errcode_t StopHotsync(int (*GetCh)(), int (*PutCh)(int c));

extern const char *ErrString(errcode_t code);
