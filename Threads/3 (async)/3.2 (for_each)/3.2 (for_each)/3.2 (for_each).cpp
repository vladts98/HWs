#include <iostream>
#include <vector>
#include <future>

template <typename it, typename f>
void p_for(it begin, it end, f func) {
	auto size = std::distance(begin, end);
	if (size < 10) {
		std::for_each(begin, end, func);
		return;
	}
	it mid = begin + size / 2;
	auto a = std::async(std::launch::async, p_for<it, f>, begin, mid, func);
	p_for(mid, end, func);
}

int main()
{
	std::vector<int> v;
	for (int i = 0; i < 1000; ++i) {
		v.push_back(rand() % 100);
	}
	auto lamda = [](int& n) {
		if (n % 2 == 0) {
			n = 0;
		}
	};
	p_for(v.begin(), v.end(), lamda);
	for (auto a : v) {
		std::cout << a << " ";
	}
}