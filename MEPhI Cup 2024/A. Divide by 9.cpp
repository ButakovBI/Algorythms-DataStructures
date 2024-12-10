#include <iostream>
#include <vector>

bool check(std::vector<long long>& arr) {
    long long divide_by_three = 0;
    long long not_divide_by_three = 0;
    long long divide_by_nine = 0;

    for (long long& num : arr) {
        if (num % 9 == 0) {
            divide_by_nine++;
        } else if (num % 3 == 0) {
            divide_by_three++;
        } else {
            not_divide_by_three++;
        }
    }

    bool ans = true;
    if (!(not_divide_by_three == divide_by_nine + 1 && divide_by_three == 0) &&
    ((not_divide_by_three > divide_by_nine) || (divide_by_nine == 0 && divide_by_three == 1))) {
        ans = false;
    }

//    std::cout << divide_by_three << divide_by_nine << not_divide_by_three << '\n';
    return ans;
}

int main() {
    long long n = 0;
    std::cin >> n;

    std::vector<long long> arr(n);
    for (long long i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::string ans = "No";
    if (check(arr)) {
        ans = "Yes";
    }

    std::cout << ans;

    return 0;
}