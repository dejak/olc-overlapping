#include "sequence.hpp"

namespace OLC
{

Sequence::Sequence(const std::string& identifier, const std::string& description, std::unique_ptr<OLC::Nucleotides> nucleotides)
  : identifier_(identifier),
    description_(description),
    nucleotides_(std::move(nucleotides))
{

}

Sequence::~Sequence()
{

}

}
