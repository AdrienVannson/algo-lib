#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "data-structures/disjoint-set.hpp"

#include <algorithm>

template<class G>
class Kruskal
{
public:
    Kruskal(const G &g) : m_sum(0)
    {
        assert(!g.isDirected());

        DisjointSet ds(g.vertexCount());

        auto edges = g.edges();
        std::sort(
            edges.begin(),
            edges.end(),
            [&g](const typename G::Edge &e1, const typename G::Edge &e2) {
                return g.weight(e1.edgeId) < g.weight(e2.edgeId);
            }
        );

        for (auto e : edges) {
            if (ds.find(e.vertex1) != ds.find(e.vertex2)) {
                ds.merge(e.vertex1, e.vertex2);
                m_edges.push_back(e);
                m_sum += g.weight(e.edgeId);
            }
        }
    }

    /// \brief Edges of a minimum spanning forest
    const std::vector<typename G::Edge> &edges() const
    {
        return m_edges;
    }

    /// \brief Number of edges of a minimum spanning forest
    int edgeCount() const
    {
        return m_edges.size();
    }

    /// \brief Sum of the weights of the edges of a minimum spanning forest
    typename G::Weight sum() const
    {
        return m_sum;
    }

private:
    // Edges of the minimum spanning forest
    std::vector<typename G::Edge> m_edges;

    // Sum of their weights
    typename G::Weight m_sum;
};

#endif // KRUSKAL_HPP
