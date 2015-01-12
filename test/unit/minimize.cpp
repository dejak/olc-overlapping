#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "minimizator.hpp"

TEST_CASE("minimize", "[minimize")
{
  std::vector<OLC::Nucleotide> vec;

  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x02)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x03)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x00)));
  vec.push_back(OLC::Nucleotide(OLC::NucleotideLetter(0x01)));

  auto minimizers = minimize(vec, 3, 3);

  SECTION("test minimizer size")
  {
    REQUIRE(minimizers.size() == 13);
  }

  SECTION("test minimizer values")
  {
    const OLC::Minimizer minimizer1(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x01), OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x03)}, 0);
    const OLC::Minimizer minimizer2(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x03), OLC::NucleotideLetter(0x02)}, 0);
    const OLC::Minimizer minimizer3(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x03), OLC::NucleotideLetter(0x02)}, 0);
    const OLC::Minimizer minimizer4(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x03), OLC::NucleotideLetter(0x02)}, 0);
    const OLC::Minimizer minimizer5(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x01), OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x01)}, 0);
    const OLC::Minimizer minimizer6(std::vector<OLC::Nucleotide>{OLC::NucleotideLetter(0x00), OLC::NucleotideLetter(0x01), OLC::NucleotideLetter(0x02)}, 0);

    REQUIRE(minimizers.at(0) == minimizer1);
    REQUIRE(minimizers.at(1) == minimizer2);
    REQUIRE(minimizers.at(2) == minimizer3);
    REQUIRE(minimizers.at(3) == minimizer4);
    REQUIRE(minimizers.at(4) == minimizer5);
    REQUIRE(minimizers.at(5) == minimizer6);
  }
}
