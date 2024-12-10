import pytest
from parser.data_classes import AllowedTagRecord
from parser.parse_from_table import parse_html_to_rules

html_table = """
<table>
    <tr>
        <th>тэг</th>
        <th>комментарий</th>
        <th>синонимы</th>
        <th>оставить как есть</th>
        <th>часть составного тега</th>
    </tr>
    <tr>
        <td>svc</td>
        <td>сервис</td>
        <td>Service</td>
        <td></td>
        <td>да</td>
    </tr>
    <tr>
        <td>sms</td>
        <td></td>
        <td>сообщения, messages</td>
        <td></td>
        <td></td>
    </tr>
    <tr>
        <td>AUTO</td>
        <td>автобаги</td>
        <td></td>
        <td>да</td>
        <td></td>
    </tr>
</table>
"""


def test_parse_html_to_rules():
    expected_rules = [
        AllowedTagRecord(
            allowed_name="svc",
            synonyms="Service",
            immutable=False,
            separated=True),
        AllowedTagRecord(
            allowed_name="sms",
            synonyms="сообщения, messages",
            immutable=False,
            separated=False),
        AllowedTagRecord(
            allowed_name="AUTO",
            synonyms=None,
            immutable=True,
            separated=False)]

    result = parse_html_to_rules(html_table)

    assert result == expected_rules
