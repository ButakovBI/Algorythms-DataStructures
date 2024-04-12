def merge(size1, size2, arr1, arr2):
    i, j, k = 0, 0, 0
    ans = [0 for _ in range(size1 + size2)]
    while i != size1 and j != size2:
        if arr1[i] < arr2[j]:
            ans[k] = arr1[i]
            i += 1
        else:
            ans[k] = arr2[j]
            j += 1
        k += 1
    while i != size1:
        ans[k] = arr1[i]
        k += 1
        i += 1
    while j != size2:
        ans[k] = arr2[j]
        k += 1
        j += 1
    return ans


def main():
    size1 = int(input())
    arr1 = list(map(int, input().split()))
    size2 = int(input())
    arr2 = list(map(int, input().split()))
    print(*merge(size1, size2, arr1, arr2))


if __name__ == '__main__':
    main()