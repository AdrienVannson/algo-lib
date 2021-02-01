#ifndef KOSARAJU_HPP
#define KOSARAJU_HPP

#include <vector>

#include "transpose-graph.hpp"

template<class G>
class Kosaraju
{
public:
    Kosaraju (const G &graph)
    {
        m_graph = &graph;
        m_states.resize(graph.verticeCount(), NOT_VISITED);

        // First DFS: find a postordering
        for (int v=0; v<graph.verticeCount(); v++) {
            findPostOrdering(v);
        }

        const G transposeGraph = getTransposeGraph(graph);
        m_graph = &transposeGraph;

        // Second DFS: find the SCCs
        for (int i=graph.verticeCount()-1; i>=0; i--) {
            const int v = m_postOrdering[i];

            if (m_states[v] < 0) { // Not visited during the second DFS
                m_sccs.push_back({});
                findSccs(v);
            }
        }

        m_postOrdering.clear();
    }

    /// \brief Returns the number of strongly connected components of the graph
    inline int sccCount () const {
        return m_sccs.size();
    }

    /// \brief Returns a vector containing the strongly connected components of the graph
    inline const std::vector<std::vector<int>>& sccs () const {
        return m_sccs;
    }

    /// \brief Returns the ID of the strongly connected component containing a given vertice
    inline int scc (const int v) const {
        return m_states[v];
    }


private:
    // DFS 1
    void findPostOrdering (const int v)
    {
        if (m_states[v] == VISITED_1) return;
        m_states[v] = VISITED_1;

        for (auto edge : m_graph->neighbours(v)) {
            findPostOrdering(edge.neighbour);
        }

        m_postOrdering.push_back(v);
    }

    // DFS 2
    void findSccs (const int v)
    {
        if (m_states[v] >= 0) return;
        m_states[v] = m_sccs.size() - 1;

        m_sccs.back().push_back(v);

        for (auto edge : m_graph->neighbours(v)) {
            findSccs(edge.neighbour);
        }
    }

    const G *m_graph; // Only valid during the construction of the object
    std::vector<int> m_postOrdering;

    const int NOT_VISITED = -2;
    const int VISITED_1 = -1;

    // NOT_VISITED, VISITED_1 (for the first DFS) or the ID of the SCC
    std::vector<int> m_states;

    // Strongly Connected Components
    std::vector<std::vector<int>> m_sccs;
};

#endif // KOSARAJU_HPP
