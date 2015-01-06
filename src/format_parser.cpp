#include "format_parser.hpp"

#include <random>

namespace OLC
{

FormatParser::FormatParser(std::ifstream& in)
  : in_(in)
{

}

FormatParser::~FormatParser()
{
  in_.close();
}

NucleotideLetter FormatParser::getRandomNucleotide() const
{
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, 3);
  const uint32_t randomNucleotide = distribution(generator);
  return static_cast<NucleotideLetter>(randomNucleotide);
}

}
