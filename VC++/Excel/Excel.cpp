#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define ERR_LEN 1024
#define TEXT_LEN 8848

#ifdef _WIN64
#define DLL_PATH _T("..\\..\\Release\\excel-win-64.dll")
#else
#define DLL_PATH _T("..\\..\\Release\\excel-win-32.dll")
#endif

#define  XLSX_FILE "..\\..\\Release\\1.xlsx"

int main()
{
	HMODULE module = LoadLibrary(DLL_PATH);
	if (module == NULL)
	{
		printf("Load excel.dll failed\n");
		return -1;
	}

	//OpenFile
	typedef void(*OpenFileFunc)(char *, char*);
	OpenFileFunc OpenFile;
	OpenFile = (OpenFileFunc)GetProcAddress(module, "OpenFile");
	char output[ERR_LEN];
	memset(output, 0, ERR_LEN);
	OpenFile(XLSX_FILE, output);
	printf(output);

	//OpenFileWithRowLimit
	//typedef void(*OpenFileWithRowLimitFunc)(char *, int, char*);
	//OpenFileWithRowLimitFunc OpenFileWithRowLimit;
	//OpenFileWithRowLimit = (OpenFileWithRowLimitFunc)GetProcAddress(module, "OpenFileWithRowLimit");
	//char output[ERR_LEN];
	//memset(output, 0, ERR_LEN);
	//OpenFileWithRowLimit(XLSX_FILE, 1, output);
	//printf(output);

	//OpenBinary
	//typedef void(*OpenBinaryFunc)(char *, int, char*);
	//OpenBinaryFunc OpenBinary;
	//OpenBinary = (OpenBinaryFunc)GetProcAddress(module, "OpenBinary");
	//char output[ERR_LEN];
	//memset(output, 0, ERR_LEN);
	//FILE * pFile;
	//long lSize;
	//char * buffer;
	//size_t result;
	//fopen_s(&pFile, XLSX_FILE, "rb");
	//if (pFile == NULL)
	//{
	//	fputs("File error", stderr);
	//	exit(1);
	//}
	//fseek(pFile, 0, SEEK_END);
	//lSize = ftell(pFile);
	//rewind(pFile);
	//buffer = (char*)malloc(sizeof(char)*lSize);
	//if (buffer == NULL)
	//{
	//	fputs("Memory error", stderr);
	//	exit(2);
	//}
	//memset(buffer, 0, sizeof(char)*lSize);
	//result = fread_s(buffer, sizeof(char)*lSize, sizeof(char), lSize, pFile);
	//if (result != lSize)
	//{
	//	fputs("Reading error", stderr);
	//	exit(3);
	//}
	//OpenBinary(buffer, sizeof(char)*lSize, output);
	//fclose(pFile);
	//free(buffer);
	//printf(output);

	//OpenBinaryWithRowLimit
	//typedef void(*OpenBinaryWithRowLimitFunc)(char *, int, int, char*);
	//OpenBinaryWithRowLimitFunc OpenBinaryWithRowLimit;
	//OpenBinaryWithRowLimit = (OpenBinaryWithRowLimitFunc)GetProcAddress(module, "OpenBinaryWithRowLimit");
	//char output[ERR_LEN];
	//memset(output, 0, ERR_LEN);
	//FILE * pFile;
	//long lSize;
	//char * buffer;
	//size_t result;
	//fopen_s(&pFile, XLSX_FILE, "rb");
	//if (pFile == NULL)
	//{
	//	fputs("File error", stderr);
	//	exit(1);
	//}
	//fseek(pFile, 0, SEEK_END);
	//lSize = ftell(pFile);
	//rewind(pFile);
	//buffer = (char*)malloc(sizeof(char)*lSize);
	//if (buffer == NULL)
	//{
	//	fputs("Memory error", stderr);
	//	exit(2);
	//}
	//memset(buffer, 0, sizeof(char)*lSize);
	//result = fread_s(buffer, sizeof(char)*lSize, sizeof(char), lSize, pFile);
	//if (result != lSize)
	//{
	//	fputs("Reading error", stderr);
	//	exit(3);
	//}
	//OpenBinaryWithRowLimit(buffer, sizeof(char)*lSize, 1, output);
	//fclose(pFile);
	//free(buffer);
	//printf(output);

	//GetSheetsCount
	typedef int(*GetSheetsCountFunc)();
	GetSheetsCountFunc GetSheetsCount;
	GetSheetsCount = (GetSheetsCountFunc)GetProcAddress(module, "GetSheetsCount");
	printf("%d\n", GetSheetsCount());

	//GetRowsCount
	typedef int(*GetRowsCountFunc)(int);
	GetRowsCountFunc GetRowsCount;
	GetRowsCount = (GetRowsCountFunc)GetProcAddress(module, "GetRowsCount");
	printf("%d\n", GetRowsCount(0));

	//GetCellsCount
	typedef int(*GetCellsCountFunc)(int, int);
	GetCellsCountFunc GetCellsCount;
	GetCellsCount = (GetCellsCountFunc)GetProcAddress(module, "GetCellsCount");
	printf("%d\n", GetCellsCount(0, 0));

	//GetCellString
	typedef int(*GetCellStringFunc)(int, int, int, char*);
	GetCellStringFunc GetCellString;
	GetCellString = (GetCellStringFunc)GetProcAddress(module, "GetCellString");
	char cell_string[TEXT_LEN];
	memset(cell_string, 0, TEXT_LEN);
	GetCellString(0, 0, 0, cell_string);
	printf(cell_string);

	//NewFile
	typedef void(*NewFileFunc)();
	NewFileFunc NewFile;
	NewFile = (NewFileFunc)GetProcAddress(module, "NewFile");
	NewFile();

	//AddSheet
	typedef void(*AddSheetFunc)(char*);
	AddSheetFunc AddSheet;
	AddSheet = (AddSheetFunc)GetProcAddress(module, "AddSheet");
	AddSheet("new_sheet");

	//AddRow
	typedef void(*AddRowFunc)(int);
	AddRowFunc AddRow;
	AddRow = (AddRowFunc)GetProcAddress(module, "AddRow");
	AddRow(0);

	//AddCell
	typedef void(*AddCellFunc)(int, int);
	AddCellFunc AddCell;
	AddCell = (AddCellFunc)GetProcAddress(module, "AddCell");
	AddCell(0, 0);

	//SetCellString
	typedef void(*SetCellStringFunc)(int, int, int, char*);
	SetCellStringFunc SetCellString;
	SetCellString = (SetCellStringFunc)GetProcAddress(module, "SetCellString");
	SetCellString(0, 0, 0, "cell_string");

	//SaveFile
	typedef void(*SaveFileFunc)(char*);
	SaveFileFunc SaveFile;
	SaveFile = (SaveFileFunc)GetProcAddress(module, "SaveFile");
	SaveFile("..\\..\\Release\\2.xlsx");

	FreeLibrary(module);
    return 0;
}

