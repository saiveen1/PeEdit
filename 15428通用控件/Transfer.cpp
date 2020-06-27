
#include "Transfer.h"

//void Hex2Str(int64_t qwSrc, TCHAR *wszDest)
//{
//	DWORD dwLow = (DWORD)qwSrc;
//	DWORD dwHigh = (DWORD)(qwSrc >> 32);
//
//	DWORD dwTemp = dwHigh;
//	QWORD dwDigits = GetDigits(dwHigh);
//
//	wsprintfW(wszDest, TEXT("%lx"), dwHigh);
//	wsprintfW((LPWSTR)((int64_t)wszDest + dwDigits * 2), TEXT("%lx"), dwLow);
//}

LPWSTR Hex2Str(int64_t qwSrc, int64_t srcType)
{
	DWORD dwHigh = HIQWORD(qwSrc);
	DWORD dwLow = LOQWORD(qwSrc);
	TCHAR *pwszDes = new WCHAR[srcType + 1]{ 0 };
	TCHAR szBase[4] = TEXT("%u");
	QWORD qwDigits = GetDigits(dwLow);
	if((srcType >> 12) == 0xA)
		srcType &= 0xFF;
	else
	{
		TCHAR szTemp[] = TEXT("%lX");
		memcpy(szBase, szTemp, 8);
	}


	if (srcType == TYPDEFAULT)
	{	
		qwDigits = GetDigits(dwHigh);
		wsprintfW(pwszDes, szBase, dwHigh);
		wsprintfW((LPWSTR)((int64_t)pwszDes + qwDigits * 2), szBase, dwLow);
		return pwszDes;
	}

	LPCWSTR wszPad = TEXT("0000000000000000");
	//wszDest = (TCHAR *)(TEXT("0000000000000000")); �����ᵼ��wszdest��Ϊstatic
	memcpy(pwszDes, wszPad, srcType * 2);

	if (srcType == TYPQWORD || !srcType)
	{
		wsprintfW((LPWSTR)((int64_t)pwszDes + qwDigits * 2 * (8 - qwDigits)), szBase, dwHigh);
		qwDigits = GetDigits(dwLow);
		wsprintfW((LPWSTR)((int64_t)pwszDes + 0x10 + 2 * (8 - qwDigits)), szBase, LOQWORD(qwSrc));
		return pwszDes;
	}
	//8����16����λ��
	if (!qwDigits)
		qwDigits++; //Ϊ0�����
	wsprintfW((LPWSTR)((int64_t)pwszDes + 2 * (srcType - qwDigits)), szBase, LOQWORD(qwSrc));
	return pwszDes;
}

int  Str2Int(const char *nptr)
{
	return (int)Str2Long(nptr);
}

long Str2Long(const char *nptr)
{
	int c;              /* ��ǰҪת�����ַ�(һ��һ���ַ�ת��������) */
	long total;         /* ��ǰת����� */
	int sign;           /* ��־ת������Ƿ������*/

	/*�����ո񣬿ո񲻽���ת��*/
	while (isspace((int)(unsigned char)*nptr))
		++nptr;

	c = (int)(unsigned char)*nptr++;//��ȡһ���ַ�׼��ת�� 
	sign = c;           /*������ű�ʾ*/
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++;    /*����'+'��'-'�ţ�������ת��*/

	total = 0;//����ת�����Ϊ0 

	while (isdigit(c)) {//����ַ������� 
		total = 10 * total + (c - '0');     /* ����ASCII�뽫�ַ�ת��Ϊ��Ӧ�����֣����ҳ�10�ۻ������ */
		c = (int)(unsigned char)*nptr++;    /* ȡ��һ���ַ� */
	}

	//���ݷ���ָʾ�����Ƿ�����ŵĽ�� 
	if (sign == '-')
		return -total;
	else
		return total;
}

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

QWORD GetDigits(QWORD qwSrc)
{
	QWORD dwDigits = 0;
	while (qwSrc)
	{
		dwDigits++;
		qwSrc /= 0x10;
	}
	return dwDigits;
}


VOID Hex2Str(int64_t qwSrc, int64_t srcType, TCHAR *wszDest)
{
	DWORD dwHigh = HIQWORD(qwSrc);
	DWORD dwLow = LOQWORD(qwSrc);
	TCHAR szBase[4] = TEXT("%u");
	QWORD qwDigits = GetDigits(dwHigh);
	if ((srcType >> 12) == 0xA)
		srcType &= 0xFF;
	else
	{
		TCHAR szTemp[] = TEXT("%lX");
		memcpy(szBase, szTemp, 8);
	}


	if (srcType == TYPDEFAULT)
	{
		qwDigits = GetDigits(dwHigh);
		wsprintfW(wszDest, szBase, dwHigh);
		wsprintfW((LPWSTR)((int64_t)wszDest + qwDigits * 2), szBase, dwLow);
		return;
	}

	LPCWSTR wszPad = TEXT("0000000000000000");
	//wszDest = (TCHAR *)(TEXT("0000000000000000")); �����ᵼ��wszdest��Ϊstatic
	memcpy(wszDest, wszPad, srcType * 2);

	if (srcType == TYPQWORD || !srcType)
	{
		wsprintfW((LPWSTR)((int64_t)wszDest + qwDigits * 2 * (8 - qwDigits)), szBase, dwHigh);
		qwDigits = GetDigits(dwLow);
		wsprintfW((LPWSTR)((int64_t)wszDest + 0x10 + 2 * (8 - qwDigits)), szBase, LOQWORD(qwSrc));
	}
	//8����16����λ��

	qwDigits = GetDigits(dwLow);	//DWORD
	if (!qwDigits)
		qwDigits++; //Ϊ0�����
	wsprintfW((LPWSTR)((int64_t)wszDest + 2 * (srcType - qwDigits)), szBase, LOQWORD(qwSrc));
}
