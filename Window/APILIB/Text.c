/*========================================================
  Text.c
  all routine is running with Platform non-related,
  simulated the Text manager function in Palm OS.


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0510, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>

Boolean TxtCharIsPunct (Char ch);
Boolean TxtCharIsSpace (Char ch);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsAlNum
//
// DESCRIPTION: This routine indicates if the character is alphanumeric.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a letter in an alphabet
//					 or a numeric digital.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsAlNum (Char ch)
{
	if ( (ch >= Digit_0) && (ch <= Digit_9) )
		return	true;
	else if ( (ch >= Char_A) && (ch <= Char_Z) )
		return	true;
	else if ( (ch >= Char_a) && (ch <= Char_z) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsAlpha
//
// DESCRIPTION: This routine indicates if the character is a letter in
//					 an alphabet.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a letter in an alphabet.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsAlpha (Char ch)
{
	if ( (ch >= Char_A) && (ch <= Char_Z) )
		return	true;
	else if ( (ch >= Char_a) && (ch <= Char_z) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsCntrl
//
// DESCRIPTION: This routine indicates if the character is a control
//					 character.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a non-printable character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsCntrl (Char ch)
{
	if ( ch < Char_Space ) {
		return	true;
	} else {
		return	false;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsDelim
//
// DESCRIPTION: This routine indicates if the character is a delimiter.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a word delimiter 
//					 (whitesspace or punctuation).
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsDelim (Char ch)
{
	if ( TxtCharIsSpace (ch) || TxtCharIsPunct (ch) ) {
		return	true;
	} else {
		return	false;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsDigit
//
// DESCRIPTION: This routine indicates if the character is a decimal digit.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is 0 throuh 9
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsDigit (Char ch)
{
	if ( (ch >= Digit_0) && (ch <= Digit_9) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsGraph
//
// DESCRIPTION: This routine indicates if the character is a graphic
//					 character.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a graphic character.
//					 such as words, letters, digits, and punctuation marks.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsGraph (Char ch)
{
	if ( TxtCharIsAlNum (ch) || TxtCharIsPunct (ch) ) {
		return	true;
	} else {
		return	false;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsHex
//
// DESCRIPTION: This routine indicates if the character is a hexadecimal
//					 digit.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a hexadecimal digit from
//					 0 to F.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsHex (Char ch)
{
	if ( (ch >= Digit_0) && (ch <= Digit_9) )
		return	true;
	else if ( (ch >= Char_A) && (ch <= Char_F) )
		return	true;
	else if ( (ch >= Char_a) && (ch <= Char_f) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsLower
//
// DESCRIPTION: This routine indicates if the character is a lowercase
//					 letter.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a lowercase letter.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsLower (Char ch)
{
	if ( (ch >= Char_a) && (ch <= Char_z) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsPrint
//
// DESCRIPTION: This routine indicates if the character is printable.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is not a control or 
//					 virtual character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsPrint (Char ch)
{
	if ( TxtCharIsGraph (ch) || TxtCharIsSpace (ch) ) {
		return	true;
	} else {
		return	false;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsPunct
//
// DESCRIPTION: This routine indicates if the character is a punctuation
//					 mark.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a punctuation mark.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsPunct (Char ch)
{
	return	true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsSpace
//
// DESCRIPTION: This routine indicates if the character is a whitespace
//					 character.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a whitespace character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsSpace (Char ch)
{
	if ( ch == Char_Space )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharIsUpper
//
// DESCRIPTION: This routine indicates if the character is a uppercase
//					 letter.
//
// PARAMETERS:  (Char) ch - A valid character
//
// RETURNED:    Returns true if the character is a uppercase letter.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean TxtCharIsUpper (Char ch)
{
	if ( (ch >= Char_A) && (ch <= Char_Z) )
		return	true;
	else
		return	false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    TxtCharSize
//
// DESCRIPTION: This routine return the number of bytes required to
//					 store the character in a string.
//
// PARAMETERS:  (WChar) inChar - A valid character
//
// RETURNED:    Returns the number of bytes required to store the
//					 character in a string.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/11/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 TxtCharSize (WChar inChar)
{
	return	(UInt16) Vstrlen ((const char *)&inChar);
}
