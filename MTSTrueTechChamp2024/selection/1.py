import sys


def solve(response: str):
    a, b, u, end = response.split('\n')
    a = int(a)
    b = int(b)
    u = int(u)
    return a + (max(0, u - 100) * b)


response = ""
for line in sys.stdin:
    response += line

print(solve(response))