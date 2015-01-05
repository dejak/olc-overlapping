#ifndef FASTA_READER_HPP_
#define FASTA_READER_HPP_

#include <fstream>

#include "format_reader.hpp"

namespace OLC
{

class FASTAReader : protected IFormatReader
{
  public:
    FASTAReader(std::ifstream& in);
    ~FASTAReader();

    const std::vector<std::unique_ptr<OLC::Sequence>> readSequences();
};

}

#endif // FASTA_READER_HPP_
