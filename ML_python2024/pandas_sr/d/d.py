import pandas as pd

df = pd.read_csv('input.csv')
df['Ram'] = df['Ram'].str.replace('GB', '').astype(float)
df = df.groupby('OpSys', as_index=False)['Ram'].mean().round(2)
df = df.sort_values(by='Ram')
df['Ram'] = df['Ram'].astype(str) + 'GB'
df.to_csv('output.csv', index=False)