#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <map>
#include <algorithm>
#include <random>
#include <mutex>
#include <execution>
#include <numeric>

std::once_flag flag;
void print_n() {
	std::cout << "number of processor cores: " << std::thread::hardware_concurrency() << "\n";
}

void sum(double& summ, std::vector<int>& v, int start, int end) {
	std::call_once(flag, print_n);

	auto s = std::accumulate(v.begin() + start, v.begin() + end, 0);
	summ += s;
}

int main()
{
	int n_threades[] = { 1, 2, 4, 8, 16 };
	int n_elem[] = { 1000, 10'000, 100'000, 1'000'000 };

	std::random_device rnd_device;
	std::mt19937 mersenne_engine{ rnd_device() };
	std::uniform_int_distribution<int> dist {-1000, 1000};
	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

	std::map<int, std::map<int, double> > result; // будующие результаты

	for (auto n : n_elem) {
		std::vector<int> v(n);  // новый вектор из n элементов
		std::generate(begin(v), end(v), gen);
		for (auto n_th : n_threades) {
			std::list <std::thread> threads;

			auto start = std::chrono::high_resolution_clock::now();
			int step = v.size() / n_th;
			int it = 0;
			double summ = 0;
			for (int i = 0; i < n_th - 1; ++i) {
				threads.push_back(std::thread(sum, std::ref(summ), std::ref(v), it, it + step));
				it += step;
			}
			threads.push_back(std::thread(sum, std::ref(summ), std::ref(v), it, v.size()));
			for (auto& th : threads)
				th.join();
			auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> d = end - start;
			//std::cout << summ << "\n";
			result[n][n_th] = d.count();
		}
		//std::cout << "\n";
	}

	std::cout << "\t";
	for (auto n : n_elem) {
		std::cout << "\t\t" << n;
	}
	for (auto t : n_threades) {
		std::cout << '\n' << t << " threades\t";
		for (auto n : n_elem) {
			std::cout << '\t' << result[n][t] << "s";
		}
	}

	return 0;
}