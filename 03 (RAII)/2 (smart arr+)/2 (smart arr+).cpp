#include <iostream>

class smart_array {
public:
	smart_array(int size_) : size(std::move(size_)) {
		std::cout << this << "\tconstr" << "\n";
		if (size > 0) {
			arr = new int[size];
			std::cout << "arr\t" << arr << "\n\n";
		}
		else {
			throw std::logic_error("size <= 1");
		}
	}

	~smart_array() {
		std::cout << this << "\tdistr" << "\n";
		std::cout << "arr\t" << arr << "\n\n";
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

	int get_size() {
		return this->size;
	}

	smart_array& operator = (smart_array &a1) {
		std::cout << this << "\t =\n";
		std::cout << "arr\t" << this->arr << "  " << *this->arr << "\n";
		
		delete[] this->arr;
		std::cout << "arr-\t" << this->arr << "  " << *this->arr << "\n";

		this->size = a1.size;
		this->N = a1.N;
		this->arr = new int[this->size];
		std::cout << "arr\t" << this->arr << "\n\n";
		for (int i = 0; i < N; i++) {
			this->arr[i] = a1.arr[i];
		}
		return *this;
	}

protected:
	//public:
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

		smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);

		arr = new_array;

		//std::cout << arr.arr << "    " << new_array.arr;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
