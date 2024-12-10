#include <iostream>
#include <vector>

long long mod_pow(long long base, long long exp, long long mod) {
  long long res = 1;
  while (exp > 0) {
    if (exp % 2 == 1) {
      res = (res * base) % mod;
    }
    base = (base * base) % mod;
    exp /= 2;
  }
  return res;
}

long long factorial(long long x, long long mod) {
  long long res = 1;
  for (long long i = 2; i <= x; i += 1) {
    res = (res * i) % mod;
  }
  return res;
}

long long combinations(long long n, long long k, long long mod) {
  long long res = 0;

  if (n >= k) {
    long long sub = n - k;
    if (sub < k) {
      std::swap(sub, k);
    }
    res = 1;
    for (long long num = sub + 1; num <= n; num += 1) {
      res = (res * num) % mod;
    }
    res = res * mod_pow(factorial(k, mod), mod - 2, mod) % mod;
  }
  return res;
}

long long calculation(long long n, long long mod) {
  long long res = 0;

  for (long long k = 0; k <= n; k += 1) {
    long long comb1 = combinations(n, k, mod);
    long long comb2 = combinations(n - k, 2, mod);
    long long term = ((k % 2 == 0) ? 1 : -1) * comb1 * mod_pow(2, comb2, mod);
    res = (res + term + mod) % mod;
  }

  return res;
}

int main() {
  const long long mod = 1e9 + 7;
  long long n = 0;
  std::cin >> n;
  std::cout << n * calculation(n - 1, mod) % mod;
  return 0;
}
