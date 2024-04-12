#include <iostream>
#include <vector>

int main() {
    std::string s;
    std::cin >> s;
    int n = s.length();
    std::vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = std::min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    z[0] = n;
    for (int i = 0; i < n; i++) {
        std::cout << z[i] << " ";
    }
    return 0;
}