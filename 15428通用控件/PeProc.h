#ifndef __PEPROC_H_
#define __PEPROC_H_
#include <windows.h>
#include "iostream"
#include "namedefine.h"
#include "FileMethod.h"
#include "x86PeFile.h"
#include "debugPrintf.h"
#endif // _DEBUG

//class Filemethod;
//class x86PeFile;


INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

VOID SetEditItem(HWND hwndOwner);