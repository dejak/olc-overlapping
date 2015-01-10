#ifndef INPUT_FILE_READER_HPP_
#define INPUT_FILE_READER_HPP_

#include <fstream>

#include "input_reader.hpp"

namespace OLC
{

class InputFileReader : public InputReader
{
  public:
    InputFileReader(const std::string& filename);
    ~InputFileReader();

    std::vector<OLC::Sequence*> readSequences();

  private:
    std::ifstream in_;
};

}

#endif // INPUT_FILE_READER_HPP_
