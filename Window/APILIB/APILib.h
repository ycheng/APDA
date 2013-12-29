// APILib.h : main header file for the APILIB DLL
//

#if !defined(AFX_APILIB_H__F5557BE5_B89D_4CE5_8455_C9D4195F5C2A__INCLUDED_)
#define AFX_APILIB_H__F5557BE5_B89D_4CE5_8455_C9D4195F5C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAPILibApp
// See APILib.cpp for the implementation of this class
//

class CAPILibApp : public CWinApp
{
public:
	CAPILibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAPILibApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAPILibApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APILIB_H__F5557BE5_B89D_4CE5_8455_C9D4195F5C2A__INCLUDED_)
