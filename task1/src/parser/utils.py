from functools import lru_cache
import re


@lru_cache(maxsize=1000)
def to_snake_case(tag: str) -> str:
    """Преобразует строку в snake_case, учитывая последовательности заглавных букв и неалфавитные символы."""
    tag = tag.strip()
    tag = re.sub(r'(?<=[a-z])(?=[A-Z])', '_', tag)
    tag = re.sub(r'(?<=[A-Z])(?=[A-Z][a-z])', '_', tag)

    return tag

async def split_tags(tags: str) -> set[str]:
    """Разделяет строку тегов по разделителям ';' и '_', удаляет лишние пробелы и возвращает множество уникальных тегов."""
    split_by_semi = {tag.strip() for tag in tags.split(';') if tag.strip()}
    split_by_underscore = {subtag.strip() for tag in split_by_semi for subtag in tag.split('_') if subtag.strip()}
    return split_by_semi | split_by_underscore


def convert_tags_to_semi_colon(tags: str) -> str:
    """Преобразует строку с тегами, разделёнными пробелами, в строку с тегами, разделёнными ';'."""
    filtered_tags = [tag.strip() for tag in tags.split() if tag.strip()]
    return "; ".join(filtered_tags)
