#include <iostream>
#include <vector>

template <typename T>
//void move_vectors(T&& one, T&& two) { //тут rvalue
//	two = std::move(one); //  а как move отчищает объект который мы перемещаем (one)?
//}

void move_vectors(T&& one, T& two) {		// так тоже работает, тут lvalue
	two = std::move(one);
}

int main()
{
	std::vector <std::string> one = { "test_string1", "test_string2" };
	std::vector <std::string> two;
	std::cout << one.size() << " " << &one.at(0) << "\n";
	std::cout << two.size() << "\n";
	move_vectors(std::move(one), two);
	std::cout << one.size() << "\n";
	std::cout << two.size() << " " << &two.at(0) << "\n";
}