#include <iostream>
//using namespace std;

struct point {
	double m_x;
	double m_y;
	//point(double x, double y) {
	//	m_x = x;
	//	y = y;
	//}
};

void print_point(const point& point_object) {
	std::cout << "x:" << point_object.m_x << ", y: "
		<< point_object.m_y << std::endl;
}

int main()
{
	for (int i = 0; i < 5; i++) {
		point my_point{ static_cast<double>(i), static_cast<double>(2 * i) };
		print_point(my_point);
	}
	return 0;
}

//void print_point(const point& point_object) {
//	std::cout << "x:" << point_object.m_x << ", y: "
//		<< point_object.m_y << std::endl;
//}

// можно код писать на русском языке буквами которые такие же как англ ( а(рус) и a(eng) ) в универе бывало такое в маткаде))