# compiler options
CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

# directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIB_DIR = lib
LIB_NAME = $(LIB_DIR)/liblongintlib.so

# source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.PHONY: all clean

# targets
all: $(OBJ_DIR) $(LIB_DIR) $(LIB_NAME)

# create dynamic library
$(LIB_NAME): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $(LIB_NAME) $^

# make sure obj and directories exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean: 
	rm -rf $(OBJ_DIR)/*.o $(LIB_NAME)
