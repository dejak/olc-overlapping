#ifndef INPUT_FILE_READER_HPP_
#define INPUT_FILE_READER_HPP_

#include <fstream>

#include "input_reader.hpp"
#include "fasta_parser.hpp"
#include "fastq_parser.hpp"

namespace OLC
{

class InputFileReader final : public InputReader
{
public:

  InputFileReader(const std::string& filename) noexcept :
    InputReader(),
    in_(std::ifstream(filename))
  {
  }


  virtual std::vector<Sequence*> readSequences() override
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
      return std::vector<Sequence*>();
  }

private:
    std::ifstream in_;

};

}

#endif // INPUT_FILE_READER_HPP_
