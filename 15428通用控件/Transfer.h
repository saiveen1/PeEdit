#ifndef __TRANSFER_H_
#define __TRANSFER_H_
#endif


#include <windows.h>
#include <stdint.h>
#include "namedefine.h"



#define TYPDEFAULT			0XF
#define TYPWORD				0X4
#define TYPDWORD			0X8
#define TYPDWORD_DECIMAL	0xA008
#define TYPDEFAULT_DECIMAL	0xA00F
//#define TYPQWORD_DECIMAL	0xA010
#define TYPQWORD			0X10


QWORD GetDigits(QWORD qwSrc);

int  Str2Int(const char *nptr);

long  Str2Long(const char *nptr);

wchar_t * char2wchar(const char* cchar);

char * wchar2char(const wchar_t* wchar);



//void newHex2Str(int64_t qwSrc, TCHAR *wszDest);

LPWSTR Hex2Str(int64_t qwSrc, int64_t srcType);

VOID Hex2Str(int64_t qwSrc, int64_t srcType,TCHAR *wszDest);
