#include <iostream>
#include <Windows.h>

class bad_length : public std::exception {
public: 
    const char* what() const override {
        return "bad lenth"; 
    }
};

int function(std::string str, int forbidden_length) {
    int lenth = str.length();
    if (lenth == forbidden_length) {
        throw bad_length();
    }
    else {
        return lenth;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int lenth = 0;
    std::cout << "Введите запретную длину: ";
    std::cin >> lenth;
    std::string word = "";
    try {
        while(1) {
            std::cout << "Введите слово: ";
            std::cin >> word;
            std::cout << "Длина слова \"" << word << " равна " << function(word, lenth) << std::endl;
        }
    }
    catch(const std::exception& ex) {
        std::cout << "Вы ввели слово запретной длины! До свидания" << std::endl;
        //std::cout << ex.what();
    }
}