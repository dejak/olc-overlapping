#ifndef READER_HPP_
#define READER_HPP_

#include <string>
#include <vector>

namespace OLC
{

class FASTQSequence;
class FASTQReader
{
  private:
    std::string filename_;
    std::vector<FASTQSequence> sequences_;

  public:
    FASTQReader(const std::string& filename);
    ~FASTQReader();

    const std::vector<FASTQSequence>& readSequences();
};

}

#endif  // READER_HPP_
