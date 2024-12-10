from bs4 import BeautifulSoup
from parser.data_classes import AllowedTagRecord

def parse_html_to_rules(html_table: str) -> list[AllowedTagRecord]:
    """
    Парсит HTML-таблицу и извлекает правила для разрешенных тегов.

    args:
        html_table (str): строка, содержащая HTML-код таблицы с правилами тегов.

    return:
        List[AllowedTagRecord]: список объектов AllowedTagRecord

    Исключения:
        В случае некорректного формата HTML или отсутствия необходимых данных 
        может произойти пропуск строк.
    """
    soup = BeautifulSoup(html_table, 'html.parser')
    rules = []

    for row in soup.find_all('tr')[1:]:
        columns = row.find_all('td')
        if len(columns) < 5:
            continue  # пропускаем строки с недостаточным количеством ячеек

        tag = columns[0].get_text(strip=True)
        synonyms = columns[2].get_text(strip=True) or None
        immutable = bool(columns[3].get_text(strip=True))
        separated = bool(columns[4].get_text(strip=True))

        rules.append(AllowedTagRecord(
            allowed_name=tag,
            synonyms=synonyms,
            immutable=immutable,
            separated=separated
        ))

    return rules
