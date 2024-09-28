CC = gcc
CFLAGS = -Wall -Werror -Iinclude
SRC_DIR = src
OBJ_DIR = obj
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
BIN_DIR = bin
BIN = $(BIN_DIR)/csv

all: $(BIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# This command is for windows system only
clean:
	del /q /f $(OBJ_DIR)\* $(BIN_DIR)\*