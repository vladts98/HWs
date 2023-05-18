#include <iostream>
#include <Windows.h>
#include "print_info.h"
#include "Figures.h"

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