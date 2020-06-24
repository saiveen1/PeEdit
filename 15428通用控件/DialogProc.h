
#ifndef __DIALOGPROC_H_
#define __DIALOGPROC_H_

#include "windows.h"
#include "iostream"
#include "PeProc.h"
#include "x86PeFile.h"
#include "FileMethod.h"

extern HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif

//因为要在这里delete 而使用是在别的地方, 所以要设为全局变量
//而dialogproc 作为peproc 的父回调
//h 使用前置声明 .cpp 声明全局变量 需要用到的地方
//相互包含的情况  需要使用前置声明

extern FileMethod *pFile;
extern x86PeFile *pFileInfo;






