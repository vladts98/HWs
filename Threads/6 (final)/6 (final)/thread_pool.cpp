#include "thread_pool.h"

thread_pool::thread_pool()
{
	cores = std::thread::hardware_concurrency();
	create_vector();
}

thread_pool::thread_pool(int n)
{
	cores = n;
	create_vector();
}

thread_pool::~thread_pool()
{
	stop = true;
	while (q.size())
		std::this_thread::sleep_for(std::chrono::seconds(1));
	for (auto& t : threads)
		t.join();
}

bool thread_pool::work()
{
	while (!stop && q.size()) {
		if (q.size())
			q.pop();
		else
			std::this_thread::yield;
	}
	return true;
}

bool thread_pool::submit(std::function<void()> f)
{
	if (stop)
		return false;

	q.push(f);
	return true;
}

void thread_pool::create_vector()
{
	for (int i = 0; i < cores; ++i)
		threads.push_back(std::thread(&thread_pool::work, this));
}
