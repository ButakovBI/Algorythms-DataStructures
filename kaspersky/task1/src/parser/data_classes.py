from typing import NamedTuple


class AllowedTagRecord(NamedTuple):
    """Запись в таблице правил."""
    allowed_name: str
    synonyms: str | None = None
    immutable: bool = False
    separated: bool = False