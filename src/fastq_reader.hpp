#ifndef FASTQ_READER_HPP_
#define FASTQ_READER_HPP_

#include <vector>

#include "format_reader.hpp"

namespace OLC
{

class FASTQReader : protected IFormatReader
{
  public:
    FASTQReader(std::ifstream& in);
    ~FASTQReader();

    const std::vector<std::unique_ptr<OLC::Sequence>> readSequences() override;
};

}

#endif // FASTQ_READER_HPP_
