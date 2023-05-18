#pragma once
#include <iostream>
#define PI 3.14159265
#include <string>

#ifdef Classes_EXPORTS
#define Classes_API __declspec(dllexport)
#else
#define Classes_API __declspec(dllimport)
#endif

class Figure {
public:
	Classes_API Figure();
	Classes_API Figure(const Figure& f) = delete;
	Classes_API void operator=(const Figure& f) = delete;
	Classes_API int get_sides_count();
	Classes_API std::string get_name();
	Classes_API float get_side_lenth(int i);
	Classes_API float get_angle(int i);
	Classes_API virtual bool check();
	Classes_API ~Figure();
protected:
	Figure(int count);
	int sides_count = 0;
	std::string name = "";
	float* lenth = nullptr;
	float* angle = nullptr;
};

class Triangle : public Figure {
public:
	Classes_API Triangle();
	Classes_API Triangle(float angle0, float angle1, float angle2, float lenth0, float lenth1, float lenth2);
	Classes_API bool check() override;
};

class right_Triangle : public Triangle {
public:
	Classes_API right_Triangle(float angle0, float lenth0, float lenth1, float lenth2);
};

class isosceles_Triangle : public Triangle {
public:
	Classes_API isosceles_Triangle(float a, float l);
};

class equilateral_Triangle : public isosceles_Triangle {
public:
	Classes_API equilateral_Triangle(float l);
};

class Quadrangle : public Figure {
public:
	Classes_API Quadrangle();
	Classes_API Quadrangle(float* a, float* l);
	Classes_API bool check() override;
protected:
	void angle_90();
	void angle_pair(float angle);
	void lenth_q(float lenth);
	void lenth_pair(float ab_lenth, float bc_lenth);
};

class rectangle : public Quadrangle {
public:
	Classes_API rectangle(float a, float b);
};

class square : public Quadrangle {
public:
	Classes_API square(float a);
};

class parallelogram : public Quadrangle {
public:
	Classes_API parallelogram(float a, float l1, float l2);
};

class rhomb :public Quadrangle {
public:
	Classes_API rhomb(float a, float l);
};