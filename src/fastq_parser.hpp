#ifndef FASTQ_PARSER_HPP_
#define FASTQ_PARSER_HPP_

#include <vector>

#include "format_parser.hpp"

namespace OLC
{

class FASTQParser : protected FormatParser
{
  public:
    FASTQParser(std::ifstream& in);
    ~FASTQParser();

    const std::vector<OLC::Sequence*> readSequences() override;
};

}

#endif // FASTQ_PARSER_HPP_
