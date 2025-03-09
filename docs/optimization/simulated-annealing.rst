Simulated annealing
===================

:cpp:class:`SimulatedAnnealing` can minimize a function using the simulated annealing algorithm. Ths solution is
progressively improved by performing small changes to it.

The user must define a solution struct representing a solution to the problem. The struct must define the following
methods:

..  code-block:: c++
    :caption: Solution struct

    struct Solution {
        Solution() {
            // ...
        }

        Solution randomNeighbor() const {
            // ...
        }

        double score() const {
            // ...
        }
    };

Then, the user can create a :cpp:class:`SimulatedAnnealing` object and call the :cpp:func:`SimulatedAnnealing::minimize`
method to minimize the function.

.. code-block:: c++
    :caption: Finding a good solution

    Solution sol;

    SimulatedAnnealing<Solution> sa(1);
    sa.minimize(sol, 100000);

    cout << sa.m_bestScore << endl;>>

.. doxygenclass:: SimulatedAnnealing
