#ifndef TREE_HPP
#define TREE_HPP

#include <ostream>
#include <vector>

class Tree
{
public:
    Tree();
    Tree(const int vertexCount, const int root = 0);

    inline int vertexCount() const
    {
        return m_vertices.size();
    }

    inline int root() const
    {
        return m_root;
    }

    inline int parent(const int vertex) const
    {
        return m_vertices[vertex].parent;
    }

    inline const std::vector<int> &children(const int vertex) const
    {
        return m_vertices[vertex].children;
    }

    void setParent(const int vertex, const int newParent);

private:
    struct Vertex {
        int parent;
        std::vector<int> children;
    };

    int m_root;
    std::vector<Vertex> m_vertices;
};

std::ostream &operator<<(std::ostream &, const Tree &);

#endif // TREE_HPP
