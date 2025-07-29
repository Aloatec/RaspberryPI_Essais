#include <ProjetSuperDurDll.h>
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <chrono>
#include <thread>

struct Math2Init
{
    static constexpr int nTestValue = 10;

    Math2Init() : test(nTestValue) // Initialisation de la variable test
    {
        // Code exécuté avant TOUS les tests de la suite
        BOOST_TEST_MESSAGE("Setup for suite");
    }

    int test;
};

BOOST_FIXTURE_TEST_SUITE(Math2, Math2Init)

BOOST_AUTO_TEST_CASE(Math_AdditionFonctionne)
{
    BOOST_CHECK_EQUAL(2 + 6, 8);
    BOOST_CHECK_EQUAL(test - 5, 5);

    BOOST_TEST(2 + 5 == 7);
}

BOOST_AUTO_TEST_CASE(multiplication2)
{
    BOOST_CHECK_EQUAL(addition(5, 9), 14);
}

BOOST_DATA_TEST_CASE(test_even_numbers, std::vector({2, 4, 6, 8}), value)
{
    BOOST_TEST(value % 2 == 0);
}

BOOST_AUTO_TEST_CASE(test_perf, *boost::unit_test::timeout(2)) // 2 secondes
{
    const int nTimeSleep = 10;
    std::this_thread::sleep_for(std::chrono::milliseconds(nTimeSleep));
}

BOOST_AUTO_TEST_SUITE_END()
