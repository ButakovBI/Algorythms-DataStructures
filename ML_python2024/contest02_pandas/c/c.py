import pandas as pd
import time

start_time = time.time()

data = pd.read_csv("input.csv")
computer_technologies = data[data['ДИСЦИПЛИНА'] == "Компьютерные технологии в дизайне"]
computer_technologies = computer_technologies.drop_duplicates(subset='STD_ID')
grouped_by_year_avg_marks = computer_technologies.groupby('ГОД', as_index=False)['mark'].mean()
grouped_by_year_avg_marks['ДИСЦИПЛИНА'] = "Компьютерные технологии в дизайне" 
grouped_by_year_avg_marks = grouped_by_year_avg_marks[['ГОД', 'ДИСЦИПЛИНА', 'mark']]
grouped_by_year_avg_marks.to_csv("output.csv", index=False)

# import polars as pl


# data = pl.read_csv("input.csv")
# computer_technologies = data.filter(pl.col('ДИСЦИПЛИНА') == "Компьютерные технологии в дизайне")
# computer_technologies = computer_technologies.unique(subset=['STD_ID'])
# grouped_by_year_avg_marks = computer_technologies.group_by('ГОД').agg(
#     pl.col('mark').mean().alias('mark')
# )
# grouped_by_year_avg_marks = grouped_by_year_avg_marks.with_columns(
#     pl.lit("Компьютерные технологии в дизайне").alias('ДИСЦИПЛИНА')
# )
# grouped_by_year_avg_marks = grouped_by_year_avg_marks.select(['ГОД', 'ДИСЦИПЛИНА', 'mark'])
# grouped_by_year_avg_marks.write_csv("output.csv")

end_time = time.time()
print(end_time - start_time)