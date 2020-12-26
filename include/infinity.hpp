#ifndef INFINITY_HPP
#define INFINITY_HPP

#include <cstdlib>
#include <limits>

template<class T>
T infinity () = delete;

template<>
int infinity ()
{
    return std::numeric_limits<int>::max();
}

template<>
unsigned int infinity ()
{
    return std::numeric_limits<unsigned int>::max();
}

template<>
long long infinity ()
{
    return std::numeric_limits<long long>::max();
}

template<>
unsigned long long infinity ()
{
    return std::numeric_limits<unsigned long long>::max();
}

template<>
float infinity ()
{
    return std::numeric_limits<float>::infinity();
}

template<>
double infinity ()
{
    return std::numeric_limits<double>::infinity();
}

#endif // INFINITY_HPP
