#ifndef PRIM_HPP
#define PRIM_HPP

#include <queue>
#include <vector>

template<class G>
class Prim
{
public:
    Prim(const G &g) : m_sum(0)
    {
        assert(!g.isDirected());

        std::vector<bool> isVisited(g.verticeCount(), false);

        auto cmp = [&g](const typename G::Edge &a, const typename G::Edge &b) {
            return g.weight(a.edgeId) > g.weight(b.edgeId);
        };
        std::priority_queue<
            typename G::Edge, std::vector<typename G::Edge>,
            decltype(cmp)>
            pending(cmp); // The first vertex is the one already visited

        int nextVertice = getNextVertice(isVisited);

        while (nextVertice != -1) {
            pending.push(typename G::Edge {-1, nextVertice, -1});

            while (pending.size()) {
                auto edge = pending.top();
                pending.pop();

                if (isVisited[edge.vertex2]) continue;
                isVisited[edge.vertex2] = true;

                if (edge.vertex1 != -1) {
                    m_edges.push_back(edge);
                    m_sum += g.weight(edge.edgeId);
                }

                for (const auto edgeTo : g.edgesToNeighbours(edge.vertex2)) {
                    if (!isVisited[edgeTo.neighbour]) {
                        pending.push(typename G::Edge {
                            edge.vertex2, edgeTo.neighbour, edgeTo.edgeId});
                    }
                }
            }

            nextVertice = getNextVertice(isVisited);
        }
    }

    /// \brief Edges of a minimum spanning forest
    const std::vector<typename G::Edge> &edges() const { return m_edges; }

    /// \brief Number of edges of a minimum spanning forest
    int edgeCount() const { return m_edges.size(); }

    /// \brief Sum of the weights of the edges of a minimum spanning forest
    typename G::Weight sum() const { return m_sum; }

private:
    std::vector<typename G::Edge> m_edges; // Edges of the minimum spanning forest
    typename G::Weight m_sum; // Sum of their weights

    int getNextVertice(const std::vector<bool> &isVisited)
    {
        for (int i = 0; i < (int)isVisited.size(); i++) {
            if (!isVisited[i]) return i;
        }
        return -1;
    }
};

#endif // PRIM_HPP
