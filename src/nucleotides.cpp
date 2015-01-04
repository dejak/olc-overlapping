#include "nucleotides.hpp"

namespace OLC
{

Nucleotides::Nucleotides()
{

}

Nucleotides::Nucleotides(const std::vector<Nucleotide>& sequence)
  : sequence_(sequence)
{

}

void Nucleotides::reserve(const std::size_t size)
{
  sequence_.reserve(size);
}

void Nucleotides::push_back(const Nucleotide& nucleotide)
{
  sequence_.push_back(nucleotide);
}

std::string Nucleotides::toString() const
{
  std::string stringRepresentation = std::string();
  stringRepresentation.reserve(sequence_.size());

  for (const auto c : sequence_)
    stringRepresentation.push_back(c.getNucleotide());

  return stringRepresentation;
}

std::vector<Nucleotide> Nucleotides::getSequence() const
{
  return sequence_;
}

}
