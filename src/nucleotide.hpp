#ifndef NUCLEOTIDE_HPP_
#define NUCLEOTIDE_HPP_

#include <cstdint>

namespace OLC
{

enum NucleotideLetter : char
{
  A = 0x00,
  T = 0x01,
  C = 0x02,
  G = 0x03
};

#pragma pack(1)
class Nucleotide
{
  private:
    uint32_t value_ : 2;

  public:
    Nucleotide(const NucleotideLetter nucleotide);

    char getNucleotide() const;
    int getValue() const;

    bool operator==(const Nucleotide &other) const {
      return this->value_ == other.getValue();
    }
};

}

#endif // NUCLEOTIDE_HPP_
