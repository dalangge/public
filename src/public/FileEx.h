
#ifndef _FILE_EX_75894328849318493216789054320573409
#define _FILE_EX_75894328849318493216789054320573409

#include <vector>
#include <string>

class CFileEx
{
public:
	static char Separator();

	static std::string GetCurDirectory();
	static std::string GetExeDirectory();

    static bool SetCurDirectory(const char * lpszFolder);

    static bool CreateFolder(const char * lpszFolder);

    static bool CreateFolderForFile(const char * lpszFile);

    static void GetSubFiles(const char * lpszFolder, std::vector<std::string> &vecFile);

    static void GetSubFolders(const char * lpszFolder, std::vector<std::string> &vecFolder);

    static std::string Path2FileName(const char *lpszPath);

    static unsigned int GetFreeDiskSpace(const char * lpszPath);

    static bool DelFolder(const char * lpszFolder);

    static bool DelFile(const char * lpszPath);

private:
	CFileEx(void){}
	~CFileEx(void){}
};

#endif

