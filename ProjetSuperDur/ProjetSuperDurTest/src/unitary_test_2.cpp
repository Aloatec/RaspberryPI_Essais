#include "pch.h"
#include <ProjetSuperDurDll.h>
#include <boost/test/unit_test.hpp>

namespace test2
{
BOOST_AUTO_TEST_SUITE(Math2)

BOOST_AUTO_TEST_CASE(Math_AdditionFonctionne)
{
    BOOST_CHECK_EQUAL(2 + 6, 8);
}

BOOST_AUTO_TEST_CASE(multiplication)
{
    BOOST_CHECK_EQUAL(addition(7, 7), 13);
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace test2