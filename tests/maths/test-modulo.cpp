#include <cassert>

#include "maths/modulo.hpp"
#include "test-done.hpp"
#include "test-modulo.hpp"

void testModulo()
{
    Modulo<int>::setMod(17);

    Modulo<int> a(12), b(7);

    assert((a + b).val() == 2);
    assert((a * b).val() == 16);

    for (int i = 1; i < 17; i++) {
        assert((int)(Modulo<int>(i).inverse() * Modulo<int>(i)) == 1);
        assert((int)(Modulo<int>(i) / Modulo<int>(i)) == 1);
    }

    show_test_done("Modulo");
}
