#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cwctype>
#include <stack>

class ini_parser
{
public:
	ini_parser(std::string file_name);
	~ini_parser();

	template<typename T>
	T get_value(std::string section_value) {
		auto stack = std::move(find_values(section_value));
		if (stack.empty()) {
			throw std::invalid_argument("empty values");
		}
		T value;
		convert(value, stack.top());
		return value;
	}

	std::stack<std::string> find_values(std::string section_value);

private:
	std::ifstream fin;

	void convert(int& value, std::string& s);
	void convert(float& value, std::string& s);
	void convert(double& value, std::string& s);
	void convert(std::string& value, std::string& s);

	//template<>							
	//int convert<int>(std::string& s); нельзя же содавать такие функции?
};