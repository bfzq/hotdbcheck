#pragma once
#ifndef __PROGRAMFOCUS__
#define __PROGRAMFOCUS__

#include <vector>
#include "struct.h"
#include "comline.h"
#include "mysqlc.h"
#include "threadpool.h"

class ProgramFocus {
private:
		void init();
public:
	ProgramFocus();
	ProgramFocus(int argc, char* argv[]);
	~ProgramFocus();
private:
	ComLine* cl;
	MySQLC* mysqlc;
	struct Config config;
	std::vector<std::string*> keys;
	fivestar::ThreadPool threadPool;
private:
	bool getRuleColumn();
	bool getRuleValue();
	void deleteVector(std::vector<std::string*>);
	bool run(std::function<void(std::vector<std::string*>)> f);
public:
	bool main();
};
#endif // !__PROGRAMFOCUS__



