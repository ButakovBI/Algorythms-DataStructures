def count_steak_sets(n, disliked):
    prev_row = [0] * (n + 1)
    curr_row = [0] * (n + 1)
    prev_row[0] = 1

    total_sets = 2 ** n

    for i in range(1, n + 1):
        curr_row[0] = 1
        curr_row[i] = 1
        for j in range(1, i):
            curr_row[j] = prev_row[j - 1] + prev_row[j]

        prev_row = curr_row[:]

    for d in disliked:
        total_sets -= curr_row[d]

    return total_sets % (10 ** 9 + 7) - 1


n, k = map(int, input().split())
disliked = list(map(int, input().split()))
print(count_steak_sets(n, k, disliked))