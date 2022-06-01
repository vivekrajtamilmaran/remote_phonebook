#compiler
GCC = g++
#compiler flags
CFLAG = -g -Wall
#output file
LFLAGS = -o 
#binary file directory
BIN = ../bin
#source file directory
SRC = ../src
#include file directory
INC = ../inc
#object file directory
OBJ = ../obj
#IFLAG
IFLAGS = -I $(INC)

#valgrind report
CVFLAGS = -v --tool=memcheck --leak-check=full --show-reachable=yes --log-file=valclient

#compile all source file

all: buildServer buildClient

buildServer: $(OBJ)/server.o $(OBJ)/user.o $(OBJ)/phonebook.o  
	$(GCC) $(IFLAGS) $(CFLAG) $(LFLAGS) $(BIN)/server $(OBJ)/server.o $(OBJ)/user.o $(OBJ)/phonebook.o $(SRC)/serverMain.cpp 

buildClient: $(OBJ)/client.o
	$(GCC) $(IFLAGS) $(CFLAG) $(LFLAGS) $(BIN)/client $(OBJ)/client.o $(SRC)/clientMain.cpp

$(OBJ)/server.o: $(SRC)/server.cpp
	$(GCC) $(IFLAGS) $(CFLAG) -c  $(LFLAGS) $(OBJ)/server.o $(SRC)/server.cpp
	
$(OBJ)/client.o: $(SRC)/client.cpp
	$(GCC) $(IFLAGS) $(CFLAG) -c $(LFLAGS) $(OBJ)/client.o $(SRC)/client.cpp

$(OBJ)/user.o: $(SRC)/user.cpp
	$(GCC) $(IFLAGS)  $(CFLAG) -c $(LFLAGS) $(OBJ)/user.o $(SRC)/user.cpp

$(OBJ)/phonebook.o: $(SRC)/phonebook.cpp
	$(GCC) $(IFLAGS) $(CFLAG) -c  $(LFLAGS) $(OBJ)/phonebook.o $(SRC)/phonebook.cpp


#run server
server:
	$(BIN)/server

client:
	$(BIN)/client

clean:
	rm $(BIN)/server 
	rm $(BIN)/client 
	rm $(OBJ)/server.o 
	rm $(OBJ)/client.o 
	rm $(OBJ)/user.o 
	rm $(OBJ)/phonebook.o
