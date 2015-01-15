#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "minimize.hpp"

using namespace std;
using namespace OLC;

TEST_CASE("minimize", "[minimize]")
{
  vector<Nucleotide> vec;

  vec.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec.push_back(Nucleotide(NucleotideLetter(0x00)));
  vec.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec.push_back(Nucleotide(NucleotideLetter(0x00)));
  vec.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec.push_back(Nucleotide(NucleotideLetter(0x02)));
  vec.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec.push_back(Nucleotide(NucleotideLetter(0x03)));
  vec.push_back(Nucleotide(NucleotideLetter(0x01)));
  vec.push_back(Nucleotide(NucleotideLetter(0x00)));
  vec.push_back(Nucleotide(NucleotideLetter(0x01)));

  auto* minimizers = minimize(vec, 3, 3);

  SECTION("test minimizer size")
  {
    REQUIRE(minimizers->size() == 7);
  }

  SECTION("test minimizer values")
  {
    Minimizer minimizer0(vector<Nucleotide>{NucleotideLetter(0x00), NucleotideLetter(0x01), NucleotideLetter(0x02)}, 0);
    Minimizer minimizer1(vector<Nucleotide>{NucleotideLetter(0x00), NucleotideLetter(0x03), NucleotideLetter(0x02)}, 0);
    Minimizer minimizer2(vector<Nucleotide>{NucleotideLetter(0x01), NucleotideLetter(0x00), NucleotideLetter(0x01)}, 0);
    Minimizer minimizer3(vector<Nucleotide>{NucleotideLetter(0x01), NucleotideLetter(0x00), NucleotideLetter(0x03)}, 0);
    Minimizer minimizer4(vector<Nucleotide>{NucleotideLetter(0x01), NucleotideLetter(0x02), NucleotideLetter(0x03)}, 0);
    Minimizer minimizer5(vector<Nucleotide>{NucleotideLetter(0x02), NucleotideLetter(0x03), NucleotideLetter(0x01)}, 0);
    Minimizer minimizer6(vector<Nucleotide>{NucleotideLetter(0x02), NucleotideLetter(0x03), NucleotideLetter(0x03)}, 0);

    REQUIRE(minimizers->at(0) == minimizer0);
    REQUIRE(minimizers->at(1) == minimizer1);
    REQUIRE(minimizers->at(2) == minimizer2);
    REQUIRE(minimizers->at(3) == minimizer3);
    REQUIRE(minimizers->at(4) == minimizer4);
    REQUIRE(minimizers->at(5) == minimizer5);
    REQUIRE(minimizers->at(6) == minimizer6);
  }
}
