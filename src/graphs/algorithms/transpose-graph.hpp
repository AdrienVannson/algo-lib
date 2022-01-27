#ifndef TRANSPOSE_GRAPH_HPP
#define TRANSPOSE_GRAPH_HPP

template<class G>
G getTransposeGraph(const G &graph)
{
    G res(graph.verticeCount(), graph.isDirected());

    for (int vertex = 0; vertex < graph.verticeCount(); vertex++) {
        for (int neighbourPos = 0; neighbourPos < graph.neighbourCount(vertex);
             neighbourPos++) {
            res.addEdge(graph.neighbour(vertex, neighbourPos), vertex);
        }
    }

    return res;
}

#endif // TRANSPOSE_GRAPH_HPP
