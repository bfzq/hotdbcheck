#include <cstdio>
#include "programfocus.h"

// valgrind --leak-check=full ./hotdbcheck.out  --hotdb-user=jwy --hotdb-host=192.168.200.51 --hotdb-port=5553 --hotdb-password=jwy --hotdb-db=BENCHMARK_JWY --mysql-host=192.168.200.51 --mysql-port=3306 --mysql-password=hotdb_config --mysql-user=hotdb_config --mysql-db=hotdb_config_245  --table-name=history

int main(int argc, char* argv[]) {
	ProgramFocus* pf = new ProgramFocus(argc, argv);
	int retVal = pf->main();
	delete pf;
	pf = nullptr;
    return !retVal;
}

