#include "myfile.h"
#include "stdlib.h"
#include "string.h"


sql_string::sql_string(std::string str) {
	this->str = str;
	this->down = nullptr;
	this->right = nullptr;
}



MyFile::MyFile() {
}


MyFile::~MyFile() {
	//free(&file_name);
	//free(&rwfile);
}

bool MyFile::open_file() {
	return open_file(std::ios::in | std::ios::binary);
}



bool MyFile::open_file(std::ios_base::openmode om) {
	if (file_name.empty()) {
		return false;
	}
	rwfile.open(file_name, om);
	return rwfile.is_open();
}

struct sql_string* scan(std::string limiter, std::string str) {
	int i = str.find_first_of(limiter.c_str());
	if (i >= 0) {
		return new sql_string(str.substr(i));
	}
	else {
		return nullptr;
	}


}

struct sql_string* MyFile::read_csv(std::string limiter) {
	char* b = (char*)malloc(sizeof(char) * 256);
	struct sql_string* s = nullptr;
	std::string str;
	while (!rwfile.eof()) {
		rwfile.getline(b, 256);
		std::string str(b);
		scan(limiter, str);
		//file.end();
		//file >> str;
		//std::cout << str << std::endl;
	}
	return nullptr;
}

void* MyFile::read_line(std::function<void*(std::string str)> f) {
	if (!open_file()) {
		return nullptr;
	}
	char* b = (char*)malloc(sizeof(char) * 256);
	//struct sql_string* s = nullptr;
	std::string str;
	void* n = nullptr;
	while (!rwfile.eof()) {
		rwfile.getline(b, 256);
		std::string str(b);
		n = f(str);
	}
	free(b);
	return n;
}

bool MyFile::write(std::function<void(std::fstream*)> f) {
	if (this->rwfile.is_open()) {
		this->rwfile.close();
	}
	if (!open_file(std::ios::out)) {
		return false;
	}
	f(&rwfile);
	return true;
}

bool MyFile::write_line(std::string txt) {
	return write([txt](std::fstream* fs) {
		*fs << txt << std::endl;
	});
}

bool MyFile::close() {
	this->rwfile.close();
	return true;
}
