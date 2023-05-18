#include "ini_parser.h"


ini_parser::ini_parser(std::string file_name)
{
	try {
		fin.open(file_name);
		if (!fin.is_open()) {
			throw std::invalid_argument("File is not open.\n");
		}
	}
	catch (const std::invalid_argument e) {
		std::cout << e.what();
	}
}

ini_parser::~ini_parser()
{
	if (fin.is_open()) {
		fin.close();
	}
}

void ini_parser::convert(int& value, std::string& s)
{
	value = std::stoi(s);
}

void ini_parser::convert(float& value, std::string& s)
{
	value = std::stof(s);
}

void ini_parser::convert(double& value, std::string& s)
{
	value = std::stod(s);
}

void ini_parser::convert(std::string& value, std::string& s)
{
	value = s;
}
