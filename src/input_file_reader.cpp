#include "input_file_reader.hpp"

#include "fasta_parser.hpp"
#include "fastq_parser.hpp"

namespace OLC
{

InputFileReader::InputFileReader(const std::string& filename)
  : in_(filename)
{

}

InputFileReader::~InputFileReader()
{
  in_.close();
}

std::vector<OLC::Sequence*> InputFileReader::readSequences()
{
  const char firstCharacter = in_.peek();

  if (firstCharacter == '>' || firstCharacter == ';')
  {
    FASTAParser parser(in_);
    return parser.readSequences();
  }
  else if (firstCharacter == '@')
  {
    FASTQParser parser(in_);
    return parser.readSequences();
  }
  else
    return std::vector<OLC::Sequence*>();
}

}
