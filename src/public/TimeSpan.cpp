#include "stdafx.h"
#include "TimeSpan.h"
#include <sstream>

using namespace std;

#ifndef _WIN32

#define SECOND_PERDAY 86400
#define SECOND_PERHOUR 3600


CTimeSpan::CTimeSpan()
{
	m_nSeconds = 0;
	m_nDays =0;
}

CTimeSpan::CTimeSpan(const CTimeSpan &timespan)
{
	this->m_nDays = timespan.GetDays();
	this->m_nSeconds = timespan.GetTimeSpanSeconds();
}

CTimeSpan::CTimeSpan(const long nSec)
{
	m_nDays = nSec / 86400;
	m_nSeconds = nSec % 86400;
}

CTimeSpan::CTimeSpan(long nDays, long nSecs)
{
	m_nDays = nDays;
	m_nSeconds = nSecs;
}

CTimeSpan::CTimeSpan(LONG lDays, int nHours, int nMins, int nSecs)
{
	m_nSeconds = 0;
	m_nDays = 0;
	_SetTimeSpan(lDays, nHours, nMins, nSecs);
}

CTimeSpan::~CTimeSpan()
{

}

long CTimeSpan::GetDays() const
{
	return m_nDays;	
}

long CTimeSpan::GetHours() const
{
	long nHours = m_nSeconds / SECOND_PERHOUR;
	return nHours;
}

long CTimeSpan::GetTotalHours() const
{
	long nHours = m_nDays * 24 + m_nSeconds / SECOND_PERHOUR;
	return nHours;
}

long CTimeSpan::GetMinutes() const
{
	long nSeconsMinusHour = m_nSeconds % SECOND_PERHOUR;
	long nMins = nSeconsMinusHour / 60;
	return nMins;
}

long CTimeSpan::GetTotalMinutes() const
{
	long nMins = m_nSeconds / 60 + m_nDays * 24 * 60;
	return nMins;
}

long CTimeSpan::GetSeconds() const
{
	long nSecs = m_nSeconds % 60;
	return nSecs;
}

long CTimeSpan::GetTotalSeconds() const
{
	long nSecs = m_nDays * SECOND_PERDAY + m_nSeconds;
	return nSecs;
}

bool CTimeSpan::operator == (const CTimeSpan &timespan) const
{
	return !( *this < timespan || timespan < *this);
}

bool CTimeSpan::operator !=(const CTimeSpan &timespan) const
{
	return ( *this < timespan || timespan < *this);	
}

bool CTimeSpan::operator < (const CTimeSpan &timespan) const
{
	if(this->GetDays() < timespan.GetDays())
	{
		return true;
	}
	else if(this->GetDays() == timespan.GetDays()
		&& this->GetTimeSpanSeconds() < timespan.GetTimeSpanSeconds())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CTimeSpan::operator > (const CTimeSpan &timespan) const
{
	return (timespan < *this);
}

bool CTimeSpan::operator <= (const CTimeSpan &timespan) const
{
	return !(timespan < *this);
}

bool CTimeSpan::operator >= (const CTimeSpan &timespan) const
{
	return !(*this < timespan);
}

CTimeSpan& CTimeSpan::operator = (const CTimeSpan &timespan)
{
	this->m_nDays = timespan.GetDays();
	this->m_nSeconds = timespan.GetTimeSpanSeconds();
	return *this;
}

BOOL CTimeSpan::_SetTimeSpan(LONG lDays, int nHours, int nMins, int nSecs)
{
	m_nDays = lDays;
	m_nSeconds = (long) nHours * SECOND_PERHOUR + (long) nMins * 60 + (long) nSecs;
	return TRUE;
}

BOOL CTimeSpan::_GetTimeSpan(int &nDay, int &nHour, int &nMin, int &nSec) const
{
	nDay = 0;
	nHour = 0;
	nMin = 0;
	nSec = 0;

	nDay = m_nDays;

	int nOffset = (int)m_nSeconds;

	nHour = nOffset / SECOND_PERHOUR;
	nOffset -= nHour * SECOND_PERHOUR;

	nMin = nOffset / 60;
	nOffset -= nMin * 60;

	nSec = nOffset;

	return TRUE;    
}

std::string CTimeSpan::_GetValue(char cFormat) const
{
	std::string strValue(1, cFormat);

	int nDay, nHour, nMin, nSec;
	string strDay, strHour, strMin, strSec;

	_GetTimeSpan(nDay, nHour, nMin, nSec);

	stringstream ss;

	ss << nDay;
	ss >> strDay;
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

	switch(cFormat)
	{
	case 'd'://
		strValue = strDay;
		break;
	case 'H'://
		strValue = strHour;
		break;
	case 'M'://
		strValue = strMin;
		break;
	case 'S'://
		strValue = strSec;
		break;
	default:
		break;		
	}

	return strValue;
}

BOOL CTimeSpan::SetTimeSpan(long nDays, long nSeconds)
{
	m_nDays = nDays;
	m_nSeconds = nSeconds;
	return TRUE;
}

CString CTimeSpan::Format( LPCSTR pszFormat) const
{
	string   strFormat   =  (string) pszFormat;   
	string   strObject   =   "%"; 

	int nLen = strFormat.length();	
	int nIndex;
	nIndex = strFormat.find(strObject);
	while( nIndex != -1 && nIndex + 1 < nLen)
	{
		char cFormat = strFormat[nIndex + 1];

		string strValue = _GetValue(cFormat);
		if(!strValue.empty())
		{
			strFormat.replace(nIndex, 2, strValue);
		}		

		nIndex = strFormat.find(strObject, nIndex + 1);
		nLen = strFormat.length();
	}
	LPCSTR szResult = strFormat.c_str();
	CString strResult(szResult);

	return strResult;
}

long CTimeSpan::GetTimeSpanSeconds() const
{
	return m_nSeconds;
}

#endif		// end of _WIN32
