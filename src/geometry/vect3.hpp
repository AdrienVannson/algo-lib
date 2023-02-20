#ifndef VECT3_HPP
#define VECT3_HPP

#include "constants.hpp"

template<class T>
class Vect3
{
public:
    inline explicit Vect3() :
        x(Constants<T>::zero()), y(Constants<T>::zero()),
        z(Constants<T>::zero())
    {}

    inline explicit Vect3(const T x_, const T y_, const T z_) :
        x(x_), y(y_), z(z_)
    {}

    inline bool isNull() const
    {
        return x == Constants<T>::zero() && y == Constants<T>::zero()
            && z == Constants<T>::zero();
    }

    inline T manhattanNorm() const
    {
        return abs(x) + abs(y) + abs(z);
    }

    /// \brief Returns the norm of the vector, squared
    inline T squared_norm() const
    {
        return x * x + y * y + z * z;
    }

    inline double norm() const
    {
        return sqrt(squared_norm());
    }

    inline void normalize()
    {
        const double currentNorm = norm();

        x /= currentNorm;
        y /= currentNorm;
        z /= currentNorm;
    }

    template<class U>
    operator Vect3<U>() const
    {
        return Vect3<U>(x, y, z);
    }

    inline Vect3<T> operator-() const
    {
        return Vect3<T>(-x, -y, -z);
    }

    inline void operator*=(const T k)
    {
        x *= k;
        y *= k;
        z *= k;
    }

    inline void operator/=(const T k)
    {
        x /= k;
        y /= k;
        z /= k;
    }

    inline void operator+=(const Vect3<T> &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    inline void operator-=(const Vect3<T> &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    static inline double dist(const Vect3<T> &a, const Vect3<T> &b)
    {
        return (a - b).norm();
    }

    T x, y, z;
};

template<class T>
inline Vect3<T> operator+(const Vect3<T> &a, const Vect3<T> &b)
{
    return Vect3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<class T>
inline Vect3<T> operator-(const Vect3<T> &a, const Vect3<T> &b)
{
    return Vect3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<class T>
inline T operator*(const Vect3<T> &a, const Vect3<T> &b) // Dot product
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<class T>
inline Vect3<T>
operator^(const Vect3<T> &a, const Vect3<T> &b) // Cross product on z
{
    return Vect3<T>(
        a.y * b.z - b.y * a.z,
        a.z * b.x - b.z * a.x,
        a.x * b.y - b.x * a.y
    );
}

template<class T>
inline Vect3<T> operator*(const T k, const Vect3<T> &v)
{
    return Vect3<T>(k * v.x, k * v.y, k * v.z);
}

template<class T>
inline Vect3<T> operator*(const Vect3<T> &v, const T k)
{
    return Vect3<T>(k * v.x, k * v.y, k * v.z);
}

template<class T>
inline bool operator==(const Vect3<T> &u, const Vect3<T> &v)
{
    return u.x == v.x && u.y == v.y && u.z == v.z;
}

template<class T>
inline bool operator!=(const Vect3<T> &u, const Vect3<T> &v)
{
    return u.x != v.x || u.y != v.y || u.z != v.z;
}

template<class T>
inline bool operator<(const Vect3<T> &u, const Vect3<T> &v)
{
    if (u.x != v.x) return u.x < v.x;
    if (u.y != v.y) return u.y < v.y;
    return u.z < v.z;
}

#endif // VECT3_HPP
