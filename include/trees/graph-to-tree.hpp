#ifndef GRAPHTOTREE_HPP
#define GRAPHTOTREE_HPP

#include "Tree.hpp"

#include <vector>

template<class G>
Tree graphToTree(const G &g, const int root = 0)
{
    Tree tree(g.verticeCount(), root);

    std::vector<std::pair<int,int>> pending; // (vertex, parent)
    pending.push_back(std::make_pair(root, -1));

    while (pending.size()) {
        const int vertex = pending.back().first;
        const int parent = pending.back().second;
        pending.pop_back();

        tree.setParent(vertex, parent);

        for (int neighbour : g.neighbours(vertex)) {
            if (neighbour != parent) {
                pending.push_back(std::make_pair(neighbour, vertex));
            }
        }
    }

    return tree;
}

#endif // GRAPHTOTREE_HPP
