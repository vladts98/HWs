#include <iostream>
#include <vector>
#include <set>
#include <list>

template<typename T>
void print_container(T t) {
    auto i = t.begin();
    while (i != t.end()) {
        std::cout << *i << " ";
        i++;
    }
    std::cout << "\n";
}


int main()
{
    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set); // four one three two. помните почему такой порядок? :) // по алфавиту 

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list); // one, two, three, four

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector); // one, two, three, four
}
