from typing import Tuple, Dict, Set
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select
from parser.db_models import tags_table, synonyms_table
from parser.db_operations import add_tag_to_cache, is_tag_in_cache, remove_expired_tags_from_cache
from parser.utils import split_tags, to_snake_case, convert_tags_to_semi_colon


async def apply_tag_rules(
		tags: str, 
        db_session: AsyncSession,
		delayed_clean: bool = False
	) -> str:
    """
    Основная функция для обработки тега в соответствии с заданными правилами.
    Возвращает отформатированный тег или список разрешенных тегов.
    """
    # Загружаем правила тегов
    allowed_tags, synonyms, separated_tags, immutable_tags = await load_rules(db_session)

    tags = convert_tags_to_semi_colon(tags)

    # Проверка на immutable=true
    if is_immutable(tags, immutable_tags):
        return immutable_tags[tags.lower()]

    # Заменяем синоним на исходный тег
    tags = await replace_synonym(tags, synonyms, db_session)

    # Добавляем тег в snake_case
    tags = tags + '; ' + to_snake_case(tags)

    # Очищаем устаревшие теги из кеша, если они есть
    await remove_expired_tags_from_cache(db_session)

    # Обработка некорректных тегов с учетом флага `delayed_clean`
    processed_tags = await process_split_tags(
        tags, allowed_tags, synonyms, separated_tags, immutable_tags, db_session, delayed_clean
    )

    return "; ".join(sorted(processed_tags))



async def load_rules(db_session: AsyncSession) -> Tuple[Dict[str, dict], Dict[str, dict], Set[str], Dict[str, str]]:
    """
    Загружает правила тегов из базы данных.
    Возвращает кортеж с разрешенными тегами, синонимами, разделяемыми тегами и иммутабельными тегами.
    """
    # извлекаем данные о тегах и синонимах
    tag_data = await db_session.execute(select(tags_table))
    tag_data = tag_data.fetchall()
    synonym_data = await db_session.execute(select(synonyms_table))
    synonym_data = synonym_data.fetchall()

    # форматируем данные для удобства использования в коде
    allowed_tags = {rule._mapping['name']: rule._mapping for rule in tag_data}
    synonyms = {rule._mapping['name']: rule._mapping for rule in synonym_data}
    separated_tags = {rule._mapping['name'] for rule in tag_data if rule._mapping.get('separated')}
    immutable_tags = {rule._mapping['name'].lower(): rule._mapping['name'] for rule in tag_data if rule._mapping.get('immutable')}
    
    return allowed_tags, synonyms, separated_tags, immutable_tags


def is_immutable(tags: str, immutable_tags: Dict[str, str]) -> bool:
    """
    Проверяет, является ли тег immutable.
    Возвращает True, если тег immutable, иначе False.
    """
    return tags.lower() in immutable_tags


async def replace_synonym(tags: str, synonyms: Dict[str, dict], db_session: AsyncSession) -> str:
    """
    Заменяет тег-синоним на оригинальный тег, если он существует.
    Возвращает оригинальный тег или исходный тег, если синоним не найден.
    """
    if tags in synonyms:
        query = select(tags_table).where(tags_table.c.id == synonyms[tags]['tag_id'])
        result = await db_session.execute(query)
        original_tag = result.fetchone()
        if original_tag:
            return original_tag[1]
    return tags


async def process_split_tags(
    tags: str,
    allowed_tags: Dict[str, dict],
    synonyms: Dict[str, dict],
    separated_tags: Set[str],
    immutable_tags: Dict[str, str],
    db_session: AsyncSession,
    delayed_clean: bool = False
) -> Set[str]:
    """
    Обрабатывает разделенные теги и добавляет разрешенные в список.
    Если `delayed_clean=True`, сохраняет невалидные теги в кеш.
    Возвращает множество разрешенных тегов.
    """
    splited_tags = await split_tags(tags)
    processed_tags = set()

    for part in splited_tags:
        part = part.lower()

        # Проверяем на immutable
        if part in immutable_tags:
            processed_tags.add(immutable_tags[part])
            continue

        # Заменяем синонимы на оригинальные теги
        part = await replace_synonym(part, synonyms, db_session)

        # Проверяем, является ли тег разрешенным
        if part in allowed_tags:
            processed_tags.add(part)
        elif delayed_clean:
            # Проверяем, если отложенное удаление включено
            if not await is_tag_in_cache(db_session, part):
                await add_tag_to_cache(db_session, part)  # Добавляем в кеш
        else:
            # Если delayed_clean выключен, просто игнорируем некорректный тег
            pass

        # Проверяем на разделяемые теги и добавляем
        for separated_tag in separated_tags:
            if separated_tag in part:
                processed_tags.add(separated_tag)

    return processed_tags
