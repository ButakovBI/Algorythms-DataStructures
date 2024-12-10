is_even_sum = 0
n = int(input())
for i in range(n):
    is_even_sum += (int(input()) % 2)

print(int(is_even_sum % 2 == 0))