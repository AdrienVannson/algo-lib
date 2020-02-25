#ifndef TRANSPOSEGRAPH_HPP
#define TRANSPOSEGRAPH_HPP

#include "global.hpp"


template<class G>
G getTransposeGraph (const G &graph)
{
    G res (graph.verticeCount(), graph.isDirected());

    for (int vertex=0; vertex<graph.verticeCount(); vertex++) {
        for (int neighbourPos=0; neighbourPos<graph.neighbourCount(vertex); neighbourPos++) {
            res.addEdge(graph.neighbour(vertex, neighbourPos), vertex);
        }
    }

    return res;
}


#endif // TRANSPOSEGRAPH_HPP
