#ifndef FORMAT_READER_HPP_
#define FORMAT_READER_HPP_

#include <vector>
#include <memory>
#include <fstream>

#include "sequence.hpp"
#include "nucleotide.hpp"

namespace OLC
{

class IFormatReader
{
  public:
    virtual const std::vector<std::unique_ptr<OLC::Sequence>> readSequences() = 0;

  protected:
    std::ifstream& in_;

    IFormatReader(std::ifstream& in);
    virtual ~IFormatReader();

    NucleotideLetter getRandomNucleotide() const;
};

}

#endif // FORMAT_READER_HPP_
