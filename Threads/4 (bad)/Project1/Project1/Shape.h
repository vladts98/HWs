#pragma once
#include <cmath>
#include <vector>
#define from_data_base 15 //предположим это запрос в БД

class OBJECT {
public:
	OBJECT() {
		id = from_data_base;
	}
	 unsigned int get_id() { return id; }
private:
	unsigned int id;
};
class dot : public OBJECT{
public:
	double x = 0, y = 0, z = 0;
	virtual void scale_x(double s) {
		x *= s;
	}
	virtual void scale_y(double s) {
		y *= s;
	}
	virtual void scale_z(double s) {
		z *= s;
	}
	virtual void scale(double s) {
		scale_x(s);
		scale_y(s);
		scale_z(s);
	}
	virtual void shift(double x_, double y_, double z_) {
		x += x_;
		y += y_;
		z += z_;
	};
	dot() {
		x = 0;
	}
	dot(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	dot(dot& d) {
		this->x = d.x;
		this->y = d.y;
		this->z = d.z;
	}
	dot& operator = (const dot& d) {
		this->x = d.x;
		this->y = d.y;
		this->z = d.z;
		return *this;
	}
	dot& operator = (const dot&& d) {
		this->x = d.x;
		this->y = d.y;
		this->z = d.z;
		return *this;
	}
	dot(dot&& d) {
		this->x = d.x;
		this->y = d.y;
		this->z = d.z;
	}
	~dot() {}
};

class object_2D : public dot {
public:
	double get_square() {
		return square;
	}
	void shift(double x_, double y_, double z_) override {
		for (auto a : v) {
			a.shift(x_, y_, z_);
		}
	};
	void scale(double s) override {
		for (auto a : v) {
			a.scale(s);
		}
	}
	void scale_x(double s) override {
		for (auto a : v) {
			a.scale_x(s);
		}
	}
	void scale_y(double s) override {
		for (auto a : v) {
			a.scale_y(s);
		}
	}
	void scale_z(double s) override {
		for (auto a : v) {
			a.scale_z(s);
		}
	}
protected:
	double square;
	std::vector<dot> v;
};

class object_3D : public object_2D {
public:
	double get_volume() {
		return volume;
	}
	double get_height() {
		return height;
	}
protected:
	double volume;
	double height;
};

class line : public object_2D {
public:
	line(dot d_1, dot d_2) {
		v.push_back(d_1);
		v.push_back(d_2);
	}
	double lenth() {
		//тут находим длину лини
		return 0;
	}
};

class sqr : public object_2D {
public:
	sqr(dot d1, dot d2, dot d3, dot d4) {
		v.push_back(d1);
		v.push_back(d2);
		v.push_back(d3);
		v.push_back(d4);
		line l1(d1, d2);
		line l2(d2, d3);
		square = l1.lenth() * l2.lenth();
	}
};

class cube : public object_3D {
public:
	cube(dot d1, dot d2, dot d3, dot d4, dot d5, dot d6, dot d7, dot d8) {
		v.push_back(d1);
		v.push_back(d2);
		v.push_back(d3);
		v.push_back(d4);
		v.push_back(d5);
		v.push_back(d6);
		v.push_back(d7);
		v.push_back(d8);
		line l1(d1, d2);
		line l2(d2, d3);
		line l3(d1, d5);
		square = l1.lenth() * l2.lenth();
		volume = square * l3.lenth();
	}
};

class circle : public object_2D {
public:
	circle(dot d1, double r_) {
		r = r_;
		v.push_back(d1);
		square = 3.14 * r * r;
	}
protected:
	double r;
};

class cylinder : public object_3D {
public:
	cylinder(dot d1, double r_, double H_) {
		r = r_;
		v.push_back(d1);
		H = H_;
		square = 3.14 * r * r + 2 * r * H;
		volume = 3.14 * r * r * height;
	}
protected:
	double H;
	double r;
};