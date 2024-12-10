### 1. **Класс `Node`**
```python
class Node:
    def __init__(self, index, t, true_branch, false_branch):
        self.index = index  # Индекс признака
        self.t = t  # Пороговое значение
        self.true_branch = true_branch  # Ветка для объектов, где признак <= t
        self.false_branch = false_branch  # Ветка для объектов, где признак > t
```
#### **Задача**:  
Класс `Node` описывает узел дерева, который проверяет условие. Узел хранит:
1. **Признак (`index`)**: Какой столбец из данных проверяется.
2. **Порог (`t`)**: Сравнение значения признака с этим порогом.
3. **Ветки (`true_branch`, `false_branch`)**: Ссылки на поддеревья (ветви), куда данные попадут в зависимости от выполнения условия.

---

### 2. **Класс `Leaf`**
```python
class Leaf:
    def __init__(self, data, labels):
        self.prediction = self.predict(labels)

    def predict(self, labels):
        classes, counts = np.unique(labels, return_counts=True)
        return classes[np.argmax(counts)]
```
#### **Задача**:
`Leaf` описывает конечный узел дерева (лист). В лист попадают данные, которые нельзя разделить дальше.  
Лист вычисляет и хранит прогноз:
- Прогноз — это **наиболее часто встречающийся класс** среди объектов в листе.

**Код:**
1. В конструкторе (`__init__`) вызывается метод `predict`, который:
   - Находит все классы и их частоты (`np.unique(labels, return_counts=True)`).
   - Определяет самый частый класс с помощью `np.argmax(counts)`.
2. Результат сохраняется в атрибуте `self.prediction`.

---

### 3. **Функция `gini`**
```python
def gini(labels):
    _, counts = np.unique(labels, return_counts=True)
    probs = counts / counts.sum()
    return 1 - np.sum(probs**2)
```
#### **Задача**:
Расчет критерия Джини, который измеряет "чистоту" узла.  
- Если все объекты в узле принадлежат одному классу, значение Джини = 0 (идеальная "чистота").
- Чем больше смешение классов, тем больше значение Джини.

**Код:**
1. `np.unique(labels, return_counts=True)`:
   - Определяет уникальные классы и их частоты.
2. `counts / counts.sum()`:
   - Вычисляет вероятность появления каждого класса (частота делится на общее число объектов).
3. `1 - np.sum(probs**2)`:
   - Квадрат вероятностей суммируется и вычитается из 1. Это формула критерия Джини.

---

### 4. **Функция `quality`**
```python
def quality(left_labels, right_labels, current_gini):
    left_weight = len(left_labels) / (len(left_labels) + len(right_labels))
    return current_gini - left_weight * gini(left_labels) - (1 - left_weight) * gini(right_labels)
```
#### **Задача**:
Оценка качества разбиения узла. Показывает, насколько снизился критерий Джини после деления узла на две части.

**Код:**
1. Вычисляется **доля левой ветви** в общем количестве данных:  
   ```python
   left_weight = len(left_labels) / (len(left_labels) + len(right_labels))
   ```
2. Для каждой ветви вычисляется критерий Джини:  
   ```python
   gini(left_labels), gini(right_labels)
   ```
3. Считается разница между текущим значением Джини (`current_gini`) и взвешенными значениями для обеих ветвей:  
   ```python
   current_gini - left_weight * gini(left_labels) - (1 - left_weight) * gini(right_labels)
   ```

---

### 5. **Функция `split`**
```python
def split(data, labels, index, t):
    left_mask = data[:, index] <= t
    right_mask = ~left_mask
    return data[left_mask], labels[left_mask], data[right_mask], labels[right_mask]
```
#### **Задача**:
Разделить данные и метки на две группы по заданному признаку `index` и порогу `t`.

**Код:**
1. Создается логическая маска (`left_mask`), где объекты удовлетворяют условию `data[:, index] <= t`.
2. Инвертируется маска (`right_mask`) для получения объектов, которые **не** удовлетворяют условию.
3. Возвращаются:
   - Данные и метки для левой группы (`data[left_mask], labels[left_mask]`).
   - Данные и метки для правой группы (`data[right_mask], labels[right_mask]`).

---

### 6. **Функция `find_best_split`**
```python
def find_best_split(data, labels):
    best_quality = -1
    best_t = None
    best_index = None
    current_gini = gini(labels)
    
    n_features = data.shape[1]
    for index in range(n_features):
        thresholds = np.unique(data[:, index])
        for t in thresholds:
            left_data, left_labels, right_data, right_labels = split(data, labels, index, t)
            if len(left_labels) == 0 or len(right_labels) == 0:
                continue
            
            current_quality = quality(left_labels, right_labels, current_gini)
            if current_quality > best_quality:
                best_quality = current_quality
                best_t = t
                best_index = index
    
    return best_quality, best_t, best_index
```
#### **Задача**:
Найти наилучший признак (`index`) и порог (`t`) для разбиения данных.

**Код:**
1. Инициализация переменных для хранения лучшего разбиения (`best_quality`, `best_t`, `best_index`).
2. Вычисляется текущее значение Джини для узла (`current_gini`).
3. Цикл по всем признакам:
   - Определяются все уникальные значения признака (возможные пороги) с помощью `np.unique`.
   - Для каждого порога данные делятся на группы с помощью `split`.
   - Проверяются только те пороги, которые реально делят данные.
4. Оценивается качество разбиения с помощью `quality`.
5. Если качество выше предыдущего лучшего (`current_quality > best_quality`), обновляются переменные.

---

### 7. **Функция `build_tree`**
```python
def build_tree(data, labels, min_leaf=5):
    if len(data) <= min_leaf or len(np.unique(labels)) == 1:
        return Leaf(data, labels)
    
    best_quality, best_t, best_index = find_best_split(data, labels)
    if best_quality == -1:
        return Leaf(data, labels)
    
    left_data, left_labels, right_data, right_labels = split(data, labels, best_index, best_t)
    true_branch = build_tree(left_data, left_labels, min_leaf)
    false_branch = build_tree(right_data, right_labels, min_leaf)
    
    return Node(best_index, best_t, true_branch, false_branch)
```
#### **Задача**:
Построить дерево рекурсивно, начиная с корня.

**Код:**
1. Если количество объектов меньше `min_leaf` или все объекты одного класса, создается лист (`Leaf`).
2. Ищется лучшее разбиение с помощью `find_best_split`.
3. Если разбиение не найдено, также создается лист.
4. Делятся данные на две группы (`split`), и для каждой группы вызывается `build_tree` (рекурсия).
5. Создается узел (`Node`) с найденным признаком, порогом и ветвями.

---

### 8. **Функция `classify_object`**
```python
def classify_object(obj, node):
    if isinstance(node, Leaf):
        return node.prediction
    
    if obj[node.index] <= node.t:
        return classify_object(obj, node.true_branch)
    else:
        return classify_object(obj, node.false_branch)
```
#### **Задача**:
Определить класс для одного объекта, проходя по дереву.

**Код:**
1. Если текущий узел — лист, возвращается прогноз (`node.prediction`).
2. Иначе проверяется условие:
   - Если значение признака `<= t`, объект направляется в левую ветвь (`true_branch`).
   - Иначе — в правую ветвь (`false_branch`).

---

### 9. **Функция `predict`**
```python
def predict(data, tree):
    return np.array([classify_object(obj, tree) for obj in data])
```
#### **Задача**:
Применить дерево ко всему набору данных.

**Код:**
- Для каждого объекта в `data` вызывается `classify_object`.
- Результаты собираются в массив `np.array`.

---

### 10. **Функция `accuracy_metric`**
```

python
def accuracy_metric(actual, predicted):
    correct = (actual == predicted).sum()
    return correct / len(actual) * 100
```
#### **Задача**:
Рассчитать точность модели как процент правильных предсказаний.

**Код:**
1. `actual == predicted`: массив логических значений, где `True` означает правильный прогноз.
2. `sum()`: подсчитывает количество правильных прогнозов.
3. Делится на общее число объектов и умножается на 100, чтобы получить процент.