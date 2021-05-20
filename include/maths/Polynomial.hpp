#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include <ostream>
#include <vector>

#include "constants.hpp"

template<class T>
class Polynomial
{
public:
    /// \brief The coefficients must be given lower degree first
    Polynomial (const std::vector<T> &coefs = {}) :
        m_coefs(coefs)
    {
        removeLeadingZeros();
    }

    inline int degree () const
    {
        return m_coefs.size() - 1;
    }

    inline T coef (const int i) const
    {
        return m_coefs[i];
    }

    /// \brief Evalute the polynomial
    template<class U>
    U operator() (const U &x) const;

    // Arithmetical operations
    template<class T_>
    friend Polynomial<T_> operator+ (const Polynomial<T_> &P, const Polynomial<T_> &Q);

    template<class T_>
    friend Polynomial<T_> operator* (const Polynomial<T_> &P, const Polynomial<T_> &Q);

    // Other functions
    template<class T_>
    friend bool operator== (const Polynomial<T_> &P, const Polynomial<T_> &Q);

    template<class T_>
    friend std::ostream &operator<< (std::ostream &os, const Polynomial<T_> &P);

private:
    std::vector<T> m_coefs; // Lower degree first

    void removeLeadingZeros ();
};

template<class T>
template<class U>
U Polynomial<T>::operator() (const U &x) const
{
    U s = zero<U>();
    U p = one<U>();

    for (const T &coef : m_coefs) {
        s += coef * p;
        p *= x;
    }

    return s;
}

template<class T>
Polynomial<T> operator+ (const Polynomial<T> &P, const Polynomial<T> &Q)
{
    std::vector<T> v(std::max(P.m_coefs.size(), Q.m_coefs.size()), zero<T>());

    for (int i=0; i<(int)v.size(); i++) {
        if (i < (int)P.m_coefs.size()) {
            v[i] += P.m_coefs[i];
        }
        if (i < (int)Q.m_coefs.size()) {
            v[i] += Q.m_coefs[i];
        }
    }

    Polynomial<T> S(v);
    return S;
}

template<class T>
Polynomial<T> operator* (const Polynomial<T> &P, const Polynomial<T> &Q)
{
    std::vector<T> v(P.m_coefs.size() + Q.m_coefs.size() - 1, zero<T>());

    for (int i=0; i<(int)v.size(); i++) {
        for (int k=0; k<=i; k++) {
            v[i] += P.m_coefs[k] * Q.m_coefs[i-k];
        }
    }

    Polynomial<T> S(v);
    return S;
}

template<class T>
bool operator== (const Polynomial<T> &P, const Polynomial<T> &Q)
{
    return P.m_coefs == Q.m_coefs;
}

template<class T>
std::ostream &operator<< (std::ostream &os, const Polynomial<T> &P)
{
    os << "(";

    for (int k=P.degree(); k>=0; k--) {
        os << P.m_coefs[k] << " X^" << k;

        if (k > 0) {
            os << " + ";
        }
    }

    os << ")";
    return os;
}

template<class T>
void Polynomial<T>::removeLeadingZeros ()
{
    while (m_coefs.size() && m_coefs.back() == 0) {
        m_coefs.pop_back();
    }
}

#endif // POLYNOMIAL_HPP
