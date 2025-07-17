#include "pch.h"
#include <boost/test/unit_test.hpp>

namespace test
{
BOOST_AUTO_TEST_SUITE(Math)

BOOST_AUTO_TEST_CASE(addition)
{
    BOOST_CHECK_EQUAL(2 + 2, 4);
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    BOOST_CHECK_EQUAL(2 * 4, 8);
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace test
