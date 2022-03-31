#ifndef BFS_HPP
#define BFS_HPP

#include "constants.hpp"

#include <queue>
#include <vector>

template<class G>
class BFS
{
public:
    BFS(const G &graph, const std::vector<int> startVertice)
    {
        m_dists.resize(graph.verticeCount(), Constants<int>::infinity());

        std::queue<std::pair<int, int>> pendingVertice; // {vertex, dist}

        for (int vertex : startVertice) {
            m_dists[vertex] = 0;
            pendingVertice.push(std::make_pair(vertex, 0));
        }

        while (pendingVertice.size()) {
            const int vertex = pendingVertice.front().first;
            const int dist = pendingVertice.front().second + 1;
            pendingVertice.pop();

            for (int i = 0; i < graph.neighbourCount(vertex); i++) {
                const int neighbour = graph.neighbour(vertex, i);

                if (m_dists[neighbour] == Constants<int>::infinity()) {
                    m_dists[neighbour] = dist;
                    pendingVertice.push(std::make_pair(neighbour, dist));
                }
            }
        }
    }

    BFS(const G &graph, const int startVertex) :
        BFS(graph, std::vector<int> {startVertex})
    {}

    int distTo(const int vertex) const
    {
        return m_dists[vertex];
    }

private:
    std::vector<int> m_dists;
};

#endif // BFS_HPP
