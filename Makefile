CC = g++
CXXFLAGS = -Wall -g
LDFLAGS = 

OBJ_PATH=obj
all: bin/fakeDev

bin/fakeDev: $(OBJ_PATH)/fakeDev.o $(OBJ_PATH)/dev.o $(OBJ_PATH)/serial.o $(OBJ_PATH)/simpleProtocol.o
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_PATH)/%.o: %.cpp
	$(CC) -c $(CXXFLAGS) -o $@ $<

clean:
	rm  $(OBJ_PATH)/*.o bin/fakeDev

