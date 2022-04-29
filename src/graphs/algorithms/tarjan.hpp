#ifndef TARJAN_HPP
#define TARJAN_HPP

#include "constants.hpp"

#include <stack>
#include <vector>

template<class G>
class Tarjan
{
public:
    Tarjan(const G &graph) : m_nextID(0)
    {
        m_states.resize(graph.vertexCount(), NOT_VISITED);
        m_ids.resize(graph.vertexCount(), -1);

        for (int v = 0; v < graph.vertexCount(); v++) {
            if (m_states[v] == NOT_VISITED) {
                findSccs(graph, v);
            }
        }

        m_ids.clear();
    }

    /// \brief Returns the number of strongly connected components of the graph
    inline int sccCount() const
    {
        return m_sccs.size();
    }

    /// \brief Returns a vector containing the strongly connected components of
    /// the graph
    inline const std::vector<std::vector<int>> &sccs() const
    {
        return m_sccs;
    }

    /// \brief Returns the ID of the strongly connected component containing a
    /// given vertex
    inline int scc(const int v) const
    {
        return m_states[v];
    }

private:
    /// \brief Returns the lowest id of a vertex directly accessible from the
    /// subtree
    int findSccs(const G &g, const int vertex);

    const int NOT_VISITED = -2;
    const int IN_STACK = -1;

    // NOT_VISITED, IN_STACK or the ID of the SCC
    std::vector<int> m_states;

    int m_nextID;
    std::vector<int> m_ids;

    std::stack<int> pendingVertice;

    // Strongly Connected Components
    std::vector<std::vector<int>> m_sccs;
};

template<class G>
int Tarjan<G>::findSccs(const G &graph, const int vertex)
{
    // We know that m_states[vertex] == NOT_VISITED

    m_ids[vertex] = m_nextID++;
    m_states[vertex] = IN_STACK;
    pendingVertice.push(vertex);

    int minID = m_ids[vertex];

    for (const int neighbour : graph.neighbours(vertex)) {

        if (m_states[neighbour] == IN_STACK) {
            minID = std::min(m_ids[neighbour], minID);
        }

        if (m_states[neighbour] == NOT_VISITED) {
            minID = std::min(findSccs(graph, neighbour), minID);
        }
    }

    if (minID == m_ids[vertex]) {
        std::vector<int> scc;

        bool isOver = false;

        while (!isOver) {
            isOver = pendingVertice.top() == vertex;

            scc.push_back(pendingVertice.top());
            m_states[pendingVertice.top()] = m_sccs.size();
            pendingVertice.pop();
        }

        m_sccs.push_back(scc);

        return Constants<int>::infinity();
    }

    return minID;
}

#endif // TARJAN_HPP
