CC = g++
CXXFLAGS = -Wall -g
LDFLAGS = 

all: bin/fakeDev

bin/fakeDev: fakeDev.o dev.o simpleProtocol.o caseChangeProtocol.o fifo.o
	$(CC) $(LDFLAGS) -o $@ $^

.cpp.o:
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	rm  *.o bin/fakeDev

