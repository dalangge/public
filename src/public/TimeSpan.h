/*******************************************************************************
* ��Ȩ���� (C) 2007
* 
* �ļ����ƣ� timespan.h
* �ļ���ʶ�� 
* ����ժҪ�� 
* ����˵���� ������MFC��CTimeSpan����
* ��ǰ�汾�� V1.0
* ��    �ߣ� ˾����
* ������ڣ� 2007-12-05
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

	//���캯��
	CTimeSpan();

	//�������캯��
	CTimeSpan(const CTimeSpan &timespan);

	//���캯��
	CTimeSpan(const long nSec);

	//���캯��
	CTimeSpan(long nDays, long nSecs);

	//���캯������������Ϊʱ�������ա�ʱ���֡���ֵ
	CTimeSpan(LONG lDays,	//ʱ������ֵ 0-24800(Լ)
		int nHours,			//ʱ����ʱֵ 0-23
		int nMins,			//ʱ������ֵ 0-59
		int nSecs);			//ʱ������ֵ 0-59

	//��������
	~CTimeSpan();
	
	//��ȡʱ����ռ���
	long GetDays() const;

	//��ȡʱ���ʱ����
	long GetHours() const;
	
	//��ȡʱ��������ʱ��
	long GetTotalHours() const;

	//��ȡʱ��ķּ���
	long GetMinutes() const;

	//��ȡʱ�������ܷ���
	long GetTotalMinutes() const;

	//��ȡʱ��������
	long GetSeconds() const;

	//��ȡʱ������������
	long GetTotalSeconds() const;
	
	// == ��������� 
	bool operator == (const CTimeSpan &span) const ;

	// != ��������� 
	bool operator != (const CTimeSpan &span) const ;

	// < ��������� 
	bool operator < (const CTimeSpan &span) const ;

	// > ��������� 
	bool operator > (const CTimeSpan &span) const ;

	// <= ��������� 
	bool operator <= (const CTimeSpan &span) const ;

	// >= ��������� 
	bool operator >= (const CTimeSpan &span) const ;

	// = ��������� 
	CTimeSpan& operator = (const CTimeSpan &timespan);

	//ʱ���ʽ��Ϊ�ַ���
	CString Format( LPCSTR pszFormat) const;

	//��ȡʱ��������ֵ
	long GetTimeSpanSeconds() const;

	//����ʱ����
	BOOL SetTimeSpan(long nDays, long nSeconds);

protected:
	//ʱ�����������
	long m_nSeconds;

	//ʱ�������ռ���
	long m_nDays;

	//����ʱ��������������Ϊʱ�������ա�ʱ���֡���ֵ
	BOOL _SetTimeSpan(LONG lDays, int nHours, int nMins, int nSecs);

	//��ȡʱ����
	BOOL _GetTimeSpan(
		int &nDay,				//��
		int &nHour,				//ʱ
		int &nMin,				//��
		int &nSec				//��
		) const;

	//���ݸ�ʽ�ַ���ȡ��ʽֵ
	std::string _GetValue(char cFormat) const;

	
};

#endif		// end of _WIN32

#endif

