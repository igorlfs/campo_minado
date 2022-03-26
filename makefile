CC = g++

CFLAGS = -Wall -Wextra -std=c++17 -g -Wshadow -Wpedantic

OBJ = obj
LIB = lib
SRC = src

BIN = binary
TEST = tests

.PHONY: clean test

all: $(BIN) $(TEST)

$(BIN): $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/random.o $(OBJ)/logic.o $(OBJ)/mines.o $(OBJ)/main.o
		$(CC) -o $(BIN) $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/random.o $(OBJ)/logic.o $(OBJ)/mines.o $(OBJ)/main.o

$(OBJ)/grid.o: $(LIB)/color.hpp $(LIB)/msgassert.hpp $(LIB)/grid.hpp $(SRC)/grid.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/grid.cpp -o $(OBJ)/grid.o

$(OBJ)/input.o: $(LIB)/actions.hpp $(LIB)/input.hpp $(SRC)/input.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/input.cpp -o $(OBJ)/input.o

$(OBJ)/random.o: $(LIB)/random.hpp $(SRC)/random.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/random.cpp -o $(OBJ)/random.o

$(OBJ)/logic.o: $(LIB)/actions.hpp $(LIB)/random.hpp $(LIB)/logic.hpp $(SRC)/logic.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/logic.cpp -o $(OBJ)/logic.o

$(OBJ)/mines.o: $(LIB)/actions.hpp $(LIB)/msgassert.hpp $(LIB)/input.hpp $(LIB)/logic.hpp $(LIB)/mines.hpp $(SRC)/mines.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/mines.cpp -o $(OBJ)/mines.o

$(OBJ)/main.o: $(LIB)/actions.hpp $(LIB)/mines.hpp $(SRC)/main.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/main.cpp -o $(OBJ)/main.o

test: $(TEST)

$(TEST): $(OBJ)/input.o $(OBJ)/test.o
		$(CC) -lgtest -o $(TEST) $(OBJ)/input.o $(OBJ)/test.o
		./$(TEST)

$(OBJ)/test.o: $(LIB)/input.hpp $(SRC)/test.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/test.cpp -o $(OBJ)/test.o

clean:
	rm -rf $(OBJ)/* $(BIN) $(TEST)
