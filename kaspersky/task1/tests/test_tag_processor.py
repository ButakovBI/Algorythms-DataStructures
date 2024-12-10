import pytest
from parser.data_classes import AllowedTagRecord
from parser.tag_processor import apply_tag_rules
from conftest import override_get_async_session


@pytest.mark.asyncio
async def test_apply_tag_rules_with_synonym():
    async for db_session in override_get_async_session():

        tags = "дисплэй; сообщения"
        expected = "display; sms"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_with_unknown_tag():
    async for db_session in override_get_async_session():
        tags = "unknown_tag"
        expected = ""
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_empty_string():
    async for db_session in override_get_async_session():
        tags = ""
        expected = ""
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_immutable_tag():
    async for db_session in override_get_async_session():
        tags = "auto; авто"
        expected = "AUTO"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_compound_with_overlap():
    async for db_session in override_get_async_session():
        tags = "DisplaySvc"
        expected = "display; svc"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_with_special_chars():
    async for db_session in override_get_async_session():
        tags = "display@svc"
        expected = "svc"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_with_duplicate_tags():
    async for db_session in override_get_async_session():
        tags = "дисплэй; дисплэй"
        expected = "display"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_synonym_conflict():
    async for db_session in override_get_async_session():
        tags = "кему; x86"
        expected = "x86"
        assert await apply_tag_rules(tags, db_session) == expected


@pytest.mark.asyncio
async def test_apply_tag_rules_with_mixed_case():
    async for db_session in override_get_async_session():
        tags = "LoCk_Screen; LCD"
        expected = "display; lock_screen"
        assert await apply_tag_rules(tags, db_session) == expected
