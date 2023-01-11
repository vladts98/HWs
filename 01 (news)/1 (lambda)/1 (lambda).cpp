#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<int> v = { 4, 7, 9, 14, 12 };

	for (auto v_ : v) {
		std::cout << v_ << " ";
	}

	std::cout << "\n";

	std::for_each(v.begin(), v.end(), [](auto& v)
		{
			v *= 3;
		});

	for (auto v_ : v) {
		std::cout << v_ << " ";
	}
}