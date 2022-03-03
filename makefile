CC = g++

CFLAGS = -Wall -Wextra -std=c++17 -g

OBJ = obj
LIB = lib
SRC = src

BIN = binary

$(BIN): $(OBJ)/grid.o $(OBJ)/input.o $(OBJ)/random.o $(OBJ)/logic.o $(OBJ)/mines.o $(OBJ)/main.o
		$(CC) -o $(BIN) $(OBJ)/*.o

$(OBJ)/grid.o: $(LIB)/grid.hpp $(SRC)/grid.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/grid.cpp -o $(OBJ)/grid.o

$(OBJ)/input.o: $(LIB)/input.hpp $(SRC)/input.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/input.cpp -o $(OBJ)/input.o

$(OBJ)/random.o: $(LIB)/random.hpp $(SRC)/random.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/random.cpp -o $(OBJ)/random.o

$(OBJ)/logic.o: $(LIB)/random.hpp $(LIB)/logic.hpp $(SRC)/logic.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/logic.cpp -o $(OBJ)/logic.o

$(OBJ)/mines.o: $(LIB)/input.hpp $(LIB)/grid.hpp $(LIB)/mines.hpp $(SRC)/mines.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/mines.cpp -o $(OBJ)/mines.o

$(OBJ)/main.o: $(LIB)/mines.hpp $(SRC)/main.cpp
		$(CC) $(CFLAGS) -I$(LIB) -c $(SRC)/main.cpp -o $(OBJ)/main.o

clean:
	rm -rf $(OBJ)/* $(BIN)
