#ifndef __stdlib_h
#define __stdlib_h

// The following macros are only included if we're building without the
//  help of the standard ANSI C library, i.e. Native Pilot code only.
// Essentially, if you include <stdlib.h> above this header, this stuff
//  does not get used.
#define		malloc(x)			MemPtrNew(x)
#define		calloc(x,y)			MemCalloc(x,y)
#define		realloc(x,y)		MemRealloc(x,y)
#define		free(x)				MemPtrFree(x)
#define		atoi(x)				StrAToI(x)
#define		atol(x)				StrAToI(x)

#endif  /* !__stdlib_h */