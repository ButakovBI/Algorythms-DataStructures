#### Предыстория
Некоторый проект X использует абстрактрую систему управления проектами (далее`АСУП?`), в которой можно удобно планировать выполнение задач.

У задачи есть набор признаков:

| имя         | тип | описание                        |
| ----------- | --- | ------------------------------- |
| id          | int | идентификационный номер         |
| title       | str | заголовок                       |
| description | str | описание                        |
| tags        | str | теги, строка, теги разделены`;` |
| creator     | str | имя и фамилия создателя задачи  |
В проекте возникла потребность в группировке задач по некоторым признакам для удобного поиска, анализа и планирования. Для чего было решено использовать признак задачи: `тег`.

Но до того момента, как было принято подобное решение, каждый мог создавать и выставлять различные теги, из-за чего возникло большое количество дублирующих и лишних тегов, от этого и требуется избавиться.
## Основное задание
Требуется написать функцию `apply_tag_rules`, которая преобразует теги в соответствии с правилами:

 1. Основное правило формата тега: `snake_case`, если это не зарезервированный тег (флаг в таблице правил immutable=True)
 2. Есть предопределенная таблица разрешенных тегов, она может изменяться при каждом запуска (удаляться записи, добавляться новые, изменяться существующие.)
 3. Если после преобразования тег присутствует   в поле `allowed_name` в таблице разрешенных , то  результатом будет преобразованный тег.
 4. У тега существуют теги-синонимы, которые могут встречаться и которые нужно заменить на исходный из поля `allowed_name`, например, у тега `my_pretty_tag` есть синоним `мой_прекрасный_тег`, автоматической заменой будет изменение синонима `мой_прекрасный_тег` на `my_pretty_tag`.
 5. Есть предопределенные теги, которые запрещено менять, игнорируя правило 1.
    Такие теги помечены в таблице флагом `immutable=True`. 
 6. Если тег не найден в таблице правил и даже после преобразования, тег нужно удалить.
 7. При наличии составного тега (несколько тегов в одном), требуется их разделить на два и привести к верному формату по правилам выше. Например: `DisplayService` содержит два разрешенных тега `display` и `svc`, один тег, нужно заменить двумя. Это правило распространяется на теги из таблицы правил, где флаг `separated=True`.
```python
from typing import NamedTuple

class AllowedTagRecord(NamedTuple):
	"""Запись в таблице правил."""
    allowed_name: str
    synonyms: str | None = None
    immutable: bool = False
    separated: bool = False


def apply_tag_rules(
		tags: str, 
		rules: tuple[AllowedTagRecord, ...], 
		task_id: int | None = None,
		delayed_clean: bool = False
	) -> str:
	"""
	Применение правил к тегам.
	
	:param tags: Строка, содержащая теги.
	:param rules: Кортеж правил.
	:param task_id: идентификатор задачи, опциональное поле для дополнительного задания.
	:param delayed_clean: флаг, сигнализирующий о включении дополнительной функциональности - отложенного удаления неверных тегов.
	:return str: Возвращает строку с преобразованными тегами.
	"""
    # your code here
    ...

if __name__ == "__main__":
	# пример таблицы правил
    rules = (
	    # зарезервированный тег, менять нельзя
        AllowedTagRecord("SRS", immutable=True),
        AllowedTagRecord("web_engine"),
        # тег с известными синонимами
        AllowedTagRecord("sms", "сообщения, messages"),
        AllowedTagRecord("x86", "QEMU, кему"),
        # тег, при наличии в составе тега, нужно вынести в отдельный, есть
        # синоним
        AllowedTagRecord("svc", "Service", separated=True),
        AllowedTagRecord("contacts", "контакты"),
        AllowedTagRecord("display", "lcd, дисплей"),
        AllowedTagRecord("AUTO", immutable=True),
        AllowedTagRecord("lock_screen", "экран блокировки"),
    )

    for input_tags, expected_tags in (
	    # тег WebEngine заменился на тег из правил web_engine
	    # тег AUTO остался неизменным
        ("WebEngine; AUTO", "web_engine; AUTO"),
        # тег-синоним заменился на исходный
        ("экран блокировки; дисплэй", "lock_screen"),
        # тег-синоним заменился на исходный
        ("КеМу", "x86"),
        # тег разделился на два из-за наличия svc
        ("DisplaySvc", "display; svc"),
        # неизвестный тег, удаляем
        ("SomeTrashTag", ""),
        # нет тегов, ну и не надо
        ("", ""),
        # неизвестный тег удален, известный синоним заменен
        ("unknown-tag; lcd", "display"),
        ("auto", "AUTO"),
    ):
        assert apply_tag_rules(input_tags, rules) == expected_tags
```
## Дополнительные задания:
#### 1. Парсер таблицы правил из html-таблицы. 
Нужно написать преобразование такой таблицы в формат, поддерживаемый функцией `apply_tag_rules`
```html
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
		<td> </td>
		<td> </td>
	</tr>
	<tr>
		<td>AUTO</td>
		<td>автобаги</td>
		<td></td>
		<td>да</td>
		<td></td>
	</tr>
</table>
```
#### 2. Механизм отложенного удаления: 
Требуется реализовать дополнительный механизм, который бы не сразу удалял неверный тег, а сохранял его в некий кеш (произвольное хранилище) сроком на **2 недели**:
- Кеш должен быть доступен на каждом запуске и учитывать существующие записи:
	- При работе механизма отложенного удаления теги не будут моментально удаляться из задачи, поэтому задача при каждом запуске программы будет появляться на входе функции, но запись в кеше при этом не должна обновляться.
-  Управлять включением механизма должен флаг `delayed_clean`. Если механизм включен, то 
	- пока срок удаления не подошел -  некорректные теги не удаляются в выходной строке.
	- срок подошел: некорректные теги удалились в выходной строке.
- Если выключен, то тег просто удаляется, кеш не используется.

## Общие требования к реализации:
 1. Требуется использовать минимальное количество зависимостей. В идеале, если все будет написано только с использованием Python Standard Library. Требуется соблюсти балланс, если какая-то библиотека уже делает что-то хорошо, ее можно использовать. ***Выбор библиотеки потребует указания ее наименования рядом с импортом и обоснование  в комментарии в коде.***
 2. Использовать type-hints
 3. Сопроводить реализованный код документацией через docstrings.