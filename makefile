MYSQL_INCLUDE=-I/usr/local/mysql/include
MYSQL_LIB=/usr/local/mysql/lib/libmysqlclient.a
hotdbcheck:main.o threadpool.o comline.o mysqlc.o programfocus.o
	g++ -g -o hotdbcheck main.o threadpool.o comline.o mysqlc.o programfocus.o $(MYSQL_LIB) -ldl -lpthread
programfocus.o:programfocus.cpp
	g++ -g -std=c++11 -o programfocus.o -c programfocus.cpp $(MYSQL_INCLUDE)
main.o:main.cpp programfocus.h
	g++ -g -std=c++11 -o main.o -c main.cpp $(MYSQL_INCLUDE)
threadpool.o:threadpool.cpp threadpool.h nocopyable.h
	g++ -g -std=c++11 -o threadpool.o -c threadpool.cpp
comline.o:comline.cpp comline.h
	g++ -g -std=c++11 -o comline.o -c comline.cpp $(MYSQL_INCLUDE)
mysqlc.o:mysqlc.cpp mysqlc.h
	g++ -g -std=c++11 -o mysqlc.o -c mysqlc.cpp $(MYSQL_INCLUDE)
clean:
	rm -rf *.o hotdbcheck
install:
	mv hotdbcheck /usr/bin/
uninstall:
	mv /usr/bin/hotdbcheck /tmp/
