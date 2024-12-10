import pandas as pd

df = pd.read_csv('test_data.csv')
print(df['Domains'].value_counts().idxmax())
print(df['Domains'].value_counts().max())

