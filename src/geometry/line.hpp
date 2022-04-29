#ifndef LINE_HPP
#define LINE_HPP

#include <cassert>

#include "Vect2.hpp"

/// \brief Line defined by its cartesian equation ax + by + x = 0
template<class T>
class Line
{
public:
    Line(const T a, const T b, const T c) : m_a(a), m_b(b), m_c(c) {}

    Line(const Vect2<T> A, const Vect2<T> B) :
        m_a(B.y - A.y), m_b(A.x - B.x), m_c(A.y * B.x - A.x * B.y)
    {
        assert(A != B);
    }

    /// \brief Check if a point belongs to the line
    bool containsPoint(const Vect2<T> M) const
    {
        return m_a * M.x + m_b * M.y + m_c == Constants<T>::zero();
    }

    inline T a() const
    {
        return m_a;
    }

    inline T b() const
    {
        return m_b;
    }

    inline T c() const
    {
        return m_c;
    }

private:
    T m_a, m_b, m_c;
};

#endif // LINE_HPP
