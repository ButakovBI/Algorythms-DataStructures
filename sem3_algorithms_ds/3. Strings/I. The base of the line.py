def main():
    s = input()
    n = len(s)
    x = 547
    p = 10000000
    h = [0] * (n + 1)
    pows = [1] * (n + 1)
    for i in range(1, n + 1):
        h[i] = ((h[i - 1] * x) % p + ord(s[i - 1])) % p
    for i in range(1, n + 1):
        pows[i] = (pows[i - 1] * x) % p
    ans = n
    for i in range(1, n):
        if h[i] == (h[n] - (h[n - i] * pows[i]) % p) % p:
            ans = n - i
    print(ans)


if __name__ == '__main__':
    main()
