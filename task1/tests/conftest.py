from typing import AsyncGenerator

from sqlalchemy import text

import pytest
from sqlalchemy.ext.asyncio import AsyncSession, create_async_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.pool import NullPool

from config import DB_HOST_TEST, DB_NAME_TEST, DB_PASS_TEST, DB_PORT_TEST, DB_USER_TEST
from database import metadata

DATABASE_TEST_URL = f"postgresql+asyncpg://{DB_USER_TEST}:{DB_PASS_TEST}@{DB_HOST_TEST}:{DB_PORT_TEST}/{DB_NAME_TEST}"

engine_test = create_async_engine(DATABASE_TEST_URL, poolclass=NullPool)
async_session_maker = sessionmaker(
    engine_test, class_=AsyncSession, expire_on_commit=False
)
metadata.bind = engine_test


async def override_get_async_session() -> AsyncGenerator[AsyncSession, None]:
    async with async_session_maker() as session:
        yield session


@pytest.fixture(autouse=True, scope="session")
async def prepare_database():
    async with engine_test.begin() as conn:
        await conn.run_sync(metadata.drop_all)
        await conn.run_sync(metadata.create_all)
    yield
    async with engine_test.begin() as conn:
        await conn.run_sync(metadata.drop_all)


@pytest.fixture(scope='function')
async def db_session():
    async with async_session_maker() as session:
        yield session
        await session.rollback()
        await session.close()


@pytest.fixture(scope='function')
async def insert_test_data(db_session):
    async for db_session in override_get_async_session():
        await db_session.execute(text("""
            INSERT INTO tag (name, immutable, separated) VALUES
            ('SRS', true, false),
            ('web_engine', false, false),
            ('sms', false, false),
            ('x86', false, false),
            ('svc', false, true),
            ('contacts', false, false),
            ('display', false, false),
            ('AUTO', true, false),
            ('lock_screen', false, false)
        """))

        await db_session.execute(text("""
            INSERT INTO synonym (name, tag_id) VALUES
            ('сообщения', (SELECT id FROM tag WHERE name = 'sms')),
            ('messages', (SELECT id FROM tag WHERE name = 'sms')),
            ('QEMU', (SELECT id FROM tag WHERE name = 'x86')),
            ('кему', (SELECT id FROM tag WHERE name = 'x86')),
            ('Service', (SELECT id FROM tag WHERE name = 'svc')),
            ('контакты', (SELECT id FROM tag WHERE name = 'contacts')),
            ('lcd', (SELECT id FROM tag WHERE name = 'display')),
            ('дисплэй', (SELECT id FROM tag WHERE name = 'display')),
            ('экран блокировки', (SELECT id FROM tag WHERE name = 'lock_screen'))
        """))

        await db_session.commit()
