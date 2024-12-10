import pandas as pd

data = pd.read_csv("input.csv")
exams = data[(data['STD_ID'] == 99125) & (data['АТТЕСТАЦИЯ'] == 'Экзамен')]
cnt_exams = len(exams)
avg_mark = round(exams['mark'].sum() / cnt_exams, 2)
print(cnt_exams)
print(avg_mark)
