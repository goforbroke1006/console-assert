//
// Created by goforbroke on 01.01.19.
//

#ifndef CONSOLE_ASSERT_ASSERTS_H
#define CONSOLE_ASSERT_ASSERTS_H

#include <cstdlib>
#include <vector>

namespace asserts {

    template<typename T>
    bool assertArrayEquals(
            const T *arr1, const size_t &s1,
            const T *arr2, const size_t &s2
    ) {
        if (s1 != s2) return false;
        for (int i = 0; i < s1; ++i) {
            bool found = false;
            for (int j = 0; j < s2; ++j) {
                if (arr1[i] == arr2[j])
                    found = true;
            }
            if (!found)
                return false;
        }
        return true;
    }

    template<typename T>
    bool assertVectorsEquals(std::vector<T> v1, std::vector<T> v2) {
        return assertArrayEquals(v1.data(), v1.size(), v2.data(), v2.size());
    }

}

#endif //CONSOLE_ASSERT_ASSERTS_H
