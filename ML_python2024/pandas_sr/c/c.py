import pandas as pd

df = pd.read_csv('train_data.csv')
df = df.drop_duplicates(subset='ID')
data = df[df['Domains'].str.startswith('Strategy Games', na=False)]['Rating Average']
print(round(data.str.replace(',', '.').astype(float).mean(), 2))

