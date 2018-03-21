#include "mysqlc.h"



MySQLC::MySQLC() {
	mysql_init(&mysql);
}


MySQLC::~MySQLC() {
	disConnect();
}


bool MySQLC::connect(std::string host, std::string user, std::string password, std::string db, int port) {
	if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), port, NULL, 0)) {
		return false;
	}
	return true;
}

void MySQLC::disConnect() {
	mysql_close(&mysql);
	mysql_library_end();
}

bool MySQLC::query(std::string sql, std::function<bool(MYSQL_ROW)> f) {
	if (!mysql_query(&mysql, sql.c_str())) {
		if (res = mysql_store_result(&mysql)) {
			MYSQL_ROW row;
			int num = mysql_num_rows(res);
			bool retVal;
			if (num) {
				while ((row = mysql_fetch_row(res)) != NULL) {
					retVal = f(row);
				}
			}
			else {
				retVal = f(NULL);
			}
		
			mysql_free_result(res);
			return retVal;
		}
	}
	else {
		std::cout << mysql_error(&mysql) << " == " << sql << std::endl;
		return false;
	}
}

std::vector<std::string> MySQLC::getValue(std::string column)
{
	return std::vector<std::string>();
}
