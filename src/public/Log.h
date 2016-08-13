/*******************************************************************************
* ��Ȩ���У�	�����в���Ƽ����޹�˾(C) 2013
* �ļ����ƣ�	Log.h 
*
* ����ժҪ�� 	��־�࣬д�ļ���STD���
*
--------------------------------------------------------------------------------
* �汾		�޸�ʱ��		�޸���		�޸�����
* V1.0		2013/08/30		���廪		����
* V1.1		2014/09/30		���廪		����CLogSrv�ȼ������CLog����
* V1.2		2015/07/27		���廪		����Log��ʽ������������������vsnprintf
*******************************************************************************/
#ifndef _BroadvTool_Log_H_
#define _BroadvTool_Log_H_

#include <string>
#include <vector>
#include "Thread.h"

#include <stdio.h>
#include <stdarg.h>

namespace BroadvTool
{

class CLogSrv : public Thread
{
	typedef std::vector<std::string> MsgVec;

public:
	CLogSrv();
	virtual ~CLogSrv();

	// dir β������'\\'��'/'
	void SetDir(const std::string & dir);
	
	// ��� <= level ����־
	void SetLevel(unsigned int level = 3);
	unsigned int GetLevel() const;

	// ���� ��p��printf/f-file��
	void Enable(bool p, bool f);

	// д��־
	void WriteLog(unsigned int level, const char * buf);

	// ��ʽ��д��־����ע�⣺�ڴ����� 4096��
	void FormatLog(unsigned int level, const char * fmt, ...);

private:
	virtual void Routine();

private:
	bool m_bStop;

	Mutex m_cs;
	MsgVec m_vecMsg;

	std::string m_strDir;
	bool m_bPrint, m_bFile;

	unsigned int m_nLevel;
};


// Ĭ����־������
extern CLogSrv g_DefaultLogSrv;


// ��־����
class CLogObj
{
public:
	CLogObj(unsigned int level) : m_nLevel(level) {}
	~CLogObj() {}

	void operator()(const char * fmt, ...) const
	{
		if (m_nLevel > g_DefaultLogSrv.GetLevel())
			return;

		char buf[4096]={0};
		va_list ptr; 
		va_start(ptr, fmt);
		//vsprintf(buf, fmt, ptr); 
		vsnprintf(buf, 4096, fmt, ptr); 
		va_end(ptr);
		g_DefaultLogSrv.WriteLog(m_nLevel, buf);
	}

private:
	unsigned int m_nLevel;
};

#define Log_Debug	CLogObj(3)
#define Log_Warning	CLogObj(2)
#define Log_Error	CLogObj(1)

//#define Log_Debug	g_DefaultLogSrv.FormatLog
//#define Log_Warning	g_DefaultLogSrv.FormatLog
//#define Log_Error	g_DefaultLogSrv.FormatLog


};	// namespace BroadvTool

#endif	// _BroadvTool_UdpSrv_H_
