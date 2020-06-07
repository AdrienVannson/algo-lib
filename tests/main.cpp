#include "algolib.hpp"


// Graphs
void checkBFS ()
{
    Graph graph (4, true);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);

    BFS<Graph> bfs (graph, 0);
    assert(bfs.distTo(0) == 0);
    assert(bfs.distTo(1) == +oo);
    assert(bfs.distTo(2) == 1);
    assert(bfs.distTo(3) == 2);

    cerr << "BFS checked" << endl;
}

void checkDijkstra ()
{
    WGraph<int> graph (4, true);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 3, 3);

    Dijkstra<WGraph<int>, int> dijkstra (graph, 0);
    assert(dijkstra.distTo(0) == 0);
    assert(dijkstra.distTo(1) == +oo);
    assert(dijkstra.distTo(2) == 1);
    assert(dijkstra.distTo(3) == 4);

    cerr << "Dijkstra checked" << endl;
}


// Maths
void testerExponentiationRapide ()
{
    assert(getPuissance(2, 7) == 128);
}

void testerFraction ()
{
    const Fraction<int> a(3, 4), b(1, 3);
    const Fraction<int> r = a - b;

    assert(r.num() == 5 && r.den() == 12);
}

void checkGCD_LCM ()
{
    assert(getGCD(42, 13*14) == 14);
    assert(getGCD(42, -13*14) == 14);
    assert(getGCD(0, 0) == 0);
    assert(getGCD(0, 42) == 42);

    array<long long,3> res;

    res = getGCDBezout(42, 13*14);
    assert(res[0] == 14 && 42*res[1]+13*14*res[2] == res[0]);

    res = getGCDBezout(42, -13*14);
    assert(res[0] == 14 && 42*res[1]-13*14*res[2] == res[0]);

    res = getGCDBezout(0, 0);
    assert(res[0] == 0);

    res = getGCDBezout(0, 42);
    assert(res[0] == 42 && 42*res[2] == res[0]);

    assert(getLCM(2*7, 2*13) == 2*7*13);
    assert(getLCM(2*7, -2*13) == 2*7*13);
    cerr << "GCD / LCM checked" << endl;
}


int main ()
{
    // Graphs
    checkBFS();
    checkDijkstra();

    // Maths
    testerExponentiationRapide();
    testerFraction();
    checkGCD_LCM();
}
