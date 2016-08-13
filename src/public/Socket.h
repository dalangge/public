/*******************************************************************************
* 版权所有：	北京市博汇科技有限公司(C) 2013
* 文件名称：	Socket.h
*
* 内容摘要： 	跨平台 SOCKET 
*
--------------------------------------------------------------------------------
* 版本		修改时间		修改人		修改内容
* V1.0		2013/07/06		龚清华		创建
* V1.1		2014/06/20		龚清华		WSAStartup、WSACleanup移动到全局变量中。
*******************************************************************************/
#ifndef _BroadvTool_Socket_H_
#define _BroadvTool_Socket_H_

#include <string>

// windows相关头文件
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

// linux相关头文件、宏
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <unistd.h>

typedef int SOCKET;

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket close
#define ioctlsocket ioctl
#define WSAGetLastError() errno
#endif

namespace BroadvTool
{

/////////////////////////////////// SockAddr ///////////////////////////////////////
class SockAddr
{
public:
	explicit SockAddr(void);
	explicit SockAddr(const std::string & ip, unsigned short port);

	void SetAddr(const sockaddr_in & addr);

	void SetPort(unsigned short port);
	unsigned short GetPort() const;

	void SetIP(const std::string & ip);
	std::string GetIP() const;

private:	
	sockaddr_in m_addr;
};

///////////////////////////////// Socket /////////////////////////////////////////
class Socket
{
public:
	Socket(void);
	Socket(SOCKET s);

	// 析构函数将会关闭 SOCKET，若不想关闭，调用Detach
	virtual ~Socket(void);

	SOCKET Create(int domain = AF_INET, int type = SOCK_DGRAM, int protocol = IPPROTO_IP);

	SOCKET Handle();
	bool IsValid();
	void Attach(SOCKET s);
	void Detach();

	// 关闭方式：0-reading 1-writing 2-both
	void Shutdown(int how);
	void Close();
	
	int Bind(const SockAddr & addr);
	int Listen(int backlog);
	SOCKET Accept(SockAddr * peer = NULL);
	int Connect(const SockAddr & peer);

	int SendTo(const char * buf, int len, const SockAddr & peer);
	int RecvFrom(char * buf, int len, SockAddr * peer = NULL);
	int Send(const char * buf, int len);
	int Recv(char * buf, int len);

	int IoBlocked(bool blocked = false);
	int SetSockOpt(int level, int optname, const char * optval, socklen_t optlen);
	int GetSockOpt( int level, int optname, char * optval, socklen_t * optlen);

	int GetPeerName(SockAddr & peer);
	int GetSockName(SockAddr & addr);

	// 组播相关操作
	int AddMembership(const std::string & multip, const std::string & localip);
	int DropMembership(const std::string & multip, const std::string & localip);

	// SOCKET属性快速设置函数
	int ReuseAddr(bool reuse = true);
	int SetRecvBufSize(int sz);
	int SetSendBufSize(int sz);
	int SetRecvTimeout(int ms);
	int SetSendTimeout(int ms);

protected:
	SOCKET m_hSocket;
};

};	// namespace BroadvTool

#endif //_BroadvTool_Socket_H_

