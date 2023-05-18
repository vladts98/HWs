#include <iostream>
#include <Windows.h>
#include "Race.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int reapeat = 0;
	do {
		Race Race;
		std::cout << "Добро пожаловать в гоночный симулятр!" << std::endl;
		for (int i = 0; i < Race.max_type; ++i) {
			std::cout << i + 1 << " " << Race.type_name[i] << std::endl;
		}
		std::cout << "Выбирите тип гонки: ";
		int type;
		std::cin >> type;

		std::cout << "Укажите длину дистанции (должна быть положительна): ";
		float lenth;
		std::cin >> lenth;
		Race.Create_race(type, lenth);

		int action = 0;
		while (action != 2) {
			if (Race.get_reg_v() < 2) {
				std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства" << std::endl;
			}
			std::cout << "1. Зарегистрировать транспорт" << std::endl;
			if (Race.get_reg_v() > 1) {
				std::cout << "2. Начать гонку" << std::endl;
			}
			std::cout << "Выбирите действие: ";
			std::cin >> action;

			switch (action) {
			case 1:
			{
				int action_regist = 1;
				do {
					std::cout << std::endl;
					Race.print_all_info();
					std::cout << "Выбирите транспорт или 0 для окнчания процесса регистрации: ";
					std::cin >> action_regist;
					switch (Race.reg(action_regist)) {
					case 0:
						std::cout << Race.get_v_name(action_regist - 1) << " успешно зарегестрирован!" << std::endl;
						break;
					case 1:
						std::cout << "Такого ТС НЕТ" << std::endl;
						break;
					case 2:
						std::cout << Race.get_v_name(action_regist - 1) << " уже зарагестрирован" << std::endl;
						break;
					case 3:
						std::cout << Race.get_v_name(action_regist - 1) << " не может быть зарегестрирован" << std::endl;
						break;
					case 4:
						break;
					};
				} while (action_regist);
			}
			break;
			case 2:
				if (Race.get_reg_v() > 1) {
					Race.start();
					for (int i = Race.get_all_v() - 1, n = 1; i > -1; --i) {
						if (Race.get_v_status(i)) {
							std::cout << n << ". " << Race.get_v_name(i) << ". Время: " << Race.get_time(i) << std::endl;
							++n;
						}
					}
					break;
				}
				break;
			default:
				action = 0;
				break;
			}
		}
		do {
			std::cout << std::endl << "1. Провести еще одну гонку" << std::endl
				<< "2. Выйти" << std::endl;
			std::cout << "Выбирите действие: ";
			std::cin >> reapeat;
		} while (!((reapeat == 1) || (reapeat == 2)));
	} while (reapeat == 1);
}