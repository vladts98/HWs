#include <iostream>

struct account
{
    int number;
    std::string name;
    float balance;
};

void change_balance(float* balance) { //я тут передал только одну ячейку из всей структуры, а не всю структуру
    std::cout << "Введите новый баланс: ";
    std::cin >> *balance;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    account p;
    std::cout << "Введите номер счёта : ";
    std::cin >> p.number;
    std::cout << "Введите имя владельца: ";
    std::cin >> p.name;
    std::cout << "Введите баланс: ";
    std::cin >> p.balance;
    change_balance(&p.balance);
    std::cout << "Ваш счёт: " << p.name << ", " << p.number << ", " << p.balance;
}
