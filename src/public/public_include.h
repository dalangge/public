/*******************************************************************************
* ��Ȩ���У�	�����в���Ƽ����޹�˾(C) 2013
* �ļ����ƣ�	public_include.h 
*
* ����ժҪ�� 	���ù���ͷ�ļ��ܰ���
*
--------------------------------------------------------------------------------
				����������  �汾�仯���ڴ˼�¼  ����������
--------------------------------------------------------------------------------
* �汾		�޸�ʱ��		�޸���		�޸�����
* V1.0		2013/07/05		���廪		����
* V1.1		2015/05/15		���廪		1������public�汾����
*										2������ HttpClientSocket "Content-Length"���ӳ���Ϊ"long long"��
*										3������ CString��CTime��CTimeSpan��windowsƽ̨�����ͻ���ƺꡣ
*										4������ "typedef.h"������
* V1.2		2015/06/13		���廪		1������HttpRequest\HttpResponse Line��ȡconst���ơ�
* V1.3		2015/06/13		���廪		1������GBK��UTF-8����ת��������
* V1.4		2015/07/27		���廪		1������Log��ʽ������������������vsnprintf��
*
*
*******************************************************************************/
#ifndef	__PUBLIC_INCLUDE_H_92387498234498543985__
#define	__PUBLIC_INCLUDE_H_92387498234498543985__

// ��ƽ̨�궨��
#include "typedef.h"

// �ļ�Ŀ¼��ز���
#include "FileEx.h"

// �̡߳�����
#include "Thread.h"

// �׽���
#include "Socket.h"

// ͨͨ����
#include "Utility.h"

// ��־
#include "Log.h"

// ������ UDP ������
#include "UdpSrv.h"

// ������ HTTP�������� HTTPͨ��
#include "WebServer.h"

// ����MFCʹ�÷���
#ifndef _WIN32
#include "String.h"
#include "Time.h"
#include "TimeSpan.h"
#endif

// XML���������
#include "Markup.h"

// ����XML��������ٽ��ʹ��rapidxml��
#include "BHXml.h"

// ʹ�����ֿռ�
using namespace BroadvTool;


#endif
