#ifndef FRACTION_HPP
#define FRACTION_HPP

#include "global.hpp"

template<class T>
class Fraction
{
public:
    Fraction (const T num=0, const T den=1) :
        m_num (num),
        m_den (den)
    {
        simplifier();
    }

    /// \brief Numérateur
    inline T num () const {
        return m_num;
    }

    /// \brief Dénominateur
    inline T den () const {
        return m_den;
    }

    /// \brief Valeur numérique approchée
    inline double valeur () const {
        return (double)m_num / (double)m_den;
    }

    inline Fraction inverse () const {
        return Fraction (m_den, m_num);
    }

private:
    T m_num, m_den;

    T PGCD (const T a, const T b)
    {
        if (a == 0) return b;
        return PGCD(b%a, a);
    }

    inline void simplifier ()
    {
        assert(m_den != 0);

        const T pgcd = PGCD(m_num, m_den);
        m_num /= pgcd;
        m_den /= pgcd;

        if (m_den < 0) {
            m_num *= -1;
            m_den *= -1;
        }
    }
};

template<class T>
inline Fraction<T> operator+ (const Fraction<T> &a, const Fraction<T> &b)
{
    return Fraction<T> (a.num()*b.den() + b.num()*a.den(), a.den() * b.den());
}

template<class T>
inline Fraction<T> operator- (const Fraction<T> &a, const Fraction<T> &b)
{
    return Fraction<T> (a.num()*b.den() - b.num()*a.den(), a.den() * b.den());
}

template<class T>
inline Fraction<T> operator* (const Fraction<T> &a, const Fraction<T> &b)
{
    return Fraction<T> (a.num() * b.num(), a.den() * b.den());
}

template<class T>
inline Fraction<T> operator/ (const Fraction<T> &a, const Fraction<T> &b)
{
    return a * b.inverse();
}

template<class T>
inline Fraction<T> operator- (const Fraction<T> &f)
{
    return Fraction<T> (-f.num(), f.den());
}

template<class T>
inline bool operator== (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() == b.num() && a.den() == b.den();
}

template<class T>
inline bool operator!= (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() != b.num() || a.den() != b.den();
}

template<class T>
inline bool operator< (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() * b.den() < b.num() * a.den();
}

template<class T>
inline bool operator<= (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() * b.den() <= b.num() * a.den();
}

template<class T>
inline bool operator> (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() * b.den() > b.num() * a.den();
}

template<class T>
inline bool operator>= (const Fraction<T> &a, const Fraction<T> &b)
{
    return a.num() * b.den() >= b.num() * a.den();
}

template<class T>
inline ostream &operator<< (ostream &os, const Fraction<T> &fraction)
{
    return os << fraction.num() << "/" << fraction.den() << " (" << fraction.valeur() << ")";
}


#endif // FRACTION_HPP
