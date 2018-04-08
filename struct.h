#pragma once
#ifndef __STRUCT__
#define __STRUCT__

#include <string>
#include <thread>

#define __OPTION_HOTDB_HOST__ "hotdb-host"
#define __OPTION_HOTDB_PORT__ "hotdb-port"
#define __OPTION_HOTDB_USER__ "hotdb-user"
#define __OPTION_HOTDB_PASSWORD__ "hotdb-password"
#define __OPTION_HOTDB_DB__ "hotdb-db"

#define __OPTION_MYSQL_HOST__ "mysql-host"
#define __OPTION_MYSQL_PORT__ "mysql-port"
#define __OPTION_MYSQL_PASSWORD__ "mysql-password"
#define __OPTION_MYSQL_USER__ "mysql-user"
#define __OPTION_MYSQL_DB__ "mysql-db"

#define __OPTION_TASKS__ "tasks"
#define __OPTION_EACH_DATA__ "each-data"
#define __OPTION_TABLE_NAME__ "table-name"
#define __CACHE__ "cache"
#define __HELP__ "help"

#define __PATH__ "path"


struct Config {
	std::string hotdbHost;
	std::string hotdbUser;
	std::string hotdbPassword;
	std::string hotdbDB;
	int hotdbPort;
	
	std::string mysqlHost;
	std::string mysqlUser;
	std::string mysqlPassword;
	std::string mysqlDB;
	int mysqlPort;

	int tasks; // 线程数量
	int eachData; // 给个线程处理数据行数
	bool cache; // 是否一次性缓存数据
	std::string tableName; // 处理的表

	std::string path;

	std::string ruleColumn;

	Config(std::string hh, std::string hu, std::string hp, std::string hd, int hpo,
		std::string mh, std::string mu, std::string mp, std::string md, int mpo,
		int t, int ed, bool c, std::string tn, std::string p) {
		hotdbHost = hh;
		hotdbUser = hu;
		hotdbPassword = hp;
		hotdbDB = hd;
		hotdbPort = hpo;
		mysqlHost = mh;
		mysqlUser = mu;
		mysqlPassword = mp;
		mysqlDB = md;
		mysqlPort = mpo;
		tasks = t;
		eachData = ed;
		cache = c;
		tableName = tn;
		path = p;
	}

	Config() {
		hotdbHost = "127.0.0.1";
		hotdbUser = "root";
		hotdbPassword = "root";
		hotdbDB = "test";
		hotdbPort = 3323;
		mysqlHost = "127.0.0.1";
		mysqlUser = "root";
		mysqlPassword = "root";
		mysqlDB = "hotdb_config";
		mysqlPort = 3306;
		tasks = 8;
		eachData = 10000;
		cache = true;
		tableName = "t1";
		path = "config.cnf";
	}
};

#endif // !__STRUCT__


