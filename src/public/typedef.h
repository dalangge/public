
#ifndef __TYPEDEF_H_54323895192321809332856435365123123__
#define __TYPEDEF_H_54323895192321809332856435365123123__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <afxwin.h>				 
#include <afxext.h>				 
#pragma warning(disable : 4996)

#else
typedef void * LPVOID;
typedef void *HANDLE;
typedef void * HWND;
typedef int LONG ;
typedef char CHAR;
typedef unsigned int ULONG;
typedef unsigned char BYTE;
typedef unsigned char byte;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int BOOL;
typedef unsigned char UINT8, *PUINT8;
typedef unsigned int UINT;
typedef char _TCHAR;
typedef const char *LPCTSTR;
typedef const char *LPCSTR;
typedef char * LPSTR;
typedef char * PCHAR;
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT32;;
typedef int INT;
typedef short SHORT;
typedef const void * LPCVOID;
typedef BYTE * LPBYTE;
typedef BYTE * PBYTE;

#define TRUE 1
#define FALSE 0
#define _T(x) x
#define _tcsncicmp strncasecmp
#define _tcsnccmp strncmp
#define _tcschr strchr
#define _tcslen strlen
#define _tclen(p) 1 
#define _tcsncpy strncpy
#define _tcscpy strcpy
#define _tccpy(p1,p2) *(p1)=*(p2) 
#define _tcstol strtol
#define _tcsncmp strncmp
#define _stprintf sprintf
#define _tcsstr strstr
#define _tfopen fopen
#define _ttoi atoi
#define sprintf_s sprintf
#define sscanf_s sscanf
#define vsprintf_s vsprintf

#define MAKELONG(a,b)  ((LONG)(((WORD)((DWORD)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD)(b) & 0xffff))) << 16))
#define MAKEWORD(a, b) ((WORD)(((BYTE)((DWORD)(a) & 0xff)) | ((WORD)((BYTE)((DWORD)(b) & 0xff))) << 8))
#define LOWORD(l)           ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD)(l) >> 16))
#define MAX_PATH		260

#define DEBUG_NEW new
#define ASSERT(x)
#define VERIFY(x) x
#endif

#define  SAFE_DELETE(p) if(p){delete p; p=NULL;}
#define  SAFE_DELETE_ARRAY(p) if(p){delete []p; p=NULL;}

#endif

