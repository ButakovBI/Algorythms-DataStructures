#include <iostream>
#include <vector>


bool isSafe(std::vector<int>& board, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || std::abs(board[i] - col) == std::abs(i - row)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int n, int row, std::vector<int>& board, int& cnt) {
    if (row == n) {
        cnt++;
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(n, row + 1, board, cnt);
        }
    }
}

int totalNQueens(int n) {
    std::vector<int> board(n, -1);
    int cnt = 0;
    solveNQueens(n, 0, board, cnt);
    return cnt;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::cout << totalNQueens(n) << '\n';
    return 0;
}
