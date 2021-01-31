#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "infinity.hpp"

#include <queue>
#include <vector>

template<class G>
class Dijkstra
{
public:
    Dijkstra (const G &graph, const std::vector<int> startVertice)
    {
        m_dists.resize(graph.verticeCount(), infinity<typename G::Weight>());

        std::priority_queue<
            std::pair<typename G::Weight, int>,
            std::vector<std::pair<typename G::Weight,int>>,
            std::greater<std::pair<typename G::Weight,int>>
        > pendingVertice; // {dist, vertex}

        for (int vertex : startVertice) {
            pendingVertice.push(std::make_pair(0, vertex));
        }

        while (pendingVertice.size()) {
            const int vertex = pendingVertice.top().second;
            const int dist = pendingVertice.top().first;
            pendingVertice.pop();

            if (m_dists[vertex] != infinity<typename G::Weight>()) {
                continue;
            }
            m_dists[vertex] = dist;

            for (int i=0; i<graph.neighbourCount(vertex); i++) {
                const int neighbour = graph.neighbour(vertex, i);

                if (m_dists[neighbour] == infinity<typename G::Weight>()) {
                    pendingVertice.push(make_pair(dist + graph.weight(vertex, i), neighbour));
                }
            }
        }
    }

    Dijkstra (const G &graph, const int startVertex) :
        Dijkstra (graph, std::vector<int>{startVertex})
    {}

    inline typename G::Weight distTo (const int vertex) const
    {
        return m_dists[vertex];
    }

private:
    std::vector<typename G::Weight> m_dists;
};

#endif // DIJKSTRA_HPP
