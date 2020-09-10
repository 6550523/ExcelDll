GOOS=darwin
GOARCH=386
go build -ldflags "-s -w" -buildmode=c-shared -o ../Release/excel-osx-32.so