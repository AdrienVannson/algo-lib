#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "global.hpp"


class Graph
{
public:

    Graph (const int verticeCount, const bool isDirected) :
        m_isDirected (isDirected),
        m_edgeCount(0)
    {
        m_vertice.resize(verticeCount);
    }

    inline bool isDirected () const
    {
        return m_isDirected;
    }

    inline int verticeCount () const
    {
        return m_vertice.size();
    }

    inline int neighbourCount (const int vertex) const
    {
        return m_vertice[vertex].size();
    }

    /// \brief Returns the id of the n-th neighbour of a vertex
    inline int neighbour (const int vertex, const int neighbourPos) const
    {
        return m_vertice[vertex][neighbourPos].first;
    }

    /// \brief Always returns 1 (the graph is not weighted)
    inline int weight (const int vertex, const int neighbourPos) const
    {
        (void)vertex, (void)neighbourPos;
        return 1;
    }

    /// \brief Returns the id of the n-th out-edge of a vertex
    inline int edgeId (const int vertex, const int neighbourPos) const
    {
        return m_vertice[vertex][neighbourPos].second;
    }

    /// \brief Returns the id of the first edge from one vertex to another (-1 if it doesn't exist)
    inline int edgeIdTo (const int vertex, const int neighbour)
    {
        for (int i=0; i<neighbourCount(vertex); i++) {
            if (m_vertice[vertex][i].first == neighbour) {
                return m_vertice[vertex][i].second;
            }
        }
        return -1;
    }

    /// \brief Creates a new edge between two vertice
    inline void addEdge (const int vertex1, const int vertex2)
    {
        m_vertice[vertex1].push_back(make_pair(vertex2, m_edgeCount));
        if (!m_isDirected) {
            m_vertice[vertex2].push_back(make_pair(vertex1, m_edgeCount));
        }

        m_edgeCount++;
    }

protected:
    bool m_isDirected;
    int m_edgeCount;
    vector<vector<pair<int, int>>> m_vertice; // [vertex][neighbourPos] --> {neighbourID, edgeID}
};

#endif // GRAPH_HPP
