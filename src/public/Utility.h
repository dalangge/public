/*******************************************************************************
* 版权所有：	北京市博汇科技有限公司(C) 2013
* 文件名称：	Log.h 
*
* 内容摘要： 	日志类，写文件和STD输出
*
--------------------------------------------------------------------------------
* 版本		修改时间		修改人		修改内容
* V1.0		2013/08/30		龚清华		创建
*******************************************************************************/
#ifndef _BroadvTool_Utility_H_
#define _BroadvTool_Utility_H_

#include <string>

namespace BroadvTool
{

class CUtility
{
public:
	// 获取当前系统时间
	static void GetLocalTime(struct tm * t);

	// 获取当前格式化系统时间 "2014-01-01 01:01:01"
	static std::string GetFormatLocalTime();

public:
	static std::string ToUpper(const std::string & str);
	static std::string ToLower(const std::string & str);
	static std::string & Trim(std::string & str);

	// 返回被替换字符串的个数
	static int Replace(std::string & str, const std::string & find, const std::string & replacement);

	// str1-源字符串， str2-带通配符"*"的字符串
	static bool Wildcard(const char *str1, const char *str2);

	static void Gbk2Utf(const char * buf, int len, std::string & str);
	static void Utf2Gbk(const char * buf, int len, std::string & str);

public:

};

};	// namespace BroadvTool

#endif

