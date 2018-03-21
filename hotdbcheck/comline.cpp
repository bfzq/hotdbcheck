#include "comline.h"



ComLine::ComLine() {
	
}


ComLine::~ComLine()
{
}

void ComLine::startTime()
{
}

void ComLine::endTime()
{
}

struct Config ComLine::getParam(int argc, char * argv[]) {
	struct Config config;
	for (int i = 1; i < argc; i++) {
		std::string t = std::string(argv[i]);
		int idx = t.find('=', 1);
		std::string tmp = t.substr(2, idx - 2);
		if (tmp == __OPTION_HOTDB_HOST__) {
			config.hotdbHost = t.substr(idx + 1);
		}
		else if (tmp == __OPTION_HOTDB_PORT__) {
			config.hotdbPort = atoi(t.substr(idx + 1).c_str());
		}
		else if (tmp == __HELP__) {
			std::cout << "This is help page." << std::endl;
		}
		else if(tmp == __OPTION_HOTDB_USER__) {
			config.hotdbUser = t.substr(idx + 1);
		}
		else if (tmp == __OPTION_HOTDB_PASSWORD__) {
			config.hotdbPassword = t.substr(idx + 1);
		}
		else if (tmp == __OPTION_HOTDB_DB__) {
			config.hotdbDB = t.substr(idx + 1);
		}
		else if (tmp == __OPTION_MYSQL_HOST__) {
			config.mysqlHost = t.substr(idx + 1);
		}
		else if (tmp == __OPTION_MYSQL_PORT__) {
			config.mysqlPort = atoi(t.substr(idx + 1).c_str());

		}
		else if (tmp == __OPTION_MYSQL_PASSWORD__) {
			config.mysqlPassword = t.substr(idx + 1);

		}
		else if (tmp == __OPTION_MYSQL_USER__) {
			config.mysqlUser = t.substr(idx + 1);

		}
		else if (tmp == __OPTION_MYSQL_DB__) {
			config.mysqlDB = t.substr(idx + 1);

		}
		else if (tmp == __OPTION_TASKS__) {
			config.tasks = atoi(t.substr(idx + 1).c_str());

		}
		else if (tmp == __OPTION_EACH_DATA__) {
			config.eachData = atoi(t.substr(idx + 1).c_str());

		}
		else if (tmp == __OPTION_TABLE_NAME__) {
			config.tableName = t.substr(idx + 1);

		}
		else if (tmp == __CACHE__) {
			config.cache = atoi(t.substr(idx + 1).c_str());

		}
		else if (tmp == __PATH__) {
			config.path = t.substr(idx + 1);
		}
	}
	return config;
}
