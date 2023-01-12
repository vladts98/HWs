#include <iostream>
#include <vector>
#include <functional>
#include <Windows.h>
#include <math.h>

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::vector<double> angles = { 30, 60, 90 };
	angles.emplace_back(40);

	std::cout << "Входные данные: ";
	for (int i = 0; i < angles.size(); i++) {
		std::cout << angles[i] << " * 3.1415 / 180";
		angles[i] = angles[i] * 3.1415 / 180;
		if (i != angles.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << "\t// перевод градусов в радианы \n";

	std::function<void(char)> sin = [](int angle) {
		// почему не ругается компилятор ведь в аргументах char, а везде double фигурирует (ну и конечно же считает не правильно)
		std::cout << "\tsin: " << std::sin(angle);
	};
	std::function<void(double)> cos = [](auto angle) {
		std::cout << "\tcos: " << std::cos(angle);
	};
	std::function<void(double)> tan = [](auto angle) {
		std::cout << "\ttan: " << std::tan(angle);
	};

	std::vector < std::function<void(double)>> functions;
	functions.emplace_back(sin); // он и в вектор добавляет хотя как бы разные аргументы, но я как понимаю за этим надо следить как с динамичской памятью
	functions.emplace_back(cos);
	functions.emplace_back(tan); //добавим тангенс



	for (const auto& angle : angles) {
		std::cout << angle << ": ";
		for (const auto& function : functions)
			function(angle);
		std::cout << std::endl;
	}

}