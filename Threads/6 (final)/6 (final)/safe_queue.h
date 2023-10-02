#pragma once
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>

template <typename T>
class safe_queue {
public:
	void push(T);
	void pop();
	size_t size();
private:
	std::queue<T> queue;
	std::mutex mtx;
	std::condition_variable cv;
};

template<typename T>
void safe_queue<T>::push(T f) {
	std::unique_lock<std::mutex> ul(mtx);
	queue.push(f);
	cv.notify_all();
}

template<typename T>
void safe_queue<T>::pop() {
	std::unique_lock<std::mutex> ul(mtx);
	cv.wait(ul);
	if (queue.size() > 0) {
		queue.pop();
	}
}

template<typename T>
size_t safe_queue<T>::size() {
	std::unique_lock<std::mutex> ul(mtx);
	return queue.size();
}
