#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

class addres {
public:
	addres() {
	}

	void set_city(std::string city) {
		this->city = city;
	}
	void set_street(std::string street) {
		this->street = street;
	}
	void set_building(int building) {
		this->building = building;
	}
	void set_flat(int flat) {
		this->flat = flat;
	}

	std::string get_addres() {
		return city + ", " + street + ", " + std::to_string(building) + ", " + std::to_string(flat);
	}

private:
	std::string city = "";
	std::string street = "";
	int building = 0;
	int flat = 0;
};

void read_file(std::ifstream& file, const int size, addres* a) {
	std::string s;
	for (int i = 0; i < size; ++i) {
		file >> s;
		a[i].set_city(s);
		file >> s;
		a[i].set_street(s);
		file >> s;
		a[i].set_building(std::stoi(s));
		file >> s;
		a[i].set_flat(std::stoi(s));
	}
}

void sort_addres(const int size, addres* a) {
	for (int i = 0; i < size-1; ++i) {
		if ((a[i].get_addres()) > (a[i+1].get_addres())) {
			std::swap(a[i], a[i + 1]);
			i = 0;
		}
	}
}

void out_file(std::ofstream& file, const int size, addres* a) {
	file << size << std::endl;
	for (int i = 0; i < size; ++i) {
		file << a[i].get_addres();
		if (i <size - 1) {
			file << std::endl;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream fin("in.txt"); // открываю
	if (!fin.is_open()) {
		std::cout << "Not open.";
		return 1;
	}

	int size;
	fin >> size;
	addres* a = new addres[size];  //создал д. память
	read_file(fin, size, a);
	fin.close(); // закрываю

	sort_addres(size, a);
	std::ofstream fout("out.txt"); // открыли файл или создали
	if (!fout.is_open()) {
		std::cout << "Not open2.";
		return 2;
	}
	out_file(fout, size, a);
	delete[] a; // удалил д. память
	return 0;
}