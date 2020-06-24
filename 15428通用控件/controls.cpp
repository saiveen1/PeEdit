#include "controls.h"
static const TCHAR *pszListTitleArr[4] =
{
	L"Process",
	L"PID",
	L"ImageBase",
	L"SizeOfImage"
};

static const TCHAR *szArrModuleListTitle[3] =
{
	L"Process",
	L"ImageBase",
	L"SizeOfImage"
};

static const DWORD dwListProcessColumns = 4;

static const DWORD dwListModulesColums = 3;

static HWND hwndListProcess;

static HWND hwndListModules;

static const TCHAR szProblemProc[] = TEXT("System Process");

VOID InitProcessList(HWND hwndOwner)
{
	LV_COLUMN lvColumn;

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
	DWORD dwProcessCount = 0;	//����ֻ��column����, �����3�в�Ӧ����������, ���ǲ����5�з��ֵ����п���Ȼ��嵽������Ȼ�������ݳ���

	PROCESSENTRY32W *arrProcessEntry = new PROCESSENTRY32W[MAX_PROCESSES]{ 0 };
	memset(arrProcessEntry, 0, sizeof(PROCESSENTRY32W)*MAX_PROCESSES);
	EnumProcess(arrProcessEntry);

	MODULEENTRY32W pModuleEntryW = {0};	//new �Զ������ڴ�, new �����л��Զ�ִ�й��캯�� ����Ҫǿ��ת�� ��������
	TCHAR szNameSysPrc[] = L"svchost.exe";	//���ܷ���ѭ������ һֱѭ���ֵ���ջ�ռ䲻��
	char szProcessID[0x10];
	char szImageSize[MAX_LENGTH_IMAGE] = {0};
	WCHAR szImageBase[MAX_LENGTH_IMAGE * 2] = {0};	//�ʼ�����10��Ϊ���� ����64λ��16λ...���³��� �������½���Ϣ ��������ַ������Ҳ����1f��Ϣ��windows 
	while (arrProcessEntry[dwProcessCount].dwSize)
	{
		if (!memcmp(szNameSysPrc, arrProcessEntry[dwProcessCount].szExeFile, 22))
		{
			dwProcessCount++;
			continue;
		}

		vitem.pszText = arrProcessEntry[dwProcessCount].szExeFile;
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_InsertItem(hListWnd, &vitem);


		_ultoa_s(arrProcessEntry[dwProcessCount].th32ProcessID, szProcessID, __DECIMAL);
		vitem.pszText = char2wchar(szProcessID);
		DbgPrintf("%d %d\n", dwRow, dwColumn);
		vitem.iItem = dwRow;	//Row
		vitem.iSubItem = dwColumn++;
		ListView_SetItem(hListWnd, &vitem);	//��һ����Insert ������SetItem

		if (!GetProcImageInfo(arrProcessEntry[dwProcessCount].th32ProcessID, pModuleEntryW))
		{
			vitem.pszText = (LPWSTR)szProblemProc;
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
		}
		else
		{
			int64_t i64ImageBase = (int64_t)(pModuleEntryW.modBaseAddr);	//������64λ ���Ի����Ӳ����Լ�д���ֵ��ַ�����ת��....
			HexToStr(i64ImageBase, szImageBase);
			vitem.pszText = szImageBase;
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
			
			_ultoa_s((pModuleEntryW.modBaseSize), szImageSize, __HEX);
			vitem.pszText = char2wchar(szImageSize);
			vitem.iItem = dwRow;
			vitem.iSubItem = dwColumn++;
			ListView_SetItem(hListWnd, &vitem);
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
	memset(&lvColumn, 0, sizeof(lvColumn));

	hwndListProcess = GetDlgItem(hwndOwner, IDC_LIST_MODULES);
	SendMessage(hwndListProcess, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	for (int64_t i = 0; i < dwListModulesColums; i++)
	{
		lvColumn.iSubItem = (int)i;
		if(!i)
			lvColumn.cx = 236;
		else
			lvColumn.cx = 118;
		lvColumn.pszText = (LPWSTR)szArrModuleListTitle[i];
		ListView_InsertColumn(hwndListProcess, i, &lvColumn);
	}
}

VOID SetModulesListItem(HWND hWndOwner, HWND hwndListProcess)
{
	DWORD dwListProcRow = 0;;
	TCHAR wszPid[0x10] = { 0 };
	LV_ITEM lvItem = { 0 };

	hwndListModules= GetDlgItem(hWndOwner, IDC_LIST_MODULES);

	dwListProcRow = (DWORD)SendMessage(hwndListProcess, LVM_GETNEXTITEM, -1, LVNI_SELECTED);	//��ȡ�к�
	if (dwListProcRow == -1)
	{
		MessageBox(NULL, L"Please select a process", L"Error", MB_OK);
		return;
	}
	
	ListView_DeleteAllItems(hwndListModules);

	lvItem.mask = LVIF_TEXT;
	lvItem.iSubItem = 1;		//Ҫ��ȡ����
	lvItem.pszText = wszPid;
	lvItem.cchTextMax = 0x10;	//ָ����������С
	//ListView_GetItem(hwndListProcess, &lvItem);	//������
	SendMessage(hwndListProcess, LVM_GETITEMTEXT, dwListProcRow, (LPARAM)&lvItem);	//��һ���������� �ڶ�������ҪOUT�� ��Ҫ��õ�һ�е�text Ȼ���ֵ����szPid��

	TCHAR wszProcName[MAX_LENGTH_NAME] = { 0 };
	lvItem.iSubItem = 2;
	lvItem.pszText = wszProcName;
	lvItem.cchTextMax = MAX_LENGTH_NAME;
	SendMessage(hwndListProcess, LVM_GETITEMTEXT, dwListProcRow, (LPARAM)&lvItem);
	if (!wcscmp(wszProcName, szProblemProc))
		return;

	char *szPid = wchar2char(wszPid);
	DWORD dwPID = Str2Int(szPid);
	DWORD dwCount = 0;
	DWORD dwRow = 0;
	DWORD dwColumn = 0;
	MODULEENTRY32W *arrModuleEntry = new MODULEENTRY32W[MAX_MODULES]{ 0 };
	memset(arrModuleEntry, 0, sizeof(MODULEENTRY32W)*MAX_MODULES);
	char szImageSize[MAX_LENGTH_IMAGE] = { 0 };
	TCHAR wszImageBase[MAX_LENGTH_IMAGE * 2] = { 0 };
	EnumModules(dwPID, arrModuleEntry);
	while (arrModuleEntry[dwCount].modBaseSize)
	{
		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn++;
		lvItem.pszText = arrModuleEntry[dwCount].szModule;
		ListView_InsertItem(hwndListModules, &lvItem);

		int64_t ImageBase = (int64_t)(arrModuleEntry[dwCount].modBaseAddr);
		HexToStr(ImageBase, wszImageBase);
		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn++;
		lvItem.pszText = wszImageBase;
		ListView_SetItem(hwndListModules, &lvItem);

		
		_ultoa_s((arrModuleEntry[dwCount].modBaseSize), szImageSize, __HEX);
		lvItem.pszText = char2wchar(szImageSize);
		lvItem.iItem = dwRow;
		lvItem.iSubItem = dwColumn;
		ListView_SetItem(hwndListModules, &lvItem);
		
		dwRow++;
		dwCount++;
		dwColumn = 0;
	}
	delete arrModuleEntry;
}

VOID SetPeFileBaseInfo(HWND hwndOwner)
{
	//SetDlgItemText(hwndOwner, IDC_EDIT_IMAGEBASE, pFileInfo->getImageBase());
}
