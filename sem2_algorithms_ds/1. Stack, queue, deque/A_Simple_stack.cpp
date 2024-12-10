#include <iostream>
#include <stack>

int main() {
    std::stack<int> st;
    std::string command;
    while (std::cin >> command) {
        if (command == "push") {
            int val = 0;
            std::cin >> val;
            st.push(val);
            std::cout << "ok" << std::endl;
        }
        else if (command == "pop") {
            if (st.size()) {
                std::cout << st.top() << std::endl;
                st.pop();
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "back") {
            if (st.size()) {
                std::cout << st.top() << std::endl;
            }
            else {
                std::cout << "error" << std::endl;
            }
        }
        else if (command == "size") {
            std::cout << st.size() << std::endl;
        }
        else if (command == "clear") {
            while (!st.empty()) {
                st.pop();
            }
            std::cout << "ok" << std::endl;
        }
        else if (command == "exit") {
            std::cout << "bye" << std::endl;
            break;
        }
    }
}