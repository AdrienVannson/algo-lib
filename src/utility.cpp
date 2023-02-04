#include "utility.hpp"

#include <cassert>

std::vector<int> range(const int n)
{
    assert(n >= 0);

    std::vector<int> res(n);

    for (int i = 0; i < n; i++) {
        res[i] = i;
    }

    return res;
}
