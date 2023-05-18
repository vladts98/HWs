#include <iostream>

enum class month {
	January = 1,
	February,
	March,
	April,
	May	,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

void print_monthV2(int month_number) {
	switch (static_cast<month>(month_number)) {
	case month::January:
		std::cout << "Январь";
		break;
	case month::February:
		std::cout << "Февраль";
		break;
	case month::March:
		std::cout << "Март";
		break;
	case month::April:
		std::cout << "Апрель";
		break;
	case month::May:
		std::cout << "Май";
		break;
	case month::June:
		std::cout << "Июнь";
		break;
	case month::July:
		std::cout << "Июль";
		break;
	case month::August:
		std::cout << "Август";
		break;
	case month::September:
		std::cout << "Сентябрь";
		break;
	case month::October:
		std::cout << "Октябрь";
		break;
	case month::November:
		std::cout << "Ноябрь";
		break;
	case month::December:
		std::cout << "Декабрь";
		break;
	}
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int month_number;
	do {
		std::cout << "Введите номер месяца: ";
		std::cin >> month_number;
		if (month_number > 0 && month_number < 13) {
			print_monthV2(month_number);
		}
		else if (month_number == 0) {
			break;
		}
		else {
			std::cout << "Неправильный номер!" << std::endl;
		}
	} while (month_number != 0);
	std::cout << "До свидания";
}