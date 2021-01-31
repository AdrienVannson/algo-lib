#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "global.hpp"

template<class G>
class Dijkstra
{
public:
    Dijkstra (const G &graph, const vector<int> startVertice)
    {
        m_dists.resize(graph.verticeCount(), +oo);

        priority_queue<pair<typename G::Weight, int>,
                       vector<pair<typename G::Weight,int>>,
                       greater<pair<typename G::Weight,int>>> pendingVertice; // {dist, vertex}

        for (int vertex : startVertice) {
            pendingVertice.push(make_pair(0, vertex));
        }

        while (pendingVertice.size()) {
            const int vertex = pendingVertice.top().second;
            const int dist = pendingVertice.top().first;
            pendingVertice.pop();

            if (m_dists[vertex] != +oo) {
                continue;
            }
            m_dists[vertex] = dist;

            for (int i=0; i<graph.neighbourCount(vertex); i++) {
                const int neighbour = graph.neighbour(vertex, i);

                if (m_dists[neighbour] == +oo) {
                    pendingVertice.push(make_pair(dist + graph.weight(vertex, i), neighbour));
                }
            }
        }
    }

    Dijkstra (const G &graph, const int startVertex) :
        Dijkstra (graph, vector<int>{startVertex})
    {}

    inline typename G::Weight distTo (const int vertex) const
    {
        return m_dists[vertex];
    }

private:
    vector<typename G::Weight> m_dists;
};

#endif // DIJKSTRA_HPP
