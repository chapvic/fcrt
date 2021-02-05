PROJECT = fcrt

CC = cl
AR = lib
LD = link

DLLNAME = $(PROJECT).dll
LIBNAME = $(PROJECT)_s.lib

CFLAGS  = /c /nologo /O2 /W3 /MT /D "NDEBUG"
ARFLAGS = /out:$(LIBNAME)
LDFLAGS = /nologo /release /version:1.0 /dll /out:$(DLLNAME)

OBJ_D = $(PROJECT).obj
OBJ_S = $(PROJECT)_s.obj

all:	dll lib

dll::
	$(CC) $(CFLAGS) /D "FCRT_DLL" /Fo:$(OBJ_D) fcrt.c
	$(LD) $(LDFLAGS) $(OBJ_D)

lib::
	$(CC) $(CFLAGS) /Fo:$(OBJ_S) fcrt.c
	$(AR) $(ARFLAGS) $(OBJ_S)

clean:
	-del *.obj > nul 2>&1
	-del *.exp > nul 2>&1
	-del *.lib > nul 2>&1
	-del *.dll > nul 2>&1

.PHONY: all clean
