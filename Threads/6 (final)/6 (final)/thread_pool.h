#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include "safe_queue.h"

class thread_pool {
public:
	thread_pool();
	thread_pool(int n);
	~thread_pool();
	bool submit(std::function<void()>);
private:
	bool work();
	void create_vector();
private:
	int cores;
	std::vector<std::thread> threads;
	safe_queue<std::function<void()>> q;
	std::atomic_bool stop = false;
};
