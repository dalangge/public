#include "stdafx.h"
#include "UdpSrv.h"

#include "Log.h"

namespace BroadvTool
{

///////////////////////////// CUdpSrv::PerThread /////////////////////////////////////////////
CUdpSrv::PerThread::PerThread()
{
	m_bStop = false;
	Run();
}

CUdpSrv::PerThread::~PerThread()
{
	m_bStop = true;
	Thread::Join(this);

	AutoLock mx(m_cs);
	for (size_t i = 0; i < m_vecSock.size(); ++i)
	{
		delete m_vecSock[i];
	}
	m_vecSock.clear();
}

size_t  CUdpSrv::PerThread::Size() const
{
	return m_vecSock.size();
}

bool CUdpSrv::PerThread::Insert(PerSock * p)
{
	AutoLock mx(m_cs);
	m_vecSock.push_back(p);
	return true;
}

bool CUdpSrv::PerThread::Remove(SOCKET s)
{
	AutoLock mx(m_cs);
	for (size_t i = 0; i < m_vecSock.size(); ++i)
	{
		if (m_vecSock[i]->sock.Handle() == s)
		{
			delete m_vecSock[i];
			m_vecSock.erase(m_vecSock.begin()+i);
			return true;
		}
	}
	return false;
}

void CUdpSrv::PerThread::Routine()
{
	while (!m_bStop)
	{
		if (m_vecSock.empty())
		{
			Thread::Sleep(100);
			continue;
		}

		SOCKET nMax = 0;
		fd_set rfds;
		FD_ZERO(&rfds);

		m_cs.Lock();
		for (size_t i = 0; i < m_vecSock.size(); ++i)
		{
			SOCKET s = m_vecSock[i]->sock.Handle();
			FD_SET(s, &rfds);
			nMax = (s > nMax) ? s : nMax;
		}
		m_cs.Unlock();

		timeval tv = {1, 0};
		int n = select( (int)(nMax + 1), &rfds, NULL, NULL, &tv);
		if (n > 0)
		{
			// 此处可能会因为回调函数导致长期占用锁，导致上层无法最快速度Insert/Remove
			// 若实际代码中出现阻塞时间较长，再优化
			AutoLock mx(m_cs);
			for (size_t i = 0; i < m_vecSock.size() && !m_bStop; ++i)
			{
				PerSock * pSock = m_vecSock[i];
				if (!FD_ISSET(pSock->sock.Handle(), &rfds))
					continue;

				char buf[2048];
				SockAddr addr;
				int ret = pSock->sock.RecvFrom(buf, 2048);
				pSock->pfn(pSock->param, buf, ret, pSock->strMultiIP, pSock->nPort, pSock->strLocalIP);
			}
		}
		else if (n == 0)
		{
			// select 超时
			continue; 
		}
		else
		{
			int err = WSAGetLastError();
#ifdef _WIN32
			if (err == WSAENOTSOCK)
				continue;		
#else
			if (err != EBADF)
				continue;
#endif

			Log_Error("CUdpSrv::PerThread --- fatal error, select failed! err=%d", err);
			break;
		}

	}	// end of while
}



//////////////////////////////// CUdpSrv //////////////////////////////////////////
CUdpSrv::CUdpSrv(size_t nMaxSockPerThread /* = 64 */)
{
	m_nMaxSockPerThread = nMaxSockPerThread % 65;
}

CUdpSrv::~CUdpSrv(void)
{
	StopAll();
}

SOCKET CUdpSrv::Join(const std::string & multip, int port, const std::string & localip, 
					 pfn_UdpSrv_Recv pfn, void * param)
{
	Log_Debug("CUdpSrv --- Join <%s %d %s>", multip.c_str(), port, localip.c_str());

	Socket s;
	if (s.Create() == INVALID_SOCKET)
	{
		Log_Error("CUdpSrv --- create socket error! err=%d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	if (s.ReuseAddr())
	{
		Log_Error("CUdpSrv --- reuse addr error! err=%d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	// 将缓冲增大100倍，防止数据突发丢失
	if (s.SetRecvBufSize(100*8*1024))
	{
		Log_Warning("CUdpSrv --- set recv buffer size error! err=%d", WSAGetLastError());
	}

	SockAddr addr(localip, port);
	if (!multip.empty())
	{
// linux需要bind到多播地址上
#ifndef _WIN32
		addr.SetIP(multip);
#endif
	}
	if (s.Bind(addr))
	{
		Log_Error("CUdpSrv --- bind error! err=%d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	if (!multip.empty() && s.AddMembership(multip, localip) != 0)
	{
		Log_Error("CUdpSrv --- add membership error! err=%d", WSAGetLastError());
		return INVALID_SOCKET;
	}

	PerSock * pSock = new PerSock;
	pSock->strMultiIP = multip;
	pSock->nPort = port;
	pSock->strLocalIP = localip;
	pSock->pfn = pfn;
	pSock->param = param;
	pSock->sock.Attach(s.Handle());
	s.Detach();

	AutoLock mx(m_cs);
	for (size_t i = 0; i < m_vecThread.size(); ++i)
	{
		if (m_vecThread[i]->Size() < m_nMaxSockPerThread)
		{
			m_vecThread[i]->Insert(pSock);
			return pSock->sock.Handle();
		}
	}

	// 新创建一个线程
	PerThread * pThread = new PerThread();
	pThread->Insert(pSock);
	m_vecThread.push_back(pThread);

	Log_Debug("CUdpSrv --- create a new thread, total is %d", (int)m_vecThread.size());

	return pSock->sock.Handle();
}

bool CUdpSrv::Leave(SOCKET s)
{
	AutoLock mx(m_cs);
	for (size_t i = 0; i < m_vecThread.size(); ++i)
	{
		PerThread * pThread = m_vecThread[i];
		if (pThread->Remove(s))
		{
			if (pThread->Size() <= 0)
			{
				delete pThread;
				m_vecThread.erase(m_vecThread.begin()+i);

				Log_Debug("CUdpSrv --- destroy a thread, total is %d!", (int)m_vecThread.size());

			}
			return true;
		}
	}
	return false;
}

void CUdpSrv::StopAll()
{
	AutoLock mx(m_cs);
	for (size_t i = 0; i < m_vecThread.size(); ++i)
	{
		delete m_vecThread[i];
	}
	m_vecThread.clear();
}

int CUdpSrv::SendTo(const char * buf, int len, const char * ip, int port, const char * localip)
{
	Socket s;
	s.Create();
	if (localip!=NULL && !std::string(localip).empty())
	{
		m_sock.ReuseAddr();
		s.Bind(SockAddr(localip, 0));
	}

	return s.SendTo(buf, len, SockAddr(ip, port));
}

void CUdpSrv::SetSendInfo(const char * ip, int port, const char * localip)
{
	if (m_sock.IsValid())
	{
		m_sock.Close();
	}
	m_sock.Create();

	m_addr.SetIP(ip);
	m_addr.SetPort(port);

	if (localip!=NULL && !std::string(localip).empty())
	{
		m_sock.ReuseAddr();
		m_sock.Bind(SockAddr(localip, 0));
	}
}

int CUdpSrv::Send(const char * buf, int len)
{
	return m_sock.SendTo(buf, len, m_addr);
}

};	// namespace BroadvTool

