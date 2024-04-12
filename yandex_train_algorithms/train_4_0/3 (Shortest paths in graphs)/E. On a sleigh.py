from collections import deque
import heapq
import sys

n = int(input())
coachman = [(0, 0)] + [tuple(map(int, input().split())) for _ in range(n)]
gr: list[list[tuple[int, int]]] = [[] for _ in range(n + 1)]

for _ in range(n - 1):
    a, b, c = map(int, input().split())
    gr[a].append((b, c))
    gr[b].append((a, c))


matrix = [[0.0] * (n + 1) for _ in range(n + 1)]


def bfs(start, speed):
    visited = [False] * (n + 1)
    queue = deque()
    queue.append((start, coachman[start][0]))
    visited[start] = True
    while queue:
        current_vertex, time = queue.popleft()
        if current_vertex == 1:
            continue
        for (neighbor, way) in gr[current_vertex]:
            if not visited[neighbor]:
                visited[neighbor] = True
                path = time + way/speed
                matrix[start][neighbor] = path
                queue.append((neighbor, path))


for i in range(1, n + 1):
    bfs(i, coachman[i][1])


def dijkstra(graph, start):
    vertices = len(graph)
    p = [0] * vertices
    distances = [sys.maxsize] * vertices
    distances[start] = 0
    max_dist = 0
    max_index = 0
    visited = [False] * vertices
    min_heap = [(0, start)]
    while min_heap:
        min_distance, min_index = heapq.heappop(min_heap)
        if min_distance > distances[min_index]:
            continue
        visited[min_index] = True
        for v in range(1, vertices):
            if not visited[v] and graph[v][min_index] != 0 and distances[min_index] + graph[v][min_index] < distances[v]:
                distances[v] = distances[min_index] + graph[v][min_index]
                p[v] = min_index
                heapq.heappush(min_heap, (distances[v], v))
    for i in range(1, n+1):
        if max_dist < distances[i]:
            max_dist = distances[i]
            max_index = i
    print(max_dist)
    while max_index != start:
        print(max_index, end=' ')
        max_index = p[max_index]
    print(start)


dijkstra(matrix, 1)
