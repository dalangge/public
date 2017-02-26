#include "stdafx.h"
#include "String.h"
#include <stdarg.h>

#include <vector>

#ifndef _WIN32

#if _MSC_VER > 1000
	#pragma warning(disable : 4996)
#endif

CString::CString()
{
	m_nLength = 0;
	m_nAllocLength = 1;
	m_pData = new char[m_nAllocLength];
	m_pData[m_nLength] = 0;
}

CString::CString(const CString &str)
{
	m_nLength = 0;
	m_nAllocLength = 0;
	m_pData = NULL;
	InputData((const char *)str, str.GetLength());
}

CString::CString(const char * lpsz)
{
	m_nLength = 0;
	m_nAllocLength = 0;
	m_pData = NULL;
	InputData(lpsz, (int)strlen(lpsz));
}

CString::CString(const char *pch, int nLength)
{
	m_nLength = 0;
	m_nAllocLength = 0;
	m_pData = NULL;
	InputData(pch, nLength);
}

CString::~CString()
{
	delete []m_pData;
}

void CString::InputData(const char *lpsz, int nLength)
{
	if (nLength < 0)
	{
		nLength = 0;
	}
	if (nLength + 1 > m_nAllocLength)
	{
		do 
		{
			m_nAllocLength = (0 == m_nAllocLength) ? (nLength + 1) : (m_nAllocLength * 2);
		}
		while (nLength + 1 > m_nAllocLength);

		delete []m_pData;
		m_pData = new char [m_nAllocLength];
	}
	m_nLength = nLength;
	memcpy(m_pData, lpsz, m_nLength);
	m_pData[m_nLength] = 0;
}

CString::operator const char *() const
{
	return m_pData;
}

CString & CString::operator = (const char * lpsz)
{
	InputData(lpsz, (int)strlen(lpsz));
	return *this;
}

CString & CString::operator = (const CString &str)
{
	InputData((const char *)str, str.GetLength());
	return *this;
}

bool CString::operator == (const char * lpsz)
{
	return (0 == strcmp(m_pData, lpsz));
}

bool CString::operator != (const char * lpsz)
{
	return (0 != strcmp(m_pData, lpsz));
}

bool CString::operator < (const char * lpsz)
{
	return (0 > strcmp(m_pData, lpsz));
}

bool CString::operator <= (const char * lpsz)
{
	return (0 >= strcmp(m_pData, lpsz));
}

bool CString::operator > (const char * lpsz)
{
	return (0 < strcmp(m_pData, lpsz));
}

bool CString::operator >= (const char * lpsz)
{
	return (0 <= strcmp(m_pData, lpsz));
}

bool CString::operator == (const CString &str)
{
	return *this == (const char *)str;
}

bool CString::operator != (const CString &str)
{
	return *this != (const char *)str;
}

bool CString::operator < (const CString &str)
{
	return *this < (const char *)str;
}

bool CString::operator <= (const CString &str)
{
	return *this <= (const char *)str;
}

bool CString::operator > (const CString &str)
{
	return *this > (const char *)str;
}

bool CString::operator >= (const CString &str)
{
	return *this >= (const char *)str;
}

void CString::Empty()
{
	m_nLength = 0;
	m_pData[0] = 0;
}

char * CString::GetBuffer(int nLength)
{
	if (-1 != nLength)
	{
		if (nLength + 1 > m_nAllocLength)
		{
			m_nAllocLength = nLength + 1;
			char *pData = m_pData;
			m_pData = new char [m_nAllocLength];
			memcpy(m_pData, pData, m_nLength + 1);
			delete []pData;
		}
	}
	return m_pData;
}

void CString::Format(const char * lpszFormat, ...)
{
	va_list ptr;
	std::vector<char> buf;

	va_start(ptr, lpszFormat);
	int nSize = vsnprintf(NULL, 0, lpszFormat, ptr);
	va_end(ptr);

	buf.resize(nSize + 1);
	va_start(ptr, lpszFormat);
	vsnprintf(&buf[0], buf.size(), lpszFormat, ptr);
	va_end(ptr);

	char *pBuf = &buf[0];

	InputData(pBuf, (int)strlen(pBuf));
}

CString & CString::operator += (const char * lpsz)
{
	int nNewLength = m_nLength + (int)strlen(lpsz);
	if (nNewLength + 1 > m_nAllocLength)
	{
		do 
		{
			m_nAllocLength *= 2;
		}
		while (nNewLength + 1 > m_nAllocLength);

		char *pData = m_pData;
		m_pData = new char [m_nAllocLength];
		memcpy(m_pData, pData, m_nLength + 1);
		delete []pData;
	}
	memcpy(m_pData + m_nLength, lpsz, nNewLength - m_nLength);
	m_nLength = nNewLength;
	m_pData[m_nLength] = 0;
	return *this;
}

CString CString::Mid(int nFirst, int nCount) const
{
	if (nFirst < 0)
	{
		nFirst = 0;
	}
	if (nCount < 0)
	{
		nCount = 0;
	}
	if (nFirst >= m_nLength)
	{
		return CString();
	}
	if (nFirst + nCount > m_nLength)
	{
		nCount = m_nLength - nFirst;
	}
	return CString(m_pData + nFirst, nCount);
}

CString operator + (const char *lpsz, const CString& str)
{
	CString strRet(lpsz);
	strRet += str;
	return strRet;
}

CString& CString::MakeUpper()
{
	for (int i = 0; i < m_nLength; ++i)
	{
		if (m_pData[i] >= 'a' && m_pData[i] <= 'z')
		{
			m_pData[i] = m_pData[i] - 'a' + 'A';
		}
	}
	return (*this);
}

CString& CString::MakeLower()
{
	for (int i = 0; i < m_nLength; ++i)
	{
		if (m_pData[i] >= 'A' && m_pData[i] <= 'Z')
		{
			m_pData[i] = m_pData[i] - 'A' + 'a';
		}
	}
	return (*this);
}

int CString::Find(LPCTSTR lpszSub)
{
	char *pSub = strstr(m_pData, lpszSub);
	if (NULL == pSub)
	{
		return -1;
	}
	return pSub - m_pData;
}

bool operator == (const char * lpsz, const CString &str)
{
	return CString(lpsz) == str;
}

bool operator != (const char * lpsz, const CString &str)
{
	return CString(lpsz) != str;
}

bool operator < (const char * lpsz, const CString &str)
{
	return CString(lpsz) < str;
}

bool operator <= (const char * lpsz, const CString &str)
{
	return CString(lpsz) <= str;
}

bool operator > (const char * lpsz, const CString &str)
{
	return CString(lpsz) > str;
}

bool operator >= (const char * lpsz, const CString &str)
{
	return CString(lpsz) >= str;
}


#endif		// end of _WIN32
