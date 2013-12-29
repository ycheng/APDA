#ifndef __stdarg_h
#define __stdarg_h

typedef char * va_list;		// from <va_list.h>

#define __va_start(parm)	(va_list) (&parm + 1)

#define va_start(ap, parm)	ap = __va_start(parm)
#define va_end(ap)


#endif  /* !__stdarg_h */