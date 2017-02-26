
#ifndef _TIME_SPAN_H_78R789493289148932819452839KFLDKL
#define _TIME_SPAN_H_78R789493289148932819452839KFLDKL


#ifndef _WIN32

#include "typedef.h"
#include <string>
#include "String.h"

class CTimeSpan
{
public:
	CTimeSpan();
	CTimeSpan(const CTimeSpan &timespan);
	CTimeSpan(const long nSec);
	CTimeSpan(long nDays, long nSecs);
	CTimeSpan(LONG lDays,
              int nHours,
              int nMins,
              int nSecs);
    
	~CTimeSpan();
	
    long GetDays() const;
	long GetHours() const;
	long GetTotalHours() const;
	long GetMinutes() const;
	long GetTotalMinutes() const;
	long GetSeconds() const;
	long GetTotalSeconds() const;
	
	bool operator == (const CTimeSpan &span) const ;
	bool operator != (const CTimeSpan &span) const ;
	bool operator < (const CTimeSpan &span) const ;
	bool operator > (const CTimeSpan &span) const ;
	bool operator <= (const CTimeSpan &span) const ;
	bool operator >= (const CTimeSpan &span) const ;
	CTimeSpan& operator = (const CTimeSpan &timespan);

	CString Format( LPCSTR pszFormat) const;

	long GetTimeSpanSeconds() const;

	BOOL SetTimeSpan(long nDays, long nSeconds);

protected:
	long m_nSeconds;
	long m_nDays;

    BOOL _SetTimeSpan(LONG lDays, int nHours, int nMins, int nSecs);

    BOOL _GetTimeSpan(
                      int &nDay,
                      int &nHour,
                      int &nMin,
                      int &nSec
                      ) const;

	std::string _GetValue(char cFormat) const;
	
};

#endif		// end of _WIN32

#endif

