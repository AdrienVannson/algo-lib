#ifndef MINCUT_HPP
#define MINCUT_HPP

#include <vector>

#include "graphs/data-structures/Graph.hpp"
#include "graphs/algorithms/BFS.hpp"

// F: max-flow algorithm; G: graph type; T: weigth type
template<class F, class G, class T>
class MinCut
{
public:
    MinCut (const F &maxFlow, const G &graph) :
        m_minCut(maxFlow.maxFlow())
    {
        Graph g(graph.verticeCount(), true);

        for (auto edge : graph.edges()) {
            const T capacity = graph.weight(edge.edgeId);
            const T flow = maxFlow.flowOnEdge(edge.edgeId);

            if (flow > 0) {
                g.addEdge(edge.vertex2, edge.vertex1);
            }
            if (flow < capacity) {
                g.addEdge(edge.vertex1, edge.vertex2);
            }
        }

        BFS<Graph> bfs(g, maxFlow.source());

        for (auto edge : graph.edges()) {
            if (bfs.distTo(edge.vertex1) != INT_MAX && bfs.distTo(edge.vertex2) == INT_MAX) {
                m_cut.push_back(edge);
            }
        }
    }

    T minCut () const
    {
        return m_minCut;
    }

    const std::vector<typename G::Edge>& cutEdges () const
    {
        return m_cut;
    }

private:
    const T m_minCut;
    std::vector<typename G::Edge> m_cut;
};


#endif // MINCUT_HPP
