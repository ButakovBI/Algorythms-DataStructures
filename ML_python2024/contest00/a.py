def f(x):
    res = x
    if x > 0:
        res = 0
    return res


n = int(input())
w = list(map(int, input().split()))
b = int(input())
x = list(map(int, input().split()))

if len(w) != n or len(x) != n or n < 0:
	print("No solution")
else:
	print(f(sum(x[i] * w[i] for i in range(n)) + b))