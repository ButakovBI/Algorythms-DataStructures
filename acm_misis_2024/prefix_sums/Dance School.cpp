#include <iostream>
#include <map>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n = 0;
    std::cin >> n;
    std::vector<int> prefix(n + 1);
    std::map<int, int> count;
    count[0] = 1;
    long long ans = 0;
    char cur_person = 0;
    for (int i = 1; i <= n; i += 1) {
        std::cin >> cur_person;
        if (cur_person == 'a') {
            prefix[i] = prefix[i - 1] + 1;
        } else {
            prefix[i] = prefix[i - 1] - 1;
        }

        ans += count[prefix[i]];
        count[prefix[i]] += 1;
//        std::cout << count[-1] << ' ' << count[0] << ' ' << count[1] << '\n';
    }

    std::cout << ans;
    return 0;
}