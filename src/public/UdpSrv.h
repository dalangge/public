/*******************************************************************************
* 版权所有：	北京市博汇科技有限公司(C) 2013
* 文件名称：	UdpSrv.h
*
* 内容摘要： 	本类提供一个可伸缩的UDP服务器
*
--------------------------------------------------------------------------------
* 版本		修改时间		修改人		修改内容
* V1.0		2013/08/30		龚清华		创建
*******************************************************************************/
#ifndef _BroadvTool_UdpSrv_H_
#define _BroadvTool_UdpSrv_H_

#include "Thread.h"
#include "Socket.h"

#include <vector>

namespace BroadvTool
{


// UDP数据接收回调
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
	// 单线程同时处理最大SOCKET数目，（默认64）
	CUdpSrv(size_t nMaxSockPerThread = 64);

	~CUdpSrv(void);

	// 加入监听
	SOCKET Join(const std::string & multip, 
		int port,  
		const std::string & localip, 
		pfn_UdpSrv_Recv pfn,
		void * param);

	// 停止监听
	bool Leave(SOCKET s);

	// 停止所有监听
	void StopAll();

	// 发送数据
	int SendTo(const char * buf, int len, const char * ip, int port, const char * localip);

	// 设置数据发送信息，与SendTo(par1,par2)配合使用
	void SetSendInfo(const char * ip, int port, const char * localip);

	// 发送数据
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

