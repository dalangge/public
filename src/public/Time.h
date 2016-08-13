/*******************************************************************************
* ��Ȩ���� (C) 2007
* 
* �ļ����ƣ� time.h
* �ļ���ʶ�� 
* ����ժҪ��  
* ����˵���� ������MFC��CTime���ƣ���Чʱ�䷶Χ��1900-1-1 0:0:0����2100-12-31 12:59:59
* ��ǰ�汾�� V1.0
* ��    �ߣ� ˾����
* ������ڣ� 2007-12-05
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
	//���캯��
	CTime();

	//�������캯��
	CTime(const CTime &time);

	//���캯��
	CTime(
		long nDays,		//ʱ��ֵ���1900��1��1�յ�������
		long nSec = 0	//ʱ��ֵ���00��00��00 ��������
		);

	//���캯��
	CTime(
		int nYear,		//��Ԫ������� 1900-2100
		int nMonth,		//��Ԫ������� 1-12
		int nDay,		//��Ԫ������� 1-31
		int nHour,		//ʱ0-23
		int nMin,		//��0-59
		int nSec);		//��0-59
	
	//��������
	~CTime();

	//��ȡϵͳ��ǰʱ��
	static CTime GetCurrentTime();

	//��ȡʱ��ֵ�Ĺ�Ԫ�������ֵ
	int GetYear() const;

	//��ȡʱ��ֵ�ù�Ԫ�������ֵ
	int GetMonth() const;

	//��ȡʱ��ֵ�Ĺ�Ԫ�������ֵ
	int GetDay() const;

	//��ȡʱ��ֵ�Ĺ�Ԫ�����ʱֵ
	int GetHour() const;

	//��ȡʱ��ֵ�Ĺ�Ԫ����ķ�ֵ
	int GetMinute() const;

	//��ȡʱ��ֵ�Ĺ�Ԫ�������ֵ
	int GetSecond() const;

	//��ȡʱ��ֵ�����ڼ�
	int GetDayOfWeek() const;
	
	// < ��������� 
	bool operator < (const CTime &time) const;

	// == ��������� 
	bool operator == (const CTime &time) const;

	// != ��������� 
	bool operator != (const CTime &time) const;

	// <= ��������� 
	bool operator <= (const CTime &time) const;

	// >= ��������� 
	bool operator >= (const CTime &time) const;

	// > ��������� 
	bool operator > (const CTime &time) const;

	// + ��������� 
	CTime operator + (const CTimeSpan &timeSpan) const;

	// - ��������� 
	CTime operator - (const CTimeSpan &timeSpan) const;

	// - ��������� 
	CTimeSpan operator - (const CTime &time) const;

	// = ��������� 
	CTime& operator = (const CTime &time);	
	
	//ʱ���ʽ��Ϊ�ַ���
	CString Format( LPCSTR pszFormat) const;

	//��ȡ���1900��1��1�յ�ʱ������
	long GetTotalDays() const;

	//��ȡ���00��00��00 ��ʱ������
	long GetTotalSeconds() const;

protected:

	//ʱ��ֵ���1900��1��1�յ�������
	long m_nDays;

	//ʱ��ֵ���00��00��00 ��������
	long m_nSeconds;

	//����ʱ��ֵ
	BOOL _SetDate(
		int nYear,				//��Ԫ������� 1900-2100
		int nMonth,				//��Ԫ������� 1-12
		int nDay,				//��Ԫ������� 1-31
		int nHour,				//ʱ0-23
		int nMin,				//��0-59
		int nSec);				//��0-59

	//����ʱ��ֵ
	BOOL _SetDate(
		int nDays,				//���1900��1��1�յ�������
		int nSeconds);			//���00��00��00 ��������

	//��ȡ���� 
	BOOL _GetDate(
		int &nYear,				//��Ԫ�������
		int &nMonth,			//��Ԫ�������
		int &nDay				//��Ԫ�������
		) const;	

	//��ȡʱ��
	BOOL _GetTime(
		int &nHour,				//ʱ
		int &nMin,				//��
		int &nSec				//��
		) const;

	//���ݸ�ʽ�ַ���ȡ��ʽֵ
	string _GetValue(char cFormat) const;

	//�������ڼ���ȡ������д
	string _GetDayofWeekAbbrevName(int nDayofWeek) const;

	//�������ڼ���ȡ����ȫ��
	string _GetDayofWeekFullName(int nDayofWeek) const;

	//���ݼ��»�ȡ����д
	string _GetMonthAbbrevName(int nMonth) const;

	//���ݼ��»�ȡ��ȫ��
	string _GetMonthFullName(int nMonth)const;

};

#endif		// end of _WIN32

#endif





