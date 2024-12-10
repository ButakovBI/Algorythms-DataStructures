import pandas as pd
import numpy as np

df = pd.read_csv('Price_euros_train.csv')
df.drop_duplicates(subset='ScreenResolution')
df.drop_duplicates(subset='Inches')

df['ScreenResolution'] = df['ScreenResolution'].str.extract(r'(\d+x\d+)')
print(df['ScreenResolution'])
df[['Width', 'Height']] = df['ScreenResolution'].str.split('x', expand=True)
print(df)
df['Width'] = df['Width'].dropna().astype(int)
df['Height'] = df['Height'].dropna().astype(int)
df['Resolution'] = np.sqrt(df['Width']**2 + df['Height']**2)
df['PPI'] = df['Resolution'] / df['Inches']
print(round(df['PPI'].mean(), 2))