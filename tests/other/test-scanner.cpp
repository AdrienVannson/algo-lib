#include <cassert>
#include <sstream>
#include <utility>
#include <vector>

#include "graphs/data-structures/graph.hpp"
#include "graphs/data-structures/wgraph.hpp"
#include "test-scanner.hpp"
#include "scanner.hpp"
#include "test-done.hpp"

using namespace std;

void test_scanner()
{
    istringstream buff(
        "3\n"
        "12 25\n"
        "3\n"
        "0 1 2 3 4 5\n"
        "0 1 2 3 4 5\n"
        "1 2 5\n"
        "3 2\n"
        "1 2 2 3\n"
        "3 2\n"
        "1 2 10 2 3 7\n"
    );

    long long x;
    read(x, buff);
    assert(x == 3);

    pair<int, int> p;
    read(p, buff);
    assert(p.first == 12 && p.second == 25);

    vector<pair<int, int>> vec;
    read(vec, buff);
    assert(vec.size() == 3);
    assert(vec[0].first == 0 && vec[0].second == 1);
    assert(vec[1].first == 2 && vec[1].second == 3);
    assert(vec[2].first == 4 && vec[2].second == 5);

    vec.clear();
    read(vec, 3, buff);
    assert(vec.size() == 3);
    assert(vec[0].first == 0 && vec[0].second == 1);
    assert(vec[1].first == 2 && vec[1].second == 3);
    assert(vec[2].first == 4 && vec[2].second == 5);

    array<int, 3> arr;
    read<int, 3>(arr, buff);
    assert(arr[0] == 1 && arr[1] == 2 && arr[2] == 5);

    Graph graph;
    read(graph, true, true, buff);
    assert(graph.isDirected());
    assert(graph.vertexCount() == 3 && graph.edgeCount() == 2);
    assert(graph.neighbours(0) == vector<int>{1});

    WGraph<int> wgraph;
    read(wgraph, true, true, buff);
    assert(wgraph.isDirected());
    assert(wgraph.vertexCount() == 3 && wgraph.edgeCount() == 2);
    assert(wgraph.weight(wgraph.edgeIdTo(0, 1)) == 10);
    assert(wgraph.weight(wgraph.edgeIdTo(1, 2)) == 7);

    show_test_done("Scanner");
}
