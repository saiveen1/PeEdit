
#ifndef __DIALOGPROC_H_
#define __DIALOGPROC_H_

#include "windows.h"
#include "iostream"
#include "PeProc.h"
#include "x86PeFile.h"
#include "FileMethod.h"

extern HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif

//��ΪҪ������delete ��ʹ�����ڱ�ĵط�, ����Ҫ��Ϊȫ�ֱ���
//��dialogproc ��Ϊpeproc �ĸ��ص�
//h ʹ��ǰ������ .cpp ����ȫ�ֱ��� ��Ҫ�õ��ĵط�
//�໥���������  ��Ҫʹ��ǰ������

extern FileMethod *pFile;
extern x86PeFile *pFileInfo;






