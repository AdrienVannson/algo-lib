#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <vector>

template<class T>
std::vector<T> mergeSort(const std::vector<T> &v)
{
    if (v.size() <= 1) { return v; }

    std::vector<T> v1, v2;
    for (const T &a : v) {
        if (v1.size() < v.size() / 2) {
            v1.push_back(a);
        } else {
            v2.push_back(a);
        }
    }

    const std::vector<T> sorted1 = mergeSort(v1);
    const std::vector<T> sorted2 = mergeSort(v2);

    std::vector<T> sorted;

    int i1 = 0, i2 = 0;

    while (i1 != (int)sorted1.size() || i2 != (int)sorted2.size()) {
        if (i2 == (int)sorted2.size()
            || (i1 != (int)sorted1.size() && sorted1[i1] < sorted2[i2])) {
            sorted.push_back(sorted1[i1]);
            i1++;
        } else {
            sorted.push_back(sorted2[i2]);
            i2++;
        }
    }

    return sorted;
}

#endif // MERGESORT_HPP
