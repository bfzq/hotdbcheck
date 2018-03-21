#pragma once
#ifndef __COMLINE__
#define __COMLINE__
#include <ctime>
#include "struct.h"
#include <string>
#include <iostream>

class ComLine {
private:
	time_t rawtime;
	struct tm *ptminfo;
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
};


#endif // !__COMLINE__


