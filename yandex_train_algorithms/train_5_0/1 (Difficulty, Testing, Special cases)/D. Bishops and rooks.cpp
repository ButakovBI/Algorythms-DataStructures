#include <iostream>
#include <vector>

void bishop_beat(std::vector<std::vector<char>>& board, std::vector<std::vector<bool>>& ans_board,
                 int x, int y, int n);
void rook_beat(std::vector<std::vector<char>>& board, std::vector<std::vector<bool>>& ans_board,
               int x, int y, int n);

int main() {
    const int n = 8;
    char sym = 0;
    std::vector<std::vector<bool>> ans_board(n, std::vector<bool>(n, false));
    std::vector<std::vector<char>> board(n, std::vector<char>(n, '*'));
    int cnt = 0;
    while (cnt < n * n) {
        std::cin >> sym;
        if (sym == 'B') {
            board[cnt / n][cnt % n] = 'B';
            cnt++;
        } else if (sym == 'R') {
            board[cnt / n][cnt % n] = 'R';
            cnt++;
        } else if (sym == '*') {
            cnt++;
        }
    }
    for (int i = 0; i < n; i += 1) {
        for (int j = 0; j < n; j += 1) {
            if (board[i][j] == 'B') {
                bishop_beat(board, ans_board, i, j, n);
            } else if (board[i][j] == 'R') {
                rook_beat(board, ans_board, i, j, n);
            }
        }
    }
    int ans = 0;
    for (size_t i = 0; i < n; i += 1) {
        for (size_t j = 0; j < n; j += 1) {
            if (!ans_board[i][j]) {
                ans++;
            }
        }
    }
    std::cout << ans;
    return 0;
}

void bishop_beat(std::vector<std::vector<char>>& board, std::vector<std::vector<bool>>& ans_board,
                 int x, int y, const int n) {
    ans_board[x][y] = true;
    int i = 1;
    while (x - i >= 0 && y - i >= 0 && board[x - i][y - i] == '*') {
        ans_board[x - i][y - i] = true;
        i++;
    }
    i = 1;
    while (x - i >= 0 && y + i < n && board[x - i][y + i] == '*') {
        ans_board[x - i][y + i] = true;
        i++;
    }
    i = 1;
    while (x + i < n && y - i >= 0 && board[x + i][y - i] == '*') {
        ans_board[x + i][y - i] = true;
        i++;
    }
    i = 1;
    while (x + i < n && y + i < n && board[x + i][y + i] == '*') {
        ans_board[x + i][y + i] = true;
        i++;
    }
}

void rook_beat(std::vector<std::vector<char>>& board, std::vector<std::vector<bool>>& ans_board,
               int x, int y, const int n) {
    ans_board[x][y] = true;
    int i = 1;
    while (x - i >= 0 && board[x - i][y] == '*') {
        ans_board[x - i][y] = true;
        i++;
    }
    i = 1;
    while (y - i >= 0 && board[x][y - i] == '*') {
        ans_board[x][y - i] = true;
        i++;
    }
    i = 1;
    while (x + i < n && board[x + i][y] == '*') {
        ans_board[x + i][y] = true;
        i++;
    }
    i = 1;
    while (y + i < n && board[x][y + i] == '*') {
        ans_board[x][y + i] = true;
        i++;
    }
}