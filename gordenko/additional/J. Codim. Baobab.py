import sys
sys.setrecursionlimit(100000)


def dfs(v: int, parent: int, ans: str, used, path, g):
    used[v] = 1
    if v in path:
        ans = "NO"
    path.append(v)
    for to in g[v]:
        if used[to] == 0:
            dfs(to, v, ans, used, path, g)
        elif to != parent:
            ans = "NO"


def main():
    n = int(input())
    res = "YES"
    used = [0 for _ in range(n + 1)]
    path = []
    g = [[] for _ in range(n + 1)]
    for i in range(n):
        values = list(map(int, input().split()))
        # print(values)
        for j in range(i + 1, n):
            if values[j]:
                g[i + 1].append(j + 1)
                g[j + 1].append(i + 1)

    dfs(1, 0, res, used, path, g)
    if len(path) != n:
        res = "NO"
    print(res)


if __name__ == "__main__":
    main()
