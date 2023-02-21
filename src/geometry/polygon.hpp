#pragma once

#include <vector>

#include "constants.hpp"
#include "intersections.hpp"
#include "segment.hpp"
#include "vect2.hpp"

/// \brief A polygon represented by a list of its vertices
template<class T>
class Polygon
{
public:
    Polygon() {}

    Polygon(const std::vector<Vect2<T>> &vertices) : m_vertices(vertices) {}

    /// \brief Returns the number of vertices in the polygon
    inline int vertexCount() const
    {
        return m_vertices.size();
    }

    /// \brief Returns the i-th vertex of the polygon
    Vect2<T> vertex(const int i) const
    {
        return m_vertices[i];
    }

    const std::vector<Vect2<T>> &vertices() const
    {
        return m_vertices;
    }

    /// \brief Adds a vertex at the end of the list
    inline void addVertex(const Vect2<T> vertex)
    {
        m_vertices.push_back(vertex);
    }

    /// \brief Tests if a point is on the boundary of the polygon
    bool isOnBoundary(const Vect2<T>) const;

    /// \brief Tests if a point is inside the polyon
    bool isInside(const Vect2<T>) const;

    /// \brief Tests if a point is strictly inside the polyon
    bool isStrictlyInside(const Vect2<T>) const;

private:
    /// \brief Tests if a point outside the boundary is inside the polygon
    bool isInsideNotBoundary(const Vect2<T>) const;

    std::vector<Vect2<T>> m_vertices;
};

template<class T>
bool Polygon<T>::isOnBoundary(const Vect2<T> M) const
{
    for (int i = 0; i < (int)m_vertices.size(); i++) {
        const int j = i == (int)m_vertices.size() - 1 ? 0 : i + 1;

        if ((m_vertices[i] - m_vertices[j]).manhattanNorm()
            == Constants<T>::zero()) {
            continue;
        }

        Segment<T> seg(m_vertices[i], m_vertices[j]);

        if (seg.containsPoint(M)) {
            return true;
        }
    }

    return false;
}

template<class T>
bool Polygon<T>::isInside(const Vect2<T> M) const
{
    if (isOnBoundary(M)) {
        return true;
    }
    return isInsideNotBoundary(M);
}

template<class T>
bool Polygon<T>::isStrictlyInside(const Vect2<T> M) const
{
    if (isOnBoundary(M)) {
        return false;
    }
    return isInsideNotBoundary(M);
}

template<class T>
bool Polygon<T>::isInsideNotBoundary(const Vect2<T> M) const
{
    // MN shouldn't intersect any vertex of the polygon (works if the
    // coordinates are integers)
    T xMax = 0;
    for (auto P : m_vertices) {
        xMax = max(abs(P.x - M.x) + Constants<T>::one(), xMax);
    }

    Vect2<T> N = M + Vect2<T>(xMax, 1);

    // Check if the ray intersects with an even or an odd number of edges
    int intersectionCount = 0;

    for (int i = 0; i < (int)m_vertices.size(); i++) {
        const int j = i == (int)m_vertices.size() - 1 ? 0 : i + 1;

        if ((m_vertices[i] - m_vertices[j]).manhattanNorm()
            == Constants<T>::zero()) {
            continue;
        }

        const Segment<T> seg(m_vertices[i], m_vertices[j]);
        const Shape<T> inter = getIntersection(Line<T>(M, N), seg);

        if (inter.type() == Shape<T>::POINT) {
            if ((N - M) * (inter.point() - M) >= Constants<T>::zero()) {
                intersectionCount++;
            }
        }
    }

    return intersectionCount % 2;
}
