#include "fasta_parser.hpp"

namespace OLC
{

FASTAParser::FASTAParser(std::ifstream& in)
  : FormatParser(in)
{

}

FASTAParser::~FASTAParser()
{

}

const std::vector<OLC::Sequence*> FASTAParser::readSequences()
{
  std::vector<OLC::Sequence*> sequences;

  if (FormatParser::in_.fail())
    return sequences;

  while (!FormatParser::in_.eof())
  {
    std::string identifier;
    std::getline(FormatParser::in_, identifier);

    // comment line, ignore

    if (identifier.at(0) == ';')
      continue;

    // invalid line, try to start over

    if (identifier.empty() || (identifier.at(0) != '>'))
      continue;

    // cut the initial '>' off

    identifier = identifier.substr(1);

    std::string description;
    const std::size_t delimiterIndex = identifier.find('|');

    if (delimiterIndex != std::string::npos)
    {
      description = identifier.substr(delimiterIndex + 1);
      identifier = identifier.substr(0, delimiterIndex);
    }

    Nucleotides* nucleotides = new Nucleotides();

    char nextChar = FormatParser::in_.peek();

    while (nextChar != '>')
    {
      std::string sequence;
      std::getline(FormatParser::in_, sequence);

      for (const auto c : sequence)
      {
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

      nextChar = FormatParser::in_.peek();
    }

    Sequence *sequence = new Sequence(identifier, description, nucleotides);
    sequences.push_back(sequence);
  }

  return sequences;
}

}

