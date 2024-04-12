def count_palindromes(s):
    n1 = len(s)
    s = '#' + '#'.join(s) + '#'
    n = len(s)
    p = [0] * n
    c = r = 0
    for i in range(1, n - 1):
        mirr = 2 * c - i
        if i < r:
            p[i] = min(r - i, p[mirr])
        while i + (1 + p[i]) < n and i - (1 + p[i]) >= 0 and s[i + (1 + p[i])] == s[i - (1 + p[i])]:
            p[i] += 1
        if i + p[i] > r:
            c, r = i, i + p[i]
    return sum((v + 1) // 2 for v in p) - n1


def main():
    s = input()
    print(count_palindromes(s))


if __name__ == '__main__':
    main()