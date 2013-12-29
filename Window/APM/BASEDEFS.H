#ifdef WIN32
#define WIN_NT
#else
#define WIN_DOS
#endif

#define WM_MYCOMMAND (WM_USER+1000)

#ifdef WIN_DOS
#define WINPROC        long FAR PASCAL
#define MDIPROC        long FAR PASCAL
#define DLGPROC        BOOL FAR PASCAL
#define ENUMPROC       BOOL FAR PASCAL
#define WINDOWS_PARAMS HWND hWnd, unsigned msg, WPARAM wParam, LONG lParam
#define DIALOG_PARAMS  HWND hDlg, unsigned msg, WPARAM wParam, LONG lParam
#define ENUM_PARAMS    HWND hWnd, LPARAM lParam
#endif

#ifdef WIN_NT
#define WINPROC        long FAR PASCAL
#define MDIPROC        long FAR PASCAL
#define DLGPROC        BOOL FAR PASCAL
#define ENUMPROC       BOOL FAR PASCAL
#define WINDOWS_PARAMS HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
#define DIALOG_PARAMS  HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam
#define ENUM_PARAMS    HWND hWnd, LPARAM lParam
#endif

#define CRACKER_VARS           \
  HWND CRACKER_hWnd;           \
  WORD CRACKER_wNotification;  \
  WORD CRACKER_wID;

#ifdef WIN_DOS
#define NOTIFYPARENT(hWndParent,wID,wNotifyCode)                     \
  SendMessage ( hWndParent,                                          \
                WM_COMMAND,                                          \
                wID,                                                 \
                MAKELONG ( GetDlgItem(hWndParent,wID), wNotifyCode ) \
              );
#endif

#ifdef WIN_NT
#define NOTIFYPARENT(hWndParent,wID,wNotifyCode)                     \
  SendMessage ( hWndParent,                                          \
                WM_COMMAND,                                          \
                MAKELONG ( wID, wNotifyCode ),                       \
                GetDlgItem(hWndParent,wID)                           \                      \
              );
#endif

#ifdef WIN_DOS
#define NOTIFYPARENTPOST(hWndParent,wID,wNotifyCode)                 \
  PostMessage ( hWndParent,                                          \
                WM_COMMAND,                                          \
                wID,                                                 \
                MAKELONG ( GetDlgItem(hWndParent,wID), wNotifyCode ) \
              );
#endif

#ifdef WIN_NT
#define NOTIFYPARENTPOST(hWndParent,wID,wNotifyCode)                 \
  PostMessage ( hWndParent,                                          \
                WM_COMMAND,                                          \
                MAKELONG ( wID, wNotifyCode ),                       \
                GetDlgItem(hWndParent,wID)                           \                      \
              );
#endif


#ifdef WIN_DOS
#define CRACK_MESSAGEsc                      \
  {                                          \
  CRACKER_wID           = wParam;            \
  CRACKER_wNotification = HIWORD (lParam );  \
  CRACKER_hWnd          = LOWORD (lParam );  \
  }                                      
#endif

#ifdef WIN_NT
#define CRACK_MESSAGEsc                      \
  {                                          \
  CRACKER_wID           = LOWORD (wParam );  \
  CRACKER_wNotification = HIWORD (wParam );  \
  CRACKER_hWnd          = (HWND)lParam;      \
  }
#endif

#ifdef WIN_DOS
#define HICHUNK(lParam) HIWORD(lParam)
#define LOCHUNK(lParam) LOWORD(lParam)
#define MAKECHUNKsc(lParam,lo,hi) lParam=MAKELONG(lo,hi);
#define HILOCHUNK DWORD
#define HILOCHUNKPARAM(lParam) (lParam)
#endif

#ifdef WIN_NT

typedef struct tagHILOCHUNK
  {
  LONG hi;
  LONG lo;
  }
HILOCHUNK;

typedef HILOCHUNK FAR *LPHILOCHUNK;

#define HICHUNK(lParam) (((LPHILOCHUNK)(lParam))->hi)
#define LOCHUNK(lParam) (((LPHILOCHUNK)(lParam))->lo)
#define MAKECHUNKsc(lParam,low,high) {lParam.lo=(LONG)(low);lParam.hi=(LONG)(high);}
#define HILOCHUNKPARAM(lParam) ((LONG)(&lParam))
#endif

// MACROS FOR VARAIBLE DECLARATIONS 

#ifndef INMAIN
#define GLOBAL extern
#define GLOBALCHAR(p1,p2) char p1;
#endif
#ifdef INMAIN
#define GLOBAL
#define GLOBALCHAR(p1,p2) char p1 = p2;
#endif

// Endian Independant storage facilities

typedef struct diWORDtag
  {
  BYTE   bLo;
  BYTE   bHi;
  }
diWORD;
typedef struct diLONGtag
  {
  diWORD diwLo;
  diWORD diwHi;
  }
diLONG;

#define GETWORD(diWord) ((diWord).bHi*256+(diWord).bLo)
#define GETLONG(diLong) (MAKELONG(GETWORD(diLong.diwLo),GETWORD(diLong.diwHi)))

#define MAKEdiWORD(diWord,wWord)            \
  {                                         \
  (diWord).bHi = (wWord)/256;                   \
  (diWord).bLo = (wWord)%256;                   \
  }                              

#define MAKEdiLONG(diLong,lLong)            \
  {                                         \
  MAKEdiWORD((diLong).diwHi, HIWORD(lLong));  \
  MAKEdiWORD((diLong).diwLo, LOWORD(lLong));  \
  }


