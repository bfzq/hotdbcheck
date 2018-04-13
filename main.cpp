#include <cstdio>
#include "programfocus.h"

// `-static` `mysql_config --cflags`  `pkg-config --static --libs mysqlclient` 
int main(int argc, char* argv[]) {
	_mysql_library_init ;
	ProgramFocus* pf = new ProgramFocus(argc, argv);
	int retVal = pf->main();
	delete pf;
	pf = nullptr;
	_mysql_library_end ;
	return !retVal;
}
