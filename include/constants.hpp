#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <cstdlib>
#include <limits>

// Infinity
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


// Zero
template<class T>
T zero () = delete;

template<>
int zero ()
{
    return 0;
}

template<>
unsigned int zero ()
{
    return 0;
}

template<>
long long zero ()
{
    return 0;
}

template<>
unsigned long long zero ()
{
    return 0;
}

template<>
float zero ()
{
    return 0;
}

template<>
double zero ()
{
    return 0;
}


// One
template<class T>
T one () = delete;

template<>
int one ()
{
    return 1;
}

template<>
unsigned int one ()
{
    return 1;
}

template<>
long long one ()
{
    return 1;
}

template<>
unsigned long long one ()
{
    return 1;
}

template<>
float one ()
{
    return 1;
}

template<>
double one ()
{
    return 1;
}


#endif // CONSTANTS_HPP
