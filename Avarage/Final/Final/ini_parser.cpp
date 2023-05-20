#include "Ini_parser.h"

Ini_parser::Ini_parser(std::string file_name)
{
	fin.open(file_name);
	if (!fin.is_open())
		std::cout << "File is not open.\n";
	else
		read();
}

Ini_parser::~Ini_parser()
{
	if (fin.is_open())
		fin.close();
}

void Ini_parser::print_sactions()
{
	std::cout << "Availible sactions: ";
	for (auto element : this->values)
		std::cout << element.first << ", ";
}

void Ini_parser::print_values(std::string saction)
{
	if (this->values.count(saction)) {
		std::cout << "Availible values in \"" << saction << "\": ";
		for (const auto& element : this->values[saction])
			std::cout << element.first << ", ";
	}
	else
		std::cout << "Saction is not exist";
}

void Ini_parser::read()
{
	auto delete_comment_spaces = [](std::string& s) {
		auto com = s.find(';');
		if (com != std::string::npos) {
			s.erase(com);
		}

		auto start = false;
		auto iter = s.cbegin();
		while (iter != s.cend()) {
			if (std::iswspace(*iter)) {
				s.erase(iter);
				iter = s.cbegin();
				continue;
			}
			else
				break;
			++iter;
		}
		iter = s.cend();
		while (iter != s.cbegin()) {
			if (!std::iswspace(*(iter - 1)))
				break;
			--iter;
		}
		s.erase(iter, s.end());
	};

	std::string s = "";
	std::string saction_name = "";

	unsigned int line = 0;
	while (std::getline(fin, s)) {
		line++;
		delete_comment_spaces(s);
		if (!s.size())
			continue;

		if (s.at(0) == '[') {
			auto a = s.find(']');
			if (a != std::string::npos) {
				saction_name = s.substr(1, a - 1);
			}
			else {
				std::cout << "wrong file structure, line: " << line;
				throw std::invalid_argument("wrong file structure");
			}
			continue;
		}
		else {
			if (saction_name == "")
				continue;
			auto eq = s.find('=');
			if (eq == std::string::npos) {
				std::cout << "wrong file structure, line: " << line;
				throw std::invalid_argument("wrong file structure");
			}
			std::string current_value_name = s.substr(0, eq);
			delete_comment_spaces(current_value_name);
			std::string current_value = s.substr(eq + 1, s.size());
			delete_comment_spaces(current_value);
			this->values[saction_name][current_value_name].push_back(current_value);
		}
	}
}

void Ini_parser::convert(int& value, std::string& s)
{
	value = std::stoi(s);
}

void Ini_parser::convert(float& value, std::string& s)
{
	value = std::stof(s);
}

void Ini_parser::convert(double& value, std::string& s)
{
	value = std::stod(s);
}

void Ini_parser::convert(std::string& value, std::string& s)
{
	value = s;
}
