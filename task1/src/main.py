import asyncio

from sqlalchemy import text
from parser.tag_processor import apply_tag_rules
from database import get_async_session


async def insert_test_data():
    async for db_session in get_async_session():
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


async def check_rules():
    input_data = [
        ("WebEngine; AUTO", "web_engine; AUTO"),
        ("экран блокировки; дисплэй", "display; lock_screen"),
        ("КеМу", "x86"),
        ("DisplaySvc", "display; svc"),
        ("SomeTrashTag", ""),
        ("", ""),
        ("unknown-tag; lcd", "display"),
        ("auto", "AUTO"),
        ("дисплэй; сообщения", 'display; sms')
    ]

    async for db_session in get_async_session():
        for input_tags, expected_tags in input_data:
            result = await apply_tag_rules(input_tags, db_session)
            print(f"Processed tags: {result} | Expected: {expected_tags}")


async def main():
    await insert_test_data()
    await check_rules()
    

if __name__ == "__main__":
    asyncio.run(main())
