#include <iostream>
#include <Windows.h>

class Fraction
{
private:
	int numerator_;
	int denominator_;
	bool sokr(int& a, int& b) {
		int min = b;
		if (a == b) { //провераю не равна ли дробь 1
			a = 1;
			b = 1;
			return false;
		}
		else if (a < b) { //определюя что больше числитель или знаменатель
			min = a;
		}
		for (int i = 2; i < sqrt(min + 1); ++i) { //иду только до корня минимального числа с оруглением большую сторону
			if (!(a % i) && !(b % i)) {
				a = a / i;
				b = b / i;
				i = 1;
			}
		}
		return false;
	}
public:
	Fraction(int numerator, int denominator)
	{
		numerator_ = numerator;
		denominator_ = denominator;
	}
	bool print() {
		std::cout << numerator_ << "/" << denominator_;
		return true;
	}

	bool operator == (Fraction& other) {
		return (static_cast<float>((this->numerator_ / this->denominator_)) == static_cast<float>((other.numerator_ / other.denominator_)));
	}
	bool operator != (Fraction& other) {
		return !(operator ==(other));
	}

	bool operator > (Fraction& other) {
		return (static_cast<float>((this->numerator_ / this->denominator_)) > static_cast<float>((other.numerator_ / other.denominator_)));
	}
	bool operator <= (Fraction& other) {
		return !(operator > (other));
	}

	bool operator < (Fraction& other) {
		return (static_cast<float>((this->numerator_ / this->denominator_)) < static_cast<float>((other.numerator_ / other.denominator_)));
	}
	bool operator >= (Fraction& other) {
		return !(operator < (other));
	}

	Fraction& operator = (const Fraction& other) {
		this->numerator_ = other.numerator_;
		this->denominator_ = other.denominator_;
		return *this;
	}
	Fraction operator - () {
		int num = -this->numerator_;
		return Fraction(num, this->denominator_);
	}

	Fraction operator + (const Fraction& other) {
		int num = this->numerator_ * other.denominator_ + this->denominator_ * other.numerator_;
		int den = this->denominator_ * other.denominator_;
		sokr(num, den);
		return Fraction(num, den);
	}
	Fraction operator - (const Fraction& other) {
		int num = this->numerator_ * other.denominator_ - this->denominator_ * other.numerator_;
		int den = this->denominator_ * other.denominator_;
		sokr(num, den);
		return Fraction(num, den);
	}
	Fraction operator * (const Fraction& other) {
		int num = this->numerator_ * other.numerator_;
		int den = this->denominator_ * other.denominator_;
		sokr(num, den);
		return Fraction(num, den);
	}
	Fraction operator / (const Fraction& other) {
		int num = this->numerator_ * other.denominator_;
		int den = this->denominator_ * other.numerator_;
		sokr(num, den);
		return Fraction(num, den);
	}

	Fraction& operator ++() {
		this->numerator_ +=this->denominator_;
		return *this;
	}
	Fraction operator ++(int) {
		Fraction result = *this;
		++(*this);
		return result;
	}
	Fraction& operator --() {
		this->numerator_ -= this->denominator_;
		return *this;
	}
	Fraction operator --(int) {
		Fraction result = *this;
		--(*this);
		return result;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int a1, a2, b1, b2;
	std::cout << "Введите числитель дроби 1: ";
	std::cin >> a1;
	std::cout << "Введите знаменатель дроби 1: ";
	std::cin >> a2;
	std::cout << "Введите числитель дроби 2: ";
	std::cin >> b1;
	std::cout << "Введите знаменатель дроби 2: ";
	std::cin >> b2;
	Fraction f1(a1, a2);
	Fraction f2(b1, b2);

	/*std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
	std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
	std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
	std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
	std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
	std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';*/

	f1.print();
	std::cout << " + ";
	f2.print();
	std::cout << " = ";
	Fraction f_plus = f1 + f2;
	f_plus.print();
	std::cout << std::endl;

	f1.print();
	std::cout << " - ";
	f2.print();
	std::cout << " = ";
	Fraction f_minus = f1 - f2;
	f_minus.print();
	std::cout << std::endl;

	f1.print();
	std::cout << " * ";
	f2.print();
	std::cout << " = ";
	Fraction f_mult = f1 * f2;
	f_mult.print();
	std::cout << std::endl;

	f1.print();
	std::cout << " / ";
	f2.print();
	std::cout << " = ";
	Fraction f_dev = f1 / f2;
	f_dev.print();
	std::cout << std::endl;

	std::cout << "++";
	f1.print();
	std::cout << " * ";
	f2.print();
	std::cout << " = ";
	Fraction f_1 = ++f1 * f2;
	f_1.print();
	std::cout << std::endl << "Значение дроби 1 = ";
	f1.print();
	std::cout << std::endl;


	f1.print();
	std::cout << "--";
	std::cout << " * ";
	f2.print();
	std::cout << " = ";
	Fraction f_2 = f1-- * f2;
	f_2.print();
	std::cout << std::endl << "Значение дроби 1 = ";
	f1.print();
	std::cout << std::endl;

	std::cout << "-f1 = ";
	(-f1).print();
	std::cout << std::endl;
	Fraction m_f1 = - f1;
	std::cout << "m_f1 = ";
	m_f1.print();



	return 0;
}