# compiler and flags
CC := gcc
CFLAGS := -fPIC

# directories
LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj

# source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# target names
LIB_NAME_LINUX = $(LIB_DIR)/liblongint.so
LIB_NAME_WINDOWS = $(LIB_DIR)/liblongint.dll
LIB_NAME_MACOS = $(LIB_DIR)/liblongint.dylib

# target platform
TARGET_PLATFORM := linux	# change to 'windows' or 'macos'

ifeq ($(TARGET_PLATFORM), windows)
	CC := mingw-w64-gcc
	LIB_NAME := $(LIB_NAME_WINDOWS)
	LDFLAGS := -shared
else ifeq ($(TARGET_PLATFORM), macos)
	LIB_NAME := $(LIB_NAME_MACOS)
	LDFLAGS := -dynamiclib
else
	LIB_NAME := $(LIB_NAME_LINUX)
	LDFLAGS := -shared
endif

.PHONY: all clean

all: $(OBJ_DIR) $(LIB_DIR) $(LIB_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(LIB_NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

# object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
  
clean:
	rm -f $(LIB_NAME) $(OBJ_FILES)
