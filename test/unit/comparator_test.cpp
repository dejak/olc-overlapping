#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "comparator.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("comparator methods", "[comparator]")
{
  const vector<int> first({3,1,1,2,4,3});
  const vector<int> second({4,1,2,4,2,1});
  const vector<OLC::Position> overlapPath = OLC::compare(first, second);
  const uint32_t overlapFirstEnd = overlapPath[0].get(0);
  const uint32_t overlapSecondEnd = overlapPath[0].get(1);
  const uint32_t overlapFirstStart = overlapPath[overlapPath.size() - 1].get(0);
  const uint32_t overlapSecondStart = overlapPath[overlapPath.size() - 1].get(1);

  SECTION("check overlap length")
  {
    REQUIRE(overlapPath.size() == 3);
  }

  SECTION("check overlap values")
  {
    REQUIRE(first[overlapFirstStart] == 1);
    REQUIRE(first[overlapFirstStart + 1] == 2);
    REQUIRE(first[overlapFirstStart + 2] == 4);

    REQUIRE(second[overlapSecondStart] == 1);
    REQUIRE(second[overlapSecondStart + 1] == 2);
    REQUIRE(second[overlapSecondStart + 2] == 4);
  }
}
