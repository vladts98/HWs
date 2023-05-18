#include <iostream>
#include <Windows.h>
#include "print_info.h"
#include "Figures.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try {
		Figure f;
		print_info(&f);
		f.check(); //если что то не так я тут кидаю проблему
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		Triangle t(20, 55, 80, 10, 32, 40);
		print_info(&t);
		t.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}
	
	try {
		right_Triangle rt(20, 10, 5, 4);
		print_info(&rt);
		rt.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		isosceles_Triangle it(30, 5);
		print_info(&it);
		it.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		equilateral_Triangle et(5);
		print_info(&et);
		et.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		float a[4] = { 10, 20, 30, 40 };
		float b[4] = { 1, 2, 3, 4 };
		Quadrangle q(a, b);
		print_info(&q);
		q.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}
	
	try {
		rectangle r(50, 40);
		print_info(&r);
		r.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		square s(5);
		print_info(&s);
		s.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		parallelogram p(60, 20, 10);
		print_info(&p);
		p.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}

	try {
		rhomb rh(50, 10);
		print_info(&rh);
		rh.check();
		std::cout << " Cоздан";
		std::cout << std::endl << std::endl;
	}
	catch (const std::domain_error& d) {
		std::cout << " Несоздан ";
		std::cout << d.what() << std::endl << std::endl;
	}
}