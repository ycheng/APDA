/*========================================================
  Field.c
  all routine is running with Platform non-related,
  simulated the Field function in Palm OS.
  Current status is ControlModal free funtion.

  All is Palm related function.
  Completed 26 of 52 Control function.

  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0328, 2001 by Jerry Chu
					 0504, 2001 by Jerry Chu Modify to FormLink free
 =========================================================*/

#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif

#define	TEXTBLOCKSIZE		1024

void ParseField (FieldType *fldP);
extern void WDrawFieldString (FieldType *fldP, UInt16 selfirst, UInt16 sellast, Boolean Background);
extern void VDrawGrafState (Boolean drawMode);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldCalcFieldHeight
//
// DESCRIPTION: This routine determine the height of a field for a string.
//
// PARAMETERS:  (const Char *) chars - pointer to a null-terminated string.
//					 (UInt16) maxWidth - Maximum line width in pixels
//
// RETURNED:    Returns the total number of lines needed to draw the 
//					 string passed.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldCalcFieldHeight (const Char* chars, UInt16 maxWidth)
{
	return	1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldCopy
//
// DESCRIPTION: This routine copy the current selection to the text
//				clipboard.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldCopy (const FieldType *fldP)
{
	UInt16	selfirst, sellast;

	if ( (!fldP) || (fldP->selFirstPos==0xFFFF) || (fldP->selLastPos==0xFFFF) )	return;

	if ( fldP->selFirstPos > fldP->selLastPos ) { 
		selfirst = fldP->selLastPos;
		sellast = fldP->selFirstPos;
	} else {
		sellast = fldP->selLastPos;
		selfirst = fldP->selFirstPos;
	}
	GlobalText = (Char *) Vrealloc (GlobalText, (sellast-selfirst+1));
	Vstrncpy (GlobalText, &(fldP->text[selfirst]), (sellast-selfirst));
	GlobalText[sellast-selfirst] = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldCut
//
// DESCRIPTION: This routine copy the current selection to the text
//				clipboard.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldCut (FieldType *fldP)
{
	UInt16	selfirst, sellast;

	if ( (!fldP) && ((fldP->selFirstPos==0xFFFF)||(fldP->selLastPos==0xFFFF)) )	return;

	if ( fldP->selFirstPos > fldP->selLastPos ) { 
		selfirst = fldP->selLastPos;
		sellast = fldP->selFirstPos;
	} else {
		sellast = fldP->selLastPos;
		selfirst = fldP->selFirstPos;
	}
	GlobalText = (Char *) Vrealloc (GlobalText, (sellast-selfirst+2));
	Vstrncpy (GlobalText, &(fldP->text[selfirst]), (sellast-selfirst+1));
	GlobalText[sellast-selfirst+1] = 0;
	FldDelete (fldP, selfirst, sellast);
	fldP->selFirstPos = fldP->selLastPos = 0xFFFF;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldDelete
//
// DESCRIPTION: This routine delete the specified range of characters
//				from the field and redraw the field
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//				(UInt16) start - The beginning of the range of characters
//								to delete given as a valid byte offset
//								into the field's text string
//				(Unt16) end - The end of the range of characters to delete
//							given as a valid byte offset into the field's
//							text sting. On systems that support multi-byte
//							characters, this position must be an inter-
//							character boundary. That is, it must not point
//							to a middle byte of a multi-byte character
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldDelete (FieldType *fldP, UInt16 start, UInt16 end)
{
	UInt16	temp;

	if ( (!fldP) || (fldP->selFirstPos==0xFFFF) || (fldP->selLastPos==0xFFFF) )	
		return;

	if ( start > end ) {
		temp = start;
		start = end;
		end = temp;
	}

	if ( fldP->text && (end < fldP->textLen) ) {
		int	i, textLen = (end-start+1);

		Vmemcpy ( &(fldP->text[start]), &(fldP->text[end+1]), (fldP->textLen-end));
		fldP->textLen -= textLen; 
		if ( (fldP->textLen+1) < (fldP->textBlockSize-TEXTBLOCKSIZE) ) {
			fldP->textBlockSize = ((fldP->textLen/TEXTBLOCKSIZE)+1)*TEXTBLOCKSIZE;
			fldP->text = Vrealloc (fldP->text, fldP->textBlockSize);
		}
		fldP->text[fldP->textLen] = 0;

		for ( i = 0; i < fldP->reserved; i++ ) {
			if ( (start >= fldP->lines[i].start) && 
				(start <= fldP->lines[i].start+fldP->lines[i].length)) {
				fldP->lines[i].length -= (end-start+1);
				break;
			}
		}

		FldSetInsertionPoint (fldP, start);

		if ( fldP->attr.visible ) {
			FldDrawField (fldP);
		}
	}
	fldP->selFirstPos = fldP->selLastPos = 0xFFFF;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldDirty
//
// DESCRIPTION: This routine return true if the field has been modified.
//				since the text value was set.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns true if the field has been modified either by
//				the usero through calls to certain function.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FldDirty (FieldType *fldP)
{
	if ( !fldP )	return	false;

	return	fldP->attr.dirty;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldDrawField
//
// DESCRIPTION: This routine draw the text of the field
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldDrawField (FieldType *fldP)
{
	RectangleType	rect;
	UInt16	strLen;

	if ( !fldP || !fldP->attr.visible || !fldP->attr.usable )	return;

	if ( fldP->attr.hasFocus )
		VDrawCursor ( (Coord)(fldP->insPtXPos), (Coord)(fldP->insPtYPos+2), CUR_CLEAR);
	Vmemcpy (&rect, &(fldP->rect), sizeof(RectangleType));

	if ( fldP->rect.extent.y == -1 ) {
		rect.extent.y = FntLineHeight();
	}
	VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, COORD_STRETCH, DRAW_SET);
	if ( fldP->attr.singleLine ) { // true as multiplelines
		if ( fldP->attr.underlined ) {	// draw underline
			VDrawLine (rect.topLeft.x, (Coord)(rect.topLeft.y+rect.extent.y-1), 
						   (Coord)(rect.topLeft.x+rect.extent.x), 
							(Coord)(rect.topLeft.y+rect.extent.y-1), 
							THIN_LINE, FOREGROUNDCOLOR, PS_DOT);

		}
		// draw text of field
		if ( fldP->text ) {
			strLen = FntWordWrap (fldP->text, VPDAToSysXRes(rect.extent.x));
			VDrawString (rect.topLeft.x,	
							(Coord)(rect.topLeft.y+rect.extent.y-FntLineHeight()+2),
							fldP->text, strLen, 
							fldP->attr.singleLine, CL_FOREGROUND, COORD_STRETCH);
		}
	} else {	// if multiple lines
		UInt16	i;
		UInt16	x, width;
		UInt16	lines = (rect.extent.y+1)/FntLineHeight();

		if ( fldP->attr.underlined ) {	// draw underline
			for ( i = 1; i <= lines; i++ ) {
				VDrawLine (rect.topLeft.x, (Coord)(rect.topLeft.y+i*FntLineHeight()-1), 
								(Coord)(rect.topLeft.x+rect.extent.x), 
								(Coord)(rect.topLeft.y+i*FntLineHeight()-1), 
								THIN_LINE, FOREGROUNDCOLOR, PS_DOT);
			}
		}
		// draw text of field
		if ( fldP->text ) {
			for ( i = fldP->firstLine; (i < fldP->reserved) && 
					(i <= (lines+fldP->firstLine)) ; i++ ) {
				if ( (i-fldP->firstLine+1)*FntLineHeight() >	rect.extent.y )
					break;

				if ( fldP->attr.justification == rightAlign ) {
					width = FntCharsWidth (&fldP->text[fldP->lines[i].start], 
									fldP->lines[i].length);
					x = VPDAToSysXCoord((rect.topLeft.x+rect.extent.x)) - width - 2;
					VDrawString (x, 
									(Coord)VPDAToSysYCoord((rect.topLeft.y+(i-fldP->firstLine)*FntLineHeight()+2)),
									&fldP->text[fldP->lines[i].start], 
									fldP->lines[i].length, 
									fldP->attr.singleLine, CL_FOREGROUND, COORD_NORMAL);
				} else if ( fldP->attr.justification == leftAlign ) {
					VDrawString (rect.topLeft.x, 
									(Coord)(rect.topLeft.y+(i-fldP->firstLine)*FntLineHeight()+2), 
									fldP->text+fldP->lines[i].start, 
									fldP->lines[i].length, 
									fldP->attr.singleLine, CL_FOREGROUND, COORD_STRETCH);
				}
			}
		}
		if ( fldP->attr.hasScrollBar ) {
			for ( i = 0; i < ActiveForm->numObjects; i++ ) {
				if ( ActiveForm->objects[i].objectType ==	frmScrollBarObj ) {
					SclSetScrollBar (ActiveForm->objects[i].object.scrollBar, 
											fldP->firstLine,												// current value
											0,												// min
											(Int16)(fldP->reserved-lines),	// max
											(Int16)(fldP->rect.extent.y/FntLineHeight()) );		// page size
					break;
				}
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldEraseField
//
// DESCRIPTION: This routine erase the text of a field and turn off 
//				the insertion point if it's in the field.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/27/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldEraseField (FieldType *fldP)
{
	if ( !fldP )	return;

	FldDelete (fldP, 0, fldP->textLen);
	fldP->attr.insPtVisible = FALSE;
	if ( fldP->attr.visible ) {
		FldDrawField (fldP);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldFreeMemory
//
// DESCRIPTION: This routine release the handled-based memory allocated
//					 to the field's text and associated word-wrapping information.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/06/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldFreeMemory (FieldType *fldP)
{
	if ( !fldP || !fldP->textLen )
		return;

	Vfree (fldP->text);
	fldP->text = NULL;
	fldP->textHandle = NULL;
	fldP->textLen = 0; 
	fldP->textBlockSize = 0;
	Vfree (fldP->lines);
	fldP->lines = NULL;
	fldP->reserved = 0;
	// reset the insertion point
	FldSetInsertionPoint (fldP, 0);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetAttributes
//
// DESCRIPTION: This routine return the attributes of a field
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//				(FieldAttrPtr) attrP - Pointer to the FieldAttrType 
//									structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldGetAttributes (const FieldType *fldP, FieldAttrType *attrP)
{
	if ( !fldP )	return;

	*attrP = fldP->attr;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetBounds
//
// DESCRIPTION: This routine return the current bounds of a field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//				(RectanglePtr) rect - Pointer to a RectangleType structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldGetBounds (const FieldType *fldP, RectangleType *rect)
{
	if ( !fldP )	return;

	*rect = fldP->rect;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetFont
//
// DESCRIPTION: This routine return the ID of the font used to draw
//				the text of a field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//
// RETURNED:    Returns the ID of the font.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
FontID FldGetFont (const FieldType *fldP)
{
	if ( !fldP )	return	0;

	return	fldP->fontID;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetInsPtPosition
//
// DESCRIPTION: This routine return the insertion point position within
//				the string
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//
// RETURNED:    Returns the byte offset of the insertion point
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetInsPtPosition (const FieldType *fldP)
{
	UInt16	lines, i, charWidth, strWidth = 0;

	if ( !fldP || !fldP->text )
		return	0;
	lines = ((fldP->insPtYPos-fldP->rect.topLeft.y)/FntLineHeight())+fldP->firstLine;
	for ( i = 0; i < fldP->lines[lines].length; i++ ) {
		charWidth = FntCharWidth (fldP->text[fldP->lines[lines].start+i]);
		if ( (VPDAToSysXRes(fldP->rect.topLeft.x)+strWidth+charWidth) == fldP->insPtXPos ) {
			if ( charWidth )
				return	(fldP->lines[lines].start+i+1);
			else
				return	(fldP->lines[lines].start+i);
		}
		strWidth += charWidth;
	}

	return	fldP->lines[lines].start;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetMaxChars
//
// DESCRIPTION: This routine return the maximum number of bytes the 
//				field accepts.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//
// RETURNED:    Returns the maximum length in bytes of characters the
//				user is allowed to enter.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetMaxChars (const FieldType *fldP)
{
	if ( !fldP )	return	0;

	return	fldP->maxChars;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetNumberOfBlankLines
//
// DESCRIPTION: This routine return the number of blank lines that are
//					 displayed at the button of a field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//
// RETURNED:    Returns the number of blank lines visible.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetNumberOfBlankLines (const FieldType *fldP)
{
	Int16	count, lines=0;

	if ( !fldP )	return	0;

	if ( (fldP->lines[fldP->reserved-1].length == 1) &&
			fldP->text[fldP->lines[fldP->reserved-1].start] == 0x0a) {
		lines = 1;
		for ( count = fldP->reserved-2; count >=0 ; count-- ) {
			if ( (fldP->lines[fldP->reserved-1].length == 1) &&
					fldP->text[fldP->lines[fldP->reserved-1].start] == 0x0a) {
				lines++;
			} else {
				break;
			}
		}
	}

	return	lines;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetScrollValues
//
// DESCRIPTION: This routine return the values necessary to update a scroll
//					 bar.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//					 (UInt16 *) scrollPosP - The line of text that is the topmost
//									visible line. Line numbering starts with 0.
//					 (UInt16 *) textHeightP - The number of lines needed to display
//									the field's text, given the width of the field.
//					 (UInt16 *) fieldHeightP - The number of visible lines in the
//									field.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	11/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldGetScrollValues (const FieldType *fldP, UInt16 *scrollPosP,
								UInt16 *textHeightP, UInt16 *fieldHeightP)
{
	if ( !fldP )	return;

	*scrollPosP = (UInt16)(fldP->firstLine);
	*textHeightP = (UInt16)(fldP->reserved);
	*fieldHeightP = (UInt16)(fldP->rect.extent.y/FntLineHeight());
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetSelection
//
// DESCRIPTION: This routine return the current selection of a field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//				(UInt16 *) startPosition - Pointer to the start of the
//							selected characters range, given as the 
//							byte offset into the field's text.
//				(UInt16 *) endPosition - Pointer to end of the selected 
//							characters range, given as the byte offset
//							into the field's text.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldGetSelection (const FieldType *fldP, UInt16 *startPosition, UInt16 *endPosition)
{
	if ( !fldP )	return;

	*startPosition = fldP->selFirstPos;
	*endPosition = fldP->selLastPos;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetTextAllocatedSize
//
// DESCRIPTION: This routine return the number of bytes allocated to 
//				hold the field's text string. Don't confuse this number
//				with the actual length of the text string displayed
//				in the flied
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns the number of bytes allocated for the field's
//				text.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetTextAllocatedSize (const FieldType *fldP)
{
	if ( !fldP )	return	0;

	return	fldP->textBlockSize;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetTextHandle
//
// DESCRIPTION: This routine return a handle to the block that contains
//				the text strng of a field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns the handle to the text string of a field or 
//				NULL if no handle has been allocated for the field
//				pointer.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
MemHandle FldGetTextHandle (const FieldType *fldP)
{
	if ( !fldP )	return	NULL;

	return	fldP->textHandle;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetTextLength
//
// DESCRIPTION: This routine return the length in bytes of the field's
//				text
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns the length in bytes of a field's text, not 
//				including the terminating null character. This is
//				textLen field of FieldType
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetTextLength (const FieldType *fldP)
{
	if ( !fldP )	return	0;

	return	fldP->textLen;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetTextPtr
//
// DESCRIPTION: This routine return a locked pointer to the field's 
//				text string
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns a locked pointer to the field's text string
//				or NULL if the field is empty.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char *FldGetTextPtr (FieldType *fldP)
{
	if ( !fldP )	return	NULL;

	return	fldP->text;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGetVisibleLines
//
// DESCRIPTION: This routine return the number of lines that can be 
//					 displayed within the visible bounds of the field.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns the number of lines the field displays.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt16 FldGetVisibleLines (const FieldType *fldP)
{
	if ( !fldP )	return	0;

	return	(UInt16)fldP->rect.extent.y/FntCharHeight();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldGrabFocus
//
// DESCRIPTION: This routine turn the insertion point on (if the
//					 specified field is visible) and position the 
//					 blinking insetion point in the field
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/07/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldGrabFocus (FieldType *fldP)
{
	if ( !fldP )	return;

	fldP->attr.hasFocus = true;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldInsert
//
// DESCRIPTION: This routine replace the current selection if any with
//					 the specified string and redraw the field.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//					 (const Char *) insertChars - Text string to be inserted
//					 (UInt16) insertLen - Length in bytes of the text string
//								to be inserted, not counting the trailing
//								null character.
//
// RETURNED:    Returns true if string was successfully inserted.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01	Initial Revision
//			Jerry 5/09/01	Modify to realloc memory for text buffer
////////////////////////////////////////////////////////////////////////
Boolean FldInsert (FieldType *fldP, const Char* insertChars, UInt16 insertLen)
{
	UInt16	line, insPos, i;

	if ( !fldP || !insertChars )	return	false;

	if ( fldP->attr.singleLine ) {
		UInt16	strLen, inputStrLen;
		// if field is single line, don't accept 0x0a
		if ( insertChars[0] == 0x0a )	
			return	false;

		strLen = FntCharsWidth (fldP->text, fldP->textLen);
		inputStrLen = FntCharsWidth (insertChars, insertLen);
		// if input string length exceed boundary of field, skip it
		if ( (strLen+inputStrLen) > VPDAToSysXRes (fldP->rect.extent.x) )
			return	false;
	}

	line = (fldP->insPtYPos-fldP->rect.topLeft.y)/FntLineHeight();
	if ( insertChars[0] == ASCII_BS ) {
		if ( fldP->textLen == 0 )
			return	FALSE;
		insPos = FldGetInsPtPosition(fldP);
		if ( insPos == 0 )
			return	FALSE;

		// adjust lines structure before erase the character
		if ( fldP->text[insPos-1] == 0x0a ) {
			fldP->lines[line-1].length += (fldP->lines[line].length-1);
			for ( i = line+1; i < fldP->reserved; i++ ) {
				fldP->lines[i].start -= insertLen;
			}

			Vmemcpy (&(fldP->lines[line]), &(fldP->lines[line+1]), sizeof(fldP->lines)*(fldP->reserved-line-1));
			fldP->lines = (LineInfoPtr) Vrealloc (fldP->lines, sizeof(LineInfoType)*(fldP->reserved-1));
			fldP->reserved--;
		} else {
			if (fldP->lines[line].length > 0)
				fldP->lines[line].length--;
			else {
				fldP->reserved--;
				fldP->lines[line-1].length--;
			}
		}

		// delete the character at the current insert position
		if ( (fldP->textLen) < (fldP->textBlockSize-TEXTBLOCKSIZE) ) {
			fldP->textBlockSize = (fldP->textLen/TEXTBLOCKSIZE)*TEXTBLOCKSIZE;
			fldP->text = Vrealloc (fldP->text, fldP->textBlockSize);
		}
		Vmemmove (&(fldP->text[insPos-1]), &(fldP->text[insPos]), fldP->textLen-insPos);
		fldP->textLen--;
		fldP->text[fldP->textLen] = 0;

		FldSetInsertionPoint (fldP, (UInt16)(insPos-1));
	} else {
		insPos = FldGetInsPtPosition(fldP);
		fldP->textLen += insertLen;
		if ( (fldP->textLen+insertLen+1) > fldP->textBlockSize ) {
			fldP->textBlockSize = (((fldP->textLen+insertLen+1)/TEXTBLOCKSIZE)+1)*TEXTBLOCKSIZE;
			fldP->text = Vrealloc (fldP->text, fldP->textBlockSize);
		}

		if ( insPos <= fldP->textLen )
			Vmemmove (&(fldP->text[insPos+insertLen]), &(fldP->text[insPos]), 
				(fldP->textLen-insPos-insertLen));

		Vmemcpy (&(fldP->text[insPos]), insertChars, insertLen);
		fldP->text[fldP->textLen] = 0;
		if ( !fldP->lines ) {
			fldP->lines = (LineInfoPtr) Vmalloc (sizeof(LineInfoType)*(fldP->reserved+1));
			fldP->reserved++;
			fldP->lines[0].start = 0;
			fldP->lines[0].length = 0;
		}

		if ( insertChars[0] != 0x0a ) {
			// skip judgement of exceed line width
			fldP->lines[line].length += insertLen;
			for ( i = line+1; i < fldP->reserved; i++ ) {
				fldP->lines[i].start += insertLen;
			}
		} else {
			fldP->lines = (LineInfoPtr) Vrealloc (fldP->lines, sizeof(LineInfoType)*(fldP->reserved+1));
			if ( line < (fldP->reserved-1) )
				Vmemcpy (&(fldP->lines[line+2]), &(fldP->lines[line+1]), sizeof(fldP->lines)*(fldP->reserved-line-1));
			if ( insPos < (fldP->lines[line].start+fldP->lines[line].length) ) {
				fldP->lines[line+1].length = (fldP->lines[line].start+fldP->lines[line].length)-insPos;
				fldP->lines[line].length = insPos-fldP->lines[line].start+insertLen;
				fldP->lines[line+1].start = insPos+insertLen;
			} else {
				fldP->lines[line].length++;
				fldP->lines[line+1].start = fldP->textLen;
				fldP->lines[line+1].length = 0;
			}
			fldP->reserved++;	// used to denote lines
			for ( i = line+2; i < fldP->reserved; i++ ) {
				fldP->lines[i].start += insertLen;
			}
		}

		// if insertLen, must recalculate the line structure to
		// ensure the correct display
		if ( (insertLen > 1) ||
			(FntCharsWidth (&(fldP->text[fldP->lines[line].start]),fldP->lines[line].length) >
			VPDAToSysXRes (fldP->rect.extent.x)) )
			ParseField (fldP);
		FldSetInsertionPoint (fldP, (UInt16)(insPos+insertLen));
	}

	if ( fldP->attr.visible ) {
		FldDrawField (fldP);
	}
	return TRUE;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldMakeFullyVisible
//
// DESCRIPTION: This routine cause a dynamically resizable field to 
//					 expand its height to make its text fully visible.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns true if the filed is dynamically resizable and 
//					 was not fully visible; false otherwise.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean FldMakeFullyVisible (FieldType *fldP)
{
	if ( !fldP )	return	false;

	return	fldP->attr.dynamicSize;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldNewField
//
// DESCRIPTION: This routine create a new field object dynamically and
//					 install it in the specified form.
//
// PARAMETERS:  (void *) formPP - Pointer to the pointer to the form in
//										which the new field is installed.
//					 (UInt16) id - Symbolic ID of the field.
//					 (Coord) x - Horizontal coordinate of the upper-left corner
//										of the field's boundaries.
//					 (Coord) y - Vertical coordinate of the upper-left corner
//										of the field's boundaries.
//					 (Coord) width - Width of the field, expressed in pixels.
//					 (Coord) height - Height of the field, expressed in pixels.
//					 (FontID) font - Font used to draw the field's text.
//					 (UInt32) maxChars - Maximum number of bytes held by the
//										field this function creates.
//					 (Boolean) editable - Pass true to create a field in which
//										the user can edit text.
//					 (Boolean) underlined - Pass noUnderline for no underline,
//										or grayUnderline to have the field underline
//										the text is displays.
//					 (Boolean) singleLine - Pass true to create a field that 
//										resizes dynamically according to the amout
//										of text it displays.
//					 (Boolean) dynamicSize - Pass true to create a field that 
//										can display only a single line of text.
//					 (JustificationType) justification - Pass either of the
//										value leftAlign or rightAlign to specify
//										left justification or right justification.
//					 (Boolean) autoShift - Pass true to specify the use of
//										auto-shift rules.
//					 (Boolean) hasScrollBar - Pass true to attach a scroll bar
//										control to the field this function creates.
//					 (Boolean) numeric - Pass true to specify that only characters
//										in the range of 0 through 9 are allowed in
//										the field.
//
// RETURNED:    Returns a pointer to the new field object.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/14/01		Initial Revision
////////////////////////////////////////////////////////////////////////
FieldType *FldNewField (void **formPP, UInt16 id, Coord x, Coord y, Coord width,
						Coord heght, FontID font, UInt32 maxChars, Boolean editable,
						Boolean underlined, Boolean singleLine, Boolean dynamicSize,
						JustificationType justification, Boolean autoShift,
						Boolean hasScrollBar, Boolean numeric)
{
	FieldType	*fldP;
	FormType		*formP = (FormType *) *formPP;

	if ( !formP )	return	NULL;

	formP->objects = (FormObjListType *) Vrealloc (formP->objects, 
			sizeof(FormObjListType)*(formP->numObjects+1));

	formP->objects[formP->numObjects].objectType = frmFieldObj;
	fldP = formP->objects[formP->numObjects].object.field = 
			(FieldType *) Vmalloc (sizeof(FieldType));

	Vmemset (fldP, 0, sizeof (FieldType));

	fldP->id = id;
	fldP->fontID = font;
	fldP->text = NULL;

	fldP->attr.editable = editable;
	fldP->attr.underlined = underlined;
	fldP->attr.singleLine = singleLine;
	fldP->attr.dynamicSize = dynamicSize;
	fldP->attr.justification = justification;
	fldP->attr.autoShift = autoShift;
	fldP->attr.hasScrollBar = hasScrollBar;
	fldP->attr.numeric = numeric;

	fldP->maxChars = (UInt16)maxChars;
  
	return	formP->objects[++formP->numObjects].object.field;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldPaste
//
// DESCRIPTION: This routine replace the current selection in the field,
//				if any, with the contents of the text clipboard.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldPaste (FieldType *fldP)
{
	UInt16	strLen = (UInt16)Vstrlen (GlobalText);

	if ( !fldP || !strLen )	return;

	if ( (fldP->selFirstPos!=0xFFFF) && (fldP->selLastPos!=0xFFFF) )
		FldDelete (fldP, fldP->selFirstPos, fldP->selLastPos);
	if ( Vstrlen(GlobalText) )
		FldInsert (fldP, GlobalText, (UInt16)Vstrlen(GlobalText));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldRecalculateField
//
// DESCRIPTION: This routine update the structure that contains the 
//					 word-wrapping information for each visile line.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType
//									structure.
//					 (Boolean) redraw - If true, redraws the field. Currently,
//									this parameter must be set to true to update
//									the word-wrapping information.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldRecalculateField (FieldType *fldP, Boolean redraw)
{
	if ( !fldP )	return;

	ParseField (fldP);
	if ( redraw ) 
		FldDrawField (fldP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldReleaseFocus
//
// DESCRIPTION: This routine turn the blinking insertion point off if
//					 the field is visible and has the current focus, reset
//					 the Graffiti state, and the undo state.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType	structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	10/29/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldReleaseFocus (FieldType *fldP)
{
	if ( !fldP )	return;

	fldP->attr.hasFocus = false;
	if ( fldP->attr.editable ) {
		VDrawCursor ( (Coord)(fldP->insPtXPos), (Coord)(fldP->insPtYPos+2),
							CUR_CLEAR);
		VDrawGrafState (FALSE);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldScrollField
//
// DESCRIPTION: This routine scroll a field up or down by the number
//					 of lines specified.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType	structure.
//					 (UInt16) linesToScroll - Number of lines to scroll.
//					 (WinDirectionType) direction - The direction to scroll.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldScrollField (FieldType *fldP, UInt16 linesToScroll, WinDirectionType direction)
{
	if ( !fldP )	return;

	if (direction)
		fldP->firstLine += linesToScroll;
	else
		fldP->firstLine -= linesToScroll;

	if ( fldP->firstLine < 0 )
		fldP->firstLine = 0;
	
	if ( fldP->firstLine > fldP->reserved )
		fldP->firstLine = fldP->reserved; 
		
	FldDrawField (fldP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetAttributes
//
// DESCRIPTION: This routine set the attributes of a field.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType
//									structure.
//				(const FieldAttrPtr) attrP - Pointer to the Attributes
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetAttributes (FieldType *fldP, const FieldAttrType *attrP)
{
	if ( !fldP )	return;

	 fldP->attr = *attrP;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetBounds
//
// DESCRIPTION: This routine change the position or size of a field
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType
//									structure.
//				(const RectanglePtr) rect - Pointer to a RectangleType structure.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetBounds (FieldType *fldP, const RectangleType *rP)
{
	if ( !fldP )	return;

	fldP->rect = *rP;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetDirty
//
// DESCRIPTION: This routine set whether the field has been modified.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//				(Boolean) dirty - true if the text is modified.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetDirty (FieldType *fldP, Boolean dirty)
{
	if ( !fldP )	return;

	fldP->attr.dirty = dirty;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetFont
//
// DESCRIPTION: This routine set the font used by the field, update
//				the word-wrapping information, and draw the field
//				if visible.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//				(FontID) fontID - ID of new font.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetFont (FieldType *fldP, FontID fontID)
{
	if ( !fldP )		return;

	fldP->fontID = fontID;
	if ( fldP->attr.visible ) {
		FldDrawField (fldP);
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetInsertionPoint
//
// DESCRIPTION: This routine set the location of the insertion point
//					 based on a spedcified string position.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//					 (UInt16) pos - New location of the insertion point, 
//									given as a valid offset in bytes into the
//									filed's text.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetInsertionPoint (FieldType *fldP, UInt16 pos)
{
	UInt16	i;

	if ( !fldP )	return;

	fldP->insPtXPos = VPDAToSysXRes(fldP->rect.topLeft.x);
	fldP->insPtYPos = fldP->rect.topLeft.y;

	if ( fldP->reserved == 0 )
		return;

	for ( i = fldP->reserved-1; i >= 0; i-- ) {
		if ( (pos >= fldP->lines[i].start) && 
			(pos <= fldP->lines[i].start+fldP->lines[i].length)) {
			fldP->insPtXPos += FntCharsWidth ( &(fldP->text[fldP->lines[i].start]),
											(short)(pos-fldP->lines[i].start) );
			if ( fldP->insPtXPos > VPDAToSysXRes((fldP->rect.topLeft.x+fldP->rect.extent.x)) )
				fldP->insPtXPos = VPDAToSysXRes((fldP->rect.topLeft.x+fldP->rect.extent.x))-1;
			if ( !fldP->attr.singleLine ) {
				if ( i > fldP->rect.extent.y/FntLineHeight() )
					fldP->firstLine = fldP->reserved-(fldP->rect.extent.y/FntLineHeight());
				fldP->insPtYPos += (i-fldP->firstLine)*FntLineHeight();
			}
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetInsPtPosition
//
// DESCRIPTION: This routine set the location of the insertion point for
//					 a given string position.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//					 (UInt16) pos - New location of the insertion point, given
//										as a valid offset in bytes into the field's
//										text. On systems that support multi-byte
//										character, you must take sure that this
//										specifies an inter-character boundary.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
//////////////////////////////////////////////////////////////////////////
void FldSetInsPtPosition (FieldType *fldP, UInt16 pos)
{
	UInt16	i;

	if ( !fldP )	return;

	fldP->insPtXPos = VPDAToSysXRes(fldP->rect.topLeft.x);
	fldP->insPtYPos = fldP->rect.topLeft.y;

	for ( i = fldP->reserved-1; i >= 0; i-- ) {
		if ( (pos >= fldP->lines[i].start) && 
			(pos <= fldP->lines[i].start+fldP->lines[i].length)) {
			fldP->insPtXPos += FntCharsWidth ( &(fldP->text[fldP->lines[i].start]),
											(short)(pos-fldP->lines[i].start) );
			fldP->insPtYPos += i*FntLineHeight();
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetMaxChars
//
// DESCRIPTION: This routine set the maximum number of bytes the field
//					 accepts (the maxChars value).
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//					 (UInt16) maxChars - Maximum size in bytes of the 
//							characters the user may enter. You may
//							specify any value up to maxFieldTextLen.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
//////////////////////////////////////////////////////////////////////////
void FldSetMaxChars (FieldType *fldP, UInt16 maxChars)
{
	if ( !fldP )	return;

	fldP->maxChars = maxChars;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldsetScrollPosition
//
// DESCRIPTION: This routine scroll the field such that the character at
//					 the indicated offset is the first character on the first
//					 character on the first visible line. Redraw the field
//					 if necessary.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a FieldType	structure.
//					 (UInt16) pos - Byte offset into the field's text string
//									of first character to be made visible.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/27/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetScrollPosition (FieldType *fldP, UInt16 pos)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetSelection
//
// DESCRIPTION: This routine set the current selection in a field and 
//				heightlight the selection if the field is visible.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a FieldType
//									structure.
//				(UInt16) startPosition - Starting offset of the 
//							character range to highlight, given as
//							a byte offset into the field's text.
//				(UInt16) endPosition - Ending offset of the 
//							character range to highlight.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetSelection (FieldType *fldP, UInt16 startPosition, UInt16 endPosition)
{
	if ( !fldP )	return;

	fldP->selFirstPos = startPosition;
	fldP->selLastPos = endPosition;
	if ( (fldP->selFirstPos != fldP->selLastPos) &&
			(fldP->selFirstPos != 0xFFFF) && 
			(fldP->selLastPos != 0xFFFF) ) {
		//	if previous select texts, clear if select less than previous
		if ( fldP->selFirstPos > fldP->selLastPos ) {
			WDrawFieldString (fldP, fldP->selLastPos, fldP->selFirstPos, CL_BACKGROUND);
		} else {
			WDrawFieldString (fldP, fldP->selFirstPos, fldP->selLastPos, CL_BACKGROUND);
		}
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetText
//
// DESCRIPTION: This routine set the text value of the field without 
//					 updating the display.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//					 (MemHandle) textHandle - Unlocked handle of a block
//										containing a null-terminated text string.
//					 (UInt16) offset - Offset from start of block to start
//										of the text string.
//					 (UInt16) size - Allocated size of text string, not the
//										string length.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/24/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetText (FieldType *fldP, MemHandle textHandle, UInt16 offset,
						  UInt16 size)
{
	Char	*charPtr = (Char *)textHandle;

	if ( !fldP )	return;

	if ( !fldP->text ) {
		fldP->textBlockSize = ((size/TEXTBLOCKSIZE)+1)*TEXTBLOCKSIZE;
		fldP->text = Vmalloc (fldP->textBlockSize);
	} else {
		if ( size > fldP->textBlockSize ) {
			fldP->textBlockSize = ((size/TEXTBLOCKSIZE)+1)*TEXTBLOCKSIZE;
			fldP->text = Vrealloc (fldP->text, size);
		}
	}

//	fldP->textHandle = (void *)fldP->text;
	Vstrncpy (fldP->text, &(charPtr[offset]), size);
	fldP->textLen = size;
	ParseField (fldP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetTextAllocatedSize
//
// DESCRIPTION: This routine set the number of bytes allocated to hold
//				the field's text string. Don't confuse this with the
//				actual length of the text string displayed in the field.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//				(UInt16) allocatedSize - Number of bytes to allocated
//							for the text.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetTextAllocatedSize (FieldType *fldP, UInt16 allocatedSize)
{
	if ( !fldP )	return;

	fldP->textBlockSize = allocatedSize;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetTextHandle
//
// DESCRIPTION: This routine set the text value of a field to the string
//				associated with the specified handle. Does not update
//				display.
//
// PARAMETERS:  (const FieldType *) fldP - pointer to a field object
//				(MemHandle) textHandle - Unlocked handle of a field's
//								text string. Pass NULL fo this parameter
//								to remove the assocaton between the
//								field and the string it is currently
//								displaying so that the string is not
//								freed with the field when the form
//								is deleted.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01	Initial Revision
//			Jerry 7/23/01	Modify text when change textHandle
//			Jerry	8/24/01	Set textLen and lines(ParseField) when set 
//								textHandle
//			Jerry	10/09/01	Pointer fldP->text to *fldP->textHandle
////////////////////////////////////////////////////////////////////////
void FldSetTextHandle (FieldType *fldP, MemHandle textHandle)
{
	if ( !fldP || !textHandle )	return;

	fldP->textHandle = textHandle;
	fldP->textLen = (UInt16)Vstrlen ((Char *)*(fldP->textHandle));

	if ( fldP->textLen ) {
		fldP->text = (Char *)*textHandle;
	}

	ParseField (fldP);
	FldSetInsertionPoint (fldP, (UInt16)(fldP->textLen));
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetTextPtr
//
// DESCRIPTION: This routine set a noneditable field's text to point
//				to point to the specified text string.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//				(Char *) textP - Pointer to a null-terminated string.
//
// RETURNED:    Returns nothing. May display an error message if 
//				passed an editable text field.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/21/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetTextPtr (FieldType *fldP, Char *textP)
{
	if ( !fldP )	return;

	fldP->text = textP;
	fldP->textLen = (UInt16) Vstrlen (textP);
	fldP->textHandle = &fldP->text;
	ParseField (fldP);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldSetUsable
//
// DESCRIPTION: This routine set a field to usable or nonusable.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//					 (Boolean) usable - true to set usable;false to set nonusable
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/28/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldSetUsable (FieldType *fldP, Boolean usable)
{
	if ( !fldP )	return;

	fldP->attr.usable = usable;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FldUndo
//
// DESCRIPTION: This routine undo the last change made to the field 
//					 object, if any. Changes include typing, backspaces,
//					 delete, past, and cut.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/16/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FldUndo (FieldType *fldP)
{
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ParseField
//
// DESCRIPTION: This routine parse the text of field, and set the lines
//					 attribute.
//
// PARAMETERS:  (FieldType *) fldP - pointer to a field object
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ParseField (FieldType *fldP)
{
	Int16	index;
	Int16	charWidth, strWidth=0;

	if ( !fldP || !fldP->textLen )
		return;

	if ( fldP->lines )
		Vfree (fldP->lines);
	fldP->lines = (LineInfoPtr) Vmalloc (sizeof(LineInfoType));
	fldP->reserved = 0;
	fldP->lines[fldP->reserved++].start = 0;
	for ( index = 0; index < fldP->textLen; index++ ) {
		if ( fldP->text[index] == 0x0a ) {	// encounter return character
			fldP->lines[fldP->reserved-1].length = index-fldP->lines[fldP->reserved-1].start+1;
			fldP->reserved++;
			fldP->lines = (LineInfoPtr) Vrealloc (fldP->lines, sizeof(LineInfoType)*(fldP->reserved));
			fldP->lines[fldP->reserved-1].start = index+1;
			strWidth = 0 ;
		} else {
			charWidth = FntCharWidth (fldP->text[index]);
			if ( (strWidth+charWidth) > VPDAToSysXRes(fldP->rect.extent.x) ) {
				fldP->lines[fldP->reserved-1].length = index-fldP->lines[fldP->reserved-1].start;
				fldP->reserved++;
				fldP->lines = (LineInfoPtr) Vrealloc (fldP->lines, sizeof(LineInfoType)*(fldP->reserved));
				fldP->lines[fldP->reserved-1].start = index;
				strWidth = charWidth;
			} else {
				strWidth += charWidth;
			}
		}
	}

	fldP->lines[fldP->reserved-1].length = index-fldP->lines[fldP->reserved-1].start;
}
