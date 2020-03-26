#ifndef VECT_HPP
#define VECT_HPP

#include "global.hpp"


template<class T>
class Vect
{
public:
    inline explicit Vect (const T x_=0, const T y_=0) :
        x (x_),
        y (y_)
    {}

    inline double norm () const
    {
        return sqrt(x*x + y*y);
    }

    inline void normalize ()
    {
        const double currentNorm = norm();

        x /= currentNorm;
        y /= currentNorm;
    }

    inline Vect<T> operator- () const { return Vect<T> (-x, -y); };

    inline void operator*= (const T k) { x *= k; y *= k; }
    inline void operator/= (const T k) { x /= k; y /= k; }
    inline void operator+= (const Vect<T> &v) { x += v.x; y += v.y; }
    inline void operator-= (const Vect<T> &v) { x -= v.x; y -= v.y; }

    T x, y;
};

template<class T>
inline Vect<T> operator+ (const Vect<T> &a, const Vect<T> &b)
{
    return Vect<T>(a.x+b.x, a.y+b.y);
}

template<class T>
inline Vect<T> operator- (const Vect<T> &a, const Vect<T> &b)
{
    return Vect<T>(a.x-b.x, a.y-b.y);
}

template<class T>
inline T operator* (const Vect<T> &a, const Vect<T> &b) // Dot product
{
    return a.x*b.x + a.y*b.y;
}

template<class T>
inline T operator^ (const Vect<T> &a, const Vect<T> &b) // Cross product on z
{
    return a.x * b.y - b.x * a.y;
}

template<class T>
inline Vect<T> operator* (const T k, const Vect<T> &v)
{
    return Vect<T>(k*v.x, k*v.y);
}

template<class T>
inline Vect<T> operator* (const Vect<T> &v, const T k)
{
    return Vect<T>(k*v.x, k*v.y);
}

template<class T>
inline double getDist (const Vect<T> &a, const Vect<T> &b)
{
    return (a-b).norm();
}


#endif // VECT_HPP
