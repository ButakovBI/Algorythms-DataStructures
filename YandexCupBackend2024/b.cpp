#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления обратного элемента по модулю 23
int mod_inverse(int x, int mod) {
    for (int i = 1; i < mod; ++i) {
        if ((x * i) % mod == 1) {
            return i;
        }
    }
    return -1;  // Если обратный элемент не найден
}

// Функция для приведения числа к положительному значению по модулю
int mod(int x, int m) {
    return (x % m + m) % m;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<long long> x(m);
    vector<int> b(m);
    
    // Вводим x_j
    for (int i = 0; i < m; ++i) {
        cin >> x[i];
    }
    
    // Вводим b_j
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // Матрица системы и вектор правой части
    vector<vector<int>> matrix(m, vector<int>(n));
    vector<int> result(m);

    // Заполняем матрицу степенями x_j и правую часть b_j
    for (int j = 0; j < m; ++j) {
        long long x_power = 1;
        for (int i = 0; i < n; ++i) {
            matrix[j][i] = x_power % 23;  // x_j^(i-1) % 23
            x_power = (x_power * x[j]) % 23;
        }
        result[j] = b[j];
    }

    // Метод Гаусса для решения системы по модулю 23
    for (int i = 0; i < min(m, n); ++i) {
        // Находим ведущий элемент и нормализуем строку
        if (matrix[i][i] == 0) {
            for (int j = i + 1; j < m; ++j) {
                if (matrix[j][i] != 0) {
                    swap(matrix[i], matrix[j]);
                    swap(result[i], result[j]);
                    break;
                }
            }
        }

        int inv = mod_inverse(matrix[i][i], 23);
        if (inv == -1) {
            continue;  // Если не удалось найти обратный элемент
        }

        // Нормализуем текущую строку
        for (int j = i; j < n; ++j) {
            matrix[i][j] = (matrix[i][j] * inv) % 23;
        }
        result[i] = (result[i] * inv) % 23;

        // Вычитаем текущую строку из всех остальных
        for (int j = 0; j < m; ++j) {
            if (i != j) {
                int factor = matrix[j][i];
                for (int k = i; k < n; ++k) {
                    matrix[j][k] = mod(matrix[j][k] - factor * matrix[i][k], 23);
                }
                result[j] = mod(result[j] - factor * result[i], 23);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << char('a' + result[i] % 23);
    }
    cout << endl;

    return 0;
}
