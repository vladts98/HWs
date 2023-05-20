#include <iostream>
#include <Windows.h>
#include "ini_parser.h"

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	Ini_parser ini("file.ini");
	ini.print_sactions();
	std::string s_v = "Section1.var6";
	std::cout << "\n" << s_v + " = " << ini.get_value<std::string>(s_v);
	return 0;
}