#include <random>
#include <vector>

#include "optimization/simulated-annealing.hpp"
#include "geometry/vect2.hpp"
#include "shortcuts.hpp"
#include "test-done.hpp"

std::vector<Vect2d> POINTS;

struct Solution {
    // Permutation of the points to visit (in order of visit)
    std::vector<int> perm;

    Solution() {
        for_n(i, POINTS.size()) {
            perm.push_back(i);
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(perm.begin(), perm.end(), g);
    }

    Solution randomNeighbor() const {
        Solution res = *this;

        const int i = rand() % (perm.size() - 2);
        const int j = rand() % (perm.size() - i - 1) + i + 1;

        std::reverse(res.perm.begin() + i, res.perm.begin() + j);

        return res;
    }

    double score() const {
        double res = 0;

        for_n(i, perm.size() - 1) {
            res += (POINTS[perm[i+1]] - POINTS[perm[i]]).norm();
        }

        return res;
    }
};


/// \brief Test the simulated annealing algorithm on the TSP.
void testSimulatedAnnealing() {
    // Generate a few points
    for_n(i, 100) {
        POINTS.push_back(Vect2d((double)rand() / RAND_MAX, (double)rand() / RAND_MAX));
    }

    // Start with a random solution
    Solution sol;

    // Improve the solution
    SimulatedAnnealing<Solution> sa(1);
    sa.optimize(sol, 100000);

    // Make sure the solution is good enough
    assert(sa.m_bestScore < 15);

    // To plot the solution, print it and pass it to the following Python script in the S variable
    /*for (int i : sa.m_bestState.perm) {
        cerr << POINTS[i].x << " " << POINTS[i].y << endl;
    }*/

    /*import matplotlib.pyplot as plt

    points = []
    for l in S.split('\n'):
        points.append((float(l.split()[0]), float(l.split()[1])))

    x_coords, y_coords = zip(*points)
    plt.plot(x_coords, y_coords, marker='o')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('2D Points Plot')
    plt.grid(True)
    plt.show()*/

    show_test_done("Simulated annealing");
}
