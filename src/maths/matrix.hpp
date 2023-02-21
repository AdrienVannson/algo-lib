#pragma once

#include <iostream>
#include <vector>

#include "constants.hpp"

template<class T>
class Matrix
{
public:
    /// Creates a matrix filled with the given coefficients
    Matrix(std::vector<std::vector<T>> coefs) :
        m_coefs(coefs)
    {
        for (const auto &line : coefs) {
            assert(line.size() == coefs[0].size());
        }
    }

    /// Creates a matrix filled with 0s
    Matrix(const int lines_count, const int columns_count)
    {
        m_coefs.resize(lines_count, std::vector<T>(columns_count, T()));
    }

    /// Creates an empty matrix
    Matrix() : Matrix(0, 0) {}

    /// Creates a square matrix of size n filled with 0s
    Matrix(const int n) : Matrix(n, n) {}

    /// Returns the identity matrix of size n
    static Matrix<T> identity(const int n);

    /// Returns the number of lines of the matrix
    inline int lines_count() const
    {
        return m_coefs.size();
    }

    /// Returns the number of colmuns of the matrix
    inline int columns_count() const
    {
        if (m_coefs.empty()) return 0;
        return m_coefs.front().size();
    }

    /// Returns the coefficient (i, j) of the matrix
    inline T operator()(const int i, const int j) const
    {
        return m_coefs[i][j];
    }

    /// Updates the coefficient (i, j) of the matrix
    inline void set(const int i, const int j, const T v)
    {
        m_coefs[i][j] = v;
    }

private:
    std::vector<std::vector<T>> m_coefs;
};

template<class T>
Matrix<T> Matrix<T>::identity(const int n)
{
    Matrix<T> M(n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M.set(i, j, i == j ? Constants<T>::one() : Constants<T>::zero());
        }
    }

    return M;
}

template<class T>
Matrix<T> operator+(const Matrix<T> &A, const Matrix<T> &B)
{
    assert(A.lines_count() == B.lines_count());
    assert(A.columns_count() == B.columns_count());

    Matrix<T> S(A.lines_count(), A.columns_count());

    for (int i = 0; i < S.lines_count(); i++) {
        for (int j = 0; j < S.columns_count(); j++) {
            S.set(i, j, A(i, j) + B(i, j));
        }
    }

    return S;
}

template<class T>
Matrix<T> operator*(const Matrix<T> &A, const Matrix<T> &B)
{
    assert(A.columns_count() == B.lines_count());

    Matrix<T> P(A.lines_count(), B.columns_count());

    for (int i = 0; i < P.lines_count(); i++) {
        for (int j = 0; j < P.columns_count(); j++) {
            T c = Constants<T>::zero();
            for (int k = 0; k < A.columns_count(); k++) {
                c += A(i, k) * B(k, j);
            }
            P.set(i, j, c);
        }
    }

    return P;
}

template<class T, class U>
Matrix<T> operator*(const U lambda, const Matrix<T> &M)
{
    Matrix<T> R(M.lines_count(), M.columns_count());

    for (int i = 0; i < M.lines_count(); i++) {
        for (int j = 0; j < M.columns_count(); j++) {
            R.set(i, j, lambda * M(i, j));
        }
    }

    return R;
}

template<class T>
bool operator==(const Matrix<T> &A, const Matrix<T> &B)
{
    assert(A.lines_count() == B.lines_count());
    assert(A.columns_count() == B.columns_count());

    for (int i = 0; i < A.lines_count(); i++) {
        for (int j = 0; j < A.columns_count(); j++) {
            if (A(i, j) != B(i, j)) {
                return false;
            }
        }
    }

    return true;
}

template<class T>
inline std::ostream &operator<<(std::ostream &os, const Matrix<T> &M)
{
    for (int i = 0; i < M.lines_count(); i++) {
        for (int j = 0; j < M.columns_count(); j++) {
            os << M(i, j);
            if (j != M.columns_count() - 1) {
                os << " ";
            }
        }
        os << "\n";
    }

    return os;
}
