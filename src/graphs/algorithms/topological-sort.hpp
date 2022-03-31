#ifndef TOPOLOGICAL_SORT_HPP
#define TOPOLOGICAL_SORT_HPP

#include <algorithm>
#include <vector>

template<class G>
class TopologicalSort
{
public:
    TopologicalSort(const G &g) : m_isPossible(true)
    {
        m_states.resize(g.verticeCount());
        m_topologicalSort.reserve(g.verticeCount());

        std::vector<std::pair<int, int>> pending; // {vertex, posNeighbour}
        pending.reserve(g.verticeCount() + 1);

        for (int vertex = 0; vertex < g.verticeCount(); vertex++) {
            pending.push_back(std::make_pair(vertex, 0));

            while (pending.size()) {
                const int vertex = pending.back().first;
                const int posNeighbour = pending.back().second;
                pending.pop_back();

                if (posNeighbour == 0) {
                    if (m_states[vertex] == 2) {
                        m_isPossible = false;
                        m_topologicalSort.clear();
                        return;
                    }
                    if (m_states[vertex] == 1) continue;

                    m_states[vertex] = 2;
                }

                if (posNeighbour < g.neighbourCount(vertex)) {
                    pending.push_back(std::make_pair(vertex, posNeighbour + 1));
                    pending.push_back(
                        std::make_pair(g.neighbour(vertex, posNeighbour), 0));
                } else {
                    m_states[vertex] = 1;
                    m_topologicalSort.push_back(vertex);
                }
            }
        }

        std::reverse(m_topologicalSort.begin(), m_topologicalSort.end());
        m_states.clear();
    }

    inline bool isPossible() const
    {
        return m_isPossible;
    }

    inline const std::vector<int> &topologicalSort() const
    {
        return m_topologicalSort;
    }

private:
    bool m_isPossible;
    std::vector<int> m_topologicalSort;
    std::vector<int> m_states; // 0: not visited, 1: visited, 2: being visited
};

#endif // TOPOLOGICAL_SORT_HPP
