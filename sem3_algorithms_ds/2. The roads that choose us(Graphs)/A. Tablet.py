n, m = map(int, input().split())

field = [list(map(int, input().split())) for _ in range(n)]
ans_field = [[1e9 for _ in range(m)] for _ in range(n)]
used = [[False for _ in range(m)] for _ in range(n)]

q = []
for i in range(n):
    for j in range(m):
        if field[i][j] == 1:
            q.append((i, j))
            ans_field[i][j] = 0

while q:
    x, y = q.pop(0)
    if x - 1 >= 0:
        if not used[x - 1][y] and field[x - 1][y] != 1:
            used[x - 1][y] = True
            q.append((x - 1, y))
            ans_field[x - 1][y] = min(ans_field[x - 1][y], ans_field[x][y] + 1)
    if x + 1 < n:
        if not used[x + 1][y] and field[x + 1][y] != 1:
            used[x + 1][y] = True
            q.append((x + 1, y))
            ans_field[x + 1][y] = min(ans_field[x + 1][y], ans_field[x][y] + 1)
    if y - 1 >= 0:
        if not used[x][y - 1] and field[x][y - 1] != 1:
            used[x][y - 1] = True
            q.append((x, y - 1))
            ans_field[x][y - 1] = min(ans_field[x][y - 1], ans_field[x][y] + 1)
    if y + 1 < m:
        if not used[x][y + 1] and field[x][y + 1] != 1:
            used[x][y + 1] = True
            q.append((x, y + 1))
            ans_field[x][y + 1] = min(ans_field[x][y + 1], ans_field[x][y] + 1)


for elem in ans_field:
    print(*elem)