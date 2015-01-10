#ifndef FORMAT_PARSER_HPP_
#define FORMAT_PARSER_HPP_

#include <vector>
#include <fstream>

#include "sequence.hpp"
#include "nucleotide.hpp"

namespace OLC
{

class FormatParser
{
  public:
    virtual const std::vector<OLC::Sequence*> readSequences() = 0;
    virtual ~FormatParser();

  protected:
    std::ifstream& in_;

    FormatParser(std::ifstream& in);

    NucleotideLetter getRandomNucleotide() const;
};

}

#endif // FORMAT_PARSER_HPP_
