SRC=./*.cpp ./src/*.cpp ./src/controller/*.cpp ./src/service/*.cpp ./struct/*.cpp
BIN=main
LDFLAGS=-L/usr/lib64/mysql -L/usr/local/lib 
CC=g++

.PHONY:$(BIN)

$(BIN):$(SRC)
	$(CC) $^ -o $@ $(LDFLAGS) -lmysqlclient -lpthread -std=c++11 -ljsoncpp -lhiredis -lcrypto 

.PHONY:clean
clean:
	rm -rf $(BIN)
