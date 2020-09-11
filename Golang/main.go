package main

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
import "C"
//befor import "C" cannot be empty line
import (
	"fmt"
	"github.com/tealeg/xlsx"
	"unsafe"
)

//export OpenFile
func OpenFile(fileName, output *C.char) {
	xlFile, err = xlsx.OpenFile(C.GoString(fileName))
	if err != nil {
		fmt.Println(err.Error())
		C.strcpy(output, C.CString(err.Error()))
		return
	}
}

//export OpenFileWithRowLimit
func OpenFileWithRowLimit(fileName *C.char, rowLimit C.int, output *C.char) {
	xlFile, err = xlsx.OpenFileWithRowLimit(C.GoString(fileName), int(rowLimit))
	if err != nil {
		fmt.Println(err.Error())
		C.strcpy(output, C.CString(err.Error()))
		return
	}
}

//export OpenBinary
func OpenBinary(bs *C.char, size C.int, output *C.char) {
	b := C.GoBytes(unsafe.Pointer(bs), size)
	xlFile, err = xlsx.OpenBinary(b)
	if err != nil {
		fmt.Println(err.Error())
		C.strcpy(output, C.CString(err.Error()))
		return
	}
}

//export OpenBinaryWithRowLimit
func OpenBinaryWithRowLimit(bs *C.char, size C.int, rowLimit C.int, output *C.char) {
	b := C.GoBytes(unsafe.Pointer(bs), size)
	xlFile, err = xlsx.OpenBinaryWithRowLimit(b, int(rowLimit))
	if err != nil {
		fmt.Println(err.Error())
		C.strcpy(output, C.CString(err.Error()))
		return
	}
}

//export NewFile
func NewFile() {
	xlFile = xlsx.NewFile()
}

//export SaveFile
func SaveFile(input *C.char) {
	if xlFile == nil {
		return
	}
	xlFile.Save(C.GoString(input))
}

//export GetSheetsCount
func GetSheetsCount() int {
	if xlFile == nil {
		return -1
	}
	return len(xlFile.Sheets)
}

//export GetRowsCount
func GetRowsCount(SheetIndex int) int {
	if xlFile == nil {
		return -1
	}

	if len(xlFile.Sheets) == 0 {
		return -2
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return -3
	}

	return len(xlFile.Sheets[SheetIndex].Rows)
}

//export GetCellsCount
func GetCellsCount(SheetIndex, RowIndex int) int {
	if xlFile == nil {
		return -1
	}

	if len(xlFile.Sheets) == 0 {
		return -2
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return -3
	}

	if len(xlFile.Sheets[SheetIndex].Rows) == 0 {
		return -4
	}

	if len(xlFile.Sheets[SheetIndex].Rows) <= RowIndex {
		return -5
	}

	return len(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells)
}

//export GetCellString
func GetCellString(SheetIndex, RowIndex, CellIndex int, output *C.char) int {
	if xlFile == nil {
		return -1
	}

	if len(xlFile.Sheets) == 0 {
		return -2
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return -3
	}

	if len(xlFile.Sheets[SheetIndex].Rows) == 0 {
		return -4
	}

	if len(xlFile.Sheets[SheetIndex].Rows) <= RowIndex {
		return -5
	}

	if len(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells) == 0 {
		return -6
	}

	if len(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells) <= CellIndex {
		return -7
	}

	C.strcpy(output, C.CString(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells[CellIndex].String()))
	return 0
}

//export AddSheet
func AddSheet(input *C.char) {
	if xlFile == nil {
		return
	}

	if input == nil {
		return
	}

	if len(C.GoString(input)) == 0 {
		return
	}
	xlFile.AddSheet(C.GoString(input))
}

//export AddRow
func AddRow(SheetIndex int) {
	if xlFile == nil {
		return
	}

	if len(xlFile.Sheets) == 0 {
		return
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return
	}
	xlFile.Sheets[SheetIndex].AddRow()
}

//export AddCell
func AddCell(SheetIndex, RowIndex int) {
	if xlFile == nil {
		return
	}

	if len(xlFile.Sheets) == 0 {
		return
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return
	}

	if len(xlFile.Sheets[SheetIndex].Rows) == 0 {
		return
	}

	if len(xlFile.Sheets[SheetIndex].Rows) <= RowIndex {
		return
	}
	xlFile.Sheets[SheetIndex].Rows[RowIndex].AddCell()
}

//export SetCellString
func SetCellString(SheetIndex, RowIndex, CellIndex int, input *C.char) int {
	if xlFile == nil {
		return -1
	}

	if len(xlFile.Sheets) == 0 {
		return -2
	}

	if len(xlFile.Sheets) <= SheetIndex {
		return -3
	}

	if len(xlFile.Sheets[SheetIndex].Rows) == 0 {
		return -4
	}

	if len(xlFile.Sheets[SheetIndex].Rows) <= RowIndex {
		return -5
	}

	if len(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells) == 0 {
		return -6
	}

	if len(xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells) <= CellIndex {
		return -7
	}

	xlFile.Sheets[SheetIndex].Rows[RowIndex].Cells[CellIndex].Value = C.GoString(input)
	return 0
}

var xlFile *xlsx.File
var err error
func main() {
	// Need a main function to make CGO compile package as C shared library
}
