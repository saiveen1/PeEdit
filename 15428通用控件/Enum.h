#ifndef __ENUM_H_
#define __ENUM_H_
#endif // __ENUM_H_
#include <windows.h>
#include <TlHelp32.h>
#include "debugPrintf.h"
#include "iostream"

void printError(const WCHAR *format, ...);

VOID EnumProcess(OUT PROCESSENTRY32W *arrProcessEntryW);

BOOL GetProcImageInfo(DWORD dwPID, OUT MODULEENTRY32W &pModuleEntryW);	//c++引用方式

BOOL EnumModules(DWORD dwPID, OUT MODULEENTRY32W *arrModuleEntryW);