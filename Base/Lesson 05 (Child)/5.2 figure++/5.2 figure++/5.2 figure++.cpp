#include <iostream>
#include <Windows.h>
#define PI 3.14159265
#include <string>

class Figure {
public:
	Figure() : Figure(0) {
		this->name = "Фигура";
	}
	Figure(const Figure& f) = delete;
	void operator=(const Figure& f) = delete;
	int get_sides_count() {
		return sides_count;
	}
	std::string get_name() {
		return name;
	}
	float get_side_lenth(int i) {
		return lenth[i];
	}
	float get_angle(int i) {
		return angle[i];
	}
	virtual bool check() {
		return true;
	}
	~Figure() {
		delete[] lenth;
		delete[] angle;
	}
protected:
	Figure(int count) {
		this->sides_count = count;
		if (count != 0) {
			this->lenth = new float[count]();
			this->angle = new float[count]();
		}
		else {
			this->lenth = new float[1]();
			this->angle = new float[1]();
		}
	}
	int sides_count = 0;
	std::string name = "";
	float* lenth = nullptr;
	float* angle = nullptr;
};

class Triangle : public Figure {
public:
	Triangle() : Figure(3) {
	}
	Triangle(float angle0, float angle1, float angle2, float lenth0, float lenth1, float lenth2) : Figure(3) {
		this->name = "Треугольник";
		angle[0] = angle0;
		angle[1] = angle1;
		angle[2] = angle2;
		lenth[0] = lenth0;
		lenth[1] = lenth1;
		lenth[2] = lenth2;
	}
	bool check() override {
		float summ = 0;
		for (int i = 0; i < sides_count; ++i) {
			if (lenth[i] == 0 || angle[i] == 0) {
				return false;
			}
			summ += angle[i];
		}
		if (summ != 180) {
			return false;
		}
		return true;
	}
};

class right_Triangle : public Triangle {
public:
	right_Triangle(float angle0, float lenth0, float lenth1, float lenth2) : Triangle() {
		this->name = "Прямоугольный треугольник";
		angle[2] = 90;
		angle[0] = angle0;
		angle[1] = 180 - angle[2] - angle[1];
		lenth[1] = lenth0;
		lenth[2] = lenth1;
		lenth[0] = lenth2;
	}
};

class isosceles_Triangle : public Triangle {
public:
	isosceles_Triangle(float a, float l) : Triangle() {  // задается длина основания и угол вершины
		this->name = "Равнобедренный треугольник";
		angle[2] = a;
		angle[1] = (180 - angle[2]) / 2;
		angle[0] = angle[1];

		lenth[2] = l;
		lenth[0] = lenth[2] / (2 / cos(angle[1] * PI / 180));
		lenth[1] = lenth[0];
	}
};

class equilateral_Triangle : public isosceles_Triangle {
public:
	equilateral_Triangle(float l) : isosceles_Triangle(60, l) {  //задается только сторона, угол автоматически 60 градусов
		this->name = "Равносторонний треугольник";

		lenth[1] = lenth[2];
		lenth[0] = lenth[2];
	}
};

class Quadrangle : public Figure {
public:
	Quadrangle() : Figure(4) {
	}
	Quadrangle(float* a, float* l) : Figure(4) {
		this->name = "Четырехугольник";
		lenth[0] = l[0];
		lenth[1] = l[1];
		lenth[2] = l[2];
		lenth[3] = l[3];

		angle[0] = a[0];
		angle[1] = a[1];
		angle[2] = a[2];
		angle[3] = a[3];
	}
	bool check() override {
		float summ_angle = 0;
		for (int i = 0; i < sides_count; ++i) {
			summ_angle += angle[i];
		}
		if (summ_angle != 360) {
			return false;
		}
		return true;
	}
protected:
	void angle_90() {
		for (int i = 0; i < sides_count; ++i) {
			angle[i] = 90;
		}
	}
	void angle_pair(float angle) {
		if (angle > 90) {
			angle = 180 - angle;
		}
		this->angle[0] = angle;
		this->angle[1] = (360 - 2 * angle) / 2;
		this->angle[2] = this->angle[0];
		this->angle[3] = this->angle[1];
	}

	void lenth_q(float lenth) {
		for (int i = 0; i < sides_count; ++i) {
			this->lenth[i] = lenth;
		}
	}
	void lenth_pair(float ab_lenth, float bc_lenth) {
		lenth[0] = ab_lenth;
		lenth[1] = bc_lenth;
		lenth[2] = lenth[0];
		lenth[3] = lenth[1];
	}
};

class rectangle : public Quadrangle {
public:
	rectangle(float a, float b) : Quadrangle() {
		name = "Прямоугольник";
		angle_90();
		lenth_pair(a, b);
	}
};

class square : public Quadrangle {
public:
	square(float a) : Quadrangle() {
		name = "Квадрат";
		angle_90();
		lenth_q(a);
	}
};

class parallelogram : public Quadrangle {
public:
	parallelogram(float a, float l1, float l2) : Quadrangle() {
		name = "Параллелограмм";
		angle_pair(a);
		lenth_pair(l1, l2);
	}
};

class rhomb :public Quadrangle {
public:
	rhomb(float a, float l) : Quadrangle() {
		name = "Ромб";
		angle_pair(a);
		lenth_q(l);
	}
};

void print_info(Figure* figure) {
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Figure f;
	print_info(&f);

	Triangle t(20, 55, 80, 10, 32, 40);
	print_info(&t);

	right_Triangle rt(20, 10, 5, 4);
	print_info(&rt);

	isosceles_Triangle it(30, 5);
	print_info(&it);

	equilateral_Triangle et(5);
	print_info(&et);

	float a[4] = { 10, 20, 30, 40 };
	float b[4] = { 1, 2, 3, 4 };
	Quadrangle q(a, b);
	print_info(&q);

	rectangle r(50, 40);
	print_info(&r);

	square s(5);
	print_info(&s);

	parallelogram p(60, 20, 10);
	print_info(&p);

	rhomb rh(50, 10);
	print_info(&rh);
}