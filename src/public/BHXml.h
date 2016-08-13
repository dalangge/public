#ifndef _H_BH_XML
#define _H_BH_XML

#ifndef UINT64
#define UINT64 long long
#endif

#include <string>

#define MAX_LAYER		16
#define MAX_ELEM_SIZE	64

enum StatusType
{
	STATUS_INIT			= 0x0,
	STATUS_ELEM_ADD		= 0x1,
	STATUS_ELEM_FINISH	= 0x2
};

class CBHXml
{
public:
	CBHXml(void);
public:
	~CBHXml(void);

public:

    bool Reserve(int nBufSize);

	bool SetBuffer(int nBufSize);

	bool SetDoc(const char *pDoc);

	char *GetDoc();

	bool AddElem(const char *pStr);

	bool IntoElem();

	bool OutOfElem();

	bool AddAttrib(const char *pKey, const char *pValue);

	bool SetAttrib(const char *pKey, const char *pValue);

	bool AddAttrib(const char *pKey, const int nValue);

	bool SetAttrib(const char *pKey, const int nValue);

    bool AddAttrib(const char *pKey, const unsigned int nValue);

    bool SetAttrib(const char *pKey, const unsigned int nValue);

    bool AddUint64Attrib(const char *pKey, const UINT64 nValue);

private:

	char*   m_pBuf;
	int     m_nBufSize;

	int     m_nLayer;
	char*   m_pElem[MAX_LAYER];

	int     m_nStatus;

	int     m_nPos;

};


#endif
