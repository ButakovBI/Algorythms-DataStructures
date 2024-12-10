from datetime import datetime, timedelta
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy import select, insert, update, delete
from parser.db_models import tags_table, synonyms_table, log_table
from parser.db_models import tag_cache_table


async def add_tag(session: AsyncSession, name: str, immutable: bool = False, separated: bool = False):
    """Добавляет тег в таблицу с исходными тегами"""
    new_tag = {"name": name, "immutable": immutable, "separated": separated}
    result = await session.execute(insert(tags_table).values(new_tag))
    await session.commit()
    tag_id = result.inserted_primary_key[0]
    await log_action(session, "create", "tag", tag_id)


async def add_synonym(session: AsyncSession, synonym_name: str, tag_id: int):
    """Добавляет тег в таблицу с синонимами тегов"""
    new_synonym = {"name": synonym_name, "tag_id": tag_id}
    result = await session.execute(insert(synonyms_table).values(new_synonym))
    await session.commit()
    synonym_id = result.inserted_primary_key[0]
    await log_action(session, "create", "synonym", synonym_id)


async def update_tag(session: AsyncSession, tag_id: int, name: str = None, immutable: bool = None, separated: bool = None):
    """Обновляет существующий тег"""
    values_to_update = {k: v for k, v in {"name": name, "immutable": immutable, "separated": separated}.items() if v is not None}
    await session.execute(update(tags_table).where(tags_table.c.id == tag_id).values(values_to_update))
    await session.commit()
    await log_action(session, "update", "tag", tag_id)


async def delete_tag(session: AsyncSession, tag_id: int):
    """Удаляет существующий тег"""
    await session.execute(delete(tags_table).where(tags_table.c.id == tag_id))
    await session.commit()
    await log_action(session, "delete", "tag", tag_id)


async def log_action(session: AsyncSession, action: str, target_table: str, target_id: int):
    """Добавляет запись в таблицу логов"""
    log_entry = {"action": action, "target_table": target_table, "target_id": target_id}
    await session.execute(insert(log_table).values(log_entry))
    await session.commit()





async def add_tag_to_cache(session: AsyncSession, tag_name: str):
    """Добавляет невалидный тег в кеш отложенного удаления."""
    expiration_date = datetime.now() + timedelta(weeks=2)
    cache_entry = {"tag_name": tag_name, "expiration_date": expiration_date}
    await session.execute(insert(tag_cache_table).values(cache_entry))
    await session.commit()

async def is_tag_in_cache(session: AsyncSession, tag_name: str) -> bool:
    """Проверяет, существует ли тег в кеше и не истек ли срок."""
    result = await session.execute(
        select(tag_cache_table).where(
            tag_cache_table.c.tag_name == tag_name,
            tag_cache_table.c.expiration_date > datetime.now()
        )
    )
    return result.fetchone() is not None

async def remove_expired_tags_from_cache(session: AsyncSession):
    """Удаляет из кеша записи с истекшим сроком действия."""
    await session.execute(
        delete(tag_cache_table).where(tag_cache_table.c.expiration_date <= datetime.now())
    )
    await session.commit()