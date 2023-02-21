#pragma once

#include "constants.hpp"
#include <vector>

template<class G>
class FloydWarshall
{
    typedef typename G::Weight Weight;

public:
    FloydWarshall(const G &g)
    {
        const auto oo = Constants<Weight>::infinity();

        m_dists.resize(g.vertexCount());
        for (int i = 0; i < g.vertexCount(); i++) {
            m_dists[i].resize(g.vertexCount());

            for (int j = 0; j < g.vertexCount(); j++) {
                m_dists[i][j] = i == j ? 0 : +oo;
            }
        }

        for (const auto e : g.edges()) {
            if (g.weight(e.edgeId) < m_dists[e.vertex1][e.vertex2]) {
                m_dists[e.vertex1][e.vertex2] = g.weight(e.edgeId);
            }
        }

        for (int z = 0; z < g.vertexCount(); z++) {
            for (int x = 0; x < g.vertexCount(); x++) {
                if (m_dists[x][z] == +oo) continue;

                for (int y = 0; y < g.vertexCount(); y++) {
                    if (m_dists[z][y] != +oo
                        && m_dists[x][z] + m_dists[z][y] < m_dists[x][y]) {
                        m_dists[x][y] = m_dists[x][z] + m_dists[z][y];
                    }
                }
            }
        }
    }

    inline Weight dist(const int vertex1, const int vertex2) const
    {
        return m_dists[vertex1][vertex2];
    }

private:
    std::vector<std::vector<Weight>> m_dists;
};
