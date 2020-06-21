#include "PeProc.h"

INT_PTR CALLBACK PeProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		MessageBox(hwndDlg, L"Second Dialog.", L"PEEDIT", MB_OK);
		return TRUE;

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
		return TRUE;

	default:
		return FALSE;
	}
}