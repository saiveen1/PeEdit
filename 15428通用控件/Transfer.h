#ifndef __TRANSFER_H_
#define __TRANSFER_H_
#endif


#include <windows.h>
#include <stdint.h>

void Hex2Str(int64_t qwSrc, TCHAR *wszDest);

int  Str2Int(const char *nptr);

long  Str2Long(const char *nptr);

wchar_t * char2wchar(const char* cchar);

char * wchar2char(const wchar_t* wchar);