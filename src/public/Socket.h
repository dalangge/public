/*******************************************************************************
* ��Ȩ���У�	�����в���Ƽ����޹�˾(C) 2013
* �ļ����ƣ�	Socket.h
*
* ����ժҪ�� 	��ƽ̨ SOCKET 
*
--------------------------------------------------------------------------------
* �汾		�޸�ʱ��		�޸���		�޸�����
* V1.0		2013/07/06		���廪		����
* V1.1		2014/06/20		���廪		WSAStartup��WSACleanup�ƶ���ȫ�ֱ����С�
*******************************************************************************/
#ifndef _BroadvTool_Socket_H_
#define _BroadvTool_Socket_H_

#include <string>

// windows���ͷ�ļ�
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32")
#pragma warning(disable : 4996)

// linux���ͷ�ļ�����
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

	// ������������ر� SOCKET��������رգ�����Detach
	virtual ~Socket(void);

	SOCKET Create(int domain = AF_INET, int type = SOCK_DGRAM, int protocol = IPPROTO_IP);

	SOCKET Handle();
	bool IsValid();
	void Attach(SOCKET s);
	void Detach();

	// �رշ�ʽ��0-reading 1-writing 2-both
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

	// �鲥��ز���
	int AddMembership(const std::string & multip, const std::string & localip);
	int DropMembership(const std::string & multip, const std::string & localip);

	// SOCKET���Կ������ú���
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

