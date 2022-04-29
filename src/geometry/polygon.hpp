#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include "Vect2.hpp"
#include "constants.hpp"
#include "intersections.hpp"
#include "segment.hpp"

/// \brief A polygon represented by a list of its vertices
template<class T>
class Polygon
{
public:
    Polygon() {}

    Polygon(std::vector<Vect2<T>> &vertices) : m_vertices(vertices) {}

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

    std::vector<Vect2<T>> const &vertices() const
    {
        return m_vertices;
    }

    /// \brief Adds a vertex at the end of the list
    void addVertex(const Vect2<T> vertex)
    {
        m_vertices.push_back(vertex);
    }

    /// \brief Tests if a vertex is inside the polyon
    bool isInside(const Vect2<T>) const;

    /// \brief Tests if a vertex is strictly inside the polyon
    bool isStrictlyInside(const Vect2<T>) const;

private:
    std::vector<Vect2<T>> m_vertices;
};

template<class T>
bool Polygon<T>::isInside(const Vect2<T> M) const
{
    /*// MN shouldn't intersect any vertex of the polygon
    T xMax = 0;
    for (auto P : m_vertices) {
        xMax = max(abs(P.x - M.x) + Constants<T>::one(), xMax);
    }

    Vect2<T> N = M + Vect2<T>(xMax, 1);

    // Check if the ray intersects with an even or an odd number of edges
    int intersectionCount = 0;

    for (int i = 0; i < (int)m_vertices.size(); i++) {
        const int j = (i + 1) % m_vertices.size();
        Segment<T> seg(m_vertices[i], m_vertices[j]);
        if ((seg.A() - seg.B()).norm2() == Constants<T>::zero()) continue;

        Intersection<T> inter = getIntersection(Line<T>(M, N), seg);

        if (inter.type == Intersection<T>::POINT) {
            // Check if M is on the border
            if (inter.point == M) {
                return true;
            }

            if ((N - M) * (inter.point - M) >= Constants<T>::zero()) {
                intersectionCount++;
            }
        }
    }

    return intersectionCount % 2;*/

    // MN shouldn't intersect any vertex of the polygon
    T xMax = 0;
    for (auto P : m_vertices) {
        xMax = max(abs(P.x - M.x) + Constants<T>::one(), xMax);
    }

    Vect2<T> N = M + Vect2<T>(xMax, 1);

    // Check if the ray intersects with an even or an odd number of edges
    int intersectionCount = 0;

    for (int i = 0; i < (int)m_vertices.size(); i++) {
        const int j = (i + 1) % m_vertices.size();
        Segment<T> seg(m_vertices[i], m_vertices[j]);
        if ((seg.A() - seg.B()).norm2() == Constants<T>::zero()) continue;

        Shape<T> inter = getIntersection(Line<T>(M, N), seg);

        if (inter.type() == Shape<T>::POINT) {
            // Check if M is on the border
            if (inter.point() == M) {
                return true;
            }

            if ((N - M) * (inter.point() - M) >= Constants<T>::zero()) {
                intersectionCount++;
            }
        }
    }

    return intersectionCount % 2;
}

// TODO
template<class T>
bool Polygon<T>::isStrictlyInside(const Vect2<T>) const
{
    return false;
}

#endif // POLYGON_HPP
