/*
 Copyright (c) 2017 Brother Wolf
 
 A common c/c++ tool code.
 
 */

#ifndef _BroadvTool_UdpSrv_H_
#define _BroadvTool_UdpSrv_H_

#include "Thread.h"
#include "Socket.h"

#include <vector>

namespace BroadvTool
{


// data recv callback
typedef void (*pfn_UdpSrv_Recv)(void * param,
							const char * buf,
							int len,
							const std::string & ip,
							int port,
							const std::string & localip);

class CUdpSrv
{
	struct PerSock
	{
		Socket sock;
		std::string strMultiIP;
		int nPort;
		std::string strLocalIP;
		pfn_UdpSrv_Recv pfn;
		void * param;

		PerSock() : nPort(0), pfn(NULL), param(NULL) {}
	};

	class PerThread : public Thread
	{
	public:
		PerThread();
		virtual ~PerThread();
		size_t Size() const;
		bool Insert(PerSock * p);
		bool Remove(SOCKET s);
	private:
		virtual void Routine();

		bool m_bStop;
		Mutex m_cs;
		std::vector<PerSock*> m_vecSock;
	};

public:
	CUdpSrv(size_t nMaxSockPerThread = 64);

	~CUdpSrv(void);

	SOCKET Join(const std::string & multip, 
		int port,  
		const std::string & localip, 
		pfn_UdpSrv_Recv pfn,
		void * param);

	bool Leave(SOCKET s);
	void StopAll();

	int SendTo(const char * buf, int len, const char * ip, int port, const char * localip);

	void SetSendInfo(const char * ip, int port, const char * localip);
	int Send(const char * buf, int len);

private:
	Mutex m_cs;
	std::vector<PerThread*> m_vecThread;
	size_t m_nMaxSockPerThread;
	
	Socket m_sock;
	SockAddr m_addr;
};

};	// namespace BroadvTool

#endif	// _BroadvTool_UdpSrv_H_

