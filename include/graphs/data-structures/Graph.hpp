#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

class Graph
{
public:
    typedef int Weight;

    struct Edge
    {
        int vertex1, vertex2;
        int edgeId;
    };

    struct EdgeTo
    {
        int neighbour;
        int edgeId;
    };

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

    inline int edgeCount () const
    {
        return m_edgeCount;
    }

    /// \brief Returns the id of the n-th neighbour of a vertex
    inline int neighbour (const int vertex, const int neighbourPos) const
    {
        return m_vertice[vertex][neighbourPos].neighbour;
    }

    /// \brief Returns the edges connected to a vertex
    const std::vector<EdgeTo>& edgesToNeighbours (const int vertex) const
    {
        return m_vertice[vertex];
    }

    /// \brief Returns the neighbours of a vertex
    std::vector<int> neighbours (const int vertex) const
    {
        std::vector<int> nbs;

        for (EdgeTo edge : m_vertice[vertex]) {
            nbs.push_back(edge.neighbour);
        }

        return nbs;
    }

    /// \brief Always returns 1 (the graph is not weighted)
    inline int weight (const int edgeId) const
    {
        (void)edgeId;
        return 1;
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
        return m_vertice[vertex][neighbourPos].edgeId;
    }

    /// \brief Returns the id of the first edge from one vertex to another (-1 if it doesn't exist)
    inline int edgeIdTo (const int vertex, const int neighbour)
    {
        for (int i=0; i<neighbourCount(vertex); i++) {
            if (m_vertice[vertex][i].neighbour == neighbour) {
                return m_vertice[vertex][i].edgeId;
            }
        }
        return -1;
    }

    /// \brief Returns a vector listing all the edges of the graph
    std::vector<Edge> edges () const
    {
        std::vector<Edge> res;

        for (int n=0; n<verticeCount(); n++) {
            for (int m=0; m<neighbourCount(n); m++) {
                if (m_isDirected || n <= neighbour(n, m)) {
                    res.push_back(Edge{n, neighbour(n, m), edgeId(n, m)});
                }
            }
        }

        return res;
    }

    /// \brief Creates a new edge between two vertice
    inline void addEdge (const int vertex1, const int vertex2)
    {
        m_vertice[vertex1].push_back(EdgeTo{vertex2, m_edgeCount});
        if (!m_isDirected && vertex1 != vertex2) {
            m_vertice[vertex2].push_back(EdgeTo{vertex1, m_edgeCount});
        }

        m_edgeCount++;
    }

protected:
    bool m_isDirected;
    int m_edgeCount;
    std::vector<std::vector<EdgeTo>> m_vertice; // [vertex][neighbourPos]
};

#endif // GRAPH_HPP
