import pandas as pd

df = pd.read_csv('input.csv')

df['Tectonic regime'] = df['Tectonic regime'].str.split('/')

df_exploded = df.explode('Tectonic regime').sort_values(by='Tectonic regime')

unique_values = df_exploded['Tectonic regime'].unique()

print(len(unique_values))

for value in unique_values:
    print(value)
