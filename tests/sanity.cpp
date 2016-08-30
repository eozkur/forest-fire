#include "catch.hpp"

unsigned int AddOneTo(unsigned int input)
{
    return (input + 1);
}

TEST_CASE("Sanity Check")
{
    REQUIRE(0 == 0);
    REQUIRE(1 == AddOneTo(0));
}
