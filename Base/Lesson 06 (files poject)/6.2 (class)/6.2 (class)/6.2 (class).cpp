#include <iostream>
#include <Windows.h>
#include "counter.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Вы хотите указать начальное значение счётчика? Введите да или нет: ";
    std::string answer;
    std::cin >> answer;

    int count = 1;
    if (answer == "да") {
        std::cout << "Введите начальное значение счётчика: ";
        std::cin >> count;
    }
    else if (answer == "нет") {
    }
    Counter c(count);

    std::string pull;
    do {
        std::cout << "Введите команду ('+', '-', '=' или 'x'): ";
        std::cin >> pull;
        if (pull == "+") {
            c.plus();
        }
        else if (pull == "-") {
            c.minus();
        }
        else if (pull == "=") {
            std::cout << c.view() << std::endl;
        }
    } while (pull != "х");
    std::cout << "До свидания! ";
}