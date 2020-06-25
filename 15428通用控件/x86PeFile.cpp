#include "x86PeFile.h"
#pragma warning(disable:4996)

TCHAR x64BaseOfData[] = TEXT("None");

x86PeFile::x86PeFile() 
{
	pszBaseNum = new TCHAR[LENGTH_QWORD]{ 0 };
}

x86PeFile::~x86PeFile()
{
	delete pszBaseNum;
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
	if (!(pFileBuffer = new QWORD[m_fileSize]{ 0 }))
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

BOOL x86PeFile::Init(TCHAR* fileName)
{
	if (!ReadPeFile(fileName))
		return FALSE;
	InitializeBasicInfo(m_pFileBuffer);
	return FALSE;
}

VOID x86PeFile::InitializeBasicInfo(LLPVOID pFileBuffer)
{
	pDosHeader = (PIMAGE_DOS_HEADER)((QWORD)pFileBuffer);
	//pNTheaders = (PIMAGE_NT_HEADERS)((QWORD)pDosHeader + pDosHeader->e_lfanew);
	pFileHeader = (PIMAGE_FILE_HEADER)((QWORD)pDosHeader + pDosHeader->e_lfanew + 0x4);
	pOptionalHeader = (PIMAGE_OPTIONAL_HEADER64)((QWORD)pFileHeader + 0x14);

	if (pFileHeader->Machine == IMAGE_FILE_MACHINE_AMD64 || pFileHeader->Machine == IMAGE_FILE_MACHINE_IA64)
	{
		mb_isX64 = TRUE;
		pSectionHeader = (PIMAGE_SECTION_HEADER)((QWORD)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);
	}
	else
	{
		mb_isX64 = FALSE;
		pOptionalHeader32 = (PIMAGE_OPTIONAL_HEADER32)pOptionalHeader;
		pSectionHeader = (PIMAGE_SECTION_HEADER)((QWORD)pOptionalHeader + pFileHeader->SizeOfOptionalHeader);

		/* 花了几个小时的极品脑残之作, 当作复习指针了....
		baseOfData = LOQWORD(pOptionalHeader->ImageBase);
		pOptionalHeader->ImageBase = HIQWORD(pOptionalHeader->ImageBase);

		//真的是个弱智啊, 这些东西做的不就是memcpy吗.........
		//留着以示警戒, 用指针以为自己很帅.....
		LLPVOID pX86 = (LLPVOID)(&(pOptionalHeader->SizeOfStackReserve));
		//QWORD x86DataDir = (*(pX86 + 3));
		//QWORD qwArrTemp[0xD] = { 0 };
		//for (QWORD i = 0; i < 0x10; i++)
		//{
		//	QWORD x86DataDir = (*(pX86 + 3 + i));	//x86实际SizeOfHeapCommit是第一个DataDirectory
		//	if (i > 1)
		//		x86DataDir = qwArrTemp[i - 2];		//存原始值 不然后面丢失
		//	qwArrTemp[i] = *((LLPVOID)((&(pOptionalHeader->DataDirectory[i]))));
		//	pOptionalHeader->DataDirectory[i].VirtualAddress = LOQWORD(x86DataDir);
		//	pOptionalHeader->DataDirectory[i].Size = HIQWORD(x86DataDir);
		//}
		LLPVOID pFirSectionLoss = new QWORD;

		//是啊 用了memcpy 突然想起来 强转不就好了吗.......................................
		//大概是脑子有病吧
		memcpy(pOptionalHeader->DataDirectory, pX86 + 3, SIZE_OF_DATADIRCTORY * 0x10);
		//memcpy(pSectionHeader, pFirSectionLoss, sizeof(QWORD));

		QWORD qwArrTemp[0x3] = { 0 };
		for (QWORD i = 0; i < 3; i++)
		{
			qwArrTemp[i] = *pX86;
			pX86++;
		}

		pOptionalHeader->SizeOfStackReserve = LOQWORD(qwArrTemp[0]);
		pOptionalHeader->SizeOfStackCommit = HIQWORD(qwArrTemp[0]);

		pOptionalHeader->SizeOfHeapReserve = LOQWORD(qwArrTemp[1]);
		pOptionalHeader->SizeOfHeapCommit = HIQWORD(qwArrTemp[1]);

		pOptionalHeader->LoaderFlags = LOQWORD(qwArrTemp[2]);
		pOptionalHeader->NumberOfRvaAndSizes = HIQWORD(qwArrTemp[2]);
		delete pFirSectionLoss;
	}
	*/
	}
}





QWORD x86PeFile::getImageBase()
{
	return pOptionalHeader->ImageBase;
}

LPCWSTR x86PeFile::getImageBase(DWORD)
{
	if (mb_isX64)
	{
		Hex2Str(pOptionalHeader->ImageBase, pszBaseNum);
		return pszBaseNum;
	}
	else
	{
		Hex2Str(pOptionalHeader32->ImageBase, pszBaseNum);
		return pszBaseNum;
	}
}

LPCWSTR x86PeFile::getEntryPoint(DWORD)
{
	Hex2Str(pOptionalHeader->AddressOfEntryPoint, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getSizeOFImage(DWORD)
{
	Hex2Str(pOptionalHeader->SizeOfImage, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getBaseOfCode(DWORD)
{
	Hex2Str(pOptionalHeader->BaseOfCode, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getBaseOfData(DWORD)
{
	if (mb_isX64)
		return x64BaseOfData;
	Hex2Str(pOptionalHeader32->BaseOfData, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getSectionAlignment(DWORD)
{
	Hex2Str(pOptionalHeader->SectionAlignment, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getFileAlignment(DWORD)
{
	Hex2Str(pOptionalHeader->FileAlignment, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getMagic(DWORD)
{
	Hex2Str(pOptionalHeader->Magic, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getSubSystem(DWORD)
{
	Hex2Str(pOptionalHeader32->Subsystem, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getNumberOfSections(DWORD)
{
	Hex2Str(pFileHeader->NumberOfSections, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getTimeDateStamp(DWORD)
{
	Hex2Str(pFileHeader->TimeDateStamp, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getSizeOfHeaders(DWORD)
{
	Hex2Str(pOptionalHeader->SizeOfHeaders, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getCharacteristics(DWORD)
{
	Hex2Str(pFileHeader->Characteristics, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getCheckSum(DWORD)
{
	Hex2Str(pOptionalHeader->CheckSum, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getSizeOfOptionalHeader(DWORD)
{
	Hex2Str(pFileHeader->SizeOfOptionalHeader, pszBaseNum);
	return pszBaseNum;
}

LPCWSTR x86PeFile::getNumOfRvaAndSizes(DWORD)
{
	Hex2Str(pOptionalHeader->NumberOfRvaAndSizes, pszBaseNum);
	return pszBaseNum;
}


