#include <iostream>
#include <stdlib.h>
#include <vector>


template <class T>
class table {
public:
	table(int c, int l) : col(std::move(c)), line(std::move(l)) {
		aaa.resize(col, std::vector<T>(line, 0));
	}
	int size() {
		return col * line;
	}


	class Proxy {
	public:
		Proxy(std::vector<T>& _array) : _array(_array) { }

		T& operator[](int index) {
			return _array.at(index);
		}
	private:
		std::vector<T>& _array;
	};

	Proxy operator[](int index) {
		return Proxy(aaa.at(index));
	}

	// ниже более простая перегрузка без проверки внутренного размер вектора
	//std::vector<T>& operator [] (int index) {
	//	return aaa.at(index);
	//}   

private:
	int col = 0;
	int line = 0;
	std::vector<std::vector<T>> aaa;
};

int main()
{
	auto test = table<int>(2, 3);
	test[0][0] = 4;
	std::cout << test[0][0]; // выводит 4
}
