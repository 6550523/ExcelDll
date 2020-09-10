GOOS=darwin
GOARCH=amd64
go build -ldflags "-s -w" -buildmode=c-shared -o ../Release/excel-osx-64.so