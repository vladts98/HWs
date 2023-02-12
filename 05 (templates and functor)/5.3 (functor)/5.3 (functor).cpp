#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Numb {
public:
	Numb() {
		sum = 0;
		count = 0;
	}

	template<typename T>
	void operator () (T a) {
		if (a % 3 == 0) {
			count++;
			sum += a;
		}
	}

	int get_sum() {
		return sum;
	}

	int get_count() {
		return count;
	}

private:
	int count;
	int sum;
};

int main()
{
	Numb s;
	std::vector<int> arr{ 4, 1, 3, 6, 25, 54 };

	//std::for_each(arr.begin(), arr.end(), s); // а почему так не раотает? он плюсует но не сохраняет
	s = std::for_each(arr.begin(), arr.end(), s);
	std::cout << "get_sum() = " << s.get_sum() << "\n"
		<< "get_count() = " << s.get_count();
}
