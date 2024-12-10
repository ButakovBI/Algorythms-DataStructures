import pandas as pd

data = pd.read_csv("input.csv")

unique_values = sorted(data['Onshore/Offshore'].unique())
unique_values_map = {value: idx for idx, value in enumerate(unique_values)}
data['Onshore/Offshore'] = data['Onshore/Offshore'].map(unique_values_map)
data['Onshore/Offshore'].to_csv("output.csv", index=False)
