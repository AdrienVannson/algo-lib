#pragma once

#include <cmath>
#include <iostream>

#include "constants.hpp"

template<class T>
class Vect2
{
public:
    inline explicit Vect2() : x(Constants<T>::zero()), y(Constants<T>::zero())
    {}

    inline explicit Vect2(const T x_, const T y_) : x(x_), y(y_) {}

    inline bool isNull() const
    {
        return x == Constants<T>::zero() && y == Constants<T>::zero();
    }

    inline T manhattanNorm() const
    {
        return abs(x) + abs(y);
    }

    /// \brief Returns the norm of the vector, squared
    inline T squared_norm() const
    {
        return x * x + y * y;
    }

    inline double norm() const
    {
        return sqrt(x * x + y * y);
    }

    inline void normalize()
    {
        const double currentNorm = norm();

        x /= currentNorm;
        y /= currentNorm;
    }

    template<class U>
    operator Vect2<U>() const
    {
        return Vect2<U>(x, y);
    }

    inline Vect2<T> operator-() const
    {
        return Vect2<T>(-x, -y);
    }

    inline void operator*=(const T k)
    {
        x *= k;
        y *= k;
    }

    inline void operator/=(const T k)
    {
        x /= k;
        y /= k;
    }

    inline void operator+=(const Vect2<T> &v)
    {
        x += v.x;
        y += v.y;
    }

    inline void operator-=(const Vect2<T> &v)
    {
        x -= v.x;
        y -= v.y;
    }

    static inline double dist(const Vect2<T> &a, const Vect2<T> &b)
    {
        return (a - b).norm();
    }

    T x, y;
};

template<class T>
inline Vect2<T> operator+(const Vect2<T> &a, const Vect2<T> &b)
{
    return Vect2<T>(a.x + b.x, a.y + b.y);
}

template<class T>
inline Vect2<T> operator-(const Vect2<T> &a, const Vect2<T> &b)
{
    return Vect2<T>(a.x - b.x, a.y - b.y);
}

template<class T>
inline T operator*(const Vect2<T> &a, const Vect2<T> &b) // Dot product
{
    return a.x * b.x + a.y * b.y;
}

template<class T>
inline T operator^(const Vect2<T> &a, const Vect2<T> &b) // Cross product on z
{
    return a.x * b.y - b.x * a.y;
}

template<class T>
inline Vect2<T> operator*(const T k, const Vect2<T> &v)
{
    return Vect2<T>(k * v.x, k * v.y);
}

template<class T>
inline Vect2<T> operator*(const Vect2<T> &v, const T k)
{
    return Vect2<T>(k * v.x, k * v.y);
}

template<class T>
inline bool operator==(const Vect2<T> &u, const Vect2<T> &v)
{
    return u.x == v.x && u.y == v.y;
}

template<class T>
inline bool operator!=(const Vect2<T> &u, const Vect2<T> &v)
{
    return u.x != v.x || u.y != v.y;
}

template<class T>
inline bool operator<(const Vect2<T> &u, const Vect2<T> &v)
{
    if (u.x != v.x) return u.x < v.x;
    return u.y < v.y;
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const Vect2<T> &v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

using Vect2f = Vect2<float>;
using Vect2d = Vect2<double>;