#include <iostream>
#include <vector>


int main() {
    long long n = 0;
    std::cin >> n;

    std::vector<std::vector<bool>> graph(n + 1, std::vector<bool>(2, false));
    for (long long i = 0; i < n; i += 1) {
        for (long long j = i + 1; j < n; j += 1) {
            char color = 0;
            std::cin >> color;
            if (color == 'R') {
                graph[j][0] = true;
            } else {
                graph[j][1] = true;
            }
        }
    }

    std::string ans = "YES";
    for (int i = 1; i < n; i += 1) {
        if (graph[i][0] && graph[i][1]) {
            ans = "NO";
            break;
        }
    }

    std::cout << ans;

    return 0;
}
