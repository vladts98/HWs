#include <iostream>
#include <vector>
#include <string>

template <class T>
class Numb {
public:
	Numb(const T& str) {
		sum = 0;
		count = 0;
		for (auto a : str)
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
	int count;
	int sum;
};

template<typename T>
Numb<T> makeNumb(T t) {
	return Numb<T>(t);
}


int main()
{
	std::vector<int> vec{ 4, 1, 3, 6, 25, 54 };

	std::cout << "get_sum() = " << makeNumb(vec).get_sum() << "\n"
		<< "get_count() = " << makeNumb(vec).get_count();
}
