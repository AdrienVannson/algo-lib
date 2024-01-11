#pragma once

#include <iostream>

#include "graphs/data-structures/graph.hpp"

// Read a graph from an istream
void read(Graph& graph, const bool is_directed, const bool indices_start_at_one,
    const int vertex_count, const int edges_count, std::istream& stream = std::cin);

void read(Graph& graph, const bool is_directed, const bool indices_start_at_one,
    std::istream& stream = std::cin);
