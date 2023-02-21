#pragma once

#include <functional>
#include <vector>

#include "constants.hpp"

/// Returns the vector [0, 1, 2, ..., n-1]
std::vector<int> range(const int n);

/// Returns a vector [begin, begin + incr, begin + 2*incr, ... ]. The array ends
/// at end (excluded).
template<class T>
std::vector<T> range(const T begin, const T end, const T incr = Constants<T>::one())
{
    assert(incr != Constants<T>::zero());

    std::vector<T> res;

    if (incr > Constants<T>::zero()) {
        for (T val = begin; val < end; val += incr) {
            res.push_back(val);
        }
    } else {
        for (T val = begin; val > end; val += incr) {
            res.push_back(val);
        }
    }

    return res;
}

/// Returns the sum of the elements of a vector
template<class T>
T sum(const std::vector<T> &vect)
{
    T sum = Constants<T>::zero();

    for (const T x : vect) {
        sum += x;
    }

    return sum;
}

/// Applies a function on all the elements of a vector, and returns the obtained
/// vector.
///
/// A lambda can be passed:
///   apply_fct<int, long long>(range(7), [](int x) { return (long long)x * x; })
template<class T, class U, typename F>
std::vector<U> apply_fct(const std::vector<T> &vect, F f)
{
    std::vector<U> res;
    res.reserve(vect.size());

    for (const T x : vect) {
        res.push_back(f(x));
    }

    return res;
}
