#ifndef EDMONDSKARP_HPP
#define EDMONDSKARP_HPP

#include <cassert>
#include <climits>
#include <queue>
#include <vector>

// G: graph type; T: weigth type
template<class G, class T>
class EdmondsKarp
{
public:
    EdmondsKarp (const G &graph, const int source, const int sink) :
        m_flow(0)
    {
        assert(source != sink);
        assert(graph.isDirected()); // If not, the same edge is represented twice with the same id

        // Build the residual graph
        m_residualGraph.resize(graph.verticeCount());

        const int edgeCount = graph.edgeCount();
        m_residualCapacities.resize(2*edgeCount, 0);

        for (int v=0; v<graph.verticeCount(); v++) {
            for (auto edgeTo : graph.neighbours(v)) {
                m_residualGraph[v].push_back(Edge{edgeTo.neighbour, edgeTo.edgeId});
                m_residualGraph[edgeTo.neighbour].push_back(Edge{v, edgeTo.edgeId + edgeCount});

                m_residualCapacities[edgeTo.edgeId] = graph.weight(edgeTo.edgeId);
            }
        }

        // Find augmenting paths
        while (true) {
            std::vector<int> dists(graph.verticeCount(), INT_MAX);

            std::queue<int> pending;
            pending.push(source);
            dists[source] = 0;

            while (pending.size()) {
                const int vertex = pending.front();
                pending.pop();

                if (vertex == sink) { // Success
                    break;
                }

                for (Edge edge : m_residualGraph[vertex]) {
                    if (m_residualCapacities[edge.id] > 0 && dists[edge.neighbour] == INT_MAX) {
                        dists[edge.neighbour] = dists[vertex] + 1;
                        pending.push(edge.neighbour);
                    }
                }
            }

            if (dists[sink] == INT_MAX) { // No more augmenting paths
                break;
            }

            std::vector<int> edges;
            int vertex = sink;
            T flow{};

            while (vertex != source) {
                const int dist = dists[vertex];

                for (Edge edge : m_residualGraph[vertex]) {
                    const int oppositeEdge = (edge.id + edgeCount) % (2*edgeCount);

                    if (dists[edge.neighbour] == dist - 1 && m_residualCapacities[oppositeEdge] != 0) {
                        if (vertex == sink || m_residualCapacities[oppositeEdge] < flow) {
                            flow = m_residualCapacities[oppositeEdge];
                        }

                        edges.push_back(oppositeEdge);
                        vertex = edge.neighbour;
                        break;
                    }
                }
            }

            for (int e : edges) {
                m_residualCapacities[e] -= flow;
                m_residualCapacities[(e + edgeCount) % (2*edgeCount)] += flow;
            }

            m_flow += flow;
        }
    }

    inline T maxFlow () const
    {
        return m_flow;
    }

    inline T flowOnEdge (const int edge) const
    {
        return m_residualCapacities[edge + m_residualCapacities.size()/2];
    }

    inline T residualCapacity (const int edge) const
    {
        return m_residualCapacities[edge];
    }

private:
    T m_flow;

    struct Edge
    {
        int neighbour;
        int id;
    };
    std::vector<std::vector<Edge>> m_residualGraph;
    std::vector<T> m_residualCapacities; // oppositeEdge = (edge + edgeCount) % (2*edgeCount)
};

#endif // EDMONDSKARP_HPP
