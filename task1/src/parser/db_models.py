from datetime import timedelta
from sqlalchemy import (
    Boolean,
    Column,
    DateTime,
    ForeignKey,
    Integer,
    String,
    Table,
    func,
)

from database import metadata

# Таблица для исходных тегов
tags_table = Table(
    "tag",
    metadata,
    Column("id", Integer, primary_key=True),
    Column("name", String, unique=True, nullable=False),
    Column("immutable", Boolean, default=False),
    Column("separated", Boolean, default=False),
)

# Таблица с синонимами тегов - связь с основной по fk
synonyms_table = Table(
    "synonym",
    metadata,
    Column("id", Integer, primary_key=True),
    Column("name", String, nullable=False),
    Column("tag_id", Integer, ForeignKey("tag.id"), nullable=False),
)

# Таблица для логов - добавления, изменения, удаления тега из таблицы тегов
log_table = Table( 
    "log",
    metadata,
    Column("id", Integer, primary_key=True),
    Column("action", String, nullable=False),  # тип действия: 'create', 'update', 'delete'
    Column("target_table", String, nullable=False),
    Column("target_id", Integer, nullable=False),
    Column("timestamp", DateTime, server_default=func.now()),
)


# Таблица кэша тегов - доп. задание
tag_cache_table = Table(
    "tag_cache",
    metadata,
    Column("id", Integer, primary_key=True),
    Column("tag_name", String, unique=True, nullable=False),
    Column("added_timestamp", DateTime, default=func.now()),
    Column("expiration_date", DateTime, default=func.now() + timedelta(weeks=2)),
)
