#include <algorithm>
#include <iostream>
#include <vector>

int solution() {
  int n = 0;
  std::cin >> n;
  std::vector<int> values(n);
  for (int i = 0; i < n; i += 1) {
    std::cin >> values[i];
  }

  int res = -1;
  if (std::is_sorted(values.begin(), values.end())) {
    res = values.back() - values[0];
  }
  return res;
}

int main() {
  std::cout << solution();

  return 0;
}