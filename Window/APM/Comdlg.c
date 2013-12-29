// COMDLG.C -- This has the Common Dialog code in it
//
// Sample code from the SDK with minimal changes
//

#include <windows.h>
#include <commdlg.h>
#include <dlgs.h>    // for fileopen.dlg

#include "comdlg.h"   // Stuff for other apps
#include "cddemo.h"  
#include "base1.h"  // This depends on your app

char szFilenameFilter      [256];
char szInitialdir          [256];
char szDefaultExtension    [4] = "dll"; // Wildcard
extern HWND hwnd;
extern HMODULE				appInst;

#define PARAMETER_VALIDATION

#define DEBUGOUT(szLine)         \
  {                              \
  OutputDebugString ( szLine );  \
  OutputDebugString ( "\r\n" );  \
  }

DLGPROC COMDLG_OpenFileHook ( DIALOG_PARAMS );
void RebuildCommDlgFileTypes ( HWND hDlg, LPSTR szFilenameFilter );
DLGPROC COMDLG_OpenFile_WM_COMMAND ( DIALOG_PARAMS );

////////////////////////////////////////////////////////////////////////
// FUNCTION:    ComDlgFormatFilterString
//
// DESCRIPTION: To initialize the szFilenameFilter variable with strings 
//					 from the string table.  This method of initializing 
//					 szInitialdir is necessary to ensure that the strings are 
//					 contiguous in memory--which is what COMMDLG.DLL requires.
//
// PARAMETERS:  None.
//
// RETURNED:    Returns TRUE if successful, FALSE if failure loading string.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
BOOL NEAR ComDlgFormatFilterString(void)
{
   WORD  wCtr, wStringLen;
   char  chWildChar;
   static int iRotateAFilter;

   *szFilenameFilter=0;

	// Set loading string (file extention type)
	wStringLen = 20;
	strcpy (szFilenameFilter, "Program Files|*.DLL|");
/*
   if (!(wStringLen=LoadString(appInst,
                               IDS_FILTERSTRING+iRotateAFilter, 
                               szFilenameFilter, 
                               sizeof(szFilenameFilter) )) ) {
		ERROR_ReportError(IDC_LOADSTRINGFAIL);
		return(FALSE);
	}
*/
	iRotateAFilter = !iRotateAFilter; // Flip from 0 to 1 to 0 to 1...

	chWildChar = szFilenameFilter[wStringLen-1];    //Grab the wild character

	wCtr = 0;

   while (szFilenameFilter[wCtr]) {
		if (szFilenameFilter[wCtr]==chWildChar)
			szFilenameFilter[wCtr]=0;
		wCtr++;
	}

   return(TRUE);
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    InitializeStruct
//
// DESCRIPTION: To initialize a structure for the current common dialog.
//					 This routine is called just before the common dialogs
//					 API is called.
//
// PARAMETERS:  (WORD) wCommDlgType -
//					 (LPSTR) lpStruct -
//
// RETURNED:    Returns none.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
void NEAR InitializeStruct(WORD wCommDlgType, LPSTR lpStruct)
{
   LPFOCHUNK           lpFOChunk;
   LPFSCHUNK           lpFSChunk;
   
   switch (wCommDlgType) {
      case COMDLG_ACTION_FILEOPEN:
         lpFOChunk = (LPFOCHUNK)lpStruct;

         *szInitialdir = 0;

         ComDlgFormatFilterString();  //Formats szFilenameFilter with strings

         *(lpFOChunk->szFile)            = 0;
         *(lpFOChunk->szFileTitle)       = 0;
         lpFOChunk->of.lStructSize       = sizeof(OPENFILENAME);
         lpFOChunk->of.hwndOwner         = (HWND)hwnd;
         lpFOChunk->of.hInstance         = (HANDLE)appInst;
         lpFOChunk->of.lpstrFilter       = szFilenameFilter;
         lpFOChunk->of.lpstrCustomFilter = (LPSTR)NULL;
         lpFOChunk->of.nMaxCustFilter    = 0L;
         lpFOChunk->of.nFilterIndex      = 1L;
         lpFOChunk->of.lpstrFile         = lpFOChunk->szFile;
         lpFOChunk->of.nMaxFile          = (DWORD)sizeof(lpFOChunk->szFile);
         lpFOChunk->of.lpstrFileTitle    = lpFOChunk->szFileTitle;
         lpFOChunk->of.nMaxFileTitle     = MAXFILETITLELEN;
         lpFOChunk->of.lpstrInitialDir   = szInitialdir;
         lpFOChunk->of.lpstrTitle        = (LPSTR)NULL;
         lpFOChunk->of.Flags             = OFN_HIDEREADONLY |
                                           OFN_ENABLEHOOK |
                                           OFN_ENABLETEMPLATE |
                                           OFN_PATHMUSTEXIST ;
         lpFOChunk->of.nFileOffset       = 0;
         lpFOChunk->of.nFileExtension    = 0;
         lpFOChunk->of.lpstrDefExt       = (LPSTR)szDefaultExtension;
         lpFOChunk->of.lCustData         = 0L;
         lpFOChunk->of.lpfnHook          = (FARPROC)MakeProcInstance (COMDLG_OpenFileHook, appInst);
         lpFOChunk->of.lpTemplateName    = (LPSTR)FILEOPENORD;

         break;

      case COMDLG_ACTION_FILESAVEAS:

         lpFSChunk = (LPFSCHUNK)lpStruct;

         *szInitialdir = 0;

         ComDlgFormatFilterString();  //Formats szFilenameFilter with strings

         *(lpFSChunk->szFile)            = 0;
         lpFSChunk->of.lStructSize       = sizeof(OPENFILENAME);
         lpFSChunk->of.hwndOwner         = (HWND)hwnd;
         lpFSChunk->of.hInstance         = (HANDLE)NULL;
         lpFSChunk->of.lpstrFilter       = szFilenameFilter;
         lpFSChunk->of.lpstrCustomFilter = (LPSTR)NULL;
         lpFSChunk->of.nMaxCustFilter    = 0L;
         lpFSChunk->of.nFilterIndex      = 1L;
         lpFSChunk->of.lpstrFile         = lpFSChunk->szFile;
         lpFSChunk->of.nMaxFile          = (DWORD)sizeof(lpFSChunk->szFile);
         lpFSChunk->of.lpstrFileTitle    = lpFSChunk->szFileTitle;
         lpFSChunk->of.nMaxFileTitle     = MAXFILETITLELEN;
         lpFSChunk->of.lpstrInitialDir   = szInitialdir;
         lpFSChunk->of.lpstrTitle        = (LPSTR)NULL;
         lpFSChunk->of.Flags             = OFN_OVERWRITEPROMPT;
         lpFSChunk->of.nFileOffset       = 0;
         lpFSChunk->of.nFileExtension    = 0;
         lpFSChunk->of.lpstrDefExt       = (LPSTR)szDefaultExtension;
         lpFSChunk->of.lCustData         = 0L;
         lpFSChunk->of.lpfnHook          = NULL;
         lpFSChunk->of.lpTemplateName    = (LPSTR)NULL;

         break;
      }

   return;
}

////////////////////////////////////////////////////////////////////////
// FUNCTION:    AllocAndLockMem
//
// DESCRIPTION: To allocate and lock a chunk of memory for the CD structure.   
//
// PARAMETERS:  (HANDLE *) hChunk -
//					 (WORD) wSize - size of chunk of memory.
//
// RETURNED:    Returns pointer of allocated memory.
//
// REVISION HISTORY:
//			Name	Date		Description
//			----	----		-----------
//			Jerry	6/14/01	Initial Revision
////////////////////////////////////////////////////////////////////////
LPSTR NEAR AllocAndLockMem(HANDLE *hChunk, WORD wSize)
{
   LPSTR lpChunk;

   *hChunk = GlobalAlloc(GMEM_FIXED, wSize);

   if (*hChunk) {
		lpChunk = GlobalLock(*hChunk);
		if (!lpChunk) {
			GlobalFree(*hChunk);
			ERROR_ReportError(IDC_LOCKFAIL);
			lpChunk=NULL;
		}
	} else {
		ERROR_ReportError(IDC_ALLOCFAIL);
		lpChunk=NULL;
	}

   return(lpChunk);
}

/*********************************************************************
*                                                                    *
*  COMDLG_ComDlgGetFileName                                          *
*                                                                    *
*  Fills the szFileName string with whatever the user chooses from   *
*  the File Common Dialog                                            *
*                                                                    *
*  wAction    Either IDM_FILEOPEN or IDM_FILEDUPLICATE, to bring     *
*             up the "Load" or "Save As" dialog                      *
*                                                                    *
*  szFileName Points to a string buffer for the filename             *
*                                                                    *
*  Return Value:                                                     *
*                                                                    *
*  If user pressed OK:     TRUE                                      *
*  If user pressed Cancel: FALSE                                     *
*                                                                    *
*********************************************************************/
BOOL COMDLG_ComDlgGetFileName ( WORD wAction, LPSTR szFileName )
{
  LPFOCHUNK lpFOChunk;    //Pointer to File Open block
  LPFSCHUNK lpFSChunk;    //Pointer to File Save block
  HANDLE    hfoChunk;     //Handle to File Open block of memory
  HANDLE    hfsChunk;     //Handle to File Save block of memory
  WORD      wSize;

#ifdef PARAMETER_VALIDATION

  if (IsBadWritePtr ( szFileName, 256 ))
    {
    DEBUGOUT ("COMDLG_ComDlgGetFileName: Invalid szFileName");
    return FALSE;
    }

#endif

	switch (wAction) {
		case COMDLG_ACTION_FILEOPEN:

			wSize=sizeof(FOCHUNK);

			if (!(lpFOChunk=(LPFOCHUNK)AllocAndLockMem(&hfoChunk, wSize)))
				break;

			InitializeStruct(COMDLG_ACTION_FILEOPEN, (LPSTR)lpFOChunk);

			if ( GetOpenFileName( &(lpFOChunk->of) ) ) {
				lstrcpy ( szFileName, lpFOChunk->of.lpstrFile);

//NOTE!!!  On a closed system (ie, not running on a network) this OpenFile
//         call should NEVER fail.  This because we passed in the 
//         OFN_FILEMUSTEXIST flag to CD.  However, on a network system,
//         there is a *very* small chance that between the time CD's checked
//         for existance of the file and the time the call to OpenFile
//         was made here, someone else on the network has deleted the file.
//         MORAL: ALWAYS, ALWAYS, ALWAYS check the return code from your
//         call to OpenFile() or _lopen.

			} else {
				*szFileName = 0;
				ERROR_ProcessCDError(CommDlgExtendedError());
			}

			// This hook proc instance was set inside the InitializeStruct function

			if (lpFOChunk->of.lpfnHook)
				FreeProcInstance (lpFOChunk->of.lpfnHook);

			GlobalUnlock ( hfoChunk );
			GlobalFree   ( hfoChunk );

			return (BOOL)*szFileName ;

			break;

		case COMDLG_ACTION_FILESAVEAS:

			wSize=sizeof(FOCHUNK);

			if (!(lpFSChunk=(LPFOCHUNK)AllocAndLockMem(&hfsChunk, wSize)))
				break;

			InitializeStruct(COMDLG_ACTION_FILESAVEAS, (LPSTR)lpFSChunk);

			if ( GetSaveFileName( &(lpFSChunk->of) ) ) {
				lstrcpy ( szFileName, lpFSChunk->of.lpstrFile);
			} else {
				*szFileName = 0;
				ERROR_ProcessCDError(CommDlgExtendedError());
			}

			GlobalUnlock ( hfsChunk );
			GlobalFree   ( hfsChunk );

			return (BOOL)*szFileName ;

			break;
#ifdef PARAMETER_VALIDATION

		default:

			DEBUGOUT ("COMDLG_ComDlgGetFileName: Invalid wAction");
			return FALSE;

#endif

	}
}

//*************************************************************************
//
//
//
//*************************************************************************

DLGPROC COMDLG_OpenFileHook ( HWND hDlg, unsigned msg, WPARAM wParam, LONG lParam )
{
	switch ( msg ) {
		case WM_COMMAND:

			return COMDLG_OpenFile_WM_COMMAND ( hDlg, msg, wParam, lParam );

		default:

			return FALSE;
	}
}

//*******************************************************
//
// This is where the techniques for using common dialogs
// are demonstrated:
//
// 1. Changing the drive/directory programatically in a
//    File open common dialog
//
// 2. Rebuilding the information in the "List Files of Type"
//    combobox.
//
// 3. Changing the selection of the "List Files of Type"
//    combobox.
//
//*******************************************************

DLGPROC COMDLG_OpenFile_WM_COMMAND ( HWND hDlg, unsigned msg, WPARAM wParam, LONG lParam )
{
	HWND CRACKER_hWnd;
	WORD CRACKER_wNotification;
	WORD CRACKER_wID;
	CRACKER_wID           = wParam;
	CRACKER_wNotification = HIWORD (lParam );
	CRACKER_hWnd          = LOWORD (lParam );

	switch ( CRACKER_wID ) {
		case IDD_WINDOWS:

			// Change directories and drives to the windows dir
			{
				char szWindowsDir[256];
				GetWindowsDirectory ( szWindowsDir, sizeof(szWindowsDir));
      
				SendDlgItemMessage ( hDlg, edt1, WM_SETREDRAW, FALSE, 0L);
				SetDlgItemText     ( hDlg, edt1, szWindowsDir           );
				SendDlgItemMessage ( hDlg, edt1, WM_SETREDRAW, TRUE,  0L);

				SendMessage ( hDlg, WM_COMMAND, IDOK, MAKELONG ( GetDlgItem(hDlg,IDOK), BN_CLICKED ) );
			}
			break;

		case IDD_TYPES:

			// Rebuild the File Type combobox
			ComDlgFormatFilterString();  // This function has been modified
                                   // to alternate between two filters.
                                   // Check out the code, it just
                                   // loads one of two strings from
                                   // the stringtable.
                                   //
                                   // Your real-life program will
                                   // probably generate this string
                                   // on-the-fly instead of loading
                                   // it from a stringtable anyway.

			RebuildCommDlgFileTypes ( hDlg, szFilenameFilter );

			// Set File Type to first item in list
			SendDlgItemMessage ( hDlg, cmb1, CB_SETCURSEL, 0, 0L);
			SendMessage ( hDlg, WM_COMMAND, cmb1, MAKELONG ( GetDlgItem(hDlg,cmb1), CBN_SELCHANGE ) );
			break;
     
		default:

			break;
	}

	return FALSE;
}

//*************************************************************************
//
// This function fills the "List files of Type" combobox in a dialog
// given the supplied formatting string. The formatting string is
// a list of "doublestrings", where the first string is the human
// readable string, and the second string is the machine readable string.
// There is an exatr terminating zero at the end of the last string.
// 
// The combobox stores the human readable string in the comboboxe's
// listbox, while the index to the machine readable string is stored
// in the extra item data for each listbox item.
//
// Look at this sample string. Since it is not easy to show a 
// null terminator in a text file, we will substitute it with a
// vertical bar (|) for this comment example only:
//
// These numbers are a handy way to show the byte index of the string...
//
//           111111111122222222223333333333444444444455555555555666666666
// 0123456789012345678901234567890123456789012345678901234567890123456789
// ----------------------------------------------------------------------
//           a                 b                                c
// All Files|*.*|Program Files|*.EXE;*.DLL;*.COM|Settings Files|*.INI||
//
//                            ^   ^----Terminator 2 for second string pair
//                            |--------Terminator 1 for second string pair
//
// This string would be reprsented in the combobox'slistbox like this:
//
// String in Listbox       Item Data (via CB_SETITEMDATA)
// ======================================================
// All Files               10 (a)
// Program Files           28 (b)
// Settings Files          61 (c)
//
//***********************************************************************
void RebuildCommDlgFileTypes ( HWND hDlg, LPSTR szFilenameFilter )
{
   HWND  hWndCombo;   // hWnd of the combobox in the File open dlg
   LPSTR szStringPtr; // Floating string pointer
   int   iLen;        // Length of string from start of szFilenameFilter
   int   iIndex;      // Index of item added to combobox
   int   iSel;        // Temporary combo selection storage variable

   // Get the combobox and its selected item
   hWndCombo = GetDlgItem ( hDlg, cmb1); 
   iSel = (int)SendMessage ( hWndCombo, CB_GETCURSEL, 0, 0L );

   // Turn off painting until we are done
   SendMessage ( hWndCombo, WM_SETREDRAW, FALSE, 0L );

   // Nix the current contents
   SendMessage ( hWndCombo, CB_RESETCONTENT, 0, 0L );

   // Start at beginning of szFilenameFilter
   iLen = 0;

   // Calculate the string pointer
   szStringPtr = szFilenameFilter + iLen;

   // Loop through each set of strings
   while (*szStringPtr) { // while there are strings
		// Add the human-readable string to the combobox
		iIndex = (int)SendMessage ( hWndCombo, CB_ADDSTRING, 0, (LONG)(LPSTR)szStringPtr );

		// Add length of current string to total length, add one to skip Terminator 1
		iLen += lstrlen (szStringPtr) + 1;

		// Bump up string pointer to the machine readable string
		szStringPtr = szFilenameFilter + iLen;

		// Add that index to the combobox
		SendMessage ( hWndCombo, CB_SETITEMDATA, (WPARAM)iIndex, (LONG)iLen );

		// Add length of current string to total length, add one to skip Terminator 2
		iLen += lstrlen (szStringPtr) + 1;

		// Bump up string pointer to the next string
		szStringPtr = szFilenameFilter + iLen;
	} // I'll be back!

   // Turn on painting
   SendMessage ( hWndCombo, WM_SETREDRAW, TRUE, 0L );

   // Force repaint
   InvalidateRect ( hWndCombo, NULL, TRUE );

   // Restore selected item
   SendMessage ( hWndCombo, CB_SETCURSEL, iSel, 0L );
}