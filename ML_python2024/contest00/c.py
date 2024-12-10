val = bin(int(input()))
print(val.count('1') * 100 // (len(val) - 2))