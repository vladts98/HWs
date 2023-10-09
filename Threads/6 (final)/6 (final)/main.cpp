#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <future>

#include "safe_queue.h"
#include "thread_pool.h"

std::atomic<int> n = 0;
std::mutex mutex;

void ff() {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::unique_lock<std::mutex> ul(mutex);
	std::cout << __FUNCTION__ << ++n << '\n';
}

void f() {
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::unique_lock<std::mutex> ul(mutex);
	std::cout << __FUNCTION__ << ++n << '\n';
}

int main() {
	std::cout << "check\n";
	thread_pool tp;

	for (int i = 0; i < 6; ++i) {
		tp.submit(ff);
		tp.submit(f);
	}
	tp.~thread_pool();
	std::cout << n;
	return 0;
}