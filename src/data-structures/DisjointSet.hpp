#ifndef DISJOINTSET_HPP
#define DISJOINTSET_HPP

#include <cassert>
#include <vector>

class DisjointSet
{
public:
    DisjointSet(const int nodeCount)
    {
        nodes.reserve(nodeCount);
        for (int i = 0; i < nodeCount; i++) {
            nodes.push_back(Node {i, 1});
        }
    }

    /// \brief The root of the tree containing the node
    int find(const int node) const
    {
        if (nodes[node].parent == node) {
            return node;
        }
        return nodes[node].parent = find(nodes[node].parent);
    }

    /// \brief Total number of nodes
    int size() const
    {
        return nodes.size();
    }

    /// \brief Size of the subtree containing a node
    int size(const int node)
    {
        return nodes[find(node)].size;
    }

    /// \brief Merge two components
    void merge(int node1, int node2)
    {
        node1 = find(node1);
        node2 = find(node2);

        if (node1 == node2) return;

        if (nodes[node2].size > nodes[node1].size) {
            std::swap(node1, node2);
        }

        nodes[node1].size += nodes[node2].size;
        nodes[node2].parent = node1;
    }

private:
    struct Node {
        int parent;
        int size;
    };
    mutable std::vector<Node> nodes;
};

#endif // DISJOINTSET_HPP
