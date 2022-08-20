// Element of Z/nZ
// The modulo is stored in a static variable: setMod must be
// called before using the class.

#ifndef MODULO_HPP
#define MODULO_HPP

#include "constants.hpp"
#include "gcd-lcm.hpp"

#include <cassert>
#include <iostream>

template<class T>
class Modulo
{
public:
    Modulo(const T val = T()) : m_val(val)
    {
        m_val %= s_mod;
        if (m_val < Constants<T>::zero()) m_val += s_mod;
    }

    inline T val() const
    {
        return m_val;
    }

    inline operator T() const
    {
        return m_val;
    }

    inline static T mod()
    {
        return s_mod;
    }

    inline static void setMod(const int mod)
    {
        s_mod = mod;
    }

    inline Modulo<T> inverse() const
    {
        assert(m_val != Constants<T>::zero());

        return Modulo<T>(getGCDBezout(m_val, s_mod)[1]);
    }

    inline void operator+=(const Modulo<T> x)
    {
        m_val += x.val();
        if (m_val >= s_mod) m_val -= s_mod;
    }

    inline void operator-=(const Modulo<T> x)
    {
        m_val -= x.val();
        if (m_val < Constants<T>::zero()) m_val += s_mod;
    }

private:
    T m_val;
    static T s_mod;
};

template<class T>
T Modulo<T>::s_mod = 1;

template<class T>
inline Modulo<T> operator+(const Modulo<T> a, const Modulo<T> b)
{
    return Modulo<T>((T)a + (T)b);
}

template<class T>
inline Modulo<T> operator-(const Modulo<T> a, const Modulo<T> b)
{
    return Modulo<T>((T)a - (T)b);
}

template<class T>
inline Modulo<T> operator*(const Modulo<T> a, const Modulo<T> b)
{
    return Modulo<T>((T)a * (T)b);
}

template<class T>
inline Modulo<T> operator/(const Modulo<T> a, const Modulo<T> b)
{
    return a * b.inverse();
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const Modulo<T> x)
{
    return os << x.val();
}

template<class T>
class Constants<Modulo<T>>
{
public:
    static int zero()
    {
        return Modulo<T>(Constants<T>::zero());
    }
    static int one()
    {
        return Modulo<T>(Constants<T>::one());
    }
};

#endif // MODULO_HPP
