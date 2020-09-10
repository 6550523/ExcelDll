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

int main()
{
	HMODULE module = LoadLibrary(DLL_PATH);
	if (module == NULL)
	{
		printf("Load excel.dll failed\n");
		return -1;
	}

	typedef void(*OpenFileFunc)(char *, char*);
	OpenFileFunc OpenFile;
	OpenFile = (OpenFileFunc)GetProcAddress(module, "OpenFile");
	char output[ERR_LEN];
	memset(output, 0, ERR_LEN);
	OpenFile("..\\..\\Release\\1.xlsx", output);
	printf(output);

	typedef int(*GetSheetsCountFunc)();
	GetSheetsCountFunc GetSheetsCount;
	GetSheetsCount = (GetSheetsCountFunc)GetProcAddress(module, "GetSheetsCount");
	printf("%d\n", GetSheetsCount());

	typedef int(*GetRowsCountFunc)(int);
	GetRowsCountFunc GetRowsCount;
	GetRowsCount = (GetRowsCountFunc)GetProcAddress(module, "GetRowsCount");
	printf("%d\n", GetRowsCount(0));

	typedef int(*GetCellsCountFunc)(int, int);
	GetCellsCountFunc GetCellsCount;
	GetCellsCount = (GetCellsCountFunc)GetProcAddress(module, "GetCellsCount");
	printf("%d\n", GetCellsCount(0, 0));

	typedef int(*GetCellStringFunc)(int, int, int, char*);
	GetCellStringFunc GetCellString;
	GetCellString = (GetCellStringFunc)GetProcAddress(module, "GetCellString");
	char cell_string[TEXT_LEN];
	memset(cell_string, 0, TEXT_LEN);
	GetCellString(0, 0, 0, cell_string);
	printf(cell_string);

	typedef void(*NewFileFunc)();
	NewFileFunc NewFile;
	NewFile = (NewFileFunc)GetProcAddress(module, "NewFile");
	NewFile();

	typedef void(*AddSheetFunc)(char*);
	AddSheetFunc AddSheet;
	AddSheet = (AddSheetFunc)GetProcAddress(module, "AddSheet");
	AddSheet("new_sheet");

	typedef void(*AddRowFunc)(int);
	AddRowFunc AddRow;
	AddRow = (AddRowFunc)GetProcAddress(module, "AddRow");
	AddRow(0);

	typedef void(*AddCellFunc)(int, int);
	AddCellFunc AddCell;
	AddCell = (AddCellFunc)GetProcAddress(module, "AddCell");
	AddCell(0, 0);

	typedef void(*SetCellStringFunc)(int, int, int, char*);
	SetCellStringFunc SetCellString;
	SetCellString = (SetCellStringFunc)GetProcAddress(module, "SetCellString");
	SetCellString(0, 0, 0, "cell_string");

	typedef void(*SaveFileFunc)(char*);
	SaveFileFunc SaveFile;
	SaveFile = (SaveFileFunc)GetProcAddress(module, "SaveFile");
	SaveFile("..\\..\\Release\\2.xlsx");

	FreeLibrary(module);
    return 0;
}

