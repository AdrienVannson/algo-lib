#include "test-two-sat.hpp"
#include "test-done.hpp"
#include "two-sat.hpp"

void testTwoSat()
{
    const int x = 0, y = 1, z = 2;

    {
        TwoSat inst(3);
        inst.addConstraint(x, inst.neg(x));
        inst.addConstraint(z);
        inst.addConstraint(x, y);
        inst.addConstraint(x, inst.neg(y));
        inst.addConstraint(inst.neg(y), inst.neg(z));

        assert(inst.solve());
        assert(inst.isTrue(x));
        assert(!inst.isTrue(y));
        assert(inst.isTrue(z));
    }

    {
        TwoSat inst(3);
        inst.addConstraint(inst.neg(x), y);
        inst.addConstraint(inst.neg(y), inst.neg(x));
        inst.addConstraint(x, inst.neg(z));
        inst.addConstraint(z, x);

        assert(!inst.solve());
    }

    show_test_done("2-SAT");
}
