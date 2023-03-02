#include <iostream>
#include <string>

class big_integer {
public:
	big_integer(std::string&& s_) : s{ s_ } {};

	big_integer(big_integer&& other) noexcept {
		*this = std::move(other);
	}

	big_integer& operator=(big_integer& other) {
		this->s = other.s;
		return *this;
	}

	big_integer& operator=(big_integer&& other) noexcept {
		this->s = std::move(other.s);
		return *this;
	}

	big_integer operator+(const big_integer& other) {
		auto a(std::to_string(std::stoll(this->s) + std::stoll(other.s) ));
		return a;
	}

	big_integer operator*(const big_integer& other) {
		auto a(std::to_string(std::stoll(this->s) * std::stoll(other.s)));
		return a;
	}

	std::string s;
};


int main()
{
	auto number1 = big_integer("114575");
	auto number2 = big_integer("78524");
	auto result = number1 * number2;
	std::cout << number1.s << " " << number2.s << " " << result.s;
}