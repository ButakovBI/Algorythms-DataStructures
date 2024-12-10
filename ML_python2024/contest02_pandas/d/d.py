import pandas as pd

students_data = pd.read_csv("students_info.csv")
exams_data = pd.read_csv("exams_info.csv")

graduates_data = students_data[students_data['Статус'] == 'ВЫП']

merged_data = pd.merge(graduates_data, exams_data, on="STD_ID")
grouped_by_id = merged_data.groupby("STD_ID", as_index=False)['mark'].mean()
sorted_data = grouped_by_id.sort_values("STD_ID")

sorted_data.to_csv("output.csv", index=False)

