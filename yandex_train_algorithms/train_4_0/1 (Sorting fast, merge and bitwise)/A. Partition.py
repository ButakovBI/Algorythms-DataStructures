def partition(arr, l, r, x):
    m = l
    for i in range(l, r):
        if arr[i] < x:
            arr[i], arr[m] = arr[m], arr[i]
            m += 1
    return m


def quicksort():
    n = int(input())
    arr = list(map(int, input().split()))
    x = int(input())
    m = partition(arr, 0, n, x)
    return m, n - m


def main():
    print(*quicksort(), sep='\n')


if __name__ == '__main__':
    main()
