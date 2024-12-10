from math import sin


def f1(x):
    return 2 * x - 15 * sin(x)


x0, N, lm = map(float, input().split())
x = x0
for _ in range(int(N)):
    x = x - lm * f1(x)
print(round(x, 4))