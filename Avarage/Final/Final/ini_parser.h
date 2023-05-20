#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cwctype>
#include <unordered_map>
#include <list>

class Ini_parser {
public:
	Ini_parser(std::string file_name);
	~Ini_parser();

	template<typename T>
	T get_value(std::string saction_value) {
		if (this->values.empty())
			throw std::invalid_argument("Empty file/values");

		std::string saction = saction_value.substr(0, saction_value.find('.'));
		std::string name = saction_value.substr(saction_value.find('.') + 1, saction_value.size());

		if (!this->values.count(saction))
			print_sactions();

		if (!this->values[saction].count(name))
			print_values(saction);

		T value;
		convert(value, this->values[saction][name].back());
		return value;
	}
	void print_sactions();
	void print_values(std::string saction);

private:
	std::ifstream fin;
	std::unordered_map<std::string, std::unordered_map<std::string, std::list<std::string> > > values;
	void read();
	void convert(int& value, std::string& s);
	void convert(float& value, std::string& s);
	void convert(double& value, std::string& s);
	void convert(std::string& value, std::string& s);
};