#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <mutex>
#include <source_location>
#include <conio.h>
#include <windows.h>
#include <string>
#include <sstream>

std::mutex m;
//short line = 0;

void bar(int number, int t) {
	auto start = std::chrono::high_resolution_clock::now();
	std::string ch = "|| ";
	std::string s = std::to_string(number) + " ";

	std::unique_lock<std::mutex> lck(m);
	std::stringstream os;
	os << std::this_thread::get_id();
	s += os.str() + " ";
	short c_line = number;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, c_line });
	std::cout << s;
	lck.unlock();

	for (int i = 0; i < t; i++) {
		s += ch;
		lck.lock();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, c_line });
		std::cout << '\r' << s;
		lck.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> d = end - start;
	lck.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, c_line });
	s += "Full time: " + std::to_string(d.count());
	std::cout << '\r' << s;
	lck.unlock();
}

int main()
{
	int n = 5; // кол-во потоков
	std::list<std::thread> threads;
	//line = __LINE__;
	for (int i = 0; i < n; ++i) {
		threads.push_back(std::thread(bar, i + 1, rand()%10));
	}
	for (auto& th : threads)
		th.join();
}