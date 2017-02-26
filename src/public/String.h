
#ifndef STRING_H_JKLJKL_5473i2
#define STRING_H_JKLJKL_5473i2

#ifndef _WIN32

#include <string>
#include <string.h>
#include <stdio.h>
#include "typedef.h"

class CString
{
private:
	char *m_pData;
	int m_nLength;
	int m_nAllocLength;

public:
	CString();
	CString(const CString &str);
	CString(const char * lpsz);
	CString(const char *pch, int nLength);

	~CString();

	void InputData(const char *lpsz, int nLength);

    operator const char *() const;
    
    CString & operator = (const char * lpsz);
    CString & operator = (const CString &str);
	bool operator == (const char * lpsz);
	bool operator != (const char * lpsz);
	bool operator < (const char * lpsz);
	bool operator <= (const char * lpsz);
	bool operator > (const char * lpsz);
	bool operator >= (const char * lpsz);
	bool operator == (const CString &str);
	bool operator != (const CString &str);
	bool operator < (const CString &str);
	bool operator <= (const CString &str);
	bool operator > (const CString &str);
	bool operator >= (const CString &str);

	void Empty();

	char * GetBuffer(int nLength = -1);

	void ReleaseBuffer(int nNewLength = -1)
	{
		if (nNewLength < 0)
		{
			nNewLength = strlen(m_pData);
			m_nLength = nNewLength;
		}
		else if (nNewLength != m_nLength)
		{
			m_nLength = nNewLength;
			m_pData[m_nLength] = 0;
		}
	}

	void Format(const char * lpszFormat, ...);

	int GetLength() const{return m_nLength;}

	bool IsEmpty() const {return (0 == m_nLength);}

	CString &operator += (const char * lpsz);

	CString Mid(int nFirst, int nCount = 1) const;

	CString& MakeUpper();

	CString& MakeLower();

	int Find(LPCTSTR lpszSub);
};

CString operator + (const char * lpsz, const CString& str);
bool operator == (const char * lpsz, const CString &str);
bool operator != (const char * lpsz, const CString &str);
bool operator < (const char * lpsz, const CString &str);
bool operator <= (const char * lpsz, const CString &str);
bool operator > (const char * lpsz, const CString &str);
bool operator >= (const char * lpsz, const CString &str);

#endif		// end of _WIN32

#endif
