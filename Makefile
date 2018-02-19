CC = g++
CFLAGS = -g -Wall -std=c++11
EXECUTABLES = hmmseqgen

all: $(EXECUTABLES)

hmmseqgen: hmmseqgen.o
	$(CC) $(CFLAGS) -o hmmseqgen hmmseqgen.o

hmmseqgen.o: hmmseqgen.cpp
	$(CC) $(CFLAGS) -c hmmseqgen.cpp

clean:
	rm $(EXECUTABLES) *.o