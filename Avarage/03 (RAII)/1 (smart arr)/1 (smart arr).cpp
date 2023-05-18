#include <iostream>

class smart_array {
public:
	smart_array(int size_) : size(std::move(size_)) {
		if (size > 0) {
			arr = new int[size];
		}
		else {
			throw std::logic_error("size <= 1");
		}
	}
	~smart_array() {
		if (size > 0) {
			delete[] arr;
		}
	}

	void add_element(int n) {
		if (N < size) {
			arr[N] = n;
			N++;
		}
		else {
			throw std::range_error("index error");
		}
	}
	int get_element(int n) {
		n--;
		if ((n < size) && (n < N)) {
			return arr[n];
		}
		else {
			throw std::invalid_argument("index invalid_argument");
		}
	}
private:
	int size;
	int N = 0;
	int* arr = nullptr;

};


int main()
{
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(1) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
