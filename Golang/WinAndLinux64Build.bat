#copy the commands to Windows PowerShell and execute
SET GOOS=windows
SET GOARCH=amd64
go build -ldflags "-s -w" -buildmode=c-shared -o ../Release/excel-win-64.dll

SET GOOS=linux
SET GOARCH=amd64
go build -ldflags "-s -w" -buildmode=c-shared -o ../Release/excel-linux-64.so