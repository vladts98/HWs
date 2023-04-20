#include <iostream>
#include <string>
#include <cstring>

class big_integer {
public:
	big_integer(std::string& s_) : s{ std::move(s_) } {};
	big_integer(std::string&& s_) : s{ std::move(s_) } {};

	big_integer(big_integer&& other) noexcept {
		//std::cout << "aaaaaaaaaaaaaaaaaaaaaaa";  // Q1 Когда используется этот кусочек кода? по отладчику не видно, но без него не работет 30 строка. Или он нужен по "правилу пяти"?
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

	big_integer operator+(big_integer& other) {
		std::string s1 = this->s;
		std::string s2 = other.get_s();

		std::string new_s = "";
		int buff = 0;
		int buff2 = 0;
		int i1 = s1.size() - 1;
		int i2 = s2.size() - 1;
		while (1) {
			int one = 0;
			int two = 0;
			if (i1 >= 0) {
				one = int(s1[i1]) - 48;
			}
			if (i2 >= 0) {
				two = int(s2[i2]) - 48;
			}
			buff2 = one + two + buff;
			buff = buff2 / 10;
			new_s.insert(0, std::to_string((buff2 + 10) % 10));
			if (i1 <= 0 && i2 <= 0) {
				break;
			}
			if (i1 >= 0)
				i1--;
			if (i2 >= 0)
				i2--;
		}
		return big_integer(new_s);
	}

	big_integer operator*(int mult) {
		std::string new_s = "";
		int buff = 0;
		for (int i = this->s.length() - 1; i >= 0 ; --i) {
			if (i == 0) {
				buff = (int(this->s[i]) - 48) * mult + buff;
				new_s.insert(0, std::to_string(buff));
			}
			else {
				buff = (int(this->s[i]) - 48) * mult + buff;
				new_s.insert(0, std::to_string(buff%10));
				buff = buff / 10;
			}
		}
		return big_integer(new_s);
	}


	big_integer operator*(big_integer& other) {
		big_integer new_s("0");
		int dek = 1;
		for (int i = other.get_s().length() - 1; i >= 0; --i) {
			big_integer buff = (*this * (int(other.get_s()[i]) - 48)) * dek;
			dek *= 10;
			new_s = buff + new_s;
		}
		return new_s;
	}

	std::string get_s() {
		return s;
	}

protected:
	std::string s;
};


int main()
{
	std::string s{ "123456" };
	auto number1 = big_integer(s);
	auto number2 = big_integer("12369");
	auto result = number1 * number2;
	std::cout << number1.get_s() << " " << number2.get_s() << " " << result.get_s();
}