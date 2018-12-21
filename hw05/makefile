CC:=g++
LIB:=-lOpenCL
PROGRAMNAME:=histogram

all: histogram 

histogram: histogram.cpp
	$(CC) $^ -o $(PROGRAMNAME)	$(LIB)

clean:
	rm $(PROGRAMNAME)
