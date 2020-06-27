#ifndef __CONTROLS_H_
#define __CONTROLS_H_


#include "Enum.h"
#include "Transfer.h"
#include "shlwapi.h"
#include "resource.h"
#include "Transfer.h"


#include <iostream>
#include <string>
using namespace std;

#include <commctrl.h>			
#pragma comment(lib,"comctl32.lib")		

#define MAX_MODULES			888
#define MAX_PROCESSES		888
#define MAX_LENGTH_IMAGE	0x10
#define MAX_LENGTH_NAME		0x20
#define __DECIMAL			10
#define __HEX				16

class FileMethod;
class x86PeFile;	//Ç°ÖÃÉùÃ÷



//LV listView
//HWND h instance windows

VOID InitProcessList(HWND hwndOwner);

VOID SetProcessListItem(HWND hwndOwner, HWND hListWnd);

VOID InitModuleList(HWND hwndOwner);

VOID SetModulesListItem(HWND hwndOwner, HWND hwndListProcess);

VOID SetPeFileBaseInfo(HWND hwndOwner);

VOID InitSectionsList(HWND hwndOwner);


#endif // !controls_H
 
