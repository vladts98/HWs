#include "L10.1 (simple cmake).h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string name;
	std::cout << "Введите имя: ";
	std::cin >> name;
	std::cout << "Здравствуйте, " << name;
	std::system("pause");
	return 0;
}
