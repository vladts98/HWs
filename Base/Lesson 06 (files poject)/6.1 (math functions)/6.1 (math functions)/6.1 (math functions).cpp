#include <iostream>
#include <Windows.h>
#include "math_f.h"


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	double first = 0;
	double second = 0;
	std::cout << "Введите первое число: ";
	std::cin >> first;
	std::cout << "Введите второе число: ";
	std::cin >> second;

	int func = 0;
	std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
	std::cin >> func;

	switch (func) {
	case(1):
		std::cout << first << " + " << second << " = " << summ(first, second);
		break;
	case(2):
		std::cout << first << " - " << second << " = " << minus(first, second);
		break;
	case(3):
		std::cout << first << " * " << second << " = " << multiply(first, second);
		break;
	case(4):
		std::cout << first << " / " << second << " = " << divide(first, second);
		break;
	case(5):
		std::cout << first << " в степени " << second << " = " << power(first, second);
		break;
	}
}