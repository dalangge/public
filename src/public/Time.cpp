#include "stdafx.h"
#include "Time.h"
#include <sstream>
#include <time.h>

#include <vector>
using namespace std;

#ifndef _WIN32

#define SECOND_PERDAY 86400
#define SECOND_PERHOUR 3600

/*******************************************************************************
* 函数名称：	
* 功能描述：	构造函数	
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
CTime::CTime()
{
	m_nDays = 0;
	m_nSeconds = 0;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	构造函数
* 输入参数：	nDays			-- 时间值相对1900年1月1日的日增量
*				nSec			-- 时间值相对00：00：00 的秒增量
* 输出参数：	
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人			修改内容
* ------------------------------------------------------------------------------
* 2010-06-03	司文丽	      	创建
*******************************************************************************/
CTime::CTime(long nDays, long nSec /* = 0  */)
{
	m_nDays = nDays;
	m_nSeconds = nSec;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	拷贝构造函数
* 输入参数：	time	:	用于拷贝的CTime型变量	
* 输出参数：	
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
CTime::CTime(const CTime &time)
{
	this->m_nDays = time.GetTotalDays();
	this->m_nSeconds = time.GetTotalSeconds();
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	构造函数	
* 输入参数：	nYear	:	公元纪年的年
*				nMonth	:	公元纪年的月
*				nDay	:	公元纪年的日
*				nHour	:	时
*				nMin	:	分
*				nSec	:	秒
* 输出参数：	无
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
CTime::CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec)
{
	m_nDays = 0;
	m_nSeconds = 0;
	_SetDate(nYear, nMonth, nDay, nHour, nMin,nSec);
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	析构函数	
* 输入参数：	
* 输出参数：	
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
CTime::~CTime()
{
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取系统当前时间
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	当前系统时间的CTime类型值
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
* 2011-01-26	司文丽		  用localtime_r代替localtime，以支持多线程安全。
*******************************************************************************/
CTime CTime::GetCurrentTime()
{
 	struct tm times;			//定义时间指针变量    
 	time_t t;					//定义系统时间变量,供提供系统时间  
 	t = time(0);				//当前系统时间给变量t
#if defined _WIN32
	localtime_s(&times, &t);	//把系统时间变量强制转换成tm结构体形式时间
#else
	localtime_r(&t, &times);
#endif

	int nYear, nMonth, nDay, nHour, nMin, nSec;
	nYear = times.tm_year + 1900;
	nMonth = times.tm_mon + 1;
	nDay = times.tm_mday;
	nHour = times.tm_hour;
	nMin = times.tm_min;
	nSec = times.tm_sec;
	
	CTime tmCur(nYear, nMonth, nDay, nHour, nMin, nSec);
	return tmCur;
}


/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的年值	
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	时间的年
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetYear() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nYear;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的月值
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	时间的月
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetMonth() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nMonth;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的日值
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	时间的日
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetDay() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nDay;

}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的时值
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	时间的时
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetHour() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nHour;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的分值
* 输入参数：	无
* 输出参数：	无
* 返 回 值：	时间的分
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetMinute() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nMin;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值的公元纪年的秒值
* 输入参数：	
* 输出参数：	
* 返 回 值：	时间的秒
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
int CTime::GetSecond() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nSec;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间值是星期几
* 输入参数：	
* 输出参数：	
* 返 回 值：	星期几（1：星期日 —— 7：星期六）
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
* 2011-03-03    陈书军		  修改星期几针对星期六获取为0的错误情况
*******************************************************************************/
int CTime::GetDayOfWeek() const
{
	int nDayofWeek = (int) (m_nDays % 7 + 1);
	return nDayofWeek;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	<
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	小于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator < (const CTime &time) const
{
	if(this->GetTotalDays() < time.GetTotalDays())
	{
		return true;
	}
	else if(this->GetTotalDays() == time.GetTotalDays()
		&&this->GetTotalSeconds() < time.GetTotalSeconds())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	==
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	等于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator == (const CTime &time) const
{
	return !( *this  < time || time < *this );		
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	!=
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	不等于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator != (const CTime &time) const
{
	return ( *this  < time || time < *this );
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	<=
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	小于等于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator <= (const CTime &time) const
{
	return ( *this < time || *this == time );
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	>=
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	大于等于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator >= (const CTime &time) const
{
	return !( *this < time);
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	>
* 输入参数：	time	:	与*this进行比较的CTime型变量
* 输出参数：	
* 返 回 值：	大于返回true， 否则返回false
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
bool CTime::operator > (const CTime &time) const
{
	return ( time < *this);
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	+
* 输入参数：	timespan	:	加数
* 输出参数：	
* 返 回 值：	（*this + 加数）后的CTime类型结果变量
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
CTime CTime::operator + (const CTimeSpan &timespan) const
{	
	long nSeconds, nDays;
	nSeconds = m_nSeconds + timespan.GetTimeSpanSeconds();
	nDays = m_nDays + timespan.GetDays() + nSeconds / SECOND_PERDAY;
	nSeconds %= SECOND_PERDAY;

	CTime time;
	time._SetDate(nDays, nSeconds);
	return time;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	-
* 输入参数：	time	:	减数
* 输出参数：	
* 返 回 值：	（*this - 减数）后的CTime类型结果变量
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
CTime CTime::operator - (const CTimeSpan &timespan) const
{
	long nTimeDays, nTimeSeconds, nSpanDays, nSpanSeconds;
	nTimeDays = GetTotalDays();
	nTimeSeconds = GetTotalSeconds();
	nSpanDays = timespan.GetDays();
	nSpanSeconds = timespan.GetTimeSpanSeconds();

	long nResultDays, nResultSeconds;
	
	if(nTimeSeconds < nSpanSeconds)
	{
		nTimeDays--;
		nResultSeconds = SECOND_PERDAY + nTimeSeconds - nSpanSeconds;			
	}
	else
		nResultSeconds = nTimeSeconds - nSpanSeconds;
	
	nResultDays = nTimeDays - nSpanDays;

    CTime time;
	time._SetDate(nResultDays, nResultSeconds);
	return time;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	-
* 输入参数：	time	:	减数
* 输出参数：	
* 返 回 值：	（*this - 减数）的CTimeSpan类型结果变量
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
CTimeSpan CTime::operator -(const CTime &time) const
{
	long nTimeDays1, nTimeSeconds1, nTimeDays2, nTimeSeconds2;
	nTimeDays1 = GetTotalDays();
	nTimeSeconds1 = GetTotalSeconds();
	nTimeDays2 = time.GetTotalDays();
	nTimeSeconds2 = time.GetTotalSeconds();

	long nResultDays, nResultSeconds;

	if(nTimeSeconds1 < nTimeSeconds2)
	{
		nTimeDays1--;
		nResultSeconds = SECOND_PERDAY + nTimeSeconds1 - nTimeSeconds2;			
	}
	else
		nResultSeconds = nTimeSeconds1 - nTimeSeconds2;
	
	nResultDays = nTimeDays1 - nTimeDays2;

	CTimeSpan timespan;
	timespan.SetTimeSpan(nResultDays, nResultSeconds);
	return timespan;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	=
* 输入参数：	
* 输出参数：	
* 返 回 值：	
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-06	司文丽	      创建
*******************************************************************************/
CTime& CTime::operator =(const CTime &time)
{
	this->m_nDays = time.GetTotalDays();
	this->m_nSeconds = time.GetTotalSeconds();
	return *this;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	时间格式化为字符串
* 输入参数：	pszFormat	:	格式化字符串
* 输出参数：	
* 返 回 值：	返回求值后的字符串
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
CString CTime::Format( LPCSTR pszFormat) const
{
	int nYear, nMonth, nDay, nHour, nMin, nSec, nDayofWeek;

	_GetDate(nYear, nMonth, nDay);
	_GetTime(nHour, nMin, nSec);
	nDayofWeek = GetDayOfWeek();

	struct tm tmTmp;
	tmTmp.tm_year = nYear - 1900;
	tmTmp.tm_mon = nMonth - 1;
	tmTmp.tm_mday = nDay;
	tmTmp.tm_hour = nHour;
	tmTmp.tm_min = nMin;
	tmTmp.tm_sec = nSec;
	tmTmp.tm_wday = nDayofWeek - 1;
	tmTmp.tm_isdst = -1;

	std::vector<char> buf(1024);
	size_t nRet = 0;
	while ((nRet = strftime(&buf[0], buf.size(), pszFormat, &tmTmp)) == 0)
 	{
 		buf.resize(buf.size() * 2);
 	}

	return CString(&buf[0]);
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取相对1900年1月1日的日增量
* 输入参数：	
* 输出参数：	
* 返 回 值：	日增量值
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
long CTime::GetTotalDays() const
{
	return m_nDays;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取相对00：00：00 的秒增量
* 输入参数：	
* 输出参数：	
* 返 回 值：	秒增量
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
long CTime::GetTotalSeconds() const
{
	return m_nSeconds;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	设置时间值	
* 输入参数：	nYear	:	公元纪年的年
*				nMonth	:	公元纪年的月
*				nDay	:	公元纪年的日
*				nHour	:	时
*				nMin	:	分
*				nSec	:	秒
* 输出参数：	无
* 返 回 值：	执行成功返回TRUE。
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
BOOL CTime::_SetDate(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec)
{
	if (nYear < 1900)
	{
		return FALSE;
	}

	int nDate = 0;
	int i = 0;
	int anMonthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	//起点到该年初的天数
	for (i=1900; i<nYear; i++)
	{
		nDate += 365;
		//如果是闰年加一天
		if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
		{
			nDate ++;
		}
	}

	//从年初到第一月初的天数
	if(((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0))
	{
		anMonthDay[1] = 29;
	}
	for (i=1; i<nMonth; i++)
	{
		nDate += anMonthDay[i - 1];
	}

	//该月的天数
	nDate += nDay;

	m_nDays = nDate;
	m_nSeconds = nHour * SECOND_PERHOUR + nMin * 60 + nSec;

	return TRUE;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	设置时间值	
* 输入参数：	nDays		:	相对1900年1月1日的时间增量的日计数
*				nSeconds	:	相对00：00：00 的时间增量的秒计数
* 输出参数：	无
* 返 回 值：	执行成功返回TRUE
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
BOOL CTime::_SetDate(int nDays, int nSeconds)
{
	m_nDays = (long)nDays;
	m_nSeconds = (long)nSeconds;
	return TRUE;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取日期	
* 输入参数：	无
* 输出参数：	nYear	:	公元纪年的年
*				nMonth	:	公元纪年的月
*				nDay	:	公元纪年的日
* 返 回 值：	执行成功返回TRUE，执行失败返回FALSE。
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
BOOL CTime::_GetDate(int &nYear, int &nMonth, int &nDay) const
{
	nYear = 0;
	nMonth = 0;
	nDay = 0;

	int nOffset = (int)m_nDays;
    
	int nTmp = 0;
	int i=0;
	for(i=1900; i<2100 && nOffset>0; i++) 
	{ 
		nTmp = 365;
		if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
		{
			nTmp ++;
		}
		nOffset -= nTmp; 
	}
	if(nOffset<=0) 
	{ 
		nOffset += nTmp;
		i--; 
	}
	nYear = i;

	int anMonthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
	{
		anMonthDay[1] = 29;
	}
	for(i=1; i<12 && nOffset>0; i++) 
	{
		nTmp = anMonthDay[i -1];
		nOffset -= nTmp;
	}

	if(nOffset <= 0)
	{ 
		nOffset += nTmp; 
		--i; 
	}
	nMonth = i;
	nDay = nOffset;	

	return TRUE;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	获取时间，参数
* 输入参数：	无
* 输出参数：	nHour	:	时
*				nMin	:	分
*				nSec	:	秒
* 返 回 值：	执行成功返回TRUE，执行失败返回FALSE。
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-04	司文丽	      创建
*******************************************************************************/
BOOL CTime::_GetTime(int &nHour, int &nMin, int &nSec) const
{
	nHour = 0;
	nMin = 0;
	nSec = 0;

	int nOffset = (int)m_nSeconds;

	nHour = nOffset / SECOND_PERHOUR;
	nOffset -= nHour * SECOND_PERHOUR;

	nMin = nOffset / 60;
	nOffset -= nMin * 60;
	
	nSec = nOffset;

	return TRUE;    
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	cFormat	:	根据格式字符获取相应的值字符串
* 输入参数：	格式字符
* 输出参数：	
* 返 回 值：	返回对应的值字符串
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-05	司文丽	      创建
*******************************************************************************/
string CTime::_GetValue(char cFormat) const
{
	string strValue(1, cFormat);

	int nYear, nMonth, nDay, nHour, nMin, nSec, nDayofWeek;
	string strYear, strMonth, strDay, strHour, strMin, strSec, strDayofWeek;

	_GetDate(nYear, nMonth, nDay);
	_GetTime(nHour, nMin, nSec);
	nDayofWeek = GetDayOfWeek();

	stringstream ss;
	ss << nYear;
	ss >> strYear;
	ss.clear();

	ss << nMonth;
	ss >> strMonth;
	if(strMonth.length() == 1)
	{
		strMonth.insert(0, "0");
	}
	ss.clear();

	ss << nDay;
	ss >> strDay;
	if(strDay.length() == 1)
	{
		strDay.insert(0, "0");
	}
	ss.clear();

	ss << nHour;
	ss >> strHour;
	if(strHour.length() == 1)
	{
		strHour.insert(0, "0");
	}
	ss.clear();

	ss << nMin;
	ss >> strMin;
	if(strMin.length() == 1)
	{
		strMin.insert(0, "0");
	}
	ss.clear();

	ss << nSec;
	ss >> strSec;
	if(strSec.length() == 1)
	{
		strSec.insert(0, "0");
	}
	ss.clear();

	ss << nDayofWeek - 1;
	ss >> strDayofWeek;
	ss.clear();

	switch(cFormat)
	{
	case 'a'://星期缩写
		strValue = _GetDayofWeekAbbrevName(nDayofWeek);
		break;
	case 'A'://星期全名
		strValue = _GetDayofWeekFullName(nDayofWeek);
		break;
	case 'b'://月缩写
		strValue = _GetMonthAbbrevName(nMonth);
		break;
	case 'B'://月全名
		strValue = _GetMonthFullName(nMonth);
		break;
	case 'd'://一个月中的第几日:00-31
		strValue = strDay;
		break;
	case 'H'://一日中的小时：00-23
		strValue = strHour;
		break;
	case 'I'://小时：01-12
		ss << (nHour % 12);
		ss >> strHour;
		strValue = strHour;		
		break;
	case 'm'://一年中的第几月：01-12
		strValue = strMonth;
		break;
	case 'M'://分钟：00-59
		strValue = strMin;
		break;
	case 'p'://AM/PM
		if(nHour / 12 == 0)
			strValue = "AM";
		else
			strValue = "PM";
		break;
	case 'S'://秒：00-59
		strValue = strSec;
		break;
	case 'w':// 星期几 0-6，星期日为0
		strValue = strDayofWeek;
		break;
	case 'Y'://年
		strValue = strYear;
		break;
	default:
		break;		
	}

	return strValue;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	根据星期几获取编写
* 输入参数：	星期几（1——7， 1为星期日）
* 输出参数：	
* 返 回 值：	星期全名
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2012-10-30	白福铭	      创建
*******************************************************************************/
string CTime::_GetDayofWeekAbbrevName(int nDayofWeek) const
{
	string strValue;

	switch(nDayofWeek)
	{
	case 1:
		strValue = "Sun";
		break;
	case 2:
		strValue = "Mon";
		break;
	case 3:
		strValue = "Tue";
		break;
	case 4:
		strValue = "Wed";
		break;
	case 5:
		strValue = "Thu";
		break;
	case 6:
		strValue = "Fri";
		break;
	case 7:
		strValue = "Sat";
		break;
	default:
		break;
	}
	return strValue;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	根据星期几获取全名
* 输入参数：	星期几（1——7， 1为星期日）
* 输出参数：	
* 返 回 值：	星期全名
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-05	司文丽	      创建
*******************************************************************************/
string CTime::_GetDayofWeekFullName(int nDayofWeek) const
{
	string strValue;

	switch(nDayofWeek)
	{
	case 1:
		strValue = "Sunday";
		break;
	case 2:
		strValue = "Monday";
		break;
	case 3:
		strValue = "Tuesday";
		break;
	case 4:
		strValue = "Wednesday";
		break;
	case 5:
		strValue = "Thursday";
		break;
	case 6:
		strValue = "Friday";
		break;
	case 7:
		strValue = "Saturday";
		break;
	default:
		break;
	}
	return strValue;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	根据几月获取月缩写
* 输入参数：	nMonth	:	几月
* 输出参数：	
* 返 回 值：	返回月缩写
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-05	司文丽	      创建
*******************************************************************************/
string CTime::_GetMonthAbbrevName(int nMonth) const
{
	string strValue;

	switch(nMonth)
	{
	case 1:
		strValue = "Jan";
		break;
	case 2:
		strValue = "Feb";
		break;
	case 3:
		strValue = "Mar";
		break;
	case 4:
		strValue = "Apr";
		break;
	case 5:
		strValue = "May";
		break;
	case 6:
		strValue = "Jun";
		break;
	case 7:
		strValue = "Jul";
		break;
	case 8:
		strValue = "Aug";
		break;
	case 9:
		strValue = "Sep";
		break;
	case 10:
		strValue = "Oct";
		break;
	case 11:
		strValue = "Nov";
		break;
	case 12:
		strValue = "Dec";
		break;
	default:
		break;
	}
	return strValue;
}

/*******************************************************************************
* 函数名称：	
* 功能描述：	根据几月获取月全名
* 输入参数：	nMonth	:	几月
* 输出参数：	
* 返 回 值：	月全名
* 其它说明：	
* 修改日期		修改人	      修改内容
* ------------------------------------------------------------------------------
* 2007-12-05	司文丽	      创建
*******************************************************************************/
string CTime::_GetMonthFullName(int nMonth) const
{
	string strValue;

	switch(nMonth)
	{
	case 1:
		strValue = "January";
		break;
	case 2:
		strValue = "February";
		break;
	case 3:
		strValue = "March";
		break;
	case 4:
		strValue = "April";
		break;
	case 5:
		strValue = "May";
		break;
	case 6:
		strValue = "June";
		break;
	case 7:
		strValue = "July";
		break;
	case 8:
		strValue = "August";
		break;
	case 9:
		strValue = "September";
		break;
	case 10:
		strValue = "October";
		break;
	case 11:
		strValue = "November";
		break;
	case 12:
		strValue = "December";
		break;
	default:
		break;
	}
	return strValue;
}


#endif		// end of _WIN32
