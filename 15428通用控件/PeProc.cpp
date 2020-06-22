#include "PeProc.h"

FileMethod *pFile = new FileMethod;	//不可以放在case里面因为编译器会检查 如果直接default会导致对象没有初始化
//尽量不要在关键词内声明新变量 吃过好多亏了
//不能声明在函数里面是因为是回调函数不断申请空间会崩掉, 所以还是设成全局

INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{


	switch (message)
	{
	case WM_INITDIALOG:
	{
		TCHAR *wszFileName = pFile->GetFileName(hwndDlg);
		MessageBox(hwndDlg, wszFileName, L"PEEDIT", MB_OK);

		return TRUE;
	}

	case WM_COMMAND:
	{
		//switch (LOWORD(wParam))
		//{
		//case IDC_BUTTON_PEEDIT:
		//	MessageBox(hwndDlg, L"Clicked PEEDIT", L"PEEDIT", MB_OK);
		//	//PeEditcProc();
		//	return TRUE;

		//case IDC_BUTTON_ABOUT:
		//	MessageBox(hwndDlg, L"Clicked About", L"About", MB_OK);
		//	//AboutProc;
		//	return TRUE;

		//case IDC_BUTTON_QUIT:
		//	EndDialog(hwndDlg, 0);
		//	return TRUE;

		//default:
		//	return FALSE;
		//}

		return TRUE;
	}

	case WM_NOTIFY:
	{
		//NMHDR *pNMHDR = (NMHDR *)lParam;
		//if (wParam == IDC_LIST_PROCESS && pNMHDR->code == NM_CLICK)
		//{
		//	SetModulesListItem(hwndDlg, GetDlgItem(hwndDlg, IDC_LIST_PROCESS));
		//	return TRUE;
		//}

		return FALSE;
	}

	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		delete pFile;
		return TRUE;

	default:
		return FALSE;
	}
}

VOID SetEditItem(HWND hwndOwner)
{

}
