# Импорт необходимых библиотек
import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap


# Реализуем класс узла
class Node:
    def __init__(self, index, t, true_branch, false_branch):
        self.index = index  # Индекс признака
        self.t = t  # Порог
        self.true_branch = true_branch  # Поддерево для true
        self.false_branch = false_branch  # Поддерево для false


class Leaf:
    def __init__(self, data, labels):
        self.prediction = self.predict(labels)

    def predict(self, labels):
        classes, counts = np.unique(labels, return_counts=True)
        return classes[np.argmax(counts)]


def gini(labels):
    _, counts = np.unique(labels, return_counts=True) 
    probs = counts / counts.sum()
    return np.sum(probs * (1 - probs)) # макс - поровну, мин - 1 класс


# показывает, насколько снизился критерий Джини после разделения узла на 2 части
def quality(left_labels, right_labels, current_gini):
    left_weight = len(left_labels) / (len(left_labels) + len(right_labels))
    return current_gini - left_weight * gini(left_labels) - (1 - left_weight) * gini(right_labels)



def split(data, labels, index, t):
    left_mask = data[:, index] <= t
    right_mask = data[:, index] > t
    return data[left_mask], labels[left_mask], data[right_mask], labels[right_mask]


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


def classify_object(obj, node):
    if isinstance(node, Leaf):
        return node.prediction
    
    if obj[node.index] <= node.t:
        return classify_object(obj, node.true_branch)
    else:
        return classify_object(obj, node.false_branch)


def predict(data, tree):
    return np.array([classify_object(obj, tree) for obj in data])


# Генерация данных и обучение дерева
classification_data, classification_labels = datasets.make_classification(n_features=2, n_informative=2, 
                                                                          n_classes=2, n_redundant=0, 
                                                                          n_clusters_per_class=1, random_state=5)

train_data, test_data, train_labels, test_labels = train_test_split(classification_data, classification_labels, test_size=0.3, random_state=1)

my_tree = build_tree(train_data, train_labels)



def accuracy_metric(actual, predicted):
    correct = (actual == predicted).sum()
    return correct / len(actual) * 100


train_predictions = predict(train_data, my_tree)
test_predictions = predict(test_data, my_tree)

train_accuracy = accuracy_metric(train_labels, train_predictions)
test_accuracy = accuracy_metric(test_labels, test_predictions)


colors = ListedColormap(['red', 'blue'])
light_colors = ListedColormap(['lightcoral', 'lightblue'])


def get_meshgrid(data, step=.05, border=1.2):
    x_min, x_max = data[:, 0].min() - border, data[:, 0].max() + border
    y_min, y_max = data[:, 1].min() - border, data[:, 1].max() + border
    return np.meshgrid(np.arange(x_min, x_max, step), np.arange(y_min, y_max, step))


plt.figure(figsize=(16, 7))


plt.subplot(1, 2, 1)
xx, yy = get_meshgrid(train_data)
mesh_predictions = predict(np.c_[xx.ravel(), yy.ravel()], my_tree).reshape(xx.shape)
plt.pcolormesh(xx, yy, mesh_predictions, cmap=light_colors)
plt.scatter(train_data[:, 0], train_data[:, 1], c=train_labels, cmap=colors)
plt.title(f'Train accuracy = {train_accuracy:.2f}%')

# график тестовой выборки
plt.subplot(1, 2, 2)
plt.pcolormesh(xx, yy, mesh_predictions, cmap=light_colors)
plt.scatter(test_data[:, 0], test_data[:, 1], c=test_labels, cmap=colors)
plt.title(f'Test accuracy = {test_accuracy:.2f}%')

plt.show()
