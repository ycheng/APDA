#include <VCommon.h>
#include <VPdaSDK.h>

#ifdef	LINUX
#include <vxddk.h>
#else
#include <vmsddk.h>
#endif


Boolean RctPtInRectangle (Coord x, Coord y, const RectangleType *rP)
{
	if ( (rP->extent.x == 0) || (rP->extent.y == 0) )
		return	FALSE;
		
	if ( (x>=rP->topLeft.x)&&(y>=rP->topLeft.y)&&
		(x<=(rP->topLeft.x+rP->extent.x))&&
		(y<=(rP->topLeft.y+rP->extent.y)) ) {
		return	TRUE;
	} else {
		return FALSE;
	}
}

void RctSetRectangle (RectangleType *P, Coord left, Coord top, Coord width, Coord height)
{
	P->topLeft.x = left;
	P->topLeft.y = top;
	P->extent.x = width;
	P->extent.y = height;
}
