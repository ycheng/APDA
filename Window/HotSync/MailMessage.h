// MailMessage.h: interface for the CMailMessage class.
// Copyright (c) 1998, Wes Clyburn
//
// Modified to have Header and Body handling in this class rather than in any
// class that uses instances of CMailMessage.
// Copyright (c) 1998 Michael Krebs
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_)
#define AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <afxtempl.h>

class CMailMessage  
{
public:
	CMailMessage();
	virtual ~CMailMessage();

	int GetNumRecipients();
	BOOL GetRecipient( CString& sEmailAddress, CString& sFriendlyName, int nIndex = 0 );
	BOOL AddRecipient( LPCTSTR szEmailAddress, LPCTSTR szFriendlyName = "" );
	BOOL AddMultipleRecipients( LPCTSTR szRecipients = NULL );
	int	 Decode_QuotedPrintable(CString *Instr);
	int	 Decode_Base64(CString *InStr);
//	int	 Decode_UUEncode(CString *InStr);
	int	 Decode_ASCII(CString *InStr);
	int	 Decode_HTML(CString *InStr);

	BOOL EncodeHeader();// Create the SMTP message header as per RFC822
	BOOL DecodeHeader();// Read fields from Header - NOT COMPLETED

	void EncodeBody(); // Exchange .CR/LF by ..CR/LF
	void DecodeBody(); // There's no Base64/Mime/UU en- or decoding done here !
	CString GetBoundaryString();
	bool ResolveMultiPart(CString *InStr);
	BOOL ResolveBody(CString *InStr);

	CString m_sFrom;
	CString m_sSubject;
	CString m_sHeader;
	CTime	m_tDateTime;	
	CString m_sBody;
	CString m_sTo;
	CString m_sToAddress;
	CString m_sFromAddress;
	CString m_sBoundary;
	CString m_sContentType;
	CString m_sEncoding;

private:
	class CRecipient
	{
		public:
			CString m_sEmailAddress;
			CString m_sFriendlyName;
	};
	CArray <CRecipient, CRecipient&> m_Recipients;

	void Sort(int *pos, int size);
	int GetMin(int endpos, int startpos1, int startpos2, int startpos3);
};

#endif // !defined(AFX_MAILMESSAGE_H__55DE48CC_BEA4_11D1_870E_444553540000__INCLUDED_)
