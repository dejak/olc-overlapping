#ifndef FASTQ_PARSER_HPP_
#define FASTQ_PARSER_HPP_

#include <vector>

#include "format_parser.hpp"

namespace OLC
{

// Implementation of FormatParser for the FASTQ format
class FASTQParser final : protected FormatParser
{
  public:
    FASTQParser(std::ifstream& in);
    ~FASTQParser();

    const std::vector<Sequence*> readSequences() override;
};

}

#endif // FASTQ_PARSER_HPP_
