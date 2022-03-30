#ifndef VECT2_HPP
#define VECT2_HPP

#include "constants.hpp"

template<class T>
class Vect2
{
public:
    inline explicit Vect2() :
        x(Constants<T>::zero()),
        y(Constants<T>::zero())
    {}

    inline explicit Vect2(const T x_, const T y_) : x(x_), y(y_) {}

    inline T manhattanNorm() const { return abs(x) + abs(y); }

    inline double norm() const { return sqrt(x * x + y * y); }

    inline void normalize()
    {
        const double currentNorm = norm();

        x /= currentNorm;
        y /= currentNorm;
    }

    inline Vect2<T> operator-() const { return Vect2<T>(-x, -y); };

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

#endif // VECT2_HPP
