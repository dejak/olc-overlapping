#ifndef FASTAREADER_HPP_
#define FASTAREADER_HPP_

#include <string>
#include <vector>

#include "reader.hpp"
#include "sequence.hpp"

namespace OLC
{

class FASTAReader : public Reader
{
  private:
    std::string filename_;

  public:
    FASTAReader(const std::string& filename);
    ~FASTAReader();

    const std::vector<std::unique_ptr<OLC::Sequence>> readSequences();
};

}

#endif // FASTAREADER_HPP_
