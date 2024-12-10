def merge(arr, arr1, arr2):
    size1, size2 = len(arr1), len(arr2)
    i, j, k = 0, 0, 0
    while i != size1 and j != size2:
        if arr1[i] < arr2[j]:
            arr[k] = arr1[i]
            i += 1
        else:
            arr[k] = arr2[j]
            j += 1
        k += 1
    while i != size1:
        arr[k] = arr1[i]
        k += 1
        i += 1
    while j != size2:
        arr[k] = arr2[j]
        k += 1
        j += 1


def merge_sort(arr):
    size = len(arr)
    if size > 1:
        mid = size // 2

        first = arr[:mid]
        second = arr[mid:]

        merge_sort(first)
        merge_sort(second)
        merge(arr, first, second)


def main():
    size = int(input())
    arr = list(map(int, input().split()))
    merge_sort(arr)
    print(*arr)


if __name__ == '__main__':
    main()