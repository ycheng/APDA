#include <windows.h>   // Windows
#include "basedefs.h"  // Dave's stuff
#include "base1ui.h"   // Symbols for resources

//===============================================================
//
// Public Function Prototypes (called between code segements)
//
// Preface these functions with the filename that they live in,
// that makes it easier to find them once your program gets
// mondo, and you can quickly recognize far calls in your code.
//
//===============================================================

int     BASE1_ModalDialog ( LPSTR   TemplateName, 
                            FARPROC FunctionName, 
                            LONG    dwParam 
                          );
WINPROC BASE1_WndProc     ( WINDOWS_PARAMS );
DLGPROC BASE1_DlgProc     ( DIALOG_PARAMS  );

//===============================================================
//
// Global Variables. The GLOBAL and GLOBAL CHAR macros expect
// that *one* of your .C files has the INMAIN symbol defined,
// all the other C files should NOT have the INMAIN symbol
// defined.
//
// If you are using precompiled headers, you will need one
// PCH file for the INMAIN definition, and one for the
// non INMAIN definition.
//
//===============================================================

GLOBAL      HANDLE ghInst;
GLOBAL      HWND   ghWnd;
GLOBALCHAR         (szAppName[],"BASE"             );
GLOBALCHAR         (szCaption[],"Tiny Windows App" );
