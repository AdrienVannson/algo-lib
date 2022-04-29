#ifndef LINE_HPP
#define LINE_HPP

#include <cassert>

#include "Vect2.hpp"

/// \brief Line defined by its two extremities: A and B
template<class T>
class Line
{
public:
    Line(const Vect2<T> A, const Vect2<T> B) : m_A(A), m_B(B)
    {
        assert(A != B);
    }

    Vect2<T> A() const
    {
        return m_A;
    }

    void setA(const Vect2<T> A)
    {
        m_A = A;
    }

    Vect2<T> B() const
    {
        return m_B;
    }

    void setB(const Vect2<T> B)
    {
        m_B = B;
    }

private:
    Vect2<T> m_A, m_B;
};

#endif // LINE_HPP
