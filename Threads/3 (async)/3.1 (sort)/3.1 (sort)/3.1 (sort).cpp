#include <iostream>
#include <vector>
#include <future>

void sort(std::vector<int>& v) {
	auto f = [&v](int k, std::promise<int> prom) mutable {
		for (int j = k; j < v.size(); ++j) {
			if (v[k] > v[j]) {
				k = j;
			}
		}
		prom.set_value(k);
	};

	for (int i = 0; i < v.size(); ++i) {
		std::promise<int> prom;
		std::future<int> ft_ = prom.get_future();
		auto ft = std::async(std::launch::async ,f, i, std::move(prom));

		int k = ft_.get();
		if (k != i) {
			std::swap(v[i], v[k]);
		}
	}
}

int main()
{
	std::vector<int> v;
	for (int i = 0; i < 20; ++i) {
		v.push_back(rand() % 100);
	}
	sort(v);
	for (auto a : v) {
		std::cout << a << " ";
	}
}