#ifndef __UNIXSTDIO_H__
#define __UNIXSTDIO_H__


#include "unix_stdarg.h"
#include "Netinet_in.h"


#define		sprintf				StrPrintF
#define		vsprintf(x,y,z)	StrVPrintF(x,(const CharPtr)y,z)


#endif /*!__UNIXSTDIO_H__*/
