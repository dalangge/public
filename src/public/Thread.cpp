#include "stdafx.h"
#include "Thread.h"

#include <sys/select.h>

namespace BroadvTool
{

Mutex::Mutex(void)
{
#ifdef _WIN32
	//m_hMutex = ::CreateMutex(NULL, FALSE, NULL);
	InitializeCriticalSection(&m_hMutex);
#else
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m_hMutex, &attr);
	pthread_mutexattr_destroy(&attr);	
#endif
}

Mutex::~Mutex(void)
{
#ifdef _WIN32
	//::CloseHandle(m_hMutex);
	DeleteCriticalSection(&m_hMutex);
#else
	pthread_mutex_destroy(&m_hMutex);
#endif
}

void Mutex::Lock()
{
#ifdef _WIN32
	//::WaitForSingleObject(m_hMutex, INFINITE);
	EnterCriticalSection(&m_hMutex);
#else
	pthread_mutex_lock(&m_hMutex);
#endif
}

void Mutex::Unlock()
{
#ifdef _WIN32
	//::ReleaseMutex(m_hMutex);
	::LeaveCriticalSection(&m_hMutex);
#else
	pthread_mutex_unlock(&m_hMutex);
#endif
}
	
////////////////////////////// Thread ////////////////////////////////////////////
#ifdef _WIN32
static unsigned int _stdcall Thread_Proc(void * par)
{
	Thread * thrd = (Thread *)par;
	thrd->Routine();
	return 1;
}
#else
static void * Thread_Proc(void * par)
{
	Thread * thrd = (Thread *)par;
	thrd->Routine();
	return NULL;
}
#endif


Thread::Thread(void)
: m_hThread(NULL)
{
}

Thread::~Thread(void)
{
}

int Thread::Run()
{
	if (m_hThread) return -1;

#ifdef _WIN32
	unsigned int thrdaddr ;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, Thread_Proc, this, 0, &thrdaddr);
	if(m_hThread == NULL)
		return -1;
#else
	if (pthread_create(&m_hThread, NULL, Thread_Proc, this) != 0)		
		return -1;
#endif	
	return 0;
}

void Thread::Join()
{
	if (m_hThread)
	{
#ifdef _WIN32
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);
#else
		pthread_join(m_hThread, NULL);
#endif
		m_hThread = NULL;
	}
}

void Thread::Join(Thread * p)
{
	if (p != NULL)
	{
		p->Join();
	}
}

void Thread::Sleep(int ms)
{
#ifdef _WIN32
	::Sleep(ms);
#else
	/*timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = (ms % 1000) * 1000000;
	nanosleep(&ts, NULL);*/
	timeval tv = {ms/1000, ms%1000*1000};
	select(0, NULL, NULL, NULL, &tv);
#endif
}

};	// namespace BroadvTool

