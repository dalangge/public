/*******************************************************************************
* ��Ȩ���� (C) 2007
* 
* �ļ����ƣ� String.h
* �ļ���ʶ�� 
* ����ժҪ�� 
* ����˵���� ������MFC��CString����
* ��ǰ�汾�� V1.0
* ��    �ߣ� �ܷ�
* ������ڣ� 2007-12-06
*******************************************************************************/
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

	//�ַ���ָ��
	char *m_pData;

	//�ַ�������
	int m_nLength;

	//�ַ����ڴ泤��
	int m_nAllocLength;

public:

	//��ͨ���캯��
	CString();

	//��������
	CString(const CString &str);

	//���ַ�����ʼ�����й���
	CString(const char * lpsz);

	//���ض��ַ������г�ʼ��
	CString(const char *pch, int nLength);

	//��������
	~CString();

	//��������
	void InputData(const char *lpsz, int nLength);

	//֧��ת��Ϊconst char *����
	operator const char *() const;

	//��ֵ����������
	CString & operator = (const char * lpsz);

	//��ֵ����������
	CString & operator = (const CString &str);

	//=�б��������װ
	bool operator == (const char * lpsz);

	//!=�б��������װ
	bool operator != (const char * lpsz);

	//<�б��������װ
	bool operator < (const char * lpsz);

	//<=�б��������װ
	bool operator <= (const char * lpsz);

	//>�б��������װ
	bool operator > (const char * lpsz);

	//>=�б��������װ
	bool operator >= (const char * lpsz);

	//=�б��������װ
	bool operator == (const CString &str);

	//!=�б��������װ
	bool operator != (const CString &str);

	//<�б��������װ
	bool operator < (const CString &str);

	//<=�б��������װ
	bool operator <= (const CString &str);

	//>�б��������װ
	bool operator > (const CString &str);

	//>=�б��������װ
	bool operator >= (const CString &str);

	//�������
	void Empty();

	//��ȡ�ڲ�����ָ��
	char * GetBuffer(int nLength = -1);

	//�ͷ�����
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

	//��ʽ���ַ���(����ʽ���ַ������Ȳ��ܳ���1024�ֽ�)
	void Format(const char * lpszFormat, ...);

	//��ȡ��ǰ�ַ�������
	int GetLength() const{return m_nLength;}

	//�жϵ�ǰ�ַ��������Ƿ�Ϊ��
	bool IsEmpty() const {return (0 == m_nLength);}

	//�ַ���׷�Ӳ���
	CString &operator += (const char * lpsz);

	//��ȡ��ĳ��λ�ÿ�ʼ���ַ���
	CString Mid(int nFirst, int nCount = 1) const;

	// ת���ɴ�д
	CString& MakeUpper();

	// ת����Сд
	CString& MakeLower();

	// �����Ӵ�
	int Find(LPCTSTR lpszSub);
};

//�ַ��� '+' ���������
CString operator + (const char * lpsz, const CString& str);

//�ַ��� '==' ���������
bool operator == (const char * lpsz, const CString &str);

//�ַ��� '!=' ���������
bool operator != (const char * lpsz, const CString &str);

//�ַ��� '<' ���������
bool operator < (const char * lpsz, const CString &str);

//�ַ��� '<=' ���������
bool operator <= (const char * lpsz, const CString &str);

//�ַ��� '>' ���������
bool operator > (const char * lpsz, const CString &str);

//�ַ��� '>=' ���������
bool operator >= (const char * lpsz, const CString &str);

#endif		// end of _WIN32

#endif
