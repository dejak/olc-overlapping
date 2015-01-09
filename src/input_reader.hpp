#ifndef INPUT_READER_HPP_
#define INPUT_READER_HPP_

#include "sequence.hpp"

namespace OLC
{

class InputReader
{
  public:
    virtual std::vector<std::unique_ptr<OLC::Sequence>> readSequences() = 0;
};

}

#endif // INPUT_READER_HPP_