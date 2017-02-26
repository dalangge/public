
#ifndef	_TIME_H_785432543
#define	_TIME_H_785432543

#ifndef _WIN32

#include "TimeSpan.h"
#include <string>
using   namespace   std; 

class CTime
{
public:
	CTime();
	CTime(const CTime &time);
	CTime(long nDays, long nSec = 0);
    CTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);

    ~CTime();

    static CTime GetCurrentTime();

    int GetYear() const;
    int GetMonth() const;
	int GetDay() const;
	int GetHour() const;
	int GetMinute() const;
	int GetSecond() const;

	int GetDayOfWeek() const;
	
	bool operator < (const CTime &time) const;
	bool operator == (const CTime &time) const;
	bool operator != (const CTime &time) const;
	bool operator <= (const CTime &time) const;
	bool operator >= (const CTime &time) const;
	bool operator > (const CTime &time) const;
	CTime operator + (const CTimeSpan &timeSpan) const;
	CTime operator - (const CTimeSpan &timeSpan) const;
	CTimeSpan operator - (const CTime &time) const;
	CTime& operator = (const CTime &time);	
	
	CString Format( LPCSTR pszFormat) const;

	long GetTotalDays() const;
	long GetTotalSeconds() const;

protected:
	long m_nDays;
	long m_nSeconds;

    BOOL _SetDate(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
	BOOL _SetDate(int nDays, int nSeconds);

    BOOL _GetDate(int &nYear, int &nMonth, int &nDay) const;
    BOOL _GetTime(int &nHour, int &nMin, int &nSec) const;

	string _GetValue(char cFormat) const;
	string _GetDayofWeekAbbrevName(int nDayofWeek) const;
	string _GetDayofWeekFullName(int nDayofWeek) const;
	string _GetMonthAbbrevName(int nMonth) const;
	string _GetMonthFullName(int nMonth)const;

};

#endif		// end of _WIN32

#endif





