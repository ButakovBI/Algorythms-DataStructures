Давайте пройдемся по каждому элементу кода и разберем, что происходит на каждом шаге, а также объясним, зачем используется та или иная функция.

### 1. **Импортирование библиотек**

```python
from sklearn import model_selection
```

Здесь мы импортируем библиотеку `model_selection` из `sklearn`, которая позволяет удобно разделить данные на обучающую и тестовую выборки, используя функцию `train_test_split`.

### 2. **Разделение данных на обучающую и тестовую выборки**

```python
train_data, test_data, train_labels, test_labels = model_selection.train_test_split(classification_data,
                                                                                     classification_labels,
                                                                                     test_size=0.3,
                                                                                     random_state=1)
```

Здесь мы делим данные (`classification_data`) и метки классов (`classification_labels`) на две выборки:
- **Обучающая выборка** (`train_data`, `train_labels`), на которой будет обучаться модель.
- **Тестовая выборка** (`test_data`, `test_labels`), которая используется для проверки точности модели.

Мы задаем параметр `test_size=0.3`, что означает, что 30% данных будет использоваться для тестирования, а 70% — для обучения. Параметр `random_state=1` позволяет гарантировать воспроизводимость разделения данных.

### 3. **Функция для расчета точности модели**

```python
def accuracy_metric(actual, predicted):
    correct = 0
    for i in range(len(actual)):
        if actual[i] == predicted[i]:
            correct += 1
    return correct / float(len(actual)) * 100.0
```

Эта функция вычисляет точность модели, то есть, какой процент правильных предсказаний было сделано моделью. Мы сравниваем реальные метки (`actual`) с предсказанными метками (`predicted`), и если они совпадают, увеличиваем счетчик правильных предсказаний. Затем делим число правильных предсказаний на общее количество и умножаем на 100, чтобы получить точность в процентах.

### 4. **Функция для расчета наилучшего разбиения в дереве**

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

Эта функция находит наилучшее разбиение данных в текущем узле дерева. Для этого:
1. Для каждого признака (колонки данных) вычисляются возможные пороги (значения признаков, которые могут быть использованы для разбиения).
2. Для каждого порога мы разделяем данные на два подмножества (левая и правая ветви).
3. Затем мы вычисляем, насколько улучшился критерий Джини (`quality`), если бы мы использовали это разбиение.
4. Функция возвращает наилучший порог и признак для разбиения, которые минимизируют критерий Джини.

### 5. **Функции для разбиения данных и расчета критерия Джини**

```python
def split(data, labels, index, t):
    left_mask = data[:, index] <= t
    right_mask = data[:, index] > t
    
    true_data = data[left_mask]
    false_data = data[right_mask]
    true_labels = labels[left_mask]
    false_labels = labels[right_mask]

    return true_data, false_data, true_labels, false_labels
```

Функция `split` делит данные на две части по выбранному индексу признака и порогу. `left_mask` и `right_mask` — это булевы маски, которые показывают, какие данные попадают в левую ветвь (если значение признака меньше или равно порогу) и в правую ветвь (если значение больше порога).

```python
def gini(labels):
    _, counts = np.unique(labels, return_counts=True) 
    probs = counts / counts.sum()
    return np.sum(probs * (1 - probs)) 
```

Функция `gini` вычисляет критерий Джини для набора меток классов. Это мера "нечистоты" подмножества: чем ниже значение, тем более однородным является множество.

```python
def quality(left_labels, right_labels, current_gini):
    left_weight = len(left_labels) / (len(left_labels) + len(right_labels))
    return current_gini - left_weight * gini(left_labels) - (1 - left_weight) * gini(right_labels)
```

Функция `quality` вычисляет улучшение критерия Джини после разбиения данных на две части (левая и правая). Чем больше улучшение, тем лучше это разбиение.

### 6. **Реализация дерева решений**

```python
class Node:
    def __init__(self, index, t, true_branch, false_branch):
        self.index = index
        self.t = t
        self.true_branch = true_branch
        self.false_branch = false_branch
```

`Node` — это класс для узлов дерева. Каждый узел хранит:
- Индекс признака, по которому произошло разбиение (`index`),
- Порог (`t`), по которому разделяются данные,
- Поддеревья (левая и правая ветви дерева) — это либо другие узлы, либо листья.

```python
class Leaf:
    def __init__(self, data, labels):
        self.prediction = self.predict(labels)

    def predict(self, labels):
        classes, counts = np.unique(labels, return_counts=True)
        return classes[np.argmax(counts)]
```

`Leaf` — это класс для листа дерева, который хранит предсказание для данного набора данных. Лист принимает метки классов и выбирает класс, который встречается наиболее часто.

### 7. **Построение дерева**

```python
def build_tree(data, labels):
    quality, t, index = find_best_split(data, labels)

    if quality == 0:
        return Leaf(data, labels)

    true_data, false_data, true_labels, false_labels = split(data, labels, index, t)

    true_branch = build_tree(true_data, true_labels)
    false_branch = build_tree(false_data, false_labels)

    return Node(index, t, true_branch, false_branch)
```

Функция `build_tree` строит дерево решений рекурсивно:
1. Находит наилучшее разбиение для текущего набора данных с помощью `find_best_split`.
2. Если улучшение критерия Джини нулевое (т.е. нет смысла разбиения), создает лист.
3. Если разбиение возможно, рекурсивно строит два поддерева: для левой и правой части данных.

### 8. **Получение bootstrap выборок**

```python
def get_bootstrap(data, labels, N):
    n_samples = data.shape[0]
    bootstrap = []

    for i in range(N):
        b_data = np.zeros(data.shape)
        b_labels = np.zeros(labels.shape)

        for j in range(n_samples):
            random_index = random.randint(0, n_samples - 1)
            b_data[j] = data[random_index]
            b_labels[j] = labels[random_index]

        bootstrap.append((b_data, b_labels))

    return bootstrap
```

`get_bootstrap` генерирует N случайных выборок с повторением из исходных данных. Это делается путем случайного выбора данных (с возвратом) для каждой выборки, что позволяет получить разнообразие в случайном лесе.

### 9. **Сборка случайного леса**

```python
def random_forest(data, labels, n_trees):
    forest = []
    bootstrap_samples = get_bootstrap(data, labels, n_trees)

    for b_data, b_labels in bootstrap_samples:
        tree = build_tree(b_data, b_labels)
        forest.append(tree)

    return forest
```

Функция `random_forest` строит случайный лес из N деревьев:
1. Для каждого дерева генерируется bootstrap выборка.
2. Для каждой bootstrap выборки строится дерево с помощью функции `build_tree`.

### 10. **Голосование деревьев для предсказания**

```python
def tree_vote(forest, data):
    all_predictions = []

    for obj in data:
        tree_predictions = [classify_object(obj, tree) for tree in forest]
        all_predictions.append(tree_predictions)

    voted_predictions = [max(set(predictions), key=predictions.count) for predictions in all_predictions]

    return np.array(voted_predictions)
```

`tree_vote` собирает предсказания всех деревьев для каждого объекта и применяет голосование:
1. Для каждого объекта вычисляются предсказания всех деревьев.
2. Для каждого объекта выбира

ется наиболее часто встречающийся класс.

---

### Заключение:
Этот код реализует **метод случайного леса** с деревьями решений, которые строятся на случайных подмножествах данных (bootstrap выборках). Каждое дерево обучается на случайной выборке и предсказывает класс, а результат предсказания случайного леса — это результат голосования всех деревьев.