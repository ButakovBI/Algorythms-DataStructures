from sqlalchemy import insert
from conftest import override_get_async_session
import pytest
from datetime import datetime, timedelta
from parser.db_operations import add_tag_to_cache, is_tag_in_cache, remove_expired_tags_from_cache
from parser.tag_processor import apply_tag_rules
from parser.db_models import tag_cache_table


@pytest.mark.asyncio
async def test_add_tag_to_cache(insert_test_data):
    async for db_session in override_get_async_session():
        tag_name = "invalid_tag"
        await add_tag_to_cache(db_session, tag_name)

        is_in_cache = await is_tag_in_cache(db_session, tag_name)
        assert is_in_cache


@pytest.mark.asyncio
async def test_tag_expires_in_cache():
    async for db_session in override_get_async_session():
        tag_name = "expired_tag"

        expiration_date = datetime.now() - timedelta(days=1)
        await db_session.execute(insert(tag_cache_table).values({"tag_name": tag_name, "expiration_date": expiration_date}))
        await db_session.commit()

        await remove_expired_tags_from_cache(db_session)

        is_in_cache = await is_tag_in_cache(db_session, tag_name)
        assert not is_in_cache


@pytest.mark.asyncio
async def test_delayed_clean_keeps_invalid_tags_in_cache():
    async for db_session in override_get_async_session():
        input_tags = "invalid_tag; svc"
        delayed_clean = True

        processed_tags = await apply_tag_rules(input_tags, db_session, delayed_clean=delayed_clean)

        is_in_cache = await is_tag_in_cache(db_session, "invalid_tag")
        assert is_in_cache

        assert "invalid_tag" not in processed_tags


@pytest.mark.asyncio
async def test_delayed_clean_removes_expired_tags():
    async for db_session in override_get_async_session():
        tag_name = "expired_tag"
        delayed_clean = True

        expiration_date = datetime.now() - timedelta(days=1)
        await db_session.execute(insert(tag_cache_table).values({"tag_name": tag_name, "expiration_date": expiration_date}))
        await db_session.commit()

        input_tags = f"{tag_name}; svc"
        processed_tags = await apply_tag_rules(input_tags, db_session, delayed_clean=delayed_clean)

        assert tag_name not in processed_tags


@pytest.mark.asyncio
async def test_non_delayed_clean_removes_invalid_tag_immediately():
    async for db_session in override_get_async_session():
        input_tags = "invalid_tag2; svc"
        delayed_clean = False

        processed_tags = await apply_tag_rules(input_tags, db_session, delayed_clean=delayed_clean)
        print(processed_tags)

        is_in_cache = await is_tag_in_cache(db_session, "invalid_tag2")
        assert not is_in_cache

        assert "invalid_tag2" not in processed_tags
