
//Pe 相关操作
#ifndef __X86PEFILE_H_
#define __X86PEFILE_H_

#include <windows.h>
#include <stdlib.h>
#include <algorithm>	//max min
#include <time.h>
#include <conio.h>
#include <minwindef.h>
#include "iostream"
#include "namedefine.h"
#include "transfer.h"

#define	GETWCHAR 1
#define SIZE_OF_SECTION 0x28
#define SIZE_OF_SECTION_NAME 0x8
#define SIZE_OF_DOSHEADER sizeof(IMAGE_DOS_HEADER)
#define SIZE_OF_EXPORTDIRECTORY 0x28
#define SIZE_OF_IMPORT_DESCRIPTOR sizeof(IMAGE_IMPORT_DESCRIPTOR)
#define SIZE_OF_RESOURCE_DIRECTORY sizeof(IMAGE_RESOURCE_DIRECTORY)
#define SIZE_OF_DATADIRCTORY sizeof(IMAGE_DATA_DIRECTORY)
#define LENGTH_QWORD 0x10
#define MAX_CHAR_ARR 20
#define TODO 0



class x86PeFile
{
public:
	x86PeFile();
	~x86PeFile();

public:
	BOOL Init(TCHAR* fileName);	//因为需要在switch外面声明 条件里面赋值, 所以新弄一个函数
	QWORD	getImageBase();
	QWORD	getNumberOfSections();
	LPCWSTR getImageBase(DWORD);
	LPCWSTR getEntryPoint(DWORD);
	LPCWSTR getSizeOFImage(DWORD);
	LPCWSTR getBaseOfCode(DWORD);
	LPCWSTR getBaseOfData(DWORD);
	LPCWSTR getSectionAlignment(DWORD);
	LPCWSTR getFileAlignment(DWORD);
	LPCWSTR getMagic(DWORD);
	LPCWSTR getSubSystem(DWORD);
	LPCWSTR getNumberOfSections(DWORD);
	LPCWSTR getTimeDateStamp(DWORD);
	LPCWSTR getSizeOfHeaders(DWORD);
	LPCWSTR getCharacteristics(DWORD);
	LPCWSTR getCheckSum(DWORD);
	LPCWSTR getSizeOfOptionalHeader(DWORD);
	LPCWSTR getNumOfRvaAndSizes(DWORD);
	PIMAGE_SECTION_HEADER GetSectionHeader();

private:
	BOOL ReadPeFile(TCHAR* wszfileName);
	VOID InitializeBasicInfo(LLPVOID pFileBuffer);


private:
	TCHAR	*pszBaseNum;
	QWORD	m_fileSize;
	LLPVOID m_pFileBuffer;
	BOOL	mb_isX64;

private:

	DWORD baseOfData;
	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER64 pOptionalHeader = NULL;
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader32 = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
};


#endif

