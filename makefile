CC = g++
DEBUG = -g
MAKE = make
PROGRAM = hotdbcheck

OS = $(shell uname -s)
ifeq ($(OS),Linux)
	MYSQL_INCLUDE = `mysql_config --cflags`
	MYSQL_LIB = `mysql_config --variable=pkglibdir`/libmysqlclient.a
else
	MYSQL_INCLUDE = -I/usr/local/mysql/include
	MYSQL_LIB = /usr/local/mysql/lib/libmysqlclient.a
endif

CFLAGS = -std=c++11 $(MYSQL_INCLUDE)
LFLAGS = -ldl -lpthread

OBJECTS = main.o threadpool.o comline.o mysqlc.o programfocus.o

$(PROGRAM):$(OBJECTS)
	$(CC) $(LFLAGS) -o $(PROGRAM) $(OBJECTS) $(MYSQL_LIB)
%.o:%.cpp
	$(CC) $(DEBUG) $(CFLAGS)  -c $< -o $@
clean:
	rm -rf *.o $(PROGRAM)
install:
	mv hotdbcheck /usr/bin/
uninstall:
	mv /usr/bin/hotdbcheck /tmp/
