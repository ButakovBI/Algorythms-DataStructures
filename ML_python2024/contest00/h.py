a, b, c = input().split()

a = (a == "true")
b = (b == "true")
c = (c == "true")

res = eval(input())
print("true" if res else "false")
