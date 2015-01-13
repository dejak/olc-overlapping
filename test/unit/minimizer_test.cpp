#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "minimize.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("minimizer methods", "[minimizer]")
{
  const Minimizer low(vector<Nucleotide>{NucleotideLetter(0x00), NucleotideLetter(0x01), NucleotideLetter(0x02)}, 0);
  const Minimizer mid(vector<Nucleotide>{NucleotideLetter(0x02), NucleotideLetter(0x02), NucleotideLetter(0x02)}, 0);
  const Minimizer high(vector<Nucleotide>{NucleotideLetter(0x03), NucleotideLetter(0x02), NucleotideLetter(0x01)}, 0);

  SECTION("test equality operator")
  {
    REQUIRE(low == low);
    REQUIRE(mid == mid);
    REQUIRE(high == high);

    // test inequality like this because we haven't overriden the != operator
    REQUIRE((low == mid) == false);
    REQUIRE((low == high) == false);
    REQUIRE((mid == high) == false);
  }

  SECTION("test less than operator")
  {
    REQUIRE(low < mid);
    REQUIRE(mid < high);
    REQUIRE(low < high);
  }

  SECTION("value string representation test")
  {
    REQUIRE(low.toValueString() == "012");
    REQUIRE(mid.toValueString() == "222");
    REQUIRE(high.toValueString() == "321");
  }

  SECTION("nucleotide string representation test")
  {
    REQUIRE(low.toNucleotideString() == "ATC");
    REQUIRE(mid.toNucleotideString() =="CCC");
    REQUIRE(high.toNucleotideString() == "GCT");
  }

  SECTION("element access test")
  {
    REQUIRE(low[0].getValue() == 0);
    REQUIRE(low[1].getValue() == 1);
    REQUIRE(low[2].getValue() == 2);

    REQUIRE(mid[0].getValue() == 2);
    REQUIRE(mid[1].getValue() == 2);
    REQUIRE(mid[2].getValue() == 2);

    REQUIRE(high[0].getValue() == 3);
    REQUIRE(high[1].getValue() == 2);
    REQUIRE(high[2].getValue() == 1);
  }
}
