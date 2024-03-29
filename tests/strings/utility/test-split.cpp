#include <cassert>

#include "strings/utility/split.hpp"
#include "test-done.hpp"
#include "test-split.hpp"

void testSplit()
{
    {
        auto res = split("  abcd efg  hij ", ' ');
        assert(res.size() == 3);
        assert(res[0] == "abcd");
        assert(res[1] == "efg");
        assert(res[2] == "hij");
    }

    {
        auto res = split("abcd,efg , hij", {' ', ','});
        assert(res.size() == 3);
        assert(res[0] == "abcd");
        assert(res[1] == "efg");
        assert(res[2] == "hij");
    }

    show_test_done("Split");
}
