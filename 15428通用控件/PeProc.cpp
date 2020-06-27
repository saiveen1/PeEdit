#include "PeProc.h"

//624 1931Ӧ����extern����ȫ�� �ر�peedit���ں�����ͷ�, ��Ϊ�ں��������� �����ٴδ򿪴��ھ�û�д˶�����.
//delete Ӧ�����������ڹر� ͬ�� PEinfoҲ�� ��߿��ǰ�x86file����filemethod������
FileMethod *pFile = new FileMethod;	//�����Է���case������Ϊ���������� ���ֱ��default�ᵼ�¶���û�г�ʼ��
//������Ҫ�ڹؼ����������±��� �Թ��ö����
//���������ں�����������Ϊ�ǻص�������������ռ�����, ���Ի������ȫ��
//��һ���������close��ʱ���Ҳ�������û��delete
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

