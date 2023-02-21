#pragma once

#include "tree.hpp"

#include <vector>

/// \brief Converts a graph to a tree. Returns a pair containing:
/// - the tree
/// - the IDs of the edges in a vector: for each vertex v, the value contained
///   at the index v is the ID of the edge
template<class G>
std::pair<Tree, std::vector<int>> graphToTree(const G &g, const int root = 0)
{
    Tree tree(g.vertexCount(), root);
    std::vector<int> ids(g.vertexCount(), -1);

    std::vector<std::pair<int, int>> pending; // (vertex, parent)
    pending.push_back(std::make_pair(root, -1));

    while (pending.size()) {
        const int vertex = pending.back().first;
        const int parent = pending.back().second;
        pending.pop_back();

        for (auto edge : g.edgesToNeighbours(vertex)) {
            const int neighbour = edge.neighbour;

            if (neighbour != parent) {
                tree.setParent(neighbour, vertex);
                ids[neighbour] = edge.edgeId;

                pending.push_back(std::make_pair(neighbour, vertex));
            }
        }
    }

    return std::make_pair(tree, ids);
}
