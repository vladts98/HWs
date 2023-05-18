#include "Figures.h"

Figure::Figure() :Figure(0) {
	this->name = "Фигура";
}

Figure::Figure(int count) {
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

int Figure::get_sides_count() {
	return sides_count;
}

std::string Figure::get_name() {
	return name;
}

float Figure::get_side_lenth(int i) {
	return lenth[i];
}

float Figure::get_angle(int i) {
	return angle[i];
}

bool Figure::check() {  // virtual писать тут или нет?
	return true;
}

Figure::~Figure() {
	delete[] lenth;
	delete[] angle;
}
//___________________________________________
Triangle::Triangle() :Figure(3) {
}

Triangle::Triangle(float angle0, float angle1, float angle2, float lenth0, float lenth1, float lenth2) : Figure(3) {
	this->name = "Треугольник";
	angle[0] = angle0;
	angle[1] = angle1;
	angle[2] = angle2;
	lenth[0] = lenth0;
	lenth[1] = lenth1;
	lenth[2] = lenth2;
}

bool Triangle::check() {  // override 
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
//---------------------------------------------
right_Triangle::right_Triangle(float angle0, float lenth0, float lenth1, float lenth2) : Triangle() {
	this->name = "Прямоугольный треугольник";
	angle[2] = 90;
	angle[0] = angle0;
	angle[1] = 180 - angle[2] - angle[1];
	lenth[1] = lenth0;
	lenth[2] = lenth1;
	lenth[0] = lenth2;
}
//---------------------------------------------
isosceles_Triangle::isosceles_Triangle(float a, float l) : Triangle() {  // задается длина основания и угол вершины
	this->name = "Равнобедренный треугольник";
	angle[2] = a;
	angle[1] = (180 - angle[2]) / 2;
	angle[0] = angle[1];

	lenth[2] = l;
	lenth[0] = static_cast<float>(lenth[2] / (2 / cos(angle[1] * PI / 180)));  //добавил сюда статик каст из double в float
	lenth[1] = lenth[0];
}
//---------------------------------------------
equilateral_Triangle::equilateral_Triangle(float l) : isosceles_Triangle(60, l) {  //задается только сторона, угол автоматически 60 градусов
	this->name = "Равносторонний треугольник";

	lenth[1] = lenth[2];
	lenth[0] = lenth[2];
}
//---------------------------------------------
Quadrangle::Quadrangle() : Figure(4) {
}

Quadrangle::Quadrangle(float* a, float* l) : Figure(4) {
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

bool Quadrangle::check() {
	float summ_angle = 0;
	for (int i = 0; i < sides_count; ++i) {
		summ_angle += angle[i];
	}
	if (summ_angle != 360) {
		return false;
	}
	return true;
}

void Quadrangle::angle_90() {
	for (int i = 0; i < sides_count; ++i) {
		angle[i] = 90;
	}
}

void Quadrangle::angle_pair(float angle) {
	if (angle > 90) {
		angle = 180 - angle;
	}
	this->angle[0] = angle;
	this->angle[1] = (360 - 2 * angle) / 2;
	this->angle[2] = this->angle[0];
	this->angle[3] = this->angle[1];
}

void Quadrangle::lenth_q(float lenth) {
	for (int i = 0; i < sides_count; ++i) {
		this->lenth[i] = lenth;
	}
}

void Quadrangle::lenth_pair(float ab_lenth, float bc_lenth) {
	lenth[0] = ab_lenth;
	lenth[1] = bc_lenth;
	lenth[2] = lenth[0];
	lenth[3] = lenth[1];
}
//-----------------------------------------------
rectangle::rectangle(float a, float b) : Quadrangle() {
	name = "Прямоугольник";
	angle_90();
	lenth_pair(a, b);
}

square::square(float a) : Quadrangle() {
	name = "Квадрат";
	angle_90();
	lenth_q(a);
}

parallelogram::parallelogram(float a, float l1, float l2) : Quadrangle() {
	name = "Параллелограмм";
	angle_pair(a);
	lenth_pair(l1, l2);
}

rhomb::rhomb(float a, float l) : Quadrangle() {
	name = "Ромб";
	angle_pair(a);
	lenth_q(l);
}