#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t n = 0;
    std::cin >> n;
    std::map<int64_t, bool> strings_hash;
    const int64_t x = 257;
    const int64_t p = 1e11 + 257;
    for (size_t i = 0; i < n; i += 1) {
        std::string s;
        std::cin >> s;
        size_t str_size = s.size();
        std::vector<int64_t> hash(str_size);
        hash[0] = s[0];
        for (size_t idx = 1; idx < str_size; idx += 1) {
            hash[idx] = (hash[idx - 1] * x + s[idx]) % p;
        }
        strings_hash.insert({hash[str_size - 1], true});
    }
    std::cout << strings_hash.size() << '\n';
    return 0;
}