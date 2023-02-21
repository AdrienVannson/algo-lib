#pragma once

#include <cstdlib>
#include <limits>

template<class T>
class Constants
{
public:
    static T zero() = delete;
    static T one() = delete;
    static T infinity() = delete;
};

template<>
class Constants<int>
{
public:
    static int zero()
    {
        return 0;
    }
    static int one()
    {
        return 1;
    }
    static int infinity()
    {
        return std::numeric_limits<int>::max();
    }
};

template<>
class Constants<unsigned int>
{
public:
    static unsigned int zero()
    {
        return 0;
    }
    static unsigned int one()
    {
        return 1;
    }
    static unsigned int infinity()
    {
        return std::numeric_limits<unsigned int>::max();
    }
};

template<>
class Constants<long long>
{
public:
    static long long zero()
    {
        return 0;
    }
    static long long one()
    {
        return 1;
    }
    static long long infinity()
    {
        return std::numeric_limits<long long>::max();
    }
};

template<>
class Constants<unsigned long long>
{
public:
    static unsigned long long zero()
    {
        return 0;
    }
    static unsigned long long one()
    {
        return 1;
    }
    static unsigned long long infinity()
    {
        return std::numeric_limits<unsigned long long>::max();
    }
};

template<>
class Constants<float>
{
public:
    static float zero()
    {
        return 0;
    }
    static float one()
    {
        return 1;
    }
    static float infinity()
    {
        return std::numeric_limits<float>::infinity();
    }
};

template<>
class Constants<double>
{
public:
    static double zero()
    {
        return 0;
    }
    static double one()
    {
        return 1;
    }
    static unsigned long long infinity()
    {
        return std::numeric_limits<unsigned long long>::infinity();
    }
};
