// MailDlg.cpp : Implementierungsdatei
//
// A sample for the new CSMTP, CPOP3 and CMailMessage class
// just a few functions !
// Copyright (c) 1998 Michael Krebs
// The system generated comments are in German - you won't mind, will ya ?
//

#include "stdafx.h"
#include <io.h>
#include "MailMessage.h"
#include "cmapi.h"
#include "Mail.h"
#include "MailDlg.h"
#include "database.h"
#include "hotsync.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int	iPIMSync = 0;
extern HWND			hWnd;
extern BYTE			syncStatus;
char		directory[256];

extern BOOL NEAR OpenConnection();
extern BOOL NEAR CloseConnection();
extern LRESULT NEAR CreateTTYInfo() ;


extern int GetCommChar ();
extern int PutCommChar (int ch);

typedef int GetChar ();
typedef int PutChar (int ch);

typedef	GetChar*	GetCharPtr;
typedef	PutChar*	PutCharPtr;


//extern errcode_t SendFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c));
//extern errcode_t RecvFile(const char *fname, int (*GetCh)(), int (*PutCh)(int c));

/////////////////////////////////////////////////////////////////////////////
// CMailDlg Dialogfeld

CMailDlg::CMailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMailDlg)
	m_Body = _T("");
	m_From = _T("");
	m_To = _T("");
	m_Subject = _T("");
	m_FromAddress = _T("");
	m_ToAddress = _T("");
	m_MailSync = TRUE;
	bLoggedOn = NULL;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf benötigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMailDlg)
	DDX_Check(pDX, IDC_CHECK_MAILSYNC, m_MailSync);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMailDlg, CDialog)
	//{{AFX_MSG_MAP(CMailDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CHECK_MAILSYNC, OnCheckMailsync)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_SYNC, OnButtonSync)
	ON_BN_CLICKED(IDC_MEMO_RADIO1, OnMemoRadio1)
	ON_BN_CLICKED(IDC_MEMO_RADIO2, OnMemoRadio2)
	ON_BN_CLICKED(IDC_MEMO_RADIO3, OnMemoRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailDlg Nachrichten-Handler

BOOL CMailDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
//	SetCheck(1);
	CheckRadioButton (IDC_MEMO_RADIO1, IDC_MEMO_RADIO2, IDC_MEMO_RADIO3);
	CheckDlgButton (IDC_MEMO_RADIO3, true);
	int radio = GetCheckedRadioButton (IDC_MEMO_RADIO1, IDC_MEMO_RADIO3);

	GetCurrentDirectory(256, directory);
	// ZU ERLEDIGEN: Hier zusätzliche Initialisierung einfügen
	
	return TRUE;  // Geben Sie TRUE zurück, außer ein Steuerelement soll den Fokus erhalten
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch für Sie erledigt.

void CMailDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext für Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, während der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CMailDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// view previous record
void CMailDlg::OnSend() 
{
/*
	CMailMessage msg;
	if (recordIndex > 0)
		recordIndex-- ;
	if (OExpress.GetMail( &msg, pIndex, recordIndex)) {
		m_Body=msg.m_sBody;
		m_Subject=msg.m_sSubject;
		m_From=msg.m_sFrom;
		m_FromAddress=msg.m_sFromAddress;
		m_To=msg.m_sTo;
		m_ToAddress=msg.m_sToAddress;

		UpdateData(FALSE);
	}
*/
}

void CMailDlg::OnStatus() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
}

void CMailDlg::OnRetr() 
{
	CMailMessage msg;
	if (bLoggedOn) {
	    //Send the message
	    BOOL bSent = session.ReadNext(MessageID, &msg);
		m_Body=msg.m_sBody;
		m_Subject=msg.m_sSubject;
		m_From=msg.m_sFrom;
		m_FromAddress=msg.m_sFromAddress;
		m_To=msg.m_sTo;
		m_ToAddress=msg.m_sToAddress;

		UpdateData(FALSE);
	}
}

void CMailDlg::OnDele() 
{
}

void CMailDlg::ImportMail() 
{
	// TODO: Add your control notification handler code here
	CMailMessage msg;

	BOOL bMapiInstalled = session.MapiInstalled();

	//Logon to MAPI
	bLoggedOn = session.Logon(_T("PJ Naughter")); //You will need to change this to use a MAPI profile
                                                     //setup on your computer. If you want CMapiSession to
                                                     //bring up a dialog to allow a MAPI profile to be 
                                                     //interactively chosen, then you will need to create
                                                     //a Window in your app using the normal MFC mechanims 
   
	DmOpenRef     MailDb=NULL;	
	Word          mailIndex=0;
	UInt32          recSize, totalSize=0; 
	     //  create pdb     
		MailDb=OpenPdb();
		if ( !MailDb )
			return;

	if (bLoggedOn) {
	    //Send the message
	    BOOL bSent = session.ReadFirst(MessageID, &msg);
		m_Body=msg.m_sBody;
		m_Subject=msg.m_sSubject;
		m_From=msg.m_sFrom;
		m_FromAddress=msg.m_sFromAddress;
		m_To=msg.m_sTo;
		m_ToAddress=msg.m_sToAddress;
			
		recSize=DataBaseSize(MailDb,m_From,m_Subject,m_Body);
		if((recSize+totalSize) < DatabaseBound) {
			SaveMailToDb(MailDb,m_From,m_Subject,m_Body,mailIndex++);
			totalSize += recSize;
		}

		while ( (bSent = session.ReadNext(MessageID, &msg))) {
			m_Body=msg.m_sBody;
			m_Subject=msg.m_sSubject;
			m_From=msg.m_sFrom;
			m_FromAddress=msg.m_sFromAddress;
			m_To=msg.m_sTo;
			m_ToAddress=msg.m_sToAddress;

			
			recSize=DataBaseSize(MailDb,m_From,m_Subject,m_Body);
			if ( totalSize > DatabaseBound-1024 )
				break;
			if((recSize < 5120) &&(recSize+totalSize) < DatabaseBound) {
    			SaveMailToDb(MailDb,m_From,m_Subject,m_Body,mailIndex++);
				totalSize += recSize;
			}
		}
		
		
	   UpdateData(FALSE);

	}
}

void CMailDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
  CMapiMessage message;

  UpdateData(TRUE);
  if ( (m_To.GetLength()!=0) && (m_Subject.GetLength()!=0) && (m_Body.GetLength()!=0) ) {
	  if (m_From.GetLength()!=0) {
		message.m_From.Add(m_From);
	  }
	message.m_To.Add(m_To);
//	message.m_CC.Add(_T("SMTP:pjn@indigo.ie"));
//	message.m_BCC.Add(_T("SMTP:pj.naughter@softech-telecom.com"));
	message.m_sSubject = _T(m_Subject);
	message.m_sBody = _T(m_Body);
  } else {
	  return ;
  }
//  message.m_Attachments.Add(_T("C:\\autoexec.bat"));
//  message.m_AttachmentTitles.Add(_T("my autoexec.bat"));

  //Setup the mapi session

  CMapiSession session;
  BOOL bMapiInstalled = session.MapiInstalled();

  //Logon to MAPI
  BOOL bLoggedOn = session.Logon(_T("PJ Naughter")); //You will need to change this to use a MAPI profile
                                                     //setup on your computer. If you want CMapiSession to
                                                     //bring up a dialog to allow a MAPI profile to be 
                                                     //interactively chosen, then you will need to create
                                                     //a Window in your app using the normal MFC mechanims 
  if (bLoggedOn)
  {

    //Send the message
    BOOL bSent = session.Send(message);
  }
}

void CMailDlg::OnSave() 
{
	// TODO: Add your control notification handler code here
	
}

void CMailDlg::OnCheckMailsync() 
{
	// TODO: Add your control notification handler code here
//	bMailSync = !bMailSync;
	m_MailSync = !m_MailSync;
}

void CMailDlg::OnButtonCancel() 
{
	// TODO: Add your control notification handler code here
//	PostQuitMessage(0);
	OnCancel();
}
void CMailDlg::OnButtonSync() 
{
   HCURSOR    hOldCursor, hWaitCursor ;
	hWnd = AfxGetMainWnd()->GetSafeHwnd();

   // show the hourglass cursor
   hWaitCursor = LoadCursor( NULL, IDC_WAIT ) ;
   hOldCursor = SetCursor( hWaitCursor ) ;

	// TODO: Add your control notification handler code here
	CreateTTYInfo();
	OpenConnection ();
	syncStatus = 1;
	if ( m_MailSync ) {
		ImportMail ();
		SendFile ( "c:\\windows\\desktop\\desktop\\PMail.PDB", GetCommChar, PutCommChar );
	}
	if ( iPIMSync == 1 ) {	// sync from PC to PDA
		SendFile ( "c:\\windows\\desktop\\desktop\\MEMO.PDB", GetCommChar, PutCommChar );
		SendFile ( "c:\\windows\\desktop\\desktop\\ADDRESS.PDB", GetCommChar, PutCommChar );
	} else if ( iPIMSync == 2 ) {	// sync from PDA to PC
		RecvFile ( "MEMO.PDB", GetCommChar, PutCommChar );
		RecvFile ( "ADDRESS.PDB", GetCommChar, PutCommChar );
	}
	syncStatus=0;
	CloseConnection ();
   // restore cursor
   SetCursor( hOldCursor ) ;
}

void CMailDlg::OnMemoRadio1() 
{
	// TODO: Add your control notification handler code here
	iPIMSync = 1;
}

void CMailDlg::OnMemoRadio2() 
{
	// TODO: Add your control notification handler code here
	iPIMSync = 2;
}

void CMailDlg::OnMemoRadio3() 
{
	// TODO: Add your control notification handler code here
	iPIMSync = 0;
}

DmOpenRef OpenPdb() 
{ 
    Word        mode;      
    DmOpenRef   dbP;             

	      mode = dmModeReadOnly; 	
         if( DmCreateDatabase(0,dBName,creatorID,dBType,false) !=0 )    
         dbP=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);   
   	   if(!dbP)   {         
                  if( DmCreateDatabase(0,dBName,creatorID,dBType,false) !=0 )    
                      return   NULL;
                  dbP=DmOpenDatabaseByTypeCreator(dBType,creatorID,mode);
                  if( !dbP)
   	                return  NULL;        
   	   }  
      	     
      	return dbP;
 }  

      //  save to pdb 
void  SaveMailToDb(DmOpenRef  dbP,CString  fromP,CString  subjP,CString  bodyP,Word  index)
{
		MemHandle     mailH;
		MemPtr		  mailP;	
		DWord         fromTextSize,subjectTextSize,bodyTextSize;
		DWord         mailSize;
		DWord         offset=0;
	          

		
		       
		fromTextSize=fromP.GetLength()+nullChrSize;
		subjectTextSize=subjP.GetLength()+nullChrSize;
		bodyTextSize=bodyP.GetLength()+nullChrSize;
		mailSize=fromTextSize+subjectTextSize+bodyTextSize;
      mailH=DmNewRecord(dbP,&index,mailSize);
		if(mailH) {
			mailP=MemHandleLock(mailH);
			DmSet(mailP,offset,mailSize,0);
		}
		ReplaceCrChrToLfChr(&fromP);
		DmWrite(mailP,offset,fromP,fromTextSize);
		offset+=fromTextSize;
		ReplaceCrChrToLfChr(&subjP);
		DmWrite(mailP,offset,subjP,subjectTextSize);
		offset+=subjectTextSize;
		ReplaceCrChrToLfChr(&bodyP);
		DmWrite(mailP,offset,bodyP,bodyTextSize);
		offset+=bodyTextSize;
	   MemHandleUnlock(mailH); 
		DmReleaseRecord(dbP,index,true);

	
}



void  ReplaceCrChrToLfChr(CString  *SrcP)
{
      
	int index=0;
	TCHAR	ch;
	int length = SrcP->GetLength();

	while(index < SrcP->GetLength ()) {
		ch = SrcP->GetAt(index);
		if ( ch == nullChr)
			break;

      if(ch==crChr) {
			*SrcP = SrcP->Left (index)+SrcP->Right(length-index-1);
			length--;
			index--;
		}
		index++;
   }  

}



UInt16  DataBaseSize(DmOpenRef  dbP,CString fromP,CString subjP, CString bodyP)

{
      DWord       newDbSize=0;      	  
      DWord       fromSize,subjSize,bodySize;

      fromSize= (fromP) ? fromP.GetLength()+1 : nullChrSize;
      subjSize= (subjP) ? subjP.GetLength()+1 : nullChrSize;
      bodySize= (bodyP) ? bodyP.GetLength()+1 : nullChrSize;
		
		return	(fromSize+subjSize+bodySize);
}
