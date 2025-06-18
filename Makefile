all: example

# declare variables
CC = g++
CFLAGS = -std=c++23 -g3 -ggdb -Wall -Wextra

BIN_DIR = ./bin
SRC_DIR = .

example: $(BIN_DIR) $(SRC_DIR)/example.cpp $(SRC_DIR)/SegmentTree.h
	$(CC) $(SRC_DIR)/example.cpp $(CFLAGS) -o $(BIN_DIR)/example

clean :
	rm -f $(BIN_DIR)/*