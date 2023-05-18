#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
void uvec(std::vector <T>& vec) {
	auto it = std::unique(vec.begin(), vec.end());
	vec.erase(it, vec.end());
}

int main()
{
	std::vector<int> vec{ 1, 1, 2, 5, 6, 6, 1, 2, 4 };
	for (auto v : vec) {
		std::cout << v << " ";
	}
	std::cout << "\n";

	sort(vec.begin(), vec.end());
	for (auto v : vec) {
		std::cout << v << " ";
	}
	std::cout << "\n";
	uvec(vec);

	for (auto v : vec) {
		std::cout << v << " ";
	}
}

