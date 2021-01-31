#ifndef WGRAPH_HPP
#define WGRAPH_HPP

#include "Graph.hpp"

template<class T>
class WGraph : public Graph
{
public:
    WGraph (const int verticeCount, const bool isDirected) :
        Graph (verticeCount, isDirected)
    {}

    /// \brief Returns the weight of the n-th edge
    inline T weight (const int edgeId) const
    {
        return m_weights[edgeId];
    }

    /// \brief Returns the weight of the n-th out-edge of a vertex
    inline T weight (const int vertex, const int neighbourPos) const
    {
        return m_weights[ m_vertice[vertex][neighbourPos].edgeId ];
    }

    /// \brief Sets the weight of the n-th out-edge of a vertex
    inline void setWeight (const int vertex, const int neighbourPos, const T weight)
    {
        m_weights[ m_vertice[vertex][neighbourPos].edgeId ] = weight;
    }

    /// \brief Sets the weight of the n-th edge
    inline void setWeight (const int edgeId, const T weight)
    {
        m_weights[edgeId] = weight;
    }


    /// \brief Creates a new edge between two vertice
    inline void addEdge (const int vertex1, const int vertex2, const T weight)
    {
        m_vertice[vertex1].push_back(EdgeTo{vertex2, m_edgeCount});
        if (!m_isDirected) {
            m_vertice[vertex2].push_back(EdgeTo{vertex1, m_edgeCount});
        }

        m_weights.push_back(weight);
        m_edgeCount++;
    }

protected:
    std::vector<T> m_weights;

private:
    inline void addEdge (const int vertex1, const int vertex2) = delete;

};

#endif // WGRAPH_HPP
