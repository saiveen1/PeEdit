#ifndef __FILEMETHOD_H_
#define __FILEMETHOD_H_
#include <Windows.h>
#include <commdlg.h>

//���ļ�������Ҫ
//Open file needed.
#include<ShObjIdl.h>
#pragma comment(lib,"Shell32.lib")

class FileMethod
{
private:
	OPENFILENAME *ofn;
	TCHAR *szFileName;

public:
	FileMethod();
	~FileMethod();
public:
	TCHAR *GetFileName(HWND hwndOwner);
};



#endif

