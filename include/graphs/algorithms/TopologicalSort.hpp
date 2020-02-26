#ifndef TOPOLOGICALSORT_HPP
#define TOPOLOGICALSORT_HPP

#include "global.hpp"


template<class G>
class TopologicalSort
{
public:
    TopologicalSort (const G &g)
    {
        m_states.resize(g.verticeCount());

        for (int vertex=0; vertex<g.verticeCount(); vertex++) {
            if (!dfs(g, vertex)) {
                break;
            }
        }

        reverse(m_topologicalSort.begin(), m_topologicalSort.end());
        m_states.clear();
    }

    inline bool isPossible () const
    {
        return !m_topologicalSort.empty();
    }

    inline const vector<int>& topologicalSort () const
    {
        return m_topologicalSort;
    }

private:
    bool dfs (const G &g, const int vertex)
    {
        if (m_states[vertex] == 2) {
            m_topologicalSort.clear();
            return false;
        }
        if (m_states[vertex] == 1) {
            return true;
        }

        m_states[vertex] = 2;

        for (int neighbourPos=0; neighbourPos<g.neighbourCount(vertex); neighbourPos++) {
            if (!dfs(g, g.neighbour(vertex, neighbourPos))) {
                return false;
            }
        }

        m_states[vertex] = 1;
        m_topologicalSort.push_back(vertex);
        return true;
    }

    vector<int> m_topologicalSort;
    vector<int> m_states; // 0: not visited, 1: visited, 2: being visited
};

#endif // TOPOLOGICALSORT_HPP
