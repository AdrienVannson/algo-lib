#include "algolib.hpp"

#include <climits>

/*******************************************************************************
 *** Data structures ***********************************************************
 ******************************************************************************/

void testMaxHeap ()
{
    MaxHeap<int> heap;
    priority_queue<int> pqueue;

    for (int i=0; i<10000; i++) {
        const int v = random() % 5000;
        heap.insert(v);
        pqueue.push(v);
    }

    while (pqueue.size() > 1000) {
        assert(heap.size() == (int)pqueue.size());
        assert(heap.max() == pqueue.top());
        heap.removeMax();
        pqueue.pop();
    }

    for (int i=0; i<10000; i++) {
        const int v = random();
        heap.insert(v);
        pqueue.push(v);
    }

    while (pqueue.size() > 0) {
        assert(heap.size() == (int)pqueue.size());
        assert(heap.max() == pqueue.top());
        heap.removeMax();
        pqueue.pop();
    }

    vector<int> vs;
    for (int i=0; i<10000; i++) {
        const int v = random() % 5000;
        vs.push_back(v);
        pqueue.push(v);
    }

    MaxHeap<int> heap2(vs);
    while (pqueue.size()) {
        assert(heap2.max() == pqueue.top());
        heap2.removeMax();
        pqueue.pop();
    }

    cerr << "### Max heap: OK" << endl;
}


/*******************************************************************************
 *** Graph algorithms **********************************************************
 ******************************************************************************/

void testBFS ()
{
    Graph graph (4, true);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);

    BFS<Graph> bfs (graph, 0);
    assert(bfs.distTo(0) == 0);
    assert(bfs.distTo(1) == INT_MAX);
    assert(bfs.distTo(2) == 1);
    assert(bfs.distTo(3) == 2);

    cerr << "### BFS: OK" << endl;
}

void testDijkstra ()
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

    cerr << "### Dijkstra: OK" << endl;
}

void testEdmondsKarp ()
{
    WGraph<int> graph(6, true);
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 3, 13);
    graph.addEdge(1, 3, 10);
    graph.addEdge(3, 1, 4);
    graph.addEdge(1, 2, 12);
    graph.addEdge(2, 3, 9);
    graph.addEdge(3, 4, 14);
    graph.addEdge(4, 2, 7);
    graph.addEdge(2, 5, 20);
    graph.addEdge(4, 5, 4);

    EdmondsKarp<WGraph<int>, int> flow(graph, 0, 5);

    assert(flow.maxFlow() == 23);
    assert(flow.flowOnEdge(5) == 0);
    assert(flow.flowOnEdge(0) == 12);
    assert(flow.flowOnEdge(1) == 11);
    assert(flow.flowOnEdge(9) == 4);
    assert(flow.flowOnEdge(7) == 7);

    cerr << "### Edmonds-Karp: OK" << endl;
}

void testMinCut ()
{
    WGraph<int> graph(6, true);
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 3, 13);
    graph.addEdge(1, 3, 10);
    graph.addEdge(3, 1, 4);
    graph.addEdge(1, 2, 12);
    graph.addEdge(2, 3, 9);
    graph.addEdge(3, 4, 14);
    graph.addEdge(4, 2, 7);
    graph.addEdge(2, 5, 20);
    graph.addEdge(4, 5, 4);

    EdmondsKarp<WGraph<int>, int> flow(graph, 0, 5);
    MinCut<EdmondsKarp<WGraph<int>, int>, WGraph<int>, int> minCut(flow, graph);

    assert(minCut.minCut() == 23);
    assert(minCut.cutEdges().size() == 3);
    assert(minCut.cutEdges()[0].edgeId == 4);
    assert(minCut.cutEdges()[1].edgeId == 7);
    assert(minCut.cutEdges()[2].edgeId == 9);

    cerr << "### Min-Cut: OK" << endl;
}

void testTarjan ()
{
    Graph graph(12, true);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 2);
    graph.addEdge(1, 4);
    graph.addEdge(4, 5);
    graph.addEdge(5, 6);
    graph.addEdge(6, 7);
    graph.addEdge(7, 5);
    graph.addEdge(6, 4);
    graph.addEdge(5, 3);
    graph.addEdge(4, 8);
    graph.addEdge(8, 9);
    graph.addEdge(9, 7);
    graph.addEdge(1, 10);
    graph.addEdge(10, 11);
    graph.addEdge(11, 1);
    graph.addEdge(11, 0);

    const Tarjan<Graph> tarjan (graph);
    const vector<vector<int>> ans {
        {0},
        {3, 2},
        {9, 8, 7, 6, 5, 4},
        {11, 10, 1}
    };

    assert(tarjan.sccs() == ans);

    cerr << "### Tarjan: OK" << endl;
}


/*******************************************************************************
 *** Sorting *******************************************************************
 ******************************************************************************/

void testSorting ()
{
    vector<int> sorted;
    for (int i=0; i<10000; i++) {
        sorted.push_back(rand() % 10000);
    }
    const vector<int> original = sorted;
    sort(sorted.begin(), sorted.end());

    vector<int> vs;

    // Merge sort
    vs = original;
    vs = mergeSort(vs);
    assert(vs == sorted);
    cerr << "### Merge sort: OK" << endl;
}


/*******************************************************************************
 *** Maths *********************************************************************
 ******************************************************************************/

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

void testPermutation ()
{
    const Permutation perm (vector<int>{5, 1, 3, 0, 4, 2, 7, 6});

    // Inverse
    assert(perm * perm.inverse() == Permutation(perm.size()));

    // Orbit
    const vector<int> orbit = perm.orbit(3);
    assert(orbit.size() == 4);
    assert(orbit[0] == 3 && orbit[1] == 0 && orbit[2] == 5 && orbit[3] == 2);

    assert(Permutation(4, 1, 2).orbit(2).size() == 2);
    assert(Permutation(4, 1, 2).orbit(2)[0] == 2);
    assert(Permutation(4, 1, 2).orbit(2)[1] == 1);

    // Orbits
    const vector<vector<int>> orbits = perm.orbits();
    assert(orbits.size() == 4);

    assert(orbits[0].size() == 4);
    assert(orbits[0][0] == 0 && orbits[0][1] == 5 && orbits[0][2] == 2 && orbits[0][3] == 3);

    assert(orbits[1].size() == 1 && orbits[1][0] == 1);
    assert(orbits[2].size() == 1 && orbits[2][0] == 4);

    assert(orbits[3].size() == 2);
    assert(orbits[3][0] == 6 && orbits[3][1] == 7);

    // Composition
    const Permutation perm2 = Permutation(vector<int>{2, 0, 1}) * Permutation(vector<int>{1, 0, 2});
    assert(perm2(0) == 0 && perm2(1) == 2 && perm2(2) == 1);

    // Signature
    assert(Permutation({2, 3, 4, 1, 0}).signature() == -1);
    assert(Permutation({2, 0, 4, 1, 3}).signature() == 1);

    // Transposition decomposition
    vector<Permutation> decomposition = perm.transpositionsDecomposition();
    Permutation res (perm.size());
    while (decomposition.size()) {
        res = decomposition.back() * res;
        decomposition.pop_back();
    }
    assert(res == perm);

    cerr << "### Permutation: OK" << endl;
}


/*******************************************************************************
 *** Other *********************************************************************
 ******************************************************************************/

void testInfinity ()
{
    assert(infinity<int>() == 2147483647);

    cerr << "### Infinity: OK" << endl;
}


/*******************************************************************************
 *** Main  *********************************************************************
 ******************************************************************************/

int main ()
{
    srand(42);

    // Data structures
    cerr << "Testing data structures..." << endl;
    testMaxHeap();
    cerr << "\n";

    // Graphs
    cerr << "Testing graphs..." << endl;
    testBFS();
    testDijkstra();
    testEdmondsKarp();
    testMinCut();
    testTarjan();
    cerr << "\n";

    // Sorting algorithms
    cerr << "Testing sorting algorithms..." << endl;
    testSorting();
    cerr << "\n";

    // Maths
    cerr << "Testing maths..." << endl;
    testerExponentiationRapide();
    testerFraction();
    checkGCD_LCM();
    testPermutation();
    cerr << "\n";

    // Other
    cerr << "Testing other functionalities..." << endl;
    testInfinity();
    cerr << "\n";
}
