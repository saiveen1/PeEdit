#ifndef __PEPROC_H_
#define __PEPROC_H_
#include "framework.h"
#include "x86PeFile.h"

extern FileMethod *pFile; 
extern x86PeFile *pFileInfo;

#endif // _DEBUG


INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

VOID SetEditItem(HWND hwndOwner);