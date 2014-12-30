#include "nucleotidesequence.hpp"

#include "nucleotide.hpp"

namespace OLC
{

NucleotideSequence::NucleotideSequence()
{

}

void NucleotideSequence::reserve(const std::size_t size)
{
  sequence_.reserve(size);
}

void NucleotideSequence::push_back(const Nucleotide& nucleotide)
{
  sequence_.push_back(nucleotide);
}

std::string NucleotideSequence::toString() const
{
  std::string stringRepresentation = std::string();
  stringRepresentation.reserve(sequence_.size());

  for (const auto c : sequence_)
    stringRepresentation.push_back(c.getNucleotide());

  return stringRepresentation;
}

std::vector<Nucleotide> NucleotideSequence::getSequence() const
{
  return sequence_;
}

}
