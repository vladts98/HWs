#include <iostream>

class smart_array {
public:
	smart_array(int full_size_) : full_size(std::move(full_size_)) {
		if (full_size > 0) {
			arr = new int[full_size];
		}
		else {
			throw std::logic_error("size <= 1");
		}
	}

	~smart_array() {
		if (full_size > 0) {
			delete[] arr;
		}
	}

	void add_element(int n) {
		if (real_size < full_size) {
			arr[real_size] = n;
			real_size++;
		}
		else {
			throw std::range_error("index error");
		}
	}
	int get_element(int n) {
		if ((0 <= n) && (n < real_size)) {
			return arr[n];
		}
		else {
			throw std::invalid_argument("index invalid_argument");
		}
	}

	int get_size() {
		return this->real_size;
	}

	smart_array& operator = (smart_array& a1) {
		delete[] this->arr;
		this->full_size = a1.full_size;
		this->arr = new int[this->full_size];
		this->real_size = a1.real_size;

		for (int i = 0; i < real_size; i++) {
			this->arr[i] = a1.arr[i];
		}
		return *this;
	}

protected:
	int full_size;
	int real_size = 0;
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
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	return 1;
}
