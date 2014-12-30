#include "sequence.hpp"

namespace OLC
{

FASTQSequence::FASTQSequence(const std::string& identifier, const std::string& description, const OLC::NucleotideSequence& nucleotides, const std::string& quality)
  : identifier_(identifier),
    description_(description),
    nucleotides_(nucleotides),
    quality_(quality)
{

}

FASTQSequence::~FASTQSequence()
{

}

}
