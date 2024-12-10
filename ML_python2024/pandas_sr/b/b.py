import pandas as pd

df = pd.read_csv('test_data.csv')
print(round(2021 - df['Year Published'].mean(), 2))

