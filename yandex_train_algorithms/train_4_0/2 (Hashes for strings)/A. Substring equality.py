def main():
    s = input()
    q = int(input())
    const = 3
    h = [0 for _ in range(len(s) + 1)]
    pows = [1 for _ in range(len(s) + 1)]
    for i in range(1, len(s) + 1):
        h[i] = (h[i - 1] * const + ord(s[i - 1]) - ord('a') + 1) % 10000000
    for i in range(1, len(s)):
        pows[i] = (pows[i - 1] * const) % 10000000
    for i in range(q):
        l, a, b = map(int, input().split())
        if (h[a + l] - h[a] * pows[l]) % 10000000 == (h[b + l] - h[b] * pows[l]) % 10000000:
            print('yes')
        else:
            print('no')


if __name__ == '__main__':
    main()
