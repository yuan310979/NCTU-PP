CC:=gcc
NVCC:=nvcc
LIB:=-lm
PROGRAMNAME1:=wave
PROGRAMNAME2:=cuda_wave

all: cuda_wave wave

wave:	serial_wave.c
	$(CC) $^ -o $(PROGRAMNAME1) $(LIB) 

cuda_wave: cuda_wave.cu
	$(NVCC) $^ -o $(PROGRAMNAME2)	

clean:
	rm $(PROGRAMNAME1) $(PROGRAMNAME2) 
