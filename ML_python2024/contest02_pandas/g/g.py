import pandas as pd


def normalize(x):
    x_min = x.min()
    x_max = x.max()
    return (x - x_min) / (x_max - x_min)


data = pd.read_csv("input.csv")
print(data)
for col in data.select_dtypes(include=['float', 'int']).columns:
    data[col] = normalize(data[col]).round(2)

data.to_csv("output.csv", index=False)