#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "comparator.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("comparator methods", "[comparator]")
{
  vector<Nucleotide> first;
  first.push_back(Nucleotide(NucleotideLetter(0x03)));
  first.push_back(Nucleotide(NucleotideLetter(0x01)));
  first.push_back(Nucleotide(NucleotideLetter(0x01)));
  first.push_back(Nucleotide(NucleotideLetter(0x02)));
  first.push_back(Nucleotide(NucleotideLetter(0x00)));
  first.push_back(Nucleotide(NucleotideLetter(0x03)));

  vector<Nucleotide> second;
  second.push_back(Nucleotide(NucleotideLetter(0x00)));
  second.push_back(Nucleotide(NucleotideLetter(0x01)));
  second.push_back(Nucleotide(NucleotideLetter(0x02)));
  second.push_back(Nucleotide(NucleotideLetter(0x00)));
  second.push_back(Nucleotide(NucleotideLetter(0x02)));
  second.push_back(Nucleotide(NucleotideLetter(0x01)));

  const Overlap overlap = compare(first, second);
  const uint32_t overlapFirstEnd = overlap.getEndFirst();
  const uint32_t overlapSecondEnd = overlap.getEndSecond();
  const uint32_t overlapFirstStart = overlap.getStartFirst();
  const uint32_t overlapSecondStart = overlap.getStartSecond();
  const int overlapLength = overlapFirstEnd - overlapFirstStart + 1;

  SECTION("check overlap length")
  {
    REQUIRE(overlapLength == 3);
  }

  SECTION("check overlap values")
  {
    REQUIRE(first[overlapFirstStart].getValue() == 1);
    REQUIRE(first[overlapFirstStart + 1].getValue() == 2);
    REQUIRE(first[overlapFirstStart + 2].getValue() == 0);

    REQUIRE(second[overlapSecondStart].getValue() == 1);
    REQUIRE(second[overlapSecondStart + 1].getValue() == 2);
    REQUIRE(second[overlapSecondStart + 2].getValue() == 0);
  }
}
