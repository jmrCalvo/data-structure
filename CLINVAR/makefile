SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS =  -g -c -std=c++11 -I$(INC)

all: $(BIN)/main

$(BIN)/main: $(OBJ)/main.o $(OBJ)/enfermedad.o $(OBJ)/mutacion.o  $(OBJ)/clinvar.o
	$(CXX) -o $(BIN)/main $(OBJ)/enfermedad.o $(OBJ)/mutacion.o $(OBJ)/clinvar.o $(OBJ)/main.o
# ************ Creacion de Objetos ************

$(OBJ)/enfermedad.o: $(SRC)/enfermedad.cpp $(INC)/enfermedad.h
	$(CXX) $(CPPFLAGS) $(SRC)/enfermedad.cpp -o $(OBJ)/enfermedad.o

$(OBJ)/mutacion.o: $(SRC)/mutacion.cpp $(INC)/mutacion.h $(OBJ)/enfermedad.o
	$(CXX) $(CPPFLAGS) $(SRC)/mutacion.cpp -o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o

$(OBJ)/clinvar.o: $(SRC)/clinvar.cpp $(INC)/clinvar.h $(OBJ)/mutacion.o $(OBJ)/enfermedad.o
	$(CXX) $(CPPFLAGS) $(SRC)/clinvar.cpp -o $(OBJ)/clinvar.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o

$(OBJ)/main.o: $(SRC)/main.cpp $(OBJ)/clinvar.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o $(OBJ)/clinvar.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o
# ************ documentación *******
documentacion:
	doxygen doc/Doxyfile /doc

# ************ Limpieza ************

clean:
	echo "Limpiando..."
	rm $(OBJ)/*

mrproper:
	rm $(BIN)/*
