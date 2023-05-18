#include <iostream>
#include <Windows.h>
#include "ini_parser.h"

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
	ini_parser ini1("file.ini");
	//std::cout << ini1.get_value<float>("Section1.var1") << "\n";
	//std::cout << ini1.get_value<std::string>("Section1.var2") << "\n";
	std::cout << ini1.get_value<int>("Section2.var1") << "\n";
}