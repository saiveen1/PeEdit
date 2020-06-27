#ifndef __TRANSFER_H_
#define __TRANSFER_H_
#endif


#include <windows.h>
#include <stdint.h>
#include "namedefine.h"



#define TYPDEFAULT 0
#define TYPWORD	4
#define TYPDWORD	8
#define TYPQWORD	16

QWORD GetDigits(QWORD qwSrc);

//void Hex2Str(int64_t qwSrc, TCHAR *wszDest);

int  Str2Int(const char *nptr);

long  Str2Long(const char *nptr);

wchar_t * char2wchar(const char* cchar);

char * wchar2char(const wchar_t* wchar);



//void newHex2Str(int64_t qwSrc, TCHAR *wszDest);

LPWSTR Hex2Str(int64_t qwSrc, int64_t srcType);