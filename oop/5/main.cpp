#include "linkedlist.hpp"
#include <iostream>

bool predicate(int value) { return value < 25; }

bool predicate2(int value) { return value == 25; }

int main() {
    LinkedList<int> list;
    list.push_front(10);
    std::cout << "empty: " << list.empty() << std::endl;
    list.pop_front();
    std::cout << "empty: " << list.empty() << std::endl;
    list.push_front(10);
    std::cout << "empty: " << list.empty() << std::endl;
    list.erase(list.begin());
    std::cout << "empty: " << list.empty() << std::endl;
    list.push_front(10);
    std::cout << "empty: " << list.empty() << std::endl;
    list.erase(0);
    std::cout << "empty: " << list.empty() << std::endl;
    list.push_front(20);
    list.push_front(30);
    list.push_back(5);
    std::cout << "write someone int: ";
    std::cin >> list;
    std::cout << list << std::endl;
    list.insert(60, ++list.begin());
    std::cout << list << std::endl;
    list.insert(45, 0);
    std::cout << list << std::endl;
    list.insert_if(25, predicate);
    std::cout << list << std::endl;
    std::cout << "finded: " << *list.find_if(predicate2) << std::endl;
    list.erase_if(predicate2);
    if (list.find_if(predicate2) == LinkedList<int>::iterator(nullptr))
        std::cout << "not finded" << std::endl;
    std::cout << "max= " << *list.max() << std::endl;
    std::cout << "min= " << *list.min() << std::endl;
    std::cout << "size before: " << list.size() << std::endl;
    std::cout << "back poped: " << list.pop_back() << std::endl;
    std::cout << "size after: " << list.size() << std::endl;
    std::cout << list;
    list.sort();
    std::cout << std::endl;
    for (auto i = list.cbegin(); i != list.cend(); i++) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    LinkedList tmp = list;
    std::cout << "tmp: " << tmp << std::endl;
    std::cout << "clean" << std::endl;
    list.clean();
    std::cout << "empty: " << list.empty() << std::endl;
    std::cout << "list = tmp: " << (list = tmp) << std::endl;
    std::cout << "list == tmp: " << (list == tmp) << std::endl;
    std::cout << "list +(+=) tmp: " << std::endl;
    std::cout << (list + tmp) << std::endl;
    std::cout << (list += tmp) << std::endl;
    std::cout << "list == tmp: " << (list == tmp) << std::endl;
    std::cout << "list != tmp: " << (list != tmp) << std::endl;
    list.swap(tmp);
    std::cout << "list.swap(tmp): " << list << std::endl;
    std::cout << "list[4]: " << list[4] << std::endl;
}