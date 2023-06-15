#include <iostream>
#include <thread>
#include <chrono>

int n = 5;

void new_c(int max_c = 10) {
	while (n < max_c) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		++n;
		std::cout << "new client " << n << "\n";
		new_c(max_c);
	}
}

void a() {
	while (n > 1) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		--n;
		std::cout << "one is done " << n << "\n";
	}
}

int main()
{
	std::thread t1(new_c, 20);
	std::thread t2(a);
	t1.join();
	t2.join();
	return 0;
}