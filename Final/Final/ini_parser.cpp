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

std::stack<std::string> ini_parser::find_values(std::string section_value)
{
	auto dot = section_value.find('.');
	std::string section_name = section_value.substr(0, dot);
	std::string value_name = section_value.substr(dot + 1, section_value.size());
	std::set<std::string> available_values; //будущий список переменных

	auto delete_comment_spaces = [](std::string& s) { // удаляю коментарий и пробелы в строке если он есть
		auto com = s.find(';');
		if (com != std::string::npos) { //удаляем коментарий при наличии
			s.erase(com);
		}

		auto start = false; //флаг, что нашли начало
		auto iter = s.cbegin();
		while (iter != s.cend()) {
			if (std::iswspace(*iter)) { // удаляем пробелы вначале
				s.erase(iter);
				iter = s.cbegin();
				continue;
			}
			else {
				break;
			}
			++iter;
		}
		iter = s.cend();
		while (iter != s.cbegin()) { //удаляем пробелы в конце
			if (!std::iswspace(*(iter - 1))) {
				break;
			}
			--iter;
		}
		s.erase(iter, s.end());
	};

	std::stack <std::string> values; // будущие значение если найдем
	bool value_finded = false; // флаг нашли ли мы значения или нет
	bool open = false; // флаг, находимся в секции или нет
	std::string s; //строка из файла

	unsigned int line = 0;
	while (std::getline(fin, s)) {
		line++;
		if (!s.size()) {
			continue;
		}
		if (s.at(0) == '[') {
			auto a = s.find(']'); // находим конец названия секции
			if (a != std::string::npos) { // если найдена 
				open = false;
				if (section_name == s.substr(1, a - 1)) { // если имя совпадает то мы находимся внутри нужной секции
					open = true;
				}
			}
			else {
				std::cout << "wrong file structure, line: " << line;
				throw std::invalid_argument("wrong file structure");
			}
			continue;
		}
		else {
			if (open) {
				delete_comment_spaces(s);
				if (s.size() == 0) { //пуста строка
					continue;
				}

				auto eq = s.find('=');
				if (eq == std::string::npos) {
					std::cout << "wrong file structure, line: " << line;
					throw std::invalid_argument("wrong file structure"); // не найдено знака равно, но есть какой то текст, и это не коментарий и пробелы
					continue;
				}

				std::string current_value_name = s.substr(0, eq);
				delete_comment_spaces(current_value_name);
				available_values.insert(current_value_name);

				if (current_value_name == value_name) {
					value_finded = true;
					std::string current_value = s.substr(eq + 1, s.size());
					delete_comment_spaces(current_value);
					values.push(current_value);
				}
			}
		}
	}
	if (!value_finded) {
		std::cout << "available values in " << section_name << ": ";
		for (auto a_v : available_values) {
			std::cout << a_v << ", ";
		}
		throw std::invalid_argument("wrong name_value / value not found");
	}
	return values;
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
