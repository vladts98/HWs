#include <iostream>
#include <set>

int main()
{
	int n;
	std::cout << "vvedite n ";
	std::cin >> n;
	std::set<int> my_set;
	for (int i = 0, a = 0; i < n; ++i) {
		std::cout << i + 1 << " ";
		std::cin >> a;
		my_set.insert(a);
	}
	for (auto a : my_set) {
		std::cout << a << " ";
	}
}
