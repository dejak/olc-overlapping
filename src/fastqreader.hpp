#ifndef FASTQREADER_HPP_
#define FASTQREADER_HPP_

#include <string>
#include <vector>

#include "reader.hpp"
#include "sequence.hpp"

namespace OLC
{

class FASTQReader : public Reader
{
  private:
    std::string filename_;

  public:
    FASTQReader(const std::string& filename);
    ~FASTQReader();

    const std::vector<std::unique_ptr<OLC::Sequence>> readSequences() override;
};

}

#endif // FASTQREADER_HPP_
