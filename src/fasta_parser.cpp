#include "fasta_parser.hpp"

#include <iostream>
#include <limits>

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
    char nextChar = FormatParser::in_.peek();

    if (nextChar == ';')
    {
      // comment line, ignore

      FormatParser::in_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    else
    {
      std::string line;
      std::getline(FormatParser::in_, line);

      if (line.size() == 0)
        continue;

      std::string description;
      std::string identifier;
      std::string sequence;

      if (line.at(0) == '>')
      {
        // cut the initial '>' off

        line = line.substr(1);

        const std::size_t delimiterIndex = line.find('|');

        if (delimiterIndex != std::string::npos)
        {
          description = line.substr(delimiterIndex + 1);
          identifier = line.substr(0, delimiterIndex);
        }
      }
      else
      {
        sequence = line;
      }

      Nucleotides* nucleotides = new Nucleotides();

      if (sequence.empty())
        nextChar = FormatParser::in_.peek();
      else
        nextChar = 'A';

      while (nextChar != '>' && !FormatParser::in_.eof())
      {
        if (sequence.empty())
          std::getline(FormatParser::in_, sequence);

        if (sequence.size() == 0)
        {
          nextChar = FormatParser::in_.peek();
          continue;
        }

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

      Sequence *fasta_sequence = new Sequence(identifier, description, nucleotides);
      sequences.push_back(fasta_sequence);
    }
  }

  return sequences;
}

}

