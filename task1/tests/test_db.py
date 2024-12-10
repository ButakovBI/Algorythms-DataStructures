from parser.db_operations import add_synonym, add_tag, delete_tag, log_action, update_tag
from parser.db_models import *
import pytest


@pytest.mark.asyncio
async def test_add_tag(db_session):
    await add_tag(db_session, "test_tag", immutable=True, separated=False)
    tag = await db_session.execute(tags_table.select().where(tags_table.c.name == "test_tag"))
    tag_result = tag.mappings().fetchone()
    assert tag_result is not None
    assert tag_result["name"] == "test_tag"
    assert tag_result["immutable"] is True
    assert tag_result["separated"] is False


@pytest.mark.asyncio
async def test_add_synonym(db_session):
    await add_tag(db_session, "main_tag")
    main_tag = await db_session.execute(tags_table.select().where(tags_table.c.name == "main_tag"))
    tag_id = main_tag.mappings().fetchone()["id"]

    await add_synonym(db_session, "test_synonym", tag_id)
    synonym = await db_session.execute(synonyms_table.select().where(synonyms_table.c.name == "test_synonym"))
    synonym_result = synonym.mappings().fetchone()
    assert synonym_result is not None
    assert synonym_result["name"] == "test_synonym"
    assert synonym_result["tag_id"] == tag_id


@pytest.mark.asyncio
async def test_update_tag(db_session):
    await add_tag(db_session, "tag_to_update", immutable=False, separated=True)
    tag = await db_session.execute(tags_table.select().where(tags_table.c.name == "tag_to_update"))
    tag_id = tag.mappings().fetchone()["id"]

    await update_tag(db_session, tag_id, name="updated_tag", immutable=True)
    updated_tag = await db_session.execute(tags_table.select().where(tags_table.c.id == tag_id))
    updated_result = updated_tag.mappings().fetchone()
    assert updated_result["name"] == "updated_tag"
    assert updated_result["immutable"] is True
    assert updated_result["separated"] is True


@pytest.mark.asyncio
async def test_delete_tag(db_session):
    await add_tag(db_session, "tag_to_delete")
    tag = await db_session.execute(tags_table.select().where(tags_table.c.name == "tag_to_delete"))
    tag_id = tag.mappings().fetchone()["id"]

    await delete_tag(db_session, tag_id)
    deleted_tag = await db_session.execute(tags_table.select().where(tags_table.c.id == tag_id))
    assert deleted_tag.mappings().fetchone() is None


@pytest.mark.asyncio
async def test_log_action(db_session):
    await log_action(db_session, "create", "tag", 1)
    log_entry = await db_session.execute(log_table.select().where(log_table.c.target_id == 1))
    log_result = log_entry.mappings().fetchone()
    assert log_result is not None
    assert log_result["action"] == "create"
    assert log_result["target_table"] == "tag"
    assert log_result["target_id"] == 1
