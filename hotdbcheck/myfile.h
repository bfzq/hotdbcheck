#ifndef __MYFILE__
#define __MYFILE__



#include <iostream>
#include <fstream>
#include <string>
#include <functional>

struct sql_string {
	std::string str;
	struct sql_string* right;
	struct sql_string* down;
	sql_string(std::string str);
};





class MyFile {
private:
	//std::ifstream file;
	std::fstream rwfile;
public:
	MyFile();
	~MyFile();
public:
	std::string file_name;
private:
	bool open_file();
	bool open_file(std::ios_base::openmode);
public:
	struct sql_string* read_csv(std::string limiter);
	void* read_line(std::function<void* (std::string str)>);
	bool write(std::function<void(std::fstream*)>);
	bool write_line(std::string);
	bool close();
};

#endif // !__MYFILE__