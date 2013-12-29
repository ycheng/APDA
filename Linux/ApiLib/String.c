/*========================================================
  String.c
  all routine is running with Platform non-related,
  simulated the list control function in Palm OS.
  Current status is ControlModal free funtion.

  All is Palm related function.
  Completed 12 of 19 List Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0330, 2001 by Jerry Chu
 =========================================================*/
#include "VCommon.h"

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


extern char *Vstrstr (const char *str, const char *token);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrAToI
//
// DESCRIPTION: This routine convert an string to an integer
//
// PARAMETERS:  (const Char *) str - String to convert
//
// RETURNED:    Returns the integer
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 StrAToI(const Char *str)
{
	return	Vatoi(str);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrCat
//
// DESCRIPTION: This routine concatenate one string to another
//
// PARAMETERS:  (Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrCat (Char *dst, const Char* src)
{
	return	Vstrcat (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrChr
//
// DESCRIPTION: This routine look for a character within a string.
//
// PARAMETERS:  (const Char *) str - string to search
//					 (WChar) chr - character to search for
//
// RETURNED:    Returns a pointer to the first occurrenc of character
//					 in str. Return NULL if the character is not found
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrChr (const Char *str, WChar chr)
{
	return	Vstrchr (str, chr);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrCompare
//
// DESCRIPTION: This routine compare two strings.
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns 0 if the strings match.
//				Returns a positive number if s1 sorts after s2.
//				Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 StrCompare (const Char *dst, const Char* src)
{
	return	Vstrcmp (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrCopy
//
// DESCRIPTION: This routine copy one string to another.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrCopy (Char *dst, const Char* src)
{
	return	Vstrcpy (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrIToA
//
// DESCRIPTION: This routine convert an integer to ASCII
//
// PARAMETERS:  (Char *) s - String pointer to store results
//				(Int32) i - Integer to convert
//
// RETURNED:    Returns the string pointer s.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/12/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char *StrIToA(Char *s, Int32 i)
{
	int	count=0;
	int	dec, num;
	char	buffer[11];

	do {
		dec = i%10;
		i = i/10;
		buffer[count] = dec + '0';
		count++;
	} while (i != 0);

	if ( count > 9 )	count = 9;
	for ( num = 0; num < count; num++ ) {
		s[num] = buffer[count-num-1];
	}
	s[count] = 0;

	return	s;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrIToH
//
// DESCRIPTION: This routine convert an integer to hexadecimal ASCII
//
// PARAMETERS:  (Char *) s - String pointer to store results
//				(Int32) i - Integer to convert
//
// RETURNED:    Returns the string pointer s.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char *StrIToH(Char *s, Int32 i)
{
	int	count=0;
	int	dec, num;
	char	buffer[10];

	do {
		dec = i%16;
		i = i/16;
		if ( dec < 10 ) {
			buffer[count] = dec + '0';
		} else {
			buffer[count] = dec-10 + 'A';
		}
		count++;
	} while (i != 0);

	for ( num = 0; num < count; num++ ) {
		s[num] = buffer[count-num-1];
	}
	s[num] = 0;

	return	s;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrLen
//
// DESCRIPTION: This routine compute the length of a string.
//
// PARAMETERS:  (const Char *) src - string pointer
//
// RETURNED:    Returns the length of the string in bytes
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 StrLen (const Char* src)
{
	return	(UInt16)Vstrlen(src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrNCat
//
// DESCRIPTION: This routine concatenate one string to another clipping
//				the destination string to a maximum of n bytes.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//				(Int16) n - maxmum length in bytes for dst, including
//							the terminating null character.
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrNCat (Char *dst, const Char* src, Int16 n)
{
	return	Vstrncat (dst, src, n);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrNCompare
//
// DESCRIPTION: This routine compare two strings out to n characters.
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//				(UInt32) n - Length in bytes of txt to compare.
//
// RETURNED:    Returns 0 if the strings match.
//				Returns a positive number if s1 sorts after s2.
//				Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 StrNCompare (const Char *dst, const Char* src, UInt32 n)
{
	return	Vstrncmp (dst, src, n);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrNCopy
//
// DESCRIPTION: This routine copies up to n characters from a souce 
//				string to the destination string.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//				(Int16) n - Maximum number of bytes to copy from src
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrNCopy (Char *dst, const Char* src, Int16 n)
{
	return	Vstrncpy (dst, src, n);
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrStr
//
// DESCRIPTION: This routine look for a substring within a string.
//
// PARAMETERS:  (const Char *) src - String to search.
//					 (const Char *) token - String to search for.
//
// RETURNED:    Returns a pointer to the first occurrence of token in str or
//					 NULL if not found.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/26/01		Initial Revision
//////////////////////////////////////////////////////////////////////////////
Char *StrStr (const Char *str, const Char *token)
{
	return	Vstrstr (str, token);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrToLower
//
// DESCRIPTION: This routine convert all the characters in a string
//				to lowercase.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* StrToLower (Char *dst, const Char* src)
{
	return	Vstrlwr (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    StrVPrintF
//
// DESCRIPTION: This routine implements a subset of the ANSI C vsprintf
//					 call, which writes formatted output to a string.
//
// PARAMETERS:  (Char *) s - Pointer to a string where the results are
//									written. This string is always terminated by
//									a null termnator.
//					 (const Char *) formatStr - Pointer to the format 
//									specification string.
//					 (_Palm_va_list) argParam - Pointer to a list of zero or 
//									more parameters to be formatted as specified
//									by the formatStr string.
//
// RETURNED:    Returns number of characters written to destination 
//					 string, not including the numm terminator. Returns a 
//					 negative number if there is an error.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 StrVPrintF (Char* s, const Char *formatStr, VoidPtr argParam)
{
	return	0;
}
