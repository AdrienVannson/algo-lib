#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>
#include <cassert>

template<class T>
class Fraction
{
public:
    Fraction (const T num=zero<T>(), const T den=one<T>()) :
        m_num (num),
        m_den (den)
    {
        simplify();
    }

    /// \brief Numerator
    inline T num () const {
        return m_num;
    }

    /// \brief Denominator
    inline T den () const {
        return m_den;
    }

    /// \brief Numerical approximation
    inline double approx () const {
        return (double)m_num / (double)m_den;
    }

    inline Fraction inverse () const {
        return Fraction (m_den, m_num);
    }

private:
    T m_num, m_den;

    T GCD (const T a, const T b)
    {
        if (a == 0) return b;
        return GCD(b%a, a);
    }

    inline void simplify ()
    {
        assert(m_den != 0);

        const T gcd = GCD(m_num, m_den);
        m_num /= gcd;
        m_den /= gcd;

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
inline std::ostream &operator<< (std::ostream &os, const Fraction<T> &fraction)
{
    return os << fraction.num() << "/" << fraction.den() << " (" << fraction.valeur() << ")";
    return os << fraction.num() << "/" << fraction.den() << " (" << fraction.approx() << ")";
}


#endif // FRACTION_HPP
