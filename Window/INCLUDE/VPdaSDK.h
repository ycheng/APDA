#ifndef __VPDASDK_H__
#define __VPDASDK_H__

#include <UI/helvr10.h>


#define	KEYWORD					1
#define	PARAMETER				0

// Global variable for O.S.
extern MWCFONT		*currentFont;
extern FormType	*ActiveForm;
extern UInt16		ActiveFormID;
extern Int16		ActiveObjIndex;
extern Char			*GlobalText;
extern Int32		CharWidth[255];
extern UInt16		curCardNo;
extern EventType	*CurEvent;
extern DmOpenRef	currentDBP;
extern pen_point	*currentPnt;
extern UInt16		formCount;
extern FormType	**formPtr;	// pointer to all the form.
extern UInt8		grfInputState;
extern point_list	*lpts;
extern UInt16		MenuCount;
extern char			PDBFilename[32];
extern char			*RCPFileName;


// Global function for O.S.
extern void		Finalize_recorder ();
extern void		FldDelete (FieldType *fldP, UInt16 start, UInt16 end);
extern void		FldDrawField (FieldType *fldP);
extern FormObjListType FrmGetObjectPtrById(UInt16 id);
extern void		*FrmGetObjectPtr (const FormType *formP, UInt16 objIndex);
extern Boolean GetWord (char *word, char *buffer, int *index, int length, Boolean beKeyword);
extern void		hwAddPoint (int x, int y);
extern void		Initialize_recorder (Widget gw);
extern Char		hwRecognizeStart (UInt8 grfInputState);
extern Boolean	ParseRCP(char *buffer, int length);
extern int		ParseInclude(char *buffer, int length);
extern Char *StrIToA(Char *s, Int32 i);
extern void		TblDrawTable (TableType *tableP);


extern void		VAppendStr (Char *str, WChar wchar);
extern void		VCategorySetName (DmOpenRef dbP, UInt16 index, const char *name);
extern void		VClearControl (ControlType *controlP);
extern int		VCloseDatabaseFile (DmOpenRef dbP);
extern void		VCopyFile (void *dstfp, void *rscfp);
extern UInt32	VDatabaseSize (DmOpenRef dbP);
extern UInt32	VDataSize (DmOpenRef dbP);
extern void		VDeleteRecord (DmOpenRef dbP, UInt16 index);
extern void		VDestroyMenuLink ();
extern void		VDrawControl (FormObjectKind type, const void *controlP, int mode);
extern void		VDrawTable ( UInt16 x, UInt16 y, TableItemPtr item, Coord width, Coord height);
extern void		*VFileOpen (char *filename, UInt32 type, UInt32 creator, UInt32 mode);
extern UInt16	VGetCategory (DmOpenRef dbP, UInt16 index);
extern Boolean VGetCategoryName (DmOpenRef dbP, UInt16 index, void *srcP);
extern void		VGetRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset);
extern UInt32	VGetRecordNo (DmOpenRef dbP, UInt16 index);
extern void		*VLoadDatabaseFile (char *filename, UInt32 type, UInt32 creator, Boolean CreateFlag);
extern short	VLoadResource (char *filename);
extern void		*VNewRecord (DmOpenRef dbP, UInt16 *atP, UInt32 size);
extern UInt16	VNumRecords (DmOpenRef dbP);;
extern void		VPDAToSysRect(RectangleType *dstRect, const RectangleType *srcRect);
extern void		VPDAToSysPoint(PointType *dstPoint, const PointType *srcPoint);
extern void		VRedrawControl (const FormObjListType controlP);
extern Int16	VReleaseRecord ();
extern void		VRemoveTempFile ();
extern void		*VResizeRecord (DmOpenRef dbP, UInt16 index, UInt32 size);
extern Err		VSetCategory (DmOpenRef dbP, UInt16 index, UInt16 category);
extern void		VSetCheckBox(const ControlType *ctlP, Boolean style);
extern void		VSetQuit(Boolean beQuit);
extern Err		VSetRecordNo (DmOpenRef dbP, UInt16 index, UInt32 RecordNo);
extern void		VWriteCategory (DmOpenRef dbP, UInt16 index, const void *srcP, UInt32 RecordSize);
extern Int16	VWriteRecord (DmOpenRef dbP, UInt16 index, UInt32 recOffset, const void *srcP, UInt32 RecordSize);

extern void		WCategoryRelease ();



#endif	// __VPDASDK_H__
