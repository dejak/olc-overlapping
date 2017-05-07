#ifndef INPUT_READER_HPP_
#define INPUT_READER_HPP_

#include <vector>

namespace OLC
{

class Sequence;

class InputReader
{
  public:
    virtual std::vector<Sequence*> readSequences() = 0;
    virtual ~InputReader() = default;
};

}

#endif // INPUT_READER_HPP_
