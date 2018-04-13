#include "programfocus.h"


void ProgramFocus::init() {
	cl = new ComLine();
	mysqlc = new MySQLC();
}

void ProgramFocus::unInit() {
	delete cl ;
	cl = nullptr ;
	delete mysqlc ;
	mysqlc = nullptr ;
}

ProgramFocus::ProgramFocus() {
	init();
}

ProgramFocus::ProgramFocus(int argc, char * argv[]) {
	init();
	config = cl->getParam(argc, argv);
	if (!cl->checkConnect(config)) {
		exit(10);
        
	}
}


ProgramFocus::~ProgramFocus() {
	unInit() ;
	deleteVector(keys);
}

bool ProgramFocus::getRuleColumn() {
	if (mysqlc->connect(config.mysqlHost, config.mysqlUser, config.mysqlPassword, config.mysqlDB, config.mysqlPort)) {
		std::string sql = "select rule_column \
		from hotdb_tableinfo as t join hotdb_rule as r on r.rule_id=t.rule_id \
		join hotdb_logic_db as l on t.logic_dbid=l.logic_dbid \
	where t.table_name='" + config.tableName + "' and l.logic_dbname='" + config.hotdbDB + "';";
		if (!mysqlc->query(sql, [&](MYSQL_ROW row) {
			if (row[0] != NULL) {
				config.ruleColumn = row[0];
                return true;
			}else {
				return false;
			}
		},nullptr)) {
			mysqlc->disConnect();
			return false;
			std::cout << "RULE COLUMN NULL" << std::endl;
		}
		mysqlc->disConnect();
		return true ;
    }else{
        return false ;
    }
}

bool ProgramFocus::getRuleValue() {
	if (mysqlc->connect(config.hotdbHost, config.hotdbUser, config.hotdbPassword, config.hotdbDB, config.hotdbPort)) {
		std::string sql = "select distinct " + config.ruleColumn + " as c1 from " + config.tableName;
		if (!mysqlc->query(sql, [&](MYSQL_ROW row) {
			std::string* s = nullptr;
			if (row[0]) {
				s = new std::string(row[0]);
			}
			keys.push_back(s);
			return true;
		}, nullptr)) {
			mysqlc->disConnect();
			return false;
		}
	}
	mysqlc->disConnect();
	return true;
}

void ProgramFocus::deleteVector(std::vector<std::string*> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v.at(i) != nullptr) {
			delete v.at(i);
		}
	}
	v.clear();
}

bool ProgramFocus::run(std::function<void(std::vector<std::string*>)> f) {
	getRuleValue();
	threadPool.setMaxQueueSize(config.tasks * 10);
	threadPool.start(config.tasks);
	while (keys.size() > 0) {
		std::vector<std::string*> key;
		if (keys.size() > config.eachData) {
			key.assign(keys.begin(), keys.begin() + config.eachData);
			keys.erase(keys.begin(), keys.begin() + config.eachData);
		}
		else {
			key.assign(keys.begin(), keys.end());
			keys.erase(keys.begin(), keys.end());
		}
		threadPool.run(std::bind(f, key));
	}
	threadPool.stop();
	return true;
}

bool ProgramFocus::main() {
//	processLine() ;
	getRuleColumn();
	if (run([&](std::vector<std::string*> key) {
		MySQLC* mysqlc = new MySQLC();
        if(!mysqlc->connect(config.hotdbHost, config.hotdbUser, config.hotdbPassword, config.hotdbDB, config.hotdbPort)) {
            delete mysqlc ;
            return false ;
        }
        for (int i = 0; i < key.size(); i++) {
            std::string sql = (key.at(i) != nullptr) ? "select distinct " + config.ruleColumn + " from " + config.tableName + " where " + config.ruleColumn + " = '" + *(key.at(i)) + "'" : "select distinct " + config.ruleColumn + " from " + config.tableName + " where " + config.ruleColumn + " is null";
            mysqlc->query(sql, [&](MYSQL_ROW row) {
                return true;
            }, [&](void) {
                if (key.at(i) != nullptr) {
//                    std::cout << " = " << *(key.at(i)) << std::endl;
					wrong.push_back(*(key.at(i))) ;
                }
                else {
					wrong.push_back("NULL") ;
//                    std::cout << " = NULL" << std::endl;
                }
            });
        }
		delete mysqlc;
		deleteVector(key);
		ProgramFocus::processLine() ;
        return true ;
	})) {
		print() ;
		return true ;
	} else {
		return false ;
	}
	
}

void ProgramFocus::processLine() {
	char bar[102];
	const char *lable = "|/-\\";
	static int i = 0 ;
	printf("[%c]\r", lable[i%4]);
	fflush(stdout);
	i++ ;
}



void ProgramFocus::print() {
	std::cout << "The check table is " << config.tableName << "." << std::endl ;
	std::cout << "The route column is " << config.ruleColumn << "." << std::endl ;
	if (0 == wrong.size()) {
		std::cout << "The rule value is right." << std::endl ;
	}else {
		std::cout << "Print wrong_route_value :" << std::endl ;
		std::vector<std::string>::iterator iter ;
		for (iter = wrong.begin() ; iter != wrong.end() ;iter++ ) {
			std::cout << *iter << std::endl ;
		}
		std::cout << "The wrong value total is " << wrong.size() << std::endl ;
	}
	
	
}
