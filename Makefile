CC = g++
CFLAGS = -g -Wall -std=c++11
EXECUTABLES = hmmseqgen forward
OBJS = forward.o hmm.o

all: $(EXECUTABLES)

forward: $(OBJS)
	$(CC) $(CFLAGS) -o forward $(OBJS)

hmmseqgen: hmmseqgen.o
	$(CC) $(CFLAGS) -o hmmseqgen hmmseqgen.o

hmm.o: hmm.cpp
	$(CC) $(CFLAGS) -c hmm.cpp

forward.o: forward.cpp
	$(CC) $(CFLAGS) -c forward.cpp

hmmseqgen.o: hmmseqgen.cpp
	$(CC) $(CFLAGS) -c hmmseqgen.cpp

clean:
	rm $(EXECUTABLES) *.o