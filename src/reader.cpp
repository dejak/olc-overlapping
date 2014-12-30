#include "reader.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <iostream>

#include "nucleotide.hpp"
#include "nucleotidesequence.hpp"
#include "sequence.hpp"

namespace OLC
{

FASTQReader::FASTQReader(const std::string& filename)
  : filename_(filename)
{

}

FASTQReader::~FASTQReader() {

}

const std::vector<FASTQSequence>& FASTQReader::readSequences()
{
  std::ifstream input(filename_);
  sequences_ = std::vector<FASTQSequence>();

  // TODO (josko): throw?

  if (input.fail())
    return sequences_;

  while (!input.eof())
  {
    std::string identifier;
    std::getline(input, identifier);

    // invalid line, try to start over

    if (identifier.empty() || identifier.at(0) != '@')
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

    std::string sequence;
    std::string nucleotides;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 3);
    std::getline(input, sequence);
    NucleotideSequence nucleotideSequence;

    nucleotideSequence.reserve(sequence.size());

    for (const auto c : sequence)
    {
      switch (c)
      {
        case 'A': nucleotideSequence.push_back(NucleotideLetter::A); break;
        case 'T': nucleotideSequence.push_back(NucleotideLetter::T); break;
        case 'C': nucleotideSequence.push_back(NucleotideLetter::C); break;
        case 'G': nucleotideSequence.push_back(NucleotideLetter::G); break;
        case '-':
        {
          const uint32_t randomNucleotide = distribution(generator);
          const NucleotideLetter nucleotide = static_cast<NucleotideLetter>(randomNucleotide);
          nucleotideSequence.push_back(nucleotide);
          break;
        }
        default:
        {
          std::cout << "ERROR: Unrecognized nucleotide " << c << " detected\n";
          break;
        }
      }
    }

    std::string plus;
    std::getline(input, plus);

    // invalid line, try to start over

    if (plus.empty() || plus.at(0) != '+')
      continue;

    std::string quality;
    std::getline(input, quality);

    if (!identifier.empty() && !sequence.empty() && !plus.empty() && !quality.empty())
      sequences_.push_back(FASTQSequence(identifier, description, nucleotideSequence, quality));
  }

  input.close();

  return sequences_;
}

}

