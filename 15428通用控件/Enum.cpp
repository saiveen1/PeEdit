#include "Enum.h"


void printError(const WCHAR *format, ...)
{
	DWORD eNum;
	WCHAR sysMsg[256] = { 0 };

	eNum = GetLastError();
	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL);

	WCHAR msg[1024];
	va_list arg;
	va_start(arg, format);
	vswprintf_s(msg, format, arg);
	va_end(arg);

	// Display the message
	DbgPrintf("\n  WARNING: %s failed with error %08X (%s)\n", msg, eNum, sysMsg);
}

VOID EnumProcess(OUT PROCESSENTRY32W *arrProcessEntryW)
{
	HANDLE		hProcessSnap = NULL;
	BOOL		bRet = FALSE;

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == (HANDLE)-1)
		printError(L"CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS)");

	DWORD dwCount = 0;
	DWORD dwPe32wSize = sizeof(PROCESSENTRY32W);

	arrProcessEntryW[dwCount].dwSize = dwPe32wSize;
	bRet = Process32FirstW(hProcessSnap, &arrProcessEntryW[dwCount]);
	
	while (bRet)
	{
		arrProcessEntryW[++dwCount].dwSize = dwPe32wSize;
		bRet = Process32NextW(hProcessSnap, &arrProcessEntryW[dwCount]);
	}
	arrProcessEntryW[dwCount].dwSize = 0;

	CloseHandle(hProcessSnap);
}

BOOL GetProcImageInfo(DWORD dwPID, OUT MODULEENTRY32W &pModuleEntryW)
{
	HANDLE		hModuleSnap = NULL;
	BOOL		bRet = FALSE;

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, dwPID);	//必须两个加起来一起用
	//64位下可以同时32和64 否则只有64  32下只有32

	if (hModuleSnap == INVALID_HANDLE_VALUE || dwPID < 10)
	{
		printError(L"CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS)");
		TCHAR szError[] = L"System Process";
		memcpy(pModuleEntryW.szModule, szError, 28);
		return FALSE;
	}

	DWORD dwCount = 0;
	DWORD dwPe32wSize = sizeof(MODULEENTRY32W);

	pModuleEntryW.dwSize = dwPe32wSize;
	Module32FirstW(hModuleSnap, &pModuleEntryW);

	CloseHandle(hModuleSnap);
	return TRUE;
}

BOOL EnumModules(DWORD dwPID, OUT MODULEENTRY32W *arrModuleEntryW)
{

	HANDLE		hModuleSnap = NULL;
	BOOL		bRet = FALSE;

	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, dwPID);	//必须两个加起来一起用
	//64位下可以同时32和64 否则只有64  32下只有32

	if (hModuleSnap == INVALID_HANDLE_VALUE || dwPID <10)
	{
		printError(L"CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS)");
		TCHAR szError[] = L"System Process";
		memcpy(arrModuleEntryW[0].szModule, szError, 28);
		return FALSE;
	}

	DWORD dwCount = 0;
	DWORD dwPe32wSize = sizeof(MODULEENTRY32W);

	arrModuleEntryW[dwCount].dwSize = dwPe32wSize;
	bRet = Module32FirstW(hModuleSnap, &arrModuleEntryW[dwCount]);

	while (bRet)
	{
		arrModuleEntryW[++dwCount].dwSize = dwPe32wSize;
		bRet = Module32NextW(hModuleSnap, &arrModuleEntryW[dwCount]);
	}
	arrModuleEntryW[dwCount].dwSize = 0;

	CloseHandle(hModuleSnap);
	return TRUE;
}
