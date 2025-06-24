#define CATCH_CONFIG_MAIN
#include <catch.hpp>

namespace tests {

    TEST_CASE("Addition fonctionne", "[math]") {
        REQUIRE(1 + 1 == 2);
        REQUIRE(2 + 2 == 4);
    }
}
