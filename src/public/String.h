/*******************************************************************************
* 版权所有 (C) 2007
* 
* 文件名称： String.h
* 文件标识： 
* 内容摘要： 
* 其它说明： 功能与MFC的CString类似
* 当前版本： V1.0
* 作    者： 周锋
* 完成日期： 2007-12-06
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

	//字符串指针
	char *m_pData;

	//字符串长度
	int m_nLength;

	//字符串内存长度
	int m_nAllocLength;

public:

	//普通构造函数
	CString();

	//拷贝构造
	CString(const CString &str);

	//用字符串初始化进行构造
	CString(const char * lpsz);

	//用特定字符串进行初始化
	CString(const char *pch, int nLength);

	//析构函数
	~CString();

	//输入数据
	void InputData(const char *lpsz, int nLength);

	//支持转化为const char *操作
	operator const char *() const;

	//赋值操作符重载
	CString & operator = (const char * lpsz);

	//赋值操作符重载
	CString & operator = (const CString &str);

	//=判别操作符重装
	bool operator == (const char * lpsz);

	//!=判别操作符重装
	bool operator != (const char * lpsz);

	//<判别操作符重装
	bool operator < (const char * lpsz);

	//<=判别操作符重装
	bool operator <= (const char * lpsz);

	//>判别操作符重装
	bool operator > (const char * lpsz);

	//>=判别操作符重装
	bool operator >= (const char * lpsz);

	//=判别操作符重装
	bool operator == (const CString &str);

	//!=判别操作符重装
	bool operator != (const CString &str);

	//<判别操作符重装
	bool operator < (const CString &str);

	//<=判别操作符重装
	bool operator <= (const CString &str);

	//>判别操作符重装
	bool operator > (const CString &str);

	//>=判别操作符重装
	bool operator >= (const CString &str);

	//清空数据
	void Empty();

	//获取内部数据指针
	char * GetBuffer(int nLength = -1);

	//释放数据
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

	//格式化字符串(被格式化字符串长度不能超过1024字节)
	void Format(const char * lpszFormat, ...);

	//获取当前字符串长度
	int GetLength() const{return m_nLength;}

	//判断当前字符串长度是否为空
	bool IsEmpty() const {return (0 == m_nLength);}

	//字符串追加操作
	CString &operator += (const char * lpsz);

	//获取从某个位置开始的字符串
	CString Mid(int nFirst, int nCount = 1) const;

	// 转化成大写
	CString& MakeUpper();

	// 转化成小写
	CString& MakeLower();

	// 查找子串
	int Find(LPCTSTR lpszSub);
};

//字符串 '+' 运算符重载
CString operator + (const char * lpsz, const CString& str);

//字符串 '==' 运算符重载
bool operator == (const char * lpsz, const CString &str);

//字符串 '!=' 运算符重载
bool operator != (const char * lpsz, const CString &str);

//字符串 '<' 运算符重载
bool operator < (const char * lpsz, const CString &str);

//字符串 '<=' 运算符重载
bool operator <= (const char * lpsz, const CString &str);

//字符串 '>' 运算符重载
bool operator > (const char * lpsz, const CString &str);

//字符串 '>=' 运算符重载
bool operator >= (const char * lpsz, const CString &str);

#endif		// end of _WIN32

#endif
