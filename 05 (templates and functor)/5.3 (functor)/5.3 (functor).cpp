#include <iostream>
#include <vector>
#include <string>


class Numb {
public:
	Numb(std::vector<int> str) : aaa(str) {
	}

	void operator() () {
		sum = 0;
		count = 0;
		for (auto a : aaa)
		{
			if (a % 3 == 0) {
				count++;
				sum += a;
			}
		}
	}

	int get_sum() {
		return sum;
	}

	int get_count() {
		return count;
	}

private:
	std::vector<int> aaa;
	int count = 0;
	int sum = 0;
};


int main()
{
	std::vector<int> vec{ 4, 1, 3, 6, 25, 54 };

	Numb aaa(vec);
	aaa();
	std::cout << "get_sum() = " << aaa.get_sum() << "\n"
		<< "get_count() = " << aaa.get_count();
}
