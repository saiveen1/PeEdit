
#include "Transfer.h"

void HexToStr(int64_t qwSrc, TCHAR *wszDest)
{
	DWORD dwLow = (DWORD)qwSrc;
	int64_t i64Temp = (qwSrc & 0xffffffff00000000) / 0x10000000;
	DWORD dwHigh = (DWORD)i64Temp;
	DWORD dwTemp = dwHigh / 0x10;
	DWORD dwDigits = 0;
	while (dwTemp)
	{
		dwTemp /= 0x10;
		dwDigits++;
	}
	wsprintfW(wszDest, TEXT("%lx"), dwHigh);
	wsprintfW((LPWSTR)((int64_t)wszDest + dwDigits * 2), TEXT("%lx"), dwLow);
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
