#pragma once

#include <cassert>

#include "line.hpp"
#include "segment.hpp"
#include "vect2.hpp"

struct Empty {};

template<class T>
union ShapeContent {
    ShapeContent() {}
    ShapeContent(Vect2<T> M) : point(M) {}
    ShapeContent(Line<T> L) : line(L) {}
    ShapeContent(Segment<T> S) : seg(S) {}

    Empty empty;
    Vect2<T> point;
    Line<T> line;
    Segment<T> seg;
};

/// \brief Safely contains any kind of shape
template<class T>
class Shape
{
public:
    enum ShapeType
    {
        EMPTY,
        POINT,
        LINE,
        SEGMENT
    };

    Shape() : m_type(EMPTY), m_content() {}

    Shape(const Vect2<T> point) : m_type(POINT), m_content(point) {}

    Shape(const Line<T> line) : m_type(LINE), m_content(line) {}

    Shape(const Segment<T> seg) : m_type(SEGMENT), m_content(seg) {}

    /// \brief Returns the type of the shape
    ShapeType type() const
    {
        return m_type;
    }

    Vect2<T> point() const
    {
        assert(m_type == POINT);
        return m_content.point;
    }

    Line<T> line() const
    {
        assert(m_type == LINE);
        return m_content.line;
    }

    Segment<T> segment() const
    {
        assert(m_type == SEGMENT);
        return m_content.seg;
    }

private:
    ShapeType m_type;
    ShapeContent<T> m_content;
};
