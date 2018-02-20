CC = g++
CFLAGS = -g -Wall -std=c++11
EXECUTABLES = hmmseqgen forvit
OBJS = forvit.o hmm.o

all: $(EXECUTABLES)

forvit: $(OBJS)
	$(CC) $(CFLAGS) -o forvit $(OBJS)

hmmseqgen: hmmseqgen.o hmm.o
	$(CC) $(CFLAGS) -o hmmseqgen hmmseqgen.o hmm.o

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) -c $*.cpp

# hmm.o: hmm.cpp
# 	$(CC) $(CFLAGS) -c hmm.cpp

# forvit.o: forvit.cpp
# 	$(CC) $(CFLAGS) -c forward.cpp

# hmmseqgen.o: hmmseqgen.cpp
# 	$(CC) $(CFLAGS) -c hmmseqgen.cpp

clean:
	rm $(EXECUTABLES) *.o