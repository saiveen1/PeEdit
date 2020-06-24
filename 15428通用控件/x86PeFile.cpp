#include "x86PeFile.h"
#pragma warning(disable:4996)
x86PeFile::x86PeFile()
{
}

x86PeFile::x86PeFile(TCHAR* fileName)
{
	ReadPeFile(fileName);
	InitializeBasicInfo(m_pFileBuffer);
}

x86PeFile::~x86PeFile()
{
}


QWORD x86PeFile::getImageBase()
{
	return imageBase;
}



BOOL x86PeFile::ReadPeFile(TCHAR *wszFileName)
{
	FILE* pFile = NULL;
	LLPVOID pFileBuffer = NULL;

	LPSTR szFileName = wchar2char(wszFileName);
	//Open file.

	if (!(pFile = fopen(szFileName, "rb")))
	{
		MessageBox(0, TEXT("Can't open the executable file"), TEXT("Error"), MB_OK);
		return FALSE;
	}

	//Read the length of file.
	fseek(pFile, 0, SEEK_END);
	m_fileSize = ftell(pFile);

	//Allocate memory.
	//写到sectionAllocate才发现这个问题 编译器会自动在分配空间的后面+0x30个空间
	if (!(pFileBuffer = new QWORD[m_fileSize]{0}))
	{
		MessageBox(0, TEXT("Open file failed. No enough memory."), TEXT("Error"), MB_OK);
		fclose(pFile);
		return FALSE;
	}

	fseek(pFile, 0, SEEK_SET);
	size_t n = fread(pFileBuffer, m_fileSize, 1, pFile);
	//成功返回1
	if (!n)
	{
		MessageBox(0, TEXT("Read data failed!"), TEXT("Error"), MB_OK);
		free(pFileBuffer);
		fclose(pFile);
		exit(0);
	}

	m_pFileBuffer = pFileBuffer;
	fclose(pFile);
	return TRUE;
}

VOID x86PeFile::InitializeBasicInfo(LLPVOID pFileBuffer)
{
	mb_isX64 = FALSE;
	pDosHeader = (PIMAGE_DOS_HEADER)((QWORD)pFileBuffer);
	pNTheaders = (PIMAGE_NT_HEADERS)((QWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)((QWORD)pDosHeader + pDosHeader->e_lfanew + 0x4);
	if (pFileHeader->Machine == IMAGE_FILE_MACHINE_AMD64 || pFileHeader->Machine == IMAGE_FILE_MACHINE_IA64)
		mb_isX64 = TRUE;

	pOptionalHeader = (PIMAGE_OPTIONAL_HEADER)((QWORD)pFileHeader + 0x14);
	pSectionHeader = (PIMAGE_SECTION_HEADER)((QWORD)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);

	numOfSections = pFileHeader->NumberOfSections;
	sizeOfOptionalHeader = pFileHeader->SizeOfOptionalHeader;
	sizeOfHeaders = pOptionalHeader->SizeOfHeaders;
	sizeOfImage = pOptionalHeader->SizeOfImage;
	addressEntryPoint = pOptionalHeader->AddressOfEntryPoint;
	imageBase = pOptionalHeader->ImageBase;
	sectionAlignment = pOptionalHeader->SectionAlignment;
	numOfRvaAndSizes = pOptionalHeader->NumberOfRvaAndSizes;
	fileAlignment = pOptionalHeader->FileAlignment;
}

