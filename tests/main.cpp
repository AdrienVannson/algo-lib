#include "algolib.hpp"

#include "maths/modulo.hpp"
#include "geometry/primitives.hpp"

#include <bits/stdc++.h>
using namespace std;

/*******************************************************************************
 *** Data structures ***********************************************************
 ******************************************************************************/

void testDisjointSet()
{
    DisjointSet ds(5);

    assert(ds.size() == 5);
    assert(ds.find(3) == 3);

    ds.merge(0, 1);
    assert(ds.size(0) == 2);

    ds.merge(1, 2);
    assert(ds.size(0) == 3);
    assert(ds.find(0) == ds.find(1));

    cerr << "### Disjoint set: OK" << endl;
}

void testMaxHeap()
{
    MaxHeap<int> heap;
    priority_queue<int> pqueue;

    for (int i = 0; i < 10000; i++) {
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

    for (int i = 0; i < 10000; i++) {
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
    for (int i = 0; i < 10000; i++) {
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

void testBellmanFord()
{
    {
        WGraph<int> graph(4, true);
        graph.addEdge(0, 2, 1);
        graph.addEdge(1, 2, 1);
        graph.addEdge(2, 0, 1);
        graph.addEdge(2, 3, 5);
        graph.addEdge(2, 3, 3);

        BellmanFord<WGraph<int>> bellmanFord(graph, 0);
        assert(bellmanFord.distTo(0) == 0);
        assert(bellmanFord.distTo(1) == Constants<int>::infinity());
        assert(bellmanFord.distTo(2) == 1);
        assert(bellmanFord.distTo(3) == 4);
    }

    {
        WGraph<int> graph(7, true);
        graph.addEdge(0, 1, 3);
        graph.addEdge(0, 3, 10000);
        graph.addEdge(3, 4, 1);
        graph.addEdge(4, 5, 1);
        graph.addEdge(5, 6, 1);
        graph.addEdge(6, 3, -4);

        BellmanFord<WGraph<int>> bellmanFord(graph, 0);

        assert(bellmanFord.distTo(0) == 0);
        assert(bellmanFord.distTo(1) == 3);
        assert(bellmanFord.distTo(2) == Constants<int>::infinity());
        assert(bellmanFord.distTo(3) == -Constants<int>::infinity());
        assert(bellmanFord.distTo(4) == -Constants<int>::infinity());
        assert(bellmanFord.distTo(5) == -Constants<int>::infinity());
        assert(bellmanFord.distTo(6) == -Constants<int>::infinity());
    }

    cerr << "### Bellman-Ford: OK" << endl;
}

void testBFS()
{
    Graph graph(4, true);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);

    BFS<Graph> bfs(graph, 0);
    assert(bfs.distTo(0) == 0);
    assert(bfs.distTo(1) == INT_MAX);
    assert(bfs.distTo(2) == 1);
    assert(bfs.distTo(3) == 2);

    cerr << "### BFS: OK" << endl;
}

void testDijkstra()
{
    WGraph<int> graph(4, true);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 3, 3);

    Dijkstra<WGraph<int>> dijkstra(graph, 0);
    assert(dijkstra.distTo(0) == 0);
    assert(dijkstra.distTo(1) == Constants<int>::infinity());
    assert(dijkstra.distTo(2) == 1);
    assert(dijkstra.distTo(3) == 4);

    cerr << "### Dijkstra: OK" << endl;
}

void testEdmondsKarp()
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

    EdmondsKarp<WGraph<int>> flow(graph, 0, 5);

    assert(flow.maxFlow() == 23);
    assert(flow.flowOnEdge(5) == 0);
    assert(flow.flowOnEdge(0) == 12);
    assert(flow.flowOnEdge(1) == 11);
    assert(flow.flowOnEdge(9) == 4);
    assert(flow.flowOnEdge(7) == 7);

    cerr << "### Edmonds-Karp: OK" << endl;
}

void testFloydWarshall()
{
    WGraph<int> graph(4, true);
    graph.addEdge(0, 2, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 0, 1);
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 3, 3);

    FloydWarshall<WGraph<int>> fw(graph);
    assert(fw.dist(0, 0) == 0);
    assert(fw.dist(0, 1) == Constants<int>::infinity());
    assert(fw.dist(0, 2) == 1);
    assert(fw.dist(0, 3) == 4);

    cerr << "### Floyd-Warshall: OK" << endl;
}

void testKosaraju()
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

    const Kosaraju<Graph> kosaraju(graph);
    const vector<vector<int>> ans {{1, 11, 10}, {4, 6, 5, 7, 9, 8}, {2, 3}, {0}};

    assert(kosaraju.sccCount() == 4);
    assert(kosaraju.sccs() == ans);

    for (int i = 0; i < (int)kosaraju.sccCount(); i++) {
        for (int v : kosaraju.sccs()[i]) {
            assert(kosaraju.scc(v) == i);
        }
    }

    cerr << "### Kosaraju: OK" << endl;
}

void testKruskal()
{
    WGraph<int> g(7, false);

    vector<array<int, 3>> edges
        = {{0, 1, 3}, {0, 2, 2}, {0, 3, 3}, {1, 2, 1}, {1, 3, 5}, {1, 4, 3},
           {2, 3, 5}, {2, 5, 2}, {3, 5, 4}, {4, 5, 5}, {5, 6, 9}};
    for (auto e : edges)
        g.addEdge(e[0], e[1], e[2]);

    Kruskal<WGraph<int>> kruskal(g);
    assert(kruskal.edgeCount() == 6);
    assert(kruskal.sum() == 20);

    vector<int> spanningForest;
    for (auto e : kruskal.edges()) {
        spanningForest.push_back(e.edgeId);
    }
    sort(spanningForest.begin(), spanningForest.end());

    assert(spanningForest == (vector<int> {1, 2, 3, 5, 7, 10}));

    cerr << "### Kruskal: OK" << endl;
}

void testMinCut()
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

    EdmondsKarp<WGraph<int>> flow(graph, 0, 5);
    MinCut<EdmondsKarp<WGraph<int>>, WGraph<int>> minCut(flow, graph);

    assert(minCut.minCut() == 23);
    assert(minCut.cutEdges().size() == 3);
    assert(minCut.cutEdges()[0].edgeId == 4);
    assert(minCut.cutEdges()[1].edgeId == 7);
    assert(minCut.cutEdges()[2].edgeId == 9);

    cerr << "### Min-Cut: OK" << endl;
}

void testPrim()
{
    WGraph<int> g(7, false);

    vector<array<int, 3>> edges
        = {{0, 1, 3}, {0, 2, 2}, {0, 3, 3}, {1, 2, 1}, {1, 3, 5}, {1, 4, 3},
           {2, 3, 5}, {2, 5, 2}, {3, 5, 4}, {4, 5, 5}, {5, 6, 9}};
    for (auto e : edges)
        g.addEdge(e[0], e[1], e[2]);

    Prim<WGraph<int>> prim(g);
    assert(prim.edgeCount() == 6);
    assert(prim.sum() == 20);

    vector<int> spanningForest;
    for (auto e : prim.edges()) {
        spanningForest.push_back(e.edgeId);
    }
    sort(spanningForest.begin(), spanningForest.end());

    assert(spanningForest == (vector<int> {1, 2, 3, 5, 7, 10}));

    cerr << "### Prim: OK" << endl;
}

void testTarjan()
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

    const Tarjan<Graph> tarjan(graph);
    const vector<vector<int>> ans {{0}, {3, 2}, {9, 8, 7, 6, 5, 4}, {11, 10, 1}};

    assert(tarjan.sccCount() == 4);
    assert(tarjan.sccs() == ans);

    for (int i = 0; i < (int)tarjan.sccCount(); i++) {
        for (int v : tarjan.sccs()[i]) {
            assert(tarjan.scc(v) == i);
        }
    }

    cerr << "### Tarjan: OK" << endl;
}

void testTopologicalSort()
{
    TopologicalSort<Graph> ts(Graph(0, true));
    assert(ts.isPossible() && ts.topologicalSort().size() == 0);

    Graph g(10, true);
    vector<array<int, 2>> edges
        = {{1, 2}, {1, 8}, {2, 3}, {2, 8}, {3, 6}, {4, 3}, {4, 5}, {5, 6}, {9, 8}};
    for (auto e : edges)
        g.addEdge(e[0], e[1]);

    ts = TopologicalSort<Graph>(g);
    assert(ts.topologicalSort() == vector<int>({9, 7, 4, 5, 1, 2, 8, 3, 6, 0}));

    cerr << "### Topological sort: OK" << endl;
}

/*******************************************************************************
 *** Trees *********************************************************************
 ******************************************************************************/

void testGraphToTree()
{
    Graph g(6, false);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 5);

    Tree t = graphToTree(g, 1);
    assert(t.verticeCount() == 6);
    assert(t.parent(0) == 1);
    assert(t.parent(1) == -1);
    assert(t.parent(2) == 1);
    assert(t.parent(3) == 1);
    assert(t.parent(4) == 2);
    assert(t.parent(5) == 4);
    assert(t.children(1) == vector<int>({3, 2, 0}));

    cerr << "### Graph to tree: OK" << endl;
}

/*******************************************************************************
 *** Sorting *******************************************************************
 ******************************************************************************/

void testSorting()
{
    vector<int> sorted;
    for (int i = 0; i < 10000; i++) {
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

void testExponentiationBySquaring()
{
    for (int p = 1; p < 30; p++) {
        assert(getPower(2, p) == (1 << p));
    }

    cerr << "### Exponentiation by squaring: OK" << endl;
}

void testerFraction()
{
    const Fraction<int> a(3, 4), b(1, 3);
    const Fraction<int> r = a - b;

    assert(r.num() == 5 && r.den() == 12);
}

void checkGCD_LCM()
{
    assert(getGCD(42, 13 * 14) == 14);
    assert(getGCD(42, -13 * 14) == 14);
    assert(getGCD(0, 0) == 0);
    assert(getGCD(0, 42) == 42);

    array<long long, 3> res;

    res = getGCDBezout(42, 13 * 14);
    assert(res[0] == 14 && 42 * res[1] + 13 * 14 * res[2] == res[0]);

    res = getGCDBezout(42, -13 * 14);
    assert(res[0] == 14 && 42 * res[1] - 13 * 14 * res[2] == res[0]);

    res = getGCDBezout(0, 0);
    assert(res[0] == 0);

    res = getGCDBezout(0, 42);
    assert(res[0] == 42 && 42 * res[2] == res[0]);

    assert(getLCM(2 * 7, 2 * 13) == 2 * 7 * 13);
    assert(getLCM(2 * 7, -2 * 13) == 2 * 7 * 13);
    cerr << "GCD / LCM checked" << endl;
}

void testPermutation()
{
    const Permutation perm(vector<int> {5, 1, 3, 0, 4, 2, 7, 6});

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
    assert(
        orbits[0][0] == 0 && orbits[0][1] == 5 && orbits[0][2] == 2 && orbits[0][3] == 3);

    assert(orbits[1].size() == 1 && orbits[1][0] == 1);
    assert(orbits[2].size() == 1 && orbits[2][0] == 4);

    assert(orbits[3].size() == 2);
    assert(orbits[3][0] == 6 && orbits[3][1] == 7);

    // Composition
    const Permutation perm2
        = Permutation(vector<int> {2, 0, 1}) * Permutation(vector<int> {1, 0, 2});
    assert(perm2(0) == 0 && perm2(1) == 2 && perm2(2) == 1);

    // Signature
    assert(Permutation({2, 3, 4, 1, 0}).signature() == -1);
    assert(Permutation({2, 0, 4, 1, 3}).signature() == 1);

    // Transposition decomposition
    vector<Permutation> decomposition = perm.transpositionsDecomposition();
    Permutation res(perm.size());
    while (decomposition.size()) {
        res = decomposition.back() * res;
        decomposition.pop_back();
    }
    assert(res == perm);

    cerr << "### Permutation: OK" << endl;
}

void testPolynomial()
{
    Polynomial<int> P({-3, 1});
    Polynomial<int> Q({5, -3, 1});

    assert(P == P);
    assert(((P + Q) == Polynomial<int>({2, -2, 1})));
    assert(((P * Q) == Polynomial<int>({-15, 14, -6, 1})));

    // Lagrange polynomial
    std::vector<std::pair<Fraction<int>, Fraction<int>>> points {
        make_pair(0, -2), make_pair(1, 2), make_pair(2, 8)};
    assert(lagrangePolynomial(points) == Polynomial<Fraction<int>>({-2, 3, 1}));

    cerr << "### Polynomial: OK" << endl;
}

/*******************************************************************************
 *** Geometry ******************************************************************
 ******************************************************************************/

void testVect2()
{
    Vect2<int> u(1, 2), v(3, 4);
    assert((u ^ v) == -2);

    cerr << "### Vect2: OK" << endl;
}

void testConvexHull()
{
    const vector<Vect2<int>> points
        = {Vect2<int>(0, 0), Vect2<int>(0, 1), Vect2<int>(0, 2),
           Vect2<int>(1, 0), Vect2<int>(1, 1), Vect2<int>(1, 2),
           Vect2<int>(2, 0), Vect2<int>(2, 1), Vect2<int>(2, 2)};

    ConvexHull<int> convexHull(points);
    assert(convexHull.verticeIds().size() == 4);
    assert(convexHull.verticeIds()[0] == 6);
    assert(convexHull.verticeIds()[1] == 8);
    assert(convexHull.verticeIds()[2] == 2);
    assert(convexHull.verticeIds()[3] == 0);

    cerr << "### Convex hull: OK" << endl;
}

/*******************************************************************************
 *** Strings *******************************************************************
 ******************************************************************************/

void testAutomaton()
{
    // Automaton testing if a number is a multiple of 3
    {
        Aut aut;
        aut.addState(true, true);
        aut.addState(false, false);
        aut.addState(false, false);
        for (int s = 0; s < 3; s++) {
            for (int d = 0; d <= 9; d++) {
                aut.addTransition(s, '0' + d, (s + d) % 3);
            }
        }

        assert(aut.isAccepted({'1', '3', '8', '4', '2'}));
        assert(!aut.isAccepted({'1', '3', '7', '4', '2'}));
        assert(!aut.isAccepted({'1', '3', '6', '4', '2'}));
        assert(aut.isAccepted({'1', '3', '5', '4', '2'}));

        assert(aut.isComplete());
        assert(!aut.isComplete({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'X'}));
    }

    // De Bruijn automaton
    {
        Reg *reg = Reg::concatenation(
            Reg::kleenStar(Reg::alternation(Reg::character('0'), Reg::character('1'))),
            Reg::concatenation(
                Reg::character('1'),
                Reg::concatenation(
                    Reg::alternation(Reg::character('0'), Reg::character('1')),
                    Reg::alternation(Reg::character('0'), Reg::character('1')))));

        Aut aut = Aut::fromRegex(reg);

        assert(aut.alphabet().size() == 2);
        assert(aut.alphabet()[0] == '0' && aut.alphabet()[1] == '1');

        aut.determinize();
        aut.minimize();

        assert(aut.isComplete());
        assert(!aut.isComplete({'0', '1', '2'}));

        for (int x = 0; x < 256; x++) {
            vector<char> v;
            for (int i = 7; i >= 0; i--) {
                v.push_back(x & (1 << i) ? '1' : '0');
            }
            assert(aut.isAccepted(v) == ((x & 4) != 0));
        }

        delete reg;
    }

    // (a+b) b^* a
    {
        Aut aut;
        aut.addState(true, false);
        aut.addState(false, false);
        aut.addState(false, false);
        aut.addState(false, true);

        aut.addTransition(0, 'a', 1);
        aut.addTransition(0, 'b', 2);
        aut.addTransition(1, 'b', 2);
        aut.addTransition(2, 'b', 1);
        aut.addTransition(1, 'a', 3);
        aut.addTransition(2, 'a', 3);

        aut.minimize();

        assert(!aut.isComplete());
        assert(aut.stateCount() == 3);
    }

    // a+b
    {
        Aut aut;

        aut.addState(true, false);
        aut.addState(false, true);
        aut.addState(false, true);
        aut.addTransition(0, 'a', 1);
        aut.addTransition(0, 'b', 2);

        aut.addState(false, false); // Useless states
        aut.addState(false, true);
        aut.addTransition(3, 'z', 4);

        aut.minimize();

        assert(aut.stateCount() == 2);
    }

    cerr << "### Automaton: OK" << endl;
}

void testKmp()
{
    const vector<int> kmp = getKmp("ababc#abababcd");
    assert(kmp == vector<int>({-1, 0, 0, 1, 2, 0, 0, 1, 2, 3, 4, 3, 4, 5, 0}));

    cerr << "### KMP: OK" << endl;
}

/*******************************************************************************
 *** Other *********************************************************************
 ******************************************************************************/

void testInfinity()
{
    assert(Constants<int>::infinity() == 2147483647);

    cerr << "### Infinity: OK" << endl;
}

/*******************************************************************************
 *** Main  *********************************************************************
 ******************************************************************************/

int main()
{
    srand(42);

    // Data structures
    cerr << "Testing data structures..." << endl;
    testDisjointSet();
    testMaxHeap();
    cerr << "\n";

    // Graphs
    cerr << "Testing graphs..." << endl;
    testBellmanFord();
    testBFS();
    testDijkstra();
    testEdmondsKarp();
    testFloydWarshall();
    testKosaraju();
    testKruskal();
    testMinCut();
    testPrim();
    testTarjan();
    testTopologicalSort();
    cerr << "\n";

    // Trees
    cerr << "Testing trees..." << endl;
    testGraphToTree();
    cerr << "\n";

    // Sorting algorithms
    cerr << "Testing sorting algorithms..." << endl;
    testSorting();
    cerr << "\n";

    // Maths
    cerr << "Testing maths..." << endl;
    testExponentiationBySquaring();
    testerFraction();
    checkGCD_LCM();
    testPermutation();
    testPolynomial();
    testModulo();
    cerr << "\n";

    // Geometry
    cerr << "Testing geometry..." << endl;
    testVect2();
    testConvexHull();
    testIntersection();
    cerr << "\n";

    // Strings
    cerr << "Testing strings..." << endl;
    testAutomaton();
    testKmp();
    cerr << "\n";

    // Other
    cerr << "Testing other functionalities..." << endl;
    testInfinity();
    cerr << "\n";
}
