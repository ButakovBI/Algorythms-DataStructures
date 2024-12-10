#include <iostream>
#include <queue>

int main() {
    std::queue<int> q;
    std::string command;
    while (std::cin >> command) {
        if (command == "push") {
            int val = 0;
            std::cin >> val;
            q.push(val);
            std::cout << "ok" << std::endl;
        }
        else if (command == "pop") {
            if (q.size()) {
                std::cout << q.front() << std::endl;
                q.pop();
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "front") {
            if (q.size()) {
                std::cout << q.front() << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "size") {
            std::cout << q.size() << std::endl;
        }
        else if (command == "clear") {
            while (!q.empty()) {
                q.pop();
            }
            std::cout << "ok" << std::endl;
        }
        else if (command == "exit") {
            std::cout << "bye" << std::endl;
            break;
        }
    }
}