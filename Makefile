OBJ_LIST = hash.obj
CFLAGS = /nologo /W3 /EHsc /Za /DWIN /D_CRT_SECURE_NO_DEPRECATE

DLLNAMES = hash.dll
build: tema1.exe
tema1.exe: main.obj parsecommand.obj hashtable.obj bucket.obj hash.lib
	link /nologo /out:tema1.exe hashtable.obj bucket.obj main.obj parsecommand.obj hash.lib
hash.lib: hash.dll
	link /nologo /dll /out:hash.dll /implib:hash.lib
hash.obj: hash.c
	cl $(CFLAGS) /c hash.c
hashtable.obj: hashtable.c
	cl $(CFLAGS) /c hashtable.c
bucket.obj: bucket.c
	cl $(CFLAGS) /c bucket.c
main.obj: main.c
	cl $(CFLAGS) /c main.c
parsecommand.obj: parsecommand.c
	cl $(CFLAGS) /c parsecommand.c
obj_clean:
	del *.obj
dll_clean:
	del $(DLLNAMES)
