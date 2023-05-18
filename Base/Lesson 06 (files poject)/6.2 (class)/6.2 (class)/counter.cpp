#include "counter.h"

Counter::Counter() {
}

Counter::Counter(int& count) {
    this->count = count;
}

void Counter::plus() {
    count++;
}

void Counter::minus() {
    count--;
}

int Counter::view() {
    return count;
}

/*int Counter::count = 1
}

class Counter {
    public:
    Counter() {
    }
    Counter(int& count) {
        this->count = count;
    }
    void plus() {
        count++;
    }
    void minus() {
        count--;
    }
    int view() {
        return count;
    }
private:
    int count = 1;
};
*/