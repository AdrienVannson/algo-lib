#include "Tree.hpp"

#include <algorithm>
#include <cassert>

Tree::Tree() : m_root(0) {}

Tree::Tree(const int vertexCount, const int root) : m_root(root)
{
    m_vertices.resize(vertexCount, Vertex {-1, std::vector<int>()});
}

void Tree::setParent(const int vertex, const int newParent)
{
    if (m_vertices[vertex].parent != -1) {
        Vertex &p = m_vertices[m_vertices[vertex].parent];

        const auto it = std::find(p.children.begin(), p.children.end(), vertex);
        assert(it != p.children.end());

        p.children.erase(it);
    }

    if (newParent != -1) {
        m_vertices[newParent].children.push_back(vertex);
    }

    m_vertices[vertex].parent = newParent;
}

void printSubtree(
    std::ostream &os, const Tree &tree, const int vertex, const int depth)
{
    for (int i = 0; i < depth; i++) {
        os << "| ";
    }
    os << vertex << "\n";

    for (int child : tree.children(vertex)) {
        printSubtree(os, tree, child, depth + 1);
    }
}

std::ostream &operator<<(std::ostream &os, const Tree &tree)
{
    printSubtree(os, tree, tree.root(), 0);
    return os;
}
