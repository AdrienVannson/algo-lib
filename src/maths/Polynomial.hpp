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
    Polynomial(const std::vector<T> &coefs = {}) : m_coefs(coefs)
    {
        removeLeadingZeros();
    }

    /// \brief Constant polynomial
    Polynomial(const T cst) : Polynomial(std::vector<T> {cst}) {}

    inline int degree() const { return m_coefs.size() - 1; }

    inline T coef(const int i) const
    {
        if (i >= (int)m_coefs.size()) { return Constants<T>::zero(); }
        return m_coefs[i];
    }

    /// \brief Evalute the polynomial
    template<class U>
    U operator()(const U &x) const;

    // Arithmetical operations
    template<class T_>
    friend Polynomial<T_> operator+(const Polynomial<T_> &P, const Polynomial<T_> &Q);

    template<class T_>
    friend Polynomial<T_> operator*(const Polynomial<T_> &P, const Polynomial<T_> &Q);

    template<class T_>
    friend Polynomial<T_> operator*(const T_ lambda, const Polynomial<T_> &P);

    void operator+=(const Polynomial<T> &P);
    void operator*=(const Polynomial<T> &P);

    // Other functions
    template<class T_>
    friend bool operator==(const Polynomial<T_> &P, const Polynomial<T_> &Q);

    template<class T_>
    friend std::ostream &operator<<(std::ostream &os, const Polynomial<T_> &P);

private:
    std::vector<T> m_coefs; // Lower degree first

    void removeLeadingZeros();
};

template<class T>
template<class U>
U Polynomial<T>::operator()(const U &x) const
{
    U s = Constants<U>::zero();
    U p = Constants<U>::one();

    for (const T &coef : m_coefs) {
        s = s + coef * p;
        p = p * x;
    }

    return s;
}

template<class T>
Polynomial<T> operator+(const Polynomial<T> &P, const Polynomial<T> &Q)
{
    std::vector<T> v(std::max(P.m_coefs.size(), Q.m_coefs.size()), Constants<T>::zero());

    for (int i = 0; i < (int)v.size(); i++) {
        if (i < (int)P.m_coefs.size()) { v[i] = v[i] + P.m_coefs[i]; }
        if (i < (int)Q.m_coefs.size()) { v[i] = v[i] + Q.m_coefs[i]; }
    }

    Polynomial<T> S(v);
    return S;
}

template<class T>
Polynomial<T> operator*(const Polynomial<T> &P, const Polynomial<T> &Q)
{
    std::vector<T> v(P.m_coefs.size() + Q.m_coefs.size() - 1, Constants<T>::zero());

    for (int i = 0; i < (int)v.size(); i++) {
        for (int k = 0; k <= i; k++) {
            v[i] = v[i] + P.coef(k) * Q.coef(i - k);
        }
    }

    Polynomial<T> S(v);
    return S;
}

template<class T>
Polynomial<T> operator*(const T lambda, const Polynomial<T> &P)
{
    Polynomial<T> R = P;
    for (T &coef : R.m_coefs) {
        coef = coef * lambda;
    }
    return R;
}

template<class T>
void Polynomial<T>::operator+=(const Polynomial<T> &P)
{
    (*this) = (*this) + P;
}

template<class T>
void Polynomial<T>::operator*=(const Polynomial<T> &P)
{
    (*this) = (*this) * P;
}

template<class T>
bool operator==(const Polynomial<T> &P, const Polynomial<T> &Q)
{
    return P.m_coefs == Q.m_coefs;
}

template<class T>
std::ostream &operator<<(std::ostream &os, const Polynomial<T> &P)
{
    os << "(";

    for (int k = P.degree(); k >= 0; k--) {
        os << P.m_coefs[k] << " X^" << k;

        if (k > 0) { os << " + "; }
    }

    os << ")";
    return os;
}

template<class T>
void Polynomial<T>::removeLeadingZeros()
{
    while (m_coefs.size() && m_coefs.back() == Constants<T>::zero()) {
        m_coefs.pop_back();
    }
}

template<class T>
Polynomial<T> lagrangePolynomial(const std::vector<std::pair<T, T>> &points)
{
    Polynomial<T> P;

    for (int i = 0; i < (int)points.size(); i++) {
        Polynomial<T> Q(Constants<T>::one());
        for (int j = 0; j < (int)points.size(); j++) {
            if (j != i) {
                Q *= Polynomial<T>({-points[j].first, 1}); // (X - x_j)
            }
        }

        P += (points[i].second / Q(points[i].first)) * Q;
    }

    return P;
}

#endif // POLYNOMIAL_HPP
