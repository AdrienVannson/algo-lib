#ifndef TARJAN_HPP
#define TARJAN_HPP

#include <stack>
#include <vector>

// TODEL
#include "graphs/data-structures/Graph.hpp"

template<class G>
class Tarjan
{
public:
    Tarjan (const Graph &graph) :
        m_nextID (0)
    {
        m_states.resize(graph.verticeCount(), NOT_VISITED);
        m_ids.resize(graph.verticeCount(), -1);

        for (int v=0; v<graph.verticeCount(); v++) {
            if (m_states[v] == NOT_VISITED) {
                findSCC(graph, v);
            }
        }

        m_states.clear();
        m_ids.clear();
    }

    inline int sccCount () const {
        return m_scc.size();
    }

    inline const std::vector<std::vector<int>>& scc () const {
        return m_scc;
    }
    inline std::vector<std::vector<int>>& scc () {
        return m_scc;
    }

    inline const std::vector<int>& scc (const int i) const {
        return m_scc[i];
    }
    inline std::vector<int>& scc (const int i) {
        return m_scc[i];
    }


private:
    // Renvoie le noeud minimal vers lequel on peut remonter
    int findSCC (const Graph &g, const int vertex);

    enum State { // TODO: meilleurs noms
        NOT_VISITED,
        BEING_VISITED,
        VISITED_WITHOUT_SCC, // La composante n'a pas encore été trouvée (dans la pile)
        VISITED_WITH_SCC // La composante a été trouvée (plus dans la pile)
    };
    std::vector<State> m_states;

    int m_nextID;
    std::vector<int> m_ids;

    std::stack<int> pile;

    // Strongly Connected Components
    std::vector<std::vector<int>> m_scc;
};

template<class G>
int Tarjan<G>::findSCC (const Graph &graph, const int vertex)
{
    // We know that m_states[vertex] == NOT_VISITED

    m_ids[vertex] = m_nextID++;
    m_states[vertex] = BEING_VISITED;
    pile.push(vertex);

    int parentMin = m_ids[vertex];

    for (auto edge : graph.neighbours(vertex)) {
        const int neighbour = edge.neighbour;

        if (m_states[neighbour] == BEING_VISITED
         || m_states[neighbour] == VISITED_WITHOUT_SCC) {
            parentMin = min(m_ids[neighbour], parentMin);
        }

        if (m_states[neighbour] == NOT_VISITED) {
            parentMin = min(findSCC(graph, neighbour), parentMin);
        }
    }

    if (parentMin == m_ids[vertex]) {
        std::vector<int> scc;

        bool succes = false;

        while (!succes) {
            succes = pile.top() == vertex;

            scc.push_back(pile.top());
            m_states[pile.top()] = VISITED_WITH_SCC;
            pile.pop();
        }

        m_scc.push_back(scc);

        return +oo;
    }

    m_states[vertex] = VISITED_WITHOUT_SCC;
    return parentMin;
}

#endif // TARJAN_HPP
