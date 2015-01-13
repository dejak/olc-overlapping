#include "nucleotide.hpp"

namespace OLC
{

Nucleotide::Nucleotide(const NucleotideLetter nucleotide)
  : value_(static_cast<int>(nucleotide))
{

}

char Nucleotide::getNucleotide() const
{
  switch (value_)
  {
    case 0x00: return 'A';
    case 0x01: return 'T';
    case 0x02: return 'C';
    case 0x03: return 'G';
    default:   return '?';
  }
}

int Nucleotide::getValue() const
{
  return value_;
}

}
