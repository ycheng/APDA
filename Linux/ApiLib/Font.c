/*========================================================
  Font.c
  all routine is running with Platform non-related,
  simulated the Font function in Palm OS.

  All is Palm related function.
  Completed 2 of 52 Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0507, 2001 by Jerry Chu
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#include <UI/helvr10.h>

FontID	curFontID=0;

/* Exported structure definition. */
MWCFONT font_helvR10 = {
  "helvR10",
  11,
  12,
  10,
  32,
  95,
  helvR10_bits,
  helvR10_offset,
  helvR10_width,
};

MWCFONT	*currentFont = &font_helvR10;
Int16 FntCharWidth (Char ch);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntAverageCharWidth
//
// DESCRIPTION: This routine return the average character width in the
//					 current font.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the average character width (in pixels).
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntAverageCharWidth (void)
{
	UInt16	count;
	UInt32	totalWidth=0;

	for ( count = 0; count < currentFont->size; count++ ) {
		totalWidth += (UInt32)currentFont->width[count];
	}
	
	return	(UInt16) (totalWidth/currentFont->size);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntCharHeight
//
// DESCRIPTION: This routine return the charracter height, int the
//					 current font including accents and descenders.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the Height of the characters in the current font,
//					 expressed in pixels.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/20/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntCharHeight (void)
{
	return	currentFont->ascent;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntCharsInWidth
//
// DESCRIPTION: This routine find the length in bytes of the characters
//					 from a specified string that fit whinin a passed with.
//
// PARAMETERS:  (const Char *) string - Pointer to the character string.
//					 (Int16 *) stringWidthP - Maximum width to allow. (pixels)
//					 (Int16 *) stringLengthP - Maximum lenth of text to allow,
//												in bytes.
//					 (Boolean *) fitWithinWidth - Set to true if string is
//												considered truncated.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01	Initial Revision
//			Jerry	9/13/01	Modify to calculate the actual width of string
////////////////////////////////////////////////////////////////////////
void FntCharsInWidth (Char const *string, Int16 *stringWidthP,
							Int16 *stringLengthP, Boolean *fitWithinWidth)
{
	if ( FntCharsWidth (string, *stringLengthP) < *stringWidthP )
		*fitWithinWidth = true;
	else
		*fitWithinWidth = false;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntCharsWidth
//
// DESCRIPTION: This routine return the width of the specified character
//					 string. The Missing Character Symbol is substituted for
//					 any character which does not exist in the current font.
//
// PARAMETERS:  (const Char *) chars - pointer to a string of characters
//					 (Int16) len - Length in bytes of the string.
//
// RETURNED:    Returns the width of the string, in pixels.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntCharsWidth (const Char *chars, Int16 len)
{
	Int16	count, strLen;
	Int16	totalwidth = 0;

	strLen = (Int16)Vstrlen (chars);
	if ( len > strLen )
		len = strLen;
	for ( count = 0; count < len; count++ ) {
		totalwidth += FntCharWidth (chars[count]);
	}

	return	totalwidth;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntCharWidth
//
// DESCRIPTION: This routine return the width of the specified character.
//					 If the specified character does not exist within the current
//					 font, the Missing Character Symbol is substituted.
//
// PARAMETERS:  (Char) ch - Character whose width is needed.
//
// RETURNED:    Returns the width of the specified character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntCharWidth (Char ch)
{
	if ( (ch >= currentFont->firstchar) &&
			(ch < currentFont->size+currentFont->firstchar) ) 
		return	(currentFont->width[(ch-currentFont->firstchar)]+1);
	else
		return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntGetFont
//
// DESCRIPTION: This routine return the Font ID of the current font
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the Font ID of the current font.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FontID FntGetFont (void)
{
	return	curFontID;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntLineHeight
//
// DESCRIPTION: This routine return the height of a line in the current
//					 font. The height of a line is the height of the character
//					 cell plus the space between lines(the external leading).
//
// PARAMETERS:  None.
//
// RETURNED:    Returns the height of a line in the current font.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/03/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntLineHeight (void)
{
	return	(currentFont->ascent+1);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntLineWidth
//
// DESCRIPTION: This routine return the width of the specified line of
//					 text, taking tab characters in to account. The function 
//					 assumes that the characters passed are left-aligned and
//					 that the first character in the string is the first 
//					 character drawn on a line. In other words, this routine
//					 doesn't work for character that don't start at the
//					 begging of a line.
//
// PARAMETERS:  (Char const *) pChar - Pointer to a string of characters.
//					 (UInt16) length - Length in bytes of the string.
//
// RETURNED:    Returns the line width.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/03/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 FntLineWidth (Char const *pChar, UInt16 length)
{
	return	FntCharsWidth (pChar, length);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntSetFont
//
// DESCRIPTION: This routine set the current font.
//
// PARAMETERS:  (FontID) font - ID of the font to make the active font.
//
// RETURNED:    Returns the ID of the current font before the change.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
FontID FntSetFont (FontID font)
{
	FontID	oldFontID = curFontID;

	curFontID = font;

	return	oldFontID;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FntWordWrap
//
// DESCRIPTION: This routine given a string, determine how many bytes
//					 of text can be displayed within the specified width.
//
// PARAMETERS:  (const Char *) chars - Pointer to a null-terminated
//													string.
//					 (UInt16) maxWidth - Maximum line width in pixels.
//
// RETURNED:    Returns the lenght of the line, in bytes.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FntWordWrap (const Char *chars, UInt16 maxWidth)
{
	UInt16	index, strLen = (UInt16)Vstrlen (chars), totalLen=0, width;

	for ( index = 0; index < strLen; index++ ) {
		width = FntCharWidth (chars[index]);
		if ( (totalLen+width) < maxWidth )
			totalLen += width;
		else
			break;
	}

	return	index;
}

