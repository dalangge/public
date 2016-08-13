/*******************************************************************************
* 版权所有 (C) 2007
* 
* 文件名称： timespan.h
* 文件标识： 
* 内容摘要： 
* 其它说明： 功能与MFC的CTimeSpan类似
* 当前版本： V1.0
* 作    者： 司文丽
* 完成日期： 2007-12-05
*******************************************************************************/
#ifndef _TIME_SPAN_H_78R789493289148932819452839KFLDKL
#define _TIME_SPAN_H_78R789493289148932819452839KFLDKL


#ifndef _WIN32

#include "typedef.h"
#include <string>
#include "String.h"

class CTimeSpan
{
public:

	//构造函数
	CTimeSpan();

	//拷贝构造函数
	CTimeSpan(const CTimeSpan &timespan);

	//构造函数
	CTimeSpan(const long nSec);

	//构造函数
	CTimeSpan(long nDays, long nSecs);

	//构造函数，参数依次为时间间隔的日、时、分、秒值
	CTimeSpan(LONG lDays,	//时间间隔日值 0-24800(约)
		int nHours,			//时间间隔时值 0-23
		int nMins,			//时间间隔分值 0-59
		int nSecs);			//时间间隔秒值 0-59

	//析构函数
	~CTimeSpan();
	
	//获取时间的日计数
	long GetDays() const;

	//获取时间的时计数
	long GetHours() const;
	
	//获取时间间隔的总时数
	long GetTotalHours() const;

	//获取时间的分计数
	long GetMinutes() const;

	//获取时间间隔的总分数
	long GetTotalMinutes() const;

	//获取时间的秒计数
	long GetSeconds() const;

	//获取时间间隔的总秒数
	long GetTotalSeconds() const;
	
	// == 运算符重载 
	bool operator == (const CTimeSpan &span) const ;

	// != 运算符重载 
	bool operator != (const CTimeSpan &span) const ;

	// < 运算符重载 
	bool operator < (const CTimeSpan &span) const ;

	// > 运算符重载 
	bool operator > (const CTimeSpan &span) const ;

	// <= 运算符重载 
	bool operator <= (const CTimeSpan &span) const ;

	// >= 运算符重载 
	bool operator >= (const CTimeSpan &span) const ;

	// = 运算符重载 
	CTimeSpan& operator = (const CTimeSpan &timespan);

	//时间格式化为字符串
	CString Format( LPCSTR pszFormat) const;

	//获取时间间隔的秒值
	long GetTimeSpanSeconds() const;

	//设置时间间隔
	BOOL SetTimeSpan(long nDays, long nSeconds);

protected:
	//时间间隔的秒计数
	long m_nSeconds;

	//时间间隔的日计数
	long m_nDays;

	//设置时间间隔，参数依次为时间间隔的日、时、分、秒值
	BOOL _SetTimeSpan(LONG lDays, int nHours, int nMins, int nSecs);

	//获取时间间隔
	BOOL _GetTimeSpan(
		int &nDay,				//天
		int &nHour,				//时
		int &nMin,				//分
		int &nSec				//秒
		) const;

	//根据格式字符获取格式值
	std::string _GetValue(char cFormat) const;

	
};

#endif		// end of _WIN32

#endif

