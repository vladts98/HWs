#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
T pow(T a) {
	return (a * a);
}

template <class T>
std::vector<T> pow(const std::vector<T>& V) {
	std::vector<T> NewV;
	for (T v : V) {
		NewV.push_back(pow(v));
	};
	return std::move(NewV);
}

int main()
{
	const std::vector<float> V{ 5.2f, 7, 10.4f };

	for (auto v : V) {
		std::cout << v << " ";
	};
	std::cout << "\n";

	const std::vector<float> NewV = pow(V); // тут работает функция для вектора и реультат записывается в новую переменную
	for (auto v : NewV) {
		std::cout << v << " ";
	};
	std::cout << "\n";

	//V = pow(V);  //теперь не работает так как V - const
	for (auto v : V) {
		std::cout << v << " ";
	};
}
