# compiler and flags
CC := gcc
CFLAGS := -fPIC -fprofile-arcs -ftest-coverage #-march=native -mrdrnd
WFLAGS = -Wall -Wpedantic -Wextra
LDFLAGS = -Llib -llongint
RPATH = -Wl,-rpath=./lib

# directories
LIB_DIR = lib
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
DEV_DIR = dev
INC_DIR = include
EXX_DIR = example
TEST_DIR = test

# environment variables
INPUT_DIR = $(shell pwd)/$(TEST_DIR)/assets/scan/
OUTPUT_DIR = $(shell pwd)/$(TEST_DIR)/assets/print/

# library files
LIB_SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/$(SRC_DIR)/%.o, $(LIB_SRC_FILES))
# example files
EXX_SRC_FILES = $(wildcard $(EXX_DIR)/ex_*.c)
EXX_OBJ_FILES = $(patsubst $(EXX_DIR)/%.c, $(OBJ_DIR)/$(EXX_DIR)/%.o, $(EXX_SRC_FILES))
EXX_TARGETS = $(patsubst $(EXX_DIR)/%.c, $(BIN_DIR)/%, $(EXX_SRC_FILES))
# test files
TEST_SRC_FILES = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/$(TEST_DIR)/%.o, $(TEST_SRC_FILES))
TEST_TARGET = $(BIN_DIR)/test_all

# library target names
LIB_NAME_LINUX = $(LIB_DIR)/liblongint.so
LIB_NAME_WINDOWS = $(LIB_DIR)/liblongint.dll
LIB_NAME_MACOS = $(LIB_DIR)/liblongint.dylib

# library target platform
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

.PHONY: clean dev examples tests

all: $(OBJ_DIR) $(LIB_DIR) $(LIB_NAME)

dev: 
	bash -c "shopt -s nullglob; mv $(DEV_DIR)/ex_*.c $(EXX_DIR)/ 2>/dev/null || true"
	bash -c "shopt -s nullglob; mv $(DEV_DIR)/*.h $(INC_DIR)/ 2>/dev/null || true"
	bash -c "shopt -s nullglob; mv $(DEV_DIR)/lil_*.c $(SRC_DIR)/ 2>/dev/null || true"
	bash -c "shopt -s nullglob; mv $(DEV_DIR)/test_*.c $(TEST_DIR)/ 2>/dev/null || true"
	make

examples: $(OBJ_DIR) $(BIN_DIR) $(EXX_TARGETS)

tests: $(OBJ_DIR) $(BIN_DIR) $(TEST_TARGET)
	INPUT_DIR=$(INPUT_DIR) OUTPUT_DIR=$(OUTPUT_DIR) $(TEST_TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/{$(SRC_DIR),$(EXX_DIR),$(TEST_DIR)}

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_NAME): $(LIB_OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^ -lgcov

$(EXX_TARGETS): $(EXX_OBJ_FILES)
	@for obj in $^; do \
		exe_name=$(BIN_DIR)/$$(basename $$(basename $$obj .o) .c); \
		$(CC) -Iinclude -o $$exe_name $$obj -L$(LIB_DIR) -llongint $(RPATH); \
		echo $(CC) -Iinclude -o $$exe_name $$obj -L$(LIB_DIR) -llongint $(RPATH); \
	done

$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CC) -Iinclude -fprofile-arcs -ftest-coverage -o $@ $^ -L$(LIB_DIR) -llongint $(RPATH) -lcriterion -lgcov

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -Iinclude $(CFLAGS) $(WFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(EXX_DIR)/%.o: $(EXX_DIR)/%.c
	$(CC) -Iinclude $(WFLAGS) -c -o $@ $<

$(OBJ_DIR)/$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) -Iinclude $(WFLAGS) -c -o $@ $< -lcriterion -lgcov

clean:
	rm -rf $(LIB_DIR) $(OBJ_DIR) $(BIN_DIR)
