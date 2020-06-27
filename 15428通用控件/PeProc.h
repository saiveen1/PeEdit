#ifndef __PEPROC_H_
#define __PEPROC_H_
#include <windows.h>
#include "iostream"
#include "namedefine.h"
#include "FileMethod.h"
#include "x86PeFile.h"
#include "debugPrintf.h"
#include "controls.h"


#endif // _DEBUG

extern HINSTANCE hInst;
#include "resource.h"


INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK SectionsProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

INT_PTR CALLBACK DirsProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);