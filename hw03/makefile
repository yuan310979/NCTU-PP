CC:=/usr/lib64/openmpi/bin/mpicc
LIB:=-lm
PROGRAMNAME1:=prime
PROGRAMNAME2:=integrate
BINDIR:=bin
OBJ1:=prime.o
OBJ2:=integrate.o

all: prime integrate

prime: $(OBJ1) 
	$(CC) $^ $(LIB) -o $(BINDIR)/$(PROGRAMNAME1) 

integrate: $(OBJ2)
	$(CC) $^ $(LIB) -o $(BINDIR)/$(PROGRAMNAME2) 

prime.o: prime.c 
	$(CC) -c $^ -o $@ 

integrate.o: integrate.c
	$(CC) -c $^ -o $@

