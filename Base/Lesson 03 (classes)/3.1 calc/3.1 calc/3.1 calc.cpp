#include <iostream>

class Calculator {
public:
	bool set_num1(double num1) {
		if (num1 == 0) {
			return false;
		}
		else {
			this->num1 = num1;
			return true;
		}
	}
	bool set_num2(double num2) {
		if (num2 == 0) {
			return false;
		}
		else {
			this->num2 = num2;
			return true;
		}
	}
	double add() {
		return num1 + num2;
	}
	double multiply() {
		return num1 * num2;
	}
	double subtract_1_2() {
		return num2 - num1;
	}
	double subtract_2_1() {
		return (num1 - num2);
	}
	double divide_1_2() {
		return (num1 / num2);
	}
	double divide_2_1() {
		return (num2 / num1);
	}
private:
	double num1;
	double num2;
};

void print(Calculator calc) {
	std::cout << "num1 + num2 = " << calc.add() << std::endl;
	std::cout << "num1 - num2 = " << calc.multiply() << std::endl;
	std::cout << "num2 - num1 = " << calc.subtract_1_2() << std::endl;
	std::cout << "num1 * num2 = " << calc.subtract_2_1() << std::endl;
	std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
	std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;
}

void set_num_(int n, Calculator& calc) {
	double buff = 0;
	bool flag = true;
	while (flag) {
		std::cout << "Введите num" << n << ": ";
		std::cin >> buff;
		if (buff == 0) {
			std::cout << "Неверный ввод!" << std::endl;
		}
		else {
			switch (n) {
			case 1:
				flag = !calc.set_num1(buff);
				break;
			case 2:
				flag = !calc.set_num2(buff);
				break;
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Calculator calc;
	while (1) {
		set_num_(1, calc);
		set_num_(2, calc);
		print(calc);
	}
}