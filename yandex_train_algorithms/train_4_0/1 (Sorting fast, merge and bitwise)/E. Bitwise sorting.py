def radix_sort(arr, idx):
    count = [[] for _ in range(10)]
    for elem in arr:
        count[int(elem[idx])].append(elem)
    ans = []
    for i in range(10):
        print(f'Bucket {i}:', end=' ')
        if len(count[i]) == 0:
            print('empty')
        else:
            print(', '.join(count[i]))
        ans.extend(count[i])
    return ans


def main():
    n = int(input())
    init_array = list(input() for _ in range(n))
    max_length = len(init_array[0])
    print("Initial array:")
    print(', '.join(init_array))
    for i in range(max_length - 1, -1, -1):
        print('**********')
        print(f'Phase {max_length - i}')
        init_array = radix_sort(init_array, i)
    print('**********')
    print('Sorted array:')
    print(', '.join(init_array))


if __name__ == '__main__':
    main()
