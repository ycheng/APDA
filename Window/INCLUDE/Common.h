#ifndef __COMMON_H__
#define __COMMON_H__

#define _WISIMPORTDLL

#include <VCommon.h>
#include <apidll.h>

#ifndef LINUX
__declspec( dllexport ) DWord PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags);
#endif

#endif // __COMMON_H__
