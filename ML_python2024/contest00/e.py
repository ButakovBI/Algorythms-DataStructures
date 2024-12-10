a, l, r = map(int, input().split())

def count_coprimes(N, dividors):
    res = N
    m = len(dividors)
    
    for i in range(1, 1 << m):
        bits = bin(i).count('1')
        prod = 1
        for j in range(m):
            if i & (1 << j):
                prod *= dividors[j]
        if prod > N:
            continue
        if bits % 2 == 1:
            res -= N // prod
        else:
            res += N // prod
    return res


dividors = []
i = 2
while (i * i <= a):
    if a % i == 0:
        dividors.append(i)
        while a % i == 0:
            a //= i
    i += 1
if a > 1:
    dividors.append(a)

cnt1 = count_coprimes(r, dividors)
cnt2 = count_coprimes(l - 1, dividors)
print(cnt1 - cnt2)