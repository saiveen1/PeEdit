#include "charTransfer.h"
wchar_t * char2wchar(const char* cchar)
{
	wchar_t *m_wchar;
	size_t len = MultiByteToWideChar(CP_ACP, 0, cchar, (int)strlen(cchar), NULL, 0);
	m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, cchar, (int)strlen(cchar), m_wchar, (int)len);
	m_wchar[len] = '\0';
	return m_wchar;
}
char * wchar2char(const wchar_t* wchar)
{
	char * m_char;
	size_t len = WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wchar, (int)wcslen(wchar), m_char, (int)len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}