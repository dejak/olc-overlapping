#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "minimizator.hpp"

#include <iostream>

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
    //REQUIRE(minimizers.size() == 13);
  }

  SECTION("test minimizer values")
  {
    for (auto mini : minimizers)
    {
      std::cout << "mini = " << mini.toString() << "\n";
    }
  }
}
