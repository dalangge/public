/*******************************************************************************
* ��Ȩ���У�	�����в���Ƽ����޹�˾(C) 2013
* �ļ����ƣ�	Log.h 
*
* ����ժҪ�� 	��־�࣬д�ļ���STD���
*
--------------------------------------------------------------------------------
* �汾		�޸�ʱ��		�޸���		�޸�����
* V1.0		2013/08/30		���廪		����
*******************************************************************************/
#ifndef _BroadvTool_Utility_H_
#define _BroadvTool_Utility_H_

#include <string>

namespace BroadvTool
{

class CUtility
{
public:
	// ��ȡ��ǰϵͳʱ��
	static void GetLocalTime(struct tm * t);

	// ��ȡ��ǰ��ʽ��ϵͳʱ�� "2014-01-01 01:01:01"
	static std::string GetFormatLocalTime();

public:
	static std::string ToUpper(const std::string & str);
	static std::string ToLower(const std::string & str);
	static std::string & Trim(std::string & str);

	// ���ر��滻�ַ����ĸ���
	static int Replace(std::string & str, const std::string & find, const std::string & replacement);

	// str1-Դ�ַ����� str2-��ͨ���"*"���ַ���
	static bool Wildcard(const char *str1, const char *str2);

	static void Gbk2Utf(const char * buf, int len, std::string & str);
	static void Utf2Gbk(const char * buf, int len, std::string & str);

public:

};

};	// namespace BroadvTool

#endif

