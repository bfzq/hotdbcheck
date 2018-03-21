#pragma once
#ifndef __MYSQLC__
#define __MYSQLC__

#include "mysql.h"
#include <string>
#include <vector>
#include <iostream>
#include <functional>

class MySQLC {
public:
	MySQLC();
	~MySQLC();
private:
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
public:
	bool connect(std::string host, std::string user, std::string password, std::string db, int port);
	void disConnect();
	bool query(std::string sql, std::function<bool(MYSQL_ROW)> f);
	std::vector<std::string> getValue(std::string column);
};

#endif // !__MYSQLC__