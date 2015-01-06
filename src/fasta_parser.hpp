#ifndef FASTA_PARSER_HPP_
#define FASTA_PARSER_HPP_

#include <fstream>

#include "format_parser.hpp"

namespace OLC
{

class FASTAParser : protected FormatParser
{
  public:
    FASTAParser(std::ifstream& in);
    ~FASTAParser();

    const std::vector<std::unique_ptr<OLC::Sequence>> readSequences();
};

}

#endif // FASTA_PARSER_HPP_
