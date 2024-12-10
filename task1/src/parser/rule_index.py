from typing import Tuple, Dict
from parser.data_classes import AllowedTagRecord


async def build_rule_index(
        rules: Tuple[AllowedTagRecord, ...]) -> Dict[str, AllowedTagRecord]:
    """Создаёт индекс для быстрого поиска правил по имени и синонимам."""
    rule_index = {}
    for rule in rules:
        rule_index[rule.allowed_name.lower()] = rule
        if rule.synonyms:
            for synonym in map(str.strip, rule.synonyms.split(',')):
                rule_index[synonym.lower()] = rule
    return rule_index
