#include <iostream>

void more_than_previous(int* count, int number, int* prev, int* first_number);

int main() {
    int count = 0;
    int number = -1;
    int prev = -1;
    int first_number = 1;
    while (number != 0) {
        std::cin >> number;
        if (number != 0) {
            more_than_previous(&count, number, &prev, &first_number);
        }
    }
    std::cout << count;
    return 0;
}

void more_than_previous(int* count, int number, int* prev, int* first_number) {
    if (*first_number) {
        *first_number = 0;
    } else {
        if (number > *prev) {
            (*count)++;
        }
    }
    *prev = number;

}