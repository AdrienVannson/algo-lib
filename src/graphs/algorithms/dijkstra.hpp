#pragma once

#include "constants.hpp"

#include <queue>
#include <vector>

template<class G>
class Dijkstra
{
public:
    Dijkstra(const G &graph, const std::vector<int> startVertices)
    {
        m_dists.resize(
            graph.vertexCount(),
            Constants<typename G::Weight>::infinity()
        );

        std::priority_queue<
            std::pair<typename G::Weight, int>,
            std::vector<std::pair<typename G::Weight, int>>,
            std::greater<std::pair<typename G::Weight, int>>>
            pendingVertices; // {dist, vertex}

        for (int vertex : startVertices) {
            pendingVertices.push(std::make_pair(0, vertex));
        }

        while (pendingVertices.size()) {
            const int vertex = pendingVertices.top().second;
            const typename G::Weight dist = pendingVertices.top().first;
            pendingVertices.pop();

            if (m_dists[vertex] != Constants<typename G::Weight>::infinity()) {
                continue;
            }
            m_dists[vertex] = dist;

            for (int i = 0; i < graph.neighbourCount(vertex); i++) {
                const int neighbour = graph.neighbour(vertex, i);

                if (m_dists[neighbour]
                    == Constants<typename G::Weight>::infinity()) {
                    pendingVertices.push(std::make_pair(
                        dist + graph.weight(vertex, i),
                        neighbour
                    ));
                }
            }
        }
    }

    Dijkstra(const G &graph, const int startVertex) :
        Dijkstra(graph, std::vector<int> {startVertex})
    {}

    /// \brief Returns the shortest distance from one of the start vertices to a
    /// vertex
    inline typename G::Weight distTo(const int vertex) const
    {
        return m_dists[vertex];
    }

    /// \brief Returns if a vertex is accessible from one of the start vertices
    inline bool isAccessible(const int vertex) const
    {
        return m_dists[vertex] != Constants<typename G::Weight>::infinity();
    }

private:
    std::vector<typename G::Weight> m_dists;
};
