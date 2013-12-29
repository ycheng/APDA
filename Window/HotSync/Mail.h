// Mail.h : Haupt-Header-Datei für die Anwendung MAIL
//

#if !defined(AFX_MAIL_H__CFFD2FB1_859A_11D2_A529_444553540000__INCLUDED_)
#define AFX_MAIL_H__CFFD2FB1_859A_11D2_A529_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CMailApp:
// Siehe Mail.cpp für die Implementierung dieser Klasse
//

class CMailApp : public CWinApp
{
public:
	CMailApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CMailApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CMailApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_MAIL_H__CFFD2FB1_859A_11D2_A529_444553540000__INCLUDED_)
