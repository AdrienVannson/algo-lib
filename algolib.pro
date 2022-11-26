TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
        src/algolib.hpp \
        src/constants.hpp \
        src/data-structures/DisjointSet.hpp \
        src/data-structures/MaxHeap.hpp \
        src/geometry/convex-hull.hpp \
        src/geometry/intersections.hpp \
        src/geometry/line.hpp \
        src/geometry/polygon.hpp \
        src/geometry/projections.hpp \
        src/geometry/segment.hpp \
        src/geometry/shape.hpp \
        src/geometry/vect2.hpp \
        src/geometry/vect3.hpp \
        src/graphs/algorithms/bellman-ford.hpp \
        src/graphs/algorithms/bfs.hpp \
        src/graphs/algorithms/dijkstra.hpp \
        src/graphs/algorithms/edmonds-karp.hpp \
        src/graphs/algorithms/floyd-warshall.hpp \
        src/graphs/algorithms/kosaraju.hpp \
        src/graphs/algorithms/kruskal.hpp \
        src/graphs/algorithms/min-cut.hpp \
        src/graphs/algorithms/prim.hpp \
        src/graphs/algorithms/tarjan.hpp \
        src/graphs/algorithms/to-bipartite.hpp \
        src/graphs/algorithms/topological-sort.hpp \
        src/graphs/data-structures/Graph.hpp \
        src/graphs/data-structures/WGraph.hpp \
        src/json.hpp \
        src/maths/Permutation.hpp \
        src/maths/Fraction.hpp \
        src/global.hpp \
        src/maths/Polynomial.hpp \
        src/maths/exponentiation-by-squaring.hpp \
        src/maths/gcd-lcm.hpp \
        src/maths/modulo.hpp \
        src/maths/prime-decomposition.hpp \
        src/maths/sieve-of-eratosthenes.hpp \
        src/simplex.hpp \
        src/sorting/merge-sort.hpp \
        src/strings/automaton.hpp \
        src/strings/kmp.hpp \
        src/strings/regex.hpp \
        src/strings/utility/split.hpp \
        src/trees/Tree.hpp \
        src/trees/graph-to-forest.hpp \
        src/trees/graph-to-tree.hpp \
        src/two-sat.hpp \
        tests/geometry/test-intersections.hpp \
        tests/geometry/test-projections.hpp \
        tests/maths/test-modulo.hpp \
        tests/maths/test-prime-decomposition.hpp \
        tests/maths/test-sieve-of-eratosthenes.hpp \
        tests/other/test-two-sat.hpp \
        tests/strings/test-utility.hpp \
        tests/test-done.hpp

SOURCES += \
    src/json.cpp \
    src/maths/Permutation.cpp \
    src/maths/gcd-lcm.cpp \
    src/maths/prime-decomposition.cpp \
    src/maths/sieve-of-eratosthenes.cpp \
    src/simplex.cpp \
    src/strings/utility/split.cpp \
    src/trees/Tree.cpp \
    tests/geometry/test-intersections.cpp \
    tests/geometry/test-projections.cpp \
    tests/main.cpp \
    tests/maths/test-modulo.cpp \
    tests/maths/test-prime-decomposition.cpp \
    tests/maths/test-sieve-of-eratosthenes.cpp \
    tests/other/test-two-sat.cpp \
    tests/strings/test-utility.cpp \
    tests/test-done.cpp

INCLUDEPATH += src tests
