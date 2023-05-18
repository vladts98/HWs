#include <iostream>
#include <Windows.h>

class Figure {
public:
	Figure() : Figure(0) {
	}
	int get_sides_count() {
		return sides_count;
	}
	std::string get_name() {
		return name;
	}
protected:
	Figure(int count, std::string name = "Фигура") {
		this->sides_count = count;
		this->name = name;
	}

	int sides_count = 0;
	std::string name = "";
};

class Triangle : public Figure {
public:
	Triangle() : Figure(3, "Треугольник") {
	}
};

class Quadrangle : public Figure {
public:
	Quadrangle() : Figure(4, "Четырехугольник") {
	}
};

void info(Figure* figure) {
	std::cout << figure->get_name() << ": " << figure->get_sides_count() << std::endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::cout << "Количество сторон:" << std::endl;

	Figure f;
	info(&f);

	Triangle t;
	info(&t);
	
	Quadrangle q;
	info(&q);
}