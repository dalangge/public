#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BHXml.h"

CBHXml::CBHXml(void)
{
	m_nBufSize = 256*16;
	m_nPos = 0;
	m_nStatus = 0;
	m_nLayer = 0;
	m_pBuf = (char *)malloc(m_nBufSize);

	for(int i=0; i<MAX_LAYER; i++)
	{
		m_pElem[i] = (char *)malloc(MAX_ELEM_SIZE);
	}
}

CBHXml::~CBHXml(void)
{
	if(NULL != m_pBuf)
	{
		free(m_pBuf);
	}

	for(int i=0; i<MAX_LAYER; i++)
	{
		if(NULL != m_pElem[i])
		{
			free(m_pElem[i]);
		}
	}
}

bool CBHXml::Reserve(int nBufSize)
{
    return SetBuffer(nBufSize);
}

bool CBHXml::SetBuffer(int nBufSize)
{
	if(nBufSize < m_nBufSize)
	{
		return false;
	}

	char *pBuf = (char *)malloc(nBufSize);

	if(NULL != m_pBuf)
	{
		memcpy(pBuf, m_pBuf, m_nPos);
		free(m_pBuf);
	}

	m_pBuf = pBuf;
	m_nBufSize = nBufSize;
	return true;
}


bool CBHXml::SetDoc(const char *pDoc)
{
	int nLen = ( int )strlen(pDoc);
	int nBufSize = m_nBufSize;
	while(nLen > nBufSize)
	{
		nBufSize <<= 1;
	}

	if(SetBuffer(nBufSize) == false)
	{
		return false;
	}

	memcpy(m_pBuf, pDoc, nLen);
	m_nPos = nLen;

	return true;
}

char *CBHXml::GetDoc()
{

	if(STATUS_ELEM_ADD == m_nStatus)
	{
		m_pBuf[m_nPos] = ' ';
		m_pBuf[m_nPos + 1] = '/';
		m_pBuf[m_nPos + 2] = '>';
		m_pBuf[m_nPos + 3] = '\n';
		m_nPos += 4;
		m_nStatus = STATUS_ELEM_FINISH;
	}

	while(m_nLayer)
	{
		m_nLayer--;
		int nLen = (int)strlen(m_pElem[m_nLayer]);
		m_pBuf[m_nPos] = '<';
		m_pBuf[m_nPos + 1] = '/';
		m_nPos += 2;
		memcpy(m_pBuf + m_nPos, m_pElem[m_nLayer], nLen);
		m_nPos += nLen;
		m_pBuf[m_nPos] = '>';
		m_pBuf[m_nPos + 1] = '\n';
		m_nPos += 2;
	}

	m_pBuf[m_nPos] = '\0';


	return m_pBuf;
}

bool CBHXml::AddElem(const char *pStr)
{
	int nLen = (int)strlen(pStr);
	if(nLen > MAX_ELEM_SIZE - 1)
	{
		return false;
	}
    
	while(nLen + m_nPos + 10 > m_nBufSize)
	{
		SetBuffer(m_nBufSize * 2);
	}

	memcpy(m_pElem[m_nLayer], pStr, nLen);
	m_pElem[m_nLayer][nLen] = '\0';

	if(STATUS_ELEM_ADD == m_nStatus)
	{
		m_pBuf[m_nPos] = ' ';
		m_pBuf[m_nPos + 1] = '/';
		m_pBuf[m_nPos + 2] = '>';
		m_pBuf[m_nPos + 3] = '\n';
		m_nPos += 4;
	}

	m_pBuf[m_nPos] = '<';
	m_nPos++;
	memcpy(m_pBuf + m_nPos, pStr, nLen);
	m_nPos += nLen;

	m_nStatus = STATUS_ELEM_ADD;

	return true;
}

bool CBHXml::IntoElem()
{
	int nLen = 4;

	while(nLen + m_nPos> m_nBufSize)
	{
		SetBuffer(m_nBufSize * 2);
	}
    
	if(STATUS_ELEM_ADD == m_nStatus)
	{
		m_pBuf[m_nPos] = '>';
		m_pBuf[m_nPos + 1] = '\n';
		m_nPos += 2;
	}

	m_nLayer++;
	if(m_nLayer >= 16)
	{
		return false;
	}
	m_pElem[m_nLayer][0] = '\0';

	m_nStatus = STATUS_ELEM_FINISH;
    return true;
}

bool CBHXml::OutOfElem()
{
	if(m_nLayer == 0)
	{
		return false;
	}

	int nLen = (int)strlen(m_pElem[m_nLayer]);

	while(nLen + m_nPos + 10> m_nBufSize)
	{
		SetBuffer(m_nBufSize * 2);
	}

	if((STATUS_ELEM_ADD == m_nStatus) && nLen)
	{
		m_pBuf[m_nPos] = ' ';
		m_pBuf[m_nPos + 1] = '/';
		m_pBuf[m_nPos + 2] = '>';
		m_pBuf[m_nPos + 3] = '\n';
		m_nPos += 4;
	}

	m_nStatus = STATUS_ELEM_FINISH;

	m_nLayer--;

	nLen = (int)strlen(m_pElem[m_nLayer]);
	while(nLen + m_nPos + 10> m_nBufSize)
	{
		SetBuffer(m_nBufSize * 2);
	}

	m_pBuf[m_nPos] = '<';
	m_pBuf[m_nPos + 1] = '/';
	m_nPos += 2;
	memcpy(m_pBuf + m_nPos, m_pElem[m_nLayer], nLen);
	m_nPos += nLen;
	m_pBuf[m_nPos] = '>';
	m_pBuf[m_nPos + 1] = '\n';
	m_nPos += 2;

	return true;
}

bool CBHXml::AddAttrib(const char *pKey, const char *pValue)
{
	if(STATUS_ELEM_FINISH == m_nStatus)
	{
		return false;
	}

	int nKeyLen = (int)strlen(pKey);
	int nValueLen = (int)strlen(pValue);

	while(nKeyLen + nValueLen + 10 + m_nPos > m_nBufSize)
	{
		SetBuffer(m_nBufSize * 2);
	}

	m_pBuf[m_nPos] = ' ';
	m_nPos++;
	memcpy(m_pBuf + m_nPos, pKey, nKeyLen);
	m_nPos += nKeyLen;
	m_pBuf[m_nPos] = '=';
	m_nPos++;
	m_pBuf[m_nPos] = '\"';
	m_nPos++;
	memcpy(m_pBuf + m_nPos, pValue, nValueLen);
	m_nPos += nValueLen;
	m_pBuf[m_nPos] = '\"';
	m_nPos++;

	return true;
}

bool CBHXml::SetAttrib(const char *pKey, const char *pValue)
{
	return AddAttrib(pKey, pValue);
}

bool CBHXml::AddAttrib(const char *pKey, const int nValue)
{
	char pValue[32];

	sprintf(pValue, "%d", nValue);

	return AddAttrib(pKey, pValue);
}

bool CBHXml::SetAttrib(const char *pKey, const int nValue)
{
	return AddAttrib(pKey, nValue);
}

bool CBHXml::AddAttrib(const char *pKey, const unsigned int nValue)
{
    char pValue[32];

    sprintf(pValue, "%u", nValue);

    return AddAttrib(pKey, pValue);
}

bool CBHXml::SetAttrib(const char *pKey, const unsigned int nValue)
{
    return AddAttrib(pKey, nValue);
}

bool CBHXml::AddUint64Attrib(const char *pKey, const UINT64 nValue)
{
    char pValue[64];

    sprintf(pValue, "%lu", (long unsigned int)nValue);

    return AddAttrib(pKey, pValue);
}

