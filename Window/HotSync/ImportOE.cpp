// ImportOE.cpp: Implementation of CIMPORTOE.
// Copyright (C) 2000 Jerry Chu
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MailMessage.h"
#include "ImportOE.h"

#define	kIndexGrowBy		100
#define	kSignatureSize		12
#define	kDontSeek			0xFFFFFFFF
#define	MaxMailNum			100

static char *gSig = 
	"\xCF\xAD\x12\xFE\xC5\xFD\x74\x6F\x66\xE3\xD1\x11";

//char	*InBox = "c:\\Windows\\Application Data\\Identities\\{8C29D50C-BECA-4B3E-BC0B-02032FA051E7}\\Microsoft\\Outlook Express\\收件匣.dbx";
char	*InBox = "寄件匣.dbx";
char	*OutBox = "寄件匣2.dbx";

CIMPORTOE::CIMPORTOE()
{
	VerifyMailInBox();
	VerifyMailOutBox();
}

CIMPORTOE::~CIMPORTOE()
{
	pFile.Close();
	oFile.Close();
}

bool CIMPORTOE::VerifyMailInBox()
{
	char		sig[kSignatureSize];
	CFileException e;

	if( !pFile.Open( InBox, CFile::modeRead, &e ) ) {
		return (false);
	}

	if (!pFile.Read(sig, kSignatureSize)) {
		return (false);
	}
	
	bool	result = true;

	for (int i = 0; (i < kSignatureSize) && result; i++) {
		if (sig[i] != gSig[i]) {
			result = false;
		}
	}
	
	long	offset = 0x24C1;				
	char	storeName[14];

	if (!ReadBytes(storeName, offset, 12)) {
		result = false;
	}

	storeName[12] = 0;
	
	if (strcmp( "LocalStore", storeName))
		result = false;

	return result ;
}

bool CIMPORTOE::VerifyMailOutBox()
{
	char		sig[kSignatureSize];
	CFileException e;

	if( !oFile.Open( OutBox, CFile::modeRead, &e ) ) {
		return (false);
	}

	if (!oFile.Read(sig, kSignatureSize)) {
		return (false);
	}
	
	bool	result = true;

	for (int i = 0; (i < kSignatureSize) && result; i++) {
		if (sig[i] != gSig[i]) {
			result = false;
		}
	}
	
	long	offset = 0x24C1;				
	char	storeName[14];

	if (!oFile.Seek(offset, CFile::begin)) {
		return (false);
	}

	if (!oFile.Read(storeName, 12)) {
		result = false;
	}

	storeName[12] = 0;
	
	if (strcmp( "LocalStore", storeName))
		result = false;

	oFile.Close();

	if( !oFile.Open( OutBox, CFile::modeWrite, &e ) ) {
		return (false);
	}

	return result ;
}

bool CIMPORTOE::ReadIndex(long **ppIndex, long *pSize)
{
	*ppIndex = NULL;
	*pSize = 0;
	PRUint32Array array;

	long	offset = 0x00e4;				
	long	indexStart = 0;

	if (!ReadBytes(&indexStart,offset,4)) {
		return (false);
	}

	array.count = 0;
	array.alloc = kIndexGrowBy;
	array.pIndex = new long[kIndexGrowBy];
	
	long next = ReadMsgIndex( &pFile, indexStart, &array);
	while (next) {
		next = ReadMsgIndex( &pFile, next, &array);
	}

	if (array.count) {
		*pSize = array.count;
		*ppIndex = array.pIndex;
		return (true);
	}		
	
	pFile.Close();
	return (false);
}

long CIMPORTOE::ReadMsgIndex( CFile *pFile, long offset, PRUint32Array *pArray)
{
	// Record is:
		// 4 byte marker
		// 4 byte unknown
		// 4 byte nextSubIndex
		// 4 byte (parentIndex?)
		// 2 bytes unknown
		// 1 byte length - # of entries in this record
		// 1 byte unknown
		// 4 byte unknown
		// length records consisting of 3 longs
			//	1 - pointer to record
			//	2 - child index pointer
			//	3 - number of records in child

	long	marker;

	if (!ReadBytes(&marker, offset, 4)) {
		return (0);
	}

	if (marker != offset)
		return( 0);
	
	long	vals[3];

	if (!ReadBytes(vals, offset+4, 12)) {
		return (0);
	}
	

	char	len[4];
	if (!ReadBytes(len, offset+16, 4)) {
		return (0);
	}
	
	long	cnt = (long) len[1];

	cnt *= 3;
	long	*pData = new long[cnt];
	
	if (!ReadBytes(pData, offset+24, cnt*4)) {
		delete [] pData;
		return( 0);
	}	

	long	next;
	long	indexOffset;
	long *	pRecord = pData;
	long *	pNewIndex;

	for (char i = 0; i < (char)len[1]; i++, pRecord += 3) {
		indexOffset = pRecord[0];
	
		if (pArray->count >= pArray->alloc) {
			pNewIndex = new long[ pArray->alloc + kIndexGrowBy];
			memcpy( pNewIndex, pArray->pIndex, (pArray->alloc * 4));
			(pArray->alloc) += kIndexGrowBy;		
			delete [] pArray->pIndex;
			pArray->pIndex = pNewIndex;
		}
		
		/* 
			We could do some checking here if we wanted - 
			make sure the index is within the file,
			make sure there isn't a duplicate index, etc.
		*/

		pArray->pIndex[pArray->count] = indexOffset;
		(pArray->count)++;
		
	
		next = pRecord[1];
		if (next)
			while ((next = ReadMsgIndex( pFile, next, pArray)) != 0);
	}
	delete pData;

	// return the pointer to the next subIndex
	return( vals[1]);
}

/*
	A message index record consists of:
		4 byte marker - matches record offset
		4 bytes size - size of data after this header
		2 bytes unknown
		1 bytes - number of attributes
		1 byte unknown
		Each attribute is a 4 byte value with the 1st byte being the tag
		and the remaing 3 bytes being data.  The data is either a direct
		offset of an offset within the message index that points to the
		data for the tag.

		Current known tags are:
			0x02 - a time value
			0x04 - text offset pointer, the data is the offset after the attribute
				of a 4 byte pointer to the message text
			0x05 - offset to truncated subject
			0x08 - offste to subject
			0x0D - offset to from
			0x0E - offset to from addresses
			0x13 - offset to to name
			0x45 - offset to to address
			0x80 - msgId
			0x84 - direct text offset, direct pointer to message text
*/

#define	kMailboxBufferSize	0x4000
const char *m_pFromLineSep = "From ????@???? 1 Jan 1965 00:00:00\x0D\x0A";

long CIMPORTOE::ImportMailBox(CMailMessage msg)
{
	char *		pBuffer = new char[kMailboxBufferSize];
	long *	pIndex;
	long	indexSize;
	int		msgCount = 0;
	
	if (!ReadIndex( &pIndex, &indexSize)) {
/*
		IMPORT_LOG1( "No messages found in mailbox: %S\n", name.GetUnicode());
		inFile->CloseStream();
		pDestination->CloseStream();
		return ( NS_OK);
*/
	}	

	ConvertIndex(pIndex, indexSize);

	long	block[4];
	int		sepLen = (int) strlen( m_pFromLineSep);

	/*
		Each block is:
			marker - matches file offset
			block length
			text length in block
			pointer to next block. (0 if end)

		So what we do for each message is:
			Read the first block
			Write out the From message separator if the message doesn't already
				start with one.
			Write out all subsequent blocks of text keeping track of the last
				2 bytes written of the message.
			if the last 2 bytes aren't and end of line then write one out before
				proceeding to the next message.
	*/
	
	long	didBytes = 0;
	char	last2[2] = {0, 0};
	long	next;

	for (long i = 0; (i < indexSize); i++) {
		if (pIndex[i]) {
			if (ReadBytes( block, pIndex[i], 16) && 
						(block[0] == pIndex[i]) &&
						(block[2] < kMailboxBufferSize) &&
						(ReadBytes( pBuffer, kDontSeek, block[2]))) {

				didBytes += block[2];

				next = block[3];
				while (next) {
					if (ReadBytes( block, next, 16) &&
						(block[0] == next) &&
						(block[2] < kMailboxBufferSize) &&
						(ReadBytes( pBuffer, kDontSeek, block[2]))) {
						next = block[3];
					}
					else {
						next = 0;
						last2[0] = 13;
						last2[1] = 10;
					}
				}
				if ((last2[0] != 13) || (last2[1] != 10)) {
					last2[0] = 13;
					last2[1] = 10;
				}

				msgCount++;
/*
				if (pCount)
					*pCount = msgCount;
				if (pBytesDone)
					*pBytesDone = didBytes;
*/
			}
			else {
				// Error reading message, should this be logged???
			}			
		}
	}

	delete [] pBuffer;
	return 1 ;
}

long CIMPORTOE::GetMail(CMailMessage *msg,long *pIndex,long rIndex)
{
	char *		pBuffer = new char[kMailboxBufferSize];
	long	block[4];
	int		sepLen = (int) strlen( m_pFromLineSep);

	char 	tBuffer[1024];
	BYTE	recordHead[12];
	long	marker;
	long	recordSize;
	long	numAttrs;
	long	offset;
	long	attrIndex;
	long	attrOffset;
	BYTE	tag;
	long	tagData;
	long	subjectoffset;
	long	fromoffset;
	long	fromaddoffset;
	long	nameoffset;
	long	toaddoffset;
	long	count;

	offset = 0;
	if (ReadBytes(recordHead, pIndex[rIndex], 12)) {
		memcpy( &marker, recordHead, 4);
		memcpy( &recordSize, recordHead + 4, 4);
		numAttrs = (long) recordHead[10];
		if ((marker == pIndex[rIndex]) && (recordSize < kMailboxBufferSize) && ((numAttrs * 4) <= recordSize)) {
			if (ReadBytes(pBuffer, kDontSeek, recordSize)) {
				attrOffset = 0;
				for (attrIndex = 0; attrIndex < numAttrs; attrIndex++, attrOffset += 4) {
					tag = (BYTE) pBuffer[attrOffset];
					count = 0;
					if (tag == (BYTE) 0x08) {
						tagData = 0;
						memcpy( &tagData, pBuffer + attrOffset + 1, 3);
						subjectoffset = tagData+numAttrs*4;
						while (*(pBuffer+subjectoffset+count)){
							tBuffer[count] = *(pBuffer+subjectoffset+count) ;
							count++ ;
						}
						tBuffer[count] = 0;
						msg->m_sSubject = tBuffer;
					}
					else if (tag == (BYTE) 0x0D) {
						tagData = 0;
						memcpy( &tagData, pBuffer + attrOffset + 1, 3);
						fromoffset = tagData+numAttrs*4;
						while (*(pBuffer+fromoffset+count)){
							tBuffer[count] = *(pBuffer+fromoffset+count) ;
							count++ ;
						}
						tBuffer[count] = 0;
						msg->m_sFrom = tBuffer;
					}
					else if (tag == (BYTE) 0x0E) {
						tagData = 0;
						memcpy( &tagData, pBuffer + attrOffset + 1, 3);
						fromaddoffset = tagData+numAttrs*4;
						while (*(pBuffer+fromaddoffset+count)){
							tBuffer[count] = *(pBuffer+fromaddoffset+count) ;
							count++ ;
						}
						tBuffer[count] = 0;
						msg->m_sFromAddress = tBuffer;
					}
					else if (tag == (BYTE) 0x13) {
						tagData = 0;
						memcpy( &tagData, pBuffer + attrOffset + 1, 3);
						nameoffset = tagData+numAttrs*4;
						while (*(pBuffer+nameoffset+count)){
							tBuffer[count] = *(pBuffer+nameoffset+count) ;
							count++ ;
						}
						tBuffer[count] = 0;
						msg->m_sTo = tBuffer;
					}
					else if (tag == (BYTE) 0x45) {
						tagData = 0;
						memcpy( &tagData, pBuffer + attrOffset + 1, 3);
						toaddoffset = tagData+numAttrs*4;
						while (*(pBuffer+toaddoffset+count)){
							tBuffer[count] = *(pBuffer+toaddoffset+count) ;
							count++ ;
						}
						tBuffer[count] = 0;
						msg->m_sToAddress = tBuffer;
					}
				}
			}
		}
	}

	/*
		Each block is:
			marker - matches file offset
			block length
			text length in block
			pointer to next block. (0 if end)

		So what we do for each message is:
			Read the first block
			Write out the From message separator if the message doesn't already
				start with one.
			Write out all subsequent blocks of text keeping track of the last
				2 bytes written of the message.
			if the last 2 bytes aren't and end of line then write one out before
				proceeding to the next message.
	*/
	
	long	didBytes = 0;
	char	last2[2] = {0, 0};
	long	next;
	CString sMsg;
	CString	csBuffer;
	

	if (bIndex[rIndex]) {
		if (ReadBytes( block, bIndex[rIndex], 16) && 
				(block[0] == bIndex[rIndex]) &&
				(block[2] < kMailboxBufferSize) &&
				(ReadBytes( pBuffer, kDontSeek, block[2]))) {

			didBytes += block[2];
			csBuffer = pBuffer;
			sMsg = csBuffer.Left(block[2]) ;

			next = block[3];
			while (next) {
				if (ReadBytes( block, next, 16) &&
					(block[0] == next) &&
					(block[2] < kMailboxBufferSize) &&
					(ReadBytes( pBuffer, kDontSeek, block[2]))) {
					csBuffer = pBuffer;
					sMsg += csBuffer.Left(block[2]) ;
					didBytes += block[2];
					next = block[3];
				}
				else {
					next = 0;
					last2[0] = 13;
					last2[1] = 10;
				}
			}
			if ((last2[0] != 13) || (last2[1] != 10)) {
				last2[0] = 13;
				last2[1] = 10;
			}

		}
		else {
			// Error reading message, should this be logged???
		}			
	}

	int br=sMsg.Find("\r\n\r\n"); //breakpoint between header and body
	msg->m_sHeader=sMsg.Left(br);
	msg->m_sBody=sMsg.Mid(br+4);
	msg->DecodeHeader();
	msg->DecodeBody();
	msg->Decode_ASCII(&msg->m_sFrom);
	msg->Decode_ASCII(&msg->m_sTo);
	msg->Decode_ASCII(&msg->m_sSubject);

	int	Headerlen = msg->m_sHeader.GetLength();
	int	Bodylen = msg->m_sBody.GetLength();
	if ( msg->m_sContentType.Left(9) == "multipart" ) {
		msg->GetBoundaryString();
		msg->ResolveMultiPart(&msg->m_sBody);
	} else {
		msg->ResolveBody(&msg->m_sBody);
	}

	delete [] pBuffer;
	return didBytes ;
}

long CIMPORTOE::ReadBytes(void *pBuffer, long offset, long bytes)
{
	if (offset != kDontSeek) {
		if (!pFile.Seek(offset, CFile::begin)) {
			return (false);
		}
	}
		
	if (!pFile.Read(pBuffer, bytes)) {
		return (false);
	}

	return	(true);
}

void CIMPORTOE::ConvertIndex(long *pIndex, long size)
{
	// for each index record, get the actual message offset!  If there is a problem
	// just record the message offset as 0 and the message reading code
	// can log that error information.

	char *		pBuffer = new char[kMailboxBufferSize];
	BYTE	recordHead[12];
	long	marker;
	long	recordSize;
	long	numAttrs;
	long	offset;
	long	attrIndex;
	long	attrOffset;
	BYTE	tag;
	long	tagData;

	for (long i = 0; i < size; i++) {
		offset = 0;
		if (ReadBytes(recordHead, pIndex[i], 12)) {
			memcpy( &marker, recordHead, 4);
			memcpy( &recordSize, recordHead + 4, 4);
			numAttrs = (long) recordHead[10];
			if ((marker == pIndex[i]) && (recordSize < kMailboxBufferSize) && ((numAttrs * 4) <= recordSize)) {
				if (ReadBytes(pBuffer, kDontSeek, recordSize)) {
					attrOffset = 0;
					for (attrIndex = 0; attrIndex < numAttrs; attrIndex++, attrOffset += 4) {
						tag = (BYTE) pBuffer[attrOffset];
						if (tag == (BYTE) 0x84) {
							tagData = 0;
							memcpy( &tagData, pBuffer + attrOffset + 1, 3);
							offset = tagData;
							break;
						}
						else if (tag == (BYTE) 0x04) {
							tagData = 0;
							memcpy( &tagData, pBuffer + attrOffset + 1, 3);
							if (((numAttrs * 4) + tagData + 4) <= recordSize)
								memcpy( &offset, pBuffer + (numAttrs * 4) + tagData, 4);
						}
					}
				}
			}
		}
		bIndex[i] = offset;
	}

	delete [] pBuffer ;
}

int	From_startpos, To_startpos, Subject_startpos, Date_startpos;
CString	m_sFrom, m_sTo, m_sSubject;

void CIMPORTOE::GetOffset(char *buffer, int size)
{
	CString	sMsg = buffer;
	CString sSearchFor;
	int		endpos;

	//We can assume that there's a CR/LF before each of the tags, as the servers insert
	//Received: lines on top of the mail while transporting the mail
	sSearchFor="\r\nFrom: ";
	From_startpos=sMsg.Find(sSearchFor);
	if (From_startpos<0)	From_startpos = 0 ;
	endpos=sMsg.Mid(From_startpos+sSearchFor.GetLength()).Find("\r\n");
	m_sFrom=sMsg.Mid(From_startpos+sSearchFor.GetLength(),endpos);

	sSearchFor="\r\nTo: ";
	To_startpos=sMsg.Find(sSearchFor);
	if (To_startpos<0)	To_startpos = 0 ;
	endpos=sMsg.Mid(To_startpos+sSearchFor.GetLength()).Find("\r\n");
	m_sTo=sMsg.Mid(To_startpos+sSearchFor.GetLength(),endpos);

	sSearchFor="\r\nSubject: ";
	Subject_startpos=sMsg.Find(sSearchFor);
	if (Subject_startpos<0)	Subject_startpos = 0 ;
	endpos=sMsg.Mid(Subject_startpos+sSearchFor.GetLength()).Find("\r\n");
	m_sSubject=sMsg.Mid(Subject_startpos+sSearchFor.GetLength(),endpos);

	sSearchFor="\r\nDate: ";
	Date_startpos=sMsg.Find(sSearchFor);
	if (Date_startpos<0)	Date_startpos = 0 ;
}

long CIMPORTOE::SendMail()
{
	CFile	fp;
	CFileException e;
	int		filesize;
	int		offset ;
	int		index[10];
	char	recordHeader[12];
	char	buffer[1024];
	char	val[4];
	int		numAttrs, attrOffset=0;
	char *		pBuffer = new char[1*4];
	long	tagData;

	if( !fp.Open( "test.eml", CFile::modeRead, &e ) ) {
		return (false);
	}

	filesize = fp.Seek(0, CFile::end);
	fp.Seek(0, CFile::begin);
	fp.Read(buffer, filesize);

//	GetIndex(buffer,pIndex);

	offset = oFile.Seek(0, CFile::end);
	index[0] = offset;
	memcpy(recordHeader, &offset, 4);
	memcpy(recordHeader+4, &filesize, 4);

	GetOffset(buffer,filesize);
// tag record count
	val[0] = 0;
	val[1] = 0;
	numAttrs = val[2] = 1;
	val[3] = 0;
	memcpy(recordHeader+8, val, 4);

//	memset(recordHeader+8, 0, 4);
	oFile.Write(recordHeader,12);

	// must put tag record here
	// tag style is tag (1byte)
	/*
		0x02 - a time value
		0x04 - text offset pointer, the data is the offset after the attribute
				of a 4 byte pointer to the message text
		0x05 - offset to truncated subject
		0x08 - offste to subject
		0x0D - offset to from
		0x0E - offset to from addresses
		0x13 - offset to to name
		0x45 - offset to to address
		0x80 - msgId
		0x84 - direct text offset, direct pointer to message text
	*/
/*
	pBuffer[attrOffset] = (BYTE) 0x08;
	tagData = Subject_startpos+numAttrs*4;
	memcpy( pBuffer + attrOffset + 1, &tagData, 3);
	numAttrs--;
	attrOffset += 4;

	pBuffer[attrOffset] = (BYTE) 0x0D;
	tagData = From_startpos+numAttrs*4;
	memcpy( pBuffer + attrOffset + 1, &tagData, 3);
	numAttrs--;
	attrOffset += 4;

	pBuffer[attrOffset] = (BYTE) 0x45;
	tagData = To_startpos+numAttrs*4;
	memcpy( pBuffer + attrOffset + 1, &tagData, 3);
	numAttrs--;
	attrOffset += 4;
*/
	pBuffer[attrOffset] = (BYTE) 0x84;
	tagData = offset + numAttrs*4 +12;
	memcpy( pBuffer + attrOffset + 1, &tagData, 3);
	numAttrs--;
	attrOffset += 4;

	oFile.Write(pBuffer,sizeof(pBuffer));
	oFile.Write(&tagData,4);
	tagData = 0;
	oFile.Write(&tagData,4);
	oFile.Write(&filesize,4);
	oFile.Write(&tagData,4);
	oFile.Write(buffer,filesize);

	offset = oFile.Seek(0, CFile::end);

	oFile.Write(&offset,4);
	memset(recordHeader, 0, 12);
	oFile.Write(recordHeader,12);

	val[0] = 0;
	val[1] = 1;
	val[2] = 0;
	val[3] = 0;
	memcpy(recordHeader, val, 4);
	oFile.Write(recordHeader,8);
	memcpy(recordHeader, &index[0], 4);
	oFile.Write(recordHeader,12);
	oFile.Seek(0xe4, CFile::begin);
	oFile.Write(&offset, 4);

	fp.Close();

	return	filesize;
}

