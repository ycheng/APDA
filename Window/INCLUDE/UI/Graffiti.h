#ifndef __GRAFFITI_H__
#define __GRAFFITI_H__


#define	glfCapsLock		0
#define	glfNumLock		1


typedef struct GrfAttrType {
	UInt16		enabled			:1;		// set if part of ui 
	UInt16		sysCapsLock		:1;
	UInt16		sysNumLock		:1;
	UInt16		sysUpperShift	:1;
} GrfAttrType;

typedef struct GrfStateType {
	GrfAttrType	attr;
	UInt16		sysTempShift;
	PointType	pos;
} GrfStateType;



#endif // __GRAFFITI_H__
