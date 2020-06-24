#include "DialogProc.h"
#include "controls.h"
#include "15428ͨ�ÿؼ�.h"
#include "x86PeFile.h"
//static WCHAR szListTitle[] = L"Process";

extern FileMethod *pFile;
extern x86PeFile *pFileInfo;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		InitProcessList(hwndDlg);
		InitModuleList(hwndDlg);
		return TRUE;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_PEEDIT:
			MessageBox(hwndDlg, L"Clicked PEEDIT", L"PEEDIT", MB_OK);
			//������������������Ӵ��ڴ���ʱ�������޷��ƶ�
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_PEEDITOR), hwndDlg, PeProc);	
			return TRUE;

		case IDC_BUTTON_ABOUT:
			MessageBox(hwndDlg, L"Clicked About", L"About", MB_OK);
			//AboutProc;
			return TRUE;

		case IDC_BUTTON_QUIT:
			EndDialog(hwndDlg, 0);
			return TRUE;

		default:
			return FALSE;
		}

		return TRUE;
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
		delete pFile;
		delete pFileInfo;
		EndDialog(hwndDlg, 0);
		return TRUE;

	default:
		return FALSE;
	}
}