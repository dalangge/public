#include "stdafx.h"
#include "Utility.h"

#include <string.h>
#include <stdio.h>
#include <algorithm>

#ifdef _WIN32
#pragma warning(disable : 4996)
#else
#include <iconv.h>
#endif

namespace BroadvTool
{


void CUtility::GetLocalTime(struct tm * t)
{
#ifdef _WIN32
	__time64_t timep = _time64(0);
	_localtime64_s(t, &timep);
#else
	time_t timep = time(0);
	localtime_r(&timep, t);
#endif
}

std::string CUtility::GetFormatLocalTime()
{
	struct tm  t;
	GetLocalTime(&t);
	char buf[32]={0};
	sprintf(buf, "%04d-%02d-%02d %02d:%02d:%02d",
		t.tm_year+1900, t.tm_mon+1, t.tm_mday,
		t.tm_hour, t.tm_min, t.tm_sec);
	return buf;
}

std::string CUtility::ToUpper(const std::string & str)
{
	std::string s(str);
	std::transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

std::string CUtility::ToLower(const std::string & str)
{
	std::string s(str);
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string & CUtility::Trim(std::string & str)
{
	if (!str.empty())
	{
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" ")+1);
	}
	return str;
}

int CUtility::Replace(std::string & str, const std::string & find, const std::string & replacement)
{
	int n = 0;
	for (size_t pos = 0; pos != std::string::npos; pos += replacement.size())
	{
		pos = str.find(find, pos);
		if (pos != std::string::npos)
		{
			++n;
			str.replace(pos, find.size(), replacement);
		}
		else
		{
			break;
		}
	}
	return n;
}

bool CUtility::Wildcard(const char *str1, const char *str2)
{
    size_t iLen1 = strlen(str1);
	size_t iLen2 = strlen(str2);
	size_t i=0, j=0, k=0, l , m , n;  

    for(l=0 , n=0; l<iLen2; l++)
	{
		if(str2[l]!='*')n=l; 
	}

	while(i<iLen1&&j<iLen2)
	{	
        while(j<iLen2)										//
		{													//
			if(str2[j]=='*')	{ k=1;  j++;}				//	
			else	{ l=j; m=i; break; }					//			
		}													//
        
		while(i<iLen1&&j<iLen2)								//				
		{													//	
			if(str2[j]=='*')break;							//
			//		
			if(str1[i]==str2[j]||str2[j]=='?'){i++;j++;}	//
			else											//
			{												//
				if(k==1){m++; i=m; j=l;}					//	
				else return false;							//
			}												//	
		}													//
        
		if(i<iLen1&&j==iLen2&&str2[j-1]!='*'&&k==1){m++; i=m; j=l;}
	}

    if((i==iLen1&&n+1==j)||((i<iLen1)&&j!=0&&str2[j-1]=='*'))
        return true;
	else
		return false;
}

#ifdef _WIN32
void Converter(const char * buf, int len, std::string & str, int srccode, int dstcode)
{
	int n1 = MultiByteToWideChar(srccode, 0, buf, len, NULL, 0);
	WCHAR * p1 = new WCHAR[n1+1];
	MultiByteToWideChar(srccode, 0, buf, len, p1, n1);

    int n2 = WideCharToMultiByte(dstcode, 0, p1, n1, NULL, 0, NULL, NULL);
	char * p2 = new char[n2+1];
	WideCharToMultiByte(dstcode, 0, p1, n1, p2, n2, NULL, NULL);

	str.clear();
	str.append(p2, n2);
	delete [] p1;
	delete [] p2;
}
#else
void Converter(const char * buf, int len, std::string & str, const char * srccode, const char * dstcode)
{
	iconv_t cd =  iconv_open(dstcode, srccode);
	if (cd == (iconv_t)-1)
	{
		return;
	}

	size_t sz = len*2+1;
	char * p = new char[sz];
	do 
	{
		char * pin = (char *)buf;
		char * pout = p;
		size_t inlen = len, outlen = sz;
		if (iconv(cd,&pin,&inlen,&pout,&outlen)==(size_t)-1)
		{
			break;
		}

		str.clear();
		str.append(p, sz-outlen);

	} while (0);
	iconv_close(cd);
	delete [] p;
}
#endif

void CUtility::Gbk2Utf(const char * buf, int len, std::string & str)
{
#ifdef _WIN32
	Converter(buf, len, str, CP_ACP, CP_UTF8);
#else
	Converter(buf, len, str, "gbk", "utf-8");
#endif
}

void CUtility::Utf2Gbk(const char * buf, int len, std::string & str)
{
#ifdef _WIN32
	Converter(buf, len, str, CP_UTF8, CP_ACP);
#else
	Converter(buf, len, str, "utf-8", "gbk");
#endif
}

};	// namespace BroadvTool
