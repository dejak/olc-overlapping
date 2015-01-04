#ifndef READER_HPP_
#define READER_HPP_

#include <vector>
#include <memory>

#include "sequence.hpp"

namespace OLC
{

class Reader
{
  public:
    virtual const std::vector<std::unique_ptr<OLC::Sequence>> readSequences() = 0;
};

}

#endif // READER_HPP_
