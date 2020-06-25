// 15428通用控件.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "15428通用控件.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance	基地址

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	////告诉编译器不必检测不使用的变量
	//UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);


	//HANDLE h222 = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 13686);
	//if (h222 == INVALID_HANDLE_VALUE)
	//	DWORD g = 1;
	//MODULEENTRY32W me;
	//int a = Module32FirstW(h222, &me);
	//int b = GetLastError();
	//CloseHandle(h222);

	//HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, 13686);
	//MODULEENTRY32W me;
	//me.dwSize = sizeof(MODULEENTRY32W);
	//int ret = Module32FirstW(h, &me);

	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DialogProc);
	return 0;

}
