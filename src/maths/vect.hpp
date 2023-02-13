#ifndef VECT_HPP
#define VECT_HPP

#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"

template<class T>
class Vect
{
public:
    /// Creates a vector filled with the given coefficients
    Vect(std::vector<T> coefs) :
        m_coefs(coefs)
    {}

    /// Creates a vector filled with 0s
    Vect(const int size)
    {
        m_coefs.resize(size, Constants<T>::zero());
    }

    /// Creates an empty vector
    Vect() : Vect(0) {}

    /// Returns the size of the vector
    inline int size() const
    {
        return m_coefs.size();
    }

    /// Returns the i-th coefficient of the vector
    inline T operator()(const int i) const
    {
        return m_coefs[i];
    }

    /// Updates the i-th coefficient of the vector
    inline void set(const int i, const T v)
    {
        m_coefs[i] = v;
    }

    /// \brief Returns the norm of the vector, squared
    inline T squared_norm() const
    {
        T norm = Constants<T>::zero();

        for (const T coef : m_coefs) {
            norm += coef * coef;
        }

        return norm;
    }

    /// \brief Returns the norm of the vector
    inline T norm() const
    {
        return sqrt(squared_norm());
    }

    void operator+=(const Vect &other);
    void operator-=(const Vect &other);

private:
    std::vector<T> m_coefs;
};

template<class T>
void Vect<T>::operator+=(const Vect &other)
{
    assert(size() == other.size());

    for (int i = 0; i < size(); i++) {
        m_coefs[i] += other.m_coefs[i];
    }
}

template<class T>
void Vect<T>::operator-=(const Vect &other)
{
    assert(size() == other.size());

    for (int i = 0; i < size(); i++) {
        m_coefs[i] -= other.m_coefs[i];
    }
}

template<class T>
Vect<T> operator+(const Vect<T> &u, const Vect<T> &v)
{
    assert(u.size() == v.size());

    Vect<T> s(u.size());

    for (int i = 0; i < s.size(); i++) {
        s.set(i, u(i) + v(i));
    }

    return s;
}

template<class T>
Vect<T> operator-(const Vect<T> &u, const Vect<T> &v)
{
    assert(u.size() == v.size());

    Vect<T> s(u.size());

    for (int i = 0; i < s.size(); i++) {
        s.set(i, u(i) - v(i));
    }

    return s;
}

template<class T, class U>
Vect<T> operator*(const U lambda, const Vect<T> &u)
{
    Vect<T> r(u.size());

    for (int i = 0; i < u.size(); i++) {
        r.set(i, lambda * u(i));
    }

    return r;
}

template<class T>
bool operator==(const Vect<T> &u, const Vect<T> &v)
{
    assert(u.size() == v.size());

    for (int i = 0; i < u.size(); i++) {
        if (u(i) != v(i)) {
            return false;
        }
    }

    return true;
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const Vect<T> &u)
{
    for (int i = 0; i < u.size(); i++) {
        os << u(i);
        if (i != u.size() - 1) {
            os << " ";
        }
    }
    os << "\n";

    return os;
}

#endif // VECT_HPP
