#define CATCH_CONFIG_MAIN // This tells the Catch2 header to generate a main

#include "catch.hpp"

////////////////////////////////////////////////////////////////
SCENARIO("Test1", "[test][tags]")
{
  GIVEN("X")
  {
    int x = 1;
    WHEN("Y")
    {
      int y = 1;
      THEN("Z")
      {
        REQUIRE(x + y == 2);
      }
    }
  }
}
