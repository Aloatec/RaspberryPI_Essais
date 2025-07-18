#include <ProjetSuperDurDll.h>
#include <boost/test/unit_test.hpp>

namespace test2
{
BOOST_AUTO_TEST_SUITE(Math2)

BOOST_AUTO_TEST_CASE(Math_AdditionFonctionne)
{
    BOOST_CHECK_EQUAL(2 + 6, 8);
}

BOOST_AUTO_TEST_CASE(multiplication2)
{
    BOOST_CHECK_EQUAL(addition(5, 9), 14);
}

BOOST_AUTO_TEST_SUITE_END()
} // namespace test2