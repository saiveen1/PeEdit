#ifndef __NAMEDEFINE_H_
#define __NAMEDEFINE_H_

#include <stdint.h>

typedef int64_t QWORD;

typedef QWORD * LLPVOID;



#endif // __NAMEDEFINE_H_
#define LOQWORD(l)           ((DWORD) ( ( (QWORD) (l) ) & 0xffffffff) )
#define HIQWORD(l)           ((DWORD)((((QWORD)(l)) >> 32) & 0xffffffff))