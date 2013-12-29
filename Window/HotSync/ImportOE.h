// POP3.h: Interface for CPOP3.
// In adaption of Wes Clyburn's CSMTP class.
// Copyright (C) 1998 Michael Krebs
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTOE_H__CFFD2FBB_859A_11D2_A529_444553540000__INCLUDED_)
#define AFX_IMPORTOE_H__CFFD2FBB_859A_11D2_A529_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIMPORTOE
{
public:
	CIMPORTOE ();
	virtual ~CIMPORTOE();
	
	long ImportMailBox(CMailMessage msg);
	bool ReadIndex(long **ppIndex, long *pSize);
	void ConvertIndex(long *pIndex, long size);
	long GetMail(CMailMessage *msg,long *pIndex,long indexSize);
	long SendMail();
private:
	typedef struct {
		long *	pIndex;
		long	count;
		long	alloc;
	} PRUint32Array;

	CFile	pFile;
	CFile	oFile;
	long	bIndex[500];

	bool VerifyMailInBox();
	bool VerifyMailOutBox();
	long ReadMsgIndex( CFile *file, long offset, PRUint32Array *pArray);
	long ReadBytes(void *pBuffer, long offset, long bytes);
	void GetOffset(char *buffer, int size);
protected:

};

#endif // !defined(AFX_IMPORTOE_H__CFFD2FBB_859A_11D2_A529_444553540000__INCLUDED_)
