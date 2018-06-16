CC = g++
CXXFLAGS = -Wall -g
LDFLAGS = 

all: bin/fakeDev

bin/fakeDev: fakeDev.o dev.o serial.o simpleProtocol.o
	$(CC) $(LDFLAGS) -o $@ $^

.cpp.o:
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	rm  *.o bin/fakeDev

