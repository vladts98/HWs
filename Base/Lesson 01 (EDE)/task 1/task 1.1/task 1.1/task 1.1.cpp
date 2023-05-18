#include <iostream>
#include <fstream>

void read_file(std::fstream& fin, int& n_1, int*& arr_1, int& n_2, int*& arr_2) {
	fin >> n_1;
	arr_1 = new int[n_1];
	for (int i = 0; i < n_1; ++i) {
		fin >> arr_1[i];
	}

	fin >> n_2;
	arr_2 = new int[n_2];
	for (int i = 0; i < n_2; ++i) {
		fin >> arr_2[i];
	}
}

bool open_file(const std::string& file_name, int& n_1, int*& arr_1, int& n_2, int*& arr_2) {
	std::fstream fin(file_name);
	if (!fin.is_open()) {
		std::cout << "file not open";
		return false;
	}
	read_file(fin, n_1, arr_1, n_2, arr_2);
	fin.close();
	return true;
}

void write_file(const std::string& file_name, int& n_1, int*& arr_1, int& n_2, int*& arr_2) {
	std::ofstream fout(file_name);
	if (fout.is_open()) {
		fout << n_2 << std::endl;
		fout << arr_2[n_2 - 1] << ' ';
		for (int i = 0; i < n_2 - 1; ++i) {
			fout << arr_2[i];
			if (i < n_2 - 1) {
				fout << ' ';
			}
		}
		fout << std::endl << n_1 << std::endl;
		for (int i = 1; i < n_1; ++i) {
			fout << arr_1[i] << ' ';
		}
		fout << arr_1[0];
		fout.close();
	}
	else {
		std::cout << "Not open.";
	}
}

int main()
{
	int* arr_1 = nullptr;
	int* arr_2 = nullptr; // объявляем указатель на массивы
	int n_1, n_2;

	if (open_file("in.txt", n_1, arr_1, n_2, arr_2)) {
		write_file("out.txt", n_1, arr_1, n_2, arr_2);
		delete[] arr_1;
		delete[] arr_2;
	}
}