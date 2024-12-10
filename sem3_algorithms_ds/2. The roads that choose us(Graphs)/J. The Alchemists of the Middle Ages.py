import heapq

n = int(input())

g = dict()

for i in range(n):
    first, pointer, second = input().split()
    if first not in g:
        g[first] = [(second, 1)]
    else:
        g[first].append((second, 1))

lengths = dict()
to_add = []
for elem in g:
    lengths[elem] = 1e9
    for v, length in g[elem]:
        to_add.append(v)
        lengths[v] = 1e9
for name in to_add:
    if name not in g:
        g[name] = []

start = input()
if start not in g:
    lengths[start] = 1e9
    g[start] = []
end = input()
if end not in g:
    lengths[end] = 1e9
    g[end] = []


lengths[start] = 0
pq = [(start, 0)]

while pq:
    v, cur_length = heapq.heappop(pq)
    if cur_length > lengths[v]:
        continue
    for to, weight in g[v]:
        if lengths[to] > lengths[v] + weight:
            lengths[to] = lengths[v] + weight
            heapq.heappush(pq, (to, lengths[to]))

if lengths[end] == 1e9:
    print(-1)
else:
    print(lengths[end])
