#pragma once

#include <array>
#include <iostream>
#include <vector>

// Default
template<class T>
inline void read(T& t, std::istream& stream = std::cin)
{
    stream >> t;
}

// Pair
template<class U, class V>
inline void read(std::pair<U, V>& pair, std::istream& stream = std::cin)
{
    read(pair.first, stream);
    read(pair.second, stream);
}

// Vector of unknown size
template<class T>
inline void read(std::vector<T>& vec, std::istream& stream = std::cin)
{
    int size;
    stream >> size;

    for (int i = 0; i < size; i++) {
        T x;
        read(x, stream);
        vec.push_back(x);
    }
}

// Vector of given size
template<class T>
inline void read(std::vector<T>& vec, const int size, std::istream& stream = std::cin)
{
    for (int i = 0; i < size; i++) {
        T x;
        read(x, stream);
        vec.push_back(x);
    }
}

// Array
template<class T, int n>
inline void read(std::array<T, n>& array, std::istream& stream = std::cin)
{
    for (int i = 0; i < n; i++) {
        read(array[i], stream);
    }
}
