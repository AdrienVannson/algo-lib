#ifndef TREE_HPP
#define TREE_HPP

#include <ostream>
#include <vector>

class Tree
{
public:
    Tree();
    Tree(const int verticeCount, const int root = 0);

    inline int verticeCount() const { return m_vertice.size(); }

    inline int root() const { return m_root; }

    inline int parent(const int vertex) const { return m_vertice[vertex].parent; }

    inline const std::vector<int> &children(const int vertex) const
    {
        return m_vertice[vertex].children;
    }

    void setParent(const int vertex, const int newParent);

private:
    struct Vertex {
        int parent;
        std::vector<int> children;
    };

    int m_root;
    std::vector<Vertex> m_vertice;
};

std::ostream &operator<<(std::ostream &, const Tree &);

#endif // TREE_HPP
