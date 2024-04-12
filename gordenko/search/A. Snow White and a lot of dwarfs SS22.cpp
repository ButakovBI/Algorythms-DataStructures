#include <iostream>

void process(int number, int* max, int* pre_max, int* first_number);

int main() {
    int number = -1;
    int first_number = 1;
    int max = 0, pre_max = 0;
    while (number != 0) {
        std::cin >> number;
        process(number, &max, &pre_max, &first_number);
    }
    std::cout << max << std::endl << pre_max;
    return 0;
}

void process(int number, int* max, int* pre_max, int* first_number) {
    if (*first_number) {
        *first_number = 0;
        *max = number;
    } else {
        if (number >= *max) {
            *pre_max = *max;
            *max = number;
        } else if (number > *pre_max) {
            *pre_max = number;
        }
    }
}