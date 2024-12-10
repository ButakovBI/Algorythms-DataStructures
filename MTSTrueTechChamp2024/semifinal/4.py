from collections import deque

n, q = map(int, input().split())
pawn_positions = set()
for _ in range(n):
    px, py = map(int, input().split())
    pawn_positions.add((px, py))

distance = [[-1] * 1001 for _ in range(1001)]
queue = deque()

for px, py in pawn_positions:
    distance[px][py] = 0
    queue.append((px, py))

directions = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
while queue:
    x, y = queue.popleft()
    for dx, dy in directions:
        nx, ny = x + dx, y + dy
        if 0 <= nx <= 1000 and 0 <= ny <= 1000 and distance[nx][ny] == -1:
            distance[nx][ny] = distance[x][y] + 1
            queue.append((nx, ny))

results = []
for _ in range(q):
    kx, ky = map(int, input().split())
    results.append(distance[kx][ky])

print('\n'.join(map(str, results)))
