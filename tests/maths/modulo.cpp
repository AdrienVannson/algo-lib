#include "modulo.hpp"
#include "maths/modulo.hpp"

#include <cassert>

void testModulo()
{
    Modulo<int>::setMod(17);

    Modulo<int> a(12), b(7);

    assert((a + b).val() == 2);
    assert((a * b).val() == 16);

    showTestDone("Modulo");
}
