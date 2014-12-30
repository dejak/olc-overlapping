#ifndef NUCLEOTIDE_SEQUENCE_HPP_
#define NUCLEOTIDE_SEQUENCE_HPP_

#include <vector>
#include <string>

#include "nucleotide.hpp"

namespace OLC
{

class NucleotideSequence
{
  private:
    std::vector<Nucleotide> sequence_;

  public:
    NucleotideSequence();

    std::string toString() const;
    void push_back(const Nucleotide& nucleotide);
    void reserve(const std::size_t size);
    std::vector<Nucleotide> getSequence() const;
};

}

#endif // NUCLEOTIDE_SEQUENCE_HPP_
