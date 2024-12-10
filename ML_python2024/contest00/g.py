values = list(map(int, input().split()))
mean = sum(values) / len(values)
print(sum(values[i] > mean for i in range(len(values))))
