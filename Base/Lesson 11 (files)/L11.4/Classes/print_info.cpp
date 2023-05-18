#include "print_info.h"

void print_info(Figure* figure){
	std::cout << figure->get_name() << ":" << std::endl;
	std::cout << "Количество сторон: " << figure->get_sides_count() << std::endl;

	if (figure->get_name() == "Фигура") {
		std::cout << std::endl;
	}
	else {
		if (figure->check()) {
			std::cout << "Правильный" << std::endl;
		}
		else {
			std::cout << "Неправильный" << std::endl;
		}
		std::cout << "Стороны: ";
		for (int i = 0; i < figure->get_sides_count(); ++i) {
			std::cout << static_cast<char>('A' + i) << " = ";
			std::cout << figure->get_side_lenth(i);
			if (i < figure->get_sides_count() - 1) {
				std::cout << " ";
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout << "Углы: ";
		for (int i = 0; i < figure->get_sides_count(); ++i) {
			std::cout << static_cast<char>('a' + i) << " = ";
			std::cout << figure->get_angle(i);
			if (i < figure->get_sides_count() - 1) {
				std::cout << " ";
			}
			else {
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
}