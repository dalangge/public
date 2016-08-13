#include "stdafx.h"
#include "WebServer.h"

#include <algorithm>
#include <string.h>
#include <stdio.h>

#include "Utility.h"
#include "Log.h"

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

namespace BroadvTool
{


// HttpRequest
//////////////////////////////////////////////////////////////////////////
HttpRequest::HttpRequest(const char * method /* = "POST" */,
	const char * uri /* = "/" */,
	const char * version /* = "HTTP/1.0" */)
{
	m_strMethod = method;
	m_strURI = uri;
	m_strVersion = version;
}

bool HttpRequest::Unpack(const std::string & header)
{
	size_t pos = header.find("\r\n\r\n");
	if (pos == std::string::npos)
	{
		return false;
	}

	std::string sss = header.substr(0, pos+4);

	pos = sss.find("\r\n");
	ParseFirstLine(sss.substr(0, pos));

	// 逐行解析
	while (1)
	{
		size_t start = pos + 2;
		pos = sss.find("\r\n", start);
		if (pos == std::string::npos)
		{
			break;
		}

		// 解析单行
		std::string line = sss.substr(start, pos-start);
		size_t pos1 = line.find(":");
		if (pos1 != std::string::npos)
		{
			std::string key = line.substr(0, pos1);
			std::string val = line.substr(pos1+1);
			Line(CUtility::Trim(key), CUtility::Trim(val));
		}
	};

	ParseArgs();
	return true;
}

std::string HttpRequest::Pack()
{
	// first line
	std::string header = m_strMethod + " " + m_strURI + " " + m_strVersion + "\r\n";

	// lines
	HttpHeaderLineMap::const_iterator it = m_mapHeaderLine.begin();
	for ( ; it != m_mapHeaderLine.end(); ++it)
	{
		header += it->first;
		header += ": ";
		header += it->second;
		header += "\r\n";
	}

	// end
	header += "\r\n";
	return header;
}

void HttpRequest::Line(const std::string & key, const std::string & val)
{
	m_mapHeaderLine[CUtility::ToLower(key)] = val;
}

void HttpRequest::Line(const std::string & key, int val)
{
	char buf[64]={0};
	sprintf(buf, "%d", val);
	Line(key, buf);
}

std::string HttpRequest::Line(const std::string & key) const
{
	std::string s = CUtility::ToLower(key);
	HttpHeaderLineMap::const_iterator it = m_mapHeaderLine.find(s);
	if (it != m_mapHeaderLine.end())
	{
		return it->second;
	}
	return "";
}

bool HttpRequest::ParseFirstLine(const std::string & str)
{
	size_t start = 0;
	size_t pos = str.find(" ", start);
	if (pos == std::string::npos)
	{
		return false;
	}
	m_strMethod = str.substr(start, pos-start);

	start = pos + 1;
	pos = str.find(" ", start);
	if (pos == std::string::npos)
	{
		return false;
	}
	m_strURI = str.substr(start, pos-start);

	start = pos + 1;
	m_strVersion = str.substr(start);
	return true;
}

bool HttpRequest::ParseArgs()
{
    size_t pos = m_strURI.find("?");
    if (pos == std::string::npos) {
        m_strURL = m_strURI;
        return true;
    }
    m_strURL = m_strURI.substr(0, pos);
    pos++;

    while(pos < m_strURI.size())
    {
        std::string arg;
        size_t end = m_strURI.find("&", pos);
        if (end == std::string::npos)
        {
            arg = m_strURI.substr(pos);
            pos = m_strURI.size();
        }
        else
        {
            arg = m_strURI.substr(pos, end-pos);
            pos = end+1;
        }

        if (!arg.empty()) {
            size_t pos1 = arg.find("=");
            if (pos1 != std::string::npos)
            {
                std::string key = arg.substr(0, pos1);
                std::string val = arg.substr(pos1+1);
                m_mapArgs[CUtility::Trim(key)] = CUtility::Trim(val);
            }
        }
    }
    return true;
}



// HttpResponse
//////////////////////////////////////////////////////////////////////////
HttpResponse::HttpResponse(int code /* = 200 */,
	const char * msg /* = "OK" */,
	const char * version /* = "HTTP/1.0" */)
{
	m_nStatusCode = code;
	m_strStatusMsg = msg;
	m_strVersion = version;
}

bool HttpResponse::Unpack(const std::string & header)
{
	size_t pos = header.find("\r\n\r\n");
	if (pos == std::string::npos)
	{
		return false;
	}

	std::string sss = header.substr(0, pos+4);

	pos = sss.find("\r\n");
	ParseFirstLine(sss.substr(0, pos));

	// 逐行解析
	while (1)
	{
		size_t start = pos + 2;
		pos = sss.find("\r\n", start);
		if (pos == std::string::npos)
		{
			break;
		}

		// 解析单行
		std::string line = sss.substr(start, pos-start);
		size_t pos1 = line.find(":");
		if (pos1 != std::string::npos)
		{
			std::string key = line.substr(0, pos1);
			std::string val = line.substr(pos1+1);
			Line(CUtility::Trim(key), CUtility::Trim(val));
		}
	};

	return true;
}

std::string HttpResponse::Pack()
{
	// first line
	char buf[64]={0};
	sprintf(buf, "%d", m_nStatusCode);
	std::string header = m_strVersion + " " + buf + " " + m_strStatusMsg + "\r\n";

	// lines
	HttpHeaderLineMap::const_iterator it = m_mapHeaderLine.begin();
	for ( ; it != m_mapHeaderLine.end(); ++it)
	{
		header += it->first;
		header += ": ";
		header += it->second;
		header += "\r\n";
	}

	// end
	header += "\r\n";
	return header;
}

void HttpResponse::Line(const std::string & key, const std::string & val)
{
	m_mapHeaderLine[CUtility::ToLower(key)] = val;
}

void HttpResponse::Line(const std::string & key, int val)
{
	char buf[64]={0};
	sprintf(buf, "%d", val);
	Line(key, buf);
}

std::string HttpResponse::Line(const std::string & key) const
{
	std::string s = CUtility::ToLower(key);
	HttpHeaderLineMap::const_iterator it = m_mapHeaderLine.find(s);
	if (it != m_mapHeaderLine.end())
	{
		return it->second;
	}
	return "";
}

bool HttpResponse::ParseFirstLine(const std::string & str)
{
	size_t start = 0;
	size_t pos = str.find(" ", start);
	if (pos == std::string::npos)
	{
		return false;
	}
	m_strVersion = str.substr(start, pos-start);

	start = pos + 1;
	pos = str.find(" ", start);
	if (pos == std::string::npos)
	{
		return false;
	}
	m_nStatusCode = atoi(str.substr(start, pos-start).c_str());

	start = pos + 1;
	m_strStatusMsg = str.substr(start);
	return true;
}


// ServletHandler
//////////////////////////////////////////////////////////////////////////
ServletHandler::ServletHandler(void)
{
	m_pServlet = NULL;
	m_bIdle = true;
	m_bStop = false;
	Run();
}

ServletHandler::~ServletHandler(void)
{
	Close();
	m_bStop = true;
	Thread::Join(this);
}

bool ServletHandler::Idle() const
{
	return m_bIdle;
}

bool ServletHandler::Start(Servlet * p, SOCKET s)
{
	Attach(s);
	m_pServlet = p;
	m_bIdle = false;
	return true;
}

bool ServletHandler::SendResponse(HttpResponse & response)
{
	if (SendN(response.Pack()) && SendN(response.m_strBody))
	{
		return true;
	}
	Log_Error("send response error! err=%d, msg=%s", WSAGetLastError(), response.Pack().c_str());
	return false;
}

void ServletHandler::Routine()
{
	while (!m_bStop)
	{
		if (m_bIdle)
		{
			Thread::Sleep(1);
			continue;
		}

		IOHandler();
		Close();
		m_bIdle = true;
	}
}

bool ServletHandler::IOHandler()
{
	std::string strCache;
	bool bHeaderCompleted = false;
	int nContentLength = 0;
	HttpRequest request;

	while (!m_bStop)
	{
		bool bAnother = !strCache.empty() && !bHeaderCompleted && strCache.find("\r\n\r\n") != std::string::npos;
		if (!bAnother)
		{
			char buf[4096]={0};
			int ret = Recv(buf, 4096);
			if (ret <= 0)
			{
				break;
			}
			strCache.append(buf, ret);
		}
		
		if (!bHeaderCompleted)
		{
			size_t pos = strCache.find("\r\n\r\n");
			if (pos != std::string::npos)
			{
				request.Unpack(strCache);
				strCache.erase(0, pos+4);

				bHeaderCompleted = true;
				nContentLength = atoi(request.Line("Content-Length").c_str());
			}
		}

		// 一次HTTP请求接收完成
		if (bHeaderCompleted && (int)strCache.size() >= nContentLength)
		{
			request.m_strBody = strCache.substr(0, nContentLength);

			HttpResponse response;
			int n = m_pServlet->OnService(request, response, *this);

			// 发送应答
			if (n & ServletReturnType_SendResponse)
			{
				if (!SendResponse(response))
				{
					break;
				}
			}

			// 保持连接
			if (n & ServletReturnType_KeepAlive)
			{
				strCache.erase(0, nContentLength);
				bHeaderCompleted = false;
				nContentLength = 0;
				HttpRequest temp;
				request = temp;

				continue;
			}

			break;;				
		}
	}
	return true;
}

bool ServletHandler::SendN(const std::string & str)
{
	size_t pos = 0;
	while (pos < str.size())
	{
		int ret = Send(&str[pos], (int)(str.size()-pos));
		if (ret <= 0)
		{
			return false;
		}
		pos += ret;
	}
	return true;
}


// WebServer
//////////////////////////////////////////////////////////////////////////
WebServer::WebServer(size_t nMaxThread /* = 8 */)
{
	m_nMaxThread = nMaxThread;
	m_bStop = false;
}

WebServer::~WebServer(void)
{
}

bool WebServer::Start(const std::string & strIP, int nPort)
{
	Log_Debug("WebServer start listen! <%s:%d>", strIP.c_str(), nPort);

	if (Create(AF_INET, SOCK_STREAM, IPPROTO_IP) == INVALID_SOCKET
		|| ReuseAddr(true) == INVALID_SOCKET
		|| Bind(SockAddr(strIP, nPort)) == INVALID_SOCKET
		|| Listen(10) == INVALID_SOCKET)
	{
		Log_Error("WebServer init socket error! err=r=%d", WSAGetLastError());
		return false;
	}

	m_bStop = false;
	return Run()==0;
}

void WebServer::Stop()
{
	m_bStop = true;
	Thread::Join(this);
	Close();

	for (size_t i = 0; i < m_vecHandler.size(); ++i)
	{
		delete m_vecHandler[i];
	}
	m_vecHandler.clear();
}

void WebServer::Routine()
{
	while (!m_bStop)
	{
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(m_hSocket, &fds);

		timeval tv = {0, 500*1000};
		if (select((int)m_hSocket+1, &fds, NULL, NULL, &tv) < 0)
		{
			Log_Error("WebServer select failed! err=%d", WSAGetLastError());
			break;
		}

		if (!FD_ISSET(m_hSocket, &fds))
			continue;

		OnAccept();

	}	// end of while()
}

bool WebServer::JoinThread(Servlet * p, SOCKET s)
{
	for (size_t i = 0; i < m_vecHandler.size(); ++i)
	{
		ServletHandler * pHandler = m_vecHandler[i];
		if (pHandler->Idle())
		{
			pHandler->Start(p, s);
			return true;
		}
	}

	// 线程池已经达到最大限度
	if (m_vecHandler.size() >= m_nMaxThread)
	{
		return false;
	}

	// 创建一个新的线程
	ServletHandler * pHandler = new ServletHandler;
	pHandler->Start(p, s);
	m_vecHandler.push_back(pHandler);
	return true;
}


// HttpClientSocket
//////////////////////////////////////////////////////////////////////////
HttpClientSocket::HttpClientSocket(const char * pURL, const char * pMethod /* = "POST"*/)
{
	const std::string str(pURL);
	if (str.size() > 7 && CUtility::ToLower(str.substr(0, 7)) == "http://")
	{
		std::string strHost, strURI;

		size_t pos = str.find('/', 7);
		if (pos != std::string::npos)
		{
			strHost = str.substr(7, pos-7);
			strURI = str.substr(pos);
		}
		else
		{
			strHost = str.substr(7);
			strURI  = "/";			
		}

		// parse server address
		std::string strIP = strHost;
		int nPort = 80;
		pos = strHost.find(":");
		if (pos != std::string::npos)
		{
			strIP = strHost.substr(0, pos);
			nPort = atoi(strHost.substr(pos+1).c_str());
		}

		m_addrSrv = SockAddr(strIP, nPort);

		m_request.m_strMethod = pMethod;
		m_request.m_strURI = strURI;

		char buf[64]={0};
		sprintf(buf, "%s:%d", strIP.c_str(), nPort);
		m_request.Line("Host", buf);
	}
}

HttpClientSocket::~HttpClientSocket(void)
{

}

HttpRequest & HttpClientSocket::Request()
{
	return m_request;
}

const HttpResponse & HttpClientSocket::Response()
{
	return m_response;
}

// 返回值true，body内容将不被m_response保存
bool HttpClientSocket::OnBody(const char * buf, size_t len)
{
	return false;
}

bool HttpClientSocket::IOHandler()
{
	if (!IsValid() && Create(AF_INET, SOCK_STREAM, IPPROTO_IP) == INVALID_SOCKET)
	{
		Log_Error("HttpSocket -- create socket error! err=%d", WSAGetLastError());
		return false;
	}

	if (Connect(m_addrSrv) == INVALID_SOCKET)
	{
		Log_Error("HttpSocket -- connect error! err=%d", WSAGetLastError());
		return false;
	}
	
	if (!SendRequest())
	{
		Log_Error("HttpSocket -- send request error! err=%d", WSAGetLastError());
		return false;
	}

	if (!RecvResponse())
	{
		Log_Error("HttpSocket -- recv response error! err=%d", WSAGetLastError());
		return false;
	}
	return true;
}

bool HttpClientSocket::SendRequest()
{
	if (SendN(m_request.Pack()) && SendN(m_request.m_strBody))
	{
		return true;
	}
	Log_Error("send request error! err=%d, msg=%s", WSAGetLastError(), m_request.Pack().c_str());
	return false;
}

bool HttpClientSocket::SendN(const std::string & str)
{
	size_t pos = 0;
	while (pos < str.size())
	{
		int ret = Send(&str[pos], (int)(str.size()-pos));
		if (ret <= 0)
		{
			return false;
		}
		pos += ret;
	}
	return true;
}

bool HttpClientSocket::RecvResponse()
{
	std::string strCache;
	while (1)
	{
		char buf[4096]={0};
		int ret = Recv(buf, 4096);
		if (ret <= 0)
		{
			return false;
		}

		strCache.append(buf, ret);
		size_t pos = strCache.find("\r\n\r\n");
		if (pos == std::string::npos)
		{
			continue;
		}

		// 头部收齐
		m_response.Unpack(strCache);
		strCache.erase(0, pos+4);

		long long nRecv = (long long)strCache.size();
		long long nContentLength = (long long)atof(m_response.Line("Content-Length").c_str());
		long long n = min(nRecv, nContentLength);

		if (!OnBody(strCache.data(), (int)n))
		{
			m_response.m_strBody.append(strCache.begin(), strCache.begin()+(int)n);
		}

		// 收齐 Content-Length
		while (nRecv < nContentLength)
		{
			ret = Recv(buf, 4096);
			if (ret <= 0)
			{
				return false;
			}

			n = min(nContentLength-nRecv, ret);
			if (!OnBody(buf, (int)n))
			{
				m_response.m_strBody.append(buf, (int)n);
			}
			nRecv += n;
		}
		return true;
	}
}


};	// namespace BroadvTool
