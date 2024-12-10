import pandas as pd

data = pd.read_csv("input.csv")
data = data.drop_duplicates(subset='STD_ID')
cnt_students = len(data[data['Статус'] == 'СТ'])
cnt_graduate = len(data[data['Статус'] == 'ВЫП'])
male_most_popular = data[(data['Статус'] == 'СТ') & (data['Пол'] == 'М')]['направление (специальность)'].value_counts().idxmax()
female_most_popular = data[(data['Статус'] == 'СТ') & (data['Пол'] == 'Ж')]['направление (специальность)'].value_counts().idxmin()
null_student = data[data.drop('STD_ID', axis=1).isnull().all(axis=1)].iloc[0, 0]
unique_fields_of_study = data['направление (специальность)'].nunique()

cnt_female_graduate = len(data[(data['Статус'] == 'ВЫП') & (data['Пол'] == 'Ж')])
cnt_male_graduate = len(data[(data['Статус'] == 'ВЫП') & (data['Пол'] == 'М')])
most_cnt_gender = 'Ж' if cnt_female_graduate > cnt_male_graduate else 'М'

print(cnt_students)
print(cnt_graduate)
print(male_most_popular)
print(female_most_popular)
print(null_student)
print(unique_fields_of_study)
print(most_cnt_gender)
