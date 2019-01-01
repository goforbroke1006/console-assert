//
// Created by goforbroke on 02.01.19.
//

#include <cstdlib>
#include <ctime>
#include <iostream>

int myRand(const int &min, const int &max) {
    return min + (rand() % static_cast<int>(max - min + 1));
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void print(int *arr, size_t size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
}

int main() {
    srand(time(0));

    int *arr = new int[10]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

    int pos1, pos2;

    for (int i = 0; i < 100; ++i) {
        pos1 = myRand(0, 9);
        pos2 = myRand(0, 9);

        swap(arr[pos1], arr[pos2]);
    }

    print(arr, 10);
}
