#include <iostream>

int max(int a, int b);
void monotonous(int number, int* prev, int* first_number, int* mode, int* count, int* ans);

int main() {
    int prev = -1;
    int first_number = 1;
    int mode = 0;
    int number = -1;
    int count = 0;
    int ans = 0;
    while (number != 0) {
        std::cin >> number;
        if (number != 0) {
            monotonous(number, &prev, &first_number, &mode, &count, &ans);
        }
    }
    if (ans == 0 && first_number == 0) {
        ans = 1;
    }
    std::cout << ans;
    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void monotonous(int number, int* prev, int* first_number, int* mode, int* count, int* ans) {
    if (*mode == 0) {
        if (*first_number) {
            *first_number = 0;
        } else {
            if (number > *prev) {
                *mode = 1;
                *count = 2;
                *ans = max(*ans, *count);
            } else if (number < *prev){
                *mode = -1;
                *count = 2;
                *ans = max(*ans, *count);
            }

        }
    } else if (*mode == 1) {
        if (number > *prev) {
            *count += 1;
            *ans = max(*ans, *count);
        } else if (number < *prev) {
            *mode = -1;
            *count = 2;
        } else {
            *mode = 0;
            *count = 0;
        }
    } else if (*mode == -1) {
        if (number < *prev) {
            *count += 1;
            *ans = max(*ans, *count);
        } else if (number > *prev) {
            *mode = 1;
            *count = 2;
        } else {
            *mode = 0;
            *count = 0;
        }
    }
    *prev = number;
}
