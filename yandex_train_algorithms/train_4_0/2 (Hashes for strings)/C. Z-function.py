def main():
    s = input()
    n = len(s)
    z = [0] * (n)
    l, r = 0, 0
    for i in range(1, n):
        if i <= r:
            z[i] = min(r - i + 1, z[i - l])
        while i + z[i] < n and s[z[i]] == s[z[i] + i]:
            z[i] += 1
        if i + z[i] - 1 > r:
            r = i + z[i] - 1
            l = i
    print(*z)


if __name__ == '__main__':
    main()
