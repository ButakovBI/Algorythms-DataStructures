import pytest
from parser.data_classes import AllowedTagRecord
from parser.rule_index import build_rule_index


@pytest.mark.asyncio
async def test_build_rule_index_basic():
    rules = [
        AllowedTagRecord("web_engine"),
        AllowedTagRecord("sms", synonyms="messages, сообщения"),
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "web_engine" in rule_index
    assert "sms" in rule_index
    assert "messages" in rule_index
    assert "сообщения" in rule_index
    assert rule_index["messages"] == rule_index["sms"]


@pytest.mark.asyncio
async def test_build_rule_index_with_immutable():
    rules = [
        AllowedTagRecord("AUTO", immutable=True),
        AllowedTagRecord("SRS", immutable=True),
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "auto" in rule_index
    assert "srs" in rule_index
    assert rule_index["auto"].immutable is True
    assert rule_index["srs"].immutable is True


@pytest.mark.asyncio
async def test_build_rule_index_empty():
    rule_index = await build_rule_index(())
    assert rule_index == {}


@pytest.mark.asyncio
async def test_build_rule_index_with_separated():
    rules = [
        AllowedTagRecord("display", synonyms="lcd, дисплей", separated=True),
        AllowedTagRecord("svc", synonyms="service", separated=True)
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "lcd" in rule_index
    assert "дисплей" in rule_index
    assert "service" in rule_index


@pytest.mark.asyncio
async def test_build_rule_index_with_duplicates():
    rules = [
        AllowedTagRecord("contacts", synonyms="контакты, Контакты, КОНТАКТЫ"),
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "contacts" in rule_index
    assert "контакты" in rule_index
    assert rule_index["контакты"] == rule_index["contacts"]


@pytest.mark.asyncio
async def test_build_rule_index_with_empty_synonyms():
    rules = [
        AllowedTagRecord("display", synonyms=""),
        AllowedTagRecord("lock_screen")
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "display" in rule_index
    assert "lock_screen" in rule_index
    assert len(rule_index) == 2


@pytest.mark.asyncio
async def test_build_rule_index_separated_with_overlap():
    rules = [
        AllowedTagRecord("display", synonyms="dis", separated=True),
        AllowedTagRecord("dis_service", synonyms="svc", separated=True)
    ]
    rule_index = await build_rule_index(tuple(rules))

    assert "dis" in rule_index
    assert "svc" in rule_index
    assert "display" in rule_index
