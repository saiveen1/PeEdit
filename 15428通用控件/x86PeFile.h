
//Pe Ïà¹Ø²Ù×÷
#ifndef __X86PEFILE_H_
#define __X86PEFILE_H_

#include <windows.h>
#include <stdlib.h>
#include <algorithm>	//max min
#include <time.h>
#include <conio.h>
#include "iostream"
#include "namedefine.h"
#include "charTransfer.h"

#endif

#define SIZE_OF_SECTION 0x28
#define SIZE_OF_SECTION_NAME 0x8
#define SIZE_OF_DOSHEADER 0x40
#define SIZE_OF_EXPORTDIRECTORY 0x28
#define SIZE_OF_IMPORT_DESCRIPTOR sizeof(IMAGE_IMPORT_DESCRIPTOR)
#define SIZE_OF_RESOURCE_DIRECTORY sizeof(IMAGE_RESOURCE_DIRECTORY)

#define MAX_CHAR_ARR 20
#define TODO 0




class x86PeFile
{
public:
	x86PeFile();
	x86PeFile(TCHAR *fileName);
	~x86PeFile();

private:
	BOOL ReadPeFile(TCHAR *wszfileName);
	VOID InitializeBasicInfo(LLPVOID pFileBuffer);


private:
	QWORD	m_fileSize;
	LLPVOID m_pFileBuffer;
	BOOL	mb_isX64;

private:
	QWORD sizeOfOptionalHeader;	//In FileHeader
	QWORD sizeOfHeaders;		//In OptionalHeader
	QWORD sizeOfImage;
	QWORD numOfSections;		//FileHeader
	QWORD addressEntryPoint;
	QWORD imageBase;
	QWORD fileAlignment;
	QWORD sectionAlignment;
	QWORD numOfRvaAndSizes;

	PIMAGE_DOS_HEADER pDosHeader = NULL;
	PIMAGE_NT_HEADERS pNTheaders = NULL;
	PIMAGE_FILE_HEADER pFileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER pOptionalHeader = NULL;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
};

x86PeFile::x86PeFile()
{
}

inline x86PeFile::x86PeFile(TCHAR * fileName)
{
	ReadPeFile(fileName);
	InitializeBasicInfo(m_pFileBuffer);
}

x86PeFile::~x86PeFile()
{
}
