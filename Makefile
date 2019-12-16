CC = gcc
EXE = x86_64-w64-mingw32-gcc
CFLAGS = -g -Wall -Werror -Wpedantic -std=c11 -Iinclude/
LIBS = -lm

TARGET=snake
TG_W64=$(TARGET).exe

source_files = main cell coord grid snake world game
headers_only = 

all_headers = $(source_files) $(headers_only)

RAW_DIR =
SRC_NAME = src/
INC_NAME = include/

OBJ_DIR = obj/
W64_NAME = w64/
GCC_NAME = gcc/

SRC_DIR = $(RAW_DIR)$(SRC_NAME)
INC_DIR = $(RAW_DIR)$(INC_NAME)

W64_DIR = $(OBJ_DIR)$(W64_NAME)
GCC_DIR = $(OBJ_DIR)$(GCC_NAME)

_OBJS = $(patsubst %, %.o, $(source_files))
_DEPS = $(patsubst %, %.h, $(all_headers))

DEPS = $(patsubst %, $(INC_DIR)%, $(_DEPS))
OW64 = $(patsubst %, $(W64_DIR)%, $(_OBJS))
OGCC = $(patsubst %, $(GCC_DIR)%, $(_OBJS))

$(W64_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	$(EXE) -c -o $@ $< $(CFLAGS)

$(TG_W64): $(OW64)
	$(EXE) -o $@ $(OW64) $(LIBS)

$(GCC_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OGCC)
	$(CC) -o $@ $(OGCC) $(LIBS)

both: $(OW64) $(OGCC)
	$(EXE) -o $(TG_W64) $(OW64) $(LIBS)
	$(CC) -o $(TARGET) $(OGCC) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OW64) $(TG_W64)
	$(RM) $(OGCC) $(TARGET)

cw64:
	$(RM) $(OW64) $(TG_W64)

cgcc:
	$(RM) $(OGCC) $(TARGET)