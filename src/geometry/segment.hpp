#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include <cassert>

#include "Vect2.hpp"
#include "constants.hpp"
#include "line.hpp"

/// \brief Segment defined by its two extremities: A and B
template<class T>
class Segment
{
public:
    Segment(const Vect2<T> A, const Vect2<T> B) : m_A(A), m_B(B)
    {
        // assert(A != B);
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

    Line<T> toLine() const
    {
        return Line<T>(m_A, m_B);
    }

    /// \brief Check if a point belongs to the segment
    bool containsPoint(const Vect2<T> M) const
    {
        // TODO: check if M is on the line

        return (m_B - m_A) * (M - m_A) >= Constants<T>::zero()
            && (m_A - m_B) * (M - m_B) >= Constants<T>::zero();
    }

    template<class U>
    operator Segment<U>() const
    {
        return Segment<U>(m_A, m_B);
    }

private:
    Vect2<T> m_A, m_B;
};

#endif // SEGMENT_HPP