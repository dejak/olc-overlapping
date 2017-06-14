#ifndef FORMAT_PARSER_HPP_
#define FORMAT_PARSER_HPP_

#include <vector>
#include <fstream>

#include "sequence.hpp"
#include "nucleotide.hpp"

namespace OLC
{

// Interface enabling parsing of both FASTA and FASTQ formats for program inputs
class FormatParser
{
  public:
    virtual const std::vector<OLC::Sequence*> readSequences() = 0;
    virtual ~FormatParser() = default;

  protected:
    std::ifstream& in_;

    FormatParser(std::ifstream& in) noexcept : in_(in)
    {
    }

    // Used for replacing gaps in error prone reads with random nucleotides as 
    // overlap algorithms should still be able to handle it.
    NucleotideLetter getRandomNucleotide() const;
};

}

#endif // FORMAT_PARSER_HPP_
