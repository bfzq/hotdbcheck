#include "programfocus.h"


void ProgramFocus::init() {
	cl = new ComLine();
	mysqlc = new MySQLC();
}

ProgramFocus::ProgramFocus() {
	init();
}

ProgramFocus::ProgramFocus(int argc, char * argv[]) {
	init();
	config = cl->getParam(argc, argv);
}


ProgramFocus::~ProgramFocus() {
	delete cl;
	cl = nullptr;
	delete mysqlc;
	mysqlc = nullptr;
}

bool ProgramFocus::getRuleColumn() {
	if (mysqlc->connect(config.mysqlHost, config.mysqlUser, config.mysqlPassword, config.mysqlDB, config.mysqlPort)) {
		std::string sql = "select rule_column \
		from " + config.mysqlDB + ".hotdb_tableinfo as t join " + config.mysqlDB + ".hotdb_rule as r on r.rule_id=t.rule_id \
		join " + config.mysqlDB + ".hotdb_logic_db as l on t.logic_dbid=l.logic_dbid \
	where t.table_name='" + config.tableName + "' and l.logic_dbname='" + config.hotdbDB + "';";
		if (!mysqlc->query(sql, [&](MYSQL_ROW row) {
			if (row[0] != NULL) {
				config.ruleColumn = row[0];
				return true;
			}else {
				return false;
			}
		})) {
			mysqlc->disConnect();
			return false;
			std::cout << "RULE COLUMN NULL" << std::endl;
		}
		mysqlc->disConnect();
		return true;
	}
}

bool ProgramFocus::getRuleValue() {
	if (mysqlc->connect(config.hotdbHost, config.hotdbUser, config.hotdbPassword, config.hotdbDB, config.hotdbPort)) {
		
		std::string sql = "select distinct " + config.ruleColumn + " as c1 from " + config.tableName;
		if (!mysqlc->query(sql, [&](MYSQL_ROW row) {
			keys.push_back(row[0]);
			return true;
		})) {
			mysqlc->disConnect();
			return false;
		}
	}
	mysqlc->disConnect();
	return true;
}

bool ProgramFocus::run(std::function<void(std::vector<std::string>)> f) {
	
	getRuleValue();
	int n = keys.size() / config.eachData;
	threadPool.setMaxQueueSize(config.tasks);
	threadPool.start(config.tasks);
	for (int i = 0; i < n + 1; i++) {
		std::vector<std::string> key;
		for (int j = 0; j < config.eachData && keys.size() > 0; j++) {
			key.push_back(keys.back());
			keys.pop_back();
		}

		threadPool.run(std::bind(f,key));
	}
}

bool ProgramFocus::main() {
	getRuleColumn();
	run([&](std::vector<std::string> key) {
		MySQLC* mysqlc = new MySQLC();
		mysqlc->connect(config.hotdbHost, config.hotdbUser, config.hotdbPassword, config.hotdbDB, config.hotdbPort);
		for (int i = 0; i < key.size(); i++) {
			std::string sql = "select distinct " + config.ruleColumn + " from " + config.hotdbDB + "." + config.tableName + " where " + config.ruleColumn + " = '" + key.at(i) + "'";
			mysqlc->query(sql, [&](MYSQL_ROW row) {
				if (!row) {
					std::cout << key.at(i) << std::endl;
				}
				return true;
			});
		}
		mysqlc->disConnect();
		delete mysqlc;
	});
	return false;
}
