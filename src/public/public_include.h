/*******************************************************************************
* 版权所有：	北京市博汇科技有限公司(C) 2013
* 文件名称：	public_include.h 
*
* 内容摘要： 	常用公共头文件总包含
*
--------------------------------------------------------------------------------
				！！！！！  版本变化后在此记录  ！！！！！
--------------------------------------------------------------------------------
* 版本		修改时间		修改人		修改内容
* V1.0		2013/07/05		龚清华		创建
* V1.1		2015/05/15		龚清华		1、创建public版本管理；
*										2、修正 HttpClientSocket "Content-Length"增加长度为"long long"；
*										3、增加 CString、CTime、CTimeSpan在windows平台编译冲突控制宏。
*										4、增加 "typedef.h"包含。
* V1.2		2015/06/13		龚清华		1、增加HttpRequest\HttpResponse Line读取const限制。
* V1.3		2015/06/13		龚清华		1、增加GBK、UTF-8编码转换函数。
* V1.4		2015/07/27		龚清华		1、修正Log格式化缓冲区保护，采用vsnprintf；
*
*
*******************************************************************************/
#ifndef	__PUBLIC_INCLUDE_H_92387498234498543985__
#define	__PUBLIC_INCLUDE_H_92387498234498543985__

// 跨平台宏定义
#include "typedef.h"

// 文件目录相关操作
#include "FileEx.h"

// 线程、互斥
#include "Thread.h"

// 套接字
#include "Socket.h"

// 通通工具
#include "Utility.h"

// 日志
#include "Log.h"

// 可伸缩 UDP 服务器
#include "UdpSrv.h"

// 可伸缩 HTTP服务器、 HTTP通信
#include "WebServer.h"

// 兼容MFC使用方法
#ifndef _WIN32
#include "String.h"
#include "Time.h"
#include "TimeSpan.h"
#endif

// XML打包、解析
#include "Markup.h"

// 快速XML打包（快速解包使用rapidxml）
#include "BHXml.h"

// 使用名字空间
using namespace BroadvTool;


#endif
