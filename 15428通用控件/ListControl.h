#ifndef __LISTCONTROL_H_
#define __LISTCONTROL_H_


#include "framework.h"
#include "Enum.h"
#include "Transfer.h"
#include "shlwapi.h"
#define MAX_MODULES			888
#define MAX_PROCESSES		888
#define MAX_LENGTH_IMAGE	0x10
#define MAX_LENGTH_NAME		0x20
#define __DECIMAL			10
#define __HEX				16

//LV listView
//HWND h instance windows
	//

VOID InitProcessList(HWND hPreWnd);

VOID SetProcessListItem(HWND hPreWnd, HWND hListWnd);

VOID InitModuleList(HWND hPreWnd);

VOID SetModulesListItem(HWND hPreWnd, HWND hwndListProcess);



#endif // !LISTCONTROL_H
 
