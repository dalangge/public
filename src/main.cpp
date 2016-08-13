

#include <iostream>
#include <stdio.h>

#include "public/public_include.h"

using namespace std;

// thread example
class MyThread : public Thread
{
public:
    MyThread() {}
    virtual ~MyThread() {}

    virtual void Routine()
    {
        while(1)
        {
            Thread::Sleep(1000);
            cout<<"hello"<<endl;
        }
    }
};


// http example
class MyWebSrv : public WebServer, public Servlet
{
public:
    MyWebSrv() {}
    virtual ~MyWebSrv() {}
    
    virtual void OnAccept()
    {
        SOCKET s = Accept();
        if (INVALID_SOCKET == s)
            return;
        
        if (!JoinThread(this, s)) {
            Log_Error("thread pool full");
            Socket tmp(s);
        }
    }
    
    virtual int OnService(const HttpRequest & request, HttpResponse & response, ServletHandler & handler)
    {
        return ServletReturnType_SendResponse;
    }
};


int main(int argc, char ** argv)
{

    // log switch
    g_DefaultLogSrv.Enable(true, true);
    Log_Debug("log test, %d", 123);

   /* MyThread thrd;
    thrd.Run();
    getchar();
    */

    MyWebSrv web;
    web.Start("", 8080);
    getchar();

    return 1;
}


