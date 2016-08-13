/*******************************************************************************
* 版权所有 (C) 2007
* 
* 文件名称： time.h
* 文件标识： 
* 内容摘要：  
* 其它说明： 功能与MFC的CTime类似，有效时间范围：1900-1-1 0:0:0——2100-12-31 12:59:59
* 当前版本： V1.0
* 作    者： 司文丽
* 完成日期： 2007-12-05
*******************************************************************************/
#ifndef	_TIME_H_785432543
#define	_TIME_H_785432543

#ifndef _WIN32

#include "TimeSpan.h"
#include <string>
using   namespace   std; 

class CTime
{
public:
	//构造函数
	CTime();

	//拷贝构造函书
	CTime(const CTime &time);

	//构造函数
	CTime(
		long nDays,		//时间值相对1900年1月1日的日增量
		long nSec = 0	//时间值相对00：00：00 的秒增量
		);

	//构造函数
	CTime(
		int nYear,		//公元纪年的年 1900-2100
		int nMonth,		//公元纪年的月 1-12
		int nDay,		//公元纪年的日 1-31
		int nHour,		//时0-23
		int nMin,		//分0-59
		int nSec);		//秒0-59
	
	//析构函数
	~CTime();

	//获取系统当前时间
	static CTime GetCurrentTime();

	//获取时间值的公元纪年的年值
	int GetYear() const;

	//获取时间值得公元纪年的月值
	int GetMonth() const;

	//获取时间值的公元纪年的日值
	int GetDay() const;

	//获取时间值的公元纪年的时值
	int GetHour() const;

	//获取时间值的公元纪年的分值
	int GetMinute() const;

	//获取时间值的公元纪年的秒值
	int GetSecond() const;

	//获取时间值是星期几
	int GetDayOfWeek() const;
	
	// < 运算符重载 
	bool operator < (const CTime &time) const;

	// == 运算符重载 
	bool operator == (const CTime &time) const;

	// != 运算符重载 
	bool operator != (const CTime &time) const;

	// <= 运算符重载 
	bool operator <= (const CTime &time) const;

	// >= 运算符重载 
	bool operator >= (const CTime &time) const;

	// > 运算符重载 
	bool operator > (const CTime &time) const;

	// + 运算符重载 
	CTime operator + (const CTimeSpan &timeSpan) const;

	// - 运算符重载 
	CTime operator - (const CTimeSpan &timeSpan) const;

	// - 运算符重载 
	CTimeSpan operator - (const CTime &time) const;

	// = 运算符重载 
	CTime& operator = (const CTime &time);	
	
	//时间格式化为字符串
	CString Format( LPCSTR pszFormat) const;

	//获取相对1900年1月1日的时日增量
	long GetTotalDays() const;

	//获取相对00：00：00 的时秒增量
	long GetTotalSeconds() const;

protected:

	//时间值相对1900年1月1日的日增量
	long m_nDays;

	//时间值相对00：00：00 的秒增量
	long m_nSeconds;

	//设置时间值
	BOOL _SetDate(
		int nYear,				//公元纪年的年 1900-2100
		int nMonth,				//公元纪年的月 1-12
		int nDay,				//公元纪年的日 1-31
		int nHour,				//时0-23
		int nMin,				//分0-59
		int nSec);				//秒0-59

	//设置时间值
	BOOL _SetDate(
		int nDays,				//相对1900年1月1日的日增量
		int nSeconds);			//相对00：00：00 的秒增量

	//获取日期 
	BOOL _GetDate(
		int &nYear,				//公元纪年的年
		int &nMonth,			//公元纪年的月
		int &nDay				//公元纪年的日
		) const;	

	//获取时间
	BOOL _GetTime(
		int &nHour,				//时
		int &nMin,				//分
		int &nSec				//秒
		) const;

	//根据格式字符获取格式值
	string _GetValue(char cFormat) const;

	//根据星期几获取星期缩写
	string _GetDayofWeekAbbrevName(int nDayofWeek) const;

	//根据星期几获取星期全名
	string _GetDayofWeekFullName(int nDayofWeek) const;

	//根据几月获取月缩写
	string _GetMonthAbbrevName(int nMonth) const;

	//根据几月获取月全名
	string _GetMonthFullName(int nMonth)const;

};

#endif		// end of _WIN32

#endif





