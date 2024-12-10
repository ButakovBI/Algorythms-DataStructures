import pandas as pd
import re

df = pd.read_csv('Price_euros_train.csv')

def parse_memory(memory):
    ssd = 0
    hdd = 0
    flash_storage = 0
    hybrid = 0

    parts = memory.split()

    for part in parts:
        size = re.search(r'\d+', part)
        if size:
            size = int(size.group())
            if 'SSD' in part:
                ssd += size
            elif 'HDD' in part:
                hdd += size
            elif 'Flash' in part:
                flash_storage += size
            elif 'Hybrid' in part:
                hybrid += size

    return pd.Series([ssd, hdd, flash_storage, hybrid])

df[['SSD', 'HDD', 'Flash Storage', 'Hybrid']] = df['Memory'].apply(parse_memory)

df = df.drop(columns=['Memory'])

df.to_csv('output.csv', index=False)
