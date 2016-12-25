#include "CSVParser.h"

using namespace std;

CSVParser::CSVParser(const char* fileName) {

	ifstream file(fileName);
	string line;
	//get each line string
	while (getline(file, line))
	{
		
	}
	file.close();
}

CSVParser::~CSVParser() {
	
}