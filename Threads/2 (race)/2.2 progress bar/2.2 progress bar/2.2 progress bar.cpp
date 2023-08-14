#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <mutex>
#include <windows.h>
#include <sstream>
#include <source_location>

std::mutex m;

void bar(int number, int full_time) {
	auto start = std::chrono::high_resolution_clock::now();

	int percent_section = 10; // процент одной секции
	std::string ch = "|| ";
	std::string bar_s = "";
	for (int i = 0; i < 100 / percent_section; i++) {
		bar_s += ch;
	}
	int pos_start_bar = 10;  // позиция начала бара для выравнивания

	std::string info = std::to_string(number) + " ";

	std::unique_lock<std::mutex> lck(m);
	std::stringstream os;
	os << std::this_thread::get_id();
	info += os.str();
	while (info.length() < pos_start_bar) {
		info += " ";
	}
	short line = number; // строчка на которой будет бар
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, line });
	std::cout << info;
	lck.unlock();

	int procent = 0;
	if (full_time == 0)
		procent = 100;
	while (procent < 100) {
		std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start;
		procent = duration.count() / full_time * 100;
		int lenth = bar_s.length() * procent / 100;
		lck.lock();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, line });
		std::cout << '\r' << info << bar_s.substr(0, lenth);
		lck.unlock();
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> d = end - start;
	info += bar_s;
	info += "Full time: " + std::to_string(d.count());
	lck.lock();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, line });
	std::cout << '\r' << info;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 15 });
	lck.unlock();
}

int main()
{
	int n = 3; // кол-во потоков
	std::list<std::thread> threads;
	for (int i = 0; i < n; ++i) {
		threads.push_back(std::thread(bar, i + 1, rand()%10));
	}
	for (auto& th : threads)
		th.join();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, short(n+1) });
}