#ifndef TREE_HPP
#define TREE_HPP

#include <cassert>
#include <ostream>
#include <vector>

/// \brief Represents a forest of rooted trees. After the initialisation, the
/// forest is composed of trees containing only one node. The forest is updated
/// using setParent on a vertex. A node is the root of a tree if and only if its
/// parent is -1. After calling setParent at least one time, updateRoots must be
/// called to update the roots of the trees.
class Tree
{
public:
    Tree(const int vertexCount = 0);
    Tree(const int vertexCount, const int root);

    /// \brief Returns the number of vertices in the forest
    inline int vertexCount() const
    {
        return m_vertices.size();
    }

    /// \brief Returs the root of the tree. The forest must contain only one
    /// tree.
    inline int root() const
    {
        assert(m_roots.size() == 1);
        return m_roots[0];
    }

    /// \brief Returns the roots of the trees in the forest.
    inline const std::vector<int> &roots() const
    {
        return m_roots;
    }

    /// \brief Returns the parent of a vertex (-1 if the vertex is a root).
    inline int parent(const int vertex) const
    {
        return m_vertices[vertex].parent;
    }

    /// \brief Returns the children of a vertex
    inline const std::vector<int> &children(const int vertex) const
    {
        return m_vertices[vertex].children;
    }

    /// \brief Sets the parent of a vertex (-1 if the vertex must become a root)
    void setParent(const int vertex, const int newParent);

    /// \brief Returns the number of tree in the forest
    inline int treeCount() const
    {
        return m_roots.size();
    }

    /// \brief Recalculates the roots of the trees. Must be called after
    /// changing the parent of at least one vertex.
    void updateRoots();

private:
    struct Vertex {
        int parent;
        std::vector<int> children;
    };

    std::vector<int> m_roots;
    std::vector<Vertex> m_vertices;
};

std::ostream &operator<<(std::ostream &, const Tree &);

#endif // TREE_HPP
