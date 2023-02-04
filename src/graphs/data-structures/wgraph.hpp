#ifndef WGRAPH_HPP
#define WGRAPH_HPP

#include "Graph.hpp"

template<class T>
class WGraph : public Graph
{
public:
    typedef T Weight;

    WGraph(const int vertexCount, const bool isDirected) :
        Graph(vertexCount, isDirected)
    {}

    /// \brief Returns the weight of the n-th edge
    inline T weight(const int edgeId) const
    {
        return m_weights[edgeId];
    }

    /// \brief Returns the weight of the n-th out-edge of a vertex
    inline T weight(const int vertex, const int neighbourPos) const
    {
        return m_weights[m_vertices[vertex][neighbourPos].edgeId];
    }

    /// \brief Sets the weight of the n-th out-edge of a vertex
    inline void
    setWeight(const int vertex, const int neighbourPos, const T weight)
    {
        m_weights[m_vertices[vertex][neighbourPos].edgeId] = weight;
    }

    /// \brief Sets the weight of the n-th edge
    inline void setWeight(const int edgeId, const T weight)
    {
        m_weights[edgeId] = weight;
    }

    /// \brief Creates a new edge between two vertices
    inline void addEdge(const int vertex1, const int vertex2, const T weight)
    {
        m_vertices[vertex1].push_back(EdgeTo {vertex2, m_edgeCount});
        if (!m_isDirected) {
            m_vertices[vertex2].push_back(EdgeTo {vertex1, m_edgeCount});
        }

        m_weights.push_back(weight);
        m_edgeCount++;
    }

    /// \brief Returns the graph obtained after changing the direction of the
    /// edges
    inline WGraph<T> transposeGraph() const
    {
        assert(m_isDirected);

        WGraph<T> g(vertexCount(), m_isDirected);
        g.m_edgeCount = m_edgeCount;
        g.m_weights = m_weights;

        for (int v = 0; v < vertexCount(); v++) {
            for (const EdgeTo edge : m_vertices[v]) {
                g.m_vertices[edge.neighbour].push_back(EdgeTo {v, edge.edgeId});
            }
        }

        return g;
    }

protected:
    std::vector<T> m_weights;

private:
    inline void addEdge(const int vertex1, const int vertex2) = delete;
};

#endif // WGRAPH_HPP
