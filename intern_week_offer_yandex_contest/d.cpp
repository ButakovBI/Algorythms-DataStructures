#include <algorithm>
#include <iostream>
#include <vector>

long long gcd(long long a, long long b) {
  while (b != 0) {
    long long tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

int giveMeFactor(long long num) {
  int count = 2;
  while (num != 1) {
    if (num % count == 0) {
      num /= count;
    } else {
      count += 1;
    }
  }
  return count;
}

int main() {
  int count = 0;
  std::cin >> count;
  std::vector<long long> answerArr(count);

  for (int i = 0; i < count; i++) {
    long long first, second;
    std::cin >> first >> second;

    long long nod = gcd(first, second);
    long long factor;

    if (nod == 1) {
      factor = std::max(first, second);
    } else {
      factor = giveMeFactor(std::max(first, second) / nod);
    }

    long long answer = 0;
    if (first > second) {
      answer = second * factor;
      answerArr[i] = gcd(answer, first);
    } else {
      answer = first * factor;
      answerArr[i] = gcd(answer, second);
    }
  }

  for (long long i : answerArr) {
    std::cout << i << '\n';
  }

  return 0;
}
