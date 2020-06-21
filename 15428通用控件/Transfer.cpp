
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
	int c;              /* 当前要转换的字符(一个一个字符转换成数字) */
	long total;         /* 当前转换结果 */
	int sign;           /* 标志转换结果是否带负号*/

	/*跳过空格，空格不进行转换*/
	while (isspace((int)(unsigned char)*nptr))
		++nptr;

	c = (int)(unsigned char)*nptr++;//获取一个字符准备转换 
	sign = c;           /*保存符号标示*/
	if (c == '-' || c == '+')
		c = (int)(unsigned char)*nptr++;    /*跳过'+'、'-'号，不进行转换*/

	total = 0;//设置转换结果为0 

	while (isdigit(c)) {//如果字符是数字 
		total = 10 * total + (c - '0');     /* 根据ASCII码将字符转换为对应的数字，并且乘10累积到结果 */
		c = (int)(unsigned char)*nptr++;    /* 取下一个字符 */
	}

	//根据符号指示返回是否带负号的结果 
	if (sign == '-')
		return -total;
	else
		return total;
}
