#ifndef TestConfig_CppCSV_h
#define TestConfig_CppCSV_h

#include <fstream>
#include <string>
#include <iostream>

class CSVParser {
public:
	CSVParser(const char* fileName);
	~CSVParser();

	short** data;
};

#endif