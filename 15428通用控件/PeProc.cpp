#include "PeProc.h"

//624 1931应当用extern声明全局 关闭peedit窗口后对象被释放, 因为在函数外声明 所以再次打开窗口就没有此对象了.
//delete 应当放在主窗口关闭 同理 PEinfo也是 后边考虑把x86file当作filemethod的子类
FileMethod *pFile = new FileMethod;	//不可以放在case里面因为编译器会检查 如果直接default会导致对象没有初始化
//尽量不要在关键词内声明新变量 吃过好多亏了
//不能声明在函数里面是因为是回调函数不断申请空间会崩掉, 所以还是设成全局
//另一方面是最后close的时候找不到声明没法delete
x86PeFile* pFileInfo = new x86PeFile;
INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		{
			TCHAR* wszFileName = pFile->GetFileName(hwndDlg);
			if (!*((LLPVOID)wszFileName))
			{
				EndDialog(hwndDlg, 0);
				return TRUE;
			}
			//MessageBox(hwndDlg, wszFileName, L"PEEDIT", MB_OK);
			pFileInfo->Init(wszFileName);
			//DbgPrintf("%lld", pFileInfo->getImageBase());
			SetPeFileBaseInfo(hwndDlg);
		}
		return TRUE;
	}

	case WM_COMMAND:
	{

		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_PEEDIT:
			MessageBox(hwndDlg, L"Clicked PEEDIT", L"PEEDIT", MB_OK);
			//PeEditcProc();
			return TRUE;

		case IDC_BUTTON_ABOUT:
			MessageBox(hwndDlg, L"Clicked About", L"About", MB_OK);
			//AboutProc;
			return TRUE;

		case IDC_BUTTON_SECTIONS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SECTIONS), hwndDlg, SectionsProc);
			return TRUE;

		case IDC_BUTTON_DIRECTORIES:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_DIRS), hwndDlg, DirsProc);
			return TRUE;

		case IDC_BUTTON_QUIT:
			EndDialog(hwndDlg, 0);
			return TRUE;

		default:
			return FALSE;
		}

	case WM_NOTIFY:
	{
		NMHDR *pNMHDR = (NMHDR *)lParam;
		if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
		{
			SetModulesListItem(hwndDlg, GetDlgItem(hwndDlg, IDC_LIST_PROCESS));
			return TRUE;
		}

		return FALSE;
	}

	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;

	default:
		return FALSE;
	}
	}
}

INT_PTR CALLBACK SectionsProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		InitSectionsList(hwndDlg);
		//{
		//	TCHAR* wszFileName = pFile->GetFileName(hwndDlg);
		//	//MessageBox(hwndDlg, wszFileName, L"PEEDIT", MB_OK);
		//	pFileInfo->Init(wszFileName);
		//	DbgPrintf("%lld", pFileInfo->getImageBase());
		//	SetPeFileBaseInfo(hwndDlg);
		//}
		return TRUE;
	}

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_SECTIONS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SECTIONS), hwndDlg, PeProc);
			return TRUE;

		case IDC_BUTTON_QUIT:
			EndDialog(hwndDlg, 0);
			return TRUE;

		default:
			return FALSE;
		}
	}

	case WM_NOTIFY:
	{
		NMHDR *pNMHDR = (NMHDR *)lParam;
		if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
		{
			SetModulesListItem(hwndDlg, GetDlgItem(hwndDlg, IDC_LIST_PROCESS));
			return TRUE;
		}

		return FALSE;
	}

	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;

	default:
		return FALSE;
	}

}

INT_PTR CALLBACK DirsProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		MessageBox(hwndDlg, TEXT("Dirs"), L"PEEDIT", MB_OK);

		return TRUE;
	}

	//case WM_COMMAND:
	//{
	//	switch (LOWORD(wParam))
	//	{
	//	case IDC_BUTTON_SECTIONS:
	//		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SECTIONS), hwndDlg, PeProc);
	//		return TRUE;

	//	case IDC_BUTTON_DIRECTORIES:
	//		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_DIRS), hwndDlg, PeProc);
	//		return TRUE;

	//	case IDC_BUTTON_QUIT:
	//		EndDialog(hwndDlg, 0);
	//		return TRUE;

	//	default:
	//		return FALSE;
	//	}
	//}

	//case WM_NOTIFY:
	//{
	//	NMHDR *pNMHDR = (NMHDR *)lParam;
	//	if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
	//	{
	//		SetModulesListItem(hwndDlg, GetDlgItem(hwndDlg, IDC_LIST_PROCESS));
	//		return TRUE;
	//	}

	//	return FALSE;
	//}

	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		return TRUE;

	default:
		return FALSE;
	}

}

