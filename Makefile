all: main

# declare variables
CC = g++
CFLAGS = -std=c++23 -g3 -ggdb -Wall -Wextra

BIN_DIR = ./bin
SRC_DIR = .

main: $(BIN_DIR) $(SRC_DIR)/main.cpp $(SRC_DIR)/SegmentTree.h
	$(CC) $(SRC_DIR)/main.cpp $(CFLAGS) -o $(BIN_DIR)/main

clean :
	rm -f $(BIN_DIR)/*