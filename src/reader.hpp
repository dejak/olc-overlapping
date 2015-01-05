#ifndef READER_HPP_
#define READER_HPP_

#include "sequence.hpp"

namespace OLC
{

class InputReader
{
  public:
    virtual const std::vector<std::unique_ptr<OLC::Sequence>> readSequences() = 0;
};

}

#endif // READER_HPP_
