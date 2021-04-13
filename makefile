SRC=./*.cpp ./src/*.cpp ./src/controller/*.cpp ./struct/*.cpp

main:$(SRC)
	g++ $^ -o $@ -L/usr/lib64/mysql -lmysqlclient -lpthread

