#include <iostream>
#include <Windows.h>
#include "Leaver.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Введите имя: ";
    std::string name = "";
    std::cin >> name;
    Leaver L;
    L.leave(name);
}