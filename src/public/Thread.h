/*
 Copyright (c) 2017 Brother Wolf
 
 A common c/c++ tool code.
 
 */

#ifndef _BroadvTool_Thread_H_
#define _BroadvTool_Thread_H_

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN			
#include <windows.h>
#include <process.h> 
#pragma warning(disable : 4996)

#else
#include <pthread.h>
#endif

namespace BroadvTool
{

////////////////////////////// Mutex ////////////////////////////////////////////
class Mutex
{
public:
	Mutex(void);
	~Mutex(void);

	void Lock();
	void Unlock();

private:
#ifdef _WIN32
	//HANDLE m_hMutex;
	CRITICAL_SECTION m_hMutex;
#else
	mutable pthread_mutex_t m_hMutex;
#endif

private:
	Mutex(const Mutex &);
	const Mutex& operator=(const Mutex &);
};


///////////////////////////// AutoLock /////////////////////////////////////////////
class AutoLock
{
public:
	AutoLock( Mutex & mx) : m_Mutex(mx) { m_Mutex.Lock(); }
	~AutoLock()	{ m_Mutex.Unlock();	}
private:
	Mutex & m_Mutex;
};


///////////////////////////// Thread /////////////////////////////////////////////
class Thread
{
public:
	Thread(void);

	/** don't stop the thread, make sure call Join before */
	virtual ~Thread(void);
	
	/** start a thread, return 0 success , -1 on error */
	int Run();

	/** wait until the thread exit */
	void Join();

	/** wait until the thread exit */
	static void Join(Thread * p);

	/** ms - millisecond */
	static void Sleep(int ms);

	/** thread main loop */
	virtual void Routine() = 0;

private:
#ifdef _WIN32
	HANDLE m_hThread;
#else
	pthread_t m_hThread;
#endif

private:
	Thread(const Thread& );
	Thread& operator=(const Thread& );
};

};	// namespace BroadvTool

#endif	// _BroadvTool_Thread_H_

