#ifndef BELLMANFORD_CPP
#define BELLMANFORD_CPP

#include "global.hpp"


template<class G, class T> // G: graph type ; T: weight type
class BellmanFord
{
public:
    BellmanFord (const G &graph, const vector<int> startVertice) :
        m_hasNegativeCycle (false)
    {
        m_dists.resize(graph.verticeCount(), +oo);

        for (int vertex : startVertice) {
            m_dists[vertex] = 0;
        }

        // Shortest paths
        for (int i=0; i<graph.verticeCount()-1; i++) {
            for (int vertex=0; vertex<graph.verticeCount(); vertex++) {
                for (int neighbourPos=0; neighbourPos<graph.neighbourCount(vertex); neighbourPos++) {
                    const int neighbour = graph.neighbour(vertex, neighbourPos);

                    m_dists[neighbour] = min(m_dists[vertex] + graph.weight(vertex, neighbourPos),
                                             m_dists[neighbour]);
                }
            }
        }

        // Negative cycles
        for (int i=0; i<graph.verticeCount(); i++) {
            for (int vertex=0; vertex<graph.verticeCount(); vertex++) {
                for (int neighbourPos=0; neighbourPos<graph.neighbourCount(vertex); neighbourPos++) {
                    const int neighbour = graph.neighbour(vertex, neighbourPos);

                    if (m_dists[vertex] + graph.weight(vertex, neighbourPos) < m_dists[neighbour]) {
                        m_dists[neighbour] = -oo;
                        m_hasNegativeCycle = true;
                    }
                }
            }

            if (!m_hasNegativeCycle) break;
        }
    }

    BellmanFord (const G &graph, const int startVertex) :
        BellmanFord (graph, vector<int>{startVertex})
    {}

    inline bool hasNegativeCycle () const
    {
        return m_hasNegativeCycle;
    }

    inline T distTo (const int vertex) const
    {
        return m_dists[vertex];
    }

private:
    vector<T> m_dists;
    bool m_hasNegativeCycle;
};

#endif // BELLMANFORD_CPP
