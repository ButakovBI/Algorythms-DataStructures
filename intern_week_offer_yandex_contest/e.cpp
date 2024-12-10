#include <iostream>
#include <vector>

// 6
// 0 0 2 2
// 0 0 1 3
// -3 2 3 3
// -2 0 -1 4
// -3 -1 1 1
// -3 -2 3 3

struct Point {
  int x;
  int y;

  Point(int x, int y) : x(x), y(y) {}
};

struct Rectangle {
  Point A;
  Point B;
  Point C;
  Point D;

  Rectangle(Point A, Point B, Point C, Point D) : A(A), B(B), C(C), D(D) {}
};

void calc_intersections(const std::vector<std::vector<int>>& rectangles,
                        std::vector<int>& cnt_intersections, int i, int x,
                        int y, int x1, int y1) {
  for (int j = i - 1; j >= 0; j -= 1) {
    if (!(y1 <= rectangles[j][1] || y >= rectangles[j][3] ||
          x1 <= rectangles[j][0] || x >= rectangles[j][2])) {
      cnt_intersections[i] += 1;
      cnt_intersections[j] += 1;
    }
  }
}

void solution() {
  int n = 0;
  std::cin >> n;

  std::vector<std::vector<int>> rectangles(n, std::vector<int>(4));
  std::vector<int> cnt_intersections(n, 0);

  for (int i = 0; i < n; i += 1) {
    int x = 0;
    int y = 0;
    int x1 = 0;
    int y1 = 0;
    std::cin >> x >> y >> x1 >> y1;

    rectangles[i][0] = x;
    rectangles[i][1] = y;
    rectangles[i][2] = x1;
    rectangles[i][3] = y1;

    if (i > 0) {
      calc_intersections(rectangles, cnt_intersections, i, x, y, x1, y1);
    }
  }

  for (int i = 0; i < n; i += 1) {
    std::cout << cnt_intersections[i] << ' ';
  }
}

int main() {
  solution();

  return 0;
}
