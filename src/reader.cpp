#include "reader.hpp"

#include <fstream>
#include <iostream>

#include "sequence.hpp"

namespace FASTQ {

Reader::Reader(const std::string& filename)
  : _filename(filename)
{
  
}

Reader::~Reader() {

}

std::vector<Sequence>& Reader::_readSequences()
{
  std::ifstream input(_filename);
  _sequences = std::vector<Sequence>();

  if (input.fail())
    return _sequences;

  // TODO (josko): check legal characters
  // TODO (josko): potentially generate minimizers here

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
    std::getline(input, sequence);

    std::string plus;
    std::getline(input, plus);

    // invalid line, try to start over

    if (plus.empty() || plus.at(0) != '+')
      continue;

    std::string quality;
    std::getline(input, quality);

    if (!identifier.empty() && !sequence.empty() && !plus.empty() && !quality.empty())
    {
      _sequences.push_back(Sequence(identifier, description, sequence, quality));
    }
  }

  input.close();

  return _sequences;
}

}

