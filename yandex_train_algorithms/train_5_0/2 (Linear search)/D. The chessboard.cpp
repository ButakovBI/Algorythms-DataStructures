#include <iostream>
#include <vector>

int main() {
    int n = 0;
    std::cin >> n;

    std::vector<std::vector<bool>> board(8, std::vector<bool>(8, false));
    int x = 0, y = 0;
    for (int i = 0; i < n; i += 1) {
        std::cin >> x >> y;
        board[x - 1][y - 1] = true;
    }

    int perimeter = 0;

    for (int i = 0; i < 8; i += 1) {
        for (int j = 0; j < 8; j += 1) {
            if (board[i][j]) {
                if (i == 0 || !board[i - 1][j]) perimeter++; // top
                if (i == 7 || !board[i + 1][j]) perimeter++; // bottom
                if (j == 0 || !board[i][j - 1]) perimeter++; // left
                if (j == 7 || !board[i][j + 1]) perimeter++; // right
            }
        }
    }

    std::cout << perimeter << std::endl;

    return 0;
}