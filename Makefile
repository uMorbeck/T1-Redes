CC = gcc
LDFLAGS = 
BUILD_DIR = .
BIN_DIR = $(BUILD_DIR)/bin
INC_DIR = $(BUILD_DIR)/inc
SRC_DIR = $(BUILD_DIR)/src
OBJ_DIR = $(BUILD_DIR)/obj
CFLAGS = -c -Wall -I$(INC_DIR)
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
EXE = bin/main

all: $(EXE)

$(EXE) : $(OBJ)
	@mkdir -p $(@D)
	$(CC) $(OBJ_DIR)/*.o -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(EXE)