#ifndef CONVEXHULL_HPP
#define CONVEXHULL_HPP

#include "Vect2.hpp"

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
            while (m_verticeIds.size() >= 2) {
                const Vect2<T> v = points[ids[i]];
                const Vect2<T> a = points[m_verticeIds.back()];
                const Vect2<T> b = points[m_verticeIds[m_verticeIds.size() - 2]];

                if (((a - b) ^ (v - b)) <= 0) {
                    m_verticeIds.pop_back();
                } else {
                    break;
                }
            }
            m_verticeIds.push_back(ids[i]);
        }

        // Lower part
        sort(ids.begin(), ids.end(), [&points](const int a, const int b) {
            if (points[a].x != points[b].x) return points[a].x < points[b].x;
            return points[a].y > points[b].y;
        });

        const uint upperSize = m_verticeIds.size();
        for (int i = 1; i < (int)points.size(); i++) {
            while (m_verticeIds.size() > upperSize) {
                const Vect2<T> v = points[ids[i]];
                const Vect2<T> a = points[m_verticeIds.back()];
                const Vect2<T> b = points[m_verticeIds[m_verticeIds.size() - 2]];

                if (((a - b) ^ (v - b)) <= 0) {
                    m_verticeIds.pop_back();
                } else {
                    break;
                }
            }
            m_verticeIds.push_back(ids[i]);
        }

        m_verticeIds.pop_back();
    }

    /// \brief Returns the ids of the points belonging to the convex hull's
    /// boundary, ordered counterclockwise
    const std::vector<int> &verticeIds() const { return m_verticeIds; }

private:
    // Ids of the points belonging to the convex hull's boundary, ordered
    // counterclockwise
    std::vector<int> m_verticeIds;
};

#endif // CONVEXHULL_HPP
