#include "stdafx.h"
#include "Socket.h"

#include <string.h>

namespace BroadvTool
{

////////////////////////////////// SockAddr ////////////////////////////////////////
SockAddr::SockAddr(void)
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = INADDR_ANY;
	m_addr.sin_port = 0;
}

SockAddr::SockAddr(const std::string & ip, unsigned short port)
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
	m_addr.sin_port = htons(port);
}

void SockAddr::SetAddr(const sockaddr_in & addr)
{
	memcpy(&m_addr, &addr, sizeof(m_addr));
}

unsigned short SockAddr::GetPort() const
{
	return ntohs(m_addr.sin_port);
}

void SockAddr::SetPort(unsigned short port)
{
	 m_addr.sin_port = htons(port);
}

void SockAddr::SetIP(const std::string & ip)
{
	m_addr.sin_addr.s_addr = ip.empty() ? INADDR_ANY : inet_addr(ip.c_str());
}

std::string SockAddr::GetIP() const
{
	return std::string(inet_ntoa(m_addr.sin_addr));
}


/////////////////////////////////// Socket ///////////////////////////////////////
Socket::Socket(void)
: m_hSocket(INVALID_SOCKET)
{
	// windowsœ¬º”‘ÿWinSockø‚
#ifdef _WIN32
	class InitWinSockLib
	{
	public:
		InitWinSockLib() {WSADATA w; ::WSAStartup(MAKEWORD(2,2), &w);}
		~InitWinSockLib() {	::WSACleanup(); }
	};
	static InitWinSockLib g_InitWinSockLib;
#endif
}

Socket::Socket(SOCKET s)
: m_hSocket(s)
{
}

Socket::~Socket(void)
{
	Close();
}

SOCKET Socket::Create(int domain /* = AF_INET */, int type /* = SOCK_DGRAM */, int protocol /* = IPPROTO_IP */)
{
	SOCKET s = socket(domain, type, protocol);
	if (s == INVALID_SOCKET)
		return s;

	Attach(s);
	return s;
}

SOCKET Socket::Handle()
{
	return m_hSocket;
}

bool Socket::IsValid()
{
	return m_hSocket != INVALID_SOCKET;
}

void Socket::Attach(SOCKET s)
{
	m_hSocket = s;
}

void Socket::Detach()
{
	Attach(INVALID_SOCKET);
}

void Socket::Shutdown(int how)
{
	if (!IsValid())
		return;
	shutdown(m_hSocket, how);
}

void Socket::Close()
{
	if (!IsValid())
		return;
	closesocket(m_hSocket);
	m_hSocket = INVALID_SOCKET;
}

int Socket::Bind(const SockAddr & addr)
{
	socklen_t len = sizeof(addr);
	return bind(m_hSocket, (struct sockaddr *)&addr, len);
}

int Socket::Listen(int backlog)
{
	return listen(m_hSocket, backlog);
}

SOCKET Socket::Accept(SockAddr * peer /* = NULL */)
{
	SockAddr addr;
	socklen_t len = sizeof(addr);
	SOCKET s = accept(m_hSocket, (struct sockaddr *)&addr, &len);
	if (peer != NULL)
		memcpy(peer, &addr, sizeof(addr));
	return s;
}

int Socket::Connect(const SockAddr & peer)
{
	socklen_t len = sizeof(peer);
	return connect(m_hSocket, ( struct sockaddr * )&peer, len);
}

int Socket::SendTo(const char * buf, int len, const SockAddr & peer)
{
	return sendto(m_hSocket, buf, len, 0, (struct sockaddr *)&peer, sizeof(peer));
}

int Socket::RecvFrom(char * buf, int len, SockAddr * peer /* = NULL */)
{
	SockAddr addr;
	socklen_t addr_len = sizeof(addr);
	int n = recvfrom(m_hSocket, buf, len, 0, (struct sockaddr *)&addr, &addr_len);
	if (peer != NULL)
		memcpy(peer, &addr, sizeof(addr));
	return n;
}

int Socket::Send(const char * buf, int len)
{
	return send(m_hSocket, (char*)buf, len, 0);
}

int Socket::Recv(char * buf, int len)
{
	return recv(m_hSocket, (char*)buf, len, 0);
}

int Socket::IoBlocked(bool blocked /* = false */)
{
	unsigned long n = blocked ? 0 : 1;
	return ioctlsocket(m_hSocket, FIONBIO, &n);
}

int Socket::SetSockOpt(int level, int optname, const char * optval, socklen_t optlen)
{
	return setsockopt(m_hSocket, level, optname, optval, optlen);
}

int Socket::GetSockOpt( int level, int optname, char * optval, socklen_t * optlen)
{
	return getsockopt(m_hSocket, level, optname, optval, optlen);
}

int Socket::GetPeerName(SockAddr & peer)
{
	socklen_t len = sizeof(peer);
	return getpeername(m_hSocket, (struct sockaddr * )&peer, &len);
}

int Socket::GetSockName(SockAddr & addr)
{
	socklen_t len = sizeof(addr);
	return getsockname(m_hSocket, (sockaddr*)&addr, &len);
}

int Socket::AddMembership(const std::string & multip, const std::string & localip)
{
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(multip.c_str());
	mreq.imr_interface.s_addr = localip.empty() ? INADDR_ANY : inet_addr(localip.c_str());
	
	return SetSockOpt(IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
}

int Socket::DropMembership(const std::string & multip, const std::string & localip)
{
	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(multip.c_str());
	mreq.imr_interface.s_addr = localip.empty() ? INADDR_ANY : inet_addr(localip.c_str());

	return SetSockOpt(IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
}

int Socket::ReuseAddr(bool reuse /* = true */)
{
	int n = reuse ? 1: 0;
	return SetSockOpt(SOL_SOCKET, SO_REUSEADDR, (char*)&n, sizeof(n));
}

int Socket::SetRecvBufSize(int sz)
{
	return SetSockOpt(SOL_SOCKET, SO_RCVBUF, (char*)&sz, sizeof(sz));
}

int Socket::SetSendBufSize(int sz)
{
	return SetSockOpt(SOL_SOCKET, SO_SNDBUF, (char*)&sz, sizeof(sz));
}

int Socket::SetRecvTimeout(int ms)
{
#ifdef _WIN32
	return  SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, (char*)&ms, sizeof(int));
#else
	timeval tv;
	tv.tv_sec = ms / 1000;
	tv.tv_usec = ms % 1000 * 1000;
	return SetSockOpt(SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));
#endif
}

int Socket::SetSendTimeout(int ms)
{
#ifdef _WIN32
	return SetSockOpt(SOL_SOCKET, SO_SNDTIMEO, (char*)&ms, sizeof(int));
#else
	timeval tv;
	tv.tv_sec = ms / 1000;
	tv.tv_usec = ms % 1000 * 1000;
	return SetSockOpt(SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(timeval));
#endif
}

};	// namespace BroadvTool

