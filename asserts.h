//
// Created by goforbroke on 01.01.19.
//

#ifndef CONSOLE_ASSERT_ASSERTS_H
#define CONSOLE_ASSERT_ASSERTS_H

#include <cstdlib>

bool assertArrayEquals(
        const int *arr1, const size_t &s1,
        const int *arr2, const size_t &s2
) {
    if (s1 != s2) return false;
    for (int i = 0; i < s1; ++i) {
        bool found = false;
        for (int j = 0; j < s2; ++j) {
            if (arr1[i] == arr2[j]) found = true;
        }
        if (!found) return false;
    }
    return true;
}

#endif //CONSOLE_ASSERT_ASSERTS_H
