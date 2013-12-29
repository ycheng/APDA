/****************************************************************************
*                                                                           *
*                             LOADSTRING CONSTANTS                          *
*                                                                           *
*                         MAKE SURE THESE DONT CONFLICT                     *
*                             WITH YOUR APPLICATION                         *
*                                                                           *
****************************************************************************/

#define IDS_DIALOGFAILURE     1
#define IDS_STRUCTSIZE        2
#define IDS_INITIALIZATION    3
#define IDS_NOTEMPLATE        4
#define IDS_NOHINSTANCE       5
#define IDS_LOADSTRFAILURE    6
#define IDS_FINDRESFAILURE    7
#define IDS_LOADRESFAILURE    8
#define IDS_LOCKRESFAILURE    9
#define IDS_MEMALLOCFAILURE  10
#define IDS_MEMLOCKFAILURE   11
#define IDS_NOHOOK           12
#define IDS_SETUPFAILURE     13
#define IDS_PARSEFAILURE     14
#define IDS_RETDEFFAILURE    15
#define IDS_LOADDRVFAILURE   16
#define IDS_GETDEVMODEFAIL   17
#define IDS_INITFAILURE      18
#define IDS_NODEVICES        19
#define IDS_NODEFAULTPRN     20
#define IDS_DNDMMISMATCH     21
#define IDS_CREATEICFAILURE  22
#define IDS_PRINTERNOTFOUND  23
#define IDS_NOFONTS          24
#define IDS_SUBCLASSFAILURE  25
#define IDS_INVALIDFILENAME  26
#define IDS_BUFFERTOOSMALL   27

#define IDS_SEARCHUP         28
#define IDS_SEARCHDOWN       29
#define IDS_CASESENSITIVE    30
#define IDS_IGNORECASE       31
#define IDS_WHOLEWORD        32
#define IDS_WHOLEANDSUB      33

#define IDS_FILTERSTRING     34
#define IDS_FILTERSTRING1    35

/****************************************************************************
*                                                                           *
*                             OTHER CONSTANTS                               *
*                                                                           *
****************************************************************************/

#define IDC_OPENFILE            1
#define IDC_SAVEFILE            2
#define IDC_FIND                3
#define IDC_FINDREPLACE         4
#define IDC_COLORS              5
#define IDC_FONT                6
#define IDC_PRINTDLG            7

#define IDC_ALLOCFAIL           1
#define IDC_LOCKFAIL            2
#define IDC_LOADSTRINGFAIL      3

#define IDC_HELPMSG          2000
#define IDC_FINDREPLACEMSG   2001

#define MAXFILTERBUF          256
#define MAXFILENAMELEN        256
#define MAXFILETITLELEN       256
#define MAXFINDWHATLEN         64
#define MAXREPLACEWITHLEN      64
#define MAXFINDDIRECTIONLEN    24
#define MAXFINDCASELEN         24
#define MAXFINDWORDLEN         26

/****************************************************************************
*                                                                           *
*                          COMMOND DIALOG NOTIFICATION CODES                *
*                                                                           *
****************************************************************************/

#define CDN_FIND             1
#define CDN_FINDREPLACE      2


/****************************************************************************
*                                                                           *
*                          FILE OPEN STRUCTURE                              *
*                                                                           *
****************************************************************************/
typedef struct tagFOCHUNK
   {
      OPENFILENAME of;
      char szFile[MAXFILENAMELEN];
      char szFileTitle[MAXFILETITLELEN];
   }
FOCHUNK;

typedef FOCHUNK FAR *LPFOCHUNK;
typedef FOCHUNK FAR *LPFSCHUNK; 


/****************************************************************************
*                                                                           *
*                          COLORS STRUCTURE                                 *
*                                                                           *
****************************************************************************/
typedef struct tagCOLORSCHUNK
   {
      CHOOSECOLOR chsclr;
      DWORD dwColor;                    
      DWORD dwCustClrs[16];       
   }
COLORSCHUNK;

typedef COLORSCHUNK FAR *LPCOLORSCHUNK; 


/****************************************************************************
*                                                                           *
*                          FIND STRUCTURE                                   *
*                                                                           *
****************************************************************************/

typedef struct tagFINDREPLACECHUNK
   {
      FINDREPLACE fr;
      char szFindWhat[MAXFINDWHATLEN];
      char szReplaceWith[MAXREPLACEWITHLEN];
   }
FINDREPLACECHUNK;

typedef FINDREPLACECHUNK FAR *LPFINDREPLACECHUNK; 


void FAR ERROR_ProcessCDError(DWORD dwErrorCode);
void FAR ERROR_ReportError(WORD wErrorType);
