#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "overlap.hpp"
#include "result.hpp"
#include "comparator.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("result class", "[result]")
{

  vector<Nucleotide> vec1;
  vec1.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec1.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec1.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec1.push_back(Nucleotide(NucleotideLetter(0x00)));
  vec1.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec1.push_back(Nucleotide(NucleotideLetter(0x02)));

  vector<Nucleotide> vec2;
  vec2.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x00)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec2.push_back(Nucleotide(NucleotideLetter(0x01)));

  const Overlap overlap = compare(vec1, vec2);
  const uint32_t overlapFirstEnd = overlap.getEndFirst();
  const uint32_t overlapSecondEnd = overlap.getEndSecond();
  const uint32_t overlapFirstStart = overlap.getStartFirst();
  const uint32_t overlapSecondStart = overlap.getStartSecond();
  const uint32_t overlapLength = overlapFirstEnd - overlapFirstStart + 1;

  int32_t ahang = overlapFirstStart;
  int32_t bhang = vec2.size() - overlapSecondEnd - 1;

  if (overlapSecondStart < overlapFirstStart)
    ahang *= -1;

  if (vec1.size() > overlapSecondEnd)
    bhang *= -1;
	
  Result result(1, 2, overlapLength, ahang, bhang);


  SECTION("check length")
  {
  	REQUIRE(result.getLength() == 3);
  }

  SECTION("check ahang and bhang") 
  {
  	REQUIRE(result.getAhng() == 1);
  	REQUIRE(result.getBhng() == -2);
  }

  const Overlap overlapReverse = compare(vec2, vec1);
  int32_t ahangReverse = overlapReverse.getStartFirst();
  int32_t bhangReverse = vec1.size() - overlapReverse.getEndSecond() - 1;
  
  if (overlapReverse.getStartSecond() < overlapReverse.getStartFirst()) {
  	ahangReverse *= -1;
  }

  if (vec2.size() > overlapReverse.getEndSecond()) {
  	bhangReverse *= -1;
  }

  SECTION("check ahang and bhang in reverse case") 
  {
  	REQUIRE(ahangReverse == -2);
  	REQUIRE(bhangReverse == -2);
  }

  vector<Nucleotide> vec3;
  vec3.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec3.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec3.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec3.push_back(Nucleotide(NucleotideLetter(0x02)));
  
  vector<Nucleotide> vec4;
  vec4.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec4.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec4.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec4.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec4.push_back(Nucleotide(NucleotideLetter(0x01)));

  const Overlap overlapEnd = compare(vec4, vec3);
  int32_t ahangEnd = overlapEnd.getStartFirst();
  int32_t bhangEnd = vec4.size() - overlapEnd.getEndSecond() -1;

  if (overlapEnd.getStartSecond() < overlapEnd.getStartFirst()) {
  	ahangEnd *= -1;
  }

  if (vec4.size() > overlapEnd.getEndSecond()) {
  	bhangEnd *= -1;
  }

  SECTION("check possible negative ahang/bhang in a trivial case")
  {
  	REQUIRE(ahangEnd == 1);
  	REQUIRE(bhangEnd == -1);
  }

}