// header.h : include file for standard system include files,
// or project specific include files
//

#ifndef __FRAMEWORK_H_
#define  __FRAMEWORK_H_

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>
#include <TlHelp32.h>

#include "debugPrintf.h"
#include "charTransfer.h"
#include "Resource.h"
#include "DialogProc.h"
#include "ListControl.h"
#include "PeProc.h"
#include "FileMethod.h"

extern HINSTANCE hInst;


#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")		


//文件操作相关


#endif



