#include "fastq_parser.hpp"

#include <limits>

namespace OLC
{

const std::vector<Sequence*> FASTQParser::readSequences()
{
  std::vector<Sequence*> sequences;

  if (FormatParser::in_.fail())
    return sequences;

  while (!FormatParser::in_.eof())
  {
    std::string identifier;
    std::getline(FormatParser::in_, identifier);

    // invalid line, try to start over

    if (identifier.empty() || identifier[0] != '@')
      continue;

    // cut the initial '@' off

    identifier = identifier.substr(1);

    std::string description;
    const std::size_t delimiterIndex = identifier.find('|');

    if (delimiterIndex != std::string::npos)
    {
      description = identifier.substr(delimiterIndex + 1);
      identifier = identifier.substr(0, delimiterIndex);
    }

    Nucleotides* nucleotides = new Nucleotides();

    char c;
    while ((c = FormatParser::in_.get()) != EOF)
    {
#ifdef _WIN32
      if (c == '\r' || c == '\n')
        break;
#else
      if (c == '\n')
        break;
#endif

      switch (c)
      {
        case 'A': nucleotides->push_back(NucleotideLetter::A); break;
        case 'T': nucleotides->push_back(NucleotideLetter::T); break;
        case 'C': nucleotides->push_back(NucleotideLetter::C); break;
        case 'G': nucleotides->push_back(NucleotideLetter::G); break;
        case '-': nucleotides->push_back(FormatParser::getRandomNucleotide()); break;
        default: break;
      }
    }

    std::string plus;
    std::getline(FormatParser::in_, plus);

    // invalid line, try to start over

    if (plus.empty() || plus[0] != '+')
      continue;

    // ignore quality line

    FormatParser::in_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!identifier.empty() && !nucleotides->getSequence().empty() && !plus.empty())
    {
      Sequence* sequence = new Sequence(identifier, description, nucleotides);
      sequences.push_back(sequence);
    }
  }

  return sequences;
}

}

