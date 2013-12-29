/*========================================================
  Parser.c
  all routine is running with Platform non-related,


  (c)2001, Jerry Chu, WISCORE, All Rights Reserved

  Last updated: 0504, 2001 by Jerry Chu
 =========================================================*/

#include "VCommon.h"
#include "VParser.h"
#include "VPdaSDK.h"

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


#define	TOPLEFTX			0
#define	TOPLEFTY			1
#define	BOTTOMRIGHTX	2
#define	BOTTOMRIGHTY	3

#define	MAXIDNO			256

UInt16		formCount=0;
FormType		**formPtr;
UInt16		menuCount=0;
MenuBarType	**menuPtr;
UInt16		sysBitmapCount=0;
BitmapLink	*sysBitmapPtr;
char			sIDList[MAXIDNO][64];
short			iIDList[MAXIDNO];
short			IDCount;
Int16			prevTop = 0, prevBottom = 0, prevRight = 0, prevLeft = 0;
Int16			prevHeight = 0, prevWidth;
Int16			formX=0, formY=0;

UInt16		autoID = 65535;

char	*word;
extern char	*RCPFileName;

////////////////////////////////////////////////////////////////////////
// FUNCTION:    IsKeyWord (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine returns true if the current word is a
//					 keyword.
//
// PARAMETERS:  (char *) word - Buffer to save the retrieved string.
//
// RETURNED:    Returns true if the current word is a keyword.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/06/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean IsKeyWord (char *word, int *id)
{
	int	strLen = Vstrlen (word);
	Boolean	bKeyWord = true;

	if ( (strLen >= 3) && (strLen <= 15) ) {
		if ( (strLen == 3) && (Vstricmp(word, "END") == 0) ) {
			*id = ENDID;
		} else if ( (strLen == 4) && (Vstricmp(word, "LIST") == 0) ) {
			*id = LISTID;
		} else if ( strLen == 5 ) {
			if ( Vstricmp(word, "FIELD") == 0 ) {
				*id = FIELDID;
			} else if ( Vstricmp(word, "LABEL") == 0 ) {
				*id = LABELID;
			} else if ( Vstricmp(word, "TABLE") == 0 ) {
				*id = TABLEID;
			} else if ( Vstricmp(word, "TITLE") == 0 ) {
				*id = TITLEID;
			} else {
				bKeyWord = false;
			}
		} else if ( (strLen == 6) && (Vstrnicmp (word, "BUTTON", 6) == 0) ) {
			*id = BUTTONID;
		} else if ( (strLen == 7) && (Vstrnicmp (word, "BUTTONS", 7) == 0) ) {
			*id = BUTTONSID;
		} else if ( (strLen == 8) && (Vstricmp(word, "CHECKBOX") == 0) ) {
			*id = CHECKBOXID;
		} else if ( strLen == 9 ) {
			if ( Vstricmp(word, "POPUPLIST") == 0 ) {
				*id = POPUPLISTID;
			} else if ( Vstricmp(word, "SCROLLBAR") == 0 ) {
				*id = SCROLLBARID;
			} else {
				bKeyWord = false;
			}
		} else if ( strLen == 10 ) {
			if ( Vstricmp(word, "PUSHBUTTON") == 0 ) {
				*id = PUSHBUTTON;
			} else if ( Vstricmp(word, "FORMBITMAP") == 0 ) {
				*id = FORMBITMAPID;
			} else {
				bKeyWord = false;
			}
		} else if ( strLen == 12 ) {
			if ( Vstricmp(word, "POPUPTRIGGER") == 0 ) {
				*id = POPUPTRIGGERID;
			} else if ( Vstricmp(word, "REPEATBUTTON") == 0 ) {
				*id = REPEATBUTTONID;
			} else {
				bKeyWord = false;
			}
		} else if ( (strLen == 15) && (Vstricmp(word, "SELECTORTRIGGER") == 0) ) {
			*id = SELECTORTRIGGER;
		} else {
			bKeyWord = false;
		}
	} else {
		bKeyWord = false;
	}

	return	bKeyWord;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetWord (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine retrieve next word in RCP file.
//
// PARAMETERS:  (char *) word - Buffer to save the retrieved string.
//					 (char *) buffer - Content of RCP file.
//					 (int *) index - Current index of retieving character
//									of buffer.
//					 (int) lenght - Length of RCP file.
//					 (Boolean) beKeyword - if true, get keyword, otherwise
//									get parameter.
//
// RETURNED:    Returns true if encounter career return character.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01	Initial Revision
//			Jerry 8/06/01	Add judge keyword function
////////////////////////////////////////////////////////////////////////
Boolean GetWord (char *word, char *buffer, int *index, int length, Boolean beKeyword)
{
	Boolean	beReturn=FALSE;
	int		i=0, oldIndex = *index;
	int		id;

	if (buffer[*index] == '"') {
		(*index)++;
		while ((*index<length)&&(buffer[*index]!='"')) {
			word[i++] = buffer[*index];
			(*index)++ ;
		}
		(*index)++ ;
	} else {
		while ((*index<length)&&(buffer[*index]!=' ')&&(buffer[*index]!=0x0D)&&(buffer[*index]!=0x0A)&&(buffer[*index]!=0x09)) {
			word[i++] = buffer[*index];
			(*index)++ ;
		}
	}

	word[i] = '\0';

	if ( (word[0] == '/') && (word[1] == '/') ) {		// if remark line, skip this line
		while ((*index < length) && (buffer[*index] != 0x0D) && (buffer[*index] != 0x0A) ) {
			(*index)++;
		}
	}
	while ((*index < length) &&((buffer[*index] == ' ') || (buffer[*index] == 0x09) || (buffer[*index] == 0x0D) || (buffer[*index] == 0x0A)) ) {
		if ( beKeyword ) {
			if ( (buffer[*index] == 0x0D) || (buffer[*index] == 0x0A) ) {
				beReturn = TRUE;
			}
		}
		(*index)++;
	}

	if ( IsKeyWord (word, &id) && !beKeyword ) {
		*index = oldIndex;
		beReturn = TRUE;
	}

	return	beReturn;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstr2int (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine transfer the coordinate string to integer
//
// PARAMETERS:  (char *) word - Buffer to save the retrieved string.
//
// RETURNED:    Returns the integer
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/18/01	Initial Revision
//			Jerry 7/24/01	Add CENTER option
//			Jerry	8/09/01	Add PREVHEIGHT, PREVWIDTH option
//			Jerry	9/03/01	If size is AUTO, denote to -1
////////////////////////////////////////////////////////////////////////
int Vstr2int (int strWidth, char *word, int position)
{
	int	length = Vstrlen(word);

	if ( length > 5 ) {
		if ( Vstrnicmp (word, "PREVR", 5) == 0 ) {	// word is PREVRIGHT
			if ( word[9]=='+' ) {
				return	prevRight+Vatoi(&word[10]);
			} else if ( word[9]=='-' ) {
				return	prevRight-Vatoi(&word[10]);
			} else {
				return	prevRight;
			}
		} else if ( Vstrnicmp (word, "PREVT", 5) == 0 ) {	// word is PREVTOP
			if ( word[7]=='+' ) {
				return	prevTop+Vatoi(&word[8]);
			} else if ( word[9]=='-' ) {
				return	prevTop-Vatoi(&word[8]);
			} else {
				return	prevTop;
			}
		} else if ( Vstrnicmp (word, "PREVB", 5) == 0 ) {	// word is PREVBOTTOM
			if ( word[10]=='+' ) {
				return	prevBottom+Vatoi(&word[11]);
			} else if ( word[9]=='-' ) {
				return	prevBottom-Vatoi(&word[11]);
			} else {
				return	prevBottom;
			}
		} else if ( Vstrnicmp (word, "PREVL", 5) == 0 ) {	// word is PREVLEFT
			if ( word[9]=='+' ) {
				return	prevLeft+Vatoi(&word[10]);
			} else if ( word[9]=='-' ) {
				return	prevLeft-Vatoi(&word[10]);
			} else {
				return	prevLeft;
			}
		} else if ( Vstrnicmp (word, "PREVH", 5) == 0 ) {	// word is PREVHEIGHT
			return	prevHeight;
		} else if ( Vstrnicmp (word, "PREVW", 5) == 0 ) {	// word is PREVWIDTH
			return	prevWidth;
		} else if ( Vstrnicmp (word, "CENTE", 5) == 0 ) {	// word is CENTER
			return	-1;
		}
	} else {
		if ( length > 4 ) {
			word[4] = '\0';
		}
		if ( Vstricmp (word, "AUTO") == 0 ) {  // should give suitable control height
			return	-1;
		}
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetCoordinate (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the digital string in the buffer.
//
// PARAMETERS:  (char *) word - Buffer to save the retrieved string.
//					 (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/18/01	Initial Revision
//			Jerry 7/25/01	Add return option
////////////////////////////////////////////////////////////////////////
Boolean GetCoordinate (char *word, char *buffer, int *index, int length)
{
	Boolean	beReturn=false;
	int		i=0;

	// Get the digital of coordinate string
	while ((*index<length)&&(buffer[*index]>='0')&&(buffer[*index]<='9')) {
		word[i++] = buffer[*index];
		(*index)++ ;
	}

	// eliminate the extra space
	while ((buffer[*index]==' ') || (buffer[*index]==0x0D) || (buffer[*index]==0x0A) ) {
		if ( (buffer[*index] == 0x0D) || (buffer[*index] == 0x0A) ) {
			beReturn = TRUE;
		}
		(*index)++;
	}
	word[i] = '\0';

	return	beReturn;
}
	
////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetPointCoord (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the start coordinate and rectangle 
//				width and height.
//
// PARAMETERS:  (int) strLength - Text length of current control
//					 (PointType *) topLeft - pointer to a PointType object
//								to storage start coordinate
//					 (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/13/01	Initial Revision
//			Jerry	3/20/01	Change Control type to PointType
//			Jerry 7/18/01	Modify to call GetCoordinate	
//			Jerry 7/24/01	Modify check first coordinate
//			Jerry 7/25/01	Add return option
////////////////////////////////////////////////////////////////////////
Boolean GetPointCoord (int strWidth, PointType *topLeft, char *buffer, int *index, int length)
{
	Boolean	beReturn=false;

	while ( ((buffer[*index]<'0')||(buffer[*index]>'9'))&&((buffer[*index]!='P')&&
				(buffer[*index]!='p')&&(buffer[*index]!='C')&&(buffer[*index]!='c')) ) {
		(*index)++;
	}

	GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevLeft = topLeft->x = Vatoi (word)+formX;
	} else {
		GetWord (word ,buffer, index, length, PARAMETER);
		prevLeft = topLeft->x = Vstr2int (strWidth, word, TOPLEFTX);
		if ( topLeft->x == -1 ) {
			prevLeft = topLeft->x = VSysToPDAXRes(((SCREENWIDTH-strWidth)/2));
		}
	}
	prevRight = prevLeft+strWidth;

	beReturn = GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevTop = topLeft->y = Vatoi (word)+formY;
	} else {
		beReturn = GetWord (word ,buffer, index, length, PARAMETER);
		prevTop = topLeft->y = Vstr2int (strWidth, word, TOPLEFTY);
	}
	prevBottom = prevTop + FntLineHeight();

	return	beReturn;
}

//////////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetRectCoord (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the start coordinate and rectangle width
//					 and height.
//
// PARAMETERS:  (RectangleType *)rect - pointer to a PointType object
//								to storage start coordinate and
//								rectangle width and height
//					 (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//
// RETURNED:    Returns true if ending with line return.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01	Initial Revision
//			Jerry 7/18/01	Modify to call GetCoordinate
//			Jerry 7/24/01	Modify check first coordinate
//			Jerry 7/25/01	Add return option
//			Jerry	8/09/01	Add reserved the prevHeight, prevWidth value
//			Jerry	9/03/01	Change prevWidth, prevHeight when size is AUTO
//////////////////////////////////////////////////////////////////////////////
Boolean GetRectCoord (char *str, int strLength, RectangleType *rect, char *buffer, int *index, int length)
{
	Boolean	beReturn=false;

	while ( ((buffer[*index]<'0')||(buffer[*index]>'9'))&&((buffer[*index]!='P')&&
				(buffer[*index]!='p')&&(buffer[*index]!='C')&&(buffer[*index]!='c')) ) {
		(*index)++;
	}

	GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevLeft = rect->topLeft.x = Vatoi (word)+formX;
	} else {
		GetWord (word ,buffer, index, length, PARAMETER);
		prevLeft = rect->topLeft.x = Vstr2int (strLength, word, TOPLEFTX);
	}
	
	GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevTop = rect->topLeft.y = Vatoi (word)+formY;
	} else {
		GetWord (word ,buffer, index, length, PARAMETER);
		prevTop = rect->topLeft.y = Vstr2int (strLength, word, TOPLEFTY);
	}

	GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevWidth = rect->extent.x = Vatoi (word);
	} else {
		GetWord (word ,buffer, index, length, PARAMETER);
		rect->extent.x = Vstr2int (strLength, word, BOTTOMRIGHTX);
		if ( rect->extent.x == -1 ) {
			prevWidth = FntCharsWidth (str, (Int16)strLength);
		}
	}
	prevRight = prevLeft+prevWidth;

	beReturn = GetCoordinate (word, buffer, index, length);
	if ( Vstrlen(word) > 0 ) {
		prevHeight = rect->extent.y = Vatoi (word);
	} else {
		beReturn = GetWord (word ,buffer, index, length, PARAMETER);
		rect->extent.y = Vstr2int (strLength, word, BOTTOMRIGHTY);
		if( rect->extent.y == -1 ) {
			prevHeight = FntLineHeight();
		}
	}
	prevBottom = prevTop+prevHeight;

	if ( prevLeft == -1 ) {
		if ( rect->extent.x != -1 ) {	// if width is not AUTO
			prevLeft = rect->topLeft.x = (PDAWIDTH-rect->extent.x)/2;
			prevRight = prevLeft+rect->extent.x;
		} else {
			prevLeft = rect->topLeft.x = (PDAWIDTH-prevWidth)/2;
			prevRight = prevLeft+prevWidth;
		}
	}

	return	beReturn;
}

void GetIncludeName(char *buffer, int *index, int length)
{
	char filename[256];

	GetWord (filename, buffer, index, length, PARAMETER);
	
	IDCount = VLoadResource (filename);

	if ( !IDCount ) {
		char	directory[256];

		WGetFileDirectory (RCPFileName, directory);
		
		Vstrcat (directory, filename);
		Vstrcpy (filename, directory);
		IDCount = VLoadResource (filename);
	}
}

int ResolveID (char *ID)
{
	short	i;

	for ( i = 0; i < IDCount; i++ ) {
		if ( Vstricmp (ID, sIDList[i]) == 0 ) 
			return	iIDList[i];
	}

	return	0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetAlertButtonAttr (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the attributes of control(BUTTON, 
//					 REPEATBUTTON, SELECTTRIGGER, CHECKBOX, POPUPTRIGGER)
//					 including coordinate, text, ID, and other atrributes.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//					 (ControlStyleType) Type - Control style type.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01	Initial Revision
//			Jerry 7/25/01	Add beReturn option
////////////////////////////////////////////////////////////////////////
void GetAlertButtonAttr (char *buffer, int *index, int length, ControlStyleType Type)
{
	ControlType	*ctlP;
	Boolean	beReturn=false;
	Int16		strLen, buttonCounts=0, objIndex = formPtr[formCount]->numObjects;
	int		strWidth;

	do {
		objIndex += buttonCounts;
		formPtr[formCount]->objects = (FormObjListType *) 
			Vrealloc (formPtr[formCount]->objects, sizeof(FormObjListType)*(objIndex+1));

		formPtr[formCount]->objects[objIndex].objectType = frmControlObj;
		formPtr[formCount]->objects[objIndex].object.control = 
				(ControlType *) Vmalloc (sizeof(ControlType));

		ctlP = formPtr[formCount]->objects[objIndex].object.control;
		Vmemset (ctlP, 0, sizeof (ControlType));
		ctlP->style = Type;
		ctlP->id = buttonCounts;

		if ( !buttonCounts )
			GetWord (word ,buffer, index, length, PARAMETER);
		strLen = (Int16)(Vstrlen(word));
		ctlP->text = (char *) Vmalloc((strLen+1));
		Vstrcpy (ctlP->text, word);
		strWidth = FntCharsWidth (word, strLen);

		if ( buttonCounts > 0 ) {
			formPtr[formCount]->objects[objIndex-1].object.control->bounds.topLeft.x 
					-= (strWidth+ArrowWidth);
			ctlP->bounds.topLeft.x = 
				formPtr[formCount]->objects[objIndex-1].object.control->bounds.topLeft.x
				+ formPtr[formCount]->objects[objIndex-1].object.control->bounds.extent.x 
				+ ArrowWidth;
		} else {
			ctlP->bounds.topLeft.x = (Coord) (PDAWIDTH-strWidth)/2;
		}
		ctlP->bounds.topLeft.y = PDAHEIGHT-(Int16)(FntLineHeight()*3/2);
		ctlP->bounds.extent.x = strWidth+ArrowWidth;
		ctlP->bounds.extent.y = FntLineHeight();
	
		ctlP->attr.frame = true;
		ctlP->attr.visible = true;
		ctlP->attr.enabled = true;

		formPtr[formCount]->numObjects++;
		buttonCounts++;
		beReturn = GetWord (word ,buffer, index, length, PARAMETER);
	} while (!beReturn);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetBitmapAttr (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the attributes of Bitmap.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/21/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GetBitmapAttr (char *buffer, int *index, int length)
{
	FormBitmapType	*bmpP;
	Boolean	beReturn=false;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmBitmapObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.bitmap = 
			(FormBitmapType *) Vmalloc (sizeof(FormBitmapType));

	bmpP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.bitmap;
	Vmemset (bmpP, 0, sizeof (FormBitmapType));

	if (!GetPointCoord (0, &(bmpP->pos), buffer, index, length)) {
		// get attribute of control
		do {
			beReturn = GetWord (word ,buffer, index, length, PARAMETER);
			if ( Vstricmp(word, "BITMAP") == 0 ) {
				beReturn = GetWord (word ,buffer, index, length, PARAMETER);
				if ( TxtCharIsDigit(word[0]) ) {
					bmpP->rscID = Vatoi (word);
				} else {
					bmpP->rscID = ResolveID (word);
				}
			}
		} while (!beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetControlAttr (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the attributes of control(BUTTON, 
//					 REPEATBUTTON, SELECTTRIGGER, CHECKBOX, POPUPTRIGGER)
//					 including coordinate, text, ID, and other atrributes.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//					 (ControlStyleType) Type - Control style type.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01	Initial Revision
//			Jerry 7/25/01	Add beReturn option
////////////////////////////////////////////////////////////////////////
void GetControlAttr (char *buffer, int *index, int length, ControlStyleType Type)
{
	ControlType	*ctlP;
	Boolean	beReturn=false;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmControlObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.control = 
			(ControlType *) Vmalloc (sizeof(ControlType));

	ctlP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.control;
	Vmemset (ctlP, 0, sizeof (ControlType));
	ctlP->style = Type;

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstrlen (word) ) {
		ctlP->text = (char *) Vmalloc((Vstrlen(word)+1));
		Vstrcpy (ctlP->text, word);
	}

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		ctlP->id = Vatoi (word);
	} else {
		ctlP->id = ResolveID (word);
	}

	// set control default attribute value
	ctlP->attr.visible = 1;
	ctlP->attr.frame = 1;
	ctlP->attr.enabled = 1;

	// if end of line, will return true; others get attributes
	if (!GetRectCoord (ctlP->text, Vstrlen(ctlP->text), &(ctlP->bounds), buffer, index, length)) {
		// get attribute of control
		do {
			beReturn = GetWord (word ,buffer, index, length, PARAMETER);
			if ( Vstricmp(word, "GROUP") == 0 ) {
				beReturn = GetWord (word ,buffer, index, length, PARAMETER);
				if ( TxtCharIsDigit(word[0]) ) {
					ctlP->group = (Vatoi (word) % 256);
				} else {
					ctlP->group = (ResolveID (word) % 256);
				}
			} else if ( Vstricmp(word, "USABLE") == 0 ) {
				ctlP->attr.usable = 1;
			} else if ( Vstricmp(word, "DISABLED") == 0 ) {
				ctlP->attr.enabled = 0;
			} else if ( Vstricmp(word, "FRAME") == 0 ) {
				ctlP->attr.frame = 1;
			} else if ( Vstricmp(word, "NOFRAME") == 0 ) {
				ctlP->attr.frame = 0;
			}
		} while (!beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetLabelAttr (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the attributes of LABEL control,
//					 including coordinate, text, ID, and other atrributes.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//					 (ControlStyleType) Type - Control style type.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01	Initial Revision
//			Jerry 7/25/01	Add beReturn option
//			Jerry	8/16/01	Add assign prevRight and prevBottom value
////////////////////////////////////////////////////////////////////////
void GetLabelAttr (char *buffer, int *index, int length, ControlStyleType Type)
{
	ControlType	*ctlP;
	Boolean		beReturn=false;
	int			strWidth;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmControlObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.control = 
			(ControlType *) Vmalloc (sizeof(ControlType));

	ctlP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.control;
	Vmemset (ctlP, 0, sizeof (ControlType));
	ctlP->style = Type;

	// Get the text of LABEL
	GetWord (word ,buffer, index, length, PARAMETER);
	ctlP->text = (char *) Vmalloc((Vstrlen(word)+1));
	Vstrcpy (ctlP->text, word);
	strWidth = FntCharsWidth (word, (Int16)Vstrlen(word));

	// Get the ID of LABEL
	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( (Vstrlen(word)>5)&&(!Vstrnicmp (word,"AUTOID",6)) ) {
		ctlP->id = autoID;
		autoID--;
	} else if ( TxtCharIsDigit(word[0]) ) {
		ctlP->id = Vatoi (word);
	} else {
		ctlP->id = ResolveID (word);
	}

	ctlP->attr.enabled = 1;
	ctlP->attr.visible = 1;
	ctlP->attr.usable = 1;

	// if end of line, will return true; others get attributes
	if ( !GetPointCoord (FntCharsWidth(ctlP->text,(short)Vstrlen(ctlP->text)), &(ctlP->bounds.topLeft), buffer, index, length) ) {
		prevRight = prevLeft + VSysToPDAXRes(strWidth);
		prevBottom = prevTop + FntLineHeight();
		// get attribute of label control
		do {
			beReturn = GetWord (word, buffer, index, length, PARAMETER);
			if ( Vstricmp (word, "NONUSABLE")==0 )
				ctlP->attr.usable = false;
		} while ( !beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetFieldAttr
//
// DESCRIPTION: This routine get the attribute of FIELD
//
// PARAMETERS:  (char *)buffer - the buffer to stoage the text of RCP 
//							files 
//				(int *) index - the current buffer index.
//				(int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01	Initial Revision
//			Jerry	3/21/02	Modify to FieldType
//			Jerry 5/03/01	Modify to FormType
//			Jerry 7/25/01	Add beReturn option
//			Jerry	8/16/01	Add fldP->attr.underlined attribute
////////////////////////////////////////////////////////////////////////
void GetFieldAttr (char *buffer, int *index, int length)
{
	FieldType	*fldP;
	Boolean	beReturn;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmFieldObj;
	fldP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.field = 
			(FieldType *) Vmalloc (sizeof(FieldType));

//	fldP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.field;
	Vmemset (fldP, 0, sizeof (FieldType));

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		fldP->id = Vatoi (word);
	} else {
		fldP->id = ResolveID (word);
	}

	fldP->text = NULL;
	fldP->attr.underlined = 0;

	fldP->attr.editable = TRUE;
	fldP->attr.visible = true;
	fldP->attr.usable = true;
	// if end of line, will return true; others get attributes
	if( !GetRectCoord ("A", 1, &(fldP->rect), buffer, index, length) ){
		// get attribute of control
		do {
			beReturn = GetWord (word, buffer, index, length, PARAMETER);
			if ( Vstricmp(word, "MULTIPLELINES")==0 ) {
				// set style[0] to 1 as multiplelines, 0 as singleline
				fldP->attr.singleLine = 0;
			} else if ( Vstricmp(word, "SINGLELINE")==0 ) {
				fldP->attr.singleLine = 1;
			} else if ( Vstricmp(word, "USABLE")==0 ) {
				fldP->attr.usable = TRUE;
			} else if ( Vstricmp(word, "NONUSABLE")==0 ) {
				fldP->attr.usable = FALSE;
			} else if ( Vstricmp(word, "UNDERLINED")==0 ) {
				fldP->attr.underlined = 1;
			} else if ( Vstricmp(word, "RIGHTALIGN")==0 ) {
				fldP->attr.justification = rightAlign;
			} else if ( Vstricmp(word, "LEFTALIGN")==0 ) {
				fldP->attr.justification = leftAlign;
			} else if ( Vstricmp(word, "NONEDITABLE")==0 ) {
				fldP->attr.editable = false;
			} else if ( Vstricmp(word, "HASSCROLLBAR")==0 ) {
				fldP->attr.hasScrollBar = true;
			} else if ( Vstricmp(word, "MAXCHARS")==0 ) {
				beReturn = GetWord (word, buffer, index, length, PARAMETER);
				fldP->maxChars = (Char)Vatoi(word);
			}
		} while ( !beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetListAttr
//
// DESCRIPTION: This routine get the attribute of LIST
//
// PARAMETERS:  (char *)buffer - the buffer to stoage the text of RCP 
//							files 
//				(int *) index - the current buffer index.
//				(int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01	Initial Revision
//			Jerry	3/21/01	Modify to ListType
//			Jerry 5/03/01	Modify to FormType
//			Jerry 7/25/01	Modify to get multiple list item, add beReturn
////////////////////////////////////////////////////////////////////////
void GetListAttr (char *buffer, int *index, int length)
{
	int		size=0, oldsize=0;
	ListType	*listP;
	UInt16	visibleItems;
	Boolean	beReturn=false;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));
	Vmemset (&(formPtr[formCount]->objects[formPtr[formCount]->numObjects]), 0, sizeof(FormObjListType));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmListObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.list = 
		(ListType *) Vmalloc (sizeof(ListType));

	listP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.list;
	Vmemset (listP, 0, sizeof (ListType));

	// Get list item
	listP->numItems = 0;
	listP->itemsText = (Char **) Vmalloc ((sizeof(Char *)*(listP->numItems+1)));

	while (buffer[*index] == '"') {
		GetWord (word ,buffer, index, length, PARAMETER);
		size += Vstrlen(word)+1;
		if ( size > 1 ) {
			listP->itemsText = (Char **) Vrealloc (listP->itemsText, sizeof(Char *)*(listP->numItems+1));
			listP->itemsText[listP->numItems] = (char *) Vmalloc(size);
			Vstrcpy (listP->itemsText[listP->numItems], word);
			listP->numItems++;
		}
	};

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		listP->id = Vatoi (word);
	} else {
		listP->id = ResolveID (word);
	}

	// if end of line, will return true; others get attributes
	if ( !GetRectCoord ("A", 1, &(listP->bounds), buffer, index, length) ) {
		do {
			beReturn = GetWord (word, buffer, index, length, PARAMETER);
			// Get Button Control parameter
			if ( Vstricmp(word, "VISIBLEITEMS") == 0 ) {
				beReturn = GetWord (word, buffer, index, length, PARAMETER);
				visibleItems = Vatoi(word);
				if ( (visibleItems > listP->numItems) && (listP->numItems!=0) ) {
					listP->bounds.extent.y = listP->numItems*(FntLineHeight());
				} else {
					listP->bounds.extent.y = visibleItems*(FntLineHeight());
				}
			} else if ( Vstricmp(word, "USABLE") == 0 ) {
				listP->attr.usable = true;
			}
		} while (!beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetMessageAttr (Add by Jerry, not in Palm OS)
//
// DESCRIPTION: This routine get the attributes of LABEL control,
//					 including coordinate, text, ID, and other atrributes.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage RCP files
//					 (int *) index - the current buffer index.
//					 (int) length - buffer length
//					 (ControlStyleType) Type - Control style type.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/20/01	Initial Revision
//			Jerry 7/25/01	Add beReturn option
////////////////////////////////////////////////////////////////////////
void GetMessageAttr (char *buffer, int *index, int length)
{
	FormLabelType	*labelP;
	Boolean		beReturn=false;
	UInt16		strLen=0, textLen, lines = 0, i;
	UInt16		*lineTextLens;	// record the text length of each lines
	int			id;
	char			*text;

	text = (char *) Vmalloc (1);
	lineTextLens = (UInt16 *) Vmalloc (sizeof(UInt16));
	lineTextLens[0] = 0;
	text[0] = 0;

	// parse the text of alert message
	do {
		beReturn = GetWord (word ,buffer, index, length, PARAMETER);
		if ( (word[0] != '\\') && (!IsKeyWord (word, &id)) ) {
			textLen = (UInt16)Vstrlen(word);
			if ( (word[textLen-2] == '\\') && (word[textLen-1]=='n') ) {
				// if get LF-CR character, add one line to alert
				lineTextLens = (UInt16 *) Vrealloc (lineTextLens, (lines+2)*sizeof(UInt16));
				strLen += (textLen-1);
				lineTextLens[lines+1] = strLen;
				word[textLen-2] = 0x0d;
				word[textLen-1] = 0;
				lines++;
			} else {
				// if no LF-CR character, add the texts to the last one
				strLen += textLen;
			}
			text = (char *) Vrealloc(text, strLen+1);
			Vstrcat (text, word);
			text[strLen] = 0;
		}
	} while ( !beReturn || (word[0] == '\\') ) ;

	lineTextLens = (UInt16 *) Vrealloc (lineTextLens, (lines+2)*sizeof(UInt16));
	lineTextLens[lines+1] = strLen;
	lines++;

	// if line length exceed the width, wrap it.
	for ( i = 0; i < lines; i++ ) {
		strLen = FntWordWrap (&(text[lineTextLens[i]]), VPDAToSysXRes(PDAWIDTH)-10);
		if ( strLen < (lineTextLens[i+1]-lineTextLens[i]) ) {
			lineTextLens = (UInt16 *) Vrealloc (lineTextLens, (lines+2)*sizeof(UInt16));
			Vmemcpy (&(lineTextLens[i+2]), &(lineTextLens[i+1]), lines+1-i);
			lineTextLens[i+1] = strLen;
			lines++;
		}
	}

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+lines));

	// allcate the message memory to the alert
	for ( i = 0; i < lines; i++ ) {
		formPtr[formCount]->objects[formPtr[formCount]->numObjects+i].objectType = frmLabelObj;
		formPtr[formCount]->objects[formPtr[formCount]->numObjects+i].object.label = 
				(FormLabelType *) Vmalloc (sizeof(FormLabelType));
		labelP = formPtr[formCount]->objects[formPtr[formCount]->numObjects+i].object.label;
		Vmemset (labelP, 0, sizeof (FormLabelType));
		textLen = lineTextLens[i+1]-lineTextLens[i];
		labelP->text = (char *) Vmalloc (textLen+1);
		Vmemcpy (labelP->text, &(text[lineTextLens[i]]), textLen);
		labelP->text[textLen] = 0;
		labelP->pos.x = 5;
		labelP->pos.y = (Int16)(PDAHEIGHT-FntLineHeight()*(lines-i)-
			FntLineHeight()*3/2);
	}

	Vfree (text);
	Vfree (lineTextLens);

	// set the alert boundary
	formPtr[formCount]->window.windowBounds.topLeft.x = 0;
	formPtr[formCount]->window.windowBounds.topLeft.y = 
		formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.control->bounds.topLeft.y-FntLineHeight()*2;
	formPtr[formCount]->window.windowBounds.extent.x = PDAWIDTH-1;
	formPtr[formCount]->window.windowBounds.extent.y = 
	PDAHEIGHT-formPtr[formCount]->window.windowBounds.topLeft.y;

	formPtr[formCount]->numObjects += lines;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetScrollAttr
//
// DESCRIPTION: This routine get the attribute of LIST
//
// PARAMETERS:  (char *)buffer - the buffer to stoage the text of RCP 
//							files 
//				(int *) index - the current buffer index.
//				(int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/09/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void GetScrollAttr (char *buffer, int *index, int length)
{
	int		size=0, oldsize=0;
	ScrollBarType	*scrollBarP;
	Boolean	beReturn=false;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));
	Vmemset (&(formPtr[formCount]->objects[formPtr[formCount]->numObjects]), 0, sizeof(FormObjListType));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmScrollBarObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.scrollBar = 
			(ScrollBarType *) Vmalloc (sizeof(ScrollBarType));

	scrollBarP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.scrollBar;
	Vmemset (scrollBarP, 0, sizeof (ScrollBarType));

	// Get the ID of the control
	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		scrollBarP->id = Vatoi (word);
	} else {
		scrollBarP->id = ResolveID (word);
	}

	// if end of line, will return true; others get attributes
	if ( !GetRectCoord ("A", 1, &(scrollBarP->bounds), buffer, index, length) ) {
		do {
			beReturn = GetWord (word, buffer, index, length, PARAMETER);
			// Get Button Control parameter
			if ( Vstricmp(word, "USABLE") == 0 ) {
				scrollBarP->attr.usable = true;
			}
		} while (!beReturn);
	}

	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetTableAttr
//
// DESCRIPTION: This routine get the attribute of TABLE
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//							files 
//				(int *) index - the current buffer index.
//				(int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01		Initial Revision
//			Jerry	3/21/02		Modify to TableType
////////////////////////////////////////////////////////////////////////
void GetTableAttr (char *buffer, int *index, int length)
{
	TableType	*tblP;
	UInt16	i;
	UInt16	itemsNo;
	Boolean	beReturn=false;

	formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
			sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

	formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmTableObj;
	formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.table = 
			(TableType *) Vmalloc (sizeof(TableType));

	tblP = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.table;
	Vmemset (tblP, 0, sizeof (TableType));

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		tblP->id = Vatoi (word);
	} else {
		tblP->id = ResolveID (word);
	}


	// if end of line, will return true; others get attributes
	if ( !GetRectCoord ("A", 1, &(tblP->bounds), buffer, index, length) ) {
		// get attribute of table
		do {
			beReturn = GetWord (word ,buffer, index, length, PARAMETER);
			if ( Vstricmp(word, "ROWS") == 0 ) {
				int	rowHeight;

				beReturn = GetWord (word ,buffer, index, length, PARAMETER);
				// numItems denote rows in TABLE
				tblP->numRows = Vatoi(word);	
				tblP->rowAttrs = (TableRowAttrType *) Vmalloc ((sizeof (TableRowAttrType)*tblP->numRows));
				Vmemset (tblP->rowAttrs, 0, sizeof (TableRowAttrType) * tblP->numRows);

				// Set the height of each rows
				rowHeight = tblP->bounds.extent.y/tblP->numRows;
				for ( i = 0; i < tblP->numRows; i++ ) {
					tblP->rowAttrs[i].height = rowHeight;
				}
			} else if ( Vstricmp(word, "COLUMNS") == 0 ) {
				beReturn = GetWord (word ,buffer, index, length, PARAMETER);
				// topItem denote rows in TABLE
				tblP->numColumns = Vatoi(word);	
				tblP->columnAttrs = (TableColumnAttrType *) Vmalloc ((sizeof (TableColumnAttrType)*tblP->numColumns));
				Vmemset (tblP->columnAttrs, 0, sizeof (TableColumnAttrType) * tblP->numColumns);
			} else if ( Vstricmp(word, "COLUMNWIDTHS") == 0 ) {
				// Use Title to memo width of each column
				for ( i = 0; i < tblP->numColumns; i++ ) {
					beReturn = GetWord (word ,buffer, index, length, PARAMETER);
					tblP->columnAttrs[i].width = (Coord) Vatoi(word);
				}
			}
		} while (!beReturn);
	}
	itemsNo = tblP->numColumns*tblP->numRows;
	tblP->items = (TableItemPtr) Vmalloc ((sizeof(TableItemType)*itemsNo));
	for ( i = 0; i < itemsNo; i++ ) {
		tblP->items[i].ptr = NULL;
	}
  
	formPtr[formCount]->numObjects++;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    GetMenuItem
//
// DESCRIPTION: This routine get the pull down item of menu.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//							files 
//				(int *) index - the current buffer index.
//				(int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01		Initial Revision
//			Jerry	3/29/01		Modify to MenuPullDownType
//			Jerry	11/10/01	Change MenuLinkPtr to MenuBarType
////////////////////////////////////////////////////////////////////////
void GetMenuItem (char *buffer, int *index, int length)
{
	UInt16	size;
	SWord		numMenus = menuPtr[menuCount]->numMenus;
	Word		numItems=0;
	UInt16	maxLength=0;

	GetWord (word ,buffer, index, length, PARAMETER);
//	do {
		menuPtr[menuCount]->menus = 
			(MenuPullDownPtr)Vrealloc (menuPtr[menuCount]->menus, 
			(numMenus+1)*sizeof(MenuPullDownType));
		size = (UInt16)(Vstrlen(word)+1);
		menuPtr[menuCount]->menus[numMenus].title = (Char *) Vmalloc (size);
		Vstrcpy (menuPtr[menuCount]->menus[numMenus].title, word);
//		menuPtr[menuCount]->numMenus++;
//		GetWord (word ,buffer, index, length, PARAMETER);
//	} while (Vstricmp(word, "PULLDOWN") == 0);

	do {
		GetWord (word ,buffer, index, length, PARAMETER);
	} while (Vstricmp(word, "BEGIN") != 0);

	menuPtr[menuCount]->menus[numMenus].items = 
			(MenuItemType *)Vmalloc (sizeof(MenuItemType));

	do {
		GetWord (word, buffer, index, length, KEYWORD);
		// Get Button Control parameter
		if ( Vstricmp(word, "MENUITEM") == 0 ) {

			GetWord (word ,buffer, index, length, PARAMETER);
			size = (UInt16)(Vstrlen(word)+1);
			if ( size > maxLength ) {
				maxLength = size;
			}
			menuPtr[menuCount]->menus[numMenus].items = 
				(MenuItemType *)Vrealloc (menuPtr[menuCount]->menus[numMenus].items, 
				(numItems+1)*sizeof(MenuItemType));
			menuPtr[menuCount]->menus[numMenus].items[numItems].itemStr = 
				(Char *) Vmalloc (size);
			Vstrcpy (menuPtr[menuCount]->menus[numMenus].items[numItems].itemStr, word);
			GetWord (word ,buffer, index, length, PARAMETER);
			if ( Vstricmp(word, "ID") == 0 ) {
				GetWord (word, buffer, index, length, PARAMETER);
			}
			if ( TxtCharIsDigit(word[0]) ) {
				menuPtr[menuCount]->menus[numMenus].items[numItems].id = Vatoi (word);
			} else {
				menuPtr[menuCount]->menus[numMenus].items[numItems].id = ResolveID (word);
			}
			numItems++;
		} 
	} while ( Vstricmp(word, "END") != 0 );

	menuPtr[menuCount]->menus[numMenus].bounds.topLeft.x = 5+numMenus*35;
	menuPtr[menuCount]->menus[numMenus].bounds.topLeft.y = 15;
	menuPtr[menuCount]->menus[numMenus].bounds.extent.x = maxLength*5;
	menuPtr[menuCount]->menus[numMenus].bounds.extent.y = numItems*FntLineHeight();

	menuPtr[menuCount]->menus[numMenus].numItems = numItems;
	menuPtr[menuCount]->numMenus++;
	word[0] = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ParseMENU
//
// DESCRIPTION: This routine parse the menu content.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//									files 
//					 (int *) index - the current buffer index.
//					 (int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01	Initial Revision
//			Jerry	3/29/01	Modify to MenuPullDownType
//			Jerry	11/10/01	Change MenuLinkPtr to MenuBarType
////////////////////////////////////////////////////////////////////////
void ParseMENU(char *buffer, int *index, int length)
{
	if ( menuCount == 0 ) {
		menuPtr = (MenuBarType **) Vmalloc ((sizeof(MenuBarType *)*(menuCount+1)));
	} else {
		menuPtr = (MenuBarType **) Vrealloc (menuPtr, sizeof(MenuBarType *)*(menuCount+1));
	}

	menuPtr[menuCount] = (MenuBarType *) Vmalloc (sizeof(MenuBarType));
	Vmemset (menuPtr[menuCount], 0, sizeof(MenuBarType));

	menuPtr[menuCount]->numMenus = 0;
	menuPtr[menuCount]->menus = (MenuPullDownPtr)Vmalloc (sizeof(MenuPullDownType));
	menuPtr[menuCount]->curItem = 0;
	menuPtr[menuCount]->curMenu = 0;

	GetWord (word, buffer, index, length, PARAMETER);

	if ( Vstricmp(word, "ID") == 0 ) {
		GetWord (word, buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		menuPtr[menuCount]->id = Vatoi (word);
	} else {
		menuPtr[menuCount]->id = ResolveID (word);
	}

	do {
		GetWord (word, buffer, index, length, KEYWORD);
		// Get Button Control parameter
		if ( Vstricmp(word, "PULLDOWN") == 0 ) {
			GetMenuItem (buffer, index, length);
		}
	} while ( (Vstricmp(word, "END") != 0) && (*index < length) );

	menuCount++;
	word[0] = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ParseALERT
//
// DESCRIPTION: This routine parse the alert content.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//									files 
//					 (int *) index - the current buffer index.
//					 (int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/31/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void ParseALERT(char *buffer, int *index, int length)
{

	if ( formCount == 0 ) {
		formPtr = (FormType **) Vmalloc ((sizeof(FormType *)*(formCount+1)));
	} else {
		formPtr = (FormType **) Vrealloc (formPtr, (sizeof(FormType *)*(formCount+1)));
	}

	formPtr[formCount] = (FormType *) Vmalloc (sizeof(FormType));
	Vmemset (formPtr[formCount], 0, sizeof(FormType));

	GetWord (word, buffer, index, length, PARAMETER);

	if ( Vstricmp(word, "ID") == 0 ) {
		GetWord (word, buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		formPtr[formCount]->formId = Vatoi (word);
	} else {
		formPtr[formCount]->formId = ResolveID (word);
	}

	formPtr[formCount]->numObjects = 0;
	formPtr[formCount]->objects = Vmalloc (sizeof(FormObjListType *));
	Vmemset (formPtr[formCount]->objects, 0, sizeof(FormObjListType *));
	formPtr[formCount]->window.windowFlags.modal = true;
	formPtr[formCount]->window.frameType.bits.width = 1;
	// set reserved to 1 denote it's a Alert
	formPtr[formCount]->attr.reserved = 1;	

	do {
		GetWord (word, buffer, index, length, KEYWORD);
		// Get Button Control parameter

		if ( Vstricmp(word, "INFORMATION") == 0 ) {
		} else if ( Vstricmp(word, "BUTTONS") == 0 ) {
			GetAlertButtonAttr (buffer, index, length, buttonCtl);
		} else if ( Vstricmp(word, "MESSAGE") == 0 ) {
			GetMessageAttr (buffer, index, length);
		} else if ( Vstricmp(word, "TITLE") == 0 ) {
			GetWord (word, buffer, index, length, PARAMETER);
			formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
					sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

			formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmTitleObj;
			formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title = 
			(FormTitleType *) Vmalloc (sizeof(FormTitleType));

			formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title->text = 
					(char *) Vmalloc((Vstrlen(word)+1));
			Vstrcpy (formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title->text, word);
			formPtr[formCount]->numObjects++;
		}
	} while ( Vstricmp (word, "END") != 0 );

	formCount++;
	word[0] = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    parseBITMAP
//
// DESCRIPTION: This routine resolved the Bitmap correspondence.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//									files 
//					 (int *) index - the current buffer index.
//					 (int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/21/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void parseBITMAP (char *buffer, int *index, int length)
{
	char	directory[256];

	if ( sysBitmapCount == 0 ) {
		sysBitmapPtr = (BitmapLink *) Vmalloc (sizeof (BitmapLink));
	} else {
		sysBitmapPtr = (BitmapLink *) Vrealloc (sysBitmapPtr, (sysBitmapCount+1)*sizeof (BitmapLink));
	}

	GetWord (word ,buffer, index, length, PARAMETER);
	if ( Vstricmp (word, "ID") == 0 ) {
		GetWord (word ,buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		sysBitmapPtr[sysBitmapCount].ID = Vatoi (word);
	} else {
		sysBitmapPtr[sysBitmapCount].ID = ResolveID (word);
	}

	GetWord (word ,buffer, index, length, PARAMETER);
	VGetCurrentDirectory (directory);
	sysBitmapPtr[sysBitmapCount].fileName = (Char *) Vmalloc ((Vstrlen(directory)+Vstrlen(word)+2));
	Vstrcpy ( sysBitmapPtr[sysBitmapCount].fileName, directory);
	Vstrcat ( sysBitmapPtr[sysBitmapCount].fileName, "\\");
	Vstrcat ( sysBitmapPtr[sysBitmapCount].fileName, word);
	sysBitmapPtr[sysBitmapCount].fileName[Vstrlen(sysBitmapPtr[sysBitmapCount].fileName)] = 0;

	sysBitmapCount++;
	word[0] = 0;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ParseFORM
//
// DESCRIPTION: This routine parse the form content.
//
// PARAMETERS:  (char *) buffer - the buffer to stoage the text of RCP 
//									files 
//					 (int *) index - the current buffer index.
//					 (int) length - the length of buffer
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/11/01	Initial Revision
//			Jerry	8/08/01	Add POPUPLIST control
//			Jerry	8/09/01	Add SCROLLBAR control
//			Jerry	8/15/01	Modify default form to be framed form
////////////////////////////////////////////////////////////////////////
void ParseFORM(char *buffer, int *index, int length)
{

	if ( formCount == 0 ) {
		formPtr = (FormType **) Vmalloc ((sizeof(FormType *)*(formCount+1)));
	} else {
		formPtr = (FormType **) Vrealloc (formPtr, sizeof(FormType *)*(formCount+1));
	}

	formPtr[formCount] = (FormType *) Vmalloc (sizeof(FormType));
	Vmemset (formPtr[formCount], 0, sizeof(FormType));

	GetWord (word, buffer, index, length, PARAMETER);

	if ( Vstricmp(word, "ID") == 0 ) {
		GetWord (word, buffer, index, length, PARAMETER);
	}
	if ( TxtCharIsDigit(word[0]) ) {
		formPtr[formCount]->formId = Vatoi (word);
	} else {
		formPtr[formCount]->formId = ResolveID (word);
	}

	GetWord (word, buffer, index, length, PARAMETER);
	if ( Vstricmp(word, "AT") == 0 ) {
		GetWord (word, buffer, index, length, PARAMETER);
	}

	if ( word[0] == '(' ) {
		if ( Vstrlen (word) > 1 ) {
			formX = formPtr[formCount]->window.windowBounds.topLeft.x = Vatoi (&word[1]);
		} else {
			GetCoordinate (word, buffer, index, length);
			formX = formPtr[formCount]->window.windowBounds.topLeft.x = Vatoi (word);
		}
	} else {
		formX = formPtr[formCount]->window.windowBounds.topLeft.x = Vatoi (word);
	}
	GetCoordinate (word, buffer, index, length);
	formY = formPtr[formCount]->window.windowBounds.topLeft.y = Vatoi (word);
	GetCoordinate (word, buffer, index, length);
	formPtr[formCount]->window.windowBounds.extent.x = Vatoi (word);
	GetCoordinate (word, buffer, index, length);
	formPtr[formCount]->window.windowBounds.extent.y = Vatoi (word);
	formPtr[formCount]->numObjects = 0;
	formPtr[formCount]->objects = Vmalloc (sizeof(FormObjListType *));
	Vmemset (formPtr[formCount]->objects, 0, sizeof(FormObjListType *));

	formPtr[formCount]->window.frameType.bits.width = 0;
	// set reserved to 0 denote it's a Form
	formPtr[formCount]->attr.reserved = 0;	

	do {
		GetWord (word, buffer, index, length, KEYWORD);
		// Get Button Control parameter

		if ( Vstricmp(word, "NOFRAME") == 0 ) {
			formPtr[formCount]->window.frameType.bits.width = 0;
		} else if ( Vstricmp(word, "FRAME") == 0 ) {
			formPtr[formCount]->window.frameType.bits.width = 1;
		} else if ( Vstricmp(word, "USABLE") == 0 ) {
			formPtr[formCount]->attr.usable = true;
		} else if ( Vstricmp(word, "NONUSABLE") == 0 ) {
			formPtr[formCount]->attr.usable = false;
		} else if ( Vstricmp(word, "MODAL") == 0 ) {
			formPtr[formCount]->window.windowFlags.modal = true;
		} else if ( Vstricmp(word, "BUTTON") == 0 ) {
			GetControlAttr (buffer, index, length, buttonCtl);
		} else if ( Vstricmp(word, "PUSHBUTTON") == 0 ) {
			GetControlAttr (buffer, index, length, pushButtonCtl);
		} else if ( Vstricmp(word, "SELECTORTRIGGER") == 0 ) {
			GetControlAttr (buffer, index, length, selectorTriggerCtl);
		} else if ( Vstricmp(word, "REPEATBUTTON") == 0 ) {
			GetControlAttr (buffer, index, length, repeatingButtonCtl);
		} else if ( Vstricmp(word, "LABEL") == 0 ) {
			GetLabelAttr (buffer, index, length, labelCtl);
		} else if ( Vstricmp(word, "CHECKBOX") == 0 ) {
			GetControlAttr (buffer, index, length, checkboxCtl);
		} else if ( Vstricmp(word, "LIST") == 0 ) {
			GetListAttr (buffer, index, length);
		} else if ( Vstricmp(word, "FIELD") == 0 ) {
			GetFieldAttr (buffer, index, length);
		} else if ( Vstricmp(word, "POPUPTRIGGER") == 0 ) {
			GetControlAttr (buffer, index, length, popupTriggerCtl);
		} else if ( Vstricmp(word, "SCROLLBAR") == 0 ) {
			GetScrollAttr (buffer, index, length);
		} else if ( Vstricmp(word, "TABLE") == 0 ) {
			GetTableAttr (buffer, index, length);
		} else if ( Vstricmp(word, "FORMBITMAP") == 0 ) {
			GetBitmapAttr (buffer, index, length);
		} else if ( Vstricmp(word, "TITLE") == 0 ) {
			GetWord (word, buffer, index, length, PARAMETER);
			formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
					sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

			formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmTitleObj;
			formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title = 
			(FormTitleType *) Vmalloc (sizeof(FormTitleType));

			formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title->text = 
					(char *) Vmalloc((Vstrlen(word)+1));
			Vstrcpy (formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.title->text, word);
			formPtr[formCount]->numObjects++;
		} else if ( Vstricmp(word, "POPUPLIST") == 0 ) {
			FormPopupType	*popup;

			formPtr[formCount]->objects = (FormObjListType *) Vrealloc (formPtr[formCount]->objects, 
					sizeof(FormObjListType)*(formPtr[formCount]->numObjects+1));

			formPtr[formCount]->objects[formPtr[formCount]->numObjects].objectType = frmPopupObj;
			formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.popup = 
					(FormPopupType *) Vmalloc (sizeof(FormPopupType));

			popup = formPtr[formCount]->objects[formPtr[formCount]->numObjects].object.popup;

			GetWord (word ,buffer, index, length, PARAMETER);
			if ( Vstricmp (word, "ID") == 0 ) {
				GetWord (word ,buffer, index, length, PARAMETER);
			}
			if ( TxtCharIsDigit(word[0]) ) {
				popup->controlID = Vatoi (word);
			} else {
				popup->controlID = ResolveID (word);
			}

			GetWord (word ,buffer, index, length, PARAMETER);
			if ( TxtCharIsDigit(word[0]) ) {
				popup->listID = Vatoi (word);
			} else {
				popup->listID = ResolveID (word);
			}
			formPtr[formCount]->numObjects++;
		} else if ( Vstricmp(word, "MENUID") == 0 ) {
			GetWord (word, buffer, index, length, PARAMETER);
			formPtr[formCount]->menuRscId = ResolveID (word);
		}
	} while ( Vstricmp (word, "END") != 0 );

	formCount++;
	word[0] = 0;
}

int ParseInclude(char *buffer, int length)
{
	int		index=0;
	int		count=0;

	while (index < length) {
		GetWord (word, buffer, &index, length, PARAMETER);

		if ( Vstricmp (word, "#define") == 0) {
			GetWord (word, buffer, &index, length, PARAMETER);
			Vstrcpy (sIDList[count], word);
			GetWord (word, buffer, &index, length, PARAMETER);
			iIDList[count++] = Vatoi (word);
		}
	};

	return	count;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ParseRCP
//
// DESCRIPTION: This routine parse the RCP file and orginization form
//					 and control link.
//
// PARAMETERS:  (char *) buffer - The text buffer of RCP file.
//					 (int) length - Buffer length.
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/01/01	Initial Revision
//			Jerry	8/01/01	Add ParseALERT()
////////////////////////////////////////////////////////////////////////
Boolean ParseRCP(char *buffer, int length)
{
	int		index=0, oldIndex=0;

	word = (char *) Vmalloc(1024);
	if ( !word )	return	false;

	while ((index < length) && (index >=oldIndex)) {
		GetWord (word, buffer, &index, length, PARAMETER);

		if ( Vstricmp (word, "#include") == 0) {
			GetIncludeName (buffer, &index, length);
		} else if ( Vstricmp (word, "FORM") == 0) {
			ParseFORM (buffer, &index, length);
		} else if ( Vstricmp (word, "MENU") == 0) {
			ParseMENU (buffer, &index, length);
		} else if ( Vstricmp (word, "ALERT") == 0) {
			ParseALERT (buffer, &index, length);
		} else if ( Vstricmp (word, "BITMAP") == 0) {
			parseBITMAP (buffer, &index, length);
		}
		if ( oldIndex != index )
			oldIndex = index;
		else
			index++;
	};
	Vfree (word);

	return	true;
}
