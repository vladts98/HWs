#include <iostream>
#include <Windows.h>
#define MODE 1


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

#ifndef MODE
	std::cout << "MODE не определен";
#error
#endif

#if (MODE == 0)
	std::cout << "Работаю в режиме тренировки" << std::endl;

#elif (MODE == 1)
	std::cout << "Работаю в боевом режиме" << std::endl;
	int a = 0, b = 0;
	std::cout << "Введите число 1: ";
	std::cin >> a;
	std::cout << "Введите число 2: ";
	std::cin >> b;
#define add(a, b) (a+b)
	std::cout << add(a, b);

#else
	std::cout << "Неизвестный режим.Завершение работы";
#endif
}