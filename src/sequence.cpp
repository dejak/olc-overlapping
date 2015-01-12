#include "sequence.hpp"

namespace OLC
{

Sequence::Sequence(const std::string& identifier, const std::string& description, OLC::Nucleotides* nucleotides)
  : identifier_(identifier),
    description_(description),
    nucleotides_(nucleotides)
{

}

Sequence::~Sequence()
{
  if (nucleotides_ != nullptr)
    delete nucleotides_;
}

}
