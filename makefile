MYSQL_INCLUDE=-I/usr/local/mysql/include
MYSQL_LIB=/usr/local/mysql/lib/libmysqlclient.a
#MYSQL_INCLUDE=`mysql_config --cflags`
#MYSQL_LIB=`mysql_config --variable=pkglibdir`/libmysqlclient.a

RELEASE=0

CFLAGS=
LFLAGS=

# [args] 生成模式. 0代表debug模式, 1代表release模式. make RELEASE=1.
ifeq ($(RELEASE),0)
# debug
	CFLAGS += -g -std=c++11
	LFLAGS += -ldl -lpthread -g
else
# release
	CFLAGS += -std=c++11
	LFLAGS += -ldl -lpthread
endif

hotdbcheck:main.o threadpool.o comline.o mysqlc.o programfocus.o
	g++ $(LFLAGS) -o hotdbcheck main.o threadpool.o comline.o mysqlc.o programfocus.o $(MYSQL_LIB)
programfocus.o:programfocus.cpp
	g++ $(CFLAGS) -o programfocus.o -c programfocus.cpp $(MYSQL_INCLUDE)
main.o:main.cpp programfocus.h
	g++ $(CFLAGS) -o main.o -c main.cpp $(MYSQL_INCLUDE)
threadpool.o:threadpool.cpp threadpool.h nocopyable.h
	g++ $(CFLAGS) -o threadpool.o -c threadpool.cpp
comline.o:comline.cpp comline.h
	g++ $(CFLAGS) -o comline.o -c comline.cpp $(MYSQL_INCLUDE)
mysqlc.o:mysqlc.cpp mysqlc.h
	g++ $(CFLAGS) -o mysqlc.o -c mysqlc.cpp $(MYSQL_INCLUDE)
clean:
	rm -rf *.o hotdbcheck
install:
	mv hotdbcheck /usr/bin/
uninstall:
	mv /usr/bin/hotdbcheck /tmp/
