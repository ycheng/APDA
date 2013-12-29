// MailDlg.h : Header-Datei
//
// A sample for the new CSMTP, CPOP3 and CMailMessage class
// just a few functions !
// Copyright (c) 1998 Michael Krebs
// The system generated comments are in German - you won't mind, will ya ?
//

#if !defined(AFX_MAILDLG_H__CFFD2FB3_859A_11D2_A529_444553540000__INCLUDED_)
#define AFX_MAILDLG_H__CFFD2FB3_859A_11D2_A529_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CMailDlg Dialogfeld

class CMailDlg : public CDialog
{
// Konstruktion
public:
	CMailDlg(CWnd* pParent = NULL);	// Standard-Konstruktor

// Dialogfelddaten
	//{{AFX_DATA(CMailDlg)
	enum { IDD = IDD_MAIL_DIALOG };
	CString	m_Body;
	CString	m_From;
	CString	m_To;
	CString	m_Subject;
	CString	m_FromAddress;
	CString	m_ToAddress;
	BOOL	m_MailSync;
	//}}AFX_DATA

	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	HICON m_hIcon;
	long *	pIndex;
	long	recordIndex;
	long	indexSize;
	char	MessageID[64];
	BOOL bLoggedOn;
	CMapiSession session;

	void	ImportMail();
	// Generierte Message-Map-Funktionen
	//{{AFX_MSG(CMailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnStatus();
	afx_msg void OnRetr();
	afx_msg void OnDele();
	afx_msg void OnButton1();
	afx_msg void OnSave();
	afx_msg void OnCheckMailsync();
	afx_msg void OnButtonCancel();
	afx_msg void OnButtonSync();
	afx_msg void OnMemoRadio1();
	afx_msg void OnMemoRadio2();
	afx_msg void OnMemoRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAILDLG_H__CFFD2FB3_859A_11D2_A529_444553540000__INCLUDED_)
