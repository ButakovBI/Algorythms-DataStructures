a, b, c, d = map(int, input().split())
c -= d

if a == 0:
    if b == 0:
        if c == 0:
            res = -1
        else:
            res = 0
    else:
        res = 1
else:
    D = b * b - 4 * a * c
    
    if D < 0:
        res = 0
    elif D == 0:
        res = 1
    else:
        res = 2

print(res)
