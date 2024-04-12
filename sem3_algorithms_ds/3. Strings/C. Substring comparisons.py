def main():
    s = input()
    q = int(input())
    const = 257
    p = 1e9 + 7
    h = [0 for _ in range(len(s) + 1)]
    pows = [1 for _ in range(len(s) + 1)]
    for i in range(1, len(s) + 1):
        h[i] = (h[i - 1] * const + ord(s[i - 1])) % p
        pows[i] = (pows[i - 1] * const) % p
    for i in range(q):
        a, b, c, d = map(int, input().split())
        if ((h[b] + h[c - 1] * pows[d - c + 1]) + p) % p == ((h[d] + h[a - 1] * pows[b - a + 1]) + p) % p:
            print('Yes')
        else:
            print('No')


if __name__ == '__main__':
    main()
