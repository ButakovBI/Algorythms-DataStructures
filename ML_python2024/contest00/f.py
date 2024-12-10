def ackermann(m, n):
	cache = [[0 for i in range(n + 1)] for j in range(m + 1)]
	
	for rows in range(m + 1):
		for cols in range(n + 1):
			if rows == 0:
				cache[rows][cols] = cols + 1
			elif cols == 0:
				cache[rows][cols] = cache[rows-1][1]
			else:
				ans = 0
				r = rows - 1
				c = cache[rows][cols-1]
				if r == 0:
					ans = c + 1
				elif c <= n:
					ans = cache[rows-1][cache[rows][cols-1]]
				else:
					ans = (c-n)*(r) + cache[r][n]

				cache[rows][cols] = ans

	return cache[m][n]


n, m = map(int, input().split())
print(ackermann(n, m))