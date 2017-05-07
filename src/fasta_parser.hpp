#ifndef FASTA_PARSER_HPP_
#define FASTA_PARSER_HPP_

#include <fstream>

#include "format_parser.hpp"

namespace OLC
{

// Implementation of FormatParser for the FASTA format
class FASTAParser final : protected FormatParser
{
  public:
    FASTAParser(std::ifstream& in);
    ~FASTAParser();

    const std::vector<OLC::Sequence*> readSequences();
};

}

#endif // FASTA_PARSER_HPP_
