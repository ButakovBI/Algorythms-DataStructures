#include <iostream>
#include <stack>

int main() {
    std::stack<char> st;

    std::string s;
    std::cin >> s;
    const int n = s.size();

    for (int i = 0; i < n; ++i) {
        switch (s[i]) {
        case '(': {
            st.push('(');
            break;
        }
        case '[': {
            st.push('[');
            break;
        }
        case '{': {
            st.push('{');
            break;
        }
        case ')': {
            if (st.empty()) {
                std::cout << "no";
                return 0;
            }
            if (st.top() != '(') {
                std::cout << "no";
                return 0;
            }
            else {
                st.pop();
            }
            break;
        }
        case ']': {
            if (st.empty()) {
                std::cout << "no";
                return 0;
            }
            if (st.top() != '[') {
                std::cout << "no";
                return 0;
            }
            else {
                st.pop();
            }
            break;
        }
        case '}': {
            if (st.empty()) {
                std::cout << "no";
                return 0;
            }
            if (st.top() != '{') {
                std::cout << "no";
                return 0;
            }
            else {
                st.pop();
            }
            break;
        }
        default: 0; break;
        }
    }
    if (st.empty()) {
        std::cout << "yes";
    }
    else {
        std::cout << "no";
    }

}
