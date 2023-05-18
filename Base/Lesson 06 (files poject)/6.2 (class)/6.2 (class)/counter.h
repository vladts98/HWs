#pragma once
#include <iostream>

class Counter {
public:
    Counter();
    Counter(int& count);
    void plus();
    void minus();
    int view();
private:
    int count = 1; // в хедер файле надо задавать начальное значение для переменных? или как то их можно задать в cpp файле?
};