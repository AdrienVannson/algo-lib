#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "constants.hpp"

#include <vector>

template<class G>
class BellmanFord
{
public:
    BellmanFord(const G &g, const std::vector<int> startVertice) :
        m_hasNegativeCycle(false)
    {
        const auto oo = Constants<typename G::Weight>::infinity();

        m_dists.resize(g.vertexCount(), +oo);

        for (int vertex : startVertice) {
            m_dists[vertex] = 0;
        }

        // Shortest paths
        for (int i = 0; i < g.vertexCount() - 1; i++) {
            for (const typename G::Edge e : g.edges()) {
                typename G::Weight d = m_dists[e.vertex1] + g.weight(e.edgeId);

                if (m_dists[e.vertex1] != +oo && d < m_dists[e.vertex2]) {
                    m_dists[e.vertex2] = d;
                }
            }
        }

        // Negative cycles
        bool succes = true;
        while (succes) {
            succes = false;

            for (const typename G::Edge e : g.edges()) {
                if (m_dists[e.vertex1] == +oo) continue;

                if ((m_dists[e.vertex1] == -oo && m_dists[e.vertex2] != -oo)
                    || (m_dists[e.vertex1] != -oo
                        && m_dists[e.vertex1] + g.weight(e.edgeId)
                            < m_dists[e.vertex2]))
                {
                    m_dists[e.vertex2] = -oo;

                    m_hasNegativeCycle = true;
                    succes = true;
                }
            }
        }
    }

    BellmanFord(const G &graph, const int startVertex) :
        BellmanFord(graph, std::vector<int> {startVertex})
    {}

    inline bool hasNegativeCycle() const
    {
        return m_hasNegativeCycle;
    }

    inline typename G::Weight distTo(const int vertex) const
    {
        return m_dists[vertex];
    }

private:
    std::vector<typename G::Weight> m_dists;
    bool m_hasNegativeCycle;
};

#endif // BELLMAN_FORD_HPP
