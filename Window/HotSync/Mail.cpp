// Mail.cpp : Legt das Klassenverhalten f�r die Anwendung fest.
//

#include "stdafx.h"
#include "MailMessage.h"
#include "cmapi.h"
#include "Mail.h"
#include "MailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailApp

BEGIN_MESSAGE_MAP(CMailApp, CWinApp)
	//{{AFX_MSG_MAP(CMailApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailApp Konstruktion

CMailApp::CMailApp()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einf�gen
	// Alle wichtigen Initialisierungen in InitInstance platzieren
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CMailApp-Objekt

CMailApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMailApp Initialisierung

BOOL CMailApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standardinitialisierung
	// Wenn Sie diese Funktionen nicht nutzen und die Gr��e Ihrer fertigen 
	//  ausf�hrbaren Datei reduzieren wollen, sollten Sie die nachfolgenden
	//  spezifischen Initialisierungsroutinen, die Sie nicht ben�tigen, entfernen.

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif

	CMailDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber OK zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// ZU ERLEDIGEN: F�gen Sie hier Code ein, um ein Schlie�en des
		//  Dialogfelds �ber "Abbrechen" zu steuern
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zur�ckliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}

