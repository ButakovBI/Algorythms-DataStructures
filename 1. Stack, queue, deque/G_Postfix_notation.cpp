#include <iostream>
#include <stack>

int main() {
    char sym = 0;
    std::stack<int> st;

    while (std::cin >> sym) {
        if ((sym >= '0') && (sym <= '9')) {
            st.push(sym - '0');
        }
        else {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            switch (sym) {
            case '+': {
                st.push(a + b);
                break;
            }
            case '-': {
                st.push(a - b);
                break;
            }
            case '*': {
                st.push(a * b);
                break;
            }
            case '/': {
                st.push(a / b);
                break;
            }
            default: 0; break;
            }
        }
    }

    while (!st.empty()) {
        std::cout << st.top() << ' ';
        st.pop();
    }
}