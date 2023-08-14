#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
	int n;
	std::mutex m;
	Data(int a) : n{ a } {
	}
	~Data() {}
	Data(const Data& d) {
		this->m.lock();
		this->n = d.n;
	}
};

void swap_lock(Data& d1, Data& d2) {
	std::lock(d1.m, d2.m);
	auto temp = d1.n;
	d1.n = d2.n;
	d2.n = temp;
	std::cout << "swap_lock - OK\n";
	d1.m.unlock();
	d2.m.unlock();

};

void swap_scoped(Data& d1, Data& d2) {
	std::scoped_lock lock(d1.m, d2.m);
	auto temp = d1.n;
	d1.n = d2.n;
	d2.n = temp;
	std::cout << "swap_scoped - OK\n";
};

void swap_unique(Data& d1, Data& d2) {
	std::unique_lock<std::mutex> lock1(d1.m);
	std::unique_lock<std::mutex> lock2(d2.m);
	auto temp = d1.n;
	d1.n = d2.n;
	d2.n = temp;
	std::cout << "swap_unique - OK\n";
};


int main()
{
	Data d1(1);
	Data d2(2);
	std::thread t1(swap_lock, std::ref(d1), std::ref(d2));
	std::thread t2(swap_scoped, std::ref(d1), std::ref(d2));
	std::thread t3(swap_unique, std::ref(d1), std::ref(d2));
	t1.join();
	t2.join();
	t3.join();
	return 0;
}