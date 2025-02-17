CFLAGS = -g -Wall -Wextra -Wpedantic -std=c11 -Iinclude/
LIBS = 
CC = x86_64-w64-mingw32-gcc

TARGET = snake

_SRCS = main snake board coord input output
_HEAD = thread

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = obj/

_OBJS = $(patsubst %, %.o, $(_SRCS))
_DEPS = $(patsubst %, %.h, $(_SRCS) $(_HEAD))

DEPS = $(patsubst %, $(INC_DIR)%, $(_DEPS))
_OBJ = $(patsubst %, $(OBJ_DIR)%, $(_OBJS))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET).exe: $(_OBJ)
	$(CC) -o $@ $(_OBJ) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(_OBJ) $(TARGET)

.PHONY: debug
debug:
	gdb $(TARGET)
