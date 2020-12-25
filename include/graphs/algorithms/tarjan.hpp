#ifndef TARJAN_HPP
#define TARJAN_HPP

#include "global.hpp"

#include <stack>
#include <vector>

template<class G>
class Tarjan
{
public:
    Tarjan (const G &graph) :
        m_nextID (0)
    {
        m_states.resize(graph.verticeCount(), NOT_VISITED);
        m_ids.resize(graph.verticeCount(), -1);

        for (int v=0; v<graph.verticeCount(); v++) {
            if (m_states[v] == NOT_VISITED) {
                findSccs(graph, v);
            }
        }

        m_states.clear();
        m_ids.clear();
    }

    /// \brief Returns the number of strongly connected components of the graph
    inline int sccCount () const {
        return m_sccs.size();
    }

    /// \brief Returns a vector containing the strongly connected components of the graph
    inline const std::vector<std::vector<int>>& sccs () const {
        return m_sccs;
    }

    /// \brief Returns the i-th strongly connected component of the graph
    inline const std::vector<int>& scc (const int i) const {
        return m_sccs[i];
    }


private:
    /// \brief Returns the lowest id of a vertice directly accessible from the subtree
    int findSccs (const G &g, const int vertex);

    enum State {
        NOT_VISITED,
        IN_STACK,
        VISITED_WITH_SCC // The vertex' component has been found
    };
    std::vector<State> m_states;

    int m_nextID;
    std::vector<int> m_ids;

    std::stack<int> pendingVertice;

    // Strongly Connected Components
    std::vector<std::vector<int>> m_sccs;
};

template<class G>
int Tarjan<G>::findSccs (const G &graph, const int vertex)
{
    // We know that m_states[vertex] == NOT_VISITED

    m_ids[vertex] = m_nextID++;
    m_states[vertex] = IN_STACK;
    pendingVertice.push(vertex);

    int minID = m_ids[vertex];

    for (auto edge : graph.neighbours(vertex)) {
        const int neighbour = edge.neighbour;

        if (m_states[neighbour] == IN_STACK) {
            minID = std::min(m_ids[neighbour], minID);
        }

        if (m_states[neighbour] == NOT_VISITED) {
            minID = min(findSccs(graph, neighbour), minID);
        }
    }

    if (minID == m_ids[vertex]) {
        std::vector<int> scc;

        bool isOver = false;

        while (!isOver) {
            isOver = pendingVertice.top() == vertex;

            scc.push_back(pendingVertice.top());
            m_states[pendingVertice.top()] = VISITED_WITH_SCC;
            pendingVertice.pop();
        }

        m_sccs.push_back(scc);

        return +oo;
    }

    return minID;
}

#endif // TARJAN_HPP
