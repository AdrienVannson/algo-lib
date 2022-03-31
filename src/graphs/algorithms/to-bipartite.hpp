#ifndef TOBIPARTITE_HPP
#define TOBIPARTITE_HPP

#include <vector>

template<class G>
class ToBipartite
{
public:
    ToBipartite(const G &g) :
        m_states(g.verticeCount(), -1), m_isBipartite(true)
    {
        for (int v = 0; v < g.verticeCount(); v++) {
            if (m_states[v] == -1) {
                explore(g, v, 0);
            }
        }
    }

    bool isBipartite() const
    {
        return m_isBipartite;
    }

    /// \brief Returns the component (0 or 1) in which the vertex v is in
    int component(const int v) const
    {
        return m_states[v];
    }

private:
    // States of a vertex:
    // -1: not visited
    // 0: visited, in the first component
    // 1: visited, in the second component
    std::vector<int> m_states;
    bool m_isBipartite;

    void explore(const G &g, const int v, const int component)
    {
        if (m_states[v] != -1) {
            if (m_states[v] != component) {
                m_isBipartite = false;
            }
            return;
        }

        m_states[v] = component;

        for (int n : g.neighbours(v)) {
            explore(g, n, 1 - component);
        }
    }
};

#endif // TOBIPARTITE_HPP
