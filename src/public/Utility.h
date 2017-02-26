/*
 Copyright (c) 2017 Brother Wolf
 
 A common c/c++ tool code.
 
 */

#ifndef _BroadvTool_Utility_H_
#define _BroadvTool_Utility_H_

#include <string>

namespace BroadvTool
{

class CUtility
{
public:
    static void GetLocalTime(struct tm * t);

	// eg: "2014-01-01 01:01:01"
	static std::string GetFormatLocalTime();

public:
	static std::string ToUpper(const std::string & str);
	static std::string ToLower(const std::string & str);
	static std::string & Trim(std::string & str);

	// return the count be replaced
	static int Replace(std::string & str, const std::string & find,
                       const std::string & replacement);

	// str2 is the wildcard string, eg: "abc*"
	static bool Wildcard(const char *str1, const char *str2);

	static void Gbk2Utf(const char * buf, int len, std::string & str);
	static void Utf2Gbk(const char * buf, int len, std::string & str);

public:

};

};	// namespace BroadvTool

#endif

