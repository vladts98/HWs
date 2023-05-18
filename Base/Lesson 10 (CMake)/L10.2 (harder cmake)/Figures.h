#pragma once
#include <iostream>
#define PI 3.14159265
#include <string>

class Figure {
public:
	Figure();
	Figure(const Figure& f) = delete;
	void operator=(const Figure& f) = delete;
	int get_sides_count();
	std::string get_name();
	float get_side_lenth(int i);
	float get_angle(int i);
	virtual bool check();
	~Figure();
protected:
	Figure(int count);
	int sides_count = 0;
	std::string name = "";
	float* lenth = nullptr;
	float* angle = nullptr;
};

class Triangle : public Figure {
public:
	Triangle();
	Triangle(float angle0, float angle1, float angle2, float lenth0, float lenth1, float lenth2);
	bool check() override;
};

class right_Triangle : public Triangle {
public:
	right_Triangle(float angle0, float lenth0, float lenth1, float lenth2);
};

class isosceles_Triangle : public Triangle {
public:
	isosceles_Triangle(float a, float l);
};

class equilateral_Triangle : public isosceles_Triangle {
public:
	equilateral_Triangle(float l);
};

class Quadrangle : public Figure {
public:
	Quadrangle();
	Quadrangle(float* a, float* l);
	bool check() override;
protected:
	void angle_90();
	void angle_pair(float angle);
	void lenth_q(float lenth);
	void lenth_pair(float ab_lenth, float bc_lenth);
};

class rectangle : public Quadrangle {
public:
	rectangle(float a, float b);
};

class square : public Quadrangle {
public:
	square(float a);
};

class parallelogram : public Quadrangle {
public:
	parallelogram(float a, float l1, float l2);
};

class rhomb :public Quadrangle {
public:
	rhomb(float a, float l);
};