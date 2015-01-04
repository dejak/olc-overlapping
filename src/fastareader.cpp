#include "fastareader.hpp"

#include <random>
#include <fstream>
#include <iostream>
#include <iostream>

#include "sequence.hpp"

namespace OLC
{

FASTAReader::FASTAReader(const std::string& filename)
  : Reader(),
    filename_(filename)
{

}

FASTAReader::~FASTAReader() {

}

const std::vector<std::unique_ptr<OLC::Sequence>> FASTAReader::readSequences()
{
  std::ifstream input(filename_);
  std::vector<std::unique_ptr<Sequence>> sequences;

  // TODO (josko): throw?

  if (input.fail())
    return sequences;

  while (!input.eof())
  {
    std::string identifier;
    std::getline(input, identifier);

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

    std::string sequence;
    std::string nucleotides;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, 3);
    std::unique_ptr<Nucleotides> nucleotideSequence(new Nucleotides());
    nucleotideSequence.get()->reserve(sequence.size());

    std::getline(input, sequence);

    for (const auto c : sequence)
    {
      switch (c)
      {
        case 'A': nucleotideSequence.get()->push_back(NucleotideLetter::A); break;
        case 'T': nucleotideSequence.get()->push_back(NucleotideLetter::T); break;
        case 'C': nucleotideSequence.get()->push_back(NucleotideLetter::C); break;
        case 'G': nucleotideSequence.get()->push_back(NucleotideLetter::G); break;
        case '-':
        {
          const uint32_t randomNucleotide = distribution(generator);
          const NucleotideLetter nucleotide = static_cast<NucleotideLetter>(randomNucleotide);
          nucleotideSequence.get()->push_back(nucleotide);
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

    // quality is ignored

    std::string quality;
    std::getline(input, quality);

    if (!identifier.empty() && !sequence.empty() && !plus.empty() && !quality.empty())
    {
      std::unique_ptr<Sequence> pointer(new Sequence(identifier, description, std::move(nucleotideSequence)));
      sequences.push_back(std::move(pointer));
    }
  }

  input.close();

  return sequences;
}

}

