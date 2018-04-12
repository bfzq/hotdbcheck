#include "comline.h"



ComLine::ComLine() {
	
}


ComLine::~ComLine() {
	delete mc;
}

void ComLine::startTime() {
}

void ComLine::endTime() {
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
			std::cout << __OPTION_HOTDB_DB__ << "	" << "is HotDB logic db. " << "Default is test." << std::endl;
			std::cout << __OPTION_HOTDB_PORT__ << "	" << "is HotDB port. " << "Default is 3323." << std::endl;
			std::cout << __OPTION_HOTDB_USER__ << "	" << "is HotDB server account. " << "Default is root." << std::endl;
			std::cout << __OPTION_HOTDB_PASSWORD__ << "	" << "is HotDB server password. " << "Default is root." << std::endl;
			std::cout << __OPTION_HOTDB_HOST__ << "	" << "is HotDB server ip. " << "Default is 127.0.0.1." << std::endl << std::endl;
			std::cout << __OPTION_MYSQL_HOST__ << "	" << "is HotDB config ip. " << "Default is 127.0.0.1." << std::endl;
			std::cout << __OPTION_MYSQL_PASSWORD__ << "	" << "is HotDB config password. " << "Default is 123456." << std::endl;
			std::cout << __OPTION_MYSQL_PORT__ << "	" << "is HotDB config port. " << "Default is 3306." << std::endl;
			std::cout << __OPTION_MYSQL_USER__ << "	" << "is HotDB config account. " << "Default is hotdb_config" << std::endl;
			std::cout << __OPTION_MYSQL_DB__ << "	" << "is HotDB config db. " << "Default is hotdb_config." << std::endl << std::endl;
			std::cout << __OPTION_TASKS__ << "		" << "is running task. " << "Default is 8." << std::endl;
			std::cout << __OPTION_EACH_DATA__ << "	" << "is number of check for each task. " << "Default is 10000." << std::endl;
			std::cout << __OPTION_TABLE_NAME__ << "	" << "is table_name. " << "Default is t1." << std::endl;
			std::cout << __HELP__ << "		" << "show help info.	" << std::endl;
			exit(0);
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

bool ComLine::checkConnect(struct Config config) {
	mc = new MySQLC();
	if (!mc->connect(config.hotdbHost,config.hotdbUser, config.hotdbPassword, config.hotdbDB, config.hotdbPort)) {
		std::cout << "To connect hotdb Error." << std::endl;
		delete mc ;
		mc = nullptr ;
		return false;
	}
	mc->disConnect();
	if (!mc->connect(config.mysqlHost, config.mysqlUser, config.mysqlPassword, config.mysqlDB, config.mysqlPort)) {
		std::cout << "To connect mysql Error." << std::endl;
		delete mc ;
		mc = nullptr ;
		return false;
	}
	delete mc ;
	mc = nullptr ;
	return true;
}
