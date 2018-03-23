#pragma once
#ifndef __COMLINE__
#define __COMLINE__
#include <ctime>
#include "struct.h"
#include <string>
#include <iostream>
#include "mysqlc.h"
class ComLine {
private:
	time_t rawtime;
	struct tm *ptminfo;
	MySQLC* mc;
private:
	std::string* cutstr(char*);
	void print_time(std::string);
public:
	ComLine();
	~ComLine();
public:
	void startTime();
	void endTime();
	struct Config getParam(int argc, char* argv[]);
	bool checkConnect(struct Config config);
};


#endif // !__COMLINE__


