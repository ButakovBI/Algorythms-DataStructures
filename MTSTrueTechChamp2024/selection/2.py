import sys


def solve(response: str):
    to_find = 'M'
    res = 0
    for i in range(len(response)):
        if response[i] == to_find:
            if to_find == 'M':
                to_find = 'T'
            elif to_find == 'T':
                to_find = 'S'
            elif to_find == 'S':
                res = 1
                break
    return res


response = ""
for line in sys.stdin:
    response += line

print(solve(response))