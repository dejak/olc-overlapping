#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "nucleotide.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("nucleotide class", "[nucleotide]")
{
  const Nucleotide zero{NucleotideLetter(0x00)};
  const Nucleotide one{NucleotideLetter(0x01)};
  const Nucleotide two{NucleotideLetter(0x02)};

  SECTION("test equality operator")
  {
    REQUIRE(zero == zero);
    REQUIRE(one == one);
    REQUIRE(two == two);

    // test inequality like this because we haven't overriden the != operator
    REQUIRE((zero == one) == false);
    REQUIRE((one == two) == false);
  }
}
