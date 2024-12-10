#include <iostream>
#include <deque>

int main() {
    std::deque<int> d;
    std::string command;
    while (std::cin >> command) {
        if (command == "push_front") {
            int val = 0;
            std::cin >> val;
            d.push_front(val);
            std::cout << "ok" << std::endl;
        }
        if (command == "push_back") {
            int val = 0;
            std::cin >> val;
            d.push_back(val);
            std::cout << "ok" << std::endl;
        }
        else if (command == "pop_front") {
            if (d.size()) {
                std::cout << d.front() << std::endl;
                d.pop_front();
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "pop_back") {
            if (d.size()) {
                std::cout << d.back() << std::endl;
                d.pop_back();
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "front") {
            if (d.size()) {
                std::cout << d.front() << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "back") {
            if (d.size()) {
                std::cout << d.back() << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "size") {
            std::cout << d.size() << std::endl;
        }
        else if (command == "clear") {
            d.clear();
            std::cout << "ok" << std::endl;
        }
        else if (command == "exit") {
            std::cout << "bye" << std::endl;
            break;
        }
    }
}