#include "FileMethod.h"

FileMethod::FileMethod()
{
	ofn = new OPENFILENAME{ 0 };
	szFileName = new TCHAR[MAX_PATH]{ 0 };
}

FileMethod::~FileMethod()
{
	delete ofn;
	delete szFileName;
}

TCHAR *FileMethod::GetFileName(HWND hwndOwner)
{
	ofn->lStructSize = sizeof(OPENFILENAME);
	ofn->hwndOwner = hwndOwner;
	ofn->lpstrFilter = TEXT("PE Flie\0*.exe;*.sys;*.dll;*.com;*.\0\0");//ÉèÖÃ¹ýÂË
	ofn->nFilterIndex = 0;
	ofn->lpstrFile = szFileName;
	ofn->nMaxFile = MAX_PATH;
	ofn->lpstrInitialDir = NULL;
	ofn->lpstrTitle = TEXT("Please Select a Pe file.");
	ofn->Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

	GetOpenFileName(ofn);

	return szFileName;
}
