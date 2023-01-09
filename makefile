CC = g++

# More warning, C++17, enable debugging symbols and additional debug info
CFLAGS = -Wall -Wextra -Wshadow -Wpedantic -std=c++20 -g

OBJ = obj
LIB = lib
SRC = src

BIN = binary
TEST = tests

.PHONY: clean test

all: $(BIN)

$(BIN): $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/random.o $(OBJ)/logic.o $(OBJ)/mines.o $(OBJ)/main.o
		$(CC) -o $(BIN) $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/random.o $(OBJ)/logic.o $(OBJ)/mines.o $(OBJ)/main.o

$(OBJ)/grid.o: $(LIB)/color.hpp $(LIB)/msgassert.hpp $(LIB)/grid.hpp $(SRC)/grid.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/grid.cpp -o $(OBJ)/grid.o

$(OBJ)/input.o: $(LIB)/msgassert.hpp $(LIB)/actions.hpp $(LIB)/input.hpp $(SRC)/input.cpp
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

$(TEST): $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/test.o
		$(CC) -lgtest -o $(TEST) $(OBJ)/input.o $(OBJ)/test.o $(OBJ)/grid.o
		./$(TEST)

$(OBJ)/test.o: $(LIB)/input.hpp $(SRC)/test.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/test.cpp -o $(OBJ)/test.o

clean:
	rm -rf $(OBJ)/* $(BIN) $(TEST)
