#ifndef __CONTROLS_H_
#define __CONTROLS_H_


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

VOID InitProcessList(HWND hwndOwner);

VOID SetProcessListItem(HWND hwndOwner, HWND hListWnd);

VOID InitModuleList(HWND hwndOwner);

VOID SetModulesListItem(HWND hwndOwner, HWND hwndListProcess);



#endif // !controls_H
 
