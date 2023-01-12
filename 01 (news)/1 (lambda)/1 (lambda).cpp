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

	std::for_each(v.begin(), v.end(), [index = 0](auto& v_) mutable
		{
			if ((index % 2) == 0) {
				v_ *= 3;
			}
			++index;
		});

	for (auto v_ : v) {
		std::cout << v_ << " ";
	}
}