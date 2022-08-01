#ifndef GRAPHTOFOREST_HPP
#define GRAPHTOFOREST_HPP

#include "Tree.hpp"

#include <vector>

/// \brief Converts a graph to a forest. Returns a pair containing:
/// - the forest
/// - the IDs of the edges in a vector: for each vertex v, the value contained
///   at the index v is the ID of the edge connecting v to its parent in the
///   graph (or -1 if the vertex is a root)
template<class G>
std::pair<Tree, std::vector<int>> graphToForest(const G &g)
{
    Tree forest(g.vertexCount());
    std::vector<int> ids(g.vertexCount(), -1);

    std::vector<bool> isVisited(g.vertexCount(), false);

    for (int root = 0; root < g.vertexCount(); root++) {
        if (isVisited[root]) continue;

        std::vector<std::pair<int, int>> pending; // (vertex, parent)
        pending.push_back(std::make_pair(root, -1));

        while (pending.size()) {
            const int vertex = pending.back().first;
            const int parent = pending.back().second;
            pending.pop_back();

            for (auto edge : g.edgesToNeighbours(vertex)) {
                const int neighbour = edge.neighbour;

                if (neighbour != parent) {
                    isVisited[neighbour] = true;
                    forest.setParent(neighbour, vertex);
                    ids[neighbour] = edge.edgeId;

                    pending.push_back(std::make_pair(neighbour, vertex));
                }
            }
        }
    }

    forest.updateRoots();

    return std::make_pair(forest, ids);
}

#endif // GRAPHTOFOREST_HPP
