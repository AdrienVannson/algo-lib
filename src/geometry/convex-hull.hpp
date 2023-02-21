#pragma once

#include "constants.hpp"
#include "vect2.hpp"

#include <algorithm>
#include <vector>

template<class T>
class ConvexHull
{
public:
    ConvexHull(const std::vector<Vect2<T>> &points)
    {
        std::vector<int> ids;
        ids.reserve(points.size());
        for (int id = 0; id < (int)points.size(); id++) {
            ids.push_back(id);
        }

        // Upper part
        sort(ids.begin(), ids.end(), [&points](const int a, const int b) {
            if (points[a].x != points[b].x) return points[a].x > points[b].x;
            return points[a].y < points[b].y;
        });

        for (int i = 0; i < (int)points.size(); i++) {
            while (m_verticesIds.size() >= 2) {
                const Vect2<T> v = points[ids[i]];
                const Vect2<T> a = points[m_verticesIds.back()];
                const Vect2<T> b =
                    points[m_verticesIds[m_verticesIds.size() - 2]];

                if (((a - b) ^ (v - b)) <= Constants<T>::zero()) {
                    m_verticesIds.pop_back();
                } else {
                    break;
                }
            }
            m_verticesIds.push_back(ids[i]);
        }

        // Lower part
        sort(ids.begin(), ids.end(), [&points](const int a, const int b) {
            if (points[a].x != points[b].x) return points[a].x < points[b].x;
            return points[a].y > points[b].y;
        });

        const uint upperSize = m_verticesIds.size();
        for (int i = 1; i < (int)points.size(); i++) {
            while (m_verticesIds.size() > upperSize) {
                const Vect2<T> v = points[ids[i]];
                const Vect2<T> a = points[m_verticesIds.back()];
                const Vect2<T> b =
                    points[m_verticesIds[m_verticesIds.size() - 2]];

                if (((a - b) ^ (v - b)) <= Constants<T>::zero()) {
                    m_verticesIds.pop_back();
                } else {
                    break;
                }
            }
            m_verticesIds.push_back(ids[i]);
        }

        m_verticesIds.pop_back();
    }

    /// \brief Returns the number of points belonging to the convex hull's
    /// boundary
    int size() const
    {
        return m_verticesIds.size();
    }

    /// \brief Returns the ids of the points belonging to the convex hull's
    /// boundary, ordered counterclockwise
    const std::vector<int> &verticesIds() const
    {
        return m_verticesIds;
    }

private:
    // Ids of the points belonging to the convex hull's boundary, ordered
    // counterclockwise
    std::vector<int> m_verticesIds;
};

#endif // CONVEXHULL_HPP
