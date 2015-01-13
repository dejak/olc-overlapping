#ifndef NUCLEOTIDES_HPP_
#define NUCLEOTIDES_HPP_

#include <vector>
#include <string>

#include "nucleotide.hpp"

namespace OLC
{

// Wrapper class for a vector of Nucleotide objects to enable moving and disable copying. 
class Nucleotides
{
  private:
    std::vector<Nucleotide> sequence_;

  public:
    Nucleotides();
    Nucleotides(const std::vector<OLC::Nucleotide>& sequence);

    // disable copying

    Nucleotides(const Nucleotides& copy) = delete;
    Nucleotides& operator=(const Nucleotides& copy) = delete;

    // enable moving

    Nucleotides(Nucleotides&& move);
    Nucleotides& operator=(Nucleotides&& move);

    const std::vector<Nucleotide>& getSequence() const;
    std::string toString() const;
    void push_back(const Nucleotide& nucleotide);
    void reserve(const std::size_t size);
};

}

#endif // NUCLEOTIDES_HPP_
