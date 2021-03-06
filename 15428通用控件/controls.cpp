#include "controls.h"
#include "DIALOGPROC.h"	//pe info 变量
static LPCWSTR pszListTitleArr[4] =
{
	L"Process",
	L"PID",
	L"ImageBase",
	L"SizeOfImage"
};

static LPCWSTR szArrModuleListTitle[3] =
{
	L"Process",
	L"ImageBase",
	L"SizeOfImage"
};

static LPCWSTR szArrSectionsListTitle[6] =
{
	L"Name",
	L"VirtualAddress",
	L"VirtualSize",
	L"PointerToRData",
	L"SizeOfRawData",
	L"Flag"
};


static HWND hwndListProcess;
static HWND hwndListModules;
static HWND hwndListSections;

static const TCHAR szProblemProc[] = TEXT("System Process");

VOID InitProcessList(HWND hwndOwner)
{
	LV_COLUMN lvColumn;
	const DWORD dwListProcessColumns = 4;

	memset(&lvColumn, 0, sizeof(lvColumn));
	//lvColumn = { 0 };

	hwndListProcess = GetDlgItem(hwndOwner, IDC_LIST_PROCESS);
	SendMessage(hwndListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	for (int64_t i = 0; i < dwListProcessColumns; i++)
	{
		lvColumn.iSubItem = (int)i;
		lvColumn.cx = 118;
		lvColumn.pszText = (LPWSTR)pszListTitleArr[i];
		ListView_InsertColumn(hwndListProcess, i, &lvColumn);
	}
	
	SetProcessListItem(hwndOwner, hwndListProcess);
}

VOID SetProcessListItem(HWND hwndOwner, HWND hListWnd)
{
	LV_ITEM vitem = {0};
	vitem.mask = LVIF_TEXT;

	DWORD dwRow = 0;
	DWORD dwColumn = 0;
	DWORD dwProcessCount = 0;	//不能只用column计数, 比如第3行不应该填入数据, 但是插入第5行发现第三行空依然会插到第三行然后导致数据出错

	PROCESSENTRY32W *arrProcessEntry = new PROCESSENTRY32W[MAX_PROCESSES]{ 0 };
	memset(arrProcessEntry, 0, sizeof(PROCESSENTRY32W)*MAX_PROCESSES);
	EnumProcess(arrProcessEntry);

	MODULEENTRY32W pModuleEntryW = {0};	//new 自动计算内存, new 在类中会自动执行构造函数 不需要强制转换 可以重载
	TCHAR szNameSysPrc[] = L"svchost.exe";	//不能放在循环里面 一直循环又导致栈空间不够
	//char szProcessID[0x10];
	//char szImageSize[MAX_LENGTH_IMAGE] = {0};
	//WCHAR szImageBase[MAX_LENGTH_IMAGE * 2] = {0};	//最开始定义的10以为够了 但是64位有16位...导致出错 发现万事皆消息 缓冲区地址不够了也传个1f消息到windows 
	while (arrProcessEntry[dwProcessCount].dwSize)
	{
		if (!memcmp(szNameSysPrc, arrProcessEntry[dwProcessCount].szExeFile, 22))	//判断是否是svchost.exe
		{
			dwProcessCount++;
			continue;
		}

		vitem.pszText = arrProcessEntry[dwProcessCount].szExeFile;
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_InsertItem(hListWnd, &vitem);


		vitem.pszText = Hex2Str(arrProcessEntry[dwProcessCount].th32ProcessID, TYPDEFAULT_DECIMAL);	//需要
		//DbgPrintf("%d %d\n", dwRow, dwColumn);
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hListWnd, &vitem);	//第一列用Insert 后续用SetItem
		delete vitem.pszText;

		if (!GetProcImageInfo(arrProcessEntry[dwProcessCount].th32ProcessID, pModuleEntryW))
		{
			vitem.pszText = (LPWSTR)szProblemProc;
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
		}
		else
		{
			int64_t i64ImageBase = (int64_t)(pModuleEntryW.modBaseAddr);	//由于是64位 所以还是逃不过自己写数字到字符串的转换....

			vitem.pszText = Hex2Str(i64ImageBase, TYPDEFAULT);
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
			delete vitem.pszText;
			
			//_ultoa_s((pModuleEntryW.modBaseSize), szImageSize, __HEX);
			vitem.pszText = Hex2Str(pModuleEntryW.modBaseSize,TYPDEFAULT);
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
			delete vitem.pszText;
		}

		memset(&pModuleEntryW,0,sizeof(MODULEENTRY32W));
		dwRow++;
		dwProcessCount++;
		dwColumn = 0;
	}

	delete arrProcessEntry;
}

VOID InitModuleList(HWND hwndOwner)
{
	LV_COLUMN lvColumn;

	const DWORD dwListModulesColums = 3;
	memset(&lvColumn, 0, sizeof(lvColumn));
	hwndListModules = GetDlgItem(hwndOwner, IDC_LIST_MODULES);

	SendMessage(hwndListModules, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	for (int64_t i = 0; i < dwListModulesColums; i++)
	{
		lvColumn.iSubItem = (int)i;
		if(!i)
			lvColumn.cx = 236;
		else
			lvColumn.cx = 118;
		lvColumn.pszText = (LPWSTR)szArrModuleListTitle[i];
		ListView_InsertColumn(hwndListModules, i, &lvColumn);
	}
}

VOID SetModulesListItem(HWND hWndOwner, HWND hwndListProcess)
{
	DWORD dwListProcRow = 0;;
	TCHAR wszPid[0x10] = { 0 };
	LV_ITEM lvItem = { 0 };

	hwndListModules= GetDlgItem(hWndOwner, IDC_LIST_MODULES);

	dwListProcRow = (DWORD)SendMessage(hwndListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);	//获取行号
	if (dwListProcRow == -1)
	{
		MessageBox(NULL, L"Please select a process", L"Error", MB_OK);
		return;
	}
	
	ListView_DeleteAllItems(hwndListModules);

	lvItem.mask = LVIF_TEXT;
	lvItem.iSubItem = 1;		//要获取的列
	lvItem.pszText = wszPid;
	lvItem.cchTextMax = 0x10;	//指定缓冲区大小
	//ListView_GetItem(hwndListProcess, &lvItem);	//不能用
	SendMessage(hwndListProcess, LVM_GETITEMTEXT, dwListProcRow, (LPARAM)&lvItem);	//第一个参数是行 第二个是需要OUT的 需要获得第一列的text 然后把值存在szPid中

	TCHAR wszProcName[MAX_LENGTH_NAME] = { 0 };
	lvItem.iSubItem = 2;
	lvItem.pszText = wszProcName;
	lvItem.cchTextMax = MAX_LENGTH_NAME;
	SendMessage(hwndListProcess, LVM_GETITEMTEXT, dwListProcRow, (LPARAM)&lvItem);
	if (!wcscmp(wszProcName, szProblemProc))
		return;

	//char *szPid = wchar2char(wszPid);
	//DWORD dwPID = stol(szPid,0,10);
	//delete szPid;
	DWORD dwPID = Str2int(wszPid);
	DWORD dwCount = 0;
	DWORD dwRow = 0;
	DWORD dwColumn = 0;
	MODULEENTRY32W *arrModuleEntry = new MODULEENTRY32W[MAX_MODULES]{ 0 };
	memset(arrModuleEntry, 0, sizeof(MODULEENTRY32W)*MAX_MODULES);
	//TCHAR wszImageSize[MAX_LENGTH_IMAGE * 2] = { 0 };
	//TCHAR wszImageBase[MAX_LENGTH_IMAGE * 2] = { 0 };
	EnumModules(dwPID, arrModuleEntry);
	while (arrModuleEntry[dwCount].modBaseSize)
	{
		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn++;
		lvItem.pszText = arrModuleEntry[dwCount].szModule;
		ListView_InsertItem(hwndListModules, &lvItem);

		int64_t ImageBase = (int64_t)(arrModuleEntry[dwCount].modBaseAddr);

		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn++;
		lvItem.pszText = Hex2Str(ImageBase, TYPDEFAULT);
		ListView_SetItem(hwndListModules, &lvItem);
		delete lvItem.pszText;

		

		//_ultoa_s((arrModuleEntry[dwCount].modBaseSize), szImageSize, __HEX);
		lvItem.pszText = Hex2Str((arrModuleEntry[dwCount].modBaseSize), TYPDEFAULT);
		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn;
		ListView_SetItem(hwndListModules, &lvItem);
		delete lvItem.pszText;
		
		dwRow++;
		dwCount++;
		dwColumn = 0;
	}
	delete arrModuleEntry;
}

VOID SetPeFileBaseInfo(HWND hwndOwner)
{
	SetDlgItemText(hwndOwner, IDC_EDIT_ENTRYPOINT, pFileInfo->getEntryPoint(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_IMAGEBASE, pFileInfo->getImageBase(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_SizeOfImage, pFileInfo->getSizeOFImage(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_BASECODE, pFileInfo->getBaseOfCode(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_BASEOFDATA, pFileInfo->getBaseOfData(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_SECTIONALIGNMENT, pFileInfo->getSectionAlignment(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_FILEALIGNMENT, pFileInfo->getFileAlignment(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_MAGIC, pFileInfo->getMagic(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_SUBSYSTEM, pFileInfo->getSubSystem(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_NUMOFSECTIONS, pFileInfo->getNumberOfSections(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_TIMEDATASTAMP, pFileInfo->getTimeDateStamp(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_SIZEOFHEADERS, pFileInfo->getSizeOfHeaders(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_CHARACTERISTICS, pFileInfo->getCharacteristics(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_CHECKSUM, pFileInfo->getCheckSum(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_SIZEOFOPTIONALHEADER, pFileInfo->getSizeOfOptionalHeader(GETWCHAR));
	SetDlgItemText(hwndOwner, IDC_EDIT_NUMOFRVAANDSIZES, pFileInfo->getNumOfRvaAndSizes(GETWCHAR));
}

VOID InitSectionsList(HWND hwndOwner)
{
	LV_COLUMN lvColumn;
	HWND hwndListSections;
	const QWORD dwListSectionsColumns = 6;

	memset(&lvColumn, 0, sizeof(lvColumn));
	//lvColumn = { 0 };

	hwndListSections = GetDlgItem(hwndOwner, IDC_LIST_SECTIONS);
	SendMessage(hwndListSections, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	for (int64_t i = 0; i < dwListSectionsColumns; i++)
	{
		lvColumn.iSubItem = (int)i;
		lvColumn.cx = 88;
		if (!i)
			lvColumn.cx = 60;
		lvColumn.pszText = (LPWSTR)szArrSectionsListTitle[i];
		ListView_InsertColumn(hwndListSections, i, &lvColumn);
	}

	SetSectionsItem(hwndOwner, hwndListSections);
}

VOID SetSectionsItem(HWND hwndOwner, HWND hwndListSections)
{
	LV_ITEM vitem = { 0 };
	vitem.mask = LVIF_TEXT;

	DWORD dwRow = 0;
	DWORD dwColumn = 0;

	PIMAGE_SECTION_HEADER pSectionHeader = pFileInfo->GetSectionHeader();


	for (int i = 0; i < pFileInfo->getNumberOfSections(); i++)
	{
		vitem.pszText = char2wchar((char *)(pSectionHeader->Name));
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_InsertItem(hwndListSections, &vitem);


		vitem.pszText = Hex2Str(pSectionHeader->VirtualAddress, TYPDWORD);
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hwndListSections, &vitem);	//第一列用Insert 后续用SetItem
		delete vitem.pszText;

		vitem.pszText = Hex2Str(pSectionHeader->Misc.VirtualSize, TYPDWORD);
		vitem.iItem = dwRow;
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hwndListSections, &vitem);
		delete vitem.pszText;

		vitem.pszText = Hex2Str(pSectionHeader->PointerToRawData, TYPDWORD);
		vitem.iItem = dwRow;
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hwndListSections, &vitem);
		delete vitem.pszText;

		vitem.pszText = Hex2Str(pSectionHeader->SizeOfRawData, TYPDWORD);
		vitem.iItem = dwRow;
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hwndListSections, &vitem);
		delete vitem.pszText;

		vitem.pszText = Hex2Str(pSectionHeader->Characteristics, TYPDWORD);
		vitem.iItem = dwRow;
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hwndListSections, &vitem);
		delete vitem.pszText;

		dwRow++;
		dwColumn = 0;
		pSectionHeader++;
	}
}

VOID SetDirtoryTable(HWND hwndOwner)
{
	PIMAGE_DATA_DIRECTORY pDataDirectory = pFileInfo->GetDirectoryTable();
	TCHAR *wszTemp = new TCHAR[TYPDWORD + 1];
	int editCount = IDC_EDIT_ER;
	for (QWORD i = 0; i < 0x10; i++)
	{
		Hex2Str(pDataDirectory->VirtualAddress, TYPDWORD, wszTemp);
		SetDlgItemText(hwndOwner, editCount++, wszTemp);
		Hex2Str(pDataDirectory->Size, TYPDWORD, wszTemp);
		SetDlgItemText(hwndOwner, editCount++, wszTemp);
		pDataDirectory++;
	}
	delete wszTemp;
}
