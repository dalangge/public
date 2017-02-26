/*
 Copyright (c) 2017 Brother Wolf
 
 A common c/c++ tool code.
 
 */

#ifndef _BroadvTool_WebServer_H_
#define _BroadvTool_WebServer_H_

#include <map>
#include <vector>

#include "Socket.h"
#include "Thread.h"

namespace BroadvTool
{

typedef std::map<std::string, std::string> HttpHeaderLineMap;

// HttpRequest
struct HttpRequest
{
	std::string m_strMethod;
	std::string m_strURI;
	std::string m_strVersion;
	HttpHeaderLineMap m_mapHeaderLine;
	std::string m_strBody;
	std::string m_strURL;
	HttpHeaderLineMap m_mapArgs;

	HttpRequest(const char * method = "POST", const char * uri = "/", const char * version = "HTTP/1.0");

	bool Unpack(const std::string & header);
	std::string Pack();

	void Line(const std::string & key, const std::string & val);
	void Line(const std::string & key, int val);
	std::string Line(const std::string & key) const;

	bool ParseFirstLine(const std::string & str);
	bool ParseArgs();
};


// HttpResponse
struct HttpResponse
{
	int m_nStatusCode;
	std::string m_strStatusMsg;
	std::string m_strVersion;
	HttpHeaderLineMap m_mapHeaderLine;
	std::string m_strBody;

	HttpResponse(int code = 200, const char * msg = "OK", const char * version = "HTTP/1.0");

	bool Unpack(const std::string & header);
	std::string Pack();

	void Line(const std::string & key, const std::string & val);
	void Line(const std::string & key, int val);
	std::string Line(const std::string & key) const;

	bool ParseFirstLine(const std::string & str);
};


class ServletHandler;

enum ServletReturnType
{
	ServletReturnType_SendResponse	= 0x01,
	ServletReturnType_KeepAlive		= 0x02,
};


// Servlet
class Servlet
{
public:
	virtual ~Servlet(void){}

	// refer to enum ServletReturnType
	virtual int OnService(const HttpRequest & request, HttpResponse & response, ServletHandler & handler) = 0;
};


// ServletHandler
class ServletHandler : public Socket, public Thread
{
public:
	ServletHandler(void);
	virtual ~ServletHandler(void);

	bool Idle() const;
	bool Start(Servlet * p, SOCKET s);

	bool SendResponse(HttpResponse & response);

protected:
	virtual void Routine();
	bool IOHandler();
	bool SendN(const std::string & str);

private:
	bool m_bIdle;
	bool m_bStop;
	Servlet * m_pServlet;
};


// WebServer
class WebServer : public Socket, public Thread
{
public:
	WebServer(size_t nMaxThread = 8);
	virtual ~WebServer(void);

	bool Start(const std::string & strIP, int nPort);
	void Stop();

	virtual void OnAccept() = 0;

protected:
	virtual void Routine();
	bool JoinThread(Servlet * p, SOCKET s);

private:
public:
	bool m_bStop;
	size_t m_nMaxThread;
	std::vector<ServletHandler*> m_vecHandler;
};


// HttpClientSocket
class HttpClientSocket : public Socket
{
public:
	HttpClientSocket(const char * pURL, const char * pMethod = "POST");
	virtual ~HttpClientSocket(void);

	HttpRequest & Request();
	const HttpResponse & Response();

	//  return true, the body data will not append to m_response
	virtual bool OnBody(const char * buf, size_t len);

	bool IOHandler();

protected:
	bool SendRequest();
	bool SendN(const std::string & str);
	bool RecvResponse();

private:
	HttpRequest m_request;
	HttpResponse m_response;
	SockAddr m_addrSrv;	
};


};	// namespace BroadvTool


#endif	// _BroadvTool_WebServer_H_
