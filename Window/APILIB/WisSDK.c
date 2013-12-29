#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#include <VCommon.h>
#include <VPdaSDK.h>

#define	ResourceFileName	"WisResource.h"

char *Vstrcat (char *dst, const char *src);
Char* Vstrchr (const Char *str, WChar chr);
char *Vstrcpy (char *dst, const char *src);
int	Vstrcmp (const char *str1, const char *str2);
char *Vstrncpy (char *dst, const char *src, int size);
char *Vstrrchr( const char *string, unsigned char c );
void *Vmalloc(UInt32 size);
void Vfree(void *str);

extern void drawline (Coord x0, Coord y0, Coord x1, Coord y1);

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vrand
//
// DESCRIPTION: This routine generates a random number.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns a random number.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/03/01		Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 Vrand ()
{
	return	rand();
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vsrand
//
// DESCRIPTION: This routine sets a random starting point
//
// PARAMETERS:  (UInt32) seed - Seed for random-number generation
//
// RETURNED:    Returns nothing.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	8/03/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void Vsrand (UInt32 seed)
{
	srand(seed);
}

int Vabs (int n)
{
	return	abs (n);
}

Char *Vgetenv (const Char *varname)
{
	return	getenv (varname);
}

//**********************************
// Below APIs are file relative API
//**********************************

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfclose
//
// DESCRIPTION: This routine closes a stream 
//
// PARAMETERS:  (void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns returns 0 if the stream is successfully closed,
//				otherwise error code.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfclose (void *stream)
{
	return	fclose ((FILE *)stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfeof
//
// DESCRIPTION: This routine tests for end-of-file on a stream.
//
// PARAMETERS:  (void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns returns 0 if the current position is not end 
//				of file.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfeof (void *stream)
{
	return	feof ((FILE *)stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfflush
//
// DESCRIPTION: This routine flush cached data to storage.
//
// PARAMETERS:  (void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns 0 if no error.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/10/01	Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfflush (void *stream)
{
	return	fflush ((FILE *)stream);
}

char *Vfgets( char *string, int n, void *stream )
{
	return	fgets (string, n, (FILE *)stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfopen
//
// DESCRIPTION: This routine open a file
//
// PARAMETERS:  (const char *) filename - Filename
//				(const char *) mode - Type of access permitted.
//
// RETURNED:    Returns a pointer to the open file.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
void *Vfopen (const char *filename, const char *mode)
{
	return	fopen (filename, mode);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfread
//
// DESCRIPTION: This routine reads data from a stream.
//
// PARAMETERS:  (void *) buffer - Storage location for data
//				(int) size - Item size in bytes.
//				(int) count - Maximum number of items to be read.
//				(void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns the number of full items actually read
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfread (void *buffer, int size, int count, void *stream)
{
	return	fread (buffer, size, count, stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfscanf
//
// DESCRIPTION: This routine reads data from a stream.
//
// PARAMETERS:  (void *) buffer - Storage location for data
//				(int) size - Item size in bytes.
//				(int) count - Maximum number of items to be read.
//				(void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns the number of full items actually read
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
//int Vfscanf( void *stream, const char *format ,... )
int Vfscanf3( void *stream, const char *format ,void *par1, void *par2, void *par3 )
{
	return fscanf ((FILE *)stream, format, par1, par2, par3);
}

int Vfscanf2( void *stream, const char *format ,void *par1, void *par2 )
{
	return fscanf ((FILE *)stream, format, par1, par2);
}

int Vfscanf( void *stream, const char *format ,void *par1 )
{
	return fscanf ((FILE *)stream, format, par1);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfscanf
//
// DESCRIPTION: This routine reads data from a stream.
//
// PARAMETERS:  (void *) buffer - Storage location for data
//				(int) size - Item size in bytes.
//				(int) count - Maximum number of items to be read.
//				(void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns the number of full items actually read
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vsscanf( const char *buffer, const char *format, void *par )
{
	return sscanf (buffer, format, par);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfseek
//
// DESCRIPTION: This routine moves the file pointer to a specified location
//
// PARAMETERS:  (void *) stream - Pointer to FILE structure.
//				(long) offset - Number of bytes from origin.
//				(int) origin - Initial position.
//
// RETURNED:    Returns 0 if successful, otherwise error code.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfseek (void *stream, long offset, int origin)
{
	return	fseek (stream, offset, origin);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vftell
//
// DESCRIPTION: This routine gets the current position of a file pointer.
//
// PARAMETERS:  (void *) stream - Pointer to FILE structure.
//
// RETURNED:    Returns the current file position.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
long Vftell (void *stream)
{
	return	ftell (stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vfwrite
//
// DESCRIPTION: This routine writes data to a stream.
//
// PARAMETERS:  (void *) buffer - Pointer to data to be written
//				(int) size - Item size in bytes.
//				(int) count - Maximum number of items to be read.
//				(void *) stream - Pointer to FILE structure
//
// RETURNED:    Returns the number of full items actually written
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int Vfwrite (const void *buffer, int size, int count, void *stream)
{
	return	fwrite (buffer, size, count, stream);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WGetApplicationName
//
// DESCRIPTION: This routine extract application name from filename.
//
// PARAMETERS:  (const Char *) szFileName - Pointer to file name string.
//					 (Char *) appName - Pointer to application name buffer.
//
// RETURNED:    Returns the directory string.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/18/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char *WGetApplicationName (const Char *szFileName, Char *appName)
{
	Char	tempStr1[256];
	Char	tempStr2[256];
	Char	*tempStr3;
	int	strLength;
	int	appLength, extLength;

	// extract application file name without path
	Vstrcpy ( tempStr1, szFileName);
	tempStr3 = tempStr1;
	do {
		Vstrcpy (tempStr2, tempStr3);
		tempStr3 = Vstrchr (tempStr3, '\\');
		if ( tempStr3 != NULL )
			tempStr3++;
	} while (tempStr3 != NULL);

	appLength = Vstrlen (tempStr2);

	// get extension file name length
	Vstrcpy (tempStr1, tempStr2);
	Vstrcpy (tempStr1, Vstrrchr (tempStr1, '.'));
	extLength = Vstrlen(tempStr1);

	strLength = appLength - extLength;

	Vstrncpy (appName, tempStr2, strLength);
	appName[strLength] = '\0';

	return	appName;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WGetFileDirectory
//
// DESCRIPTION: This routine extract directory information from filename.
//
// PARAMETERS:  (const Char *) szFileName - Pointer to file name string.
//					 (Char *) Directory - Pointer to directory name buffer.
//
// RETURNED:    Returns the directory string.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Char *WGetFileDirectory (const Char *szFileName, Char *Directory)
{
	Char	*tempStr;
	int	strLength;

	tempStr = Vstrrchr (szFileName, '\\');
	strLength = (Vstrlen(szFileName)-Vstrlen(tempStr)+1);
	Vstrncpy (Directory, szFileName, strLength);
	Directory[strLength] = '\0';

	return	Directory;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WGetFileSize
//
// DESCRIPTION: This routine return the file size.
//
// PARAMETERS:  (Char *) filename - Pointer to resource file name.
//
// RETURNED:    Returns file size.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int32 WGetFileSize (const char *filename)
{
	FILE	*fp;

	if ( (fp = Vfopen (filename, "rt")) != NULL ) {
		fseek (fp, 0, SEEK_END);

		return	Vftell (fp);
	}

	return	-1;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    WGetResourceFileName
//
// DESCRIPTION: This routine extract directory information from filename.
//
// PARAMETERS:  (const Char *) directory - Directory name that contain 
//												the application.
//					 (Char *) filename - Pointer to resource file name buffer.
//
// RETURNED:    Returns true if resource file exists, false if not.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/15/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Boolean WGetResourceFileName (Char *directory, char *filename)
{
	FILE	*fp;
	Char	rscFileName[256];

	Vstrcpy (rscFileName, directory);
	Vstrcat (rscFileName, ResourceFileName);
	if ( (fp = Vfopen (rscFileName, "rt")) != NULL ) {
		int		index = 0;
		char		word[256];
		int		count = 0;
		int		fileLen;
		char		*buffer;
		Boolean	beReturn, beRemark=false;

		Vfseek (fp, 0, SEEK_END);
		fileLen = Vftell (fp);
		buffer = Vmalloc (fileLen);

		Vfseek (fp, 0, SEEK_SET);
		Vfread (buffer, 1, fileLen, fp);

		while (index < fileLen) {
			beReturn = GetWord (word, buffer, &index, fileLen, KEYWORD);

			if ( Vstrcmp (word, "//") == 0) {
				beRemark = true;
			}
			if ( (Vstrcmp (word, "#define") == 0) && !beRemark ) {
				GetWord (word, buffer, &index, fileLen, PARAMETER);
				if ( Vstrcmp (word, "ResourceFileName_0") == 0 ) {
					GetWord (word, buffer, &index, fileLen, PARAMETER);
					Vstrcpy (filename, directory);
					Vstrcat (filename, word);
					break;
				}
			}
			if ( beReturn ) {
				beRemark = false;
			}
		};

		Vfree (buffer);
		return	true;
	}

	return	false;
}

void VCopyFile (void *dstfp, void *rscfp)
{
	char	buffer[1024];
	int	size;

	fflush (rscfp);
	fseek (rscfp, 0, SEEK_SET);
	// 0x164 is the length of database without data
	size = fread (buffer, 1, 0x164, rscfp);
	fwrite (buffer, 1, size, dstfp);
/*
	while (!feof ((FILE *)rscfp)) {
		size = fread (buffer, 1, 1024, rscfp);
		fwrite (buffer, 1, size, dstfp);
	}
	fflush (dstfp);
*/
}

// Below APIs are math relative API
////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vatoi
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
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int	Vatoi(char *str)
{
	return	atoi (str);
}

UInt32	mcounts=0;
// Below APIs are memory relative API
void *Vmalloc(UInt32 size)
{
	mcounts++;
	return	malloc (size);
}

// Below APIs are memory relative API
void *Vrealloc(void *memblock, UInt32 size)
{
	return	realloc (memblock, size);
}

void Vfree(void *str)
{
	mcounts--;
	free (str);
}

int Vmemcmp (void *dst, const void *src, UInt32 length)
{
	return	memcmp (dst, src, length);
}

void *Vmemcpy (void *dst, const void *src, UInt32 length)
{
	return	memcpy (dst, src, length);
}

void *Vmemmove (void *dst, const void *src, UInt32 length)
{
	return	memmove (dst, src, length);
}

void *Vmemset (void *str, int word, UInt32 length)
{
	return	memset (str, word, length);
}

// Below APIs are string relative API
////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrcat
//
// DESCRIPTION: This routine concatenate one string to another
//
// PARAMETERS:  (Char *) dst - destination string pointer
//				(const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
char *Vstrcat (char *dst, const char *src)
{
	return	strcat (dst, src);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrchr
//
// DESCRIPTION: This routine look for a character within a string.
//
// PARAMETERS:  (const Char *) str - string to search
//				(WChar) chr - character to search for
//
// RETURNED:    Returns a pointer to the first occurrenc of character
//				in str. Return NULL if the character is not found
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* Vstrchr (const Char *str, WChar chr)
{
	return	strchr (str, (int)chr);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrcmp
//
// DESCRIPTION: This routine compare two strings.
//
// PARAMETERS:  (const Char *) str1 - destination string pointer
//				(const Char *) str2 - source string pointer
//
// RETURNED:    Returns 0 if the strings match.
//				Returns a positive number if s1 sorts after s2.
//				Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
int	Vstrcmp (const char *str1, const char *str2)
{
	return	strcmp (str1, str2);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrcpy
//
// DESCRIPTION: This routine copy one string to another.
//
// PARAMETERS:  (Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//
// RETURNED:    Returns a pointer to the destination string.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	2/08/01	Initial Revision
//			Jerry	8/23/01	Modify if src is NULL, set dst to NULL string.
////////////////////////////////////////////////////////////////////////
char *Vstrcpy (char *dst, const char *src)
{
	if ( src != NULL ) {
		return	strcpy (dst, src);
	} else {
		dst[0] = 0;
		return	dst;
	}
}

char *Vstrdup( const char *strSource )
{
	return	strdup(strSource);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrncat
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
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01		Initial Revision
////////////////////////////////////////////////////////////////////////
Char* Vstrncat (Char *dst, const Char* src, Int16 n)
{
	return	Vstrncat (dst, src, n);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrncmp
//
// DESCRIPTION: This routine compare two strings out to n characters.
//
// PARAMETERS:  (const Char *) dst - destination string pointer
//					 (const Char *) src - source string pointer
//					 (UInt32) n - Length in bytes of txt to compare.
//
// RETURNED:    Returns 0 if the strings match.
//					 Returns a positive number if s1 sorts after s2.
//					 Returns a negative number if s1 sorts before s2.
//
// REVISION HISTORY: 
//			Name	Date		Description
//			----	----		-----------
//			Jerry	3/30/01	Initial Revision
////////////////////////////////////////////////////////////////////////
Int16 Vstrncmp (const Char *dst, const Char* src, UInt32 n)
{
	return	strncmp (dst, src, n);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrncpy
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
//			Jerry	2/08/01		Initial Revision
////////////////////////////////////////////////////////////////////////
char *Vstrncpy (char *dst, const char *src, int size)
{
	return	strncpy ( dst, src, size);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrlen
//
// DESCRIPTION: This routine return the length of string.
//
// PARAMETERS:  (const Char *) str - String pointer.
//
// RETURNED:    Returns the length of string.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
UInt32 Vstrlen (const char *str)
{
	if ( str ) {
		return	strlen (str);
	} else {
		return	0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    Vstrrchr
//
// DESCRIPTION: This routine scan a string for the last occurrence
//					 of a character.
//
// PARAMETERS:  (const Char *) str - String to search.
//					 (int) c - Character to be located.
//
// RETURNED:    Returns a pointer to the last occurence of c in 
//					 string, or NULL if c is not found.
//
// REVISION HISTORY: The number of records in a database
//			Name	Date		Description
//			----	----		-----------
//			Jerry	5/22/01	Initial Revision
////////////////////////////////////////////////////////////////////////
char *Vstrrchr( const char *string, unsigned char c )
{
	return	strrchr (string, c);
}

char *Vstrstr (const char *str, const char *token)
{
	return	strstr (str, token);
}

UInt32	Vsizeof (const void *str)
{
	if ( str ) {
		return	sizeof (str);
	} else {
		return	0;
	}
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FormDisplayAlert
//
// DESCRIPTION: This routine display a alert on the screen.
//
// PARAMETERS:  (const Char *) msg - Pointer to a NULL-terminated	string.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/19/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FormDisplayAlert (const Char *msg)
{
/*
	RectangleType	rect, pdaRect;
	int		strLength = Vstrlen(msg);
	int		lines = strLength/CharsPerLine;

	rect.topLeft.x = 0;
	rect.topLeft.y = PDAHEIGHT-(FORMMINHEIGHT+lines*FntLineHeight());
	rect.extent.x = PDAWIDTH;
	rect.extent.y = FORMMINHEIGHT+lines*FntLineHeight();

	FrmNewForm (999, "Warning", 0, (short)(PDAHEIGHT-(FORMMINHEIGHT+lines*FntLineHeight())),
					PDAWIDTH, (short)(FORMMINHEIGHT+lines*FntLineHeight()), true, 0, 0, 0);

	VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, RECT_STRECTH, DRAW_SET);
*/
/*
	RectangleType	rect;
	UInt16	i;

	Vmemcpy ( &rect, &(form->window.windowBounds), sizeof(RectangleType) );

	if ( form->window.frameType.bits.width )
		VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, COORD_STRETCH, DRAW_SET);

	// Draw title of alert form
	rect.extent.y = TitleHeight;
	VDrawRect (&rect, PS_SOLID, 0, CL_FOREGROUND, RECT_STRECTH, DRAW_SET);

	VDrawString (rect.topLeft.x+(PDAWIDTH-Vstrlen(form->objects[i].object.title->text)*6)/2, 
					 rect.topLeft.y, 
					 form->objects[i].object.title->text, 
					 Vstrlen(form->objects[i].object.title->text), 
					 SINGLELINE, 
					 CL_BACKGROUND
					 COORD_STRETCH);

	// Draw string of alert form
		} else {
			VDrawControl(form->objects[i].objectType, form->objects[i].object.ptr, DRAW_NORMAL);
		}

	// Draw button of alert form
*/
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    FormDisplayCustomAlert
//
// DESCRIPTION: This routine display a alert on the screen.
//
// PARAMETERS:  (const Char *) msg - Pointer to a NULL-terminated	string.
//
// RETURNED:    Returns nothing
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	7/24/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void FormDisplayCustomAlert (const Char *s1, const Char *s2, const Char *s3)
{
/*
	RectangleType	rect, pdaRect;
	int		strLength = Vstrlen(s1);
	int		lines = strLength/CharsPerLine;

	rect.topLeft.x = 0;
	rect.topLeft.y = PDAHEIGHT-(FORMMINHEIGHT+lines*FntLineHeight());
	rect.extent.x = PDAWIDTH;
	rect.extent.y = FORMMINHEIGHT+lines*FntLineHeight();

	FrmNewForm (999, "Warning", 0, (short)(PDAHEIGHT-(FORMMINHEIGHT+lines*FntLineHeight())),
					PDAWIDTH, (short)(FORMMINHEIGHT+lines*FntLineHeight()), true, 0, 0, 0);

	VDrawRect (&rect, PS_SOLID, 0, CL_BACKGROUND, RECT_STRECTH, DRAW_SET);
*/
}

