#include <iostream>
#include <thread>
#include <chrono>

std::atomic<int> n(5);

void new_c(int max_c = 10) {
	while (n.load() < max_c) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		//++n;
		n.store(n.load() + 1);
		std::cout << "new client " << n.load() << "\n";
		new_c(max_c);
	}
}

void a() {
	while (n.load() > 1) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		n.store(n.load() - 1);
		std::cout << "one is done " << n.load() << "\n";
	}
}

int main()
{
	std::thread t1(new_c, 10);
	std::thread t2(a);
	t1.join();
	t2.join();
	return 0;
}