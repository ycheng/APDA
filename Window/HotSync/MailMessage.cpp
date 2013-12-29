// MailMessage.cpp: implementation of the CMailMessage class.
// Copyright (c) 1998, Wes Clyburn
//
// Modified to have Header and Body handling in this class rather than in any
// class that uses instances of CMailMessage.
// Copyright (c) 1998 Michael Krebs
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MailMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMailMessage::CMailMessage()
{
m_sBody=_T("");
m_sHeader=_T("");
m_sTo=_T("");
m_sToAddress=_T("");
m_sFromAddress=_T("");
m_sContentType=_T("");
}

CMailMessage::~CMailMessage()
{

}

BOOL CMailMessage::AddRecipient( LPCTSTR szEmailAddress, LPCTSTR szFriendlyName)
{
	ASSERT( szEmailAddress != NULL );
	ASSERT( szFriendlyName != NULL );
	CRecipient to;
	to.m_sEmailAddress = szEmailAddress;
	to.m_sFriendlyName = szFriendlyName;
	m_Recipients.Add( to );
	return TRUE;
}

// sEmailAddress and sFriendlyName are OUTPUT parameters.
// If the function fails, it will return FALSE, and the OUTPUT
// parameters will not be touched.
BOOL CMailMessage::GetRecipient(CString & sEmailAddress, CString & sFriendlyName, int nIndex)
{
	CRecipient to;
	if( nIndex < 0 || nIndex > m_Recipients.GetUpperBound() )
		return FALSE;
	to = m_Recipients[ nIndex ];
	sEmailAddress = to.m_sEmailAddress;
	sFriendlyName = to.m_sFriendlyName;
	return TRUE;
}

int CMailMessage::GetNumRecipients()
{
	return m_Recipients.GetSize();
}

BOOL CMailMessage::AddMultipleRecipients(LPCTSTR szRecipients )
{
	TCHAR* buf;
	UINT pos;
	UINT start;
	CString sTemp;
	CString sEmail;
	CString sFriendly;
	UINT length;
	int nMark;
	int nMark2;

	ASSERT( szRecipients != NULL );
	
	// Add Recipients
	//
	length = strlen( szRecipients );
	buf = new TCHAR[ length + 1 ];	// Allocate a work area (don't touch parameter itself)
	strcpy( buf, szRecipients );
	for( pos = 0, start = 0; pos <= length; pos++ )
	{
		if( buf[ pos ] == ';' ||
			buf[ pos ] == 0 )
		{
			// First, pick apart the sub-strings (separated by ';')
			//  Store it in sTemp.
			//
			buf[ pos ] = 0;	// Redundant when at the end of string, but who cares.
			sTemp = &buf[ start ];

			// Now divide the substring into friendly names and e-mail addresses.
			//
			nMark = sTemp.Find( '<' );
			if( nMark >= 0 )
			{
				sFriendly = sTemp.Left( nMark );
				nMark2 = sTemp.Find( '>' );
				if( nMark2 < nMark )
				{
					delete[] buf;
					return FALSE;
				}
				// End of mark at closing bracket or end of string
				nMark2 > -1 ? nMark2 = nMark2 : nMark2 = sTemp.GetLength() - 1;
				sEmail = sTemp.Mid( nMark + 1, nMark2 - (nMark + 1) );
			}
			else
			{
				sEmail = sTemp;
				sFriendly = "";
			}
			AddRecipient( sEmail, sFriendly );
			start = pos + 1;
		}
	}
	delete[] buf;
	return TRUE;
}


BOOL CMailMessage::EncodeHeader()
{
	CString sTo;
	CString sDate;

	if( GetNumRecipients() <= 0 )
		return FALSE;

	m_sHeader = "";	// Clear it

	// Get the recipients into a single string
	sTo = "";
	CString sEmail = "";
	CString sFriendly = "";
	for( int i = 0; i < GetNumRecipients(); i++ )
	{
		GetRecipient( sEmail, sFriendly, i );
		sTo += ( i > 0 ? "," : "" );
		sTo += sFriendly;
		sTo += "<";
		sTo += sEmail;
		sTo += ">";
	}
	m_tDateTime = m_tDateTime.GetCurrentTime();
	// Format: Mon, 01 Jun 98 01:10:30 GMT
	sDate = m_tDateTime.Format( "%a, %d %b %y %H:%M:%S %Z" );
	m_sHeader.Format( "Date: %s\r\n"\
					"From: %s\r\n"\
					"To: %s\r\n"\
					"Subject: %s\r\n",
					// Include other extension lines if desired
					(LPCTSTR)sDate,
					(LPCTSTR)m_sFrom,
					(LPCTSTR)sTo,
					(LPCTSTR)m_sSubject);
	return TRUE;
}

void CMailMessage::Sort(int *pos, int size)
{
	int	i, j, temp ;

	for ( i = 0; i < size-1; i++ ) {
		for ( j = 1; j < size; j++ ) {
			if ( pos[i] > pos[j] ) {
				temp = pos[i];
				pos[i] = pos[j];
				pos[j] = temp;
			}
		}
	}
}

int CMailMessage::GetMin(int endpos, int startpos1, int startpos2, int startpos3)
{
	int pos[3] ;
	int	i;

	pos[0] = startpos1;
	pos[1] = startpos2;
	pos[2] = startpos3;
	Sort (pos,3);
	for ( i = 0; i < 3; i++ ) {
		if ( pos[i] > endpos ) return pos[i];
	}

	return 0;
}

BOOL CMailMessage::DecodeHeader()
{
	int startpos, endpos;
	CString sSearchFor;
	int	From_startpos, Date_startpos, Subject_startpos;

	//We can assume that there's a CR/LF before each of the tags, as the servers insert
	//Received: lines on top of the mail while transporting the mail
//	sSearchFor="\r\nFrom: ";
	sSearchFor="From: ";
	From_startpos=m_sHeader.Find(sSearchFor);
	if (From_startpos > 0) {
		endpos=m_sHeader.Mid(From_startpos+sSearchFor.GetLength()).Find("\r\n");
		m_sFrom=m_sHeader.Mid(From_startpos+sSearchFor.GetLength(),endpos);
	}

	sSearchFor="\r\nDate: ";
	Date_startpos=m_sHeader.Find(sSearchFor);
	if (Date_startpos > 0) {
		endpos = m_sHeader.Mid(Date_startpos+sSearchFor.GetLength()).Find("\r\n");
		//DATE=m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos));
		//This is incorrect ! We have to parse the Date: line !!!
		//Anyone likes to write a parser for the different formats a date string may have ?
		m_tDateTime = m_tDateTime.GetCurrentTime();
	}

	sSearchFor="\r\nSubject: ";
	Subject_startpos=m_sHeader.Find(sSearchFor);
	if (Subject_startpos<0) return FALSE;
	endpos=m_sHeader.Mid(Subject_startpos+sSearchFor.GetLength()).Find("\r\n");
	m_sSubject=m_sHeader.Mid(Subject_startpos+sSearchFor.GetLength(),endpos);

	sSearchFor="\r\nTo: ";
	startpos=m_sHeader.Find(sSearchFor);
	if (startpos<0) return FALSE;
//	endpos=m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find("\r\n");
//	endpos=m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find("\r\nSubject");
	endpos = GetMin(startpos, From_startpos, Date_startpos, Subject_startpos);
	m_sTo=m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos-(startpos+sSearchFor.GetLength()));


	//ATTENTION: Cc parsing won't work, if Cc is split up in multiple lines
	// Cc: recipient1 <rec1@ab.cd>,
	//	   recipient2 <rec2@ab.cd>,
	//	   recipient3 <rec3@ab.cd>
	// won't work !!!
	sSearchFor="\r\nCc: ";
	startpos=m_sHeader.Find(sSearchFor);
	if (startpos>=0) //no error if there's no Cc
	{
		endpos=m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find("\r\n");
		AddMultipleRecipients(m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos));
	}

	sSearchFor="\r\nContent-Type: ";
	startpos=m_sHeader.Find(sSearchFor);
	if (startpos<0) return FALSE;
	endpos=m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find(";");
	m_sContentType=m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos);

	sSearchFor="\r\nContent-Transfer-Encoding: ";
	startpos=m_sHeader.Find(sSearchFor);
	if (startpos<0) return FALSE;
	endpos=m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find("\r\n");
	m_sEncoding=m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos);

	return TRUE;
}


void CMailMessage::EncodeBody()
{
	CString sCooked = "";
	LPTSTR szBad = "\r\n.\r\n";
	LPTSTR szGood = "\r\n..\r\n";
	int nPos;
	int nBadLength = strlen( szBad );
	if( m_sBody.Left( 3 ) == ".\r\n" )
		m_sBody = "." + m_sBody;
	//
	// This is a little inefficient because it beings a search
	// at the beginning of the string each time. This was
	// the only thing I could think of that handled ALL variations.
	// In particular, the sequence "\r\n.\r\n.\r\n" is troublesome. 
	// (Even CStringEx's FindReplace wouldn't handle that situation
	// with the global flag set.)
	//
	while( (nPos = m_sBody.Find( szBad )) > -1 )
	{
		sCooked = m_sBody.Mid( 0, nPos );
		sCooked += szGood;
		m_sBody = sCooked + m_sBody.Right( m_sBody.GetLength() - (nPos + nBadLength) );
	}
}


void CMailMessage::DecodeBody()
{
	CString sCooked = "";
	LPTSTR szBad = "\r\n..\r\n";
	LPTSTR szGood = "\r\n.\r\n";
	int nPos;
	int nBadLength = strlen( szBad );
	if( m_sBody.Left( 4 ) == "..\r\n" )
		m_sBody = m_sBody.Mid(1);
	//
	// This is a little inefficient because it beings a search
	// at the beginning of the string each time. This was
	// the only thing I could think of that handled ALL variations.
	// In particular, the sequence "\r\n.\r\n.\r\n" is troublesome. 
	// (Even CStringEx's FindReplace wouldn't handle that situation
	// with the global flag set.)
	//
	while( (nPos = m_sBody.Find( szBad )) > -1 )
	{
		sCooked = m_sBody.Mid( 0, nPos );
		sCooked += szGood;
		m_sBody = sCooked + m_sBody.Right( m_sBody.GetLength() - (nPos + nBadLength) );
	}
}

CString CMailMessage::GetBoundaryString()
{
	int startpos, endpos;
	CString sSearchFor;

	//We can assume that there's a CR/LF before each of the tags, as the servers insert
	//Received: lines on top of the mail while transporting the mail
	sSearchFor="boundary=\"";

	startpos=m_sHeader.Find(sSearchFor);
	if (startpos<0) return "";
	endpos = m_sHeader.Mid(startpos+sSearchFor.GetLength()).Find("\"\r\n");
	m_sBoundary = m_sHeader.Mid(startpos+sSearchFor.GetLength(),endpos);

	return	m_sBoundary;
}

#define XX 127
/*
 * Table for decoding hexadecimal in quoted-printable
 */
static char index_hex[256] = {
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
     0, 1, 2, 3,  4, 5, 6, 7,  8, 9,XX,XX, XX,XX,XX,XX,
    XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};

#define HEXCHAR(c)  	(index_hex[(unsigned char)(c)])
#define NEXT_CHAR(p)	((int)((p)->inbuff[(p)->pos_inbuff++]))
#define CURRENT_CHAR(p)	((int)((p)->inbuff[(p)->pos_inbuff]))
/* 
**	quoted printable decode, as defined in RFC 1521, page18 - 20
*/
int CMailMessage::Decode_QuotedPrintable(CString *InStr)
{
    char c;
    int c1, c2;
	int	Index=0;
	CString	buff;
	int	size = InStr->GetLength();
	int	size1 = InStr->GetLength();
	
	int	real_size = 0;
	
	if (InStr->GetAt(Index) == '=') {
		/*
		** continue with the last time's left over.
		*/
		InStr->SetAt(Index,0);
		
		c1 = InStr->GetAt(++Index);		InStr->SetAt(Index,0);
		
		if ( c1 == 0) {
			c1 = InStr->GetAt(++Index);
			c2 = InStr->GetAt(++Index);
		} else {
			c2 = InStr->GetAt(++Index);
		}
		c = HEXCHAR(c1) << 4 | HEXCHAR(c2);
		
		size--;
		buff += c;
		real_size ++;
	}

	/* 
	**	Then start to work on the new data 
	*/
	while ((size > 0) && (Index <=size)) {
		if (!InStr->GetAt(Index))
			break;

		c1 = InStr->GetAt(Index++);
	
		if (c1 == '=') {
			if (!InStr->GetAt(Index))	{
				InStr->SetAt(0,c1);
				break;				
			}
			
			c1 = InStr->GetAt(Index++);
			if (c1 != '\n') {
				/*
				**	Rule #2	
				*/
				c1 = HEXCHAR(c1);
				if (!InStr->GetAt(Index))	{
					InStr->SetAt(0,'=');
					InStr->SetAt(1,c1);
					break;
				}
				
				c2 = InStr->GetAt(Index++);
				c2 = HEXCHAR(c2);
				c = c1 << 4 | c2;
				if (c != '\r') {
					size --;
					buff += c;
					real_size++;
				}
			} else {
				/* ignore the line break -- soft line break, rule #5	*/
			}
		} else {
/*
			if (c1 == CR || c1 == LF) {
				if (p_ap_decode_obj->pos_inbuff < p_ap_decode_obj->s_inbuff) {
					if (p_ap_decode_obj->boundary0 && 
					 	(!PL_strncasecmp(p_ap_decode_obj->pos_inbuff+p_ap_decode_obj->inbuff, 
									"--",
									2) 
					&&
						!PL_strncasecmp(p_ap_decode_obj->pos_inbuff+p_ap_decode_obj->inbuff+2, 
									p_ap_decode_obj->boundary0, 
									nsCRT::strlen(p_ap_decode_obj->boundary0))))
						{
							return errEOP;
						} 
				}
			}
*/			
			/* 
			**	general 8bits case, Rule #1
			*/ 
			size -- ;
			buff += c1;
			real_size++;
		}
	}

	*InStr = buff;
	return real_size;
}

static char index_64[256] = {
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,62, XX,XX,XX,63,
    52,53,54,55, 56,57,58,59, 60,61,XX,XX, XX,XX,XX,XX,
    XX, 0, 1, 2,  3, 4, 5, 6,  7, 8, 9,10, 11,12,13,14,
    15,16,17,18, 19,20,21,22, 23,24,25,XX, XX,XX,XX,XX,
    XX,26,27,28, 29,30,31,32, 33,34,35,36, 37,38,39,40,
    41,42,43,44, 45,46,47,48, 49,50,51,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
    XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};

#define CHAR64(c)  (index_64[(unsigned char)(c)])

int CMailMessage::Decode_Base64(CString *InStr)
{
	int 	i, j, buf[4];
	int 	c1, c2, c3, c4;
	int	Index=0;
	CString	buff;
	int	size = InStr->GetLength();
	int	size1 = InStr->GetLength();
	
	int	real_size = 0;
	
	/*
	** 	decode 4 by 4s characters
	*/
/*
	for (i = Instr->GetAt(Index++); i<4; i++)
	{
		if (!Instr->GetAt(Index))
		{
			p_ap_decode_obj->state64 = i;
			break;
		}
		if ((p_ap_decode_obj->c[i] = fetch_next_char_64(p_ap_decode_obj)) == 0)
			break;
	}
	
	if (i != 4)
	{
		
		// not enough data to fill the decode buff.
		return errEOB;						// end of buff
	}
*/		
	while ((size > 0) && (Index < size1)) {
		do {
			c1 = InStr->GetAt(Index++);
		} while ((c1=CHAR64(c1)) == XX );
//		c1 = InStr->GetAt(Index++);
		c2 = InStr->GetAt(Index++);
		c3 = InStr->GetAt(Index++);
		c4 = InStr->GetAt(Index++);
/*		
		if (c1 == '-' || c2 == '-' || c3 == '-' || c4 == '-') {
			return real_size;			// we meet the part boundary.	
		}
		
        if (c1 == '=' || c2 == '=') {
            return real_size;
        }
*/        

        c2 = CHAR64(c2);
		buf[0] = ((c1<<2) | ((c2&0x30)>>4));

        if (c3 != '=') {
            c3 = CHAR64(c3);
		    buf[1] = (((c2&0x0F) << 4) | ((c3&0x3C) >> 2));

            if (c4 != '=') {
                c4 = CHAR64(c4);
				buf[2] = (((c3&0x03) << 6) | c4);
            } else {
        		buff += buf[0]; (real_size)++;
	        	buff += buf[1]; (real_size)++;
				// return errEOP; bug 87784 
				*InStr = buff ;
				return real_size;
            }
        } else {
        	buff += *buf;
        	(real_size)++;
			// return errEOP; *bug 87784	 we meet the the end
			*InStr = buff ;
			return real_size;
        }

        /*
		** copy the content
		*/

		if ( (c1==XX)&&(c2==XX)&&(c3==XX)&&(c4==XX) ) {
		} else {
		for (j = 0; j<3; )
		{
			buff += buf[j++];	
			(real_size)++;
			if (--size <= 0)
				break;
		}
		}
/*
		p_ap_decode_obj->left = j % 3;
	
		if (size <=0)
		{
			if (j == 3)
				p_ap_decode_obj->state64 = 0;	// See if we used up all data, 	
												// ifnot, keep the data, 		
												// we need it for next time.	
			else
				p_ap_decode_obj->state64 = 4;
				
			break;
		}
*/			
		/*
		**	fetch the next 4 character group. 
		*/
/*
		for (i = 0; i < 4; i++)
		{
			if (EndOfBuff(p_ap_decode_obj))
				break;

			if ((p_ap_decode_obj->c[i] = fetch_next_char_64(p_ap_decode_obj)) == 0)
				break;
		}

		p_ap_decode_obj->state64 = i % 4;
	
		if (i != 4)
			break;								// some kind of end of buff met.
*/
	}

	/*
	**	decide the size and status. 
	*/
	*InStr = buff ;
	return real_size;
}

/* 
**	uudecode
*/
/*
#define UUDEC(c) (((c) - ' ') & 077)

int CMailMessage::Decode_UUEncode(CString *InStr)
{
    char c;
    int i;
    int returnVal = NOERR;
	int 	c1, c2, c3, c4;
	int	Index=0;
	CString	buff;
	int	size = InStr->GetLength();
	int	size1 = InStr->GetLength();
	
	int	real_size = 0;
	

	//	Make sure that we're in the uuencode body, or run out the buffer if
		we don't have any body text in this buffer. 

	ensure_uu_body_state(p_ap_decode_obj);
	
	if (p_ap_decode_obj->uu_state == kEnd)
		return errEOP;
	
	// Continue with what was left over last time. 

	for (i = p_ap_decode_obj->state64; i<4; i++)
	{
		if (EndOfBuff(p_ap_decode_obj))
		{
			p_ap_decode_obj->state64 = i;
			break;
		}
		if ((p_ap_decode_obj->c[i] = fetch_next_char_uu(p_ap_decode_obj, (i==0))) == 0)
			break;
	}

	if ( (i < p_ap_decode_obj->uu_line_bytes+1)
		&& (EndOfBuff(p_ap_decode_obj)))
		// not enough data to decode, return here. 
		return errEOB;


	while((size > 0) && (Index<Size1))
	{
		c1 = InStr->GetAt(Index++);
		c2 = InStr->GetAt(Index++);
		c3 = InStr->GetAt(Index++);
		c4 = InStr->GetAt(Index++);
		
		
		//	At this point we have characters ready to decode.
		//	Convert them to binary bytes.
		
		if ((i > 1) 
			&& (p_ap_decode_obj->uu_bytes_written < 1)
			&& (p_ap_decode_obj->uu_line_bytes > 0))
		{
			c = UUDEC(c1) << 2 | UUDEC(c2) >> 4;
			size --;
			*buff ++ = c;
			(*real_size) ++;
			p_ap_decode_obj->uu_line_bytes--;
			p_ap_decode_obj->uu_bytes_written++;
		}
		
		if ((i > 2) && (size > 0) 
			&& (p_ap_decode_obj->uu_bytes_written < 2)
			&& (p_ap_decode_obj->uu_line_bytes > 0))
		{
			c = UUDEC(c2) << 4 | UUDEC(c3) >> 2;
			size --;
			*buff ++ = c;
			(*real_size) ++;
			p_ap_decode_obj->uu_line_bytes--;
			p_ap_decode_obj->uu_bytes_written++;
		}

		if ((i > 3) && (size > 0)
			&& (p_ap_decode_obj->uu_line_bytes > 0))
		{
			c = UUDEC(c3) << 6 | UUDEC(c4);
			size --;
			*buff ++ = c;
			(*real_size) ++;
			p_ap_decode_obj->uu_line_bytes--;
			p_ap_decode_obj->uu_bytes_written = 0;
		}

		if (p_ap_decode_obj->uu_state == kEnd)
			continue;

		// If this line is finished, this tuple is also finished. 
		if (p_ap_decode_obj->uu_line_bytes <= 0)
			p_ap_decode_obj->uu_bytes_written = 0;

		if (p_ap_decode_obj->uu_bytes_written > 0)
		{
			// size == 0, but we have bytes left in current tuple 
			p_ap_decode_obj->state64 = i;
			continue;
		}
			
		
		//	fetch the next 4 character group. 
		
			
		for (i = 0; i < 4; i++)
		{
			if (EndOfBuff(p_ap_decode_obj))
				break;

			if ((p_ap_decode_obj->c[i] = fetch_next_char_uu(p_ap_decode_obj, (i == 0))) == 0)
				break;
		}

		p_ap_decode_obj->state64 = i;

		if ( (i < p_ap_decode_obj->uu_line_bytes+1)
			&& (EndOfBuff(p_ap_decode_obj)))
			// not enough data to decode, return here. 
			continue;
	}

	if (p_ap_decode_obj->uu_state == kEnd)
		returnVal = errEOP;
	else if (EndOfBuff(p_ap_decode_obj))
		returnVal = errEOB;
		

	return real_size;
}
*/

int CMailMessage::Decode_ASCII(CString *InStr)
{
    int c1, c2;
	int	Index=0;
	CString	buff1, buff2, buff3;
	int	size = InStr->GetLength();
	int	real_size = 0;
	
	if (!size) return 0;
	
	c1 = InStr->GetAt(0);
	c2 = InStr->GetAt(1);
	int StartPos = InStr->Find("=?");
	int EndPos = InStr->Find("?=");

	if ( (StartPos >= 0) && EndPos ) {
		buff1 = InStr->Left(StartPos);
		Index = InStr->Find("?B?");
		if ( Index < 0 ) {
			Index = InStr->Find("?b?");
		}
		if ( Index > 0 ) {
			// this is a base64 encoded string
			buff2 = InStr->Mid(Index+3,EndPos-(Index+3));
			real_size = Decode_Base64 (&buff2);
			buff3 = InStr->Mid(EndPos+2);
			if ( buff3.GetLength() ) {
				Decode_ASCII(&buff3);
			}
			*InStr = buff1+buff2+buff3;
		}
	}
	

	// it's an encode string if it start with =?
	// and end with ?=
/*
	if ( (c1 == '=') && (c2 == '?') && (StartPos > 0) ) {
		Index = InStr->Find("?B?");
		if ( Index < 0 ) {
			Index = InStr->Find("?b?");
		}
		buff1 = InStr->Mid(Index+3,StartPos-(Index+3));
		real_size = Decode_Base64 (&buff1);
		buff2 = InStr->Mid(InStr->Find("\r\n")+2);
		StartPos = buff2.Find("=?");
		if ( StartPos > 0 ) {
			int EndPos = buff2.Find("?=");
			StartPos = buff2.Find("?B?");
			if ( StartPos < 0 )
				StartPos = buff2.Find("?b?");
			buff2 = buff2.Mid(StartPos+3,EndPos-(StartPos+3));
			Decode_ASCII(&buff2);
		}
		*InStr = buff1+buff2;
	}
*/
	return real_size;
}

int CMailMessage::Decode_HTML(CString *InStr)
{
	CString	buff1, buff2;
	int	size = InStr->GetLength();
	int	real_size = 0;
	int	startpos, endpos;
	
	if (!size) return 0;
	
	startpos = InStr->Find("<");
	if ( startpos < 0 ) return 0;
	buff1 = InStr->Left(startpos);
	endpos = InStr->Mid(startpos+1).Find(">");

	buff2 = InStr->Mid(startpos+endpos+2);
	real_size = buff1.GetLength();
	real_size += Decode_HTML(&buff2);
	*InStr = buff1+buff2;

	return	real_size;
}

BOOL CMailMessage::ResolveBody(CString *InStr)
{
	int	startpos, endpos;
	CString	Encoding;

	CString	sSearchFor="\r\nContent-Transfer-Encoding: ";
	startpos=InStr->Find(sSearchFor);
	if (startpos<0) {
		if (m_sEncoding) {
			Encoding = m_sEncoding;
		} else {
			return FALSE;
		}
	} else {
		endpos=InStr->Mid(startpos+sSearchFor.GetLength()).Find("\r\n");
		Encoding=InStr->Mid(startpos+sSearchFor.GetLength(),endpos);
	}

	if ( Encoding.Left(6) == "base64" ) {
		startpos = startpos+sSearchFor.GetLength()+endpos+2;
		*InStr = InStr->Mid(startpos);
		Decode_Base64(InStr);
	} else if ( Encoding.Left(6) == "quoted") {
//		msg->Decode_QuotedPrintable(&msg->m_sHeader);
		startpos = startpos+sSearchFor.GetLength()+endpos+2;
		*InStr = InStr->Mid(startpos);
		Decode_QuotedPrintable(InStr);
	} 
	
	if ( m_sContentType.Left(9) == "text/html") {
		Decode_HTML(InStr);
	}


	return	TRUE;
}

bool CMailMessage::ResolveMultiPart(CString *InStr)
{
	int startpos, endpos;
	CString	buff1, buff2;
	int	len1, len2;

	len1 = InStr->GetLength();
	//We can assume that there's a CR/LF before each of the tags, as the servers insert
	//Received: lines on top of the mail while transporting the mail
	startpos=InStr->Find(m_sBoundary);
	if (startpos<0) return false;
//	startpos += (m_sBody.Mid(startpos+4).Find("\r\n\r\n")+4);
	endpos = InStr->Mid(startpos+m_sBoundary.GetLength()+2).Find(m_sBoundary);
	if ( endpos > InStr->GetLength() ) {
		*InStr = InStr->Mid(startpos+m_sBoundary.GetLength()+2);
		return	true;
	} else if ( endpos < 0 ) {
		*InStr = InStr->Left(startpos);
		return	true;
	}
	buff1 = InStr->Mid(startpos+m_sBoundary.GetLength()+2,endpos);
	buff2 = InStr->Mid(endpos);
	len1 = buff1.GetLength();
	len2 = buff2.GetLength();
	ResolveMultiPart(&buff2);
	ResolveBody(&buff1);
	ResolveBody(&buff2);

	*InStr = buff1+buff2;

	return true;
}


