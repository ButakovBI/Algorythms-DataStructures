n, m = map(int, input().split())


field = [list(map(int, input().split())) for _ in range(n)]
ans_field = [[1e9 for _ in range(m)] for _ in range(n)]
y1, x1 = map(int, input().split())
y2, x2 = map(int, input().split())

ans_field[x1 - 1][y1 - 1] = 0
q = [(x1 - 1, y1 - 1)]
while q:
    x, y = q.pop(0)
    if x - 1 >= 0:
        if ans_field[x - 1][y] == 1e9 and field[x - 1][y] != 1:
            q.append((x - 1, y))
            ans_field[x - 1][y] = ans_field[x][y] + 1
    if x + 1 < n:
        if ans_field[x + 1][y] == 1e9 and field[x + 1][y] != 1:
            q.append((x + 1, y))
            ans_field[x + 1][y] = ans_field[x][y] + 1
    if y - 1 >= 0:
        if ans_field[x][y - 1] == 1e9 and field[x][y - 1] != 1:
            q.append((x, y - 1))
            ans_field[x][y - 1] = ans_field[x][y] + 1
    if y + 1 < m:
        if ans_field[x][y + 1] == 1e9 and field[x][y + 1] != 1:
            q.append((x, y + 1))
            ans_field[x][y + 1] = ans_field[x][y] + 1


# print(*ans_field, sep='\n')
if field[x2 - 1][y2 - 1] == 1:
    print(-1)
else:
    if ans_field[x2 - 1][y2 - 1] != 1e9:
        print(ans_field[x2 - 1][y2 - 1])
    else:
        print(-1)
