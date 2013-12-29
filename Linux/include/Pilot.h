#ifndef __PALMOS_H__
#define __PALMOS_H__

#include <VCommon.h>
#include <apidll.h>

#ifndef LINUX
__declspec( dllexport ) DWord PilotMain (Word cmd, Ptr cmdPBP, Word launchFlags);
#endif

#endif // __PALMOS_H__
