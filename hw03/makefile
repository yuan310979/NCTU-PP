CC:=/usr/lib64/openmpi/bin/mpicc
LIB:=-lm
PROGRAMNAME:=prime
BINDIR:=bin
OBJ:=prime.o

all: $(OBJ) 
	$(CC) $^ $(LIB) -o $(BINDIR)/$(PROGRAMNAME) 

prime.o: prime.c 
	$(CC) -c $^ -o $@ 

