#include "stdafx.h"
#include "Time.h"
#include <sstream>
#include <time.h>

#include <vector>
using namespace std;

#ifndef _WIN32

#define SECOND_PERDAY 86400
#define SECOND_PERHOUR 3600

CTime::CTime()
{
	m_nDays = 0;
	m_nSeconds = 0;
}

CTime::CTime(long nDays, long nSec /* = 0  */)
{
	m_nDays = nDays;
	m_nSeconds = nSec;
}

CTime::CTime(const CTime &time)
{
	this->m_nDays = time.GetTotalDays();
	this->m_nSeconds = time.GetTotalSeconds();
}

CTime::CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec)
{
	m_nDays = 0;
	m_nSeconds = 0;
	_SetDate(nYear, nMonth, nDay, nHour, nMin,nSec);
}

CTime::~CTime()
{
}

CTime CTime::GetCurrentTime()
{
 	struct tm times;
    time_t t;
 	t = time(0);
#if defined _WIN32
	localtime_s(&times, &t);
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

int CTime::GetYear() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nYear;
}

int CTime::GetMonth() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nMonth;
}

int CTime::GetDay() const
{
	int nYear, nMonth, nDay;
	_GetDate(nYear, nMonth, nDay);
	return nDay;

}

int CTime::GetHour() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nHour;
}

int CTime::GetMinute() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nMin;
}

int CTime::GetSecond() const
{
	int nHour, nMin, nSec;
	_GetTime(nHour, nMin, nSec);
	return nSec;
}

int CTime::GetDayOfWeek() const
{
	int nDayofWeek = (int) (m_nDays % 7 + 1);
	return nDayofWeek;
}

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

bool CTime::operator == (const CTime &time) const
{
	return !( *this  < time || time < *this );		
}

bool CTime::operator != (const CTime &time) const
{
	return ( *this  < time || time < *this );
}

bool CTime::operator <= (const CTime &time) const
{
	return ( *this < time || *this == time );
}

bool CTime::operator >= (const CTime &time) const
{
	return !( *this < time);
}

bool CTime::operator > (const CTime &time) const
{
	return ( time < *this);
}

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

CTime& CTime::operator =(const CTime &time)
{
	this->m_nDays = time.GetTotalDays();
	this->m_nSeconds = time.GetTotalSeconds();
	return *this;
}

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

long CTime::GetTotalDays() const
{
	return m_nDays;
}

long CTime::GetTotalSeconds() const
{
	return m_nSeconds;
}

BOOL CTime::_SetDate(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec)
{
	if (nYear < 1900)
	{
		return FALSE;
	}

	int nDate = 0;
	int i = 0;
	int anMonthDay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (i=1900; i<nYear; i++)
	{
		nDate += 365;
        if(((i % 4 == 0) && (i % 100 != 0)) || (i % 400 == 0))
		{
			nDate ++;
		}
	}

	if(((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0))
	{
		anMonthDay[1] = 29;
	}
	for (i=1; i<nMonth; i++)
	{
		nDate += anMonthDay[i - 1];
	}

	nDate += nDay;

	m_nDays = nDate;
	m_nSeconds = nHour * SECOND_PERHOUR + nMin * 60 + nSec;

	return TRUE;
}

BOOL CTime::_SetDate(int nDays, int nSeconds)
{
	m_nDays = (long)nDays;
	m_nSeconds = (long)nSeconds;
	return TRUE;
}

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
	case 'a':
		strValue = _GetDayofWeekAbbrevName(nDayofWeek);
		break;
	case 'A':
		strValue = _GetDayofWeekFullName(nDayofWeek);
		break;
	case 'b':
		strValue = _GetMonthAbbrevName(nMonth);
		break;
	case 'B':
		strValue = _GetMonthFullName(nMonth);
		break;
	case 'd':
		strValue = strDay;
		break;
	case 'H':
		strValue = strHour;
		break;
	case 'I':
		ss << (nHour % 12);
		ss >> strHour;
		strValue = strHour;		
		break;
	case 'm':
		strValue = strMonth;
		break;
	case 'M':
		strValue = strMin;
		break;
	case 'p':
		if(nHour / 12 == 0)
			strValue = "AM";
		else
			strValue = "PM";
		break;
	case 'S':
		strValue = strSec;
		break;
	case 'w':
		strValue = strDayofWeek;
		break;
	case 'Y':
		strValue = strYear;
		break;
	default:
		break;		
	}

	return strValue;
}

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
