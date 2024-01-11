#include "read-graph.hpp"

void read(Graph& graph, const bool is_directed, const bool indices_start_at_one,
    const int vertex_count, const int edges_count, std::istream& stream)
{
    graph.reset(vertex_count, is_directed);

    for (int i = 0; i < edges_count; i++) {
        int x, y;
        stream >> x >> y;

        if (indices_start_at_one) {
            x--, y--;
        }

        graph.addEdge(x, y);
    }
}

void read(Graph& graph, const bool is_directed, const bool indices_start_at_one,
    std::istream& stream)
{
    int vertex_count, edges_count;
    stream >> vertex_count >> edges_count;

    read(graph, is_directed, indices_start_at_one, vertex_count, edges_count, stream);
}
